#include "Renderer.hpp"

// Return the camera for use outwith this object, to set/get camera position.
Camera* Renderer::GetCamera(){
    return p_camera;
}

void Renderer::SetViewport(float x, float y, float width, float height){
    m_viewportX = x;
    m_viewportY = y;
    m_viewportWidth = width;
    m_viewportHeight = height;
}

void Renderer::SetWindowDimensions(int windowWidth, int windowHeight){
    this->m_windowWidth = windowWidth;
    this->m_windowHeight = windowHeight;
    
    // Update viewport so its size is appropriate for the new window!
    int width, height;
    glfwGetFramebufferSize(p_window, &width, &height);
}

// Initialise the Renderer for this viewport
Renderer::Renderer(GLFWwindow* window, SceneGraph* scene, Camera* viewCamera) {
    int profiler = ProfilerService::GetInstance()->StartTimer("Renderer Initialisation");

    // Assign the variables to the object
    this->p_scene = scene;
    this->p_camera = viewCamera;
    this->p_window = window;

    // Grab the window dimensions for the current window, saves passing too many arguments to the constructor
    glfwGetWindowSize(p_window, &m_windowWidth, &m_windowHeight);

    // On high DPI, there are a higher number of pixels in the window than the length of the window, so we need to use the frameWidth and height,
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);

    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    {
    // Setup the framebuffer using the following code taken from the the lecture notes and code
    /*
        Frame buffer 0 is is our screen,
        Frame buffer 1 is where we render to do perform our post processing effects
    */
        glGenFramebuffers(1, &m_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        glGenTextures(1, &m_framebufferTexture);
        glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear sample when texture is minified
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear sample when texture is magnified
    }

    { // Depth buffer texture - Need to attach depth too otherwise depth testing will not be performed.
        glGenRenderbuffers(1, &m_depthbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_depthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbuffer);
    }

    { // Stored Quad verts + UVs for framebuffer
        glGenBuffers(1, &m_displayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_displayBuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     12 * sizeof(glm::vec2),
                     &m_displayCoords[0],
                     GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_displayVao);
        glBindVertexArray(m_displayVao);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), NULL);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), (GLvoid *) (sizeof(glm::vec2)));
        glEnableVertexAttribArray(1);
    }

    ShaderManager* shaderManager = ShaderManager::GetInstance();
    m_framebufferProgram = shaderManager->RequestProgram("Shaders/vs_display.glsl","Shaders/fs_display.glsl");

    ProfilerService::GetInstance()->StopTimer(profiler);
}


void Renderer::Render(){
    int profiler = ProfilerService::GetInstance()->StartTimer("Render");

    // Render to the framebuffer texture instead of screen
    glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer); // Rendering to framebuffer 1
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_framebufferTexture,0);
    
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);
    // Convert all our projected coordinates to screen coordinates for the texture
    
    glViewport(0,0, frameWidth, frameHeight);
    
    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, frameWidth, frameHeight);
    
    glClearBufferfv(GL_COLOR, 0, &m_clearColour[0]);
    static const GLfloat one = 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 viewMatrix = p_camera->BuildViewMat();

    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    vector<GameObject*> Objs = p_scene->GetObjs();
    LightStruct* p_lights = p_scene->GetLights();
    LightStruct lights[LIGHTSN];

    for(int n = 0; n < LIGHTSN; n++){
        lights[n] = *(p_lights + n);
    }

    for(int i = 0; i < Objs.size(); ++i)
    {
        GLuint index = glGetUniformBlockIndex(Objs[i]->m_program,"lightBlock");
        glUniformBlockBinding(Objs[i]->m_program, index, 0);
    }
    
    lights[2].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[2].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    lights[3].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[3].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, lightStructByteSize * LIGHTSN, NULL, GL_STATIC_DRAW); // allocate 96 bytes of memory
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, lightStructByteSize * LIGHTSN);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, lightStructByteSize * LIGHTSN, lights);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glm::vec3 camPos = p_camera->GetPosition();
    glm::mat4 projMatrix = p_camera->GetCachedProjMat();

    for(int n = 0;n<Objs.size();n++){
        Objs[n]->Render(projMatrix,viewMatrix,lights,camPos);
    }
    
    // SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
    glScissor(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); //not needed as we are just displaying a single quad
    glUseProgram(m_framebufferProgram);
    glBindVertexArray(m_displayVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    ProfilerService::GetInstance()->StopTimer(profiler);
}

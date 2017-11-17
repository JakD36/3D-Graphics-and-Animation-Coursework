//
//  init.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"


void GLapp::setupRender() {
    glfwSwapInterval(1);    // Ony render when synced (V SYNC)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);
}

void GLapp::hintsGLFW() {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);            // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


glm::vec3 lightStruct::ia = glm::vec3(0.0f,1.0f,0.2f);

void GLapp::startup() {
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight; // ARE THESE BEING CONVERTED TO FLOATS?
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);

    // Initialise Objects
    // Instantiate Object
    // initModel
    // initTexture
    // loadMat
    // sort any other variables that need set
    
    // Torch
    torchObj = modelObjectSingle();
    torchObj.initModel("newTorch.obj","vs.glsl","fs.glsl");
    torchObj.initTexture("newTorchCol.ktx");
    torchObj.loadMat("newTorch.mtl");
    torchObj.position = cameraPos + posOnSphere(sphereRadius,yawOffset,-pitchOffset);
    
    // Room
    
    // Front of room
    front = modelObjectSingle();
    front.initModel("front.obj","vs.glsl","fs.glsl");
    front.initTexture("front.ktx");
    front.loadMat("front.mtl");
    
    
    // Back wall
    back = modelObjectSingle();
    back.initModel("back.obj", "vs.glsl", "fs.glsl");
    back.initTexture("back.ktx");
    back.loadMat("back.mtl");
    back.rotation.y = 180.0f;
    back.position = glm::vec3(0.0f,2.0f,3.0f);
    
    // Roof
    roof = modelObjectSingle();
    roof.initModel("roof.obj", "vs.glsl", "fs.glsl");
    roof.initTexture("roof.ktx");
    roof.loadMat("roof.mtl");
    roof.position.y = 2.5f;
    
    beam = modelObjectInst();
    beam.initModel("beam.obj", "vs.glsl", "fs.glsl");
    beam.initTexture("beam.ktx");
    beam.loadMat("beam.mtl");
    
    beam.position.push_back(glm::vec3(0.0f,2.61f,0.0f));
    beam.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    beam.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    beam.position.push_back(glm::vec3(0.0f,2.61f,-1.5f));
    beam.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    beam.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    beam.position.push_back(glm::vec3(0.0f,2.61f,1.5f));
    beam.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    beam.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank
    planks = modelObjectInst();
    planks.initModel("plank.obj", "vs.glsl", "fs.glsl");
    planks.initTexture("plank.ktx");
    planks.loadMat("plank.mtl");
    
    // Plank 1
    planks.position.push_back(glm::vec3(2.2f,1.5f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,5.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 2
    planks.position.push_back(glm::vec3(2.0f,1.3f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,10.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 3
    planks.position.push_back(glm::vec3(1.65f,1.6f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,2.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 4
    planks.position.push_back(glm::vec3(1.4f,1.5f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,-5.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 5
    planks.position.push_back(glm::vec3(1.1f,1.3f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,1.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 6
    planks.position.push_back(glm::vec3(0.8f,1.55f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,-12.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 7
    planks.position.push_back(glm::vec3(0.5f,1.55f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,-1.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 8
    planks.position.push_back(glm::vec3(0.1f,1.55f,-3.0f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,6.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 9
    planks.position.push_back(glm::vec3(0.6f,1.7f,-2.85f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,80.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 10
    planks.position.push_back(glm::vec3(1.0f,1.15f,-2.85f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,110.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 11
    planks.position.push_back(glm::vec3(1.8f,1.65f,-2.85f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,60.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 12
    planks.position.push_back(glm::vec3(-1.4f,1.85f,-3.2f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,85.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 13
    planks.position.push_back(glm::vec3(-1.4f,1.55f,-3.2f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,95.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 14
    planks.position.push_back(glm::vec3(-1.4f,1.2f,-3.2f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,90.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 15
    planks.position.push_back(glm::vec3(-1.4f,0.85f,-3.2f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,80.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 16
    planks.position.push_back(glm::vec3(-1.4f,0.5f,-3.2f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,100.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 17
    planks.position.push_back(glm::vec3(-1.4f,0.2f,-3.2f));
    planks.rotation.push_back(glm::vec3(90.0f,0.0f,95.0f));
    planks.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Floor
    floor = modelObjectSingle();
    floor.initModel("floor.obj", "vs.glsl", "fs.glsl");
    floor.initTexture("floor.ktx");
    floor.loadMat("floor.mtl");
    
    // Wall
    wall = modelObjectInst();
    wall.initModel("wall.obj", "vs.glsl", "fs.glsl");
    wall.initTexture("wall.ktx");
    wall.loadMat("wall.mtl");
    
    // Wall 1
    wall.position.push_back(glm::vec3(3.0f,1.25f,0.0f));
    wall.rotation.push_back(glm::vec3(0.0f,180.0f,0.0f));
    wall.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Wall 2
    wall.position.push_back(glm::vec3(-3.0f,1.25f,0.0f));
    wall.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    wall.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    //Lightbulb
    bulb = modelObjectSingle();
    bulb.initModel("bulb.obj", "vs_light.glsl", "fs_light.glsl");
    bulb.initTexture("bulb.ktx");
    bulb.loadMat("bulb.mtl");
    
    
    //Add objects to vector Objs to be rendered!
    
    Objs.push_back(&torchObj);
    Objs.push_back(&front);
    Objs.push_back(&wall);
    Objs.push_back(&roof);
    Objs.push_back(&floor);
    Objs.push_back(&back);
    Objs.push_back(&planks);
    Objs.push_back(&beam);
    Objs.push_back(&bulb);
    
    
    // Add lights to scene, number of lights determined by const int LIGHTSN
    lights[0].type = lightType::point;
    lights[0].position = glm::vec3(0.0f,2.25f,0.0f) + posOnSphere(lightRadius, lightYaw, lightPitch);
    lights[0].position = glm::vec3(0.0f,2.0f,0.0f);
    lights[0].id = glm::vec3(5.0f,5.0f,5.0f);
    lights[0].is = glm::vec3(1.0f,1.0f,1.0f);
    
    lights[1].type = lightType::point;
    lights[1].position = glm::vec3(2.0f,0.5f,2.0f);
    lights[1].id = glm::vec3(0.5f,0.0f,0.0f);
    lights[1].is = glm::vec3(0.5f,0.0f,0.0f);
    
    lights[2].type = lightType::spot;
    lights[2].position = glm::vec3(0.0f,1.0f,0.0f);
    lights[2].direction = cameraFront;
    lights[2].id = glm::vec3(10.0f,10.0f,10.0f);
    lights[2].is = glm::vec3(1.0f,1.0f,1.0f);
    
    
    
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glGenTextures(1,&framebufferTexture);
    
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,windowWidth,windowHeight,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    
    // filtering needed - future lecture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Depth buffer texture    - Need to attach depth too otherwise depth testing will not be performed.
    glGenRenderbuffers(1, &depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
    
    displayVertices.push_back(glm::vec2(-1.0f, 1.0f));
    displayVertices.push_back(glm::vec2(-1.0f,-1.0f));
    displayVertices.push_back(glm::vec2( 1.0f,-1.0f));
    displayVertices.push_back(glm::vec2(-1.0f, 1.0f));
    displayVertices.push_back(glm::vec2( 1.0f,-1.0f));
    displayVertices.push_back(glm::vec2( 1.0f, 1.0f));
    
    displayUvs.push_back(glm::vec2(0.0f, 1.0f));
    displayUvs.push_back(glm::vec2(0.0f, 0.0f));
    displayUvs.push_back(glm::vec2(1.0f, 0.0f));
    displayUvs.push_back(glm::vec2(0.0f, 1.0f));
    displayUvs.push_back(glm::vec2(1.0f, 0.0f));
    displayUvs.push_back(glm::vec2(1.0f, 1.0f));
    
    glGenBuffers(2,displayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 displayVertices.size()*sizeof(glm::vec2),
                 &displayVertices[0],
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 displayUvs.size()*sizeof(glm::vec2),
                 &displayUvs[0],
                 GL_STATIC_DRAW);

    
    glGenVertexArrays(1,&displayVao);
    glBindVertexArray(displayVao);
    glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    
    //load shaders
    displayProgram = glCreateProgram();
    
    string dvs_text = readShader("vs_display.glsl");
    const char* dvs_source = dvs_text.c_str();
    GLuint dvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(dvs, 1, &dvs_source, NULL);
    glCompileShader(dvs);
    checkErrorShader(dvs);
    glAttachShader(displayProgram, dvs);
    
    string dfs_text = readShader("fs_display.glsl");
    const char* dfs_source = dfs_text.c_str();
    GLuint dfs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dfs, 1, &dfs_source, NULL);
    glCompileShader(dfs);
    checkErrorShader(dfs);
    glAttachShader(displayProgram, dfs);
    
    glLinkProgram(displayProgram);
    glUseProgram(displayProgram);

    
}

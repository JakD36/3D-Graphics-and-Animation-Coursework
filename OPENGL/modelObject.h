//
//  modelObject.h
//  OPENGLClassTest
//
//  Created by Jack Davidson on 09/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#ifndef modelObject_h
#define modelObject_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <gli/gli.hpp>
#include <GLM/gtx/transform.hpp>
#include "OBJParser.h"

struct lightStruct{
public:
    static glm::vec3 ia;
    static GLfloat ka;
    glm::vec3 id;
    GLfloat kd;
    glm::vec3 is;
    GLfloat ks;
    GLfloat shininess;
};


class modelObject{
protected:
    std::vector < glm::vec3 > out_vertices;
    std::vector < glm::vec2 > out_uvs;
    std::vector < glm::vec3 > out_normals;
    GLuint          texture[1];            // texture name
    GLuint          program;
    GLuint          vao;
    GLuint          buffer[3];
    GLint           mv_location;
    GLint           proj_location;
    GLint           tex_location;
    
    // extra variables for this example
    GLuint        matColor_location;
    GLuint        lightColor_location;
    
public:
    modelObject();
    void initModel(string,string,string); // initialise the modelObject with model and its shaders
    void initTexture(string); // provide texture for model
    void getUniLocation(); // get the uniform locations for model
    bool load(string); // load and parse .obj file
    void checkErrorShader(GLuint shader);
    string readShader(string fileName);
    virtual void render(glm::mat4&,glm::mat4&, lightStruct&, glm::vec3&) const =0;
};

#endif /* modelObject_h */

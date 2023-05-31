#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "vertex_data.h"
#include "Shader.h"
#include "texture2d.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location;

//初始化OpenGL
void init_opengl()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }
    glfwSwapInterval(1);
}

//编译、链接Shader
void compile_shader()
{
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);

    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);

    glCompileShader(fragment_shader);

    program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
  
    glLinkProgram(program);
}

void CreateTexture(std::string image_file_path)
{
    Texture2D* texture2d=Texture2D::LoadFromFile(image_file_path);
}

int main(void)
{
    init_opengl();

    CreateTexture("Assets/container.jpg");

    compile_shader();

    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4 model,view, projection, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f/255,77.f/255,121.f/255,1.f);

        glm::mat4 trans = glm::translate(glm::vec3(0,0,0));

        static float rotate_eulerAngle=0.f;
        rotate_eulerAngle+=1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); 

        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); 
        model = trans*scale*rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));

        projection=glm::perspective(glm::radians(60.f),ratio,1.f,1000.f);

        mvp=projection*view*model;

        glUseProgram(program);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);

            glEnableVertexAttribArray(vpos_location);
       
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions);
            glEnableVertexAttribArray(vcol_location);
           
            glVertexAttribPointer(vcol_location, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors);
            
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            //void glDrawArrays(GLenum mode,GLint first,GLsizei count);
            glDrawArrays(GL_TRIANGLES, 0, 6*6);
        }
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
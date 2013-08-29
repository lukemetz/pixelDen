#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "Program.h"
#include "Uniforms.h"
#include "Geometry.h"
#include "Model.h"
#include "Camera.h"
#include "CameraControls.h"

static std::string vertexShaderSource = "\
#version 120\n\
in vec3 iPosition;\
uniform mat4 uModelView;\
void main() \
{ \
  gl_Position = uModelView * vec4(iPosition, 1); \
}";

static std::string fragmentShaderSource = "\
#version 150\n\
out vec4 oColor;\n\
void main(void)\n\
{\n\
  oColor = vec4(1.0,1.0,0,1.0);\n\
}";

void key(GLFWwindow *w, int i, int b, int c, int z) {
  std::cout << "OtheroneWorking!!! \n \n" << std::endl;
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if(!glfwInit())
      return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(2*640, 2*480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    /* Initialize extension loader once context up*/
    if(GLEW_OK != glewInit())
      return -1;

    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    //Setup inputs
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    Shader::Ptr vertexShader = createShaderFromSource(Shader::Type::Vertex, vertexShaderSource);
    Shader::Ptr fragmentShader = createShaderFromSource(Shader::Type::Fragment, fragmentShaderSource);

    std::vector<Shader::Ptr> shaders{vertexShader, fragmentShader};
    Program::Ptr program = createProgramWithShaders(shaders);

    Geometry::Ptr geometry = std::make_shared<Geometry>();

    geometry->positions = {
        1.0f, 1.0f, 0.f,
        -1.f, -1.f, 0.f,
        1.f, -0.8f, 0.f
    };

    geometry->indices = {
      0, 1, 2,
    };

    Model::Ptr model = createModel(geometry);
    Camera::Ptr camera = createCamera();
    camera->projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    camera->view = glm::lookAt(
        glm::vec3(0,0,-4), //Position
        glm::vec3(0,0,0), //Look at
        glm::vec3(0,1,0) //up
    );

    geometry->bindGlBuffers();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);

      float right = glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE ? 0 : 1;
      right += glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE ? 0 :-1;

      float in = glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE ? 0 : 1;
      in += glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE ? 0 :-1;

      float scale = 0.1;
      //CameraControls::panHorizontal(camera, right, scale);
      CameraControls::panInto(camera, in * scale);
      CameraControls::panHorizontal(camera, -right * scale);

      double newCursorX, newCursorY;
      float rotateScale = .4f;
      glfwGetCursorPos(window, &newCursorX, &newCursorY);
      glfwSetCursorPos(window, width/2, height/2);
      CameraControls::rotateHorizontal(camera, (newCursorX - width/2) * rotateScale);
      CameraControls::rotateVertical(camera, (newCursorY - height/2) * rotateScale);

      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear depthbit here if depth on

      renderModelFromCamera(camera, model, program);

      /* Swap front and back buffers */
      glfwSwapBuffers(window);
      /* Poll for and process events */
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

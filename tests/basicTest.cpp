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
#include "Texture.h"
#include "TextureCube.h"

#include "DebugOpengl.h"


static std::string vertexShaderSource = "\
#version 150\n\
in vec3 iPosition;\
in vec3 iNormal;\
out vec3 normal;\
out vec3 position;\
uniform mat4 uModelView;\
void main() \
{ \
  gl_Position = uModelView * vec4(iPosition, 1); \
  normal = iNormal;\n\
  position = iPosition;\n\
}";

static std::string fragmentShaderSource = "\
#version 150\n\
struct Light \
{ \
  vec3 color; \
  vec3 position;\
  float intensity; \
}; \
uniform Light light;\
uniform sampler2D sampler;\
uniform samplerCube cube;\
in vec3 normal;\n\
in vec3 position; \n\
out vec4 oColor;\n\
void main(void)\n\
{\n\
  vec3 lightDir = light.position - position;\n\
  lightDir = normalize(lightDir);\n\
  float NdotL = max( dot(normal, lightDir), 0.0f );\n\
  oColor = vec4(vec3(0.3f, 0.3f, 0.3f) * light.color * NdotL, 1);\n\
  vec4 res = texture2D(sampler, position.xz/10);\n\
  oColor = vec4(res.xyz, 1);\n\
  oColor = texture(cube, normal);\n\
}";

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
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

    if (glewIsSupported("GL_ARB_debug_output")) {
        glDebugMessageCallbackARB(DebugCallbackARB, stderr); // print debug output to stderr
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    } else {
      std::cerr << "Error detection not supported" << std::endl;
      assert(0);
    }

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

    Geometry::Ptr geometry = createGeometryFromFile("./assets/perlin.geo");

    Model::Ptr model = createModel(geometry);
    Camera::Ptr camera = createCamera();
    camera->projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 500.0f);
    camera->view = glm::lookAt(
        glm::vec3(0,100,-100), //Position
        glm::vec3(0,0,0), //Look at
        glm::vec3(0,1,0) //up
    );

    geometry->bindGlBuffers();

    Light::Ptr light = createLight(glm::vec3(0,10,0), glm::vec3(1, .5, .4), 1.0f);

    Texture::Ptr texture = createTextureFromFile("./tests/assets/texture.jpg");

    setUniformTexture(program, "sampler", texture, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetCursorPos(window, width/2, height/2);
    glfwSwapBuffers(window);
    glfwPollEvents();

    TextureCube::Ptr cube = createTextureCubeWithPrefix("./tests/assets/cube", "png");
    setUniformTexture(program, "cube", texture, 0);

    while (!glfwWindowShouldClose(window))
    {
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);

      float right = glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE ? 0 : 1;
      right += glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE ? 0 :-1;

      float in = glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE ? 0 : 1;
      in += glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE ? 0 :-1;

      float scale = 3;
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

      light->position.x += .1f;
      setLightUniform(program, light);
      /* Swap front and back buffers */
      glfwSwapBuffers(window);
      /* Poll for and process events */
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

#include <bandit/bandit.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace bandit;

int main(int argc, char* argv[])
{
  if(!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow * window = glfwCreateWindow(640, 480, "Spec Testing", NULL, NULL);
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

  return bandit::run(argc, argv);
}


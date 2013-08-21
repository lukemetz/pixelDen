#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//NIGHTMARE do not add comments CHANGE ME asap
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


GLuint makeShader(GLenum type, const std::string& source)
{
  GLuint shader = glCreateShader(type);
  GLchar* rawSource = (GLchar*) source.c_str();
  GLsizei size = source.size();
  glShaderSource(shader, 1, (const GLchar**)&rawSource, &size);
  glCompileShader(shader);

  GLint shaderOk;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOk);
  if (!shaderOk) {
    std::cerr << "Failed compile shader" << std::endl;
    GLint logSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    char *logMsg = new char[logSize];
    glGetShaderInfoLog(shader, logSize, NULL, logMsg);
    std::cerr << logMsg << std::endl;
    delete[] logMsg;
    return shader;
  }
  return shader;
}

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    GLuint vShader = makeShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fShader = makeShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);


    glLinkProgram(program);
    
    GLint shaderOk;
    glGetProgramiv(program, GL_LINK_STATUS, &shaderOk);
    if (!shaderOk) {
      std::cerr << "Failed linking shader" << std::endl;
      GLint logSize;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
      char *logMsg = new char[logSize];
      glGetProgramInfoLog(program, logSize, NULL, logMsg);
      std::cerr << logMsg << std::endl;
      delete[] logMsg;
      return 0;
    }
    
    GLuint shaders[4];
    int count = 0;
    glGetAttachedShaders(program, 4, &count, shaders);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
      std::cerr << "Shader program failed to link" << std::endl;
      GLint logSize;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
      char* logMsg = new char[logSize];
      glGetProgramInfoLog(program, logSize, NULL, logMsg);
      std::cerr << logMsg << std::endl;
      delete[] logMsg;
    }

    /*glValidateProgram(program);
    GLint validated;
    if (!validated)
    {
      std::cerr << "Shader program failed to validate:" << validated << std::endl;
      GLint logSize;
      glGetProgramiv(program, GL_VALIDATE_STATUS, &logSize);
      std::cout << logSize << std::endl;
      char* logMsg = new char[logSize];
      glGetProgramInfoLog(program, logSize, NULL, logMsg);
      std::cerr << logMsg << std::endl;
      delete[] logMsg;
    }*/

    



    GLfloat vertices[] = {
        1.0f, 1.0f, 0.f,
        -1.f, -1.f, 0.f,
        1.f, -0.8f, 0.f
    };

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear depthbit here if depth on

        glUseProgram(program);
        GLuint iPosition = glGetAttribLocation(program, "iPosition");
        glEnableVertexAttribArray(iPosition);
        glVertexAttribPointer(iPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);



        GLuint uModelView = glGetUniformLocation(program, "uModelView");

        glm::mat4 projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(
            glm::vec3(0,4,-4), //Position
            glm::vec3(0,0,0), //Look at
            glm::vec3(0,1,0) //up
        );
        glm::mat4 model(1.0f);

        glm::mat4 modelView = projection * view * model;

        glUniformMatrix4fv(uModelView, 1, GL_FALSE, glm::value_ptr(modelView));
        

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(iPosition);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
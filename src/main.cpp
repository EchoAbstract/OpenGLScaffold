#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void ErrorCallback(int error, const char *description){
  std::cerr << description << std::endl;
  glfwTerminate();
  exit( -1 );
}

static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods){
  std::cout << "I'm here!\n";
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose( window, GL_TRUE );
}

int main(int argc, char **argv){

  int errorCode = EXIT_FAILURE;
  
  if (!glfwInit())
    exit( errorCode );

  glfwSetErrorCallback( ErrorCallback );

  GLFWwindow *window = glfwCreateWindow( 640, 480, "Sample OpenGL", NULL, NULL );
  if (!window) goto EXIT;


  glfwMakeContextCurrent( window );

  glfwSetKeyCallback( window, KeyCallback );


  // Rendering
  int width, height;
  glfwGetFramebufferSize( window, &width, &height );
  glViewport( 0, 0, width, height );
  glfwSwapInterval( 1 );


  // Main loop (for now)
  while (!glfwWindowShouldClose( window )){
    double t = glfwGetTime();

    glfwSwapBuffers( window );
    glfwPollEvents();

  }


  errorCode = EXIT_SUCCESS;

 EXIT:
  glfwTerminate();
  exit( errorCode );
}

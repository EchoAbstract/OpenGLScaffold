#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

void ErrorCallback(int error, const char *description){
  std::cerr << description << std::endl;
}

static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose( window, GL_TRUE );
}

int main(int argc, char **argv){

  GLFWwindow *window;
  
  // Set up error handling
  glfwSetErrorCallback( ErrorCallback );

  // Initialize GLFW
  if (!glfwInit())
    exit( EXIT_FAILURE );


  // Create our rendering window
  window = glfwCreateWindow( 640, 480, "Sample OpenGL", NULL, NULL );
  if (!window) {
    glfwTerminate();
    exit( EXIT_FAILURE );
  }


  glfwMakeContextCurrent( window ); // Set OpenGL rendering context
  glfwSwapInterval( 1 );            // Set swap interval to 1 to avoid tearing

  // Handle keypresses
  glfwSetKeyCallback( window, KeyCallback );


  // Main loop
  while (!glfwWindowShouldClose( window )){
    float ratio;
    int width, height;

    glfwGetFramebufferSize( window, &width, &height );
    ratio = width / (float) height;

    // Set the displayed viewport and clear the background
    glViewport( 0, 0, width, height );
    glClear( GL_COLOR_BUFFER_BIT );


    // Render time!

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( -ratio, ratio, -1.f, 1.f, 1.f, -1.f );
    glMatrixMode( GL_MODELVIEW );
    
    glLoadIdentity();
    glRotatef( (float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f );
    
    glBegin( GL_TRIANGLES );

    glColor3f( 1.f, 0.f, 0.f );
    glVertex3f( -0.6f, -0.4f, 0.f );
    
    glColor3f( 0.f, 1.f, 0.f );
    glVertex3f( 0.6, -0.4f, 0.f );

    glColor3f( 0.f, 0.f, 1.f );
    glVertex3f( 0.f, 0.6f, 0.f );

    glEnd();

    glfwSwapBuffers( window );  // Display our new scene
    glfwPollEvents();           // Handle event processing
  }


  // Clean up
  glfwDestroyWindow( window );
  glfwTerminate();
  exit( EXIT_SUCCESS );
}

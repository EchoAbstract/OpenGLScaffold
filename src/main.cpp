#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>


bool cursorDisabled = false;

void ErrorCallback(int error, const char *description){
  std::cerr << description << std::endl;
}

static void CursorPosCallback( GLFWwindow *window, double xpos, double ypos ){}

static void ScrollCallback( GLFWwindow *window, double xoffset, double yoffset ){}

static void MouseButtonCallback( GLFWwindow *window, int button, int action, int mods){
  if (action == GLFW_PRESS && cursorDisabled == false){
      glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
      cursorDisabled = true;
  }
}

static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods){
  if (action == GLFW_PRESS || action == GLFW_REPEAT){
    switch (key) {
    case GLFW_KEY_ESCAPE:
      glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
      cursorDisabled = false;
      break;
    case GLFW_KEY_Q:
      glfwSetWindowShouldClose( window, GL_TRUE );
      break;
    default:
      std::cout << "Unhandled key!" << std::endl;
      break;
    }
  }
}

int main(int argc, char **argv){

  GLFWwindow *window;
  
  glfwSetErrorCallback( ErrorCallback ); // Error callback


  // Initialize GLFW
  if (!glfwInit())
    exit( EXIT_FAILURE );


  // Change this to #if 1 in order to use modern OpenGL
#if 0
  // TODO(brian): update the rest of the code for modern times
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
#endif  
  
  // Create our rendering window
  window = glfwCreateWindow( 640, 480, "Sample OpenGL", NULL, NULL );
  if (!window) {
    glfwTerminate();
    exit( EXIT_FAILURE );
  }

  // Finish setting up GLFW
  glfwMakeContextCurrent( window ); // Set OpenGL rendering context
  glfwSwapInterval( 1 );            // Set swap interval to 1 to avoid tearing

  // Input callbacks
  glfwSetKeyCallback( window, KeyCallback );                 // Keypress
  glfwSetCursorPosCallback( window, CursorPosCallback );     // Mouse cursor
  glfwSetScrollCallback( window, ScrollCallback );           // Mouse scrollwheel
  glfwSetMouseButtonCallback( window, MouseButtonCallback ); // Mouse press


  // Set up GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte *renderer = glGetString( GL_RENDERER );
  const GLubyte *version  = glGetString( GL_VERSION );

  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version: " << version << std::endl;

  // For perf counting
  double lastTime = glfwGetTime();
  int numFrames = 0;

  std::string rootTitle = "OpenGL Window -- ";
  std::string title;

  // Main loop
  while (!glfwWindowShouldClose( window )){
    double currentTime = glfwGetTime();
    numFrames++;
    if ( currentTime - lastTime >= 1.0){
      std::cout << 1000.0 / double( numFrames ) << " ms/frame" << std::endl;
      title = rootTitle + std::to_string(numFrames) + " fps";
      numFrames = 0;
      lastTime += 1.0;
      glfwSetWindowTitle( window, title.c_str() );
    }

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
    glRotatef( (float)currentTime * 50.f, 0.f, 0.f, 1.f );
    
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

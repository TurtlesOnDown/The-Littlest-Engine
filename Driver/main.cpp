#include "Includes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MessageBus.h"
#include "Console.h"
#include "Misc.h"

#include <stack>
#include "Profiler.h"
#include "ResourceManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
MessageBus testBus;
Console testConsole(&testBus);
ResourceManager testResourceManager(&testBus, true);

Stopwatch teststopwatch;

Message testMessage{ "PHYSICS", "BALL DROPPED" };

struct TESTSTRUCT {
  //int a;
  //uint8 b{ 0 };
  //uint16 B{ 3 };
  uint64 c;
  uint32 b;
  uint64 a;
  
  //MessageBus d;
  //MessageBus a;
  //MessageBus b;
  //MessageBus e;
};

int main()
{
  //Path a("C:/engine/test.txt", '/');
  //testConsole.printToConsole(" ", a.getFile(), a.getFileType(), a.getPath());
  std::shared_ptr<Resource> a = testResourceManager.load(Path("C:/engine/test.txt", '/'));
  testConsole.printToConsole(" ", a, a.use_count());
  testConsole.printToConsole(" ", Path("test.txt", '/').getPath());
  //a = nullptr;
  //testResourceManager.clearUnusedResources();
  testBus.notfitySystems();

  teststopwatch.start();
  testBus.addMessage(testMessage);
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

                                                       // glfw window creation
                                                       // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  teststopwatch.stop();
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    teststopwatch.start();
    // input
    // -----
    processInput(window);
    
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
    teststopwatch.stop();
    //testConsole.printToConsole("", teststopwatch.getMiliseconds());
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  std::string test;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //std::cin.get();
    //glfwSetWindowShouldClose(window, true);
    testConsole.getInput();
  //testConsole.printToConsole(" ", "This", "Should", "work");
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
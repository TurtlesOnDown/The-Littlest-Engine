#include "Engine/Common/Includes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/System/MessageBus.h"
#include "Engine/Console.h"
#include "Engine/Utility/Misc.h"

#include "Engine/Debug/Profiler.h"
#include "Engine/ResourceManager/ResourceManager.h"

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
  std::shared_ptr<Texture2D> texture = std::dynamic_pointer_cast<Texture2D>(testResourceManager.load("box", Path(Path::CWD() + "\\container.jpg", '/'), false));
  std::shared_ptr<Texture2D> texture2 = std::dynamic_pointer_cast<Texture2D>(testResourceManager.load("face", Path(Path::CWD() + "\\awesomeface.png", '/'), false));
  std::shared_ptr<Shader> shader = std::dynamic_pointer_cast<Shader>(testResourceManager.load("testShader", Path(Path::CWD() + "\\test.lshader", '/'), false));
  std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(testResourceManager.load("testModel", Path(Path::CWD() + "\\nanosuit\\nanosuit.obj", '/'), false));
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

  texture->init();
  texture2->init();
  shader->init();
  model->init();

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };
  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  shader->use();
  shader->setInt("texture1", 0);
  shader->setInt("texture2", 1);

  
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

    // bind textures on corresponding texture units
    texture->activateTexure(0);
    texture->bind();
    texture->activateTexure(1);
    texture2->bind();

    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
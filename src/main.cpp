#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include "helpers/shader.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "../stb/stb_image.h"
#include "helpers/camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 1.5f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 7.0f);

int main()
{
  // inicializando glfw configs
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  
  // configurando window glfw 
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cubes visualizer", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  // carregando e construindo shaders
  Shader ourShader("src/cube/cube.vert", "src/cube/cube.frag");
  Shader lightCubeShader("src/light/light.vert", "src/light/light.frag");
  Shader floorShader("src/floor/floor.vert", "src/floor/floor.frag");

  // construindo vertices do cubo (3 posicoes) + textura (2 posicoes) + normal (3 posicoes)
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

  // posicionando os cubos no mundo
  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3(2.0f, 5.0f, 15.0f),
      glm::vec3(-1.5f, -2.2f, 2.5f),
      glm::vec3(-3.8f, -2.0f, 12.3f),
      glm::vec3(2.4f, -0.4f, 3.5f),
      glm::vec3(-1.7f, 3.0f, 7.5f),
      glm::vec3(1.3f, -2.0f, 2.5f),
      glm::vec3(1.5f, 2.0f, 2.5f),
      glm::vec3(1.5f, 0.2f, 1.5f),
      glm::vec3(-1.3f, 1.0f, 1.5f)};
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // informando as posicoes de vertice, textura e normal 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // cubo de luz
  float lightCubeVertices[] = {
      -0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,

      -0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,

      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,

      0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,

      -0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.5f,
      -0.5f,
      -0.5f,

      -0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      0.5f,
      -0.5f,
      0.5f,
      -0.5f,
  };
  unsigned int otherVBO, cubeVAO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &otherVBO);

  glBindBuffer(GL_ARRAY_BUFFER, otherVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(lightCubeVertices), lightCubeVertices, GL_STATIC_DRAW);

  glBindVertexArray(cubeVAO);
  // informando dados do cubo de luz
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, cubeVAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // fazendo a mesma coisa aqui para o plano representando o chao
  float floorVertices[] = {
      -40.0f, -4.0f, -40.0f,
      40.0f, -4.0f, -40.0f,
      40.0f, -4.0f, 40.0f,

      40.0f, -4.0f, 40.0f,
      -40.0f, -4.0f, 40.0f,
      -40.0f, -4.0f, -40.0f};

  unsigned int floorVBO, floorVAO;
  glGenVertexArrays(1, &floorVAO);
  glGenBuffers(1, &floorVBO);

  glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

  glBindVertexArray(floorVAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // carregando e configurando textura
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // configurando wrapping e filtros
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // carregando imagem e configurando mimap
  int width, height, nrChannels;
  unsigned char *data = stbi_load("src/assets/wall.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // MAIN LOOP
  while (!glfwWindowShouldClose(window))
  {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind de texturas
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // ativa shaders
    ourShader.use();

    // seta algumas propriedades
    ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    ourShader.setVec3("lightPos", lightPos);
    ourShader.setVec3("viewPos", camera.Position);

    // seta matriz de projecao para o shader
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    // seta a camera
    glm::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("view", view);

    // renderiza os cubos
    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++)
    {
      // calcula o model para cada objeto e passa para o shader
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);

      // adiciona rotacao para cada cubo
      float angle = 20.0f * i + currentFrame * 50.f;
      float r = rand() / double(RAND_MAX);
      model = glm::rotate(model, glm::radians(angle), glm::vec3(r));
      ourShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(cubeVAO);

    // desenha o cubo de luz fixo
    lightCubeShader.use();
    lightCubeShader.setMat4("projection", projection);
    lightCubeShader.setMat4("view", view);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.5f)); // a smaller cube
    lightCubeShader.setMat4("model", lightModel);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    // desenha o chao
    glBindVertexArray(floorVAO);
    floorShader.use();
    floorShader.setMat4("projection", projection);
    floorShader.setMat4("view", view);
    floorShader.setMat4("model", glm::mat4(1.0f));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    // lida com eventos de IO (teclado/mouse/etc)
    glfwPollEvents();
  }

  // de-aloca recursos; opcional
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  // termina o programa, limpando recursos previamente alocados pelo GLFW
  glfwTerminate();
  return 0;
}

// funcao que processa input do teclado
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

// atualiza window caso seja sofra resize
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// funcao que processa movimento do mouse
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// funcao que processa scroll do mouse
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
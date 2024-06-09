EP de Síntese - Computação Gráfica

Integrantes:
  - Caio Hayashi NUSP 12542162
  - Guilherme Teodoro NUSP 11953911
  - Juan Kineipe NUSP 11894610
  - Luiz Fernando dos Santos NUSP 11840300
  - Vinicius Roland Crisci NUSP 10773381

Descrição do que foi feito:
  - Display de vários cubos
  - Movimentação de camera com o mouse
  - Movimentação via WASD com teclado
  - Zoom com scroll
  - Rotação das entidades
  - Iluminação (ambiente, difusa, especular)
  - Textura

Descrição da estrutura de projeto:
  - Feito em C++ com GLFW
  - Arquivo principal: `main.cpp`
  - Pasta `helper` guarda funções e classes auxiliares para lidar com shader e camera
  - Fragment shaders e Vertex shaders estão dentro de suas respectivas entidades (`cube`/`floor`/`light`)
  - Pastas `glad`, `glm` e `stb` sao arquivos auxiliares para lidar com OpenGL e interfaces gráficas (vide tutorial de OpenGL)

Principais referências:
  - [Tutorial OpenGL em texto](https://learnopengl.com/Getting-started/OpenGL)
  - [Tutorial OpenGL em vídeo](https://www.youtube.com/watch?v=YaiSvKTOeRg&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-&index=6)
  - [Config de ambiente](https://crackthagamedev.com/posts/configurando-glfw-opengl-no-visual-studio)
  - [Iluminação](https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)

Para rodar em Windows: Provavelmente usando Visual Studio

Para rodar em MacOS/Linux: `g++ stb/stb_image.cpp glad/glad.c src/main.cpp -o src/main.o -lglfw.3 -L/opt/homebrew/lib -I/opt/homebrew/Cellar/glfw/3.3.8/include -Wno-deprecated-declarations -Wno-deprecated -framework OpenGL; ./src/main.o`

/opt/homebrew/lib -> pasta onde o linker do glfw esta localizado
/opt/homebrew/Cellar/glfw/3.3.8/include -> pasta de include para os headers do glfw
framework OpenGl -> setando framework OpenGL

Essas são as pastas para MacOS. Se você usa Linux, provavelmente tenha que atualizar o comando trocando as pastas.

[Demo](https://github.com/viniciusroland/pyramid-cg/assets/41706108/48e53088-4800-4760-b138-7fca5c7eb5ac)

Screenshots:
<img width="1134" alt="Screenshot 1" src="https://github.com/viniciusroland/pyramid-cg/assets/41706108/f1d85b8b-b2b2-4cfc-a4ca-9a3dad5d1c38">
<img width="1134" alt="Screenshot 2" src="https://github.com/viniciusroland/pyramid-cg/assets/41706108/5569688e-fee8-4562-a6cf-f4d3554c4a19">
<img width="1134" alt="Screenshot 3" src="https://github.com/viniciusroland/pyramid-cg/assets/41706108/ecd0e9dd-d01b-41df-9d81-623f2871880b">

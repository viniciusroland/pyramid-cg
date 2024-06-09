Para rodar em Windows: Provavelmente usando Visual Studio

Para rodar em MacOS/Linux: `g++ stb/stb_image.cpp glad/glad.c pyramid/main.cpp -o pyramid/main.o -lglfw.3 -L/opt/homebrew/lib -I/opt/homebrew/Cellar/glfw/3.3.8/include -Wno-deprecated-declarations -Wno-deprecated -framework OpenGL; ./pyramid/main.o`

/opt/homebrew/lib -> pasta onde o linker do glfw esta localizado
/opt/homebrew/Cellar/glfw/3.3.8/include -> pasta de include para os headers do glfw
framework OpenGl -> setando framework OpenGL

Essas são as pastas para MacOS. Se você usa Linux, provavelmente tenha que atualizar o comando trocando as pastas.

[Demo](https://github.com/viniciusroland/pyramid-cg/assets/41706108/48e53088-4800-4760-b138-7fca5c7eb5ac)

Screenshots:
<img width="1134" alt="Screenshot 1" src="https://github.com/viniciusroland/pyramid-cg/assets/41706108/f1d85b8b-b2b2-4cfc-a4ca-9a3dad5d1c38">
<img width="1134" alt="Screenshot 2" src="https://github.com/viniciusroland/pyramid-cg/assets/41706108/5569688e-fee8-4562-a6cf-f4d3554c4a19">
<img width="1134" alt="Screenshot 3" src="https://github.com/viniciusroland/pyramid-cg/assets/41706108/ecd0e9dd-d01b-41df-9d81-623f2871880b">

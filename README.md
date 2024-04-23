To run on Windows: Probably using Visual Studio

To run on MacOS: `g++ stb/stb_image.cpp glad/glad.c pyramid/main.cpp -o pyramid/main.o -lglfw.3 -L/opt/homebrew/lib -I/opt/homebrew/Cellar/glfw/3.3.8/include -Wno-deprecated-declarations -Wno-deprecated -framework OpenGL; ./pyramid/main.o`

/opt/homebrew/lib -> folder that glfw.3 linker is located
/opt/homebrew/Cellar/glfw/3.3.8/include -> include folder for the glfw headers
framework OpenGl -> option to target OpenGL framework


[Demo](https://github.com/viniciusroland/pyramid-cg/assets/41706108/48e53088-4800-4760-b138-7fca5c7eb5ac)


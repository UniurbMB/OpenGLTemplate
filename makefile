build:
	gcc -g -Wall -Wextra *.c -o bin/OpenGLTemplate.exe -Iinclude -Llib -lglfw3 -lopengl32

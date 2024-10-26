release:
	gcc -O *.c -o bin/gameEngine.exe -mwindows -Iinclude -Llib -lglfw3 -lopengl32 
debug:
	gcc -g -Wall -Wextra *.c -o bin/gameEngineDebug.exe -Iinclude -Llib -lglfw3 -lopengl32

/*OpenGL headers*/
#include "glad/glad.h"
#include "GLFW/glfw3.h"
/*standart C headers*/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*imported headers*/
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(){

	/*pre init calls*/
	stbi_set_flip_vertically_on_load(true);

	/*glfw init*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*window creation*/
	GLFWwindow* window = glfwCreateWindow(1000, 700, "Basic Game Engine", NULL, NULL);

	/*window debug*/
	if (window == NULL){
		FILE* output;
		output = fopen("errLog.txt", "a");
		fprintf(output, "Error! Failed to create window\n");
		fclose(output);
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/*loading glad*/
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		FILE* output;
		output = fopen("errLog.txt", "a");
		fprintf(output, "Error! Failed to initialize GLAD!\n");
		fclose(output);
		return -1;
	}

	/*setting the background color*/
	glClearColor(0.1f, 0.6f, 0.3f, 1.0f);

	const char* vertexSource = "#version 330 core\n"
			"layout (location = 0) in vec2 aPos;\n"
			"void main(){\n"
			"gl_Position = vec4(aPos, 0.0f, 1.0f);\n"
			"}\0";
	const char* fragmentSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main(){\n"
			"FragColor = vec4(0.3f, 0.3f, 0.9f, 1.0f);\n"
			"}\0";
	/*
	char* vertexSource;
	char* fragmentSource;
	FILE* f = fopen("vertShader.glsl", "rb");
	fseek(f, 0, SEEK_END);
	size_t s = ftell(f) + 1;
	fclose(f);
	vertexSource = calloc(s, sizeof(char));
	f = fopen("vertShader.glsl", "r");
	fread(vertexSource, s, 1, f);
	fclose(f);
	f = fopen("fragShader.glsl", "rb");
	fseek(f, 0, SEEK_END);
	s = ftell(f) + 1;
	fclose(f);
	fragmentSource = calloc(s, sizeof(char));
	f = fopen("fragShader.glsl", "r");
	fread(fragmentSource, s, 1, f);
	fclose(f);
	*/
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char* const*)&vertexSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Failed to compile vertex shader!\n%s\n", infoLog);
	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char* const*)&fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Failed to compile fragment shader!\n%s\n", infoLog);
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "Failed to link the shader program!\n%s\n", infoLog);
	}
	
	glUseProgram(shaderProgram);
	printf("%s\n%s\n", vertexSource, fragmentSource);
	//free(vertexSource);
	//free(fragmentSource);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f
	};
	
	unsigned short indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	/*enable depth testing*/ 
	//glEnable(GL_DEPTH_TEST);

	
	while(!glfwWindowShouldClose(window)){

		/*clear background*/
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		/*swap screen buffers*/
		glfwSwapBuffers(window);

		/*poll events*/
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}


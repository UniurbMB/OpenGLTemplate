/*OpenGL headers*/
#include "glad/glad.h"
#include "GLFW/glfw3.h"
/*standart C headers*/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(){

	/*glfw init*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*window creation*/
	GLFWwindow* window = glfwCreateWindow(1000, 700, "OpenGL Template!", NULL, NULL);

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

	/*SHADERS*/
	
	/*Vertex shader*/
	const char* vertexSource = "#version 330 core\n"
			"layout (location = 0) in vec2 aPos;\n"
			"void main(){\n"
			"gl_Position = vec4(aPos, 0.0f, 1.0f);\n"
			"}\0";

	/*Fragment shader*/
	const char* fragmentSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main(){\n"
			"FragColor = vec4(0.3f, 0.3f, 0.9f, 1.0f);\n"
			"}\0";

	/*Same thing as above, but the shaders are loaded from a file*/
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

	/*OpenGL shader loading and debugging*/

	unsigned int vertexShader, fragmentShader;

	/*Creating and compiling the vertex shader*/
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

	/*Creating and compiling the fragment shader*/
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char* const*)&fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Failed to compile fragment shader!\n%s\n", infoLog);
	}

	/*Creating and linking the shader program*/

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

	/*Uncomment these if you opted for the file approach*/
	//free(vertexSource);
	//free(fragmentSource);

	/*You can delete the shaders after they've been linked to the shader program*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*Vertex data of a rectangle to be passed to a Vertex Buffer Object (VBO)*/
	float vertices[] = {
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f
	};
	
	/*Index data of the rectangle to be passed to an Element Buffer Object (EBO)*/
	unsigned short indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	unsigned int VBO, VAO, EBO;
	/*Generate VBO*/
	glGenBuffers(1, &VBO);

	/*Generate Vertex Array Object (VAO)*/
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/*Assign the vertex data to a VBO*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*Describe the layout of the data with a VAO*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*Generate EBO*/
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	/*enable depth testing*/ 
	//glEnable(GL_DEPTH_TEST);

	
	while(!glfwWindowShouldClose(window)){

		/*clear background*/

		/*Comment the second glClear and uncomment the first one if you enabled depth testing*/
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		/*Bind the VAO and use the shaderProgram before drawing the rectangle*/
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		/*Draw the triangle*/
	
		/*The commented draw function is used when the EBO is not present*/
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		/*swap screen buffers*/
		glfwSwapBuffers(window);

		/*poll events*/
		glfwPollEvents();
	}

	/*Clean up*/
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}


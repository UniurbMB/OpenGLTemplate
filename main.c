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


	/*enable depth testing*/ 
	//glEnable(GL_DEPTH_TEST);

	
	while(!glfwWindowShouldClose(window)){

		/*clear background*/
		glClear(GL_COLOR_BUFFER_BIT);

		/*swap screen buffers*/
		glfwSwapBuffers(window);

		/*poll events*/
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


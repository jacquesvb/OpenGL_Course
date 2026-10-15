#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <openglErrorReporting.h>
#include <shader.h>

#include <iostream>

float triangleData[] = {
	// positions		colors
	//x  y  z			r  g  b
	  -1, -1, 0,		0.5, 0.8, 1, // bottom-left (light blue)
	  0, -1, 0,			0.5, 0.8, 1, // bottom-center (light blue)
	  -0.5, 0, 0,		0.5, 0.8, 1, // left-edge midpoint (light blue)

	  0, -1, 0,			0.5, 0.8, 1, // bottom-center (light blue)
	  0, 1, 0,			1, 0, 0, // top (red)
	  -0.5, 0, 0,		0.5, 0.8, 1, // left-edge midpoint (light blue)

	  0, -1, 0,			0.5, 0.8, 1, // bottom-center (light blue)
	  1, -1, 0,			0, 0, 0, // bottom-right (black)
	  0, 1, 0,			1, 0, 0  // top (red)
};

int main(void)
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init Error!\n";
		return 1;
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

	GLFWwindow *window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		std::cout << "Window Error!\n";
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 1;
	}

	enableReportGlErrors();

#pragma region buffer
	// create the buffer
	GLuint buffer = 0;
	glGenBuffers(1, &buffer);

	// send the data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	// the attribute representing position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	// the attribute representing color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));

#pragma endregion
#pragma region shader loading
	Shader shader;

	shader.loadShaderProgramFromFile(RESOURCES_PATH "myshader.vert", RESOURCES_PATH "myshader.frag");

	shader.bind();
#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		// tell OpenGL that we resized our  window
		int w = 0, h = 0;
		glfwGetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);
		
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 9);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
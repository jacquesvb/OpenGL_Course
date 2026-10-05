#include <openglErrorReporting.h>

#include <iostream>

void GLAPIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char *message,
	const void *userParam)
{
	(void)source;
	(void)id;
	(void)length;
	(void)userParam;

	const char *label = "Debug";
	if (type == GL_DEBUG_TYPE_ERROR)
		label = "Error";
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR || type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
		label = "Invalid";
	else if (type == GL_DEBUG_TYPE_PERFORMANCE)
		label = "Performance";
	else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		label = "Note";

	std::cout << "[OpenGL " << label << "] " << (message ? message : "") << "\n";
	std::cout.flush();
}

void enableReportGlErrors()
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
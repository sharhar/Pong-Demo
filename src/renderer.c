//
//  renderer.c
//  Pong
//
//  Created by Shahar Sandhaus on 10/28/19.
//

#include <stdio.h>
#include "renderer.h"

GLuint vao, vbo, vertShader, fragShader, shaderProgram, screenLoc, transLoc;

void initGL() {
	float vects[] = {
		0, 0,
		1, 0,
		1, 1,
		
		0, 0,
		1, 1,
		0, 1
	};
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vects, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
	const char* vertSource = "\
	#version 330 core\n\
	in vec2 position;\n\
	uniform vec4 screen;\n\
	uniform vec4 trans;\n\
	void main(void) {\n\
	vec2 translated_coords = vec2(trans.x + position.x*trans.z, trans.y + position.y*trans.w);\n\
	gl_Position = vec4(2*translated_coords.x/screen.x - 1, 2*translated_coords.y/screen.y - 1, 0, 1);\n\
	}\n";
	
	const char* fragSource = "\
	#version 330 core\n\
	out vec4 out_color;\n\
	void main(void) {\n\
	out_color = vec4(1, 1, 1, 1);\n\
	}\n";
	
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
	
	glShaderSource(vertShader, 1, &vertSource, 0);
	glShaderSource(fragShader, 1, &fragSource, 0);
	
	glCompileShader(vertShader);
	
	int compiled = 0;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int maxLength = 0;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);
		
		char* message = (char*)malloc(sizeof(char)*maxLength);
		glGetShaderInfoLog(vertShader, maxLength, &maxLength, message);
		
		printf("Vertex Shader failed to compile:\n");
		printf("%s\n", message);
		
		free(message);
		return;
	}
	
	glCompileShader(fragShader);
	
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int maxLength = 0;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);
		
		char* message = (char*)malloc(sizeof(char)*maxLength);
		glGetShaderInfoLog(fragShader, maxLength, &maxLength, message);
		
		printf("Fragment Shader failed to compile:\n");
		printf("%s\n", message);
		
		free(message);
		return;
	}
	
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	
	glBindAttribLocation(shaderProgram, 0, "position");
	
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	
	glUseProgram(shaderProgram);
	
	screenLoc = glGetUniformLocation(shaderProgram, "screen");
	transLoc = glGetUniformLocation(shaderProgram, "trans");
	
	glUniform4f(screenLoc, 800, 600, 0, 0);
	
	glUseProgram(0);
}

void initRender() {
	glBindVertexArray(vao);
	
	glEnableVertexAttribArray(0);
	
	glUseProgram(shaderProgram);
}

void renderRect(float x, float y, float w, float h) {
	glUniform4f(transLoc, x, y, w, h);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void endRender() {
	glUseProgram(0);
	
	glDisableVertexAttribArray(0);
	
	glBindVertexArray(0);
}


#include <stdio.h>
#include <swin/SWin.h>
#include <stext/SText.h>
#include <stext/SText_GL.h>
#include "renderer.h"

float key_w = 0;
float key_s = 0;

float key_up = 0;
float key_down = 0;

void keyDownCallback(SKeyCode keyCode) {
	if(keyCode == SWIN_KEY_W) {
		key_w = 1;
	} else if (keyCode == SWIN_KEY_S) {
		key_s = -1;
	} else if (keyCode == SWIN_KEY_UP) {
		key_up = 1;
	} else if (keyCode == SWIN_KEY_DOWN) {
		key_down = -1;
	}
}

void keyUpCallback(SKeyCode keyCode) {
	if(keyCode == SWIN_KEY_W) {
		key_w = 0;
	} else if (keyCode == SWIN_KEY_S) {
		key_s = 0;
	} else if (keyCode == SWIN_KEY_UP) {
		key_up = 0;
	} else if (keyCode == SWIN_KEY_DOWN) {
		key_down = 0;
	}
}

int main() {
	swInit();
	swInitGL();
	
	SWindow* window = swCreateWindow(800, 600, "Pong-Demo");
	
	SView* view = swGetRootView(window);
	
	swSetKeyDownCallback(view, keyDownCallback);
	swSetKeyUpCallback(view, keyUpCallback);
	
	SOpenGLContextAttribs attribs;
	attribs.debug = 0;
	attribs.forwardCompat = 0;
	attribs.major = 3;
	attribs.minor = 2;
	attribs.swapInterval = 1;
	attribs.profile = SWIN_OPENGL_CONTEXT_PROFILE_CORE;
	
	SOpenGLContext* context = swCreateOpenGLContext(view, &attribs);
	
	swMakeContextCurrent(context);
	
	gladLoadGLLoader(swGetProcAddressGL);
	
	stInitGL((stPfnGetProcAdressGL)swGetProcAddressGL);
	
	SFont* font = stCreateFont("Arial", 32);
	
	SFontGL* fontGL = stCreateFontGL(font);
	
	initGL();
	
	glClearColor(0, 0, 0, 1);
	
	float speed = 1000.0f/60.0f;
	float player1Pos = 10;
	float player2Pos = 10;
	
	char player1Score = 0;
	char player2Score = 0;
	
	char* scoreText = (char*)malloc(sizeof(char) * 6);
	scoreText[0] = '0';
	scoreText[1] = ' ';
	scoreText[2] = '|';
	scoreText[3] = ' ';
	scoreText[4] = '0';
	scoreText[5] = 0;
	
	while(!swCloseRequested(window)) {
		swPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		scoreText[0] = '0' + player1Score;
		scoreText[4] = '0' + player2Score;
		
		stRenderTextGL(fontGL, "score Text", 360, 590);
		
		player1Pos += speed*key_w + speed*key_s;
		player2Pos += speed*key_up + speed*key_down;
		
		initRender();
		
		renderRect(10, player1Pos, 10, 100);
		
		renderRect(780, player2Pos, 10, 100);
		
		endRender();
		
		swSwapBufers(context);
		swDraw(window);
	}
	
	free(scoreText);
	
	swDestroyOpenGLContext(context);
	swDestroyWindow(window);
	
	swTerminate();
	
	return 0;
}

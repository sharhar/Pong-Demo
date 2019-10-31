//
//  renderer.h
//  Pong
//
//  Created by Shahar Sandhaus on 10/28/19.
//

#ifndef renderer_h
#define renderer_h

#include <glad/glad.h>

void initGL();

void initRender();
void renderRect(float x, float y, float w, float h);
void endRender();

#endif /* renderer_h */

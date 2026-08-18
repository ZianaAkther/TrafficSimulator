#ifndef DAYNIGHT_H
#define DAYNIGHT_H

extern float sunX, sunY;
extern float moonX, moonY;
extern bool nightMode;

void drawSun(float x, float y);
void drawMoon(float x, float y);
void moveSun();
void moveMoon();
void toggleNight();

#endif

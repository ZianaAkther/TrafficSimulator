#ifndef DAYNIGHT_H
#define DAYNIGHT_H

extern float sunX, sunY;   //sun
extern float moonX, moonY; //moon

extern bool nightMode; //d/n
extern bool rain; //rain


//Day/Night Functions
void drawSun(float x, float y);
void drawMoon(float x, float y);

void moveSun();
void moveMoon();

void toggleNight();

//Rain Functions
void initRain();

void startRain();
void stopRain();

void moveRain();
void drawRain();

//Sky
void setSkyColor();

#endif

#ifndef DAYNIGHT_H
#define DAYNIGHT_H

extern float sunX;
extern float sunY;

extern float moonX;
extern float moonY;

extern bool nightMode;

//top side
void drawOfficeBuilding(float x, float y);
void drawHouse(float x, float y);
void drawApartment(float x, float y);
void drawShop(float x, float y);

//bottom side
void drawLake(float x, float y);
void drawPark(float x, float y);
void drawSchool(float x, float y);
void drawParkTree(float x, float y);

//SunMoon

void drawSun(float x, float y);
void moveSun();

void drawMoon(float x, float y);
void toggleNight();
void moveMoon();

#endif

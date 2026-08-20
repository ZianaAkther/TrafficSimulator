#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// Primitive & Helper Functions
void drawRectangle(float left, float bottom, float right, float top);
void drawCircle(float cx, float cy, float radius);
void drawParkRectangle(float left, float bottom, float right, float top);

// Infrastructure & Crosswalks
void drawLaneMarking(float x1, float y1, float x2, float y2);
void drawHorizontalCrosswalk(float startX, float y);
void drawVerticalCrosswalk(float x, float startY);
void drawTrafficLight(float x, float y, int currentLight);
void drawStreetLamp(float x, float y);

// Park, School & Buildings
void drawParkTree(float x, float y);
void drawPark(float x, float y);
void drawSchool(float x, float y);
void drawLakeWithWaves(float x1, float y1, float x2, float y2);

void drawOfficeBuilding(float x, float y);
void drawHouse(float x, float y);
void drawApartment(float x, float y);
void drawShop(float x, float y);

void drawStaticEnvironment();

#endif

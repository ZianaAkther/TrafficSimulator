#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

extern float car1;
extern float car2;

extern float busY;
extern float microbusY;

extern bool moveCar;
extern bool pauseGame;
extern bool automatic;
extern bool emergency;

extern int light;
extern int verticalLight;

//Surroundings
void drawRectangle(float left, float bottom, float right, float top);
void drawLaneMarking(float x1, float y1, float x2, float y2);

void drawHorizontalCrosswalk(float startX, float y);
void drawVerticalCrosswalk(float x, float startY);

void drawOfficeBuilding(float x, float y);
void drawHouse(float x, float y);
void drawApartment(float x, float y);
void drawShop(float x, float y);

// Vehicles
void drawCircle(float cx, float cy, float radius);
void drawCar(float x, float y, float r, float g, float b);
void drawBus(float x, float y);
void drawMicrobus(float x, float y);

//TrafficLights
void drawTrafficLight(float x, float y, int currentLight);

//Vehicles Simulation
bool horizontalCarHasSpace(float newX, int currentCar);
bool canCrossStopLine(float currentX, float newX, float stopLine);
bool vehiclesOverlap(
    float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2);
bool horizontalVehicleHasClearPath(float newX, float carY);

void moveHorizontalCars();
void moveVerticalVehicles();
void resetCar(float &carX);
#endif

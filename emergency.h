#ifndef EMERGENCY_H
#define EMERGENCY_H

extern bool emergency;
extern float emergencyX;

extern float car1;
extern float car2;
extern bool pauseGame;
extern int light;
extern int verticalLight;
extern int lightCount;

void drawAmbulance(float x, float y);
void moveEmergency();

#endif

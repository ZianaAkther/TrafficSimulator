#include <windows.h>
#include <GL/glut.h>
#include "emergency.h"

bool emergency = false;
float emergencyX = -115.0f;

void moveEmergency() {
    if (!emergency) return;

    emergencyX += 0.8f;

    if (emergencyX > 110.0f) {
    emergency = false;
    emergencyX = -115.0f;

    // Safely reset phase to Horizontal RED / Vertical GREEN
    extern int light, verticalLight, lightCount;
    light = 0;
    verticalLight = 2;
    lightCount = 0;
    }
}



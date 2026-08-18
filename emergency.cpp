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
    }
}

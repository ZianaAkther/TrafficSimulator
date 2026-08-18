#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "Environment.h"
#include "Vehicles.h"
#include "DayNight.h"
#include "emergency.h"

// Vehicle Positions & Lane Offsets
float car1 = -80.0f, car1Y = -10.0f;
float car2 = -40.0f, car2Y = -10.0f;
float car3 = 80.0f;
float busY = 105.0f;
float microbusY = -105.0f;

// Controls & State
bool pauseGame = false;

// Traffic Signal States (0 = Red, 1 = Yellow, 2 = Green)
int light = 0;          // Horizontal Light (Starts RED)
int verticalLight = 2;  // Vertical Light (Starts GREEN)
int lightCount = 0;
int previousLight = 0;

// Vehicle Movement Helper
bool canCrossStopLine(float currentPos, float newPos, float stopLine, bool isPositive) {
    if (isPositive) {
        if (currentPos < stopLine && newPos >= stopLine) return false;
    } else {
        if (currentPos > stopLine && newPos <= stopLine) return false;
    }
    return true;
}

void moveHorizontalCars() {
    if (pauseGame) return;

    // Pull Over Logic During Emergency
    if (emergency) {
        if (car1Y > -20.0f) car1Y -= 0.2f;
        if (car2Y > -20.0f) car2Y -= 0.2f;
        return;
    } else {
        if (car1Y < -10.0f) car1Y += 0.2f;
        if (car2Y < -10.0f) car2Y += 0.2f;
    }

    float speed = (light == 1) ? 0.2f : 0.5f;
    float minGap = 24.0f;

    // Move Car 2 (Lead Car)
    float newX2 = car2 + speed;
    if (light == 2 || canCrossStopLine(car2, newX2, -37.0f, true)) {
        car2 = newX2;
    }

    // Move Car 1 (Follower - Enforces Gap)
    float newX1 = car1 + speed;
    bool gapIsSafe = (car2 <= car1) || ((car2 - car1) >= minGap);

    if ((light == 2 || canCrossStopLine(car1, newX1, -37.0f, true)) && gapIsSafe) {
        car1 = newX1;
    }

    // Move Car 3 (Opposite Direction)
    float newX3 = car3 - speed;
    if (light == 2 || canCrossStopLine(car3, newX3, 25.0f, false)) {
        car3 = newX3;
    }

    // Screen Boundary Wrap Around
    if (car2 > 110.0f) car2 = -110.0f;
    if (car1 > 110.0f) car1 = -110.0f;
    if (car3 < -110.0f) car3 = 110.0f;
}

void moveVerticalVehicles() {
    if (pauseGame || emergency) return;

    float speed = (verticalLight == 1) ? 0.2f : 0.5f;

    float newBusY = busY - speed;
    if (verticalLight == 2 || canCrossStopLine(busY, newBusY, 40.0f, false)) {
        busY = newBusY;
    }

    float newMicrobusY = microbusY + speed;
    if (verticalLight == 2 || canCrossStopLine(microbusY, newMicrobusY, -44.0f, true)) {
        microbusY = newMicrobusY;
    }

    if (busY < -110.0f) busY = 110.0f;
    if (microbusY > 110.0f) microbusY = -110.0f;
}

void timer(int value) {
    if (emergency) {
        moveEmergency();
    } else {
        lightCount++;

        if (light == 0) { // Horizontal RED, Vertical GREEN
            verticalLight = 2;
            if (lightCount >= 100) {
                previousLight = 0;
                light = 1;
                verticalLight = 1;
                lightCount = 0;
            }
        } else if (light == 1) { // YELLOW Transition
            verticalLight = 1;
            if (lightCount >= 50) {
                if (previousLight == 0) { light = 2; verticalLight = 0; }
                else { light = 0; verticalLight = 2; }
                lightCount = 0;
            }
        } else if (light == 2) { // Horizontal GREEN, Vertical RED
            verticalLight = 0;
            if (lightCount >= 200) {
                previousLight = 2;
                light = 1;
                verticalLight = 1;
                lightCount = 0;
            }
        }
    }

    moveHorizontalCars();
    moveVerticalVehicles();
    moveSun();
    moveMoon();

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'p': case 'P':
            pauseGame = !pauseGame;
            break;
        case 'n': case 'N':
            toggleNight();
            break;
        case 'e': case 'E':
            emergency = true;
            emergencyX = -115.0f;
            light = 0;
            verticalLight = 0; // Both directions set to RED during emergency
            break;
        case 'r': case 'R': // Complete System Reset
            car1 = -80.0f; car1Y = -10.0f;
            car2 = -40.0f; car2Y = -10.0f;
            car3 = 80.0f;
            busY = 105.0f;
            microbusY = -105.0f;
            pauseGame = false;
            emergency = false;
            emergencyX = -115.0f;
            light = 0;
            verticalLight = 2;
            previousLight = 0;
            lightCount = 0;
            break;
        case 27:
            exit(0);
            break;
    }
}

void display() {
    if (nightMode) glClearColor(0.03f, 0.05f, 0.15f, 1.0f);
    else glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Celestial Bodies
    if (nightMode) drawMoon(moonX, moonY);
    else drawSun(sunX, sunY);

    // 2. Environment
    drawStaticEnvironment();

    // 3. Traffic Signals
    drawTrafficLight(28.0f, 25.0f, light);
    drawTrafficLight(-28.0f, -42.0f, verticalLight);

    // 4. Vehicles
    drawCar(car1, car1Y, 0.8f, 0.1f, 0.1f);  // Red Car
    drawCar(car2, car2Y, 0.1f, 0.3f, 0.8f);  // Blue Car
    drawCar(car3, 10.0f, 0.1f, 0.8f, 0.2f);   // Green Car

    drawBus(-18.0f, busY);
    drawMicrobus(5.0f, microbusY);

    // 5. Emergency Vehicle
    if (emergency) {
        drawAmbulance(emergencyX, -6.0f);
    }

    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Automated Traffic Simulator");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    // Note: glutSpecialFunc removed (no manual mode needed)
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

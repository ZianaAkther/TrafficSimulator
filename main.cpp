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

// Boats
float boat1X = 35.0f;
float boat1Y = -48.0f;
bool boat1MovingRight = true;  // Boat 1 starts moving right

float boat2X = 88.0f;
float boat2Y = -78.0f;
bool boat2MovingRight = false; // Boat 2 starts moving left

// Controls & State
bool pauseGame = false;

// Traffic Signal States (0 = Red, 1 = Yellow, 2 = Green)
int light = 0;          // Horizontal Light (Starts RED)
int verticalLight = 2;  // Vertical Light (Starts GREEN)
int lightCount = 0;
int previousLight = 0;

void timer(int value) {
    if (pauseGame) {
        glutPostRedisplay();
        glutTimerFunc(30, timer, 0);
        return;
    }

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
    moveBoats();

    moveSun();
    moveMoon();
    moveRain();

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) return;

    if (button == GLUT_LEFT_BUTTON) {
        startRain();
    } else if (button == GLUT_RIGHT_BUTTON) {
        stopRain();
    }
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
            if (!pauseGame) {
                emergency = true;
                emergencyX = -115.0f;
            }
            break;
        case 'r': case 'R':
            car1 = -80.0f; car1Y = -10.0f;
            car2 = -40.0f; car2Y = -10.0f;
            car3 = 80.0f;
            busY = 105.0f;
            microbusY = -105.0f;

            boat1X = 35.0f; boat1Y = -48.0f;
            boat2X = 88.0f; boat2Y = -78.0f;
            boat1MovingRight = true;
            boat2MovingRight = false;

            pauseGame = false;
            emergency = false;
            emergencyX = -115.0f;

            light = 0;
            verticalLight = 2;
            previousLight = 0;
            lightCount = 0;

            stopRain();
            break;
        case 27:
            exit(0);
            break;
    }
}

void display() {

    setSkyColor();
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Celestial Bodies
    if (!rain) {
        if (nightMode) drawMoon(moonX, moonY);
        else drawSun(sunX, sunY);
    }

    // 2. Environment
    drawStaticEnvironment();

    // 3. Traffic Signals (Force RED during emergency visually)
    drawTrafficLight(28.0f, 25.0f, emergency ? 0 : light);
    drawTrafficLight(-28.0f, -42.0f, emergency ? 0 : verticalLight);

    // 4. Vehicles
    drawCar(car1, car1Y, 0.8f, 0.1f, 0.1f);
    drawCar(car2, car2Y, 0.1f, 0.3f, 0.8f);
    drawCar(car3, 10.0f, 0.1f, 0.8f, 0.2f);

    drawBus(-18.0f, busY);
    drawMicrobus(5.0f, microbusY);

    // 5. Emergency Vehicle
    if (emergency) {
        drawAmbulance(emergencyX, -6.0f);
    }

    // 6. Rain
    drawRain();

    // 7. Boats
    drawBoat(boat1X, boat1Y);
    drawBoat(boat2X, boat2Y);

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
    glutCreateWindow("GoingMerry- InteractiveTraffic Simulator");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

//main.cpp
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "DayNight.h"
#include "emergency.h"
#include "Environment.h"

// ================= CAR VARIABLES =================

float car1 = -80;
float car2 = -40;

int selectedCar = 1;

bool moveCar = true;
bool pauseGame = false;

bool automatic = true;

// ================= VERTICAL VEHICLES =================

float busY = 80;
float microbusY = -80;

// ================= TRAFFIC LIGHT =================

// Horizontal road
// 0 = Red
// 1 = Yellow
// 2 = Green

int light = 0;
int lightCount = 0;
int previousLight = 0;

// Vertical road
int verticalLight = 2;

// ============================================================
// TIMER
// ============================================================

void timer(int value)
{
    // ========================================================
    // NORMAL TRAFFIC SIGNAL
    // ========================================================

    if (emergency == false)
    {
        lightCount++;

        // ----------------------------------------------------
        // HORIZONTAL RED / VERTICAL GREEN
        // ----------------------------------------------------
        if (light == 0)
        {
            verticalLight = 2;

            if (lightCount >= 100)
            {
                previousLight = 0;

                light = 1;
                verticalLight = 1;
                lightCount = 0;
            }
        }

        // ----------------------------------------------------
        // BOTH YELLOW
        // ----------------------------------------------------
        else if (light == 1)
        {
            verticalLight = 1;

            if (lightCount >= 50)
            {
                // Coming from RED/GREEN
                if (previousLight == 0)
                {
                    light = 2;
                    verticalLight = 0;
                }

                // Coming from GREEN/RED
                else if (previousLight == 2)
                {
                    light = 0;
                    verticalLight = 2;
                }

                lightCount = 0;
            }
        }

        // ----------------------------------------------------
        // HORIZONTAL GREEN / VERTICAL RED
        // ----------------------------------------------------
        else if (light == 2)
        {
            verticalLight = 0;

            if (lightCount >= 200)
            {
                previousLight = 2;

                light = 1;
                verticalLight = 1;
                lightCount = 0;
            }
        }
    }
    else
    {
        // Emergency gets priority.
        light = 0;
        verticalLight = 0;
        moveEmergency();
    }

    // ========================================================
    // VEHICLE MOVEMENT
    // ========================================================

    moveHorizontalCars();
    moveVerticalVehicles();

    // ========================================================
    // ENVIRONMENT
    // ========================================================

    moveSun();
    moveMoon();

    // ========================================================
    // REDRAW
    // ========================================================

    glutPostRedisplay();

    // Run again after 30 ms
    glutTimerFunc(30, timer, 0);
}

// ============================================================
// KEYBOARD
// ============================================================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':

            automatic = true;

            break;

        case 'm':
        case 'M':

            automatic = false;

            break;

        case '1':

            selectedCar = 1;

            break;

        case '2':

            selectedCar = 2;

            break;

        case 's':
        case 'S':

            moveCar = false;

            break;


        case 'g':
        case 'G':

            moveCar = true;

            break;

        case 'p':
        case 'P':

            pauseGame = !pauseGame;

            break;

        case 'r':
        case 'R':

            // Reset horizontal cars
            car1 = -80;
            car2 = -40;

            // Reset vertical vehicles
            busY = 80;
            microbusY = -80;

            selectedCar = 1;

            moveCar = true;
            pauseGame = false;

            automatic = true;

            // Reset emergency
            emergency = false;
            emergencyX = -100;

            // Reset traffic lights
            light = 0;
            verticalLight = 2;

            // Reset timer
            lightCount = 0;

            break;

        case 'n':
        case 'N':

            toggleNight();

            break;


        case 'e':
        case 'E':

            emergency = true;
            emergencyX = -100;

            light = 0;
            verticalLight = 0;
            lightCount = 0;

            break;

        case 27:

            exit(0);

            break;
    }
}


// ============================================================
// MANUAL CONTROL
// ============================================================

void specialKeyboard(int key, int x, int y)
{
    if (automatic == false &&
        pauseGame == false)
    {
        if (key == GLUT_KEY_RIGHT)
        {
            if (selectedCar == 1)
                car1 = car1 + 2;

            if (selectedCar == 2)
                car2 = car2 + 2;

        }

        if (key == GLUT_KEY_LEFT)
        {
            if (selectedCar == 1)
                car1 = car1 - 2;

            if (selectedCar == 2)
                car2 = car2 - 2;
        }
    }

    glutPostRedisplay();
}

// ============================================================
// DISPLAY
// ============================================================

void display()
{
    if (nightMode)
    {
        glClearColor(0.03f, 0.05f, 0.15f, 1.0f);
    }
    else
    {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    // ========================================================
    // SUN / MOON
    // ========================================================

    if (nightMode)
    {
        drawMoon(moonX, moonY);
    }
    else
    {
        drawSun(sunX, sunY);
    }

    // ========================================================
    // ENVIRONMENT
    // ========================================================

    drawPark(-100, -100);
    drawSchool(-80, -65);
    drawLake(25, -100);

    drawParkTree(-92, -45);
    drawParkTree(-35, -45);

    drawParkTree(-92, -85);
    drawParkTree(-35, -85);

    // ========================================================
    // HORIZONTAL ROAD
    // ========================================================

    glColor3f(0.2f, 0.2f, 0.2f);
    drawRectangle(-100, -25, 100, 25);

    // ========================================================
    // VERTICAL ROAD
    // ========================================================

    drawRectangle(-25, -100, 25, 100);

    // ========================================================
    // SIDEWALKS
    // ========================================================

    glColor3f(0.7f, 0.7f, 0.7f);

    drawRectangle(-100, 25, -25, 32);
    drawRectangle(25, 25, 100, 32);
    drawRectangle(-100, -32, -25, -25);
    drawRectangle(25, -32, 100, -25);

    // ========================================================
    // ENVIRONMENT BUILDINGS
    // ========================================================

    drawOfficeBuilding(-90, 32);
    drawHouse(-60, 32);
    drawApartment(35, 32);
    drawShop(70, 32);

    // ========================================================
    // LANE MARKINGS
    // ========================================================

    drawLaneMarking(-90, -1, -60, 1);
    drawLaneMarking(-50, -1, -20, 1);
    drawLaneMarking(20, -1, 50, 1);
    drawLaneMarking(60, -1, 90, 1);

    // VERTICAL

    drawLaneMarking(-1, 60, 1, 90);
    drawLaneMarking(-1, 20, 1, 50);
    drawLaneMarking(-1, -50, 1, -20);
    drawLaneMarking(-1, -90, 1, -60);

    // ========================================================
    // ZEBRA CROSSINGS
    // ========================================================

    drawHorizontalCrosswalk(-12, 27);
    drawHorizontalCrosswalk(-12, -35);

    drawVerticalCrosswalk(27, -12);
    drawVerticalCrosswalk(-35, -12);

    // ========================================================
    // TRAFFIC LIGHTS
    // ========================================================

    // Horizontal traffic light - upper right
    drawTrafficLight(30, 30, light);

    // Vertical traffic light - opposite lower left
    drawTrafficLight(-35, -15, verticalLight);

    // ========================================================
    // HORIZONTAL CARS
    // ========================================================

    // Red car - lower lane
    drawCar(car1, -10, 0.8f, 0.1f, 0.1f);

    // Blue car - lower lane
    drawCar(car2, -10, 0.1f, 0.3f, 0.8f);

    // ========================================================
    // VERTICAL VEHICLES
    // ========================================================

    // LEFT SIDE OF VERTICAL ROAD
    drawBus(-18, busY);

    // RIGHT SIDE OF VERTICAL ROAD
    drawMicrobus(5, microbusY);

    // ========================================================
    // EMERGENCY VEHICLE

    if (emergency == true)
    {
        drawAmbulance(emergencyX, 10);
    }

    glFlush();
}

// ============================================================
// INIT
// ============================================================

void init()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-100, 100, -100, 100);
}

// ============================================================
// MAIN
// ============================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(900, 700);

    glutCreateWindow("Team GoingMerry - Traffic Simulator");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutSpecialFunc(specialKeyboard);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "DayNight.h"
#include "emergency.h"

// ================= CAR VARIABLES =================

float car1 = -80;
float car2 = -40;
float car3 = 20;

int selectedCar = 1;

bool moveCar = true;
bool pauseGame = false;

bool automatic = true;

// ================= VERTICAL VEHICLES =================

float busY = 80;
float microbusY = -80;

// ================= EMERGENCY =================

bool emergency = false;
float emergencyX = -100;

// ================= TRAFFIC LIGHT =================

// Horizontal road
// 0 = Red
// 1 = Yellow
// 2 = Green

int light = 0;
int lightCount = 0;

// Vertical road
int verticalLight = 2;


// ================= DRAW RECTANGLE =================

void drawRectangle(float left, float bottom, float right, float top)
{
    glBegin(GL_QUADS);

        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);

    glEnd();
}


// ================= LANE MARKING =================

void drawLaneMarking(float x1, float y1, float x2, float y2)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(x1, y1, x2, y2);
}


// ================= CROSSWALK =================

void drawHorizontalCrosswalk(float startX, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 6; i++)
    {
        float x = startX + i * 4;

        drawRectangle(x, y, x + 2, y + 8);
    }
}


void drawVerticalCrosswalk(float x, float startY)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 6; i++)
    {
        float y = startY + i * 4;

        drawRectangle(x, y, x + 8, y + 2);
    }
}


// ================= CIRCLE =================

void drawCircle(float cx, float cy, float radius)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100;

        glVertex2f(
            cx + cos(angle) * radius,
            cy + sin(angle) * radius
        );
    }

    glEnd();
}


// ================= TRAFFIC LIGHT =================

void drawTrafficLight(float x, float y, int currentLight)
{
    // Pole
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 1, y - 15, x + 1, y);

    // Box
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 5, y, x + 5, y + 18);

    // RED
    if (currentLight == 0)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.3f, 0.0f, 0.0f);

    drawCircle(x, y + 14, 2.5f);

    // YELLOW
    if (currentLight == 1)
        glColor3f(1.0f, 1.0f, 0.0f);
    else
        glColor3f(0.3f, 0.3f, 0.0f);

    drawCircle(x, y + 9, 2.5f);

    // GREEN
    if (currentLight == 2)
        glColor3f(0.0f, 1.0f, 0.0f);
    else
        glColor3f(0.0f, 0.3f, 0.0f);

    drawCircle(x, y + 4, 2.5f);
}


// ================= CAR =================

void drawCar(float x, float y, float r, float g, float b)
{
    // Body
    glColor3f(r, g, b);

    drawRectangle(x, y, x + 12, y + 6);

    // Roof
    drawRectangle(x + 3, y + 6, x + 9, y + 10);

    // Windows
    glColor3f(0.2f, 0.6f, 0.8f);

    drawRectangle(x + 4, y + 7, x + 6, y + 9);
    drawRectangle(x + 6.5f, y + 7, x + 8, y + 9);

    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);

    drawCircle(x + 3, y, 1.5f);
    drawCircle(x + 9, y, 1.5f);
}


// ================= RED BLACK BUS =================

void drawBus(float x, float y)
{
    // Main body
    glColor3f(0.05f, 0.05f, 0.05f);
    drawRectangle(x, y, x + 8, y + 18);

    // Red upper part
    glColor3f(0.8f, 0.0f, 0.0f);
    drawRectangle(x, y + 13, x + 8, y + 18);

    // Windows
    glColor3f(0.2f, 0.6f, 0.8f);

    drawRectangle(x + 1, y + 9, x + 7, y + 12);
    drawRectangle(x + 1, y + 5, x + 7, y + 8);

    // Wheels
    glColor3f(0.02f, 0.02f, 0.02f);

    drawCircle(x + 1, y + 2, 1.3f);
    drawCircle(x + 7, y + 2, 1.3f);
}


// ================= MICROBUS =================

void drawMicrobus(float x, float y)
{
    // Body
    glColor3f(0.85f, 0.65f, 0.1f);

    drawRectangle(x, y, x + 8, y + 12);

    // Top
    glColor3f(0.9f, 0.75f, 0.2f);

    drawRectangle(x + 1, y + 12, x + 7, y + 14);

    // Front window
    glColor3f(0.2f, 0.6f, 0.8f);

    drawRectangle(x + 1, y + 8, x + 7, y + 11);

    // Lower window
    drawRectangle(x + 1, y + 4, x + 7, y + 7);

    // Wheels
    glColor3f(0.02f, 0.02f, 0.02f);

    drawCircle(x + 1, y + 2, 1.2f);
    drawCircle(x + 7, y + 2, 1.2f);
}


// ============================================================
// CHECK HORIZONTAL CAR SPACING
// ============================================================

bool horizontalCarHasSpace(float newX, int currentCar)
{
    float gap = 16.0f;

    // CAR 1 AND CAR 2 ARE IN THE LOWER LANE
    if (currentCar == 1)
    {
        if (car2 > newX && car2 - newX < gap)
            return false;
    }

    if (currentCar == 2)
    {
        if (car1 > newX && car1 - newX < gap)
            return false;
    }

    // CAR 3 IS IN THE UPPER LANE
    // Therefore it does NOT collide with car1 or car2.
    if (currentCar == 3)
    {
        return true;
    }

    return true;
}


// ============================================================
// MOVE HORIZONTAL CARS
// ============================================================

void moveHorizontalCars()
{
    if (automatic == false ||
        moveCar == false ||
        pauseGame == true)
    {
        return;
    }

    float normalSpeed = 0.5f;
    float yellowSpeed = 0.2f;

    // Stop line
    float stopLine = -37.0f;


    // ========================================================
    // EMERGENCY MODE
    // ========================================================

    if (emergency == true)
    {
        // Normal cars move slower so ambulance can pass.
        float emergencyTrafficSpeed = 0.25f;

        // ----------------------------------------------------
        // CAR 1
        // ----------------------------------------------------

        float newCar1 = car1 + emergencyTrafficSpeed;

        if (horizontalCarHasSpace(newCar1, 1))
            car1 = newCar1;


        // ----------------------------------------------------
        // CAR 2
        // ----------------------------------------------------

        float newCar2 = car2 + emergencyTrafficSpeed;

        if (horizontalCarHasSpace(newCar2, 2))
            car2 = newCar2;


        // ----------------------------------------------------
        // CAR 3
        // ----------------------------------------------------
        // Green car is on another lane, so ambulance does not
        // interact with it.

        float newCar3 = car3 + emergencyTrafficSpeed;

        car3 = newCar3;


        // ----------------------------------------------------
        // RESET CARS
        // ----------------------------------------------------

        if (car1 > 105)
            car1 = -105;

        if (car2 > 105)
            car2 = -105;

        if (car3 > 105)
            car3 = -105;

        return;
    }


    // ========================================================
    // NORMAL TRAFFIC
    // ========================================================

    float speed;

    if (light == 0)
    {
        speed = normalSpeed;
    }
    else if (light == 1)
    {
        speed = yellowSpeed;
    }
    else
    {
        speed = normalSpeed;
    }


    // ========================================================
    // CAR 1
    // ========================================================

    float newX1 = car1 + speed;

    bool allowedCar1 = true;

    // Red or Yellow:
    // Stop only if car has NOT crossed the stop line.
    if (light != 2)
    {
        if (car1 < stopLine &&
            newX1 >= stopLine)
        {
            allowedCar1 = false;
        }

        if (car1 >= stopLine)
        {
            allowedCar1 = true;
        }
    }

    if (allowedCar1 &&
        horizontalCarHasSpace(newX1, 1))
    {
        car1 = newX1;
    }


    // ========================================================
    // CAR 2
    // ========================================================

    float newX2 = car2 + speed;

    bool allowedCar2 = true;

    if (light != 2)
    {
        if (car2 < stopLine &&
            newX2 >= stopLine)
        {
            allowedCar2 = false;
        }

        if (car2 >= stopLine)
        {
            allowedCar2 = true;
        }
    }

    if (allowedCar2 &&
        horizontalCarHasSpace(newX2, 2))
    {
        car2 = newX2;
    }


    // ========================================================
    // CAR 3
    // ========================================================
    // Green car is in the upper lane.
    // It has its own lane spacing.

    float newX3 = car3 + speed;

    bool allowedCar3 = true;

    if (light != 2)
    {
        if (car3 < stopLine &&
            newX3 >= stopLine)
        {
            allowedCar3 = false;
        }

        if (car3 >= stopLine)
        {
            allowedCar3 = true;
        }
    }

    if (allowedCar3)
    {
        car3 = newX3;
    }


    // ========================================================
    // RESET AFTER LEAVING SCREEN
    // ========================================================

    if (car1 > 105)
    {
        if (car2 < -85)
            car1 = -105;
    }

    if (car2 > 105)
    {
        if (car1 < -85)
            car2 = -105;
    }

    if (car3 > 105)
    {
        car3 = -105;
    }
}


// ============================================================
// MOVE VERTICAL VEHICLES
// ============================================================

void moveVerticalVehicles()
{
    if (automatic == false ||
        moveCar == false ||
        pauseGame == true)
    {
        return;
    }

    float speed = 0.0f;

    if (verticalLight == 0)
    {
        speed = 0.0f;
    }
    else if (verticalLight == 1)
    {
        speed = 0.2f;
    }
    else
    {
        speed = 0.5f;
    }


    // ========================================================
    // BUS MOVES UP
    // ========================================================

    if (speed > 0.0f)
    {
        float newY = busY + speed;

        bool allowedByLight = true;

        if (verticalLight != 2 &&
            busY < -44 &&
            newY > -44)
        {
            allowedByLight = false;
        }

        if (allowedByLight)
        {
            busY = newY;
        }
    }


    // ========================================================
    // MICROBUS MOVES DOWN
    // ========================================================

    if (speed > 0.0f)
    {
        float newY = microbusY - speed;

        bool allowedByLight = true;

        if (verticalLight != 2 &&
            microbusY > 40 &&
            newY < 40)
        {
            allowedByLight = false;
        }

        if (allowedByLight)
        {
            microbusY = newY;
        }
    }


    // ========================================================
    // BUS RESET
    // ========================================================

    if (busY > 110)
        busY = -110;


    // ========================================================
    // MICROBUS RESET
    // ========================================================

    if (microbusY < -110)
        microbusY = 110;
}


// ============================================================
// EMERGENCY VEHICLE
// ============================================================

void moveEmergency()
{
    if (emergency == false ||
        pauseGame == true)
    {
        return;
    }

    float emergencySpeed = 0.8f;

    bool blocked = false;

    // Ambulance is on LOWER lane.
    float ambulanceFront = emergencyX + 18.0f;

    float safeDistance = 17.0f;


    // ========================================================
    // CHECK CAR 1
    // ========================================================

    if (car1 > emergencyX &&
        car1 - ambulanceFront < safeDistance)
    {
        blocked = true;
    }


    // ========================================================
    // CHECK CAR 2
    // ========================================================

    if (car2 > emergencyX &&
        car2 - ambulanceFront < safeDistance)
    {
        blocked = true;
    }


    // ========================================================
    // CAR 3 IS ON OTHER LANE
    // ========================================================
    // Therefore it is NOT considered an obstacle for ambulance.


    // ========================================================
    // MOVE AMBULANCE
    // ========================================================

    if (blocked == false)
    {
        emergencyX += emergencySpeed;
    }


    // ========================================================
    // EMERGENCY FINISHED
    // ========================================================

    if (emergencyX > 110)
    {
        emergency = false;

        emergencyX = -100;

        // Start normal cycle again from RED.
        light = 0;
        verticalLight = 2;

        lightCount = 0;
    }
}


// ============================================================
// TIMER
// ============================================================

void timer(int value)
{
    // ========================================================
    // EMERGENCY MODE
    // ========================================================

    if (emergency == true)
    {
        // Emergency gets priority.
        light = 2;
        verticalLight = 0;

        moveHorizontalCars();
        moveVerticalVehicles();
        moveEmergency();
    }


    // ========================================================
    // NORMAL MODE
    // ========================================================

    else
    {
        // Count always starts from the current light state.
        lightCount++;


        // ====================================================
        // RED
        // ====================================================

        if (light == 0)
        {
            verticalLight = 2;

            // RED = 100 timer cycles
            if (lightCount >= 100)
            {
                light = 2;

                verticalLight = 0;

                lightCount = 0;
            }
        }


        // ====================================================
        // GREEN
        // ====================================================

        else if (light == 2)
        {
            verticalLight = 0;

            // GREEN = 200 timer cycles
            if (lightCount >= 200)
            {
                light = 1;

                verticalLight = 0;

                lightCount = 0;
            }
        }


        // ====================================================
        // YELLOW
        // ====================================================

        else if (light == 1)
        {
            verticalLight = 0;

            // YELLOW = 50 timer cycles
            if (lightCount >= 50)
            {
                light = 0;

                verticalLight = 2;

                lightCount = 0;
            }
        }


        moveHorizontalCars();
        moveVerticalVehicles();
    }


    moveSun();
    moveMoon();

    glutPostRedisplay();

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


        case '3':

            selectedCar = 3;

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
            car3 = 20;

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

            // Emergency gets green light
            light = 2;

            // Other road gets red
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

            if (selectedCar == 3)
                car3 = car3 + 2;
        }


        if (key == GLUT_KEY_LEFT)
        {
            if (selectedCar == 1)
                car1 = car1 - 2;

            if (selectedCar == 2)
                car2 = car2 - 2;

            if (selectedCar == 3)
                car3 = car3 - 2;
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

    // Green car - upper lane
    drawCar(car3, 3, 0.1f, 0.7f, 0.2f);


    // ========================================================
    // VERTICAL VEHICLES
    // ========================================================

    // LEFT SIDE OF VERTICAL ROAD
    drawBus(-18, busY);

    // RIGHT SIDE OF VERTICAL ROAD
    drawMicrobus(5, microbusY);


    // ========================================================
    // EMERGENCY VEHICLE
    // ========================================================

    if (emergency == true)
    {
        drawAmbulance(emergencyX, -10);
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

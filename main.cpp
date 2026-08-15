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


// ================= MOVE HORIZONTAL CARS =================

void moveHorizontalCars()
{
    float speed = 0;

    if (light == 0)
        speed = 0;

    if (light == 1)
        speed = 0.2f;

    if (light == 2)
        speed = 0.5f;


    if (automatic == true &&
        moveCar == true &&
        pauseGame == false)
    {
        // If the car is already inside the intersection,
        // allow it to leave completely.

        if (light == 2)
        {
            car1 += speed;
            car2 += speed;
            car3 += speed;
        }
        else
        {
            // Car 1
            if (car1 < -37 || car1 > 25)
                car1 += speed;

            // Car 2
            if (car2 < -37 || car2 > 25)
                car2 += speed;

            // Car 3
            if (car3 > 25)
                car3 += speed;
        }
    }


    // Reset after leaving screen

    if (car1 > 100)
        car1 = -100;

    if (car2 > 100)
        car2 = -100;

    if (car3 > 100)
        car3 = -100;
}


// ================= MOVE VERTICAL VEHICLES =================

void moveVerticalVehicles()
{
    float speed = 0;

    if (verticalLight == 0)
        speed = 0;

    if (verticalLight == 1)
        speed = 0.2f;

    if (verticalLight == 2)
        speed = 0.5f;


    if (automatic == true &&
        moveCar == true &&
        pauseGame == false)
    {
        // BUS MOVES UP

        if (verticalLight == 2)
        {
            busY += speed;
        }
        else
        {
            // If already near/inside intersection,
            // keep moving until it clears.

            if (busY < -37 || busY > 25)
                busY += speed;
        }


        // MICROBUS MOVES DOWN

        if (verticalLight == 2)
        {
            microbusY -= speed;
        }
        else
        {
            if (microbusY > 37 || microbusY < -25)
                microbusY -= speed;
        }
    }


    // Reset bus

    if (busY > 110)
        busY = -110;


    // Reset microbus

    if (microbusY < -110)
        microbusY = 110;
}


// ================= EMERGENCY =================

void moveEmergency()
{
    if (emergency == true &&
        pauseGame == false)
    {
        emergencyX += 0.8f;

        if (emergencyX > 110)
        {
            emergency = false;
            emergencyX = -100;

            // Normal traffic resumes
            light = 0;
            verticalLight = 2;
            lightCount = 0;
        }
    }
}


// ================= TIMER =================

void timer(int value)
{
    moveHorizontalCars();
    moveVerticalVehicles();
    moveEmergency();

    moveSun();
    moveMoon();

    // ================= EMERGENCY PRIORITY =================

    if (emergency == true)
    {
        // Horizontal side gets green
        light = 2;

        // Vertical side gets red
        verticalLight = 0;
    }
    else
    {
        lightCount++;

        // RED -> GREEN
        if (light == 0 && lightCount >= 100)
        {
            light = 2;
            verticalLight = 0;

            lightCount = 0;
        }

        // GREEN -> YELLOW
        if (light == 2 && lightCount >= 200)
        {
            light = 1;
            verticalLight = 0;

            lightCount = 0;
        }

        // YELLOW -> RED
        if (light == 1 && lightCount >= 50)
        {
            light = 0;

            // Vertical becomes GREEN
            verticalLight = 2;

            lightCount = 0;
        }
    }


    glutPostRedisplay();

    glutTimerFunc(30, timer, 0);
}


// ================= KEYBOARD =================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // AUTOMATIC MODE
        case 'a':
        case 'A':

            automatic = true;

            break;


        // MANUAL MODE
        case 'm':
        case 'M':

            automatic = false;

            break;


        // SELECT CAR 1
        case '1':

            selectedCar = 1;

            break;


        // SELECT CAR 2
        case '2':

            selectedCar = 2;

            break;


        // SELECT CAR 3
        case '3':

            selectedCar = 3;

            break;


        // STOP
        case 's':
        case 'S':

            moveCar = false;

            break;


        // START
        case 'g':
        case 'G':

            moveCar = true;

            break;


        // PAUSE / RESUME
        case 'p':
        case 'P':

            pauseGame = !pauseGame;

            break;


        // RESET
        case 'r':
        case 'R':

            car1 = -80;
            car2 = -40;
            car3 = 20;

            busY = 80;
            microbusY = -80;

            selectedCar = 1;

            moveCar = true;
            pauseGame = false;

            automatic = true;

            emergency = false;
            emergencyX = -100;

            light = 0;
            verticalLight = 2;
            lightCount = 0;

            break;


        // NIGHT MODE
        case 'n':
        case 'N':

            toggleNight();

            break;


        // EMERGENCY
        case 'e':
        case 'E':

            emergency = true;

            // Emergency starts from left
            emergencyX = -100;

            // Give horizontal road priority
            light = 2;
            verticalLight = 0;

            lightCount = 0;

            break;


        // EXIT
        case 27:

            exit(0);

            break;
    }
}


// ================= MANUAL CONTROL =================

void specialKeyboard(int key, int x, int y)
{
    if (automatic == false && pauseGame == false)
    {
        // RIGHT ARROW

        if (key == GLUT_KEY_RIGHT)
        {
            if (selectedCar == 1)
                car1 = car1 + 2;

            if (selectedCar == 2)
                car2 = car2 + 2;

            if (selectedCar == 3)
                car3 = car3 + 2;
        }


        // LEFT ARROW

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


// ================= DISPLAY =================

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


    // SUN / MOON

    if (nightMode)
    {
        drawMoon(moonX, moonY);
    }
    else
    {
        drawSun(sunX, sunY);
    }


    // ENVIRONMENT

    drawPark(-100, -100);
    drawSchool(-80, -65);
    drawLake(25, -100);

    drawParkTree(-92, -45);
    drawParkTree(-35, -45);

    drawParkTree(-92, -85);
    drawParkTree(-35, -85);


    // ================= HORIZONTAL ROAD =================

    glColor3f(0.2f, 0.2f, 0.2f);

    drawRectangle(-100, -25, 100, 25);


    // ================= VERTICAL ROAD =================

    drawRectangle(-25, -100, 25, 100);


    // ================= SIDEWALKS =================

    glColor3f(0.7f, 0.7f, 0.7f);

    // Top-left
    drawRectangle(-100, 25, -25, 32);

    // Top-right
    drawRectangle(25, 25, 100, 32);

    // Bottom-left
    drawRectangle(-100, -32, -25, -25);

    // Bottom-right
    drawRectangle(25, -32, 100, -25);


    // ================= ENVIRONMENT =================

    drawOfficeBuilding(-90, 32);
    drawHouse(-60, 32);
    drawApartment(35, 32);
    drawShop(70, 32);


    // ================= LANE MARKINGS =================

    drawLaneMarking(-90, -1, -60, 1);
    drawLaneMarking(-50, -1, -20, 1);
    drawLaneMarking(20, -1, 50, 1);
    drawLaneMarking(60, -1, 90, 1);


    // VERTICAL

    drawLaneMarking(-1, 60, 1, 90);
    drawLaneMarking(-1, 20, 1, 50);
    drawLaneMarking(-1, -50, 1, -20);
    drawLaneMarking(-1, -90, 1, -60);


    // ================= ZEBRA CROSSINGS =================

    drawHorizontalCrosswalk(-12, 27);
    drawHorizontalCrosswalk(-12, -35);

    drawVerticalCrosswalk(27, -12);
    drawVerticalCrosswalk(-35, -12);


    // ================= TRAFFIC LIGHTS =================

    // Horizontal traffic light
    drawTrafficLight(30, 30, light);

    // Vertical traffic light
    drawTrafficLight(-30, 30, verticalLight);


    // ================= HORIZONTAL CARS =================

    drawCar(car1, -10, 0.8f, 0.1f, 0.1f);

    drawCar(car2, -10, 0.1f, 0.3f, 0.8f);

    drawCar(car3, -10, 0.1f, 0.7f, 0.2f);


    // ================= VERTICAL VEHICLES =================

    // LEFT SIDE OF VERTICAL ROAD
    drawBus(-18, busY);

    // RIGHT SIDE OF VERTICAL ROAD
    drawMicrobus(5, microbusY);


    // ================= EMERGENCY VEHICLE =================

    if (emergency == true)
    {
        drawAmbulance(emergencyX, -10);
    }


    glFlush();
}


// ================= INIT =================

void init()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-100, 100, -100, 100);
}


// ================= MAIN =================

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

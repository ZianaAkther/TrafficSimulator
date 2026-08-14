#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// ================= CAR VARIABLES =================

float car1 = -80;
float car2 = -40;
float car3 = 20;

int selectedCar = 1;

bool moveCar = true;
bool pauseGame = false;

bool automatic = true;

// Traffic light
// 0 = Red
// 1 = Yellow
// 2 = Green

int light = 0;
int lightCount = 0;


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

void drawTrafficLight(float x, float y)
{
    // Pole
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 1, y - 15, x + 1, y);

    // Traffic light box
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 5, y, x + 5, y + 18);

    // Red
    if (light == 0)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.3f, 0.0f, 0.0f);

    drawCircle(x, y + 14, 2.5f);

    // Yellow
    if (light == 1)
        glColor3f(1.0f, 1.0f, 0.0f);
    else
        glColor3f(0.3f, 0.3f, 0.0f);

    drawCircle(x, y + 9, 2.5f);

    // Green
    if (light == 2)
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


// ================= MOVE THREE CARS =================

void moveCars()
{
    float speed = 0;

    // RED
    if (light == 0)
    {
        speed = 0;
    }

    // YELLOW
    if (light == 1)
    {
        speed = 0.2;
    }

    // GREEN
    if (light == 2)
    {
        speed = 0.5;
    }


    // AUTOMATIC MODE

    if (automatic == true && moveCar == true && pauseGame == false)
    {
        car1 = car1 + speed;
        car2 = car2 + speed;
        car3 = car3 + speed;
    }


    // Bring cars back when they leave the screen

    if (car1 > 100)
    {
        car1 = -100;
    }

    if (car2 > 100)
    {
        car2 = -100;
    }

    if (car3 > 100)
    {
        car3 = -100;
    }
}


// ================= TIMER =================

void timer(int value)
{
    moveCars();

    lightCount++;

    // RED → GREEN
    if (light == 0 && lightCount == 100)
    {
        light = 2;
        lightCount = 0;
    }

    // GREEN → YELLOW
    if (light == 2 && lightCount == 200)
    {
        light = 1;
        lightCount = 0;
    }

    // YELLOW → RED
    if (light == 1 && lightCount == 50)
    {
        light = 0;
        lightCount = 0;
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

            selectedCar = 1;

            moveCar = true;
            pauseGame = false;

            automatic = true;

            light = 0;
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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Horizontal road
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRectangle(-100, -25, 100, 25);
    // Vertical road
    drawRectangle(-25, -100, 25, 100);

    // Sidewalks

    glColor3f(0.7f, 0.7f, 0.7f);
    // Top-left
    drawRectangle(-100, 25, -25, 32);
    // Top-right
    drawRectangle(25, 25, 100, 32);
    // Bottom-left
    drawRectangle(-100, -32, -25, -25);
    // Bottom-right
    drawRectangle(25, -32, 100, -25);


    // LANE MARKINGS

    drawLaneMarking(-90, -1, -60, 1);
    drawLaneMarking(-50, -1, -20, 1);
    drawLaneMarking(20, -1, 50, 1);
    drawLaneMarking(60, -1, 90, 1);

    //vertical
    drawLaneMarking(-1, 60, 1, 90);
    drawLaneMarking(-1, 20, 1, 50);
    drawLaneMarking(-1, -50, 1, -20);
    drawLaneMarking(-1, -90, 1, -60);


    // ZEBRA CROSSINGS
    drawHorizontalCrosswalk(-12, 27);
    drawHorizontalCrosswalk(-12, -35);
    drawVerticalCrosswalk(27, -12);
    drawVerticalCrosswalk(-35, -12);

    // Traffic Light

    drawTrafficLight(30, 30);

    // ================= THREE CARS =================

    drawCar(car1, -10, 0.8f, 0.1f, 0.1f);   // Red car
    drawCar(car2, -10, 0.1f, 0.3f, 0.8f);   // Blue car
    drawCar(car3, 10, 0.1f, 0.7f, 0.2f);    // Green car

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

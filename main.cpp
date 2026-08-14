#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void drawRectangle(float left, float bottom, float right, float top)
{
    glBegin(GL_QUADS);

        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);

    glEnd();
}

void drawLaneMarking(float x1, float y1, float x2, float y2)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    drawRectangle(x1, y1, x2, y2);
}

void drawHorizontalCrosswalk(float startX, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 6; i++)
    {
        float x = startX + i * 4;

        drawRectangle(x, y, x + 2, y + 8);
    }
}

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

void drawTrafficLight(float x, float y)
{
    // Pole
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 1, y - 15, x + 1, y);

    // Traffic light box
    drawRectangle(x - 5, y, x + 5, y + 18);

    // Red
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(x, y + 14, 2.5f);

    // Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(x, y + 9, 2.5f);

    // Green
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCircle(x, y + 4, 2.5f);
}

void drawCar(float x, float y)
{
    // Body
    glColor3f(0.8f, 0.1f, 0.1f);

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

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'p':
        case 'P':
            // Pause/resume
            break;

        case 'r':
        case 'R':
            // Reset
            break;

        case 27:
            exit(0);
            break;
    }
}

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
    drawLaneMarking(-90, -2, -60, 2);
    drawLaneMarking(-50, -2, -20, 2);
    drawLaneMarking(20, -2, 50, 2);
    drawLaneMarking(60, -2, 90, 2);

    drawLaneMarking(-2, 60, 2, 90);
    drawLaneMarking(-2, 20, 2, 50);
    drawLaneMarking(-2, -50, 2, -20);
    drawLaneMarking(-2, -90, 2, -60);

    // ZEBRA CROSSINGS
    drawHorizontalCrosswalk(-12, 27);
    drawHorizontalCrosswalk(-12, -35);

    //TrafficLight
    drawTrafficLight(30, 30);

    //Car
    drawCar(-60, -10);
    drawCar(30, 10);

    glFlush();
}

void init()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(900, 700);

    glutCreateWindow("Team GoingMerry - Traffic Simulator");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

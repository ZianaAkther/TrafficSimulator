#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#include "DayNight.h"
#include "Environment.h"

float sunX = -90.0f;
float sunY = 90.0f;

float moonX = -90.0f;
float moonY = 90.0f;

bool nightMode = false;

void drawSun(float x, float y) {
    glColor3f(1.0f, 0.85f, 0.1f);
    drawCircle(x, y, 8.0f);
}

void drawMoon(float x, float y)
{
    // Moon
    glColor3f(0.9f, 0.9f, 0.75f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100;

        glVertex2f(
            x + cos(angle) * 8,
            y + sin(angle) * 8
        );
    }
    glEnd();

    // Moon shadow to create crescent
    glColor3f(0.08f, 0.12f, 0.25f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x + 4, y + 3);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100;

        glVertex2f(
            x + 4 + cos(angle) * 7,
            y + 3 + sin(angle) * 7
        );
    }

    glEnd();
}

void moveSun() {
    if (!nightMode) {
        sunX += 0.1f;
        if (sunX > 110.0f) sunX = -110.0f;
    }
}

void moveMoon()
{
    moonX += 0.1f;
    if (moonX > 90.0f)
    {
        moonX = -90.0f;
    }
}

void toggleNight() {
    nightMode = !nightMode;
}

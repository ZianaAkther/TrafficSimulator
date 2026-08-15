#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "DayNight.h"

float sunX = -90.0f;
float sunY = 90.0f;

bool nightMode = false;

float moonX = -90.0f;
float moonY = 90.0f;

void drawLakeRectangle(float left, float bottom, float right, float top)
{
    glBegin(GL_QUADS);

    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);

    glEnd();
}

void drawParkRectangle(float left, float bottom, float right, float top)
{
    glBegin(GL_QUADS);

    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);

    glEnd();
}

void drawParkTree(float x, float y)
{
    // Trunk
    glColor3f(0.35f, 0.20f, 0.08f);

    drawParkRectangle(
        x - 1,
        y,
        x + 1,
        y + 8
    );

    // Tree crown
    glColor3f(0.10f, 0.45f, 0.15f);

    glBegin(GL_POLYGON);

    glVertex2f(x, y + 20);
    glVertex2f(x + 5, y + 15);
    glVertex2f(x + 6, y + 10);
    glVertex2f(x, y + 8);
    glVertex2f(x - 6, y + 10);
    glVertex2f(x - 5, y + 15);

    glEnd();
}
void drawOfficeBuilding(float x, float y)
{
    // Main building
    glColor3f(0.45f, 0.48f, 0.55f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 24, y);
    glVertex2f(x + 24, y + 42);
    glVertex2f(x, y + 42);

    glEnd();


    // Roof / top section
    glColor3f(0.30f, 0.32f, 0.38f);

    glBegin(GL_QUADS);

    glVertex2f(x + 3, y + 42);
    glVertex2f(x + 21, y + 42);
    glVertex2f(x + 21, y + 46);
    glVertex2f(x + 3, y + 46);

    glEnd();


    // Windows
    glColor3f(0.20f, 0.35f, 0.45f);

    for (float wy = y + 5; wy <= y + 35; wy += 8)
    {
        // Left window
        glBegin(GL_QUADS);

        glVertex2f(x + 4, wy);
        glVertex2f(x + 9, wy);
        glVertex2f(x + 9, wy + 5);
        glVertex2f(x + 4, wy + 5);

        glEnd();


        // Right window
        glBegin(GL_QUADS);

        glVertex2f(x + 15, wy);
        glVertex2f(x + 20, wy);
        glVertex2f(x + 20, wy + 5);
        glVertex2f(x + 15, wy + 5);

        glEnd();
    }
}

void drawHouse(float x, float y)
{
    // House body
    glColor3f(0.75f, 0.55f, 0.35f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 25, y);
    glVertex2f(x + 25, y + 20);
    glVertex2f(x, y + 20);

    glEnd();


    // Roof
    glColor3f(0.45f, 0.15f, 0.12f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x - 2, y + 20);
    glVertex2f(x + 12.5f, y + 32);
    glVertex2f(x + 27, y + 20);

    glEnd();


    // Door
    glColor3f(0.25f, 0.15f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(x + 10, y);
    glVertex2f(x + 15, y);
    glVertex2f(x + 15, y + 12);
    glVertex2f(x + 10, y + 12);

    glEnd();


    // Windows
    glColor3f(0.2f, 0.55f, 0.75f);

    // Left window
    glBegin(GL_QUADS);

    glVertex2f(x + 3, y + 10);
    glVertex2f(x + 8, y + 10);
    glVertex2f(x + 8, y + 15);
    glVertex2f(x + 3, y + 15);

    glEnd();


    // Right window
    glBegin(GL_QUADS);

    glVertex2f(x + 17, y + 10);
    glVertex2f(x + 22, y + 10);
    glVertex2f(x + 22, y + 15);
    glVertex2f(x + 17, y + 15);

    glEnd();
}

void drawApartment(float x, float y)
{
    // Main building
    glColor3f(0.55f, 0.40f, 0.60f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 28, y);
    glVertex2f(x + 28, y + 32);
    glVertex2f(x, y + 32);

    glEnd();


    // Top roof
    glColor3f(0.30f, 0.25f, 0.35f);

    glBegin(GL_QUADS);

    glVertex2f(x - 2, y + 32);
    glVertex2f(x + 30, y + 32);
    glVertex2f(x + 30, y + 35);
    glVertex2f(x - 2, y + 35);

    glEnd();


    // Windows
    glColor3f(0.25f, 0.55f, 0.70f);

    for (float wy = y + 5; wy <= y + 25; wy += 7)
    {
        // Left windows
        glBegin(GL_QUADS);

        glVertex2f(x + 4, wy);
        glVertex2f(x + 9, wy);
        glVertex2f(x + 9, wy + 4);
        glVertex2f(x + 4, wy + 4);

        glEnd();


        // Middle windows
        glBegin(GL_QUADS);

        glVertex2f(x + 12, wy);
        glVertex2f(x + 17, wy);
        glVertex2f(x + 17, wy + 4);
        glVertex2f(x + 12, wy + 4);

        glEnd();


        // Right windows
        glBegin(GL_QUADS);

        glVertex2f(x + 20, wy);
        glVertex2f(x + 25, wy);
        glVertex2f(x + 25, wy + 4);
        glVertex2f(x + 20, wy + 4);

        glEnd();
    }
}

void drawShop(float x, float y)
{
    // Main shop
    glColor3f(0.65f, 0.50f, 0.30f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 22, y);
    glVertex2f(x + 22, y + 27);
    glVertex2f(x, y + 27);

    glEnd();


    // Roof
    glColor3f(0.30f, 0.20f, 0.15f);

    glBegin(GL_QUADS);

    glVertex2f(x - 2, y + 27);
    glVertex2f(x + 24, y + 27);
    glVertex2f(x + 22, y + 31);
    glVertex2f(x, y + 31);

    glEnd();


    // Large front window
    glColor3f(0.20f, 0.50f, 0.65f);

    glBegin(GL_QUADS);

    glVertex2f(x + 3, y + 12);
    glVertex2f(x + 11, y + 12);
    glVertex2f(x + 11, y + 22);
    glVertex2f(x + 3, y + 22);

    glEnd();

    // Door
    glColor3f(0.25f, 0.15f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(x + 14, y);
    glVertex2f(x + 19, y);
    glVertex2f(x + 19, y + 12);
    glVertex2f(x + 14, y + 12);

    glEnd();
}

void drawLake(float x, float y)
{
    // Main water
    glColor3f(0.10f, 0.45f, 0.70f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 75, y);
    glVertex2f(x + 75, y + 68);
    glVertex2f(x, y + 68);

    glEnd();


    // Water ripples
    glColor3f(0.20f, 0.60f, 0.80f);

   drawLakeRectangle(x + 8, y + 55, x + 25, y + 57);
    drawLakeRectangle(x + 38, y + 45, x + 60, y + 47);
    drawLakeRectangle(x + 15, y + 32, x + 35, y + 34);
    drawLakeRectangle(x + 45, y + 20, x + 68, y + 22);
    drawLakeRectangle(x + 10, y + 10, x + 28, y + 12);
    drawLakeRectangle(x + 50, y + 58, x + 70, y + 60);
}
void drawPark(float x, float y)
{
    // ================= PARK GROUND =================

    glColor3f(0.35f, 0.60f, 0.25f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 75, y);
    glVertex2f(x + 75, y + 68);
    glVertex2f(x, y + 68);

    glEnd();


    // ================= PARK PATH =================

    glColor3f(0.75f, 0.60f, 0.40f);

    glBegin(GL_QUADS);

    glVertex2f(x + 32, y);
    glVertex2f(x + 43, y);
    glVertex2f(x + 39, y + 68);
    glVertex2f(x + 28, y + 68);

    glEnd();


    // FLOWER BEDS

    glColor3f(0.90f, 0.80f, 0.20f);

    drawParkRectangle(x + 8, y + 8, x + 11, y + 11);
    drawParkRectangle(x + 60, y + 10, x + 63, y + 13);
    drawParkRectangle(x + 10, y + 50, x + 13, y + 53);
    drawParkRectangle(x + 62, y + 48, x + 65, y + 51);


    //BENCH 1

    glColor3f(0.35f, 0.18f, 0.08f);

    drawParkRectangle(x + 8, y + 25, x + 20, y + 28);

    // legs
    drawParkRectangle(x + 10, y + 22, x + 12, y + 25);
    drawParkRectangle(x + 17, y + 22, x + 19, y + 25);


    // BENCH 2

    drawParkRectangle(x + 55, y + 25, x + 67, y + 28);

    drawParkRectangle(x + 57, y + 22, x + 59, y + 25);
    drawParkRectangle(x + 64, y + 22, x + 66, y + 25);
}

void drawSchool(float x, float y)
{
    glColor3f(0.85f, 0.65f, 0.35f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + 35, y);
    glVertex2f(x + 35, y + 25);
    glVertex2f(x, y + 25);

    glEnd();


    //SCHOOL ROOF

    glColor3f(0.55f, 0.15f, 0.10f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x - 3, y + 25);
    glVertex2f(x + 17.5f, y + 38);
    glVertex2f(x + 38, y + 25);

    glEnd();


    //DOOR

    glColor3f(0.25f, 0.15f, 0.08f);

    drawParkRectangle(
        x + 14,
        y,
        x + 21,
        y + 14
    );


    // WINDOWS

    glColor3f(0.15f, 0.50f, 0.70f);

    // Left
    drawParkRectangle(
        x + 4,
        y + 12,
        x + 11,
        y + 19
    );

    // Right
    drawParkRectangle(
        x + 24,
        y + 12,
        x + 31,
        y + 19
    );


    // SCHOOL SIGN

    glColor3f(0.95f, 0.90f, 0.60f);

    drawParkRectangle(
        x + 11,
        y + 26,
        x + 24,
        y + 30
    );
}
void drawSun(float x, float y)
{
    // Sun
    glColor3f(1.0f, 0.85f, 0.1f);

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
}

void moveSun()
{
    sunX += 0.1f;

    if (sunX > 90.0f)
    {
        sunX = -90.0f;
    }
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

void toggleNight()
{
    nightMode = !nightMode;
}

void moveMoon()
{
    moonX += 0.1f;

    if (moonX > 90.0f)
    {
        moonX = -90.0f;
    }
}

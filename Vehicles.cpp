#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#include "Vehicles.h"
#include "Environment.h"


// =====================================================
// CAR
// =====================================================

void drawCar(float x, float y, float r, float g, float b)
{
    // Body
    glColor3f(r, g, b);

    drawRectangle(
        x,
        y,
        x + 12.0f,
        y + 6.0f
    );

    // Roof
    drawRectangle(
        x + 3.0f,
        y + 6.0f,
        x + 9.0f,
        y + 10.0f
    );


    // Windows
    glColor3f(0.2f, 0.6f, 0.8f);

    drawRectangle(
        x + 4.0f,
        y + 7.0f,
        x + 6.0f,
        y + 9.0f
    );

    drawRectangle(
        x + 6.5f,
        y + 7.0f,
        x + 8.0f,
        y + 9.0f
    );


    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);

    drawCircle(
        x + 3.0f,
        y,
        1.5f
    );

    drawCircle(
        x + 9.0f,
        y,
        1.5f
    );
}


// =====================================================
// BUS
// =====================================================

void drawBus(float x, float y)
{
    // Main body
    glColor3f(0.05f, 0.05f, 0.05f);

    drawRectangle(
        x,
        y,
        x + 8.0f,
        y + 18.0f
    );


    // Red upper part
    glColor3f(0.8f, 0.0f, 0.0f);

    drawRectangle(
        x,
        y + 13.0f,
        x + 8.0f,
        y + 18.0f
    );


    // Windows
    glColor3f(0.2f, 0.6f, 0.8f);

    drawRectangle(
        x + 1.0f,
        y + 9.0f,
        x + 7.0f,
        y + 12.0f
    );

    drawRectangle(
        x + 1.0f,
        y + 5.0f,
        x + 7.0f,
        y + 8.0f
    );


    // Wheels
    glColor3f(0.02f, 0.02f, 0.02f);

    drawCircle(
        x + 1.0f,
        y + 2.0f,
        1.3f
    );

    drawCircle(
        x + 7.0f,
        y + 2.0f,
        1.3f
    );
}


// =====================================================
// MICROBUS
// =====================================================

void drawMicrobus(float x, float y)
{
    // Body
    glColor3f(0.85f, 0.65f, 0.1f);

    drawRectangle(
        x,
        y,
        x + 8.0f,
        y + 12.0f
    );


    // Top
    glColor3f(0.9f, 0.75f, 0.2f);

    drawRectangle(
        x + 1.0f,
        y + 12.0f,
        x + 7.0f,
        y + 14.0f
    );


    // Front window
    glColor3f(0.2f, 0.6f, 0.8f);

    drawRectangle(
        x + 1.0f,
        y + 8.0f,
        x + 7.0f,
        y + 11.0f
    );


    // Lower window
    drawRectangle(
        x + 1.0f,
        y + 4.0f,
        x + 7.0f,
        y + 7.0f
    );


    // Wheels
    glColor3f(0.02f, 0.02f, 0.02f);

    drawCircle(
        x + 1.0f,
        y + 2.0f,
        1.2f
    );

    drawCircle(
        x + 7.0f,
        y + 2.0f,
        1.2f
    );
}


// =====================================================
// AMBULANCE
// =====================================================

void drawAmbulance(float x, float y)
{
    // =================================================
    // MAIN BODY
    // =================================================

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

        glVertex2f(x, y);
        glVertex2f(x + 18.0f, y);
        glVertex2f(x + 18.0f, y + 8.0f);
        glVertex2f(x, y + 8.0f);

    glEnd();


    // =================================================
    // TOP
    // =================================================

    glBegin(GL_QUADS);

        glVertex2f(x + 4.0f, y + 8.0f);
        glVertex2f(x + 14.0f, y + 8.0f);
        glVertex2f(x + 12.0f, y + 13.0f);
        glVertex2f(x + 5.0f, y + 13.0f);

    glEnd();


    // =================================================
    // RED STRIPE
    // =================================================

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

        glVertex2f(x, y + 3.0f);
        glVertex2f(x + 18.0f, y + 3.0f);
        glVertex2f(x + 18.0f, y + 4.5f);
        glVertex2f(x, y + 4.5f);

    glEnd();


    // =================================================
    // WINDOWS
    // =================================================

    glColor3f(0.2f, 0.6f, 0.8f);


    // Front window
    glBegin(GL_QUADS);

        glVertex2f(x + 5.0f, y + 9.0f);
        glVertex2f(x + 8.0f, y + 9.0f);
        glVertex2f(x + 8.0f, y + 12.0f);
        glVertex2f(x + 5.5f, y + 12.0f);

    glEnd();


    // Back window
    glBegin(GL_QUADS);

        glVertex2f(x + 8.5f, y + 9.0f);
        glVertex2f(x + 12.5f, y + 9.0f);
        glVertex2f(x + 11.5f, y + 12.0f);
        glVertex2f(x + 8.5f, y + 12.0f);

    glEnd();


    // =================================================
    // RED CROSS - VERTICAL
    // =================================================

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

        glVertex2f(x + 13.0f, y + 2.0f);
        glVertex2f(x + 14.0f, y + 2.0f);
        glVertex2f(x + 14.0f, y + 6.0f);
        glVertex2f(x + 13.0f, y + 6.0f);

    glEnd();


    // =================================================
    // RED CROSS - HORIZONTAL
    // =================================================

    glBegin(GL_QUADS);

        glVertex2f(x + 11.5f, y + 3.5f);
        glVertex2f(x + 15.5f, y + 3.5f);
        glVertex2f(x + 15.5f, y + 4.5f);
        glVertex2f(x + 11.5f, y + 4.5f);

    glEnd();


    // =================================================
    // WHEELS
    // =================================================

    glColor3f(0.03f, 0.03f, 0.03f);


    // Wheel 1
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x + 4.0f, y);

        for (int i = 0; i <= 30; i++)
        {
            float angle =
                2.0f * 3.14159f * i / 30.0f;

            glVertex2f(
                x + 4.0f + cos(angle) * 1.7f,
                y + sin(angle) * 1.7f
            );
        }

    glEnd();


    // Wheel 2
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x + 14.0f, y);

        for (int i = 0; i <= 30; i++)
        {
            float angle =
                2.0f * 3.14159f * i / 30.0f;

            glVertex2f(
                x + 14.0f + cos(angle) * 1.7f,
                y + sin(angle) * 1.7f
            );
        }

    glEnd();


    // =================================================
    // EMERGENCY LIGHT
    // =================================================

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

        glVertex2f(x + 7.0f, y + 13.0f);
        glVertex2f(x + 10.0f, y + 13.0f);
        glVertex2f(x + 10.0f, y + 14.0f);
        glVertex2f(x + 7.0f, y + 14.0f);

    glEnd();
}


// =====================================================
// BOAT
// =====================================================

void drawBoat(float x, float y)
{
    // =================================================
    // BOAT HULL
    // =================================================

    glColor3f(0.45f, 0.20f, 0.05f);

    glBegin(GL_POLYGON);

        glVertex2f(x, y);
        glVertex2f(x + 18.0f, y);
        glVertex2f(x + 14.0f, y - 5.0f);
        glVertex2f(x + 4.0f, y - 5.0f);

    glEnd();


    // =================================================
    // UPPER PART
    // =================================================

    glColor3f(0.9f, 0.9f, 0.9f);

    drawRectangle(
        x + 5.0f,
        y,
        x + 13.0f,
        y + 3.0f
    );


    // =================================================
    // MAST
    // =================================================

    glColor3f(0.3f, 0.2f, 0.1f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);

        glVertex2f(x + 9.0f, y + 3.0f);
        glVertex2f(x + 9.0f, y + 15.0f);

    glEnd();


    // =================================================
    // SAIL
    // =================================================

    glColor3f(1.0f, 0.8f, 0.2f);

    glBegin(GL_TRIANGLES);

        glVertex2f(x + 9.0f, y + 14.0f);
        glVertex2f(x + 9.0f, y + 4.0f);
        glVertex2f(x + 17.0f, y + 4.0f);

    glEnd();
}

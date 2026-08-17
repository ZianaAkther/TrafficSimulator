#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "emergency.h"

bool emergency = false;
float emergencyX = -100;

void drawAmbulance(float x, float y)
{
    // ================= MAIN BODY =================

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

        glVertex2f(x, y);
        glVertex2f(x + 18, y);
        glVertex2f(x + 18, y + 8);
        glVertex2f(x, y + 8);

    glEnd();
    // ================= TOP =================
    glBegin(GL_QUADS);

        glVertex2f(x + 4, y + 8);
        glVertex2f(x + 14, y + 8);
        glVertex2f(x + 12, y + 13);
        glVertex2f(x + 5, y + 13);

    glEnd();
    // ================= RED STRIPE =================
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

        glVertex2f(x, y + 3);
        glVertex2f(x + 18, y + 3);
        glVertex2f(x + 18, y + 4.5f);
        glVertex2f(x, y + 4.5f);

    glEnd();
    // ================= WINDOWS =================
    glColor3f(0.2f, 0.6f, 0.8f);

    // Front window

    glBegin(GL_QUADS);

        glVertex2f(x + 5, y + 9);
        glVertex2f(x + 8, y + 9);
        glVertex2f(x + 8, y + 12);
        glVertex2f(x + 5.5f, y + 12);

    glEnd();
    // Back window

    glBegin(GL_QUADS);

        glVertex2f(x + 8.5f, y + 9);
        glVertex2f(x + 12.5f, y + 9);
        glVertex2f(x + 11.5f, y + 12);
        glVertex2f(x + 8.5f, y + 12);

    glEnd();
    // ================= RED CROSS =================

    glColor3f(1.0f, 0.0f, 0.0f);

    // Vertical part

    glBegin(GL_QUADS);

        glVertex2f(x + 13, y + 2);
        glVertex2f(x + 14, y + 2);
        glVertex2f(x + 14, y + 6);
        glVertex2f(x + 13, y + 6);

    glEnd();
    // Horizontal part

    glBegin(GL_QUADS);

        glVertex2f(x + 11.5f, y + 3.5f);
        glVertex2f(x + 15.5f, y + 3.5f);
        glVertex2f(x + 15.5f, y + 4.5f);
        glVertex2f(x + 11.5f, y + 4.5f);

    glEnd();
    // ================= WHEELS =================

    glColor3f(0.03f, 0.03f, 0.03f);

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x + 4, y);

        for (int i = 0; i <= 30; i++)
        {
            float angle = 2.0f * 3.14159f * i / 30;

            glVertex2f(
                x + 4 + cos(angle) * 1.7f,
                y + sin(angle) * 1.7f
            );
        }

    glEnd();
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x + 14, y);

        for (int i = 0; i <= 30; i++)
        {
            float angle = 2.0f * 3.14159f * i / 30;

            glVertex2f(
                x + 14 + cos(angle) * 1.7f,
                y + sin(angle) * 1.7f
            );
        }

    glEnd();
    // ================= EMERGENCY LIGHT =================

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

        glVertex2f(x + 7, y + 13);
        glVertex2f(x + 10, y + 13);
        glVertex2f(x + 10, y + 14);
        glVertex2f(x + 7, y + 14);

    glEnd();
}

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

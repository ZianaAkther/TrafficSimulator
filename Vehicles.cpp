#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#include "Vehicles.h"
#include "Environment.h"  // Provides primitive drawing functions like drawRectangle and drawCircle

void drawCar(float x, float y, float r, float g, float b) {
    // Body & Roof
    glColor3f(r, g, b);
    drawRectangle(x, y, x + 12.0f, y + 6.0f);
    drawRectangle(x + 3.0f, y + 6.0f, x + 9.0f, y + 10.0f);

    // Windows
    glColor3f(0.2f, 0.6f, 0.8f);
    drawRectangle(x + 4.0f, y + 7.0f, x + 6.0f, y + 9.0f);
    drawRectangle(x + 6.5f, y + 7.0f, x + 8.0f, y + 9.0f);

    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);
    drawCircle(x + 3.0f, y, 1.5f);
    drawCircle(x + 9.0f, y, 1.5f);
}

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

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "Environment.h"

void drawRectangle(float left, float bottom, float right, float top) {
    glBegin(GL_QUADS);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
    glEnd();
}

void drawCircle(float cx, float cy, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100.0f;
        glVertex2f(cx + cos(angle) * radius, cy + sin(angle) * radius);
    }
    glEnd();
}

void drawLaneMarking(float x1, float y1, float x2, float y2) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(x1, y1, x2, y2);
}

void drawHorizontalCrosswalk(float startX, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 6; i++) {
        float x = startX + i * 4.0f;
        drawRectangle(x, y, x + 2.0f, y + 8.0f);
    }
}

void drawVerticalCrosswalk(float x, float startY) {
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 6; i++) {
        float y = startY + i * 4.0f;
        drawRectangle(x, y, x + 8.0f, y + 2.0f);
    }
}

// --- DETAILED BUILDINGS & LAKE ---

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

void drawHouse(float x, float y) {
    // Base Wall
    glColor3f(0.8f, 0.5f, 0.3f);
    drawRectangle(x, y, x + 20.0f, y + 20.0f);

    // Triangular Roof
    glColor3f(0.6f, 0.15f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 2.0f, y + 20.0f);
        glVertex2f(x + 22.0f, y + 20.0f);
        glVertex2f(x + 10.0f, y + 32.0f);
    glEnd();

    // Door & Window
    glColor3f(0.3f, 0.2f, 0.1f);
    drawRectangle(x + 8.0f, y, x + 12.0f, y + 8.0f); // Door

    glColor3f(0.9f, 0.9f, 0.6f);
    drawRectangle(x + 3.0f, y + 10.0f, x + 7.0f, y + 14.0f); // Window
    drawRectangle(x + 13.0f, y + 10.0f, x + 17.0f, y + 14.0f);
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

void drawShop(float x, float y) {
    // Body
    glColor3f(0.9f, 0.7f, 0.2f);
    drawRectangle(x, y, x + 25.0f, y + 20.0f);

    // Red Awning Striped Roof
    glColor3f(0.8f, 0.1f, 0.1f);
    drawRectangle(x - 1.0f, y + 18.0f, x + 26.0f, y + 23.0f);

    // Display Window & Entrance
    glColor3f(0.2f, 0.7f, 0.9f);
    drawRectangle(x + 2.0f, y + 4.0f, x + 12.0f, y + 14.0f);

    glColor3f(0.4f, 0.2f, 0.1f);
    drawRectangle(x + 16.0f, y, x + 22.0f, y + 14.0f);
}

//Park and School
void drawParkRectangle(float left, float bottom, float right, float top) {
    glBegin(GL_QUADS);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
    glEnd();
}

void drawParkTree(float x, float y) {
    // Trunk
    glColor3f(0.35f, 0.20f, 0.08f);
    drawParkRectangle(x - 1.0f, y, x + 1.0f, y + 8.0f);

    // Tree Crown
    glColor3f(0.10f, 0.45f, 0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(x, y + 20.0f);
        glVertex2f(x + 5.0f, y + 15.0f);
        glVertex2f(x + 6.0f, y + 10.0f);
        glVertex2f(x, y + 8.0f);
        glVertex2f(x - 6.0f, y + 10.0f);
        glVertex2f(x - 5.0f, y + 15.0f);
    glEnd();
}

void drawPark(float x, float y) {
    // Ground
    glColor3f(0.35f, 0.60f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 75.0f, y);
        glVertex2f(x + 75.0f, y + 68.0f);
        glVertex2f(x, y + 68.0f);
    glEnd();

    // Path
    glColor3f(0.75f, 0.60f, 0.40f);
    glBegin(GL_QUADS);
        glVertex2f(x + 32.0f, y);
        glVertex2f(x + 43.0f, y);
        glVertex2f(x + 39.0f, y + 68.0f);
        glVertex2f(x + 28.0f, y + 68.0f);
    glEnd();

    // Flower Beds
    glColor3f(0.90f, 0.80f, 0.20f);
    drawParkRectangle(x + 8.0f, y + 8.0f, x + 11.0f, y + 11.0f);
    drawParkRectangle(x + 60.0f, y + 10.0f, x + 63.0f, y + 13.0f);
    drawParkRectangle(x + 10.0f, y + 50.0f, x + 13.0f, y + 53.0f);
    drawParkRectangle(x + 62.0f, y + 48.0f, x + 65.0f, y + 51.0f);

    // Bench 1
    glColor3f(0.35f, 0.18f, 0.08f);
    drawParkRectangle(x + 8.0f, y + 25.0f, x + 20.0f, y + 28.0f);
    drawParkRectangle(x + 10.0f, y + 22.0f, x + 12.0f, y + 25.0f);
    drawParkRectangle(x + 17.0f, y + 22.0f, x + 19.0f, y + 25.0f);

    // Bench 2
    drawParkRectangle(x + 55.0f, y + 25.0f, x + 67.0f, y + 28.0f);
    drawParkRectangle(x + 57.0f, y + 22.0f, x + 59.0f, y + 25.0f);
    drawParkRectangle(x + 64.0f, y + 22.0f, x + 66.0f, y + 25.0f);
}

void drawSchool(float x, float y) {
    // School Structure
    glColor3f(0.85f, 0.65f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 35.0f, y);
        glVertex2f(x + 35.0f, y + 25.0f);
        glVertex2f(x, y + 25.0f);
    glEnd();

    // Roof
    glColor3f(0.55f, 0.15f, 0.10f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 3.0f, y + 25.0f);
        glVertex2f(x + 17.5f, y + 38.0f);
        glVertex2f(x + 38.0f, y + 25.0f);
    glEnd();

    // Door
    glColor3f(0.25f, 0.15f, 0.08f);
    drawParkRectangle(x + 14.0f, y, x + 21.0f, y + 14.0f);

    // Windows
    glColor3f(0.15f, 0.50f, 0.70f);
    drawParkRectangle(x + 4.0f, y + 12.0f, x + 11.0f, y + 19.0f);
    drawParkRectangle(x + 24.0f, y + 12.0f, x + 31.0f, y + 19.0f);

    // Sign
    glColor3f(0.95f, 0.90f, 0.60f);
    drawParkRectangle(x + 11.0f, y + 26.0f, x + 24.0f, y + 30.0f);
}

void drawLakeWithWaves(float x1, float y1, float x2, float y2) {
    // Lake Water Base
    glColor3f(0.1f, 0.45f, 0.85f);
    drawRectangle(x1, y1, x2, y2);

    // Wave Line Ripples
    glColor3f(0.3f, 0.65f, 0.98f);
    glLineWidth(2.0f);
    for (float wy = y1 + 8.0f; wy < y2 - 5.0f; wy += 12.0f) {
        for (float wx = x1 + 5.0f; wx < x2 - 15.0f; wx += 22.0f) {
            glBegin(GL_LINE_STRIP);
                glVertex2f(wx, wy);
                glVertex2f(wx + 4.0f, wy + 2.0f);
                glVertex2f(wx + 8.0f, wy);
                glVertex2f(wx + 12.0f, wy + 2.0f);
            glEnd();
        }
    }
}

void drawStaticEnvironment() {

    // 1. Base Park Area
    drawPark(-100.0f, -100.0f);

    // 2. School Building placed neatly inside the park quadrant
    drawSchool(-80,-80);

    // 3. Trees in Park
    drawParkTree(-85.0f, -50.0f);
    drawParkTree(-40.0f, -50.0f);

    // Lake with Waves
    drawLakeWithWaves(25.0f, -100.0f, 100.0f, -25.0f);

    // Main Roads
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRectangle(-100.0f, -25.0f, 100.0f, 25.0f);
    drawRectangle(-25.0f, -100.0f, 25.0f, 100.0f);

    // Sidewalks
    glColor3f(0.7f, 0.7f, 0.7f);
    drawRectangle(-100.0f, 25.0f, -25.0f, 32.0f);
    drawRectangle(25.0f, 25.0f, 100.0f, 32.0f);
    drawRectangle(-100.0f, -32.0f, -25.0f, -25.0f);
    drawRectangle(25.0f, -32.0f, 100.0f, -25.0f);

    // Detailed Scenery Buildings
    drawOfficeBuilding(-90.0f, 32.0f);
    drawHouse(-60.0f, 32.0f);
    drawApartment(35.0f, 32.0f);
    drawShop(70.0f, 32.0f);

    // Dash Lane Markings
    drawLaneMarking(-90.0f, -0.5f, -60.0f, 0.5f);
    drawLaneMarking(-50.0f, -0.5f, -20.0f, 0.5f);
    drawLaneMarking(20.0f, -0.5f, 50.0f, 0.5f);
    drawLaneMarking(60.0f, -0.5f, 90.0f, 0.5f);

    drawLaneMarking(-0.5f, 60.0f, 0.5f, 90.0f);
    drawLaneMarking(-0.5f, 20.0f, 0.5f, 50.0f);
    drawLaneMarking(-0.5f, -50.0f, 0.5f, -20.0f);
    drawLaneMarking(-0.5f, -90.0f, 0.5f, -60.0f);

    // Crosswalks
    drawHorizontalCrosswalk(-12.0f, 27.0f);
    drawHorizontalCrosswalk(-12.0f, -35.0f);
    drawVerticalCrosswalk(27.0f, -12.0f);
    drawVerticalCrosswalk(-35.0f, -12.0f);
}

void drawTrafficLight(float x, float y, int currentLight) {
    // Pole Base on Sidewalk
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 1.0f, y - 10.0f, x + 1.0f, y);
    drawRectangle(x - 4.0f, y, x + 4.0f, y + 16.0f);

    // Red Light
    if (currentLight == 0) glColor3f(1.0f, 0.0f, 0.0f);
    else glColor3f(0.3f, 0.0f, 0.0f);
    drawCircle(x, y + 12.5f, 2.0f);

    // Yellow Light
    if (currentLight == 1) glColor3f(1.0f, 1.0f, 0.0f);
    else glColor3f(0.3f, 0.3f, 0.0f);
    drawCircle(x, y + 8.0f, 2.0f);

    // Green Light
    if (currentLight == 2) glColor3f(0.0f, 1.0f, 0.0f);
    else glColor3f(0.0f, 0.3f, 0.0f);
    drawCircle(x, y + 3.5f, 2.0f);
}

#include <windows.h>
#include <GL/glut.h>
#include<math.h>

#include "emergency.h"
#include "Vehicles.h"
#include "Environment.h"  // Provides primitive drawing functions like drawRectangle and drawCircle

// Global variables defined in main.cpp
extern float car1, car1Y, car2, car2Y, car3;
extern float busY, microbusY;
extern float boat1X, boat1Y, boat2X, boat2Y;
extern bool boat1MovingRight;
extern bool boat2MovingRight;

extern bool pauseGame;
extern int light, verticalLight;

// Helper: Circular distance along a wrap-around track [-110, 110] (Width = 220)
float getForwardDistance(float fromX, float toX) {
    float dist = toX - fromX;
    if (dist < 0.0f) dist += 220.0f;
    return dist;
}

//Drawing Functions
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

//drawBus
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
// AMBULANCE
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
// BOAT
void drawBoat(float x, float y)
{
    // BOAT HULL

    glColor3f(0.45f, 0.20f, 0.05f);

    glBegin(GL_POLYGON);

        glVertex2f(x, y);
        glVertex2f(x + 18.0f, y);
        glVertex2f(x + 14.0f, y - 5.0f);
        glVertex2f(x + 4.0f, y - 5.0f);

    glEnd();

    // UPPER PART

    glColor3f(0.9f, 0.9f, 0.9f);

    drawRectangle(
        x + 5.0f,
        y,
        x + 13.0f,
        y + 3.0f
    );

    // MAST
    glColor3f(0.3f, 0.2f, 0.1f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);

        glVertex2f(x + 9.0f, y + 3.0f);
        glVertex2f(x + 9.0f, y + 15.0f);

    glEnd();

    // SAIL

    glColor3f(1.0f, 0.8f, 0.2f);

    glBegin(GL_TRIANGLES);

        glVertex2f(x + 9.0f, y + 14.0f);
        glVertex2f(x + 9.0f, y + 4.0f);
        glVertex2f(x + 17.0f, y + 4.0f);

    glEnd();
}

//Vehicles Simulation

// Vehicle Movement Helper
bool canCrossStopLine(float currentPos, float newPos, float stopLine, bool isPositive) {
    if (isPositive) {
        if (currentPos < stopLine && newPos >= stopLine) return false;
    } else {
        if (currentPos > stopLine && newPos <= stopLine) return false;
    }
    return true;
}

void moveHorizontalCars() {
    if (pauseGame) return;

    float minGap = 24.0f;

    // --- EMERGENCY LOGIC ---
    if (emergency) {
        // Smoothly pull over to shoulder
        if (car1Y > -20.0f) car1Y -= 0.2f;
        if (car2Y > -20.0f) car2Y -= 0.2f;

        float accelSpeed = 1.0f; // Fast clearance speed

        // Lead car (car2): Accelerate if past stop line (-37.0) and inside intersection
        if (car2 > -37.0f && car2 < 35.0f) {
            car2 += accelSpeed;
        }

        // Follower car (car1): Accelerate through intersection while enforcing gap
        float dist12 = getForwardDistance(car1, car2);
        if (car1 > -37.0f && car1 < 35.0f && dist12 >= minGap) {
            car1 += accelSpeed;
        }

        // Opposite car (car3): Accelerate to clear going left
        if (car3 < 25.0f && car3 > -45.0f) {
            car3 -= accelSpeed;
        }

        return; // Pause forward motion once cleared
    } else {
        // Return cars back to normal lane (y = -10.0)
        if (car1Y < -10.0f) car1Y += 0.2f;
        if (car2Y < -10.0f) car2Y += 0.2f;
    }

    // --- NORMAL HORIZONTAL CAR MOVEMENT ---
    float speed = (light == 1) ? 0.2f : 0.5f;

    // Dynamic forward distances regardless of screen wrap-around
    float dist12 = getForwardDistance(car1, car2);
    float dist21 = getForwardDistance(car2, car1);

    // Move Car 2
    float newX2 = car2 + speed;
    if ((light == 2 || canCrossStopLine(car2, newX2, -37.0f, true)) && dist21 >= minGap) {
        car2 = newX2;
    }

    // Move Car 1
    float newX1 = car1 + speed;
    if ((light == 2 || canCrossStopLine(car1, newX1, -37.0f, true)) && dist12 >= minGap) {
        car1 = newX1;
    }

    // Move Car 3
    float newX3 = car3 - speed;
    if (light == 2 || canCrossStopLine(car3, newX3, 25.0f, false)) {
        car3 = newX3;
    }

    // Screen Wrap Around
    if (car2 > 110.0f) car2 = -110.0f;
    if (car1 > 110.0f) car1 = -110.0f;
    if (car3 < -110.0f) car3 = 110.0f;
}

void moveVerticalVehicles() {
    if (pauseGame) return;

    // --- EMERGENCY LOGIC ---
    if (emergency) {
        float accelSpeed = 1.0f;

        // Bus (moving down): height is 18, so fully clears when busY <= -45.0
        if (busY <= 40.0f && busY > -45.0f) {
            busY -= accelSpeed;
        }

        // Microbus (moving up): height is 14, clears when microbusY >= 28.0
        if (microbusY >= -44.0f && microbusY < 28.0f) {
            microbusY += accelSpeed;
        }

        return; // Halt behind stop lines
    }

    // --- NORMAL VERTICAL MOVEMENT ---
    float speed = (verticalLight == 1) ? 0.2f : 0.5f;

    float newBusY = busY - speed;
    if (verticalLight == 2 || canCrossStopLine(busY, newBusY, 40.0f, false)) {
        busY = newBusY;
    }

    float newMicrobusY = microbusY + speed;
    if (verticalLight == 2 || canCrossStopLine(microbusY, newMicrobusY, -44.0f, true)) {
        microbusY = newMicrobusY;
    }

    if (busY < -110.0f) busY = 110.0f;
    if (microbusY > 110.0f) microbusY = -110.0f;
}

void moveBoats() {
    if (pauseGame) return;

    // Boat 1 Movement (Bounds: 28.0 to 78.0)
    if (boat1MovingRight) {
        boat1X += 0.15f;
        if (boat1X >= 78.0f) {
            boat1MovingRight = false; // Turn around to go left
        }
    } else {
        boat1X -= 0.15f;
        if (boat1X <= 28.0f) {
            boat1MovingRight = true;  // Turn around to go right
        }
    }

    // Boat 2 Movement (Bounds: 52.0 to 95.0)
    if (boat2MovingRight) {
        boat2X += 0.15f;
        if (boat2X >= 95.0f) {
            boat2MovingRight = false; // Turn around to go left
        }
    } else {
        boat2X -= 0.15f;
        if (boat2X <= 52.0f) {
            boat2MovingRight = true;  // Turn around to go right
        }
    }
}


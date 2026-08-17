//environment.cpp
#include <windows.h>
#include <GL/glut.h>
#include "Environment.h"
#include <math.h>

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

//Simulation starts here
// ============================================================
// CHECK HORIZONTAL CAR SPACING
// ============================================================
bool horizontalCarHasSpace(float newX, int currentCar)
{
    float gap = 16.0f;

    if (currentCar == 1)
    {
        if (car2 > newX && (car2 - newX )< gap) //car2 ahead of car1
            return false;
    }

    else if (currentCar == 2)
    {
        if (car1 > newX && (car1 - newX) < gap) // Car 1 is ahead of Car 2
            return false;
    }

    return true;
}

bool vehiclesOverlap(
    float x1, float y1, float width1, float height1,
    float x2, float y2, float width2, float height2)
{
    return (x1 < x2 + width2 &&
            x1 + width1 > x2 &&
            y1 < y2 + height2 &&
            y1 + height1 > y2);
}
bool horizontalVehicleHasClearPath(float newX, float carY)
{
    // Check against BUS
    if (vehiclesOverlap(
            newX, carY, 12.0f, 10.0f,
            -18.0f, busY, 8.0f, 18.0f))
    {
        return false;
    }

    // Check against MICROBUS
    if (vehiclesOverlap(
            newX, carY, 12.0f, 10.0f,
            5.0f, microbusY, 8.0f, 14.0f))
    {
        return false;
    }

    return true;
}

// Generic stop line check for both horizontal and vertical vehicles
bool canCrossStopLineGeneric(float currentPos, float newPos, float stopLine, bool isPositiveDirection)
{
    if (isPositiveDirection) {
        // Vehicle moving in positive direction (right or upward)
        if (currentPos < stopLine && newPos >= stopLine)
            return false;
    } else {
        // Vehicle moving in negative direction (left or downward)
        if (currentPos > stopLine && newPos <= stopLine)
            return false;
    }
    return true;
}

// ============================================================
// MOVE HORIZONTAL CARS
// ============================================================

void resetCar(float &carX)
{
    if (carX > 105)
        carX = -105;
}

void moveHorizontalCars()
{
    if (automatic == false ||
        moveCar == false ||
        pauseGame == true)
    {
        return;
    }

    float normalSpeed = 0.5f;
    float yellowSpeed = 0.2f;
    float stopLine = -37.0f;// Stop line

    // ========================================================
    // EMERGENCY MODE
    // ========================================================
    if (emergency == true)
    {
        float emergencyTrafficSpeed = 0.25f;

        // Car 1
        float newCar1 = car1 + emergencyTrafficSpeed;

        if (horizontalCarHasSpace(newCar1, 1))
            car1 = newCar1;

        // Car 2
        float newCar2 = car2 + emergencyTrafficSpeed;

        if (horizontalCarHasSpace(newCar2, 2))
            car2 = newCar2;

        resetCar(car1);
        resetCar(car2);

        return;
    }

    // ========================================================
    // NORMAL TRAFFIC
    // ========================================================

    float speed = (light == 1) ? yellowSpeed : normalSpeed;

    // ========================================================
    // CAR 1
    // ========================================================

    float newX1 = car1 + speed;

    bool car1CanMove =
        (light == 2) ||
        canCrossStopLineGeneric(car1, newX1, stopLine, true);

    if (car1CanMove && horizontalCarHasSpace(newX1, 1)&&
    horizontalVehicleHasClearPath(newX1, -10))
        car1 = newX1;

    // ---------------- CAR 2 ----------------
    float newX2 = car2 + speed;

    bool car2CanMove =
        (light == 2) ||
        canCrossStopLineGeneric(car2, newX2, stopLine, true);

    if (car2CanMove && horizontalCarHasSpace(newX2, 2) &&
        horizontalVehicleHasClearPath(newX2, -10))
        car2 = newX2;

    resetCar(car1);
    resetCar(car2);
}

// ============================================================
// MOVE VERTICAL VEHICLES
// ============================================================

// Helper function for resetting vertical vehicles
void resetVerticalVehicle(float &vehicleY, float limit, float resetValue, bool isUpward)
{
    if (isUpward) {
        if (vehicleY > limit)
            vehicleY = resetValue;
    } else {
        if (vehicleY < limit)
            vehicleY = resetValue;
    }
}

void moveVerticalVehicles()
{
    if (automatic == false ||
        moveCar == false ||
        pauseGame == true)
    {
        return;
    }

    const float normalSpeed = 0.5f;
    const float yellowSpeed = 0.2f;

    // Green = normal speed
    // Yellow = slow speed
    float speed = (verticalLight == 1)
                    ? yellowSpeed
                    : normalSpeed;

    // ========================================================
    // BUS MOVES UP
    // ========================================================

    float newBusY = busY + speed;

    bool busCanMove = true;

    // RED LIGHT
    if (verticalLight == 0)
    {
        busCanMove =
            canCrossStopLineGeneric(
                busY,
                newBusY,
                -44.0f,
                true
            );
    }

    if (busCanMove)
    {
        busY = newBusY;
    }

    // ========================================================
    // MICROBUS MOVES DOWN
    // ========================================================

    float newMicrobusY = microbusY - speed;

    bool microbusCanMove = true;

    // RED LIGHT
    if (verticalLight == 0)
    {
        microbusCanMove =
            canCrossStopLineGeneric(
                microbusY,
                newMicrobusY,
                40.0f,
                false
            );
    }

    if (microbusCanMove)
    {
        microbusY = newMicrobusY;
    }

    // ========================================================
    // RESET
    // ========================================================

    resetVerticalVehicle(
        busY,
        110,
        -110,
        true
    );

    resetVerticalVehicle(
        microbusY,
        -110,
        110,
        false
    );
}

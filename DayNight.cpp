#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <ctime>

#include "DayNight.h"
#include "Environment.h"

// ============================================================
// SUN
// ============================================================

float sunX = -90.0f;
float sunY = 90.0f;


// ============================================================
// MOON
// ============================================================

float moonX = -90.0f;
float moonY = 90.0f;


// ============================================================
// DAY / NIGHT
// ============================================================

bool nightMode = false;


// ============================================================
// RAIN
// ============================================================

bool rain = false;

const int MAX_RAINDROPS = 180;

float rainX[MAX_RAINDROPS];
float rainY[MAX_RAINDROPS];


// ============================================================
// SUN
// ============================================================

void drawSun(float x, float y)
{
    glColor3f(
        1.0f,
        0.85f,
        0.1f
    );

    drawCircle(
        x,
        y,
        8.0f
    );
}


// ============================================================
// MOON
// ============================================================

void drawMoon(float x, float y)
{
    // Moon
    glColor3f(
        0.9f,
        0.9f,
        0.75f
    );

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= 100; i++)
    {
        float angle =
            2.0f * 3.14159f * i / 100.0f;

        glVertex2f(
            x + cos(angle) * 8.0f,
            y + sin(angle) * 8.0f
        );
    }

    glEnd();


    // Moon shadow to create crescent
    glColor3f(
        0.08f,
        0.12f,
        0.25f
    );

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(
        x + 4.0f,
        y + 3.0f
    );

    for (int i = 0; i <= 100; i++)
    {
        float angle =
            2.0f * 3.14159f * i / 100.0f;

        glVertex2f(
            x + 4.0f + cos(angle) * 7.0f,
            y + 3.0f + sin(angle) * 7.0f
        );
    }

    glEnd();
}


// ============================================================
// SUN MOVEMENT
// ============================================================

void moveSun()
{
    if (!nightMode)
    {
        sunX += 0.1f;

        if (sunX > 110.0f)
            sunX = -110.0f;
    }
}


// ============================================================
// MOON MOVEMENT
// ============================================================

void moveMoon()
{
    moonX += 0.1f;

    if (moonX > 90.0f)
    {
        moonX = -90.0f;
    }
}


// ============================================================
// DAY / NIGHT TOGGLE
// ============================================================

void toggleNight()
{
    nightMode = !nightMode;
}


// ============================================================
// INITIALIZE RAIN
// ============================================================

void initRain()
{
    /*
        Rain is distributed over the ENTIRE screen.

        Horizontal spacing keeps drops separated.
        Vertical spacing keeps drops separated.
    */

    const float horizontalSpacing = 15.0f;
    const float verticalSpacing = 11.0f;

    const int columns = 14;
    const int rows = 13;

    int index = 0;

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            if (index >= MAX_RAINDROPS)
                return;

            // Stagger alternate rows
            float offsetX;

            if (row % 2 == 0)
                offsetX = 0.0f;
            else
                offsetX = horizontalSpacing * 0.5f;

            rainX[index] =
                -100.0f +
                column * horizontalSpacing +
                offsetX;

            rainY[index] =
                100.0f -
                row * verticalSpacing;

            index++;
        }
    }
}


// ============================================================
// START RAIN
// ============================================================

void startRain()
{
    // Immediately fill the entire screen with rain.
    initRain();

    rain = true;
}


// ============================================================
// STOP RAIN
// ============================================================

void stopRain()
{
    rain = false;
}


// ============================================================
// MOVE RAIN
// ============================================================

void moveRain()
{
    if (!rain)
        return;

    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        // ====================================================
        // DIAGONAL MOVEMENT
        //
        // Rain moves DOWN + LEFT
        // ====================================================

        rainX[i] -= 0.35f;
        rainY[i] -= 1.4f;


        // ====================================================
        // CONTINUOUS TOP/BOTTOM LOOP
        //
        // When a drop reaches the bottom, immediately place
        // it at the TOP with a small variation.
        //
        // This prevents the upper part of the screen from
        // becoming empty.
        // ====================================================

        if (rainY[i] < -105.0f)
        {
            rainY[i] = 105.0f;

            /*
                Move it slightly forward horizontally.

                This prevents all recycled drops from forming
                one straight vertical column.
            */

            rainX[i] -= 7.5f;

            if (rainX[i] < -110.0f)
            {
                rainX[i] += 210.0f;
            }
        }


        // ====================================================
        // LEFT SIDE LOOP
        // ====================================================

        if (rainX[i] < -110.0f)
        {
            rainX[i] = 105.0f;
        }
    }
}


// ============================================================
// DRAW RAIN
// ============================================================

void drawRain()
{
    if (!rain)
        return;

    // Light blue rain
    glColor3f(
        0.65f,
        0.8f,
        1.0f
    );

    // Small raindrops
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        // ====================================================
        // SMALL /-SHAPED RAINDROP
        //
        // Top-right
        //       /
        //      /
        // Bottom-left
        // ====================================================

        glVertex2f(
            rainX[i],
            rainY[i]
        );

        glVertex2f(
            rainX[i] - 2.0f,
            rainY[i] - 5.0f
        );
    }

    glEnd();
}

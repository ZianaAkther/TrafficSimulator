#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#include "Environment.h"
#include "Vehicles.h"
#include "DayNight.h"
#include "emergency.h"

// =====================================================
// ROAD VEHICLE POSITIONS
// =====================================================

float car1 = -80.0f;
float car1Y = -10.0f;

float car2 = -40.0f;
float car2Y = -10.0f;

float car3 = 80.0f;

float busY = 105.0f;
float microbusY = -105.0f;


// =====================================================
// BOAT POSITIONS
// =====================================================

float boat1X = 35.0f;
float boat1Y = -48.0f;

float boat2X = 88.0f;
float boat2Y = -78.0f;


// =====================================================
// GAME CONTROL
// =====================================================

bool pauseGame = false;


// =====================================================
// TRAFFIC SIGNAL STATES
// 0 = RED
// 1 = YELLOW
// 2 = GREEN
// =====================================================

int light = 0;
int verticalLight = 2;

int lightCount = 0;
int previousLight = 0;


// =====================================================
// STREET LAMP
// =====================================================

void drawStreetLamp(float x, float y)
{
    // =================================================
    // POLE
    // =================================================

    glColor3f(0.12f, 0.12f, 0.12f);

    // Vertical pole
    glBegin(GL_QUADS);

        glVertex2f(x - 0.8f, y);
        glVertex2f(x + 0.8f, y);
        glVertex2f(x + 0.8f, y + 15.0f);
        glVertex2f(x - 0.8f, y + 15.0f);

    glEnd();


    // =================================================
    // TOP ARM
    // =================================================

    glBegin(GL_QUADS);

        glVertex2f(x - 0.8f, y + 14.0f);
        glVertex2f(x + 5.0f, y + 14.0f);
        glVertex2f(x + 5.0f, y + 15.0f);
        glVertex2f(x - 0.8f, y + 15.0f);

    glEnd();


    // =================================================
    // LAMP HEAD
    // =================================================

    if (nightMode)
    {
        // Bright light at night
        glColor3f(1.0f, 1.0f, 0.4f);

        drawCircle(
            x + 5.0f,
            y + 13.5f,
            2.0f
        );

        // Small glow
        glColor3f(0.8f, 0.75f, 0.25f);

        drawCircle(
            x + 5.0f,
            y + 13.5f,
            3.2f
        );
    }
    else
    {
        // Lamp OFF during daytime
        glColor3f(0.25f, 0.25f, 0.20f);

        drawCircle(
            x + 5.0f,
            y + 13.5f,
            1.8f
        );
    }
}


// =====================================================
// STOP LINE CHECK
// =====================================================

bool canCrossStopLine(
    float currentPos,
    float newPos,
    float stopLine,
    bool isPositive)
{
    if (isPositive)
    {
        if (currentPos < stopLine &&
            newPos >= stopLine)
        {
            return false;
        }
    }
    else
    {
        if (currentPos > stopLine &&
            newPos <= stopLine)
        {
            return false;
        }
    }

    return true;
}


// =====================================================
// HORIZONTAL CAR MOVEMENT
// =====================================================

void moveHorizontalCars()
{
    if (pauseGame)
        return;


    // Emergency pull-over
    if (emergency)
    {
        if (car1Y > -20.0f)
            car1Y -= 0.2f;

        if (car2Y > -20.0f)
            car2Y -= 0.2f;

        return;
    }
    else
    {
        if (car1Y < -10.0f)
            car1Y += 0.2f;

        if (car2Y < -10.0f)
            car2Y += 0.2f;
    }


    float speed =
        (light == 1) ? 0.2f : 0.5f;

    float minGap = 24.0f;


    // -------------------------------------------------
    // Car 2 - Lead Car
    // -------------------------------------------------

    float newX2 = car2 + speed;

    if (light == 2 ||
        canCrossStopLine(
            car2,
            newX2,
            -37.0f,
            true))
    {
        car2 = newX2;
    }


    // -------------------------------------------------
    // Car 1 - Following Car
    // -------------------------------------------------

    float newX1 = car1 + speed;

    bool gapIsSafe =
        (car2 <= car1) ||
        ((car2 - car1) >= minGap);

    if ((light == 2 ||
         canCrossStopLine(
             car1,
             newX1,
             -37.0f,
             true))
        && gapIsSafe)
    {
        car1 = newX1;
    }


    // -------------------------------------------------
    // Car 3 - Opposite Direction
    // -------------------------------------------------

    float newX3 = car3 - speed;

    if (light == 2 ||
        canCrossStopLine(
            car3,
            newX3,
            25.0f,
            false))
    {
        car3 = newX3;
    }


    // Screen wrapping
    if (car2 > 110.0f)
        car2 = -110.0f;

    if (car1 > 110.0f)
        car1 = -110.0f;

    if (car3 < -110.0f)
        car3 = 110.0f;
}


// =====================================================
// VERTICAL VEHICLE MOVEMENT
// =====================================================

void moveVerticalVehicles()
{
    if (pauseGame || emergency)
        return;


    float speed =
        (verticalLight == 1) ? 0.2f : 0.5f;


    // -------------------------------------------------
    // Bus
    // -------------------------------------------------

    float newBusY = busY - speed;

    if (verticalLight == 2 ||
        canCrossStopLine(
            busY,
            newBusY,
            40.0f,
            false))
    {
        busY = newBusY;
    }


    // -------------------------------------------------
    // Microbus
    // -------------------------------------------------

    float newMicrobusY =
        microbusY + speed;

    if (verticalLight == 2 ||
        canCrossStopLine(
            microbusY,
            newMicrobusY,
            -44.0f,
            true))
    {
        microbusY = newMicrobusY;
    }


    // Screen wrapping

    if (busY < -110.0f)
        busY = 110.0f;

    if (microbusY > 110.0f)
        microbusY = -110.0f;
}


// =====================================================
// BOAT MOVEMENT
// =====================================================

void moveBoats()
{
    if (pauseGame || emergency)
        return;


    // =================================================
    // BOAT 1
    // LEFT -> RIGHT
    // =================================================

    boat1X += 0.20f;

    if (boat1X > 78.0f)
    {
        boat1X = 28.0f;
    }


    // =================================================
    // BOAT 2
    // RIGHT -> LEFT
    // =================================================

    boat2X -= 0.15f;

    if (boat2X < 52.0f)
    {
        boat2X = 95.0f;
    }
}


// =====================================================
// TIMER
// =====================================================

void timer(int value)
{
    if (emergency)
    {
        moveEmergency();
    }
    else
    {
        lightCount++;


        // -------------------------------------------------
        // Horizontal RED
        // Vertical GREEN
        // -------------------------------------------------

        if (light == 0)
        {
            verticalLight = 2;

            if (lightCount >= 100)
            {
                previousLight = 0;

                light = 1;
                verticalLight = 1;

                lightCount = 0;
            }
        }


        // -------------------------------------------------
        // YELLOW
        // -------------------------------------------------

        else if (light == 1)
        {
            verticalLight = 1;

            if (lightCount >= 50)
            {
                if (previousLight == 0)
                {
                    light = 2;
                    verticalLight = 0;
                }
                else
                {
                    light = 0;
                    verticalLight = 2;
                }

                lightCount = 0;
            }
        }


        // -------------------------------------------------
        // Horizontal GREEN
        // Vertical RED
        // -------------------------------------------------

        else if (light == 2)
        {
            verticalLight = 0;

            if (lightCount >= 200)
            {
                previousLight = 2;

                light = 1;
                verticalLight = 1;

                lightCount = 0;
            }
        }
    }


    // =================================================
    // MOVE ROAD VEHICLES
    // =================================================

    moveHorizontalCars();
    moveVerticalVehicles();


    // =================================================
    // MOVE BOATS
    // =================================================

    moveBoats();


    // =================================================
    // MOVE SUN, MOON AND RAIN
    // =================================================

    moveSun();
    moveMoon();
    moveRain();


    glutPostRedisplay();

    glutTimerFunc(
        30,
        timer,
        0);
}


// =====================================================
// MOUSE
// =====================================================

void mouse(
    int button,
    int state,
    int x,
    int y)
{
    if (state != GLUT_DOWN)
        return;


    // -------------------------------------------------
    // LEFT CLICK = START RAIN
    // -------------------------------------------------

    if (button == GLUT_LEFT_BUTTON)
    {
        startRain();
    }


    // -------------------------------------------------
    // RIGHT CLICK = STOP RAIN
    // -------------------------------------------------

    else if (button == GLUT_RIGHT_BUTTON)
    {
        stopRain();
    }
}


// =====================================================
// KEYBOARD
// =====================================================

void keyboard(
    unsigned char key,
    int x,
    int y)
{
    switch (key)
    {
        // -------------------------------------------------
        // Pause
        // -------------------------------------------------

        case 'p':
        case 'P':

            pauseGame = !pauseGame;

            break;


        // -------------------------------------------------
        // Day / Night
        // -------------------------------------------------

        case 'n':
        case 'N':

            toggleNight();

            break;


        // -------------------------------------------------
        // Emergency
        // -------------------------------------------------

        case 'e':
        case 'E':

            emergency = true;

            emergencyX = -115.0f;

            light = 0;
            verticalLight = 0;

            break;


        // -------------------------------------------------
        // RESET
        // -------------------------------------------------

        case 'r':
        case 'R':

            car1 = -80.0f;
            car1Y = -10.0f;

            car2 = -40.0f;
            car2Y = -10.0f;

            car3 = 80.0f;

            busY = 105.0f;
            microbusY = -105.0f;


            // Reset boats
            boat1X = 35.0f;
            boat1Y = -48.0f;

            boat2X = 88.0f;
            boat2Y = -78.0f;


            // Reset game
            pauseGame = false;

            emergency = false;

            emergencyX = -115.0f;

            light = 0;
            verticalLight = 2;

            previousLight = 0;
            lightCount = 0;

            // Stop rain
            stopRain();

            break;


        // -------------------------------------------------
        // ESC
        // -------------------------------------------------

        case 27:

            exit(0);

            break;
    }
}


// =====================================================
// DISPLAY
// =====================================================

void display()
{
    // -------------------------------------------------
    // SKY
    // -------------------------------------------------

    if (nightMode)
    {
        glClearColor(
            0.03f,
            0.05f,
            0.15f,
            1.0f);
    }
    else
    {
        glClearColor(
            0.5f,
            0.8f,
            1.0f,
            1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT);


    // =================================================
    // SUN / MOON
    // =================================================

    // During rain, hide sun/moon.
    if (!rain)
    {
        if (nightMode)
        {
            drawMoon(
                moonX,
                moonY);
        }
        else
        {
            drawSun(
                sunX,
                sunY);
        }
    }


    // =================================================
    // ENVIRONMENT
    // =================================================

    drawStaticEnvironment();


    // =================================================
    // STREETLAMPS
    // =================================================

    // Upper horizontal road
    drawStreetLamp(-90.0f, 25.0f);
    drawStreetLamp(-60.0f, 25.0f);
    drawStreetLamp(-30.0f, 25.0f);
    drawStreetLamp(35.0f, 25.0f);
    drawStreetLamp(65.0f, 25.0f);
    drawStreetLamp(90.0f, 25.0f);


    // Lower horizontal road
    drawStreetLamp(-85.0f, -32.0f);
    drawStreetLamp(-55.0f, -32.0f);
    drawStreetLamp(-30.0f, -32.0f);
    drawStreetLamp(35.0f, -32.0f);
    drawStreetLamp(65.0f, -32.0f);
    drawStreetLamp(90.0f, -32.0f);


    // =================================================
    // TRAFFIC LIGHTS
    // =================================================

    drawTrafficLight(
        28.0f,
        25.0f,
        light);

    drawTrafficLight(
        -28.0f,
        -42.0f,
        verticalLight);


    // =================================================
    // ROAD VEHICLES
    // =================================================

    drawCar(
        car1,
        car1Y,
        0.8f,
        0.1f,
        0.1f);

    drawCar(
        car2,
        car2Y,
        0.1f,
        0.3f,
        0.8f);

    drawCar(
        car3,
        10.0f,
        0.1f,
        0.8f,
        0.2f);


    drawBus(
        -18.0f,
        busY);

    drawMicrobus(
        5.0f,
        microbusY);


    // =================================================
    // BOATS
    // =================================================

    drawBoat(
        boat1X,
        boat1Y);

    drawBoat(
        boat2X,
        boat2Y);


    // =================================================
    // EMERGENCY VEHICLE
    // =================================================

    if (emergency)
    {
        drawAmbulance(
            emergencyX,
            -6.0f);
    }


    // =================================================
    // RAIN
    // =================================================

    drawRain();


    glFlush();
}


// =====================================================
// OPENGL INITIALIZATION
// =====================================================

void init()
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(
        -100,
        100,
        -100,
        100);
}


// =====================================================
// MAIN
// =====================================================

int main(
    int argc,
    char** argv)
{
    glutInit(
        &argc,
        argv);

    glutInitDisplayMode(
        GLUT_SINGLE |
        GLUT_RGB);

    glutInitWindowSize(
        900,
        700);

    glutCreateWindow(
        "Automated Traffic Simulator");


    init();


    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    // Mouse controls for rain
    glutMouseFunc(mouse);


    glutTimerFunc(
        0,
        timer,
        0);


    glutMainLoop();

    return 0;
}

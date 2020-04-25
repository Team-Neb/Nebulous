// Omar Flores Estrada
// 191T Game Development
// Dr. Dhanyu
// Midterm 01
#include <GLLight.h>
#include "GLScene.h"
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<player.h>
#include <Objects.h>


Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *plx = new Parallax();
Parallax *pause = new Parallax();
player *ply = new player();
StateManager *stateManager = new StateManager;
Parallax *tlt = new Parallax();
Parallax *menu = new Parallax();
Parallax *help = new Parallax();





GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // For better animation transitions
    glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f); // Input the background color
    glClearDepth(1.0f);      // To choose what is in the front and in the back like layers
    glEnable(GL_DEPTH_TEST); // To calculate the depth perception

    glEnable(GL_COLOR_MATERIAL); // This is for rendering the base color of an object (glColor3f)
    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0); // create light instance

   // images to import for game states
    ply->playerInit("images/hero.png");
    plx->parallaxInit("images/par.png");
    pause->parallaxInit("images/pause.jpg");
    tlt->parallaxInit("images/title.png");
    menu->parallaxInit("images/FrontMenu.jpg");
    help->parallaxInit("images/help.jpg");

    return true;

}

//function for main to exit game when escape is pressed on certain game states
GameStates GLScene::sendState(){
    return stateManager->_gameState;}


GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    stateManager->_gameState;
    //  State manager used to manipulate game states
    switch(stateManager->_gameState){
    case LANDING:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        tlt->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case MENU:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        menu->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case HELP:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        help->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case GAME:
        glPushMatrix();
        plx -> drawSquare(screenHeight, screenWidth);
        glPopMatrix();

        glTranslated(ply->xPos, ply->yPos , ply->zPos);
        ply->drawPlayer(); // render character
        ply->playerActions(); // render actions
        break;

    case PAUSED: // pop up pause menu

        glPushMatrix();
        glScaled(.75, .75, 1.0); // reduced scaling to reduce size
        pause -> drawPopUp(screenHeight, screenWidth);
        glPopMatrix();

        glPushMatrix();
        plx -> drawSquare(screenHeight, screenWidth);// drawing the game behind the pop screen
        glPopMatrix();

        break;
        default:
        break;


    }
    //plx -> scroll("left", 0.0001);




}


GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //call this every time after modelview
}

int GLScene::winMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    	switch (uMsg)
    	{


            case WM_KEYDOWN:
            {
                KbMs ->wParam = wParam;    //second variable refernces one here other is in a differnt file
                KbMs -> keyPressed(Mdl, stateManager);


            if (stateManager->_gameState == GAME) // The game cannot be controlled while paused
                {
                KbMs -> playerAction(ply);
                KbMs -> manualParallax(plx, 0.005);
                }
                break;
            }

            case WM_KEYUP:
            {
                ply->actionTrigger="stand";
                break;

            }

case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            KbMs->mouseEventUp();
        break;
        }

        case WM_MOUSEMOVE:
        {
             KbMs->mouseEventMove(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

        case WM_MOUSEWHEEL:
        {
            KbMs->mouseEventWheel(Mdl,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;
        }




    }

}

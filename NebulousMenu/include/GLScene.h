#ifndef GLSCENE_H
#define GLSCENE_H
#include <string.h>
#include <windows.h>
#include <GL/glut.h>
#include <StateManager.h>



class GLScene
{
    public:
        GLScene();                  //constructor
        virtual ~GLScene();         //Deconstructor
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei,GLsizei);
        GameStates sendState();

        int winMsg(HWND, UINT, WPARAM, LPARAM);
        float screenWidth, screenHeight;


    protected:

    private:
        void spawnEnemies(int);
        int level;
        bool is_level_complete;
};

#endif // GLSCENE_H

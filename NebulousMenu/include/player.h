#ifndef PLAYER_H
#define PLAYER_H

#include<GL/gl.h>
#include<TextureLoader.h>

typedef struct
{
    float x;
    float y;
    float z;
}vec;

class player
{
    public:
        player();
        virtual ~player();

        void drawPlayer();
        void playerInit(char *);
        void playerActions(); // pass in character variable for actions based on words

        string actionTrigger;
        vec vertices[4];
        float xMin, yMin, xMax, yMax, xSize, ySize;

        float xPos, yPos, zPos;
        int frames;
        bool lastKeyHit; // False = facing right, True = facing left
        int health;      // player health


        bool hasPlayerAttacked();
        void setPlayerAttackStatus(bool);
        int getPlayerDirection();
        void setPlayerDirection(int);
    protected:

    private:
        bool playerSwingSword;
        int playerDir;      // -1 or 1; determines whether facing left or right
};

#endif // PLAYER_H

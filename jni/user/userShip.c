//
//  userShip.c
//  
//
//  Created by thierry allard saint albin on 22/09/2015.
//
//

#include "../SDL/src/core/android/SDL_android.h"
#include "userShip.h"
#include <android/log.h>
#include <jni.h>
#include <stdlib.h>
#include <math.h>
#include "../general/constant.h"
#include "../general/drawer.h"

// typedef struct SpriteShip
// {
//     SDL_Texture* texture;
//     Uint16 w;
//     Uint16 h;
// } SpriteShip;

// SpriteShip LoadSpriteShip(const char* file, SDL_Renderer* renderer)
// {
//     SpriteShip result;
//     result.texture = NULL;
//     result.w = 0;
//     result.h = 0;

//     SDL_Surface* temp;

//     /* Load the sprite image */
//     temp = SDL_LoadBMP(file);

//     SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0, 0, 0));
//     if (temp == NULL)
//     {
//         fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
//         return result;
//     }
//     result.w = temp->w;
//     result.h = temp->h;

//     /* Create texture from the image */
//     result.texture = SDL_CreateTextureFromSurface(renderer, temp);
//     if (!result.texture) {
//         fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
//         SDL_FreeSurface(temp);
//         return result;
//     }
//     SDL_FreeSurface(temp);

//     return result;
// }

void drawMyShip(SDL_Renderer* renderer , UserShip * myShip)
{
     if(myShip->visible == VISIBLE)
     {

        myShip->rectangle->x = myShip->posX;
        myShip->rectangle->y = myShip->posY;
        myShip->rectangle->w = 200;
        myShip->rectangle->h = 174;
        //SDL_SetRenderDrawColor(renderer, myShip->color[0], myShip->color[1], myShip->color[2], myShip->color[3]);
        //SDL_RenderFillRect(renderer, (myShip->rectangle));
        //myShip->myShipSprite = LoadSprite("myShipGood.bmp", renderer);
        myShip->myShipSprite = loadTexture("myShipGood.png", renderer);
        renderTexture(myShip->myShipSprite.texture, renderer, myShip->rectangle->x, myShip->rectangle->y);
    }
}

void moveMyShip(UserShip * myShip,int TypeMove,int widthScreen, int heightScreen, double coef)
{
    int newValue;
   // __android_log_print(ANDROID_LOG_DEBUG, "TypeMove"," %d",TypeMove);

    switch(TypeMove)
    {
        case 0:
            
            newValue = myShip->posX + (coef * myShip->speed);
           if(newValue < widthScreen - myShip->rectangle->w)
                myShip->posX = newValue;
                
            break;
            
        case 1:
            
            newValue = myShip->posY + (coef * myShip->speed);
            if(newValue < heightScreen - myShip->rectangle->h)
                myShip->posY = newValue;
            break;
     
        case 2:
            
            newValue = myShip->posX - (coef * myShip->speed);
            
            if(newValue > -1)
                myShip->posX = newValue;

            break;
    
        case 3:   
            newValue = myShip->posY - (coef * myShip->speed);
          //  if(newValue > -1)
                myShip->posY = newValue;
            break;
     
    }
}


void moveMyShipGeneral(float * accelValues,int sizeAccelValues ,UserShip * myShip,int widthScreen, int heightScreen)
{
    char values[30];
    int index = 0;
    for(index = 0 ; index < sizeAccelValues ; index++)
    {
        switch(index)
        {
            case 0:
                if(accelValues[index] > 0.15)
                {
                    moveMyShip(myShip,0,widthScreen,heightScreen, fabs(floor(accelValues[index]/0.12)));
                }
            
                if(accelValues[index] < -0.15)
                {
                    moveMyShip(myShip,2,widthScreen,heightScreen, fabs(floor(accelValues[index]/0.12)));
                }
                
                
       //         sprintf(values,"value X %f",accelValues[index]);
                break;
                
            case 1:
                if(accelValues[index] > 0.15)
                {
                    moveMyShip(myShip,1,widthScreen,heightScreen, fabs(floor(accelValues[index]/0.12)));
                }
                if(accelValues[index] < -0.15)
                {
                    moveMyShip(myShip,3,widthScreen,heightScreen, fabs(floor(accelValues[index]/0.12)));
                }
                
                
      //          sprintf(values,"value Y %f",accelValues[index]);
                break;
                
                //               case 2: sprintf(values,"value Z %f",accelValues[i]);
                //               break;
                
        }
       // __android_log_print(ANDROID_LOG_DEBUG, "accelValues","%s",values);
       // memset(values, 0, 30 * (sizeof values[0]));
    }
}



void freeShip(UserShip * myShip)
{
    free(myShip->rectangle);
    free(myShip);
}

UserShip * initialisationUserShip(int width,int height)
{
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    UserShip  * myShip = malloc( sizeof(UserShip));
    myShip->rectangle = rectangle;

    rectangle->x = width/2;
    rectangle->y = height/8 * 7;
    myShip->posX = rectangle->x;
    myShip->posY = rectangle->y;
    myShip->speed = 1;
    myShip->color[0] = 96;
    myShip->color[1] = 198;
    myShip->color[2] = 181;
    myShip->color[3] = 255;
    myShip->life = 99;
    myShip->shotLevel = 1;
    myShip->visible = VISIBLE;
    //myShip->myShipSprite = NULL;
    
    return myShip;

}

int userShipIsAlive(UserShip * userShip)
{
    if(userShip->life == 0)
        return FALSE;
    return TRUE;
}

void decreaseLife( UserShip * myShip )
{
    if(myShip->life >0)
    {
        (myShip->life)--; 
    }
    if(myShip->life == 0)
    {
        myShip->visible = INVISIBLE;
    }
}
void addLife( UserShip * myShip )
{
    if(myShip->life < MAX_LIFE && myShip->visible == VISIBLE)
        (myShip->life)++;
}






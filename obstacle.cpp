#include "obstacle.h"

Obstacle::Obstacle()
{

}

QList<QRect> Obstacle::getObstacleList()
{
    return obstacleList;
}

void Obstacle::generateObstacle(int gameLevel)
{
    obstacleList.clear();
    switch (gameLevel)
    {
    case 1:
    {
        generateObstacleGameLevelOne();
        break;
    }
    case 2:
    {
        generateObstacleGameLevelTwo();
        break;
    }
    case 3:
    {
        generateObstacleGameLevelThree();
        break;
    }
    case 4:
    {
        generateObstacleGameLevelFour();
        break;
    }
    case 5:
    {
        generateObstacleGameLevelFive();
        break;
    }
    case 6:
    {
        generateObstacleGameLevelSix();
        break;
    }
    case 7:
    {
        generateObstacleGameLevelSeven();
        break;
    }
    default:
    {
        generateObstacleGameLevelOne();
        break;
    }
    }
}

void Obstacle::generateObstacleGameLevelOne()
{
    QRect rect;
    for(int i=0; i<MAXMAPSIZE; i++)
    {
        if(i != MAXMAPSIZE / 2)
        {
            rect = QRect(i * UNIT, 0 * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
            obstacleList.append(rect);
            rect = QRect(i * UNIT, (MAXMAPSIZE - 1) * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
            obstacleList.append(rect);
        }

        if((i != 0) && (i != MAXMAPSIZE - 1) && (i != MAXMAPSIZE / 2))
        {
            rect = QRect(0 * UNIT, i * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
            obstacleList.append(rect);
            rect = QRect((MAXMAPSIZE - 1) * UNIT, i * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
            obstacleList.append(rect);
        }
    }
}

void Obstacle::generateObstacleGameLevelTwo()
{

}

void Obstacle::generateObstacleGameLevelThree()
{

}

void Obstacle::generateObstacleGameLevelFour()
{

}

void Obstacle::generateObstacleGameLevelFive()
{

}

void Obstacle::generateObstacleGameLevelSix()
{

}

void Obstacle::generateObstacleGameLevelSeven()
{

}

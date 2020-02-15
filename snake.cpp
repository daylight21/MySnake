#include "snake.h"

Snake::Snake()
{

}

Snake::~Snake()
{

}

void Snake::judgeSnakeStatus(QRect rect)
{
    for(int i=1; i<snakeLength; i++)
    {
        if(snakeList[i].x() == rect.x() && snakeList[i].y() == rect.y())
            snakeStatus = DEATH;
    }
}

void Snake::initSnake()
{
    snakeList.clear();
    eatFoodNumber = 0;
    snakeLength = 2;
    QRect rect;
    rect = QRect(MAXMAPSIZE / 2 * UNIT, MAXMAPSIZE / 2 * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
    snakeHead = rect;
    snakeList.append(snakeHead);
    rect = QRect((MAXMAPSIZE / 2 + 1) * UNIT, MAXMAPSIZE / 2 * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
    snakeTail = rect;
    snakeList.append(snakeTail);
    snakeStatus = LIVE;
}

int Snake::getSnakeLength()
{
    return snakeLength;
}

QRect Snake::getSnakeHead()
{
    return snakeList[0];
}

QRect Snake::getSnakeTail()
{
    return snakeList[snakeLength - 1];
}

QList<QRect> Snake::getSnakeList()
{
    return snakeList;
}

void Snake::addSnakeLength()
{
    snakeLength++;
}

void Snake::alterSnakeList(Direction direction)
{
    switch (direction)
    {
    case UP:
    {
        QRect rect(snakeList.at(0).x(), (snakeList.at(0).y() - MENUBARHEIGHT - UNIT + WINDOWSIZE) % WINDOWSIZE  + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
        judgeSnakeStatus(rect);
        if(!isDead())
        {
            for(int i=snakeLength-1; i>0; i--)
            {
                snakeList.replace(i, snakeList.at(i-1));
            }
            snakeList.replace(0, rect);
        }
        break;
    }
    case DOWN:
    {
        QRect rect(snakeList.at(0).x(), (snakeList.at(0).y() - MENUBARHEIGHT + UNIT) % WINDOWSIZE + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
        judgeSnakeStatus(rect);
        if(!isDead())
        {
            for(int i=snakeLength-1; i>0; i--)
            {
                snakeList.replace(i, snakeList.at(i-1));
            }

            snakeList.replace(0, rect);
        }
        break;
    }
    case LEFT:
    {
        QRect rect((snakeList.at(0).x() - UNIT + WINDOWSIZE) % WINDOWSIZE, snakeList.at(0).y(), UNITSIZE, UNITSIZE);
        judgeSnakeStatus(rect);
        if(!isDead())
        {
            for(int i=snakeLength-1; i>0; i--)
            {
                snakeList.replace(i, snakeList.at(i-1));
            }

            snakeList.replace(0, rect);
        }
        break;
    }
    case RIGHT:
    {
        QRect rect((snakeList.at(0).x() + UNIT) % WINDOWSIZE, snakeList.at(0).y(), UNITSIZE, UNITSIZE);
        judgeSnakeStatus(rect);
        if(!isDead())
        {
            for(int i=snakeLength-1; i>0; i--)
            {
                snakeList.replace(i, snakeList.at(i-1));
            }

            snakeList.replace(0, rect);
        }
        break;
    }
    }

}

void Snake::snakeEatFood()
{
    QRect rect;
    QRect rect1 = snakeList.at(snakeLength-1);
    QRect rect2 = snakeList.at(snakeLength-2);
    addSnakeLength();
    if(rect1.x() == rect2.x())
    {
        if(rect1.y() <= rect2.y())
        {
            int x = rect1.x();
            int y = (rect1.y() - UNIT - MENUBARHEIGHT + WINDOWSIZE) % WINDOWSIZE + MENUBARHEIGHT;
            rect = QRect(x, y, UNITSIZE, UNITSIZE);
            snakeList.append(rect);
        }
        else
        {
            int x = rect1.x();
            int y = (rect1.y() + UNIT - MENUBARHEIGHT) % WINDOWSIZE + MENUBARHEIGHT;
            rect = QRect(x, y, UNITSIZE, UNITSIZE);
            snakeList.append(rect);
        }
    }
    else if(rect1.y() == rect2.y())
    {
        if(rect1.x() <= rect2.x())
        {
            int x = (rect1.x() - UNIT + WINDOWSIZE) % WINDOWSIZE;
            int y = rect1.y();
            rect = QRect(x, y, UNITSIZE, UNITSIZE);
            snakeList.append(rect);
        }
        else
        {
            int x = (rect1.x() + UNIT) % WINDOWSIZE;
            int y = rect1.y();
            rect = QRect(x, y, UNITSIZE, UNITSIZE);
            snakeList.append(rect);
        }
    }
    eatFoodNumber++;
}

void Snake::isSnakeHitObstacle(QList<QRect> obstacleList)
{
    for(int i=0; i<obstacleList.size(); i++)
    {
        if((obstacleList[i].x() == snakeList[0].x()) && (obstacleList[i].y() == snakeList[0].y()))
            snakeStatus = DEATH;
    }
}

bool Snake::isDead()
{
    return (snakeStatus == DEATH);
}

int Snake::getEatFoodNumber()
{
    return eatFoodNumber;
}

void Snake::setSnakeHead(QRect head)
{
    snakeHead = head;
}

void Snake::setSnakeTail(QRect tail)
{
    snakeTail = tail;
}

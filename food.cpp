#include "food.h"

Food::Food()
{

}

Food::~Food()
{

}

void Food::generateInitialFood(QList<QRect> snakeList, QList<QRect> obstacleList)
{
    foodList.clear();
    QList<QRect> list;
    list.append(snakeList);
    list.append(obstacleList);
    for(int i=0; i<FOODAMOUNT; i++)
    {
        bool flag = true;
        while(flag)
        {
            int x = qrand() % MAXMAPSIZE;
            int y = qrand() % MAXMAPSIZE;
            QRect rect(x * UNIT, y  * UNIT + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
            if(!list.contains(rect))
            {
                foodList.append(rect);
                flag = false;
            }
        }
    }

}

void Food::generateFood()
{

}


bool Food::isEat(QList<QRect> snakeList, QList<QRect> obstacleList)
{
    QList<QRect> list;
    list.append(snakeList);
    list.append(obstacleList);
    list.append(foodList);
    if(foodList.contains(snakeList.at(0)))
    {
        int index = foodList.indexOf(snakeList.at(0));
        bool flag = true;
        while(flag)
        {
            int x = qrand() % MAXMAPSIZE;
            int y = qrand() % MAXMAPSIZE;
            QRect rect(x * UNIT, y  * UNIT  + MENUBARHEIGHT, UNITSIZE, UNITSIZE);
            if(!list.contains(rect))
            {
                foodList.replace(index, rect);
                flag = false;
            }
        }
        return true;
    }
    return false;
}

QList<QRect> Food::getFoodList()
{
    return foodList;
}

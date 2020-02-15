#ifndef SNAKE_H
#define SNAKE_H

#include <QRect>
#include <QList>
#include "definition.h"

enum Direction
{
    UP, DOWN, LEFT, RIGHT
};

enum SnakeStatus
{
    LIVE, DEATH
};

class Snake : public QObject
{
private:
   QList<QRect> snakeList;
   QRect snakeHead;
   QRect snakeTail;
   int snakeLength;
   int eatFoodNumber;
   SnakeStatus snakeStatus;

public:
    Snake();
    ~Snake();


private:
    void judgeSnakeStatus(QRect rect);

public:
    void initSnake();
    int getSnakeLength();
    QRect getSnakeHead();
    QRect getSnakeTail();
    QList<QRect> getSnakeList();
    void addSnakeLength();
    void setSnakeHead(QRect head);
    void setSnakeTail(QRect tail);
    void alterSnakeList(Direction direction);
    void snakeEatFood();
    void isSnakeHitObstacle(QList<QRect> obstacleList);
    bool isDead();
    int getEatFoodNumber();
};

#endif // SNAKE_H

#ifndef FOOD_H
#define FOOD_H

#include <QRect>
#include <QList>
#include <QObject>
#include "definition.h"


class Food : public QObject
{
    Q_OBJECT

private:
    QList<QRect> foodList;

public:
    Food();
    ~Food();

    void generateInitialFood(QList<QRect> snakeList, QList<QRect> obstacleList);
    void generateFood();
    bool isEat(QList<QRect> snakeList, QList<QRect> obstacleList);
    QList<QRect> getFoodList();
};

#endif // FOOD_H

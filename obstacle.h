#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "definition.h"
#include <QRect>
#include <QList>
#include <QObject>

class Obstacle : public QObject
{
    Q_OBJECT
public:
    Obstacle();

private:
    QList<QRect> obstacleList;

public:
    QList<QRect> getObstacleList();
    void generateObstacle(int gameLevel);

private:
    void generateObstacleGameLevelOne();
    void generateObstacleGameLevelTwo();
    void generateObstacleGameLevelThree();
    void generateObstacleGameLevelFour();
    void generateObstacleGameLevelFive();
    void generateObstacleGameLevelSix();
    void generateObstacleGameLevelSeven();

};

#endif // OBSTACLE_H

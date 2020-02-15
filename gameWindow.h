#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

#include "snake.h"
#include "food.h"
#include "obstacle.h"

enum SystemStatus
{
    NOTREADY, INIT, RUNNING, PAUSE,DEAD
};

class GameWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *widgetStart;
    QWidget *widgetRunning;
    QLabel *labelUsersOperation;
    QPushButton *buttonStart;
    QPushButton *buttonQuit;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuHelp;
    QAction *actionGameStart;
    QAction *actionGameRestart;
    QAction *actionGamePauseOrContinue;
    QAction *actionGameAbout;

    QWidget *widgetScoreBoard;
    QLabel *labelScoreBoard;
    QLabel *labelSpeedChange;
    QLineEdit *lineSpeedShow;
    QPushButton *buttonPlus;
    QPushButton *buttonMinus;
    QLabel *labelScore;
    QLineEdit *lineScore;
    QLabel *labelHighestScore;
    QLabel *labelHighestScoreNumber;
    QPushButton *buttonRestart;
    QPushButton *buttonPauseOrContinue;

    Snake *snake;
    Food *food;
    Obstacle *obstacle;
    QPainter *painter;
    QFont font;
    QTimer *timer;
    int gameSpeed;
    int highestScore;

    SystemStatus systemStatus;
    Direction direction;

public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();

private:
    void initUI();
    void initState();
    void initConnection();
    void initScoreBoard();

    void paintSnake(QPainter *painter);
    void paintFood(QPainter *painter);
    void paintObstacle(QPainter *painter);
    void paintSnakeMove(QPainter *painter, Direction direction);
    void paintBorder(QPainter *painter);
    void gamePause();
    void gameContinue();
    void gameAbout();
    int speedConvert(int speed);

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void gameStart();
    void gameQuit();
    void timeOut();
    void triggerMenu(QAction *action);
    void gameSpeedUp();
    void gameSpeedDown();
    void gamePauseOrContinue();
    void gameRestart();

};

#endif // MAINWINDOW_H

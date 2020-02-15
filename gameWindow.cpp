#include "gameWindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    initState();
    initConnection();
}

GameWindow::~GameWindow()
{

}

void GameWindow::initUI()
{
    setWindowTitle("贪吃蛇");
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);                            //窗口大小不变，不能最大化并且无法拖动放大缩小
    setFixedSize(WINDOWSIZE + SCOREBOARDWIDTH, WINDOWSIZE + MENUBARHEIGHT);

    widgetRunning = new QWidget();
    widgetRunning->setFixedSize(WINDOWSIZE + SCOREBOARDWIDTH, WINDOWSIZE + MENUBARHEIGHT);
    initScoreBoard();

    menu = new QMenu("菜单");
//    actionGameStart = new QAction("开始", this);
//    actionGameStart->setShortcut(KEYSTART);
//    menu->addAction(actionGameStart);

    actionGameRestart = new QAction("重新开始", this);
    //actionGameRestart->setShortcut(KEYRESTART);
    menu->addAction(actionGameRestart);

    actionGamePauseOrContinue= new QAction("暂停/继续", this);
    //actionGamePauseOrContinue->setShortcut(KEYPAUSEORCONTINUE);
    menu->addAction(actionGamePauseOrContinue);

    menuHelp = new QMenu("帮助");
    actionGameAbout = new QAction("关于", this);
    //actionGameAbout->setShortcut(KEYABOUT);
    menuHelp->addAction(actionGameAbout);

    menuBar = new QMenuBar();
    menuBar->addMenu(menu);
    menuBar->addMenu(menuHelp);
    menuBar->setFixedHeight(MENUBARHEIGHT);

    widgetStart = new QWidget();
    widgetStart->setFixedSize(WINDOWSIZE + SCOREBOARDWIDTH, WINDOWSIZE + MENUBARHEIGHT);
    QVBoxLayout *layoutGameWindow = new QVBoxLayout(widgetStart);

    QHBoxLayout *layoutLabelUsersOperation = new QHBoxLayout();
    labelUsersOperation = new QLabel();
    labelUsersOperation->setFixedSize((WINDOWSIZE + SCOREBOARDWIDTH) / 2, WINDOWSIZE / 2);
    font.setPixelSize(25);
    QString str;
    str.append("      游戏操作      ");
    str.append("\r\n");
    str.append("移动:      W/A/S/D");
    str.append("\r\n");
    str.append("速度调节:  +/-");
    str.append("\r\n");
    str.append("暂停/继续: 数字键2");
    str.append("\r\n");
    str.append("重新开始:  数字键3");
    str.append("\r\n");
    str.append("游戏关于:  数字键4");
    labelUsersOperation->setText(str);
    labelUsersOperation->setFont(font);
    layoutLabelUsersOperation->addWidget(labelUsersOperation, Qt::AlignCenter);

    QHBoxLayout *layoutButtonStart = new QHBoxLayout();
    buttonStart = new QPushButton("开始");
    buttonStart->setFixedSize((WINDOWSIZE + SCOREBOARDWIDTH) / 4, WINDOWSIZE / 8);
    font.setPixelSize(15);
    buttonStart->setFont(font);
    buttonQuit = new QPushButton("退出");
    buttonQuit->setFixedSize((WINDOWSIZE + SCOREBOARDWIDTH) / 4, WINDOWSIZE / 8);
    buttonQuit->setFont(font);
    layoutButtonStart->addWidget(buttonStart);
    layoutButtonStart->addWidget(buttonQuit);

    layoutGameWindow->addLayout(layoutLabelUsersOperation);
    layoutGameWindow->addLayout(layoutButtonStart);

    this->setMenuBar(menuBar);
    this->setCentralWidget(widgetStart);
}

void GameWindow::initState()
{
    snake = new Snake();
    food = new Food();
    obstacle = new Obstacle();
    highestScore = 0;
    timer = new QTimer(this);
    systemStatus = NOTREADY;
}

void GameWindow::initConnection()
{
    connect(buttonStart, SIGNAL(clicked()), this, SLOT(gameStart()));
    connect(buttonQuit, SIGNAL(clicked()), this, SLOT(gameQuit()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    connect(menuBar, SIGNAL(triggered(QAction *)), this, SLOT(triggerMenu(QAction *)));
    connect(buttonPlus, SIGNAL(clicked()), this, SLOT(gameSpeedUp()));
    connect(buttonMinus, SIGNAL(clicked()), this, SLOT(gameSpeedDown()));
    connect(buttonPauseOrContinue,  SIGNAL(clicked()), this, SLOT(gamePauseOrContinue()));
    connect(buttonRestart,  SIGNAL(clicked()), this, SLOT(gameRestart()));
}

void GameWindow::initScoreBoard()
{
    widgetScoreBoard = new QWidget(widgetRunning);
    widgetScoreBoard->setGeometry(WINDOWSIZE, 0, SCOREBOARDWIDTH, WINDOWSIZE);

    QVBoxLayout *layoutScoreBoard = new QVBoxLayout(widgetScoreBoard);

    QHBoxLayout *layoutLabelScore = new QHBoxLayout();
    labelScoreBoard = new QLabel("计分板");
    font.setPixelSize(30);
    labelScoreBoard->setFont(font);
    layoutLabelScore->addStretch();
    layoutLabelScore->addWidget(labelScoreBoard);
    layoutLabelScore->addStretch();

    QHBoxLayout *layoutSpeed = new QHBoxLayout();
    labelSpeedChange = new QLabel("速度:");
    font.setPixelSize(20);
    labelSpeedChange->setFont(font);
    lineSpeedShow = new QLineEdit();
    lineSpeedShow->setFixedSize(SCOREBOARDWIDTH / 3, WINDOWSIZE / 10);
    lineSpeedShow->setReadOnly(true);
    lineSpeedShow->setAlignment(Qt::AlignCenter);
    font.setPixelSize(15);
    lineSpeedShow->setFont(font);
    layoutSpeed->addWidget(labelSpeedChange);
    layoutSpeed->addWidget(lineSpeedShow);
    layoutSpeed->addStretch();

    QHBoxLayout *layoutButtonSpeed = new QHBoxLayout();
    buttonPlus = new QPushButton();
    buttonPlus->setFixedHeight(WINDOWSIZE / 10);
    font.setPixelSize(15);
    buttonPlus->setText("速度增加");
    buttonPlus->setFont(font);
    buttonMinus = new QPushButton();
    buttonMinus->setFixedHeight(WINDOWSIZE / 10);
    font.setPixelSize(15);
    buttonMinus->setText("速度降低");
    buttonMinus->setFont(font);
    layoutButtonSpeed->addWidget(buttonPlus);
    layoutButtonSpeed->addWidget(buttonMinus);

    QHBoxLayout *layoutScore = new QHBoxLayout();
    labelScore = new QLabel("分数:");
    font.setPixelSize(20);
    labelScore->setFont(font);
    lineScore = new QLineEdit();
    lineScore->setFixedSize(SCOREBOARDWIDTH / 3, WINDOWSIZE / 10);
    font.setPixelSize(15);
    lineScore->setFont(font);
    lineScore->setAlignment(Qt::AlignCenter);
    lineScore->setReadOnly(true);
    layoutScore->addWidget(labelScore);
    layoutScore->addWidget(lineScore);
    layoutScore->addStretch();

    QHBoxLayout *layoutHighestScore = new QHBoxLayout();
    labelHighestScore = new QLabel("最高分: ");
    font.setPixelSize(20);
    labelHighestScore->setFont(font);
    labelHighestScoreNumber = new QLabel(QString::number(highestScore));
    font.setPixelSize(20);
    labelHighestScoreNumber->setFont(font);
    labelHighestScoreNumber->setFixedSize(SCOREBOARDWIDTH / 3, WINDOWSIZE / 10);
    layoutHighestScore->addWidget(labelHighestScore);
    layoutHighestScore->addWidget(labelHighestScoreNumber);


    QHBoxLayout *layoutButtonFunction = new QHBoxLayout();
    buttonPauseOrContinue = new QPushButton();
    buttonPauseOrContinue->setFixedSize(SCOREBOARDWIDTH / 3, WINDOWSIZE / 8);
    font.setPixelSize(15);
    buttonPauseOrContinue->setText("运行");
    buttonPauseOrContinue->setFont(font);
    buttonRestart = new QPushButton();
    buttonRestart->setFixedSize(SCOREBOARDWIDTH / 3, WINDOWSIZE / 8);
    font.setPixelSize(15);
    buttonRestart->setText("重新开始");
    buttonRestart->setFont(font);
    layoutButtonFunction->addWidget(buttonPauseOrContinue);
    layoutButtonFunction->addWidget(buttonRestart);

    layoutScoreBoard->addLayout(layoutLabelScore);
    layoutScoreBoard->addSpacing(WINDOWSIZE / 30);
    layoutScoreBoard->addLayout(layoutSpeed);
    layoutScoreBoard->addLayout(layoutButtonSpeed);
    layoutScoreBoard->addSpacing(WINDOWSIZE / 10);
    layoutScoreBoard->addLayout(layoutScore);
    layoutScoreBoard->addSpacing(WINDOWSIZE / 10);
    layoutScoreBoard->addLayout(layoutHighestScore);
    layoutScoreBoard->addSpacing(WINDOWSIZE / 10);
    layoutScoreBoard->addLayout(layoutButtonFunction);
    layoutScoreBoard->addStretch();

    QPalette pal(this->palette());

    pal.setColor(QPalette::Background, QColor(99, 103, 106));
    widgetScoreBoard->setAutoFillBackground(true);
    widgetScoreBoard->setPalette(pal);
}

void GameWindow::paintSnake(QPainter *painter)
{
    QRect rect;
    painter->setPen(Qt::blue);

    for(int i=0; i<snake->getSnakeLength(); i++)
    {
        if(i == 0)
        {
            rect = snake->getSnakeList().at(i);
            painter->fillRect(rect, Qt::darkBlue);
        }
        else
        {
            rect = snake->getSnakeList().at(i);
            painter->fillRect(rect, Qt::blue);
        }
    }
}

void GameWindow::paintFood(QPainter *painter)
{
    QRect rect;
    painter->setPen(Qt::blue);

    for(int i=0; i<FOODAMOUNT; i++)
    {
        rect = food->getFoodList().at(i);
        painter->fillRect(rect, Qt::red);
    }
}

void GameWindow::paintObstacle(QPainter *painter)
{
    QRect rect;

    for(int i=0; i<obstacle->getObstacleList().size(); i++)
    {
        rect = obstacle->getObstacleList().at(i);
        painter->fillRect(rect, Qt::black);
    }
}

void GameWindow::paintSnakeMove(QPainter *painter, Direction direction)
{
    snake->alterSnakeList(direction);
    snake->isSnakeHitObstacle(obstacle->getObstacleList());
    if(food->isEat(snake->getSnakeList(), obstacle->getObstacleList()))
    {
        snake->snakeEatFood();
    }
    paintSnake(painter);
}

void GameWindow::paintBorder(QPainter *painter)
{
    QRect rect(WINDOWSIZE, MENUBARHEIGHT, SCOREBOARDWIDTH, WINDOWSIZE);
    painter->fillRect(rect, QBrush(QColor(245, 245, 220)));
}

void GameWindow::paintEvent(QPaintEvent*)
{
    painter = new QPainter();
    switch (systemStatus)
    {
    case NOTREADY:
    {
        break;
    }
    case INIT:
    {
        painter->begin(this);
        direction = LEFT;
        snake->initSnake();
        obstacle->generateObstacle(1);
        food->generateInitialFood(snake->getSnakeList(), obstacle->getObstacleList());
        paintObstacle(painter);
        paintSnake(painter);

        paintFood(painter);
        systemStatus = RUNNING;
        painter->end();
        break;
    }
    case RUNNING:
    {
        painter->begin(this);
        paintObstacle(painter);
        paintSnakeMove(painter, direction);
        paintFood(painter);
        if(snake->isDead())
        {
            systemStatus = DEAD;
        }
        painter->end();
        break;
    }
    case PAUSE:
    {
        painter->begin(this);
        paintObstacle(painter);
        paintSnake(painter);
        paintFood(painter);
        painter->end();
        break;
    }
    case DEAD:
    {
        if(highestScore < lineScore->text().toInt())
        {
            highestScore = lineScore->text().toInt();
            labelHighestScoreNumber->setText(QString::number(highestScore));
        }
        painter->begin(this);
        paintObstacle(painter);
        paintSnake(painter);
        paintFood(painter);
        painter->end();
        break;
    }
    }
    //QWidget::paintEvent(event);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_W)
    {
        if(!(direction == DOWN))
            direction = UP;
    }
    if(event->key() == Qt::Key_S)
    {
        if(!(direction == UP))
            direction = DOWN;
    }
    if(event->key() == Qt::Key_D)
    {
        if(!(direction == LEFT))
            direction = RIGHT;
    }
    if(event->key() == Qt::Key_A)
    {
        if(!(direction == RIGHT))
            direction = LEFT;
    }
    if(event->key() == KEYPAUSEORCONTINUE)
    {
        gamePauseOrContinue();
    }
    if(event->key() == KEYABOUT)
    {
        gamePause();
        gameAbout();
    }
    if(event->key() == KEYRESTART)
    {
        gameRestart();
    }
    if(event->key() == KEYSPEEDUP)
    {
        gameSpeedUp();
    }
    if(event->key() == KEYSPEEDDOWN)
    {
        gameSpeedDown();
    }

}

void GameWindow::gameStart()
{
    this->setCentralWidget(widgetRunning);
    systemStatus = INIT;
    gameSpeed = INITSPEED;
    lineSpeedShow->setText(QString::number(gameSpeed));
    timer->start(speedConvert(gameSpeed));
    lineScore->setText(QString::number(0));
}

void GameWindow::gameQuit()
{
    this->close();
}

void GameWindow::timeOut()
{
    update();
    lineScore->setText(QString::number(snake->getEatFoodNumber()));
    if(systemStatus == DEAD)
    {
        static bool flag = true;
        if(flag)
        {
            flag = false;
            QString str;
            str.append("你的分数是: ");
            str.append(lineScore->text());
            str.append("\r\n");
            str.append("  是否重来?  ");
            QMessageBox msgBox(QMessageBox::Warning, "失败", str, QMessageBox::Yes | QMessageBox::No);
            msgBox.setFixedSize(400, 400);
            int res = msgBox.exec();
            switch (res)
            {
            case QMessageBox::Yes:
            {
                systemStatus = INIT;
                flag = true;
                break;
            }
            case QMessageBox::No:
            {
                gameQuit();
                flag = true;
                break;
            }
            }
        }
    }
}

void GameWindow::triggerMenu(QAction *action)
{
    if(action->text() == "重新开始")
    {
        gameRestart();
    }
    if(action->text() == "暂停/继续")
    {
        gamePauseOrContinue();
    }
    if(action->text() == "关于")
    {
        gamePause();
        gameAbout();
    }
}

void GameWindow::gameSpeedUp()
{
    if(gameSpeed < 10)
        gameSpeed++;
    lineSpeedShow->setText(QString::number(gameSpeed));
    timer->stop();
    timer->start(speedConvert(gameSpeed));
}

void GameWindow::gameSpeedDown()
{
    if(gameSpeed > 0)
        gameSpeed--;
    lineSpeedShow->setText(QString::number(gameSpeed));
    timer->stop();
    timer->start(speedConvert(gameSpeed));
}

void GameWindow::gameRestart()
{
    systemStatus = INIT;
}

void GameWindow::gamePauseOrContinue()
{
    if(systemStatus == RUNNING)
        gamePause();
    else if(systemStatus == PAUSE)
        gameContinue();
}

void GameWindow::gamePause()
{
    systemStatus = PAUSE;
    buttonPauseOrContinue->setText("暂停");
}

void GameWindow::gameContinue()
{
    systemStatus = RUNNING;
    buttonPauseOrContinue->setText("运行");
}

void GameWindow::gameAbout()
{

    QMessageBox *messageBoxGameAbout = new QMessageBox();
    messageBoxGameAbout->setText("copyright by @daylight\r\n"
                                 "      2020/02/15      ");
    messageBoxGameAbout->exec();
}

int GameWindow::speedConvert(int speed)
{
    int timerCount;
    timerCount = 320 - speed * 30;
    return timerCount;
}

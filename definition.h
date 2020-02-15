#ifndef DEFINITION_H
#define DEFINITION_H

#define MAXMAPSIZE 20                       //地图单元格数目 地图呈正方形
#define WINDOWSIZE 400                      //游戏窗口大小，像素值
#define MENUBARHEIGHT 30                    //菜单栏高度
#define SCOREBOARDWIDTH 200                 //分数显示窗口宽度
#define UNIT WINDOWSIZE/MAXMAPSIZE          //地图单元格像素值
#define UNITSIZE UNIT-2                     //画图所用像素值，为了美观，不把所在像素值全部涂满，留下边界部分少数像素不涂
#define FOODAMOUNT 5                        //食物数量，地图单元格越多，食物设置量也应该越多
#define INITSPEED 3                         //游戏初始速度
#define KEYSTART Qt::Key_1                  //开始快捷键
#define KEYRESTART Qt::Key_2                //重新开始快捷键
#define KEYPAUSEORCONTINUE Qt::Key_3        //继续/暂停快捷键
#define KEYABOUT Qt::Key_4                  //关于快捷键
#define KEYSPEEDUP Qt::Key_Plus             //速度增加快捷键
#define KEYSPEEDDOWN Qt::Key_Minus          //速度降低快捷键

#endif // DEFINITION_H

//
// Created by ISSTECH on 2024/9/11.
//

#ifndef TEST_MOUSE_EVENT_MOUSESIMULATOR_H
#define TEST_MOUSE_EVENT_MOUSESIMULATOR_H


#include <qstring.h>
#include "mainwindow.h"

struct Point {
    int x;
    int y;
};
// 定义一个结构来存储显示器的尺寸
struct ScreenSize {
    int screenWidth;
    int screenHeight;
};
struct ScreenPosition {
    int x;
    int y;
};

class MouseSimulator {
public:
    MouseSimulator();

    ~MouseSimulator();
    // 获取当前光标显示器尺寸
    static ScreenSize getCurrentMonitorSize();
    // 获取当前光标位置(当前光标显示器)
    static ScreenPosition getCursorPosInCurrentMonitor();
    // 移动光标到指定位置(当前光标显示器)
    static void moveCursorToMonitorPos(int newX, int newY);

    void static moveMouseToTarget(Point current, Point target, int stride, int delay);

    // 1. 光标位置移动
    static void moveCursor(int x, int y, int stride, int delay);

    // 2. 左键单击
    static void leftClick();

    // 3. 左键双击
    static void leftDoubleClick();

    // 4. 左键点击拖动
    static void leftDrag(int x, int y, int stride, int delay);

    // 5. 右键单击
    static void rightClick(GestureData gestureData);

    // 6. 右键点击拖动
    static void rightDrag(int x, int y, int stride, int delay);

    // 7. 滚轮放大 (滚轮向上滚动)
    static void wheelZoomIn(float mult_wheel_delta);

    // 8. 滚轮缩小 (滚轮向下滚动)
    static void wheelZoomOut(float mult_wheel_delta);

    // 9. 中键点击拖动
    static void middleDrag(int x, int y, int stride, int delay);
};


#endif //TEST_MOUSE_EVENT_MOUSESIMULATOR_H

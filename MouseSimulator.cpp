//
// Created by ISSTECH on 2024/9/11.
//

#include "MouseSimulator.h"
#include <windows.h>
#include <QDebug>
#include <chrono>
#include <thread>

MouseSimulator::MouseSimulator() {

}

MouseSimulator::~MouseSimulator() {

}

// 光标位置移动
void MouseSimulator::moveCursor(int x, int y) {
    SetCursorPos(x, y);
}

// 左键单击
void MouseSimulator::leftClick() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

// 左键双击
void MouseSimulator::leftDoubleClick() {
    leftClick();
    Sleep(1000); // 一些时间间隔
    leftClick();
}

// 左键点击拖动
void MouseSimulator::leftDrag(int moveLong, int direction, int speed) {
    // 获取当前鼠标位置
    POINT pt;
    GetCursorPos(&pt);
    // 打印当前鼠标位置
    qDebug() << "Current Mouse Position:" << pt.x << pt.y;
    int newX = pt.x;
    int newY = pt.y;

    // 获取屏幕大小
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // 获取屏幕宽度
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 获取屏幕高度

    // 按下左键
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    for (int i = 1; i < moveLong; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        switch (direction) {
            case 1:// 左
                newX = newX - 1;
                if (newX < 0) {
                    qDebug() << "Move to left over";
                    // 松下左键
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    return;
                }
                break;
            case 2:// 右
                newX = newX + 1;
                if (newX > screenWidth) {
                    qDebug() << "Move to right over";
                    // 松下左键
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    return;
                }
                break;
            case 3:// 上
                newY = newY - 1;
                // 判断是否移动到最上边
                if (newY == 0) {
                    qDebug() << "Move to top over";
                    // 松下左键
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    return;
                }
                break;
            case 4:// 下
                newY = newY + 1;
                // 判断是否移动到最下边
                if (newY > screenHeight) {
                    qDebug() << "Move to bottom over";
                    // 松下左键
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    return;
                }
                break;
            default:
                qDebug() << "Error direction:" << direction;
                // 松下左键
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                return;
        }
        qDebug() << "Move Mouse Position:" << newX << newY;
        // 移动鼠标到指定位置
        MouseSimulator::moveCursor(newX, newY);
    }
    // 松下左键
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    qDebug() << "leftDrag end";
}

// 右键单击
void MouseSimulator::rightClick() {
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

// 右键点击拖动
void MouseSimulator::rightDrag(int startX, int startY, int endX, int endY) {
    SetCursorPos(startX, startY);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    Sleep(100); // 一些时间间隔
    SetCursorPos(endX, endY);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

// 滚轮放大 (滚轮向上滚动)
void MouseSimulator::wheelZoomIn() {
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA, 0);
}

// 滚轮缩小 (滚轮向下滚动)
void MouseSimulator::wheelZoomOut() {
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -WHEEL_DELTA, 0);
}

// 中键点击拖动
void MouseSimulator::middleDrag(int startX, int startY, int endX, int endY) {
    SetCursorPos(startX, startY);
    mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
    Sleep(100); // 一些时间间隔
    SetCursorPos(endX, endY);
    mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
}
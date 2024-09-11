//
// Created by ISSTECH on 2024/9/11.
//

#include "MouseSimulator.h"
#include <windows.h>

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
    Sleep(100); // 一些时间间隔
    leftClick();
}

// 左键点击拖动
void MouseSimulator::leftDrag(int startX, int startY, int endX, int endY) {
    SetCursorPos(startX, startY);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(100); // 一些时间间隔
    SetCursorPos(endX, endY);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
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
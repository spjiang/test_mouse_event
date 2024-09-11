//
// Created by ISSTECH on 2024/9/11.
//

#ifndef TEST_MOUSE_EVENT_MOUSESIMULATOR_H
#define TEST_MOUSE_EVENT_MOUSESIMULATOR_H


class MouseSimulator {
public:
    MouseSimulator();
    ~MouseSimulator();

    // 1. 光标位置移动
    static void moveCursor(int x, int y);

    // 2. 左键单击
    static void leftClick();

    // 3. 左键双击
    static void leftDoubleClick();

    // 4. 左键点击拖动
    static void leftDrag(int startX, int startY, int endX, int endY);
    // 5. 右键单击
    static void rightClick();

    // 6. 右键点击拖动
    static void rightDrag(int startX, int startY, int endX, int endY);

    // 7. 滚轮放大 (滚轮向上滚动)
    static void wheelZoomIn();

    // 8. 滚轮缩小 (滚轮向下滚动)
    static void wheelZoomOut();

    // 9. 中键点击拖动
    static void middleDrag(int startX, int startY, int endX, int endY);
};


#endif //TEST_MOUSE_EVENT_MOUSESIMULATOR_H

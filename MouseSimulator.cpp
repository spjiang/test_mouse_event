//
// Created by ISSTECH on 2024/9/11.
//

#include "MouseSimulator.h"
#include <windows.h>
#include <QDebug>
#include <chrono>
#include <thread>

// 鼠标模拟器
//void mouse_event(
//        DWORD dwFlags,   // 指定鼠标事件的类型
//        DWORD dx,        // 指定鼠标的水平位置
//        DWORD dy,        // 指定鼠标的垂直位置
//        DWORD dwData,    // 指定事件的附加信息
//        ULONG_PTR dwExtraInfo // 指定与事件相关的额外信息
//);
//dwFlags：
//
//指定鼠标事件的类型。这个参数可以是以下值的组合：
//MOUSEEVENTF_LEFTDOWN：模拟鼠标左键按下。
//MOUSEEVENTF_LEFTUP：模拟鼠标左键抬起。
//MOUSEEVENTF_RIGHTDOWN：模拟鼠标右键按下。
//MOUSEEVENTF_RIGHTUP：模拟鼠标右键抬起。
//MOUSEEVENTF_MIDDLEDOWN：模拟鼠标中键按下。
//MOUSEEVENTF_MIDDLEUP：模拟鼠标中键抬起。
//MOUSEEVENTF_XDOWN：模拟鼠标第一个X按钮按下。
//MOUSEEVENTF_XUP：模拟鼠标第一个X按钮抬起。
//MOUSEEVENTF_WHEEL：模拟鼠标滚轮滚动。
//MOUSEEVENTF_HWHEEL：模拟鼠标水平滚轮滚动（Windows XP中引入）。
//dx：
//
//指定鼠标的水平位置。对于MOUSEEVENTF_WHEEL和MOUSEEVENTF_HWHEEL事件，这个参数被忽略。
//dy：
//
//指定鼠标的垂直位置。对于MOUSEEVENTF_WHEEL和MOUSEEVENTF_HWHEEL事件，这个参数被忽略。
//dwData：
//
//指定事件的附加信息。对于MOUSEEVENTF_WHEEL事件，这个参数表示滚轮的移动量。对于其他类型的事件，这个参数可以表示点击次数（双击或单击）。
//dwExtraInfo：
//
//指定与事件相关的额外信息。通常，这个参数传递NULL或者应用程序的实例句柄。



MouseSimulator::MouseSimulator() {

}

MouseSimulator::~MouseSimulator() {

}

ScreenSize MouseSimulator::getCurrentMonitorSize() {
    ScreenSize size = {0, 0};
    // Get the cursor's current position
    POINT cursorPos;
    if (GetCursorPos(&cursorPos)) {
        // Get the monitor where the cursor is located
        HMONITOR hMonitor = MonitorFromPoint(cursorPos, MONITOR_DEFAULTTONEAREST);
        // Structure to store monitor information
        MONITORINFO monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFO);

        // Get the monitor information
        if (GetMonitorInfo(hMonitor, &monitorInfo)) {
            // Calculate the width and height of the monitor
            size.screenWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
            size.screenHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
        }
    }
    return size;
}

ScreenPosition MouseSimulator::getCursorPosInCurrentMonitor() {
    POINT pt;
    GetCursorPos(&pt);

    // 获取光标所在的显示器
    HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);

    // 获取显示器信息
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    if (GetMonitorInfo(hMonitor, &monitorInfo)) {
        // 计算相对于当前显示器的坐标
        ScreenPosition relativePos;
        relativePos.x = pt.x - monitorInfo.rcMonitor.left;
        relativePos.y = pt.y - monitorInfo.rcMonitor.top;

        return relativePos;
    }

    // 如果获取失败，返回原始坐标
    return {pt.x, pt.y};
}

// 移动光标到当前显示器上的指定位置 (相对当前显示器的坐标)
void MouseSimulator::moveCursorToMonitorPos(int newX, int newY) {
    // 获取当前光标的全局位置
    POINT pt;
    GetCursorPos(&pt);

    // 获取光标所在的显示器
    HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);

    // 获取显示器信息
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    if (GetMonitorInfo(hMonitor, &monitorInfo)) {
        // 计算相对于虚拟屏幕的全局坐标
        int globalX = monitorInfo.rcMonitor.left + newX;
        int globalY = monitorInfo.rcMonitor.top + newY;

        // 移动光标到新的全局坐标
        SetCursorPos(globalX, globalY);
    }
}

// 线性插值函数
double lerp(double start, double end, double t) {
    return start + t * (end - start);
}

// 缓动函数 (二次 Ease-In-Out)
double easeInOutQuad(double t) {
    if (t < 0.5) {
        return 2 * t * t;
    } else {
        return -1 + (4 - 2 * t) * t;
    }
}

// 三次方缓动函数 (三次 Ease-In-Out)
double easeInOutCubic(double t) {
    return t < 0.5 ? 4 * t * t * t : 1 - std::pow(-2 * t + 2, 3) / 2;
}

/**
 stride（移动的步长预值）:
    控制每次移动的距离。较大的步长会让光标移动得更快。
    例如，stride = 5 会让光标以较小的步长移动，stride = 20 则会让光标每次移动更大距离，移动会更快。
delay（步长延迟时间毫秒）:
    控制每次移动后的延迟时间。Sleep 函数控制每次移动后的停顿时间，以毫秒为单位。
    如果 delay = 1，移动非常快速；如果 delay = 10，移动速度明显变慢。

步长越大：鼠标移动速度越快。
延迟越短：鼠标移动速度越快。

快速移动：
 moveMouseToTarget(current, target, 20, 1);  // 大步长+短延迟，移动快
缓慢移动：
 moveMouseToTarget(current, target, 5, 10);  // 小步长+长延迟，移动慢
 */
void MouseSimulator::moveMouseToTargetSpeed(Point current, Point target, int stride, int delay) {

    // 获取屏幕大小
    ScreenSize screenSize = getCurrentMonitorSize();
    int screenWidth = screenSize.screenWidth;
    int screenHeight = screenSize.screenHeight;

    // 确保目标点在屏幕内
    if (target.x > screenWidth || target.y > screenHeight) {
        return;
    }

    int deltaX = target.x - current.x;
    int deltaY = target.y - current.y;

    int lastX = current.x;
    int lastY = current.y;

    // 计算总距离
    double totalDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (totalDistance == 0) return;

    const int steps = static_cast<int>(totalDistance / stride);

    // 开始缓动效果的鼠标移动
    for (int i = 0; i <= steps; ++i) {
        // 计算当前的缓动 progress 值 (使用 Ease-In-Out 缓动函数)
        double t = static_cast<double>(i) / steps;
        double easedT = easeInOutCubic(t); // 这里使用 easeInOutQuad

        // 根据缓动 progress 计算当前位置
        int newX = static_cast<int>(lerp(current.x, target.x, easedT));
        int newY = static_cast<int>(lerp(current.y, target.y, easedT));

        qDebug() << "newX newY: " << newX << ", " << newY;

        if (newX == lastX && newY == lastY) {
            // 如果新位置和当前位置相同，则跳过移动
            qDebug() << "  Skipping move to: " << newX << ", " << newY;
            continue;
        }

        // 移动鼠标到计算出的新位置
        moveCursorToMonitorPos(newX, newY);

        // 更新当前位置
        lastX = newX;
        lastY = newY;

        // 短暂延迟以实现平滑的移动效果
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    // 最终确保光标位置精确到目标点
    moveCursorToMonitorPos(target.x, target.y);
}

void MouseSimulator::moveMouseToTarget(Point current, Point target, int stride, int delay) {
    if (stride <= 0 || delay < 0) {
        qDebug() << "Invalid stride or delay values.";
        return;
    }

    ScreenSize screenSize = getCurrentMonitorSize();
    int screenWidth = screenSize.screenWidth;
    int screenHeight = screenSize.screenHeight;

    if (target.x < 0 || target.y < 0 || target.x > screenWidth || target.y > screenHeight) {
        return;
    }

    int deltaX = target.x - current.x;
    int deltaY = target.y - current.y;
    double totalDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (totalDistance == 0) return;

    double directionX = deltaX / totalDistance;
    double directionY = deltaY / totalDistance;

    while (totalDistance > stride) {
        current.x += static_cast<int>(directionX * stride);
        current.y += static_cast<int>(directionY * stride);
        qDebug() << "Moving to: " << current.x << ", " << current.y;
        moveCursorToMonitorPos(current.x, current.y);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));

        deltaX = target.x - current.x;
        deltaY = target.y - current.y;
        totalDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Check if we're very close to the target
        if (totalDistance < stride) {
            break;
        }
    }
    qDebug() << "Moving to target: " << target.x << ", " << target.y;
    moveCursorToMonitorPos(target.x, target.y);
}




// 光标位置移动
void MouseSimulator::moveCursor(int x, int y, int stride, int delay) {
    qDebug() << "mouseCode MouseEvent moveCursorFunc x y :" << x << " " << y;
    // 获取当前鼠标位置
    ScreenPosition pt = getCursorPosInCurrentMonitor();
    Point start = {pt.x, pt.y};
    // 打印当前鼠标位置
    qDebug() << "mouseCode MouseEvent moveCursorFunc func Current Mouse Position" << pt.x << pt.y;
    int newX = pt.x + x;
    int newY = pt.y + y;
    qDebug() << "mouseCode MouseEvent moveCursorFunc new Mouse Position-1" << newX << newY;
    // 获取屏幕大小
    ScreenSize screenSize = getCurrentMonitorSize();
    int screenWidth = screenSize.screenWidth;
    int screenHeight = screenSize.screenHeight;
    qDebug() << "mouseCode MouseEvent moveCursorFunc screenWidth screenHeight:" << screenWidth << " " << screenHeight;

    if (newX < 0) {
        newX = 0;
    }
    if (newY < 0) {
        newY = 0;
    }

    if (newX > screenWidth) {
        newX = screenWidth;
    }

    if (newY > screenHeight) {
        newY = screenHeight;
    }

    qDebug() << "mouseCode MouseEvent moveCursorFunc new Mouse Position-2" << newX << newY;

    // 移动鼠标到指定位置
    Point end = {newX, newY};

    // 移动鼠标到指定位置
    moveMouseToTarget(start, end, stride, delay);

    qDebug() << "mouseCode MouseEvent moveCursorFunc success";
}

// 左键单击
void MouseSimulator::leftClick() {
    qDebug() << "mouseCode MouseEvent leftClickFunc";
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    qDebug() << "mouseCode MouseEvent leftClickFunc success";
}

// 左键双击
void MouseSimulator::leftDoubleClick() {
    qDebug() << "mouseCode MouseEvent leftDoubleClickFunc";
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    qDebug() << "mouseCode MouseEvent leftDoubleClickFunc success";
}

// 左键点击拖动
void MouseSimulator::leftDrag(int x, int y, int stride, int delay) {
    qDebug() << "mouseCode MouseEvent leftDragFunc x y :" << x << " " << y;
    // 获取当前鼠标位置
    ScreenPosition pt = getCursorPosInCurrentMonitor();
    Point start = {pt.x, pt.y};

    // 打印当前鼠标位置
    qDebug() << "mouseCode MouseEvent leftDragFunc Current Mouse Position:" << pt.x << pt.y;
    int newX = pt.x + x;
    int newY = pt.y + y;
    qDebug() << "mouseCode MouseEvent leftDragFunc new Mouse Position-1:" << newX << newY;

    // 获取屏幕大小
    ScreenSize screenSize = getCurrentMonitorSize();
    int screenWidth = screenSize.screenWidth;
    int screenHeight = screenSize.screenHeight;

    qDebug() << "mouseCode MouseEvent leftDragFunc screenWidth screenHeight:" << screenWidth << " " << screenHeight;

    if (newX < 0) {
        newX = 0;
    }
    if (newY < 0) {
        newY = 0;
    }

    if (newX > screenWidth) {
        newX = screenWidth;
    }

    if (newY > screenHeight) {
        newY = screenHeight;
    }
    qDebug() << "mouseCode MouseEvent leftDragFunc new Mouse Position-2" << newX << newY;
    // 移动鼠标到指定位置
    Point end = {newX, newY};
    // 移动鼠标到指定位置
    moveMouseToTarget(start, end, stride, delay);
    qDebug() << "mouseCode MouseEvent leftDragFunc success";
}

// 右键单击
void MouseSimulator::rightClick(GestureData gestureData) {
    qDebug() << "mouseCode MouseEvent rightClickFunc";
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    qDebug() << "mouseCode MouseEvent rightClickFunc success";
}

// 右键点击拖动
void MouseSimulator::rightDrag(int x, int y, int stride, int delay) {
    qDebug() << "mouseCode MouseEvent rightDragFunc x y :" << x << " " << y;
    // 获取当前鼠标位置
    ScreenPosition pt = getCursorPosInCurrentMonitor();
    Point start = {pt.x, pt.y};

    // 打印当前鼠标位置
    qDebug() << "mouseCode MouseEvent rightDragFunc Current Mouse Position:" << pt.x << pt.y;
    int newX = pt.x + x;
    int newY = pt.y + y;
    qDebug() << "mouseCode MouseEvent rightDragFunc new Mouse Position-1:" << newX << newY;

    // 获取屏幕大小
    ScreenSize screenSize = getCurrentMonitorSize();
    int screenWidth = screenSize.screenWidth;
    int screenHeight = screenSize.screenHeight;
    qDebug() << "mouseCode MouseEvent rightDragFunc screenWidth screenHeight:" << screenWidth << " " << screenHeight;

    if (newX < 0) {
        newX = 0;
    }
    if (newY < 0) {
        newY = 0;
    }

    if (newX > screenWidth) {
        newX = screenWidth;
    }

    if (newY > screenHeight) {
        newY = screenHeight;
    }
    qDebug() << "mouseCode MouseEvent rightDragFunc new Mouse Position-2" << newX << newY;

    // 移动鼠标到指定位置
    Point end = {newX, newY};

    // 移动鼠标到指定位置
    moveMouseToTarget(start, end, stride, delay);

    qDebug() << "mouseCode MouseEvent rightDragFunc success";
}


// 滚轮放大 (滚轮向上滚动)
void MouseSimulator::wheelZoomIn(float mult_wheel_delta) {
    qDebug() << "mouseCode MouseEvent wheelZoomInFunc mult_wheel_delta:" << mult_wheel_delta;
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, mult_wheel_delta * WHEEL_DELTA, 0);
    qDebug() << "mouseCode MouseEvent wheelZoomInFunc success";
}

// 滚轮缩小 (滚轮向下滚动)
void MouseSimulator::wheelZoomOut(float mult_wheel_delta) {
    qDebug() << "mouseCode MouseEvent wheelZoomOutFunc mult_wheel_delta:" << mult_wheel_delta;
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -mult_wheel_delta * WHEEL_DELTA, 0);
    qDebug() << "mouseCode MouseEvent wheelZoomOutFunc success";
}

// 中键点击拖动
void MouseSimulator::middleDrag(int x, int y, int stride, int delay) {
    qDebug() << "mouseCode MouseEvent middleDragFunc x y :" << x << " " << y;
    // 获取当前鼠标位置
    ScreenPosition pt = getCursorPosInCurrentMonitor();
    Point start = {pt.x, pt.y};

    // 打印当前鼠标位置
    qDebug() << "mouseCode MouseEvent middleDragFunc Current Mouse Position:" << pt.x << pt.y;
    int newX = pt.x + x;
    int newY = pt.y + y;
    qDebug() << "mouseCode MouseEvent middleDragFunc new Mouse Position-1:" << newX << newY;


    // 获取屏幕大小
    ScreenSize screenSize = getCurrentMonitorSize();
    int screenWidth = screenSize.screenWidth;
    int screenHeight = screenSize.screenHeight;
    qDebug() << "mouseCode MouseEvent leftDragFunc screenWidth screenHeight:" << screenWidth << " " << screenHeight;
    if (newX < 0) {
        newX = 0;
    }
    if (newY < 0) {
        newY = 0;
    }

    if (newX > screenWidth) {
        newX = screenWidth;
    }

    if (newY > screenHeight) {
        newY = screenHeight;
    }
    qDebug() << "mouseCode MouseEvent middleDragFunc new Mouse Position-2:" << newX << newY;
    // 移动鼠标到指定位置
    Point end = {newX, newY};

    // 移动鼠标到指定位置
    moveMouseToTarget(start, end, stride, delay);

    qDebug() << "mouseCode MouseEvent middleDragFunc middleDrag success";
}
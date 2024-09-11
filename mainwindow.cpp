// mainwindow.cpp
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseSimulator.h"
#include <chrono>
#include <thread>
#include <windows.h>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("鼠标+键盘模拟器"));

    // 光标位置移动
    connect(ui->moveCursor_left, &QAction::triggered, this, &MainWindow::onActionMoveCursorLeftTriggered);
    connect(ui->moveCursor_right, &QAction::triggered, this, &MainWindow::onActionMoveCursorRightTriggered);
    connect(ui->moveCursor_up, &QAction::triggered, this, &MainWindow::onActionMoveCursorUpTriggered);
    connect(ui->moveCursor_down, &QAction::triggered, this, &MainWindow::onActionMoveCursorDownTriggered);

    // 左键单击
    connect(ui->leftClick, &QAction::triggered, this, &MainWindow::onActionLeftClickTriggered);

    // 左键双击
    connect(ui->leftDoubleClick, &QAction::triggered, this, &MainWindow::onActionLeftDoubleClickTriggered);


    // 左键点击拖动
    connect(ui->leftDrag_left, &QAction::triggered, this, &MainWindow::onActionLeftDragLeftTriggered);
    connect(ui->leftDrag_right, &QAction::triggered, this, &MainWindow::onActionLeftDragRightTriggered);
    connect(ui->leftDrag_up, &QAction::triggered, this, &MainWindow::onActionLeftDragUpTriggered);
    connect(ui->leftDrag_down, &QAction::triggered, this, &MainWindow::onActionLeftDragDownTriggered);



    // 右键单击
    connect(ui->rightClick, &QAction::triggered, this, &MainWindow::onActionRightClickTriggered);
    // 右键点击拖动
    connect(ui->rightDrag_left, &QAction::triggered, this, &MainWindow::onActionRightDragTriggered);
    // 滚轮放大 (滚轮向上滚动)
    connect(ui->wheelZoomIn, &QAction::triggered, this, &MainWindow::onActionWheelZoomInTriggered);
    // 滚轮缩小 (滚轮向下滚动)
    connect(ui->wheelZoomOut, &QAction::triggered, this, &MainWindow::onActionWheelZoomOutTriggered);
    // 中键点击拖动
    connect(ui->middleDrag, &QAction::triggered, this, &MainWindow::onActionMiddleDragTriggered);

    connect(ui->startTest, &QPushButton::clicked, this, &MainWindow::onStartTest);
}

MainWindow::~MainWindow() = default;


// -----------------公共参数：手势Code--------------------

// 光标位置移动
// 参数：
// direction：方向（left-1/right-2/up-3/down-4）
// moveLong：移动的距离
// speed：移动的速度（毫秒）
void MainWindow::onActionMoveCursorLeftTriggered() {
    // 移动鼠标向左移动，接口告诉我移动100像素。
    int moveLong = 100;
    int direction = 1;
    int speed = 2;

    // 获取当前鼠标位置
    POINT pt;
    GetCursorPos(&pt);

    // 打印当前鼠标位置
    qDebug() << "Current Mouse Position:" << pt.x << pt.y;
    int newX = pt.x;
    int newY = pt.y;

    // 暂停3秒
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // 打印开始移动鼠标的信息
    qDebug() << "onActionMoveCursorLeftTriggered-start";

    for (int i = 1; i < moveLong; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        // 每次移动一个像素，避免鼠标跳动
        newX = newX - 1;
        qDebug() << "Move Mouse Position:" << newX << newY;
        // 判断是否移动到最左边
        if (newX < 0) {
            break;
        }
        MouseSimulator::moveCursor(newX, newY);
    }
    // 打印移动完成的信息
    qDebug() << "onActionMoveCursorLeftTriggered-end";
}

void MainWindow::onActionMoveCursorRightTriggered() {

    int moveLong = 100;
    int direction = 2;
    int speed = 2;

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
    qDebug() << "Screen Size:" << screenWidth << "x" << screenHeight;

    // 暂停3秒
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // 打印开始移动鼠标的信息
    qDebug() << "onActionMoveCursorRightTriggered-start";

    for (int i = 1; i < moveLong; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        // 每次移动一个像素，避免鼠标跳动
        newX = newX + 1;
        qDebug() << "Move Mouse Position:" << newX << newY;
        // 判断是否移动到最左边
        if (newX > screenWidth) {
            break;
        }
        MouseSimulator::moveCursor(newX, newY);
    }
    // 打印移动完成的信息
    qDebug() << "onActionMoveCursorRightTriggered-end";
}

void MainWindow::onActionMoveCursorUpTriggered() {

    int moveLong = 100;
    int direction = 3;
    int speed = 2;

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
    qDebug() << "Screen Size:" << screenWidth << "x" << screenHeight;

    // 暂停3秒
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // 打印开始移动鼠标的信息
    qDebug() << "onActionMoveCursorUpTriggered-start";
    for (int i = 1; i < moveLong; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        // 每次移动一个像素，避免鼠标跳动
        newY = newY - 1;
        qDebug() << "Move Mouse Position:" << newX << newY;
        // 判断是否移动到最上边
        if (newY == 0) {
            break;
        }
        MouseSimulator::moveCursor(newX, newY);
    }
    // 打印移动完成的信息
    qDebug() << "onActionMoveCursorUpTriggered-end";
}

void MainWindow::onActionMoveCursorDownTriggered() {

    int moveLong = 100;
    int direction = 4;
    int speed = 2;

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
    qDebug() << "Screen Size:" << screenWidth << "x" << screenHeight;

    // 暂停3秒
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // 打印开始移动鼠标的信息
    qDebug() << "onActionMoveCursorDownTriggered-start";

    for (int i = 1; i < moveLong; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        // 每次移动一个像素，避免鼠标跳动
        newY = newY + 1;
        qDebug() << "Move Mouse Position:" << newX << newY;
        // 判断是否移动到最上边
        if (newY > screenHeight) {
            break;
        }
        MouseSimulator::moveCursor(newX, newY);
    }
    // 打印移动完成的信息
    qDebug() << "onActionMoveCursorDownTriggered-end";
}

// 左键单击
void MainWindow::onActionLeftClickTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftClickTriggered-start";
    MouseSimulator::leftClick();
    qDebug() << "onActionLeftClickTriggered-end";
}

// 左键双击
void MainWindow::onActionLeftDoubleClickTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftDoubleClickTriggered-start";
    MouseSimulator::leftDoubleClick();
    qDebug() << "onActionLeftDoubleClickTriggered-end";
}

// 左键点击拖动
// 参数：起始位置x, 起始位置y, 结束位置x, 结束位置y
void MainWindow::onActionLeftDragLeftTriggered() {

    int moveLong = 100;
    int direction = 1;
    int speed = 2;

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftDragLeftTriggered-start";
    MouseSimulator::leftDrag(moveLong,direction,speed);
    qDebug() << "onActionLeftDragLeftTriggered-end";
}

void MainWindow::onActionLeftDragRightTriggered() {
    int moveLong = 100;
    int direction = 2;
    int speed = 2;

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftDragRightTriggered-start";
    MouseSimulator::leftDrag(moveLong,direction,speed);
    qDebug() << "onActionLeftDragRightTriggered-end";
}
void MainWindow::onActionLeftDragUpTriggered() {
    int moveLong = 100;
    int direction = 3;
    int speed = 2;

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftDragUpTriggered-start";
    MouseSimulator::leftDrag(moveLong,direction,speed);
    qDebug() << "onActionLeftDragUpTriggered-end";
}
void MainWindow::onActionLeftDragDownTriggered() {
    int moveLong = 100;
    int direction = 4;
    int speed = 2;

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftDragDownTriggered-start";
    MouseSimulator::leftDrag(moveLong,direction,speed);
    qDebug() << "onActionLeftDragDownTriggered-end";
}


// 右键单击
void MainWindow::onActionRightClickTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionRightClickTriggered-start";
    MouseSimulator::rightClick();
    qDebug() << "onActionRightClickTriggered-end";
}

// 右键点击拖动
void MainWindow::onActionRightDragTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionRightDragTriggered-start";
    MouseSimulator::rightDrag(500, 500, 600, 600);
    qDebug() << "onActionRightDragTriggered-end";
}

// 滚轮放大 (滚轮向上滚动)
void MainWindow::onActionWheelZoomInTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionWheelZoomInTriggered-start";
    MouseSimulator::wheelZoomIn();
    qDebug() << "onActionWheelZoomInTriggered-end";
}

// 滚轮缩小 (滚轮向下滚动)
void MainWindow::onActionWheelZoomOutTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionWheelZoomOutTriggered-start";
    MouseSimulator::wheelZoomOut();
    qDebug() << "onActionWheelZoomOutTriggered-end";
}

// 中键点击拖动
void MainWindow::onActionMiddleDragTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionMiddleDragTriggered-start";
    MouseSimulator::middleDrag(500, 500, 600, 600);
    qDebug() << "onActionMiddleDragTriggered-end";
}

void MainWindow::onStartTest() {
    //    qDebug() << "++++++++++++startTest++++++++++++";
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //    qDebug() << "1:moveCursor: (500, 500)";
    //    // 示例1：移动光标到 (500, 500) 位置
    //    MouseSimulator::moveCursor(500, 500);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //    // 示例2：模拟左键单击
    //    qDebug() << "2:leftClick";
    //    MouseSimulator::leftClick();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //    // 示例3：左键双击
    //    qDebug() << "3:leftDoubleClick";
    //    MouseSimulator::leftDoubleClick();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //
    //    // 示例4：模拟左键点击并拖动
    //    qDebug() << "4:leftDrag";
    //    MouseSimulator::leftDrag(500, 500, 600, 600);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //
    //    // 示例5：右键单击
    //    qDebug() << "5:rightClick";
    //    MouseSimulator::rightClick();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //    // 示例6: 右键点击拖动
    //    qDebug() << "6:rightDrag";
    //    MouseSimulator::rightDrag(500, 500, 600, 600);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //    // 示例7：模拟滚轮放大
    //    qDebug() << "7:wheelZoomIn";
    //    MouseSimulator::wheelZoomIn();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //    // 示例8: 滚轮缩小 (滚轮向下滚动)
    //    qDebug() << "8:wheelZoomOut";
    //    MouseSimulator::wheelZoomOut();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //
    //    // 示例9：模拟中键点击拖动
    //    qDebug() << "9:middleDrag";
    //    MouseSimulator::middleDrag(500, 500, 600, 600);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}


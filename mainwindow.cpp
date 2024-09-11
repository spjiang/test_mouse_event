// mainwindow.cpp
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseSimulator.h"
#include <chrono>
#include <thread>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("鼠标+键盘模拟器"));
    qDebug() << "Hello, Qt!";

    // 光标位置移动
    connect(ui->moveCursor, &QAction::triggered, this, &MainWindow::onActionMoveCursorTriggered);
    // 左键单击
    connect(ui->leftClick, &QAction::triggered, this, &MainWindow::onActionLeftClickTriggered);
    // 左键双击
    connect(ui->leftDoubleClick, &QAction::triggered, this, &MainWindow::onActionLeftDoubleClickTriggered);
    // 左键点击拖动
    connect(ui->leftDrag, &QAction::triggered, this, &MainWindow::onActionLeftDragTriggered);
    // 右键单击
    connect(ui->rightClick, &QAction::triggered, this, &MainWindow::onActionRightClickTriggered);
    // 右键点击拖动
    connect(ui->rightDrag, &QAction::triggered, this, &MainWindow::onActionRightDragTriggered);
    // 滚轮放大 (滚轮向上滚动)
    connect(ui->wheelZoomIn, &QAction::triggered, this, &MainWindow::onActionWheelZoomInTriggered);
    // 滚轮缩小 (滚轮向下滚动)
    connect(ui->wheelZoomOut, &QAction::triggered, this, &MainWindow::onActionWheelZoomOutTriggered);
    // 中键点击拖动
    connect(ui->middleDrag, &QAction::triggered, this, &MainWindow::onActionMiddleDragTriggered);

    connect(ui->startTest, &QPushButton::clicked, this, &MainWindow::onStartTest);
}

MainWindow::~MainWindow() = default;


// 光标位置移动
//
void MainWindow::onActionMoveCursorTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionMoveCursorTriggered-start";
    MouseSimulator::moveCursor(500, 500);
    qDebug() << "onActionMoveCursorTriggered-end";
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
void MainWindow::onActionLeftDragTriggered() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    qDebug() << "onActionLeftDragTriggered-start";
    MouseSimulator::leftDrag(500, 500, 600, 600);
    qDebug() << "onActionLeftDragTriggered-end";
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
    qDebug() << "++++++++++++startTest++++++++++++";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    qDebug() << "1:moveCursor: (500, 500)";
    // 示例1：移动光标到 (500, 500) 位置
    MouseSimulator::moveCursor(500, 500);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // 示例2：模拟左键单击
    qDebug() << "2:leftClick";
    MouseSimulator::leftClick();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // 示例3：左键双击
    qDebug() << "3:leftDoubleClick";
    MouseSimulator::leftDoubleClick();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));


    // 示例4：模拟左键点击并拖动
    qDebug() << "4:leftDrag";
    MouseSimulator::leftDrag(500, 500, 600, 600);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));


    // 示例5：右键单击
    qDebug() << "5:rightClick";
    MouseSimulator::rightClick();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // 示例6: 右键点击拖动
    qDebug() << "6:rightDrag";
    MouseSimulator::rightDrag(500, 500, 600, 600);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // 示例7：模拟滚轮放大
    qDebug() << "7:wheelZoomIn";
    MouseSimulator::wheelZoomIn();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // 示例8: 滚轮缩小 (滚轮向下滚动)
    qDebug() << "8:wheelZoomOut";
    MouseSimulator::wheelZoomOut();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // 示例9：模拟中键点击拖动
    qDebug() << "9:middleDrag";
    MouseSimulator::middleDrag(500, 500, 600, 600);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}


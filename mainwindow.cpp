// mainwindow.cpp
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseSimulator.h"

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
}

MainWindow::~MainWindow() = default;

void MainWindow::onActionMoveCursorTriggered() {
    MouseSimulator::moveCursor(500, 500);
}

void MainWindow::onActionLeftClickTriggered() {
    MouseSimulator::leftClick();
}

void MainWindow::onActionLeftDoubleClickTriggered() {
    MouseSimulator::leftDoubleClick();
}

void MainWindow::onActionLeftDragTriggered() {
    MouseSimulator::leftDrag(500, 500, 600, 600);
}

void MainWindow::onActionRightClickTriggered() {
    MouseSimulator::rightClick();
}

void MainWindow::onActionRightDragTriggered() {
    MouseSimulator::rightDrag(500, 500, 600, 600);
}

void MainWindow::onActionWheelZoomInTriggered() {
    MouseSimulator::wheelZoomIn();
}

void MainWindow::onActionWheelZoomOutTriggered() {
    MouseSimulator::wheelZoomOut();
}

void MainWindow::onActionMiddleDragTriggered() {
    MouseSimulator::middleDrag(500, 500, 600, 600);
}


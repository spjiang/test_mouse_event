// mainwindow.cpp
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseSimulator.h"
#include <chrono>
#include <thread>
#include <windows.h>

MainWindow &MainWindow::singleton() {
    static auto *instance = new MainWindow;
    return *instance;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("鼠标+键盘模拟器"));

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

    connect(ui->submit, &QPushButton::clicked, this, &MainWindow::onSubmit);
}


void MainWindow::clearMouseEventStatus() {
    INPUT inputs[3] = {};

    // 模拟鼠标左键释放
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    // 模拟鼠标右键释放
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    // 模拟鼠标中键释放
    inputs[2].type = INPUT_MOUSE;
    inputs[2].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;

    // 发送输入
    SendInput(3, inputs, sizeof(INPUT));

    // 延时
    std::this_thread::sleep_for(std::chrono::milliseconds(m_clearEventSleepTime));
}

void MainWindow::onSubmit() {
    m_targetMoveX = ui->target_move_x->text().toInt();
    m_targetMoveY = ui->target_move_y->text().toInt();
    m_eventDownSleepTime = ui->event_down_sleep_time->text().toInt();
    m_clearEventSleepTime = ui->clear_event_sleep_time->text().toInt();
    m_forCnt = ui->for_cnt->text().toInt();
    m_stride = ui->stride->text().toInt();
    m_strideDelay = ui->stride_delay->text().toInt();
    m_frameInterval = ui->frame_interval->text().toInt();
    m_wheelZoomInMultWheelDelta = ui->wheelZoomIn_mult_wheel_delta->text().toInt();
    m_wheelZoomOutMultWheelDelta = ui->wheelZoomOut_mult_wheel_delta->text().toInt();
};

MainWindow::~MainWindow() = default;


// -----------------公共参数：手势Code--------------------

void MainWindow::onActionMoveCursorTriggered() {
    qDebug() << "onActionMoveCursorTriggered-start";
    Sleep(5000);
    clearMouseEventStatus();
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        MouseSimulator::moveCursor(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }
    qDebug() << "onActionMoveCursorriggered-end";
}

void MainWindow::onActionLeftClickTriggered() {
    Sleep(5000);
    qDebug() << "onActionLeftClickTriggered-start";
    clearMouseEventStatus();
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        MouseSimulator::leftClick();
    }
    qDebug() << "onActionLeftClickTriggered-end";
}

void MainWindow::onActionLeftDoubleClickTriggered() {
    Sleep(5000);
    qDebug() << "onActionLeftDoubleClickTriggered-start";

    clearMouseEventStatus();
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        MouseSimulator::leftDoubleClick();
    }
    qDebug() << "onActionLeftDoubleClickTriggered-end";
}

void MainWindow::onActionMiddleDragTriggered() {
    Sleep(5000);
    qDebug() << "onActionMiddleDragTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));

        INPUT inputs[3] = {};

        // 模拟鼠标左键释放
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // 模拟鼠标右键释放
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

        // 模拟鼠标中键按下
        inputs[2].type = INPUT_MOUSE;
        inputs[2].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;

        // 发送输入
        SendInput(3, inputs, sizeof(INPUT));

        MouseSimulator::middleDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }

    qDebug() << "onActionMiddleDragTriggered-end";
}

void MainWindow::onActionLeftDragTriggered() {
    Sleep(5000);
    qDebug() << "onActionLeftDragTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        INPUT inputs[3] = {};

        // 模拟鼠标右键释放
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

        // 模拟鼠标中键释放
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;

        // 模拟鼠标左键按下
        inputs[2].type = INPUT_MOUSE;
        inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        // 发送输入
        SendInput(3, inputs, sizeof(INPUT));

        MouseSimulator::leftDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }
    qDebug() << "onActionLeftDragTriggered-end";
}

void MainWindow::onActionWheelZoomOutTriggered() {
    Sleep(5000);
    qDebug() << "onActionWheelZoomOutTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        // 清空鼠标状态
        MAIN.clearMouseEventStatus();

        // 触发鼠标事件
        MouseSimulator::wheelZoomOut(MAIN.m_wheelZoomOutMultWheelDelta);
    }
    qDebug() << "onActionWheelZoomOutTriggered-end";

}

void MainWindow::onActionWheelZoomInTriggered() {
    Sleep(5000);
    qDebug() << "onActionWheelZoomInTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        // 清空鼠标状态
        MAIN.clearMouseEventStatus();
        // 触发鼠标事件
        MouseSimulator::wheelZoomIn(MAIN.m_wheelZoomInMultWheelDelta);
    }
    qDebug() << "onActionWheelZoomInTriggered-end";
}

void MainWindow::onActionRightDragTriggered() {
    Sleep(5000);
    qDebug() << "onActionRightDragTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        INPUT inputs[3] = {};

        // 模拟鼠标中键释放
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;

        // 模拟鼠标左键释放
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // 按下右键
        inputs[2].type = INPUT_MOUSE;
        inputs[2].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

        // 发送输入
        SendInput(3, inputs, sizeof(INPUT));

        MouseSimulator::rightDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }

    qDebug() << "onActionRightDragTriggered-end";

}

void MainWindow::onActionRightClickTriggered() {
    Sleep(5000);
    qDebug() << "onActionRightClickTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        // 清空鼠标状态
        MAIN.clearMouseEventStatus();

        // 触发鼠标事件
        GestureData gestureData;
        MouseSimulator::rightClick(gestureData);
    }
    qDebug() << "onActionRightClickTriggered-end";
}


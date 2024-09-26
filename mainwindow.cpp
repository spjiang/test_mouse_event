// mainwindow.cpp
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseSimulator.h"
#include <chrono>
#include <thread>
#include <windows.h>
#include <QMessageBox>
#include <QThread>

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


void MainWindow::clearMouseEventStatus(QString mouseCode) {
    if (mouseCode == "rightDrag") {
        for (int i = 0; i < m_leftDragPutDownCount; ++i) {
            // 模拟鼠标左键释放
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        for (int i = 0; i < m_middleDragPutDownCount; ++i) {
            // 模拟鼠标中键释放
            mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        }
        m_leftDragPutDownCount = 0;
        m_middleDragPutDownCount = 0;

    } else if (mouseCode == "leftDrag") {
        for (int i = 0; i < m_rightDragPutDownCount; ++i) {
            // 模拟鼠标右键释放
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        for (int i = 0; i < m_middleDragPutDownCount; ++i) {
            // 模拟鼠标中键释放
            mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        }
        m_rightDragPutDownCount = 0;
        m_middleDragPutDownCount = 0;
    } else if (mouseCode == "middleDrag") {
        for (int i = 0; i < m_leftDragPutDownCount; ++i) {
            // 模拟鼠标左键释放
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        for (int i = 0; i < m_rightDragPutDownCount; ++i) {
            // 模拟鼠标右键释放
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        m_leftDragPutDownCount = 0;
        m_rightDragPutDownCount = 0;
    } else {
        for (int i = 0; i < m_leftDragPutDownCount; ++i) {
            // 模拟鼠标左键释放
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        for (int i = 0; i < m_rightDragPutDownCount; ++i) {
            // 模拟鼠标右键释放
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        for (int i = 0; i < m_middleDragPutDownCount; ++i) {
            // 模拟鼠标中键释放
            mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        }
        m_leftDragPutDownCount = 0;
        m_rightDragPutDownCount = 0;
        m_middleDragPutDownCount = 0;
    }
}

void MainWindow::onSubmit() {
    m_targetMoveX = ui->target_move_x->text().toInt();
    m_targetMoveY = ui->target_move_y->text().toInt();
    m_mouseEventPutdownSleepTime = ui->event_down_sleep_time->text().toInt();
    m_mouseEventSleepTime = ui->clear_event_sleep_time->text().toInt();
    m_forCnt = ui->for_cnt->text().toInt();
    m_stride = ui->stride->text().toInt();
    m_strideDelay = ui->stride_delay->text().toInt();
    m_frameInterval = ui->frame_interval->text().toInt();
    m_wheelZoomInMultWheelDelta = ui->wheelZoomIn_mult_wheel_delta->text().toInt();
    m_wheelZoomOutMultWheelDelta = ui->wheelZoomOut_mult_wheel_delta->text().toInt();

    QMessageBox::information(this, "参数设置", "参数设置成功");
};

MainWindow::~MainWindow() = default;


// 函数用于清空由 mouse_event 产生的鼠标消息
void MainWindow::ClearMouseEvents() {
    qDebug() << "ClearMouseEvents";
    MSG msg;
    bool cleared = false; // 标记是否清空了事件

    // 循环检查消息队列中的鼠标消息
    while (PeekMessage(&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE)) {
        qDebug() << "Cleared Mouse Event:" << msg.message;
        cleared = true; // 标记已清空事件
    }

    if (cleared) {
        qDebug() << "Mouse events cleared successfully.";
    } else {
        qDebug() << "No mouse events to clear.";
    }
}



// -----------------公共参数：手势Code--------------------

void MainWindow::onActionMoveCursorTriggered() {
    qDebug() << "onActionMoveCursorTriggered-start";
    Sleep(3000);
    clearMouseEventStatus("MoveCursor");
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        MouseSimulator::moveCursor(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }
    qDebug() << "onActionMoveCursorriggered-end";
}

void MainWindow::onActionLeftClickTriggered() {
    Sleep(3000);
    qDebug() << "onActionLeftClickTriggered-start";
    clearMouseEventStatus("LeftClick");
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        MouseSimulator::leftClick();
    }
    qDebug() << "onActionLeftClickTriggered-end";
}

void MainWindow::onActionLeftDoubleClickTriggered() {
    Sleep(3000);
    qDebug() << "onActionLeftDoubleClickTriggered-start";

    clearMouseEventStatus("DoubleClick");
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
        MouseSimulator::leftDoubleClick();
    }
    qDebug() << "onActionLeftDoubleClickTriggered-end";
}

void MainWindow::onActionMiddleDragTriggered() {
    QThread::msleep(3000);
    qDebug() << "onActionMiddleDragTriggered-start";

    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;

        // 清空鼠标事件
        clearMouseEventStatus("middleDrag");
        // 模拟中键拖动
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
        MouseSimulator::middleDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
        QThread::msleep(m_mouseEventPutdownSleepTime);
        m_middleDragPutDownCount++;

        // 清空鼠标事件
        clearMouseEventStatus("rightDrag");
        // 模拟右键拖动
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        m_rightDragPutDownCount++;
        MouseSimulator::rightDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
        QThread::msleep(m_mouseEventPutdownSleepTime);
        // 模拟右键拖动
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        m_rightDragPutDownCount++;
        MouseSimulator::rightDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
        QThread::msleep(m_mouseEventPutdownSleepTime);
        // 模拟右键拖动
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        m_rightDragPutDownCount++;
        MouseSimulator::rightDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
        QThread::msleep(m_mouseEventPutdownSleepTime);

        // 清空鼠标事件
        clearMouseEventStatus("leftDrag");
        // 模拟左键拖动
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        MouseSimulator::leftDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
        QThread::msleep(m_mouseEventPutdownSleepTime);
    }

    qDebug() << "onActionMiddleDragTriggered-end";
}


void MainWindow::onActionLeftDragTriggered() {
    Sleep(3000);
    qDebug() << "onActionLeftDragTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));

        // 模拟鼠标右键释放
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        // 延时
        std::this_thread::sleep_for(std::chrono::milliseconds(MAIN.m_mouseEventSleepTime));
        // 模拟鼠标中键释放
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        // 延时
        std::this_thread::sleep_for(std::chrono::milliseconds(MAIN.m_mouseEventSleepTime));

        // 按下左键
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        // 延时
        std::this_thread::sleep_for(std::chrono::milliseconds(MAIN.m_mouseEventPutdownSleepTime));

        MouseSimulator::leftDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }
    qDebug() << "onActionLeftDragTriggered-end";
}

void MainWindow::onActionRightDragTriggered() {
    Sleep(3000);
    qDebug() << "onActionRightDragTriggered-start";
    for (int i = 0; i < m_forCnt; ++i) {
        qDebug() << "for i=" << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));

        // 模拟鼠标左键释放
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        // 延时
        std::this_thread::sleep_for(std::chrono::milliseconds(MAIN.m_mouseEventSleepTime));
        // 模拟鼠标中键释放
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        // 延时
        std::this_thread::sleep_for(std::chrono::milliseconds(MAIN.m_mouseEventSleepTime));
        // 按下右键
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        // 延时
        std::this_thread::sleep_for(std::chrono::milliseconds(MAIN.m_mouseEventPutdownSleepTime));

        MouseSimulator::rightDrag(m_targetMoveX, m_targetMoveY, m_stride, m_strideDelay);
    }

    qDebug() << "onActionRightDragTriggered-end";

}

void MainWindow::onActionWheelZoomOutTriggered() {
    Sleep(3000);
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
    Sleep(3000);
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

void MainWindow::onActionRightClickTriggered() {
    Sleep(3000);
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


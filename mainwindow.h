#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


struct GestureData {
    int32_t x;      // 追踪的人体框数据的x坐标
    int32_t y;      // 追踪的人体框数据的y坐标
    int32_t w;      // 追踪的人体框数据的宽度
    int32_t h;      // 追踪的人体框数据的高度
    int32_t action_id; // -1为无效，0,1,2,3 分别为左右上下
    int32_t left_right; // 左右手
    float score;       // 识别置信度

    int left_gesture; //  -1为无效1为左键拖动 2为右键拖动 3为放大或缩小 4为光标移动5为单击 6为双击
    int right_gesture; //同上
    float left_value_x;	// 左手x方向动作数值
    float left_value_y;	// 左手y方向动作数值
    float right_value_x;	// 右手x方向动作数值
    float right_value_y;	// 右手y方向动作数值
    float body_scale;	// 身体比例系数
};
struct MouseEventFlag {
    QString mouseCode;
    QTime triggeredTime;
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
public slots:

    void onActionMoveCursorLeftTriggered();
    void onActionMoveCursorRightTriggered();
    void onActionMoveCursorUpTriggered();
    void onActionMoveCursorDownTriggered();



    void onActionLeftClickTriggered();
    void onActionLeftDoubleClickTriggered();


    void onActionLeftDragLeftTriggered();
    void onActionLeftDragRightTriggered();
    void onActionLeftDragUpTriggered();
    void onActionLeftDragDownTriggered();



    void onActionRightClickTriggered();
    void onActionRightDragTriggered();
    void onActionWheelZoomInTriggered();
    void onActionWheelZoomOutTriggered();
    void onActionMiddleDragTriggered();
    void onStartTest();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
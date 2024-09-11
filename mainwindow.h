#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

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
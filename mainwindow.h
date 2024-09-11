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
    void onActionMoveCursorTriggered();
    void onActionLeftClickTriggered();
    void onActionLeftDoubleClickTriggered();
    void onActionLeftDragTriggered();
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
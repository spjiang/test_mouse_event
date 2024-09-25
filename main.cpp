#include <QApplication>
#include <windows.h>
#include <QSplashScreen>
#include <QDir>
#include "mainwindow.h"

class Application : public QApplication {

public:
    MainWindow *mainWindow{nullptr};
    QSplashScreen *splashScreen{nullptr}; // 添加启动界面的指针

    Application(int &argc, char **argv) : QApplication(argc, argv) {
        auto appPath = applicationDirPath();
        QDir dir(appPath);
        qDebug() << "appPath:" << appPath << "dir.path():" << dir.path();

        SetDllDirectoryA(appPath.toLocal8Bit());
        CreateMutexA(NULL, FALSE, "MotionCtrl-Mouse-POC Running Mutex");
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            qDebug() << "Another instance is already running";
            exit(0);
        }
        setOrganizationDomain("vopoint.com");
        setApplicationName("MotionCtrl-Mouse-POC");
        // 创建启动界面
        splashScreen = new QSplashScreen(QPixmap(":/images/start.png"), Qt::WindowStaysOnTopHint);
    };

    ~Application() override {
        delete mainWindow;
        delete splashScreen; // 确保释放启动界面资源
        qDebug() << "exiting";
    }
};

int main(int argc, char *argv[]) {
    Application a(argc, argv);
    qDebug("Starting the application MotionCtrl-Mouse-POC...");
    // 启动界面
    a.splashScreen->show();
    // 创建主窗口
    a.mainWindow = &MAIN;
    // 初始化任务完成，隐藏启动界面
    a.splashScreen->finish(a.mainWindow);
    a.mainWindow->show();
    return Application::exec();
}

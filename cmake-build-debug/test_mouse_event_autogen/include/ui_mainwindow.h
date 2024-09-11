/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actioncamera;
    QAction *actionsetting;
    QAction *actionlog;
    QAction *moveCursor_left;
    QAction *leftClick;
    QAction *leftDoubleClick;
    QAction *leftDrag_left;
    QAction *rightClick;
    QAction *rightDrag_right;
    QAction *wheelZoomIn;
    QAction *wheelZoomOut;
    QAction *middleDrag;
    QAction *moveCursor_right;
    QAction *moveCursor_up;
    QAction *moveCursor_down;
    QAction *leftDrag_right;
    QAction *leftDrag_up;
    QAction *leftDrag_down;
    QAction *rightDrag_left;
    QAction *rightDrag_up;
    QAction *rightDrag_down;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPushButton *startTest;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(554, 510);
        actioncamera = new QAction(MainWindow);
        actioncamera->setObjectName("actioncamera");
        actioncamera->setMenuRole(QAction::NoRole);
        actionsetting = new QAction(MainWindow);
        actionsetting->setObjectName("actionsetting");
        actionsetting->setMenuRole(QAction::NoRole);
        actionlog = new QAction(MainWindow);
        actionlog->setObjectName("actionlog");
        actionlog->setMenuRole(QAction::NoRole);
        moveCursor_left = new QAction(MainWindow);
        moveCursor_left->setObjectName("moveCursor_left");
        leftClick = new QAction(MainWindow);
        leftClick->setObjectName("leftClick");
        leftDoubleClick = new QAction(MainWindow);
        leftDoubleClick->setObjectName("leftDoubleClick");
        leftDrag_left = new QAction(MainWindow);
        leftDrag_left->setObjectName("leftDrag_left");
        rightClick = new QAction(MainWindow);
        rightClick->setObjectName("rightClick");
        rightDrag_right = new QAction(MainWindow);
        rightDrag_right->setObjectName("rightDrag_right");
        wheelZoomIn = new QAction(MainWindow);
        wheelZoomIn->setObjectName("wheelZoomIn");
        wheelZoomOut = new QAction(MainWindow);
        wheelZoomOut->setObjectName("wheelZoomOut");
        middleDrag = new QAction(MainWindow);
        middleDrag->setObjectName("middleDrag");
        moveCursor_right = new QAction(MainWindow);
        moveCursor_right->setObjectName("moveCursor_right");
        moveCursor_up = new QAction(MainWindow);
        moveCursor_up->setObjectName("moveCursor_up");
        moveCursor_down = new QAction(MainWindow);
        moveCursor_down->setObjectName("moveCursor_down");
        leftDrag_right = new QAction(MainWindow);
        leftDrag_right->setObjectName("leftDrag_right");
        leftDrag_up = new QAction(MainWindow);
        leftDrag_up->setObjectName("leftDrag_up");
        leftDrag_down = new QAction(MainWindow);
        leftDrag_down->setObjectName("leftDrag_down");
        rightDrag_left = new QAction(MainWindow);
        rightDrag_left->setObjectName("rightDrag_left");
        rightDrag_up = new QAction(MainWindow);
        rightDrag_up->setObjectName("rightDrag_up");
        rightDrag_down = new QAction(MainWindow);
        rightDrag_down->setObjectName("rightDrag_down");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        startTest = new QPushButton(centralWidget);
        startTest->setObjectName("startTest");

        verticalLayout_2->addWidget(startTest);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 554, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(moveCursor_left);
        menu->addAction(moveCursor_right);
        menu->addAction(moveCursor_up);
        menu->addAction(moveCursor_down);
        menu->addAction(leftClick);
        menu->addAction(leftDoubleClick);
        menu->addAction(leftDrag_left);
        menu->addAction(leftDrag_right);
        menu->addAction(leftDrag_up);
        menu->addAction(leftDrag_down);
        menu->addAction(rightClick);
        menu->addAction(rightDrag_left);
        menu->addAction(rightDrag_right);
        menu->addAction(rightDrag_up);
        menu->addAction(rightDrag_down);
        menu->addAction(wheelZoomIn);
        menu->addAction(wheelZoomOut);
        menu->addAction(middleDrag);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actioncamera->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\233\270\346\234\272", nullptr));
        actionsetting->setText(QCoreApplication::translate("MainWindow", "\351\205\215\347\275\256", nullptr));
        actionlog->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\227\245\345\277\227", nullptr));
#if QT_CONFIG(tooltip)
        actionlog->setToolTip(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\227\245\345\277\227", nullptr));
#endif // QT_CONFIG(tooltip)
        moveCursor_left->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\240\207\344\275\215\347\275\256\347\247\273\345\212\250-left", nullptr));
        leftClick->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\345\215\225\345\207\273", nullptr));
        leftDoubleClick->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\345\217\214\345\207\273", nullptr));
        leftDrag_left->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-left", nullptr));
        rightClick->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\345\215\225\345\207\273", nullptr));
        rightDrag_right->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-right", nullptr));
        wheelZoomIn->setText(QCoreApplication::translate("MainWindow", "\346\273\232\350\275\256\346\224\276\345\244\247 (\346\273\232\350\275\256\345\220\221\344\270\212\346\273\232\345\212\250)", nullptr));
        wheelZoomOut->setText(QCoreApplication::translate("MainWindow", "\346\273\232\350\275\256\347\274\251\345\260\217 (\346\273\232\350\275\256\345\220\221\344\270\213\346\273\232\345\212\250)", nullptr));
        middleDrag->setText(QCoreApplication::translate("MainWindow", "\344\270\255\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250", nullptr));
        moveCursor_right->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\240\207\344\275\215\347\275\256\347\247\273\345\212\250-right", nullptr));
        moveCursor_up->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\240\207\344\275\215\347\275\256\347\247\273\345\212\250-up", nullptr));
        moveCursor_down->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\240\207\344\275\215\347\275\256\347\247\273\345\212\250-down", nullptr));
        leftDrag_right->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-right", nullptr));
        leftDrag_up->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-up", nullptr));
        leftDrag_down->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-down", nullptr));
        rightDrag_left->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-left", nullptr));
        rightDrag_up->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-up", nullptr));
        rightDrag_down->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250-down", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\274\240\346\240\207+\351\224\256\347\233\230\346\250\241\346\213\237\345\231\250", nullptr));
        startTest->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\250\241\346\213\237", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\346\213\237\344\272\213\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

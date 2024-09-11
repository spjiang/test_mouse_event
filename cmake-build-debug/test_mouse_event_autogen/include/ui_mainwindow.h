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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actioncamera;
    QAction *actionsetting;
    QAction *actionlog;
    QAction *moveCursor;
    QAction *leftClick;
    QAction *leftDoubleClick;
    QAction *leftDrag;
    QAction *rightClick;
    QAction *rightDrag;
    QAction *wheelZoomIn;
    QAction *wheelZoomOut;
    QAction *middleDrag;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
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
        moveCursor = new QAction(MainWindow);
        moveCursor->setObjectName("moveCursor");
        leftClick = new QAction(MainWindow);
        leftClick->setObjectName("leftClick");
        leftDoubleClick = new QAction(MainWindow);
        leftDoubleClick->setObjectName("leftDoubleClick");
        leftDrag = new QAction(MainWindow);
        leftDrag->setObjectName("leftDrag");
        rightClick = new QAction(MainWindow);
        rightClick->setObjectName("rightClick");
        rightDrag = new QAction(MainWindow);
        rightDrag->setObjectName("rightDrag");
        wheelZoomIn = new QAction(MainWindow);
        wheelZoomIn->setObjectName("wheelZoomIn");
        wheelZoomOut = new QAction(MainWindow);
        wheelZoomOut->setObjectName("wheelZoomOut");
        middleDrag = new QAction(MainWindow);
        middleDrag->setObjectName("middleDrag");
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

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 554, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(moveCursor);
        menu->addAction(leftClick);
        menu->addAction(leftDoubleClick);
        menu->addAction(leftDrag);
        menu->addAction(rightClick);
        menu->addAction(rightDrag);
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
        moveCursor->setText(QCoreApplication::translate("MainWindow", "\345\205\211\346\240\207\344\275\215\347\275\256\347\247\273\345\212\250", nullptr));
        leftClick->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\345\215\225\345\207\273", nullptr));
        leftDoubleClick->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\345\217\214\345\207\273", nullptr));
        leftDrag->setText(QCoreApplication::translate("MainWindow", "\345\267\246\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250", nullptr));
        rightClick->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\345\215\225\345\207\273", nullptr));
        rightDrag->setText(QCoreApplication::translate("MainWindow", "\345\217\263\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250", nullptr));
        wheelZoomIn->setText(QCoreApplication::translate("MainWindow", "\346\273\232\350\275\256\346\224\276\345\244\247 (\346\273\232\350\275\256\345\220\221\344\270\212\346\273\232\345\212\250)", nullptr));
        wheelZoomOut->setText(QCoreApplication::translate("MainWindow", "\346\273\232\350\275\256\347\274\251\345\260\217 (\346\273\232\350\275\256\345\220\221\344\270\213\346\273\232\345\212\250)", nullptr));
        middleDrag->setText(QCoreApplication::translate("MainWindow", "\344\270\255\351\224\256\347\202\271\345\207\273\346\213\226\345\212\250", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\274\240\346\240\207+\351\224\256\347\233\230\346\250\241\346\213\237\345\231\250", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\346\213\237\344\272\213\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

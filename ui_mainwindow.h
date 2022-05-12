/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Start;
    QPushButton *svrOpen;
    QPushButton *cliOpen;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Start = new QPushButton(centralwidget);
        Start->setObjectName(QStringLiteral("Start"));
        Start->setGeometry(QRect(210, 180, 351, 71));
        svrOpen = new QPushButton(centralwidget);
        svrOpen->setObjectName(QStringLiteral("svrOpen"));
        svrOpen->setGeometry(QRect(210, 280, 351, 71));
        cliOpen = new QPushButton(centralwidget);
        cliOpen->setObjectName(QStringLiteral("cliOpen"));
        cliOpen->setGeometry(QRect(210, 370, 351, 81));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Start->setText(QApplication::translate("MainWindow", "\345\215\225\346\234\272\346\270\270\346\210\217", Q_NULLPTR));
        svrOpen->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\347\275\221\347\273\234\346\270\270\346\210\217", Q_NULLPTR));
        cliOpen->setText(QApplication::translate("MainWindow", "\345\212\240\345\205\245\344\270\200\344\270\252\347\216\260\346\234\211\346\270\270\346\210\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

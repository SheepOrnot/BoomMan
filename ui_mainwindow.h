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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1028, 722);
        MainWindow->setStyleSheet(QStringLiteral("border-image: url(:/window/res/window/MainWindow.png);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Start = new QPushButton(centralwidget);
        Start->setObjectName(QStringLiteral("Start"));
        Start->setGeometry(QRect(340, 270, 351, 111));
        Start->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/Start.png);"));
        svrOpen = new QPushButton(centralwidget);
        svrOpen->setObjectName(QStringLiteral("svrOpen"));
        svrOpen->setGeometry(QRect(340, 410, 351, 111));
        svrOpen->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/CreateNetwork.png);"));
        cliOpen = new QPushButton(centralwidget);
        cliOpen->setObjectName(QStringLiteral("cliOpen"));
        cliOpen->setGeometry(QRect(340, 550, 351, 111));
        cliOpen->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/JoinNetwork.png);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 1028, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Start->setText(QString());
        svrOpen->setText(QString());
        cliOpen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

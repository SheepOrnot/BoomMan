/********************************************************************************
** Form generated from reading UI file 'gamepara.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEPARA_H
#define UI_GAMEPARA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamepara
{
public:
    QLabel *playselect;
    QLabel *gamemode;
    QPushButton *start;
    QGroupBox *groupBox;
    QRadioButton *Molly;
    QRadioButton *Alex;
    QRadioButton *Dan;
    QRadioButton *Roki;
    QLabel *label;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QRadioButton *Molly_2;
    QRadioButton *Alex_2;
    QRadioButton *Roki_2;
    QRadioButton *Dan_2;
    QGroupBox *groupBox_3;
    QRadioButton *ppee2v2;
    QRadioButton *pe1v1;
    QRadioButton *pp1v1;
    QLineEdit *IP;
    QLabel *labelIP;
    QPushButton *JoinSvr;
    QPushButton *CreateSvr;
    QLabel *connectNumT;
    QLabel *connectNum;

    void setupUi(QWidget *gamepara)
    {
        if (gamepara->objectName().isEmpty())
            gamepara->setObjectName(QStringLiteral("gamepara"));
        gamepara->resize(1028, 722);
        gamepara->setStyleSheet(QStringLiteral("#gamepara{border-image: url(:/window/res/window/MainWindow.png);}"));
        playselect = new QLabel(gamepara);
        playselect->setObjectName(QStringLiteral("playselect"));
        playselect->setGeometry(QRect(60, 260, 61, 16));
        gamemode = new QLabel(gamepara);
        gamemode->setObjectName(QStringLiteral("gamemode"));
        gamemode->setGeometry(QRect(60, 420, 68, 15));
        start = new QPushButton(gamepara);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(320, 580, 261, 101));
        start->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/Start.png);"));
        groupBox = new QGroupBox(gamepara);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(170, 210, 621, 71));
        groupBox->setStyleSheet(QStringLiteral(""));
        Molly = new QRadioButton(groupBox);
        Molly->setObjectName(QStringLiteral("Molly"));
        Molly->setGeometry(QRect(350, 40, 110, 19));
        Alex = new QRadioButton(groupBox);
        Alex->setObjectName(QStringLiteral("Alex"));
        Alex->setGeometry(QRect(70, 40, 110, 19));
        Dan = new QRadioButton(groupBox);
        Dan->setObjectName(QStringLiteral("Dan"));
        Dan->setGeometry(QRect(210, 40, 110, 19));
        Roki = new QRadioButton(groupBox);
        Roki->setObjectName(QStringLiteral("Roki"));
        Roki->setGeometry(QRect(480, 40, 110, 19));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 41, 16));
        groupBox_2 = new QGroupBox(gamepara);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(170, 310, 621, 51));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 41, 16));
        Molly_2 = new QRadioButton(groupBox_2);
        Molly_2->setObjectName(QStringLiteral("Molly_2"));
        Molly_2->setGeometry(QRect(350, 20, 110, 19));
        Alex_2 = new QRadioButton(groupBox_2);
        Alex_2->setObjectName(QStringLiteral("Alex_2"));
        Alex_2->setGeometry(QRect(70, 20, 110, 19));
        Roki_2 = new QRadioButton(groupBox_2);
        Roki_2->setObjectName(QStringLiteral("Roki_2"));
        Roki_2->setGeometry(QRect(480, 20, 110, 19));
        Dan_2 = new QRadioButton(groupBox_2);
        Dan_2->setObjectName(QStringLiteral("Dan_2"));
        Dan_2->setGeometry(QRect(210, 20, 110, 19));
        groupBox_3 = new QGroupBox(gamepara);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(170, 390, 621, 71));
        ppee2v2 = new QRadioButton(groupBox_3);
        ppee2v2->setObjectName(QStringLiteral("ppee2v2"));
        ppee2v2->setGeometry(QRect(350, 30, 110, 19));
        pe1v1 = new QRadioButton(groupBox_3);
        pe1v1->setObjectName(QStringLiteral("pe1v1"));
        pe1v1->setGeometry(QRect(210, 30, 110, 19));
        pp1v1 = new QRadioButton(groupBox_3);
        pp1v1->setObjectName(QStringLiteral("pp1v1"));
        pp1v1->setGeometry(QRect(70, 30, 110, 19));
        IP = new QLineEdit(gamepara);
        IP->setObjectName(QStringLiteral("IP"));
        IP->setGeometry(QRect(170, 130, 231, 31));
        labelIP = new QLabel(gamepara);
        labelIP->setObjectName(QStringLiteral("labelIP"));
        labelIP->setGeometry(QRect(60, 140, 71, 16));
        JoinSvr = new QPushButton(gamepara);
        JoinSvr->setObjectName(QStringLiteral("JoinSvr"));
        JoinSvr->setGeometry(QRect(320, 580, 261, 101));
        JoinSvr->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/JoinSvr.png);"));
        CreateSvr = new QPushButton(gamepara);
        CreateSvr->setObjectName(QStringLiteral("CreateSvr"));
        CreateSvr->setGeometry(QRect(320, 580, 261, 101));
        CreateSvr->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/CreateSvr.png);"));
        connectNumT = new QLabel(gamepara);
        connectNumT->setObjectName(QStringLiteral("connectNumT"));
        connectNumT->setGeometry(QRect(460, 140, 68, 15));
        connectNum = new QLabel(gamepara);
        connectNum->setObjectName(QStringLiteral("connectNum"));
        connectNum->setGeometry(QRect(530, 140, 68, 15));

        retranslateUi(gamepara);

        QMetaObject::connectSlotsByName(gamepara);
    } // setupUi

    void retranslateUi(QWidget *gamepara)
    {
        gamepara->setWindowTitle(QApplication::translate("gamepara", "Form", Q_NULLPTR));
        playselect->setText(QApplication::translate("gamepara", "\344\272\272\347\211\251\351\200\211\346\213\251", Q_NULLPTR));
        gamemode->setText(QApplication::translate("gamepara", "\346\270\270\346\210\217\346\250\241\345\274\217", Q_NULLPTR));
        start->setText(QString());
        groupBox->setTitle(QString());
        Molly->setText(QApplication::translate("gamepara", "Molly", Q_NULLPTR));
        Alex->setText(QApplication::translate("gamepara", "Alex", Q_NULLPTR));
        Dan->setText(QApplication::translate("gamepara", "Dan", Q_NULLPTR));
        Roki->setText(QApplication::translate("gamepara", "Roki", Q_NULLPTR));
        label->setText(QApplication::translate("gamepara", "P1:", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        label_2->setText(QApplication::translate("gamepara", "P2:", Q_NULLPTR));
        Molly_2->setText(QApplication::translate("gamepara", "Molly", Q_NULLPTR));
        Alex_2->setText(QApplication::translate("gamepara", "Alex", Q_NULLPTR));
        Roki_2->setText(QApplication::translate("gamepara", "Roki", Q_NULLPTR));
        Dan_2->setText(QApplication::translate("gamepara", "Dan", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        ppee2v2->setText(QApplication::translate("gamepara", "2v2:PPVEE", Q_NULLPTR));
        pe1v1->setText(QApplication::translate("gamepara", "1v1:PVE", Q_NULLPTR));
        pp1v1->setText(QApplication::translate("gamepara", "1v1:PVP", Q_NULLPTR));
        labelIP->setText(QApplication::translate("gamepara", "\346\234\215\345\212\241\345\231\250IP", Q_NULLPTR));
        JoinSvr->setText(QString());
        CreateSvr->setText(QString());
        connectNumT->setText(QApplication::translate("gamepara", "\345\275\223\345\211\215\344\272\272\346\225\260", Q_NULLPTR));
        connectNum->setText(QApplication::translate("gamepara", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class gamepara: public Ui_gamepara {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPARA_H

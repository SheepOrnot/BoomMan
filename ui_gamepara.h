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
    QPushButton *back;

    void setupUi(QWidget *gamepara)
    {
        if (gamepara->objectName().isEmpty())
            gamepara->setObjectName(QStringLiteral("gamepara"));
        gamepara->resize(1048, 748);
        gamepara->setStyleSheet(QLatin1String("#gamepara{border-image: url(:/window/res/window/bkWall.png);}\n"
"\n"
""));
        playselect = new QLabel(gamepara);
        playselect->setObjectName(QStringLiteral("playselect"));
        playselect->setGeometry(QRect(50, 130, 181, 61));
        playselect->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        gamemode = new QLabel(gamepara);
        gamemode->setObjectName(QStringLiteral("gamemode"));
        gamemode->setGeometry(QRect(40, 460, 161, 71));
        gamemode->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        start = new QPushButton(gamepara);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(390, 580, 261, 101));
        start->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/Start.png);"));
        groupBox = new QGroupBox(gamepara);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(200, 140, 771, 141));
        groupBox->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        Molly = new QRadioButton(groupBox);
        Molly->setObjectName(QStringLiteral("Molly"));
        Molly->setGeometry(QRect(300, 70, 141, 51));
        Alex = new QRadioButton(groupBox);
        Alex->setObjectName(QStringLiteral("Alex"));
        Alex->setGeometry(QRect(10, 70, 141, 51));
        Dan = new QRadioButton(groupBox);
        Dan->setObjectName(QStringLiteral("Dan"));
        Dan->setGeometry(QRect(170, 70, 131, 51));
        Roki = new QRadioButton(groupBox);
        Roki->setObjectName(QStringLiteral("Roki"));
        Roki->setGeometry(QRect(460, 70, 161, 51));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 81, 41));
        label->setStyleSheet(QString::fromUtf8("font: 75 24pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        groupBox_2 = new QGroupBox(gamepara);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(200, 300, 771, 141));
        groupBox_2->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 81, 51));
        Molly_2 = new QRadioButton(groupBox_2);
        Molly_2->setObjectName(QStringLiteral("Molly_2"));
        Molly_2->setGeometry(QRect(300, 70, 131, 41));
        Alex_2 = new QRadioButton(groupBox_2);
        Alex_2->setObjectName(QStringLiteral("Alex_2"));
        Alex_2->setGeometry(QRect(10, 70, 131, 41));
        Roki_2 = new QRadioButton(groupBox_2);
        Roki_2->setObjectName(QStringLiteral("Roki_2"));
        Roki_2->setGeometry(QRect(470, 70, 151, 41));
        Dan_2 = new QRadioButton(groupBox_2);
        Dan_2->setObjectName(QStringLiteral("Dan_2"));
        Dan_2->setGeometry(QRect(170, 70, 131, 41));
        groupBox_3 = new QGroupBox(gamepara);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(200, 470, 771, 71));
        groupBox_3->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        ppee2v2 = new QRadioButton(groupBox_3);
        ppee2v2->setObjectName(QStringLiteral("ppee2v2"));
        ppee2v2->setGeometry(QRect(460, 20, 231, 31));
        pe1v1 = new QRadioButton(groupBox_3);
        pe1v1->setObjectName(QStringLiteral("pe1v1"));
        pe1v1->setGeometry(QRect(240, 20, 171, 31));
        pp1v1 = new QRadioButton(groupBox_3);
        pp1v1->setObjectName(QStringLiteral("pp1v1"));
        pp1v1->setGeometry(QRect(10, 10, 171, 51));
        IP = new QLineEdit(gamepara);
        IP->setObjectName(QStringLiteral("IP"));
        IP->setGeometry(QRect(200, 60, 281, 31));
        IP->setStyleSheet(QString::fromUtf8("font: 75 15pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
""));
        labelIP = new QLabel(gamepara);
        labelIP->setObjectName(QStringLiteral("labelIP"));
        labelIP->setGeometry(QRect(50, 50, 191, 41));
        labelIP->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        JoinSvr = new QPushButton(gamepara);
        JoinSvr->setObjectName(QStringLiteral("JoinSvr"));
        JoinSvr->setGeometry(QRect(390, 580, 261, 101));
        JoinSvr->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/JoinSvr.png);"));
        CreateSvr = new QPushButton(gamepara);
        CreateSvr->setObjectName(QStringLiteral("CreateSvr"));
        CreateSvr->setGeometry(QRect(390, 580, 261, 101));
        CreateSvr->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/CreateSvr.png);"));
        connectNumT = new QLabel(gamepara);
        connectNumT->setObjectName(QStringLiteral("connectNumT"));
        connectNumT->setGeometry(QRect(530, 40, 161, 61));
        connectNumT->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        connectNum = new QLabel(gamepara);
        connectNum->setObjectName(QStringLiteral("connectNum"));
        connectNum->setGeometry(QRect(730, 50, 121, 41));
        connectNum->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\346\200\235\346\272\220\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        back = new QPushButton(gamepara);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(810, 40, 161, 61));
        back->setStyleSheet(QStringLiteral("border-image: url(:/button/res/button/back.png);"));

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
        back->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gamepara: public Ui_gamepara {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPARA_H

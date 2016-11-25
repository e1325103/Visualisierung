/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTop;
    QProgressBar *progressBar;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *drawLabel;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupIntegration;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioEuler;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioRunge;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *textSteps;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_5;
    QTextEdit *textDelta;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkEven;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *checkArrows;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkColour;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_9;
    QPushButton *buttonLic;
    QWidget *widget_13;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_11;
    QPushButton *buttonRedraw;
    QWidget *widget_14;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1085, 731);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 50));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelTop = new QLabel(widget);
        labelTop->setObjectName(QStringLiteral("labelTop"));
        labelTop->setMaximumSize(QSize(16777215, 200));
        labelTop->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(labelTop);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(false);
        progressBar->setMaximumSize(QSize(200, 16777215));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout_2->addWidget(progressBar);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(widget);

        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        drawLabel = new QLabel(centralwidget);
        drawLabel->setObjectName(QStringLiteral("drawLabel"));

        horizontalLayout->addWidget(drawLabel);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(200, 16777215));
        verticalLayout_4 = new QVBoxLayout(widget_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_11 = new QWidget(widget_2);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setMaximumSize(QSize(16777215, 220));
        horizontalLayout_6 = new QHBoxLayout(widget_11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupIntegration = new QGroupBox(widget_11);
        groupIntegration->setObjectName(QStringLiteral("groupIntegration"));
        groupIntegration->setMaximumSize(QSize(16777215, 200));
        groupIntegration->setCheckable(false);
        groupIntegration->setChecked(false);
        verticalLayout_10 = new QVBoxLayout(groupIntegration);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        widget_3 = new QWidget(groupIntegration);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMaximumSize(QSize(16777215, 40));
        verticalLayout_5 = new QVBoxLayout(widget_3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        radioEuler = new QRadioButton(widget_3);
        radioEuler->setObjectName(QStringLiteral("radioEuler"));
        radioEuler->setChecked(true);

        verticalLayout_5->addWidget(radioEuler);


        verticalLayout_10->addWidget(widget_3);

        widget_8 = new QWidget(groupIntegration);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_3 = new QHBoxLayout(widget_8);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioRunge = new QRadioButton(widget_8);
        radioRunge->setObjectName(QStringLiteral("radioRunge"));

        horizontalLayout_3->addWidget(radioRunge);


        verticalLayout_10->addWidget(widget_8);

        widget_9 = new QWidget(groupIntegration);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_4 = new QHBoxLayout(widget_9);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        textSteps = new QTextEdit(widget_9);
        textSteps->setObjectName(QStringLiteral("textSteps"));
        textSteps->setMaximumSize(QSize(100, 30));
        textSteps->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout_4->addWidget(textSteps);


        verticalLayout_10->addWidget(widget_9);

        widget_10 = new QWidget(groupIntegration);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_5 = new QHBoxLayout(widget_10);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        textDelta = new QTextEdit(widget_10);
        textDelta->setObjectName(QStringLiteral("textDelta"));
        textDelta->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(textDelta);


        verticalLayout_10->addWidget(widget_10);

        widget_3->raise();
        radioRunge->raise();
        widget_8->raise();
        widget_9->raise();
        widget_10->raise();

        horizontalLayout_6->addWidget(groupIntegration);


        verticalLayout_4->addWidget(widget_11);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMaximumSize(QSize(16777215, 40));
        verticalLayout_6 = new QVBoxLayout(widget_4);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        checkEven = new QCheckBox(widget_4);
        checkEven->setObjectName(QStringLiteral("checkEven"));

        verticalLayout_6->addWidget(checkEven);


        verticalLayout_4->addWidget(widget_4);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMaximumSize(QSize(16777215, 40));
        verticalLayout_7 = new QVBoxLayout(widget_5);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        checkArrows = new QCheckBox(widget_5);
        checkArrows->setObjectName(QStringLiteral("checkArrows"));

        verticalLayout_7->addWidget(checkArrows);


        verticalLayout_4->addWidget(widget_5);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMaximumSize(QSize(16777215, 40));
        verticalLayout_8 = new QVBoxLayout(widget_6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        checkColour = new QCheckBox(widget_6);
        checkColour->setObjectName(QStringLiteral("checkColour"));

        verticalLayout_8->addWidget(checkColour);


        verticalLayout_4->addWidget(widget_6);

        widget_7 = new QWidget(widget_2);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setMaximumSize(QSize(16777215, 40));
        verticalLayout_9 = new QVBoxLayout(widget_7);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        buttonLic = new QPushButton(widget_7);
        buttonLic->setObjectName(QStringLiteral("buttonLic"));

        verticalLayout_9->addWidget(buttonLic);


        verticalLayout_4->addWidget(widget_7);

        widget_13 = new QWidget(widget_2);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        widget_13->setMaximumSize(QSize(16777215, 40));

        verticalLayout_4->addWidget(widget_13);

        widget_12 = new QWidget(widget_2);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setMaximumSize(QSize(16777215, 40));
        verticalLayout_11 = new QVBoxLayout(widget_12);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        buttonRedraw = new QPushButton(widget_12);
        buttonRedraw->setObjectName(QStringLiteral("buttonRedraw"));

        verticalLayout_11->addWidget(buttonRedraw);


        verticalLayout_4->addWidget(widget_12);

        widget_14 = new QWidget(widget_2);
        widget_14->setObjectName(QStringLiteral("widget_14"));

        verticalLayout_4->addWidget(widget_14);


        horizontalLayout->addWidget(widget_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1085, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        buttonLic->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Visualisierung 1", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open ...", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        labelTop->setText(QApplication::translate("MainWindow", "No data loaded", 0));
        drawLabel->setText(QString());
        groupIntegration->setTitle(QApplication::translate("MainWindow", "Integration", 0));
        radioEuler->setText(QApplication::translate("MainWindow", "Euler Integration", 0));
        radioRunge->setText(QApplication::translate("MainWindow", "Runge Kutta", 0));
        textSteps->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        textSteps->setPlaceholderText(QApplication::translate("MainWindow", "Anzahl Schritte", 0));
        textDelta->setPlaceholderText(QApplication::translate("MainWindow", "Delta", 0));
        checkEven->setText(QApplication::translate("MainWindow", "Gleichm\303\244\303\237ige Verteilung", 0));
        checkArrows->setText(QApplication::translate("MainWindow", "Pfeile", 0));
        checkColour->setText(QApplication::translate("MainWindow", "Farben", 0));
        buttonLic->setText(QApplication::translate("MainWindow", "Linear Intergral Convolution", 0));
        buttonRedraw->setText(QApplication::translate("MainWindow", "Neu Zeichnen", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

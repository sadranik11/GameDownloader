/********************************************************************************
** Form generated from reading UI file 'GameDownloader.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEDOWNLOADER_H
#define UI_GAMEDOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameDownloaderClass
{
public:
    QWidget *centralWidget;
    QProgressBar *progressBar_Download;
    QLabel *label_DownloadedSize;
    QPushButton *pauseResumeButton;
    QPushButton *checkFixButton;
    QPushButton *startButton;
    QPushButton *uninstallButton;
    QLabel *label;
    QLabel *label_FileCount;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameDownloaderClass)
    {
        if (GameDownloaderClass->objectName().isEmpty())
            GameDownloaderClass->setObjectName("GameDownloaderClass");
        GameDownloaderClass->resize(600, 400);
        GameDownloaderClass->setMaximumSize(QSize(600, 400));
        centralWidget = new QWidget(GameDownloaderClass);
        centralWidget->setObjectName("centralWidget");
        progressBar_Download = new QProgressBar(centralWidget);
        progressBar_Download->setObjectName("progressBar_Download");
        progressBar_Download->setGeometry(QRect(30, 300, 541, 31));
        progressBar_Download->setValue(24);
        label_DownloadedSize = new QLabel(centralWidget);
        label_DownloadedSize->setObjectName("label_DownloadedSize");
        label_DownloadedSize->setGeometry(QRect(30, 290, 181, 21));
        pauseResumeButton = new QPushButton(centralWidget);
        pauseResumeButton->setObjectName("pauseResumeButton");
        pauseResumeButton->setGeometry(QRect(300, 50, 131, 61));
        checkFixButton = new QPushButton(centralWidget);
        checkFixButton->setObjectName("checkFixButton");
        checkFixButton->setGeometry(QRect(160, 110, 141, 61));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(160, 50, 141, 61));
        uninstallButton = new QPushButton(centralWidget);
        uninstallButton->setObjectName("uninstallButton");
        uninstallButton->setGeometry(QRect(300, 110, 131, 61));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 10, 171, 21));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label_FileCount = new QLabel(centralWidget);
        label_FileCount->setObjectName("label_FileCount");
        label_FileCount->setGeometry(QRect(0, 210, 161, 21));
        QFont font1;
        font1.setPointSize(10);
        label_FileCount->setFont(font1);
        GameDownloaderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameDownloaderClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 33));
        GameDownloaderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameDownloaderClass);
        mainToolBar->setObjectName("mainToolBar");
        GameDownloaderClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GameDownloaderClass);
        statusBar->setObjectName("statusBar");
        GameDownloaderClass->setStatusBar(statusBar);

        retranslateUi(GameDownloaderClass);

        QMetaObject::connectSlotsByName(GameDownloaderClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameDownloaderClass)
    {
        GameDownloaderClass->setWindowTitle(QCoreApplication::translate("GameDownloaderClass", "GameDownloader", nullptr));
        label_DownloadedSize->setText(QCoreApplication::translate("GameDownloaderClass", "Downloaded: 0 MB / 0 MB", nullptr));
        pauseResumeButton->setText(QCoreApplication::translate("GameDownloaderClass", "Pause / Resume", nullptr));
        checkFixButton->setText(QCoreApplication::translate("GameDownloaderClass", "Check and Fix Files", nullptr));
        startButton->setText(QCoreApplication::translate("GameDownloaderClass", "Start", nullptr));
        uninstallButton->setText(QCoreApplication::translate("GameDownloaderClass", "Uninstall", nullptr));
        label->setText(QCoreApplication::translate("GameDownloaderClass", "Game Downloader", nullptr));
        label_FileCount->setText(QCoreApplication::translate("GameDownloaderClass", "Files Downloaded : X / Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameDownloaderClass: public Ui_GameDownloaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEDOWNLOADER_H

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameDownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QProgressBar>

class GameDownloader : public QMainWindow
{
    Q_OBJECT

public:
    GameDownloader(QWidget* parent = nullptr);
    ~GameDownloader();

private slots:
    void startDownload();
    void downloadFinished(QNetworkReply* reply);
    void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void pauseResumeDownload();
    void checkAndFixFiles();
    void uninstallGame();

private:
    Ui::GameDownloaderClass ui;
    QString installDirectory;
    QNetworkAccessManager* networkManager;
    QNetworkReply* currentDownload;
    QFile* downloadedFile;
    bool isDownloading;
    qint64 bytesDownloadedSoFar = 0;
    QStringList fileUrls;
    int currentDownloadIndex;
};

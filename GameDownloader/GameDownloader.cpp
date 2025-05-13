#include "GameDownloader.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

GameDownloader::GameDownloader(QWidget* parent)
    : QMainWindow(parent), networkManager(new QNetworkAccessManager(this)), isDownloading(false)
{
    ui.setupUi(this);

    ui.pauseResumeButton->setEnabled(false);
    ui.uninstallButton->setEnabled(false);
    ui.progressBar_Download->setValue(0);
    ui.label_DownloadedSize->setText("Downloaded: 0 MB / 0 MB");

    connect(ui.startButton, &QPushButton::clicked, this, &GameDownloader::startDownload);
    connect(ui.pauseResumeButton, &QPushButton::clicked, this, &GameDownloader::pauseResumeDownload);
    connect(ui.checkFixButton, &QPushButton::clicked, this, &GameDownloader::checkAndFixFiles);
    connect(ui.uninstallButton, &QPushButton::clicked, this, &GameDownloader::uninstallGame);

    connect(networkManager, &QNetworkAccessManager::finished, this, &GameDownloader::downloadFinished);
    
    currentDownloadIndex = 0;
    fileUrls = {
        "https://i.imgur.com/pw1PEQ0.png",
        "https://i.imgur.com/z75b1Fy.png",
        "https://i.imgur.com/naRoSfr.png",
        "https://i.imgur.com/mFSj8Jz.png"
    };
    ui.label_FileCount->setText(
        QString("Files Downloaded: 0 / %1").arg(fileUrls.size())
    );

}

GameDownloader::~GameDownloader()
{
    delete networkManager;
}

void GameDownloader::startDownload()
{
    if (installDirectory.isEmpty()) {
        installDirectory = QFileDialog::getExistingDirectory(this, "Select Installation Folder");

        if (installDirectory.isEmpty()) {
            qDebug() << "User cancelled the folder selection.";
            return;
        }

        installDirectory += "/Game files";
        QDir dir;
        if (!dir.exists(installDirectory)) {
            dir.mkpath(installDirectory);
        }
        ui.uninstallButton->setEnabled(true);
    }

    if (currentDownloadIndex >= fileUrls.size()) {
        qDebug() << "All downloads finished.";
        return;
    }

    QUrl url(fileUrls[currentDownloadIndex]);
    QNetworkRequest request(url);

    QString fileName = QString("image_%1.png").arg(currentDownloadIndex + 1);
    QString filePath = installDirectory + "/" + fileName;

    downloadedFile = new QFile(filePath);
    if (!downloadedFile->open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    currentDownload = networkManager->get(request);
    connect(currentDownload, &QNetworkReply::downloadProgress, this, &GameDownloader::updateDownloadProgress);

    ui.pauseResumeButton->setEnabled(true);
    ui.pauseResumeButton->setText("Pause");

    connect(currentDownload, &QNetworkReply::readyRead, this, [=]() {
        if (downloadedFile)
            downloadedFile->write(currentDownload->readAll());
        });

    isDownloading = true;
    qDebug() << "Started download:" << fileName;
}


void GameDownloader::pauseResumeDownload()
{
    if (isDownloading) {
        // Pause the current download
        qDebug() << "Download paused!";
        if (currentDownload) {
            currentDownload->abort(); // We'll cut it off.
            currentDownload->deleteLater();
            currentDownload = nullptr;
        }

        bytesDownloadedSoFar += downloadedFile->size(); // We'll record it so we can continue later.
        isDownloading = false;
        ui.pauseResumeButton->setText("Resume");
    }
    else {
        // Resume the download from where it stopped
        qDebug() << "Resuming download...";

        QUrl url(fileUrls[currentDownloadIndex]);
        QNetworkRequest request(url);

        QString fileName = QString("image_%1.png").arg(currentDownloadIndex + 1);
        QString filePath = installDirectory + "/" + fileName;

        downloadedFile = new QFile(filePath);
        if (!downloadedFile->open(QIODevice::Append)) {
            qDebug() << "Failed to open file in append mode.";
            return;
        }

        // If some has already been downloaded, request the rest of the file with Range.
        if (bytesDownloadedSoFar > 0) {
            QByteArray rangeValue = "bytes=" + QByteArray::number(bytesDownloadedSoFar) + "-";
            request.setRawHeader("Range", rangeValue);
            qDebug() << "Resuming from byte" << bytesDownloadedSoFar;
        }

        currentDownload = networkManager->get(request);
        connect(currentDownload, &QNetworkReply::downloadProgress, this, &GameDownloader::updateDownloadProgress);
        connect(currentDownload, &QNetworkReply::readyRead, this, [=]() {
            if (downloadedFile)
                downloadedFile->write(currentDownload->readAll());
            });

        isDownloading = true;
        ui.pauseResumeButton->setText("Pause");
    }
}




void GameDownloader::downloadFinished(QNetworkReply* reply)
{
    if (reply->error()) {
        qDebug() << "Download failed:" << reply->errorString();
    }
    else {
        qDebug() << "Download finished!";
    }

    downloadedFile->close();
    delete downloadedFile;
    downloadedFile = nullptr;

    isDownloading = false;
    reply->deleteLater();

    bytesDownloadedSoFar = 0;
    currentDownloadIndex++;
    ui.label_FileCount->setText(
        QString("Files Downloaded: %1 / %2")
        .arg(currentDownloadIndex)
        .arg(fileUrls.size())
    );

    if (currentDownloadIndex >= fileUrls.size()) {
        ui.pauseResumeButton->setEnabled(false);
        QMessageBox::information(this, "Download Complete", "All files have been successfully downloaded!");
        return;
    }

    startDownload();
}



void GameDownloader::updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = static_cast<int>((bytesReceived * 100) / bytesTotal);
        ui.progressBar_Download->setValue(progress);

        double receivedMB = bytesReceived / (1024.0 * 1024.0);
        double totalMB = bytesTotal / (1024.0 * 1024.0);

        ui.label_DownloadedSize->setText(
            QString("Downloaded: %1 MB / %2 MB")
            .arg(receivedMB, 0, 'f', 2)
            .arg(totalMB, 0, 'f', 2)
        );
    }
}


void GameDownloader::checkAndFixFiles()
{
    if (installDirectory.isEmpty()) {
        QMessageBox::information(this, "Check", "No installation folder selected.");
        return;
    }

    QStringList filesToFix;

    for (int i = 0; i < fileUrls.size(); ++i) {
        QString fileName = QString("image_%1.png").arg(i + 1);
        QString filePath = installDirectory + "/" + fileName;

        QFile file(filePath);

        if (!file.exists() || file.size() == 0) {
            filesToFix.append(fileUrls[i]);
            qDebug() << "File missing or empty:" << fileName;
        }
    }

    if (filesToFix.isEmpty()) {
        QMessageBox::information(this, "Check Complete", "All files are valid.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Fix Files",
        QString("%1 problematic file(s) found. Do you want to redownload them?").arg(filesToFix.size()),
        QMessageBox::Yes | QMessageBox::Cancel
    );

    if (reply == QMessageBox::Yes) {
        //Set up a new list for download
        fileUrls = filesToFix;
        currentDownloadIndex = 0;
        bytesDownloadedSoFar = 0;
        startDownload();
    }
}


void GameDownloader::uninstallGame()
{
    if (installDirectory.isEmpty()) {
        qDebug() << "Install directory is empty!";
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Uninstall",
        "Are you sure you want to uninstall and delete all game files?",
        QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        QDir dir(installDirectory);
        if (dir.exists()) {
            if (dir.removeRecursively()) {
                qDebug() << "Uninstall complete. Folder deleted.";
                ui.uninstallButton->setEnabled(false);
                ui.progressBar_Download->setValue(0);
                ui.label_DownloadedSize->setText("Downloaded: 0 MB / 0 MB");
                ui.label_FileCount->setText(QString("Files Downloaded: %1 / %2").arg(0).arg(fileUrls.size()));
                currentDownloadIndex = 0;
                installDirectory.clear();
            }
            else {
                qDebug() << "Failed to delete folder.";
            }
        }
    }
    else {
        qDebug() << "Uninstall cancelled.";
    }
}



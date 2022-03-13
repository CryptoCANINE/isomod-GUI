// Qt headers \/
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QtGlobal>
// Non-Qt headers \/
#include "./ui_window.h"
#include "log.h"
#include "window.h"

// GUI stuff \/
Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
    ui->setupUi(this);
    QObject::connect(ui->ISOBrowse, SIGNAL(clicked()), this, SLOT(ISOBrowser()));
    QObject::connect(ui->replaceBrowse, SIGNAL(clicked()), this,
        SLOT(replacementBrowser()));
    QObject::connect(ui->importButton, SIGNAL(clicked()), this, SLOT(import()));
}

Window::~Window() { delete ui; }

QString Window::OSDetection() {
#if defined(Q_OS_MACOS)
    return QDir::currentPath() + "/bin/isomod";
#elif defined(Q_OS_WIN)
    return QDir::currentPath() + "/bin/isomod.exe";
#elif defined(Q_OS_LINUX)
    return QDir::currentPath() + "/bin/isomod";
#elif defined(Q_OS_UNIX)
    return QDir::currentPath() + "/bin/isomod";
#else
    return QDir::currentPath() + "/bin/isomod";
#endif
}

void Window::ISOBrowser() {
    QString OpenISOPath = QFileDialog::getOpenFileName(
        this, tr("Open an ISO"), "", tr("ISO files (*.ISO);;All Files (*)"));
    if (OpenISOPath.isEmpty()) {
        QMessageBox noFileError;
        noFileError.critical(0, "Error opening file.",
            "Please choose a valid file.");
        noFileError.setFixedSize(500, 200);
        Logger.logStuff(LOG_WARNING, "FAILED to open a file with reason: no file chosen");
        return;
    } else {
        QFile file(OpenISOPath);
        if (!file.open(QIODevice::ReadWrite)) {
            QMessageBox::information(this, tr("Failed to open file."),
                file.errorString());
            Logger.logStuff(LOG_ERROR, "FAILED to open the file " + OpenISOPath.toStdString() + " with reason: " + file.errorString().toStdString());
            return;
        }
        ui->ISOLabel->setText(file.fileName());
    }
}

void Window::replacementBrowser() {
    QString OpenINTPath = QFileDialog::getOpenFileName(
        this, tr("Open a file"), "", tr("INT files (*.INT);;WP2 files (*.WP2);;XTR files (*.XTR);;All Files (*)"));
    if (OpenINTPath.isEmpty()) {
        QMessageBox noFileError;
        noFileError.critical(0, "Error opening file.",
            "Please choose a valid file.");
        noFileError.setFixedSize(500, 200);
        Logger.logStuff(LOG_WARNING, "FAILED to open a file with reason: no file chosen");
        return;
    } else {
        QFile file(OpenINTPath);
        if (!file.open(QIODevice::ReadWrite)) {
            QMessageBox::information(this, tr("Failed to open file."),
                file.errorString());
            Logger.logStuff(LOG_ERROR, "FAILED to open the file " + OpenINTPath.toStdString() + " with reason: " + file.errorString().toStdString());
            return;
        }
        ui->ReplacementLabel->setText(file.fileName());
    }
}

void Window::import() {
    QFile ISOLoc(ui->ISOLabel->text());
    if (!ISOLoc.exists()) {
        QMessageBox nonExistantFile;
        nonExistantFile.critical(
            0, "Error opening file.",
            "Please make sure the ISO you chose exists and try again.");
        nonExistantFile.setFixedSize(500, 200);
        Logger.logStuff(LOG_WARNING, "FAILED to open the file " + ui->ISOLabel->text().toStdString() + " with reason: file doesn't exist");
    } else {
        QFile ReplacementFileLoc(ui->ReplacementLabel->text());
        if (!ReplacementFileLoc.exists()) {
            QMessageBox nonExistantFile;
            nonExistantFile.critical(0, "Error opening file.",
                "Please make sure the replacement file you "
                "chose exists and try again.");
            nonExistantFile.setFixedSize(500, 200);
            Logger.logStuff(LOG_WARNING, "FAILED to open the file " + ui->ReplacementLabel->text().toStdString() + " with reason: file doesn't exist");
        } else {
            QString program = Window::OSDetection();
            QStringList isomodargs;
            // TODO: TEST ON WINDOWS!
            isomodargs << "put" << ui->ISOLabel->text() << ui->DirLabel->text() << ui->ReplacementLabel->text();
            QProcess isomod;
            isomod.start(program, isomodargs);
            Logger.logStuff(LOG_INFO, "Running isomod with executable " + program.toStdString() + " and with arguments: " + isomodargs.join(" ").toStdString());
            isomod.waitForFinished(-1);
            if (!isomod.waitForFinished()) {
                while (isomod.canReadLine()) {
                    Logger.logStuffNN(LOG_ISOMOD, isomod.readLine().toStdString());
                }
                if (isomod.exitCode() != 0) {
                    Logger.logStuff(LOG_ERROR, "isomod FAILED to run. Status code: " + std::to_string(isomod.exitCode()));
                    QMessageBox criticalRunError;
                    // I am aware that the end of this is messy. But it leaves no warnings, so whatever.
                    criticalRunError.critical(0, "Error running isomod!", "Something went wrong and isomod failed to run! Status code: " + QString::fromStdString(std::to_string(isomod.exitCode())));
                    criticalRunError.setFixedSize(500, 200);
                } else {
                    Logger.logStuff(LOG_INFO, "isomod completed running with no issues");
                    QMessageBox successMessage;
                    successMessage.information(0, "Done!", "Finished!");
                    successMessage.setFixedSize(500, 200);
                }
            }
        }
    }
}

void Window::on_actionConsole_triggered() {
    console.show();
}

void Window::on_actionExit_triggered() {
    this->close();
}

void Window::closeEvent(QCloseEvent *event) {
    Logger.logStuff(LOG_INFO, "isomod-GUI closing");
    console.close();
    QMainWindow::closeEvent(event);
}

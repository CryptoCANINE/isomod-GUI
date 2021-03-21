#include "window.h"

#include <QDir>
#include <QFileDialog>
#include <QIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QtGlobal>

#include "./ui_window.h"

// now GUI stuff   \/

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
    return;
  } else {
    QFile file(OpenISOPath);
    if (!file.open(QIODevice::ReadWrite)) {
      QMessageBox::information(this, tr("Failed to open file."),
                               file.errorString());
      return;
    }
    ui->ISOLabel->setText(file.fileName());
  }
}

void Window::replacementBrowser() {
  QString OpenINTPath = QFileDialog::getOpenFileName(
      this, tr("Open a File"), "", tr("INT files (*.INT);;WP2 files (*.WP2);;XTR files (*.XTR);;ISO files (*.ISO);;All Files (*)"));
  if (OpenINTPath.isEmpty()) {
    QMessageBox noFileError;
    noFileError.critical(0, "Error opening file.",
                         "Please choose a valid file.");
    noFileError.setFixedSize(500, 200);
    return;
  } else {
    QFile file(OpenINTPath);
    if (!file.open(QIODevice::ReadWrite)) {
      QMessageBox::information(this, tr("Failed to open file."),
                               file.errorString());
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
  } else {
    QFile ReplacementFileLoc(ui->ReplacementLabel->text());
    if (!ReplacementFileLoc.exists()) {
      QMessageBox nonExistantFile;
      nonExistantFile.critical(0, "Error opening file.",
                               "Please make sure the replacement file you "
                               "chose exists and try again.");
      nonExistantFile.setFixedSize(500, 200);
    } else {
      QString program = Window::OSDetection();
      QString isomodargs = " put \"" + ui->ISOLabel->text() + "\" \"" +
                           ui->DirSelect->currentText() + "\" \"" +
                           ui->ReplacementLabel->text() + "\"";

      QProcess isomod;
      isomod.execute(program + isomodargs);
      isomod.waitForFinished(-1);
    }
  }
}


/*
 * void Window::on_treeView_clicked(const QModelIndex &index)
{

}
*/

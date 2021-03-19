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

// isomod required stuff here

// now GUI stuff   \/

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
      this, tr("Open an INT"), "", tr("INT files (*.INT);;All Files (*)"));
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
  QString program = Window::OSDetection();
  QString isomodargs = " put \"" + ui->ISOLabel->text() + "\" \"" +
                       ui->DirLabel->text() + "\" \"" +
                       ui->ReplacementLabel->text() + "\"";

  QProcess isomod;
  isomod.execute(program + isomodargs);
  isomod.waitForFinished(-1);
  QString result = isomod.readAllStandardOutput();
}
/*
 * void Window::on_treeView_clicked(const QModelIndex &index)
{

}
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QDir>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window();

 private slots:
  void ISOBrowser();
  void replacementBrowser();
  void import();  // WIP
  QString OSDetection();

 private:
  Ui::Window *ui;
};
#endif  // WINDOW_H

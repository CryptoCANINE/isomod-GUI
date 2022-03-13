#ifndef WINDOW_H
#define WINDOW_H
// Qt headers \/
#include <QDialog>
#include <QDir>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QtGlobal>
// Non-Qt headers \/
#include <console.h>
#include <log.h>

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
    Log Logger;

    private slots:
    void closeEvent(QCloseEvent *event);
    void import();    // WIP
    void ISOBrowser();
    void on_actionExit_triggered();
    void on_actionConsole_triggered();
    void replacementBrowser();
    QString OSDetection();

    private:
    Console console;
    Ui::Window *ui;
};

#endif    // WINDOW_H

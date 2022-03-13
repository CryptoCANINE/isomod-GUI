#ifndef CONSOLE_H
#define CONSOLE_H
// Qt headers \/
#include <QDialog>
#include <QString>

namespace Ui {
    class Console;
}

class Console : public QDialog {
    Q_OBJECT
    public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();
    void readOutput();
    void update();

    private:
    Ui::Console *ui;
    QString logOutput;
};

#endif    // CONSOLE_H

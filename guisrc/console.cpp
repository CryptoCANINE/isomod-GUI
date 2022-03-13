// Qt headers \/
#include <QFile>
#include <QScrollBar>
#include <QString>
#include <QTextStream>
#include <QTimer>
// Non-Qt headers \/
#include "console.h"
#include "ui_console.h"
#include "window.h"

Console::Console(QWidget *parent) : QDialog(parent), ui(new Ui::Console) {
    ui->setupUi(this);
    readOutput();
    QTimer *update = new QTimer(this);
    connect(update, &QTimer::timeout, this, &Console::update);
    update->start(1000);
}

Console::~Console() {
    delete ui;
}

void Console::readOutput() {
    QString path = QDir::currentPath() + "/log.txt";
    QFile logFile(path);
    if (logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream fileContent(&logFile);
        logOutput = fileContent.readAll();
    }
}

void Console::update() {
    readOutput();
    if (logOutput != ui->logOutputText->toPlainText()) {
        ui->logOutputText->setText(logOutput);
        ui->logOutputText->verticalScrollBar()->setValue(
            ui->logOutputText->verticalScrollBar()->maximum());
    }
}

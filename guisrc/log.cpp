// Qt headers \/
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
// Non-Qt headers \/
#include "log.h"
#include <iostream>
#include <string>

Log::Log() {
    logInput.clear();
    logOutput = "";
    QFile logFile(path);
    if (logFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
        QTextStream fileStream(&logFile);
        fileStream << "\n--- SEPARATOR ---\n\n";
    }
    logFile.close();
    logStuff(LOG_INFO, "isomod-GUI started");
}

Log::~Log() {
    logInput.clear();
    logOutput = "";
}

QString Log::getCurrentDate() {
    return QDateTime::currentDateTime().toString();
}

std::string Log::giveLogOutput() {
    logOutput = "";
    for (int i = 0; i < logInput.size(); i++) {
        logOutput += logInput[i];
    }
    return logOutput;
}

void Log::logStuff(LOG_LEVELS logLevel, std::string info) {
    std::string input;
    input = "[" + getCurrentDate().toStdString() + ", " + LOG_LEVELS_CHAR[logLevel] + "] - " + info + "\n";
    QFile logFile(path);
    if (logFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
        QTextStream fileStream(&logFile);
        fileStream << input.c_str();
    }
    logFile.close();
}

// Log with no new line
void Log::logStuffNN(LOG_LEVELS logLevel, std::string info) {
    std::string input;
    input = "[" + getCurrentDate().toStdString() + ", " + LOG_LEVELS_CHAR[logLevel] + "] - " + info;
    QFile logFile(path);
    if (logFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
        QTextStream fileStream(&logFile);
        fileStream << input.c_str();
    }
    logFile.close();
}

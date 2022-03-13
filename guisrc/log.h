#ifndef LOG_H
#define LOG_H
// Qt headers \/
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
// Non-Qt headers \/
#include <string>
#include <vector>

enum LOG_LEVELS {
    LOG_ERROR,
    LOG_INFO,
    LOG_ISOMOD,
    LOG_WARNING
};

static const char *LOG_LEVELS_CHAR[] = {
    "ERROR",
    "INFO",
    "ISOMOD",
    "WARNING"};

class Log {
    public:
    Log();
    ~Log();
    QString getCurrentDate();
    std::string giveLogOutput();
    std::string logOutput;
    std::vector<std::string> logInput;
    void logStuff(LOG_LEVELS logLevel = LOG_INFO, std::string info = "");
    void logStuffNN(LOG_LEVELS logLevel = LOG_INFO, std::string info = "");

    private:
    LOG_LEVELS logMsgLevel;
    QString path = QDir::currentPath() + "/log.txt";
};

#endif    // LOG_H

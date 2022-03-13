// Qt headers \/
#include <QApplication>
#include <QProcess>
#include <QStringList>
#include <QStyleFactory>
// Non-Qt headers \/
#include "window.h"
#include <ctype.h>
#include <inttypes.h>
#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QString OSDetection() {
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

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QStringList args = a.arguments();
    Window w;
    if (args.count() != 1) {
        // This had to be done to fix bugs that were present on Windows. Sorry for
        // the inconvenience.
        QString program = OSDetection();
        QStringList isomodargs;
        // TODO: TEST ON WINDOWS!
        isomodargs << QString(argv[1]) << QString(argv[2]) << QString(argv[3]) << QString(argv[4]);
        QProcess isomod;
        isomod.execute(program, isomodargs);
        if (!isomod.waitForFinished()) {
            if (isomod.exitCode() != 0)
                fprintf(stderr, "Failed to run isomod!");
        }
    } else if (args.count() == 1) {
        w.show();
        return a.exec();
    }
}

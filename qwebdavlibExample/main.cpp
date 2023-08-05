#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>

#include "qexample.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser parser;
    QExample e;
    parser.setApplicationDescription("QtWebDAV Tester");
    parser.addHelpOption();
    parser.addVersionOption();


    parser.process(a);
    const QStringList args = parser.positionalArguments();

    if ( args.length() > 0) {
        QUrl url(args[0]);
        if ( url.isValid() ) {
            e.setUrl(url);
            e.start();
        } else {
            qCritical() << "Invalid URL: " << args[0];
            a.exit(1);
        }
    } else {
        qCritical() << "URL is mandatory";
        a.exit(1);
    }

    return a.exec();
}

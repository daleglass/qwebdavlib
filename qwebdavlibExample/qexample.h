#ifndef QEXAMPLE_H
#define QEXAMPLE_H

#include <QObject>

#include <qwebdav.h>
#include <qwebdavdirparser.h>
#include <qwebdavitem.h>
#include <QUrl>
#include <QTimer>


class QExample : public QObject
{
    Q_OBJECT

    QWebdav w;
    QWebdavDirParser p;
    QString m_path;
    QList<QNetworkReply *> m_replyList;
    QTimer m_timeout_timer;

public:
    QExample(QObject* parent = 0);
    void setUrl(const QUrl &url);

signals:

public slots:
    void printList();
    void printError(QString errorMsg);
    void replySkipRead();

public:
    void start();

};

#endif // QEXAMPLE_H

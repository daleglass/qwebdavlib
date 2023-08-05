#include "qexample.h"

QExample::QExample(QObject *parent) :
    QObject(parent), m_timeout_timer(this)
{

    connect(&p, SIGNAL(finished()), this, SLOT(printList()));
    connect(&p, SIGNAL(errorChanged(QString)), this, SLOT(printError(QString)));
    connect(&w, SIGNAL(errorChanged(QString)), this, SLOT(printError(QString)));
    m_path = "/";

    connect(&m_timeout_timer, &QTimer::timeout, this, []() {
        qWarning() << "Timed out!";
        QCoreApplication::exit(3);
    });
}

void QExample::setUrl(const QUrl &url) {
    qInfo() << "Requesting" << url;

    w.setConnectionSettings(url);

}

void QExample::printList()
{
    QList<QWebdavItem> list = p.getList();

    QWebdavItem item;
    qInfo() << "=== Received list ===";
    foreach(item, list) {
        qDebug() << item.name() << item.size() << item.lastModified();

        //QNetworkReply *reply = w.get(item.path());
        //connect(reply, SIGNAL(readyRead()), this, SLOT(replySkipRead()));
        //m_replyList.append(reply);
    }

    QCoreApplication::exit(0);
}

void QExample::printError(QString errorMsg)
{
    qDebug() << "QWebdav::printErrors()  errorMsg == " << errorMsg;
}

void QExample::replySkipRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply==0)
        return;

    QByteArray ba = reply->readAll();

    qDebug() << "QWebdav::replySkipRead()   skipped " << ba.size() << " reply->url() == " << reply->url().toString(QUrl::RemoveUserInfo);
}

void QExample::start()
{
    if (!p.listDirectory(&w, m_path)) {
        qCritical() << "ListDirectory failed, aborting";
        QCoreApplication::exit(2);
    } else {
        // Make sure we eventually terminate
        m_timeout_timer.start(10000);
    }
}

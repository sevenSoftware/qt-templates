#include "httpclass.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

HttpClass::HttpClass()
{

}

void HttpClass::ClearHeaders()
{
    par_headers.clear();
}

void HttpClass::AddHeaders(const QString &key, const QString &value)
{
    par_headers.insert(key, value);
}

void HttpClass::SetUserAgent(const QString &user_agent)
{
    par_user_agent = user_agent;
}

void HttpClass::SetContentType(const QString &content_type)
{
    par_content_type = content_type;
}

QString HttpClass::Get(const QString &url)
{
    qDebug() << "GET : " + url;
    QNetworkAccessManager http;
    QNetworkRequest request;
    QMap<QString, QString>::iterator it;
    for (it = par_headers.begin(); it != par_headers.end(); ++it)
        request.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
    request.setHeader(request.UserAgentHeader, par_user_agent);
    request.setUrl(url);
    QNetworkReply * reply = http.get(request);
    QEventLoop wait;
    QObject::connect(&http, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(par_timeout, &wait, SLOT(quit()));
    wait.exec();
    QString str;
    if (reply->isReadable())
        str = reply->readAll();
    reply->deleteLater();
    return str;
}

QString HttpClass::Post(const QString &url, const QString &data)
{
    qDebug() << "POST : " + url;
    qDebug() << data;
    QNetworkAccessManager http;
    QNetworkRequest request;
    QMap<QString, QString>::iterator it;
    for (it = par_headers.begin(); it != par_headers.end(); ++it)
        request.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
    request.setHeader(request.UserAgentHeader, par_user_agent);
    request.setHeader(request.ContentTypeHeader, par_content_type);
    request.setUrl(url);
    QNetworkReply * reply = http.post(request, data.toUtf8());
    QEventLoop wait;
    QObject::connect(&http, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(par_timeout, &wait, SLOT(quit()));
    wait.exec();
    QString str;
    if (reply->isReadable())
        str = reply->readAll();
    reply->deleteLater();
    return str;
}

QString HttpClass::MD5(const QString &s)
{
    return QString(QCryptographicHash::hash(s.toUtf8(), QCryptographicHash::Md5).toHex());
}

QString HttpClass::Par(const QString &s)
{
    QString str = QUrl::toPercentEncoding(s);
    str = str.replace(QUrl::toPercentEncoding("_"), "_");
    str = str.replace(QUrl::toPercentEncoding(" "), "+");
    return str;
}

QString HttpClass::RandText(int count)
{
    QString str_a = "qwrtypsdfghjklzxcvbnm";
    QString str_b = "euioa";
    QString res;
    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
            res += str_a.at(Random(str_a.length()));
        else
            res += str_b.at(Random(str_b.length()));
    }
    return res;
}

void HttpClass::Randomize()
{
    QTime time(0, 0, 0);
    qsrand(time.secsTo(QTime::currentTime()));
}

int HttpClass::Random(int count)
{
    return qrand() % count;
}


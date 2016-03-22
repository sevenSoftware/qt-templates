#ifndef HTTPCLASS_H
#define HTTPCLASS_H

#include <QMap>

class HttpClass
{
    int par_timeout = 10000;
    QString par_user_agent;
    QString par_content_type;
    QMap<QString, QString> par_headers;
public:
    HttpClass();
    void ClearHeaders();
    void AddHeaders(const QString &key, const QString &value);
    void SetUserAgent(const QString &user_agent);
    void SetContentType(const QString &content_type);
    QString Get(const QString &url);
    QString Post(const QString &url, const QString &data);
    static QString MD5(const QString &s);
    static QString Par(const QString &s);
    static QString RandText(int count);
    static void Randomize();
    static int Random(int count);

};

#endif // HTTPCLASS_H

#ifndef APIPACCOUNT_H
#define APIPACCOUNT_H

#include <QStringList>

class APIAccount
{
private:
    QString parEmail;
    QString parPassword;
    QString parUid;
    QString parToken;
    QString errorString;
public:
    APIProxy();    
    static const CianAPIAccount fromString(const QString &string) const {
        APIAccount acc;
        QStringList params = string.split(":");
        if (params.count() == 2)
        {
           APIAccount acc;
           acc.setEmail(params.at(0));
           acc.setPassword(params.at(1));
        }
        return acc;
    }

    void setEmail(const QString &email) {
        parEmail = email;
    }

    void setPassword(const QString &password) {
        parPassword = password;
    }

    void setUid(const QString &uid) {
        parUid = uid;
    }

    void setToken(const QString &token) {
        parToken = token;
    }

    const QString &getEmail() const {
        return parEmail;
    }

    const QString &getPassword() const {
        return parPassword;
    }

    const QString &getUid() const {
        return parUid;
    }

    const QString &getToken() const {
        return parToken;
    }

    bool auth();

    const QString &getError() {
        return errorString;
    }

};

#endif // APIACCOUNT_H

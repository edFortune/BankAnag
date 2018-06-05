#ifndef FIRESTORERESTAPIMANAGER_H
#define FIRESTORERESTAPIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>


class FirestoreRestApiManager : public QObject
{
    Q_OBJECT
public:
    explicit FirestoreRestApiManager(QObject *parent = 0);

    void postRequest(QString url);
signals:
    void dataReadyRead(QByteArray);

public slots:
    void onFinished(QNetworkReply*);
    void onSSlErrors(QNetworkReply*, const QList<QSslError> & errors);

private:
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
};

#endif // FIRESTORERESTAPIMANAGER_H

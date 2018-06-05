#include "firestorerestapimanager.h"


FirestoreRestApiManager::FirestoreRestApiManager(QObject *parent) : QObject(parent)
{

    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    connect(qnam, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )), this, SLOT(onSSlErrors(QNetworkReply*, const QList<QSslError> & )));
}

void FirestoreRestApiManager::postRequest(QString url)
{

//    QSslSocket *socket = new QSslSocket( this );
//    socket->addDefaultCaCertificate ( ":/Certs/thawte1.cer" );
//    socket->addDefaultCaCertificate ( ":/Certs/thawte2.cer" );
//    // Several more certs ...
//    socket->addDefaultCaCertificate ( ":/Certs/thawte9.cer" );

//    QSslConfiguration conf;
//    conf.setCaCertificates( socket->caCertificates() );
//    request.setSslConfiguration( conf );

    // Ignore SSL Errors [Comment out before production]
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);

    QNetworkRequest nq;
    nq.setUrl(QUrl(url));
    //nq.setSslConfiguration(sslConf);


    this->qnam->get(nq);

}

void FirestoreRestApiManager::onFinished(QNetworkReply *reply)
{
    QByteArray data;
    data = reply->readAll();
    emit(dataReadyRead(data));
}

void FirestoreRestApiManager::onSSlErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    QByteArray myData;
    myData = reply->readAll();
    emit(dataReadyRead(myData));
}

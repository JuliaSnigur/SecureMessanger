#include "stdafx.h"
#include "ClientConnect.h"
#include"parsedata.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbclientpresenter.h"

ClientConnection::ClientConnection(QObject *parent) :
    QObject(parent)
  , m_client(nullptr)
  ,m_user()
  ,m_idFriend()
  , m_db()
{

}

ClientConnection::~ClientConnection()
{
}

void ClientConnection::start(const QString& hostName,int port)
{
    m_client=new QSslSocket(this);

    if(m_client==nullptr)
    {
        qDebug()<<"Start client: m_client=nullptr";
        return ;
    }
// sertificate includes private key ecryption
    m_client->addCaCertificates("../../secure/sslserver.pem");
    m_client->connectToHostEncrypted(hostName, port);
    m_client->setProtocol(QSsl::TlsV1_2);

    connect(m_client,&QSslSocket::encrypted,this, &ClientConnection::slotEncrypted);
    connect(m_client,&QSslSocket::readyRead,this,&ClientConnection::slotReadyRead);
    connect(m_client, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(sslError(QList<QSslError>)) );
    connect(m_client,&QSslSocket::disconnected, this, &ClientConnection::slotDisconnect);


}

 void ClientConnection::sslError( QList<QSslError> errors )
 {
     QString erroStr="";
     foreach (const QSslError &e, errors)
         erroStr.append(e.errorString()).append("\n");

    qDebug()<<erroStr;

     m_client->ignoreSslErrors();
 }

void ClientConnection::slotDisconnect()
{
    m_client->disconnectFromHost();
}


void ClientConnection::slotEncrypted()
{
    qDebug()<<"Mode is encryped";
}



 void  ClientConnection::slotReadyRead()
 {
     QString message = m_client->readAll();    // Read message
     qDebug()<<"Client got-> " << message;

     QString time=StringHandlNamespace::variable(message);

     qDebug()<<"Time: "<<time;
         switch((StringHandlNamespace::variable(message)).toInt())
         {

         case Error:
             qDebug()<<"Upss.. "<<message;
             break;

         case Connection:

            qDebug()<<message;
            emit signalSendInfo();
                 break;

         case Registration:

             qDebug()<<"Success registration";

             // create db
             m_db.createDB("Client_"+m_user.getLogin()+".db");

             // insert user into tables session
             if(m_db.insertUser(m_user))
                 qDebug()<<"User was added";

             qDebug()<<"GetID";
             m_user.setID(StringHandlNamespace::variable(message).toInt());

             // get lists of clients who are online
             sendToServer(QString::number(GetNewList));

                 break;

             case Authorization:
             qDebug()<<"Success authorization";

             // create db
             m_db.createDB("Client_"+m_user.getLogin()+".db");



             if(m_db.insertUser(m_user))
                  qDebug()<<"User was added";
             else
                  qDebug()<<"User exists";


             // get lists of clients who are online
             sendToServer(QString::number(GetNewList));

                 break;

             case Message:
             qDebug()<<message;

             m_idDialog=m_db.searchIdDialog(m_idFriend,m_user.getID());

             if(m_idDialog<0)
             {
                 qDebug()<<"The dialog dosn't exist";
             }
             else
                m_db.insertMessage(message,m_idDialog);

             emit signalSendMessage();
                 break;

             case File:
                 break;

         case GetNewList:
             qDebug()<<"GetNewList";
             emit signalGetListsClients(StringHandlNamespace::separateVec(message));
             break;
    }
 }

 void ClientConnection::sendToServer(const QString& message)
 {
     if(m_client!=nullptr)
    {
         qDebug()<<"Client sent-> "<< QTime::currentTime().toString()+' '+message;
         m_client->write((QTime::currentTime().toString()+' '+message).toLocal8Bit());
     }
     else
         qDebug()<<"SendToServer: m_client=nullptr";

 }

 void ClientConnection::registration(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);

    sendToServer(QString::number(Registration)+' '+login +' '+pass);
 }
 void ClientConnection::authorization(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);

    sendToServer(QString::number(Authorization)+' '+login +' '+pass);
 }
 void ClientConnection::sendMessage(const QString& mess)
 {
    sendToServer(QString::number(Message)+' '+QString::number(m_user.getID())+' '+QString::number(m_idFriend)+' '+mess);

 }

 void ClientConnection::setIdFriend(int id)
 {
    m_idFriend= id;

    if(m_user.getID()==1)
        m_idFriend=2;
    else
        m_idFriend=1;

    m_db.insertDialog(m_user.getID(),m_idFriend);

 }






 ///////////////////////////////////////////////
void ClientConnection::run()
{
    QString hostName = "127.0.0.1";    // DO NOT CHANGE THIS AS IT MUST MATCH THE FQDN OF THE CERTIFICATE (you MUST create your own certificate in order to change this)
    quint16 port = 22333;

    QSslSocket sslSocket;
    sslSocket.addCaCertificates("../../SslProject/sslserver.pem");
    sslSocket.connectToHostEncrypted(hostName, port);

    if (sslSocket.waitForEncrypted(-1))    // Wait until encrypted connection is established, -1 means no timeout
    {
        qDebug() << "Connected";
        sslSocket.write("Hello, World!");    // Send message to the server

        if (sslSocket.waitForBytesWritten(-1))    // Wait until message is sent (also makes QSslSocket flush the buffer)
            qDebug() << "Message sent";
        else
            qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";

        while (!sslSocket.waitForDisconnected())    // Wait until disconnected
            QThread::msleep(10);

        qDebug() << "Disconnected";
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
    }

   // this->deleteLater();
    //QThread::currentThread()->quit();
    //qApp->exit();
}

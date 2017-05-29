#include "chat.h"
#include "ui_chat.h"
#include <QRegExp>
#include <iostream>

Chat::Chat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));

}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_loginButton_clicked()
{
    std::cerr << "Server\n";
    socket->connectToHost("Server", 4200);
    std::cerr << socket->errorString().toStdString();

}


void Chat::on_sendButton_clicked()
{

    QString message = ui->Message->toPlainText().trimmed();


    if(!message.isEmpty())
    {
        socket->write(QString(message + "\n").toUtf8());
    }


    ui->Message->clear();


    ui->Message->setFocus();
}


void Chat::readyRead()
{

    while(socket->canReadLine())
    {

        QString line = QString::fromUtf8(socket->readLine()).trimmed();


        QRegExp messageRegex("^([^:]+):(.*)$");


        QRegExp usersRegex("^/users:(.*)$");


        if(usersRegex.indexIn(line) != -1)
        {

            QStringList users = usersRegex.cap(1).split(",");
            ui->Clients->clear();
        }

        else if(messageRegex.indexIn(line) != -1)
        {

            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);

            ui->Chatbox->append("<b>" + user + "</b>: " + message);
        }
    }
}


void Chat::connected()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);

    socket->write(QString("/me:" + ui->Nickname->text() + "\n").toUtf8());
}

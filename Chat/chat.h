#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();

private slots:
    void on_loginButton_clicked();
    void on_sendButton_clicked();
    void connected();
    void readyRead();

private:
    Ui::Chat *ui;
    QTcpSocket *socket;
};

#endif // CHAT_H

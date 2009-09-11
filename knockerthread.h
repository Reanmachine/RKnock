#ifndef KNOCKERTHREAD_H
#define KNOCKERTHREAD_H

#include <QThread>
#include <QList>
#include <QAbstractSocket>

class KnockerThread : public QThread
{
private:
    Q_OBJECT

    QString     host;
    QList<int>  *sequence;

    bool        wait;
    bool        die;
    bool        result;

    bool knockPort(int port);

public:
    KnockerThread(QString host, QList<int> *seq = 0);
    ~KnockerThread();

    void run();
public slots:
    void catchError(QAbstractSocket::SocketError err);
    void catchConnected();
    void catchDisconnected();
    void catchTerminated();
    void catchState(QAbstractSocket::SocketState st);
signals:
    void beginSequence();
    void endSequence();

    void step();
    void status(QString msg);
};

#endif // KNOCKERTHREAD_H

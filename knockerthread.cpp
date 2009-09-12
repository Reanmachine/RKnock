#include <QTcpSocket>

#include "knockerthread.h"

KnockerThread::KnockerThread(QString host, QList<int> *seq)
{
    this->host = host;
    this->sequence = new QList<int>();

    // Make a local copy of the list, don't want to run into thread saftey concerns
    // while running.
    if (seq != 0)
    {
        for (int i = 0; i< seq->size(); i++)
            this->sequence->append(seq->at(i));
    }
}

KnockerThread::~KnockerThread()
{
    delete this->sequence;
}

void KnockerThread::run()
{
    this->die = false;
    this->beginSequence();
    this->status("Beginning Knock Sequence...");

    for(int i = 0; i < this->sequence->size(); i++)
    {
        if (this->die)
            break;

        int port = this->sequence->at(i);
        this->status(QString("Knocking Port %1...").arg(port));

        if (this->knockPort(port))
        {
            this->status("SUCCESS!");
        }
        else
        {
            this->status("FAILED!");
        }
    }

    this->status("Finished Knock Sequence...");
    this->endSequence();
}

bool KnockerThread::knockPort(int port)
{
    QTcpSocket socket(this);
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(catchError(QAbstractSocket::SocketError)));
    connect(&socket, SIGNAL(connected()), this, SLOT(catchConnected()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(catchDisconnected()));
    connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(catchState(QAbstractSocket::SocketState)));

    this->result = false;
    this->wait = true;
    socket.connectToHost(this->host, (quint16)port);

    /*while(wait)
    {
        QThread::yieldCurrentThread();
    }*/

    bool res = socket.waitForConnected(100);
    //socket.close(); // Close Immediately!


    step();

    return result;
}

void KnockerThread::catchError(QAbstractSocket::SocketError err)
{
    switch(err)
    {
        case QAbstractSocket::ConnectionRefusedError:
        case QAbstractSocket::RemoteHostClosedError:
        case QAbstractSocket::SocketTimeoutError:
            this->wait = false;
            this->result = true;
            break;
        default:
            this->wait = false;
            this->result = false;
            break;
    }
}

void KnockerThread::catchConnected()
{
    this->wait = false;
    this->result = true;
}

void KnockerThread::catchDisconnected()
{
    this->wait = false;
    this->result = true;
}

void KnockerThread::catchTerminated()
{
    this->wait = false;
    this->die = true;
}

void KnockerThread::catchState(QAbstractSocket::SocketState st)
{
    switch(st)
    {
        case QAbstractSocket::UnconnectedState:
            this->status("State: Unconnected");
            break;
        case QAbstractSocket::HostLookupState:
            this->status("State: HostLookup");
            break;
        case QAbstractSocket::ConnectingState:
            this->status("State: Connecting");
            break;
        case QAbstractSocket::ConnectedState:
            this->status("State: Connected");
            break;
        case QAbstractSocket::BoundState:
            this->status("State: Bound");
            break;
        case QAbstractSocket::ClosingState:
            this->status("State: Closing");
            break;
        case QAbstractSocket::ListeningState:
            this->status("State: Listening");
            break;

        default:
            this->status("State: Unknown");
    }
}

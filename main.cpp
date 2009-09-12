#include <QtGui/QApplication>
#include "core.h"
#include "basewindow.h"

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtGui/QMessageBox>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("RKnock");
    a.setApplicationVersion(RKNOCK_VERSION);
    a.setOrganizationName("Reanmachine");
    a.setOrganizationDomain("reanmachine.com");
    a.setQuitOnLastWindowClosed(false);


    BaseWindow w;
    //w.show();
    return a.exec();
}

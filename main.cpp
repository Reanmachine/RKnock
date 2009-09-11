#include <QtGui/QApplication>
#include "basewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("RKnock");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("Reanmachine");
    a.setOrganizationDomain("reanmachine.com");

    BaseWindow w;
    //w.show();
    return a.exec();
}

#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGui/QWidget>

namespace Ui
{
    class BaseWindow;
}

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

private:
    Ui::BaseWindow *ui;
};

#endif // BASEWINDOW_H

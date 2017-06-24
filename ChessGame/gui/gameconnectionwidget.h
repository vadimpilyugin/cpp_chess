#ifndef GAMECONNECTIONWIDGET_H
#define GAMECONNECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class GameConnectionWidget;
}

class GameConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameConnectionWidget(QWidget *parent = 0);
    ~GameConnectionWidget();
public slots:
    void ipAddressChanged(const QString& ip);
    void connectButtonReleased();
    void cancelButtonReleased();
signals:

private:
    Ui::GameConnectionWidget *ui;
};

#endif // GAMECONNECTIONWIDGET_H

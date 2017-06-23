#include "gameconnectionwidget.h"
#include "ui_gameconnectionwidget.h"

#include <string>

bool isValidIPv4Block(std::string& block) {
    int num = 0;
    if (block.size() > 0 && block.size() <= 3) {
        for (int i = 0; i < block.size(); i++) {
            char c = block[i];
            // special case: if c is a leading zero and there are characters left
            if (!isalnum(c) || (i == 0 && c == '0' && block.size() > 1))
            return false;
            else {
            num *= 10;
            num += c - '0';
            }
        }
        return num <= 255;
    }
    return false;
}

GameConnectionWidget::GameConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameConnectionWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->ipLineEdit,&QLineEdit::textChanged,this,&GameConnectionWidget::ipAddressChanged);
}

GameConnectionWidget::~GameConnectionWidget()
{
    delete ui;
}

void GameConnectionWidget::ipAddressChanged(const QString &ip){
    std::string blaa=ip.toLatin1().data();
    if(isValidIPv4Block(blaa)){
        ui->ipLineEdit->setStyleSheet("border: 1px solid green");
    }else{
        ui->ipLineEdit->setStyleSheet("border: 1px solid red");
    }
}

void GameConnectionWidget::connectButtonReleased()
{

}

void GameConnectionWidget::cancelButtonReleased()
{

}

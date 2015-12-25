#include "mytextedit.h"
#include <QLineEdit>
#include <iostream>

using namespace std;

MyTextEdit::MyTextEdit(){}

void MyTextEdit::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Return){
        emit returnKey_pressed(); 
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}
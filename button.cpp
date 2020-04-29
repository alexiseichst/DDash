#include "button.h"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet("QPushButton#pushButton {\
                  background-color: yellow;\
              }\
              QPushButton#pushButton:hover {\
                  background-color: rgb(224, 255, 0);\
              }\
              QPushButton#pushButton:pressed {\
                  background-color: rgb(224, 0, 0);\
              }");
}

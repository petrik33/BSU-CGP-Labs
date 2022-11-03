#ifndef BUTTONCOLOR_H
#define BUTTONCOLOR_H

#include <QWidget>
#include <QPushButton>

class ButtonColor : public QPushButton
{
    Q_OBJECT
public:
    ButtonColor(QWidget* parent = nullptr);
};

#endif // BUTTONCOLOR_H

#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include "GuiHandler.h"

class ButtonHandler : public GuiHandler {
public:
    bool canHandle(const QString& event) override {
        return event == "button_click";
    }

    void processEvent(const QString& event) override {
        qDebug() << "Кнопка обробила подію:" << event;
    }
};

#endif // BUTTONHANDLER_H

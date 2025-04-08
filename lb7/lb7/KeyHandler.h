#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include "GuiHandler.h"

class KeyHandler : public GuiHandler {
public:
    bool canHandle(const QString& event) override {
        return event == "key_press";
    }

    void processEvent(const QString& event) override {
        qDebug() << "Клавіатура обробила подію:" << event;
    }
};

#endif // KEYHANDLER_H

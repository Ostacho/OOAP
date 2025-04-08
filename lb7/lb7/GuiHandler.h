#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QString>
#include <QDebug>

class GuiHandler {
protected:
    GuiHandler* nextHandler = nullptr;

public:
    virtual ~GuiHandler() {}

    void setNext(GuiHandler* handler) {
        nextHandler = handler;
    }

    void handleEvent(const QString& event) {
        if (canHandle(event)) {
            processEvent(event);
        } else if (nextHandler) {
            nextHandler->handleEvent(event);
        } else {
            qDebug() << "Подія не оброблена:" << event;
        }
    }

    virtual bool canHandle(const QString& event) = 0;
    virtual void processEvent(const QString& event) = 0;
};

#endif // GUIHANDLER_H

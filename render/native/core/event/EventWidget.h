#pragma once

#include <string>
#include <map>

#include <QEvent>
#include <QObject>

// class to unify all the custom features + add extra features if needed
class EventWidget {
  public:
    std::map<std::string, bool> registerEvents;

    void addEventListener(std::string eventType);
    void removeEventListener(std::string eventType);

    bool isEventRegist(std::string eventType);

    bool event(QEvent* event, const char* uid, std::string eventType, QObject* eventTarget);
};


#include "EventWidget.h"
#include "core/jsUtils/event/Event.h"

void EventWidget::addEventListener (std::string eventType) {
    this->registerEvents.insert({ eventType, true });
};

void EventWidget::removeEventListener (std::string eventType) {
    this->registerEvents.erase(eventType);
    delete &eventType;
};

bool EventWidget::isEventRegist(std::string eventType) {
    return this->registerEvents.count(eventType) > 0;
};

bool EventWidget::event(QEvent* event, const char* uid, std::string eventType) {
    return FireEventToJS(event, uid, eventType);
};
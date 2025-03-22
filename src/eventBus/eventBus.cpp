#include "../../include/eventBus/eventBus.h"
using namespace std;

void EventBus::registerListener(string eventString, GameObject *listenerObject)
{
    cout << "register Event listener for "<< eventString.c_str() << endl;
    listeners[eventString].push_back(listenerObject);
    return;
}

void EventBus::event(string eventString, string eventObject)
{
    for (GameObject *obj : listeners[eventString])
    {
        if (eventString != "mouseWheelMoved")
        {
        cout << "triggering: " + eventString << endl;
        }
        obj->event(eventString, eventObject);
    }
}
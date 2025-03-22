#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <map>
#include "../../include/gameObject/gameObject.h"
#include <vector>
#include <string>
using namespace std;


class EventBus
{
 private:
    map<string,vector<GameObject*>> listeners; 
 public:
    void registerListener(string eventString, GameObject* listenerObject);

    void event(string eventString, string eventObject);


};

#endif
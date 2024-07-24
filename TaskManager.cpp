#include "Person.h"
#include "Task.h"
#include "TaskManager.h"
#include <string>

using namespace std;

void TaskManager::assignTask(const string &personName, const Task &task) {
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i]->getName()) {
            people[i]->assignTask(task);
            return;
        }
    }
    if (peopleSize == 10) {
        //return error
    } else {
        Person new_man(personName);
        people[peopleSize] = &new_man;
        peopleSize++;
    }
}

void TaskManager::completeTask(const string &personName) {

}

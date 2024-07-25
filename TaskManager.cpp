#include "Person.h"
#include "Task.h"
#include "TaskManager.h"
#include <string>

using namespace std;

void TaskManager::assignTask(const string &personName,
                             const Task &task) {//check for memory leak here since im making a new object
    Task newTask(task);
    if (task.getPriority() < 0 || task.getPriority() > 100) {
        //error handling
    }
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i]->getName()) {

            newTask.setId(++task_counter);
            people[i]->assignTask(newTask);
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
    //need to add try and catch for when complete task throws an exception
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i]->getName()) {
            people[i]->completeTask();
        }
    }
}

void TaskManager::printAllEmployees() const {
    for (int i = 0; i < peopleSize; ++i) {
        cout << people[i] << endl;
    }
}



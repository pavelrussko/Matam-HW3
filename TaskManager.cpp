#include "Person.h"
#include "Task.h"
#include "TaskManager.h"
#include <string>

using namespace std;

void TaskManager::assignTask(const string &personName,
                             const Task &task) {//check for memory leak here since im making a new object
    Task newTask(task);
    if (task.getPriority() < 0 || task.getPriority() > 100) {
        throw std::runtime_error("priority should only be between 0 and 100");
    }
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i]->getName()) {

            newTask.setId(++task_counter);
            people[i]->assignTask(newTask);
            return;
        }
    }
    if (peopleSize == 10) {
        throw std::runtime_error("Reached maximum amount of people");
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
            try {
                people[i]->completeTask();
            }
            catch (runtime_error &error) {
                break;
            }
        }
    }
}

void TaskManager::printAllEmployees() const {
    //need to addd a throw for when there arent people or no tasks
    for (int i = 0; i < peopleSize; ++i) {
        cout << people[i] << endl;
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> allTasks; //need to add a throw when there are no people or such
    for (int i = 0; i < peopleSize; ++i) {
        const SortedList<Task> &tasks = people[i]->getTasks();
        for (SortedList<Task>::ConstIterator it = tasks.begin();
             it != tasks.end(); ++it) {
            allTasks.insert(*it);
        }
    }

    for (SortedList<Task>::ConstIterator it = allTasks.begin();
         it != allTasks.end(); ++it) {
        std::cout << *it << std::endl;
    }
}


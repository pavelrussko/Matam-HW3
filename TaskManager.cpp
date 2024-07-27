#include "Person.h"
#include "Task.h"
#include "TaskManager.h"
#include <string>

using namespace std;

TaskManager::TaskManager():
    peopleSize(0),
    task_counter(0),
    people(new Person*[MAX_PERSONS]{nullptr}){}

void TaskManager::assignTask(const string &personName, const Task &task) {
    if (task.getPriority() < 0 || task.getPriority() > 100) {
        throw std::runtime_error("priority should only be between 0 and 100");
    }
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i]->getName()) {
            Task newTask = task;
            newTask.setId(task_counter++);
            people[i]->assignTask(newTask);
            return;
        }
    }
    if (peopleSize == 10) {
        throw std::runtime_error("Reached maximum amount of people");
    } else {
        people[peopleSize] = new Person(personName);
        Task newTask = task;
        newTask.setId(task_counter++);
        people[peopleSize]->assignTask(newTask);
        peopleSize++;
    }
}

TaskManager::~TaskManager() {
    for (int i = 0; i < peopleSize; ++i) {
        delete people[i];
    }
    delete[] people;
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    for (int i = 0; i < peopleSize; ++i) {
        if(people[i] == nullptr)
            continue;
        SortedList<Task> new_tasks_list;
        const SortedList<Task>& persons_tasks = people[i]->getTasks();
        for (const Task& task: persons_tasks) {
            if(task.getType() == type){
                Task temp(task.getPriority() + priority, type, task.getDescription());
                temp.setId(task.getId());
                new_tasks_list.insert(temp);
            } else {
                Task temp(task.getPriority(), task.getType(), task.getDescription());
                temp.setId(task.getId());
                new_tasks_list.insert(temp);
            }
        }
        people[i]->setTasks(new_tasks_list);
    }
}

void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i]->getName()) {
            try {
                people[i]->completeTask();
            }
            catch (const runtime_error &error) {
                std::cerr << "Error completing task: " << error.what() << std::endl;
            }
        }
    }
}

void TaskManager::printAllEmployees() const {
    if (peopleSize == 0) {
        throw std::runtime_error("No employees available");
    }
    for (int i = 0; i < peopleSize; ++i) {
        if (people[i] != nullptr) {
            std::cout << *people[i] << std::endl;
        }
    }
}

void TaskManager::printAllTasks() const {
    if (peopleSize == 0) {
        throw std::runtime_error("No tasks available");
    }
    SortedList<Task> allTasks;
    for (int i = 0; i < peopleSize; ++i) {
        if (!people[i])
            continue;
        const SortedList<Task> &tasks = people[i]->getTasks();
        for (const Task& task : tasks) {
            allTasks.insert(task);
        }
    }
    for (SortedList<Task>::ConstIterator it = allTasks.begin(); it != allTasks.end(); ++it) {
        std::cout << *it << std::endl;
    }
}
void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> tasks_by_type;
    for (int i = 0; i < peopleSize; ++i) {
        if(people[i] == nullptr)
            continue;
        const SortedList<Task>& tasks = people[i]->getTasks();
        for(const Task& task : tasks){
            if(task.getType() == type) {
                Task temp(task.getPriority(), type, task.getDescription());
                temp.setId(task.getId());
                tasks_by_type.insert(temp);
            }
        }
    }
    for(const Task& task : tasks_by_type){
        std::cout << task << std::endl;
    }
}


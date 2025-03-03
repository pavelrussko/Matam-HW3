#include "Person.h"
#include "Task.h"
#include "TaskManager.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

TaskManager::TaskManager() : peopleSize(0), task_counter(0) {}

void TaskManager::assignTask(const string &personName, const Task &task) {
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i].getName()) {
            Task newTask = task;
            newTask.setId(task_counter++);
            people[i].assignTask(newTask);
            return;
        }
    }
    if (peopleSize == MAX_PERSONS) {
        throw std::runtime_error("Reached maximum amount of people");
    } else {
        people[peopleSize] = Person(personName);
        Task newTask = task;
        newTask.setId(task_counter++);
        people[peopleSize].assignTask(newTask);
        peopleSize++;
    }
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority < 0) {
        return;
    }
    for (int i = 0; i < peopleSize; ++i) {
        SortedList<Task> new_tasks_list;
        const SortedList<Task> &persons_tasks = people[i].getTasks();
        for (const Task &task: persons_tasks) {
            if (task.getType() == type) {
                Task temp(task.getPriority() + priority, type,
                          task.getDescription());
                temp.setId(task.getId());
                new_tasks_list.insert(temp);
            } else {
                Task temp(task.getPriority(), task.getType(),
                          task.getDescription());
                temp.setId(task.getId());
                new_tasks_list.insert(temp);
            }
        }
        people[i].setTasks(new_tasks_list);
    }
}

void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < peopleSize; ++i) {
        if (personName == people[i].getName()) {
            people[i].completeTask();
        }
    }
}

void TaskManager::printAllEmployees() const {
    if (peopleSize == 0) {
        return;
    }
    for (int i = 0; i < peopleSize; ++i) {
        std::cout << people[i] << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    if (peopleSize == 0) {
        return;
    }
    SortedList<Task> allTasks;
    for (int i = 0; i < peopleSize; ++i) {
        const SortedList<Task> &tasks = people[i].getTasks();
        for (const Task &task: tasks) {
            allTasks.insert(task);
        }
    }
    for (const Task &allTask: allTasks) {
        std::cout << allTask << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> tasks_by_type;
    for (int i = 0; i < peopleSize; ++i) {
        const SortedList<Task> &tasks = people[i].getTasks();
        for (const Task &task: tasks) {
            if (task.getType() == type) {
                Task temp(task.getPriority(), type, task.getDescription());
                temp.setId(task.getId());
                tasks_by_type.insert(temp);
            }
        }
    }
    for (const Task &task: tasks_by_type) {
        std::cout << task << std::endl;
    }
}

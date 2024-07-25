#include "Person.h"
#include "Task.h"
#include "TaskManager.h"
#include <string>

using namespace std;

TaskManager::TaskManager():
    peopleSize(0),
    task_counter(0),
    people(new Person*[MAX_PERSONS]{nullptr}){}

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
        if(!people[i])
            continue;
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
void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> tasks_by_type;
    for (int i = 0; i < peopleSize; ++i) {
        if(people[i] == nullptr)
            continue;
        const SortedList<Task>& tasks = people[i]->getTasks();
        for(const Task& task : tasks){
            Task temp(task.getPriority(), type, task.getDescription());
            temp.setId(task.getId());
            tasks_by_type.insert(temp);
        }
    }
    for(const Task& task : tasks_by_type){
        std::cout << task << std::endl;
    }
}


#include "TaskManager.h"

TaskManager::TaskManager() : employeeCount(0), nextTaskId(0) {}

void TaskManager::assignTask(const string &personName, const Task &task){
    int index = -1;
    for(int i=0; i < employeeCount; i++){
        if(employees[i].getName() == personName){
            index = i;
        }
    }
    if(index == -1 && employeeCount == MAX_PERSONS){
        throw std::runtime_error("Max employees");
    }
    if(index == -1){
        employees[employeeCount] = Person(personName);
        index = employeeCount++;
    }
    Task assignedTask = task;
    assignedTask.setId(nextTaskId++);
    employees[index].assignTask(assignedTask);
}

void TaskManager::completeTask(const string &personName){
    for(int i=0; i < employeeCount; i++){
        if(employees[i].getName() == personName){
            employees[i].completeTask();
            return;
        }
    }
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if(priority <= 0) return;

    auto bump = [type, priority](Task t){
        if(t.getType() == type){
            Task updated(t.getPriority() + priority, t.getType(), t.getDescription());
            updated.setId(t.getId());
            return updated;
        }
        return t;
    };
    for(int i=0; i < employeeCount; i++){
        employees[i].setTasks(employees[i].getTasks().apply(bump));
    }
}

void TaskManager::printAllEmployees() const {
    for(int i = 0; i < employeeCount; i++) std::cout << employees[i] << '\n';
}

void TaskManager::printAllTasks() const {
    SortedList<Task> all;
    for(int i = 0; i < employeeCount; i++)
        for(const Task& t : employees[i].getTasks()) all.insert(t);
    for(const Task& t : all) std::cout << t << '\n';
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> all;
    for(int i = 0; i < employeeCount; i++)
        for(const Task& t : employees[i].getTasks())
            if(t.getType() == type) all.insert(t);
    for(const Task& t : all) std::cout << t << '\n';
}

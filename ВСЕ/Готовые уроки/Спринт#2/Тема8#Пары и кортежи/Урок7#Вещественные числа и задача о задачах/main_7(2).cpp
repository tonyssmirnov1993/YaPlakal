#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus
{
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo GetPersonTasksInfo(const string& person) const{
        return person_with_tasks_.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person){
        ++person_with_tasks_[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count){
        if (person_with_tasks_.count(person) == 0){
            return {};
        }
        TasksInfo current = person_with_tasks_[person];
        TasksInfo change;
        TasksInfo no_change;
        TaskStatus status = TaskStatus::NEW;
        while (status != TaskStatus::DONE){
            task_count = ChangeStatus(person, current, change, no_change, status, task_count);
            status = NextStatus(status);
        }
        return { change, no_change };
    }

private:
    map<string, TasksInfo> person_with_tasks_;

    int ChangeStatus(const string& person, const TasksInfo& current, TasksInfo& to_change, TasksInfo& no_change, TaskStatus status, int task_count){
        if (status == TaskStatus::DONE){
            return task_count;
        }
        int size = 0;
        if (current.count(status))
            size = current.at(status);
        if (size > 0){
            TaskStatus next_status = NextStatus(status);
            int N;
            if (task_count > size){
                N = size;
            }
            else {
                N = task_count;
            }
            to_change[next_status] = N;
            if (size > task_count){
                no_change[status] = size - task_count;
            }
            person_with_tasks_[person][status] -= N;
            person_with_tasks_[person][next_status] += N;
            task_count -= N;
        }
        return task_count;
    }

    TaskStatus NextStatus(TaskStatus status){
        if (status == TaskStatus::DONE){
            return status;
        }
        return static_cast<TaskStatus>(static_cast<int>(status) + 1);
    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь.
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW]             << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING]     << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE]        << " tasks are done" << endl;
}

int main()
{
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
    TasksInfo updated_tasks, untouched_tasks;
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
} 
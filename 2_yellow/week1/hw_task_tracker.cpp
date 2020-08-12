#include <iostream>
#include <tuple>
#include <map>
#include <tuple>
#include <vector>
#include <iomanip>
using namespace std;

/*
// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;
*/
class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return task_board.at(person);
	}
	  
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		task_board[person][TaskStatus::NEW] += 1;
	}
	  
	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
			const string& person, int task_count) {
		
		if (task_board.count(person) == 0) {
			return {};
		}
		auto& taskinfo = task_board[person];
		vector<TaskStatus> statuses = {TaskStatus::NEW, 
			TaskStatus::IN_PROGRESS, TaskStatus::TESTING};
		TasksInfo updates;
		TasksInfo unchanged;
		for (auto& status : statuses) {
			int n = min(taskinfo[status], task_count);
			if (n > 0) {
				updates[static_cast<TaskStatus>(static_cast<int>(status) + 1)] += n;
				taskinfo[status] -= n;
				task_count -= n;
			}
			if (taskinfo[status] > 0) {
				unchanged[status] = taskinfo[status];
			} else {
				taskinfo.erase(status);
			}
		}
		for (auto& [key,value] : updates) {
			taskinfo[key] += value;
		}
		return make_tuple(updates, unchanged);
	}

private:
	map<string, TasksInfo> task_board = {};
};


/*
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
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
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks:   ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks:   ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
*/

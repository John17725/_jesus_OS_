#define MaxLisTask 100

struct task{
	int id;
	char name_task[50];
	int priority;
	int time_execute;
}task[MaxLisTask];

struct completedtasks
{
	int id;
	char name_task[50];
	int priority;
	int time_execute;
}completedtasks[MaxLisTask];

void UploadDataTotask(int num_tasks);
void delay(int num_of_seconds);
void EmptyListTask();
void SortArray(int num_tasks);
void *ExecuteTasks(void*);
void ShowTasksFinish(int num_tasks);
void ValidateIdTask(int index, int id, int num_tasks);
void ShowTaskQueue(int num_tasks);
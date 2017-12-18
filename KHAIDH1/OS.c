
#include "OS.h"



void Task_Control()
{
	bF_TaskRunning = 1;
	do
	{
		if (bFlag_100US == 1)
		{
			
			Task_100US();
			bFlag_100US = 0; 
		}
		else if (bFlag_1MS == 1)
		{

			Task_1MS();
			bFlag_1MS = 0;
		}
		else if (bFlag_10MS == 1)
		{

			Task_10MS();
			bFlag_10MS = 0;
		}
		else if (bFlag_100MS == 1)
		{

			Task_100MS();
			bFlag_100MS = 0;
		}
		else if (bFlag_1S == 1)
		{

			Task_1S();
			bFlag_1S = 0;
		}
		else
		{
			bF_TaskRunning = 0;
		}
	} 
	while (bF_TaskRunning == 1);


}

/*ADD  Tasks */

void Task_init()
{

//	AddTask_Custom(0, &PWMLED, NULL,3);
}

void Task_RUNNING()
{

	for (int i = 0; i < count_list; i++) {
		++taskList[i].elapsedTime;
		if (taskList[i].elapsedTime == taskList[i].interval)
		{
			taskList[i].state = HIGH;
			taskList[i].elapsedTime = 0;
		}

		if (taskList[i].state == HIGH)
		{
			taskList[i].state = LOW;
			(*taskList[i].myTask)(taskList[i].param);
		}
	}
}


void AddTask_Custom(uint8_t id, void(*handleTask)(void), void *paramIn, uint16_t timer)
{
	TimerTask task = { handleTask, paramIn, timer, 0, id , 0 };
	taskList[count_list] = task;
	count_list++;
}


void AddTask_100US(uint8_t id, void(*handleTask)(void), void *paramIn)
{
	int16_t timer = 1; // 100US
	TimerTask task = { handleTask, paramIn, timer, 0, id , 0 };
	taskList[count_list] = task;
	count_list++;
}
void AddTask_1MS(uint8_t id, void(*handleTask)(void), void *paramIn)
{
	int16_t timer = 10; // 1MS
	TimerTask task = { handleTask, paramIn, timer, 0, id , 0 };
	taskList[count_list] = task;
	count_list++;
}
void AddTask_10MS(uint8_t id, void(*handleTask)(void), void *paramIn)
{
	int16_t timer = 100; // 10MS
	TimerTask task = { handleTask, paramIn, timer, 0, id , 0 };
	taskList[count_list] = task;
	count_list++;
}
void AddTask_100MS(uint8_t id, void(*handleTask)(void), void *paramIn)
{
	int16_t timer = 1000; // 100MS
	TimerTask task = { handleTask, paramIn, timer, 0, id , 0 };
	taskList[count_list] = task;
	count_list++;
}
void AddTask_1000MS(uint8_t id, void(*handleTask)(void), void *paramIn)
{
	int16_t timer = 10000; // 1S
	TimerTask task = { handleTask, paramIn, timer, 0, id , 0 };
	taskList[count_list] = task;
	count_list++;
}

void RemoveTask(uint8_t id)
{
	for (int i = 0; i < count_list; i++) {
		if (taskList[i].taskId == id) {
			--count_list;
			for (int j = i; j < count_list; j++) {
				taskList[j] = taskList[j + 1];
			}
		}
	}
}

void RemoveAllTask()
{
	count_list = 0;
}

void setInterval(uint8_t taskID, uint16_t interval) {
	for (int i = 0; i < count_list; i++) {
		if (taskList[i].taskId == taskID) {
			taskList[i].interval = interval;
			taskList[i].elapsedTime = 0;
		}
	}
}

uint8_t isTaskRunning(uint8_t taskID) {
	for (int i = 0; i < count_list; i++) {
		if (taskList[i].taskId == taskID) {
			return 1;
		}
	}
	return 0;
}


#include "scheduler.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define init_time_task  0
int option, nada, num_tasks=0;
pthread_mutex_t key;

int main(void)
{
	
	
	do{
		system("clear");
		printf("|========S=C=H=E=D=U=L=E=R========|\n");
		printf("|=========1.-Nueva tarea==========|\n");
		printf("|========2.-Listar tareas=========|\n");
		printf("|=======3.-Iniciar tareas=========|\n");
		printf("|====4.- Vaciar lista tareas======|\n");
		printf("|===========5.- Salir=============|\n");
		printf("|=================================|\n");	
		printf("Ingresa la funcion a realizar: ");
		scanf("%d", &option);
		switch (option)
		{
			case 1:
			{
				printf("Cuantos 'Tasks' agregara a la cola?:");
				scanf("%d", &num_tasks);
				UploadDataTotask(num_tasks);					
				break;
			}
			case 2:
			{
				for (int i = 0; i < 50; i++)
				{
					delay(2);
				}
				system("clear");
				printf("HISTORICO DE PROCESOS\n");
				ShowTasksFinish(num_tasks);
				printf("PROCESOS EN ESPERA DE EJECUCION\n");
				ShowTaskQueue(num_tasks);
				for (int i = 0; i < 50; i++)
				{
					delay(7);
				}
				break;
			}
			case 3:
			{
				for (int i = 0; i < num_tasks; i++)
				{
					if (task[i].time_execute==0)
					{
						printf("NO HAY PROCESOS EN COLA DE ESPERA\n");
						break;
					}else
					{
						printf("ORDENANDO TASKS POR PRIORIDAD\n");
						SortArray(num_tasks);
						for (int i = 0; i < 50; i++)
						{
							delay(3);
						}
						for (int i = 0; i < 50; i++)
						{
							delay(1);
						}
						system("clear");

						printf("IMPRIMIENDO PRIORIDAD ORDENADA\n");
						ShowTaskQueue(num_tasks);
						for (int i = 0; i < 50; i++)
						{
							delay(3);
						}
						printf("INICIALIZANDO PROCESOS\n");
						for (int i = 0; i < 50; i++)
						{
							delay(2);
						}
						printf("OK\n");
						printf("POR FAVOR ESPERE\n");
						for (int i = 0; i < 50; i++)
						{
							delay(3);
						}
						system("clear");
						pthread_t thread1;
						pthread_mutex_init(&key,NULL);
						pthread_create(&thread1,NULL,ExecuteTasks,NULL);
						pthread_join(thread1,NULL);
					}
				}
				break;
			}
			case 4:
			{
				EmptyListTask(num_tasks);
				printf("OK\n");
				for (int i = 0; i < 50; i++)
				{
					delay(3);
				}
				num_tasks = 0;
				system("clear");	
				break;
			}
			case 5:
			{
				printf("FINALIZANDO.");
				for (int i = 0; i < 50; i++)
				{
					delay(5);
					printf(".\n");	
				}
				system("clear");
				break;
			}
			default :
			{
				printf("LO SENTIMOS PERO LA OPCION INGRESADA [%d] ES INVALIDA\n", option);
				for (int i = 0; i < 50; i++)
				{
					delay(5);
				}
				system("clear");
				break;
			}
		}
	}while(option != 5);	
	return 0;
}

void delay(int num_of_seconds)
{
	int miliseconds = 10000 * num_of_seconds;
	clock_t start_time = clock();
	while(clock() < start_time + miliseconds);
}

void UploadDataTotask(int num_tasks)
{

	for (int i = 0; i < num_tasks; i++)
	{
		printf("T A S K [%d]\n", i);
		printf("Ingresa el id del task: ");
		scanf("%i", &task[i].id);
		int aux = task[i].id;
		ValidateIdTask(i,aux, num_tasks);
		printf("Ingresa el nombre del task: ");
		scanf("%s", task[i].name_task);
		printf("Ingresa la prioridad del task: ");
		scanf("%d", &task[i].priority);
		printf("Ingresa el tiempo que deseas ejecutar el task: (seg)");
		scanf("%d", &task[i].time_execute);
	}
}

void EmptyListTask(int num_tasks){
	
	for (int i = 0; i < 100; i++)
	{
		task[i].id = 0;
		strcpy(task[i].name_task,"");
		task[i].priority = 0;
		task[i].time_execute = 0;
	}
}

void SortArray(int num_tasks){
	int temporary, temprary2, temporary3;
	char temporal4[50];

	for (int i = 0;i < num_tasks; i++){
		for (int j = 0; j< num_tasks-1; j++){
			if (task[j].priority < task[j+1].priority){
				temporary = task[j].priority; 
				temprary2= task[j].id;
				temporary3=task[j].time_execute;
				strcpy(temporal4,task[j].name_task);
				task[j].priority = task[j+1].priority; 
				task[j].id = task[j+1].id;
				task[j].time_execute=task[j+1].time_execute;
				strcpy(task[j].name_task,task[j+1].name_task);
				task[j+1].priority = temporary;
				task[j+1].id=temprary2;
				task[j+1].time_execute=temporary3;
				strcpy(task[j+1].name_task,temporal4);
			}
		}
	}
	printf("OK\n");
}

void ShowTasksFinish(int num_tasks){
	char flag[20] = "FINALIZADO";
	for (int k = 0; k < num_tasks; k++)
	{
		if (task[k].time_execute == 0)
		{
			printf("|------------------------------------------------------|\n");
			printf("|=TASK[%i]\n", k);
			printf("|=TASK ID: %d\n",completedtasks[k].id);
			printf("|=NOMBRE DEL TASK: %s\n",completedtasks[k].name_task);
			printf("|=PRIORIDAD DEL TASK: %d\n",completedtasks[k].priority);
			printf("|=TIEMPO DE EJECUCION: %s\n",flag);
			printf("|------------------------------------------------------|\n\n");
		}
	}
}

void ShowTaskQueue(int num_tasks){    
	for (int k = 0; k < num_tasks; k++)
	{
		if (task[k].time_execute > 0)
		{				
			printf("|------------------------------------------------------|\n");
			printf("|=TASK[%i]\n", k);
			printf("|=TASK ID: %d\n",task[k].id);
			printf("|=NOMBRE DEL TASK: %s\n",task[k].name_task);
			printf("|=PRIORIDAD DEL TASK: %d\n",task[k].priority);
			printf("|=TIEMPO DE EJECUCION: %d\n",task[k].time_execute);
			printf("|------------------------------------------------------|\n\n");
		}
	}
}

void ValidateIdTask(int index,int id, int num_tasks){
	int a,b=0;
	for (int i = 0; i < num_tasks; i++)
	{
		if (task[i].id == id || completedtasks[i].id == id)
		{
			b=b+1;
			if (b > 1)
			{
				a = id + 1;
				printf("El id [%d] ya es usado por otra tarea use: [%d] y/o otro id\n",id,a);	
				printf("Ingresa el id del task: ");
				scanf("%i", &task[index].id);
				ValidateIdTask(index,id,num_tasks);
			}
		}
	}
}

void *ExecuteTasks(void *arg){
	printf("BLOQUEANDO HILO\n");
	for (int i = 0; i < 50; i++){
		delay(3);
	}
	pthread_mutex_lock(&key);//banderin para hacer esperar a los hilos
	printf("Hilo bloqueado\n");
	printf("EJECUTANDO PROCESOS POR PRIORIDAD");
	for (int i = 0; i < 50; i++){
		delay(3);
	}                            	                          
	for(int i = 0; i<num_tasks; i++){
		do
		{
			printf("|===============================================================|\n");
			printf("|ID TASK: [%d]\n", task[i].id);
			printf("|NOMBRE DEL TASK: [%s]\n",task[i].name_task);
			printf("|PRIORIDAD DEL TASK: [%d]\n", task[i].priority);
			printf("|TIEMPO DE EJECUCION DEL TASK: [%d]\n",task[i].time_execute);
			task[i].time_execute = task[i].time_execute - 1;
			printf("|===============================================================|\n");
			int index = i;
			completedtasks[index].id=task[index].id;
			strcpy(completedtasks[i].name_task,task[index].name_task);
			completedtasks[index].priority=task[index].priority;
			for (int i = 0; i < 50; i++)
			{
				delay(3);
			}
			system("clear");
		}while(task[i].time_execute != 0);
	}
	system("clear");
	printf("PROCESOS FINALIZADOS\n");
	for (int i = 0; i < 50; i++){
		delay(3);
	}    
	ShowTasksFinish(num_tasks);
	for (int i = 0; i < 50; i++){
		delay(4);
	}    
	pthread_mutex_unlock(&key);
	printf("HILO DESBLOQUEADOn");
	for (int i = 0; i < 50; i++){
		delay(3);
	}    
	system("clear");
	return NULL;
}
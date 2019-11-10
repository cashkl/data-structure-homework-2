/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{		
	head=NULL;
	usable_day=0;
	usable_time=0;
	
}

void WorkPlan::close()
{
	//THIS FUNCTION WILL BE CODED BY YOU
}

void WorkPlan::add(Task *task)
{
	//THIS FUNCTION WILL BE CODED BY YOU
	if(!head){
		head=task;
		task->next=head;
		task->previous=head;
		return;
	}else{
		Task *traverse = head;
		while(task->day < traverse->day && traverse->next != head){
			traverse=traverse->next;
		}
		if(traverse->day < task->day){
			task->next = traverse->next;
			task->next->previous = task;
			traverse->next = task;
			task->previous = traverse;
			task->counterpart = NULL;
			return;
		}
		else{
			
			while (traverse->counterpart != NULL && traverse->counterpart->time <= task->time )
			{
				traverse= traverse->counterpart;
			}
			if(traverse->time == task->time){
				checkAvailableNextTimesFor(task);
				task->time = usable_time;
				task->day = usable_day;
				add(task);
				return;
			}else{
				task->counterpart= traverse->counterpart;
				traverse->counterpart = task;
				return;
			}
			
		}
	}
} 

Task * WorkPlan::getTask(int day, int time)
{
	Task* traverse= head;
	while(traverse->day != day && traverse->next !=head){
		traverse = traverse->next;
	}
	if(traverse->day == day){
		while(traverse->time != time && traverse != NULL){
			traverse=traverse->counterpart;

		}
		if(traverse->time == time){
			return traverse;
		}else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{	
	Task * traverse = head;
	while(traverse->next != head || traverse == head){
		//TODO
		traverse = traverse->next;
		
	}

	traverse= head->previous;
	usable_day= traverse->day +1 ;
	usable_time = 8;
	return; 
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	//THIS FUNCTION WILL BE CODED BY YOU
}

void WorkPlan::remove(Task *target)
{
	//THIS FUNCTION WILL BE CODED BY YOU
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}

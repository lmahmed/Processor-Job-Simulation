#include "Header.h"
int Processor::processerNum = 1;
Processor::Processor()
{
	name = "CPU " + to_string(processerNum++);
	isProcessing = false;
	currentExecutionTime = 0;
	allIdleTime = 0;
	allRunTime = 0;
	totalJobsCompleted = 0;
}
void Processor::setJob(Job input)
{
	currJob = input;
	isProcessing = true;
	currentExecutionTime = 0;
}
void Processor::process()
{
	currentExecutionTime++;
	if (isProcessing)
	{
		allRunTime++;
	}
	else
	{
		allIdleTime++;
	}
}
bool Processor::isJobComplete()
{
	if (currentExecutionTime == currJob.processTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Processor::completeJob()
{
	isProcessing = false;
	currentExecutionTime = 0;
	totalJobsCompleted++;
}

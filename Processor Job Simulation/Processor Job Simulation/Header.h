#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
struct Job
{
	char type;
	int arriveTime;
	int processTime;
	int overallJobNumber;
	int typeJobNumber;
};
class Processor
{
private:
	static int processerNum;
public:
	string name;
	bool isProcessing;
	Job currJob;
	int currentExecutionTime;
	int allIdleTime;
	int allRunTime;
	int totalJobsCompleted;
	Processor();
	void setJob(Job);
	void process();
	bool isJobComplete();
	void completeJob();
};
void inputJobsList(queue <Job>&);

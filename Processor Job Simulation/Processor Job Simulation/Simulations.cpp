// Author: Latif Ahmed
#include "Header.h"
#include <iomanip>
const int numOfProcessors = 9;
const int runTime = 10000; //21910
int main()
{
	ofstream logFile("jobsim_" + to_string(numOfProcessors) +
		"_" + to_string(runTime) + ".txt");
	int totalJobA = 0;
	int totalJobB = 0;
	int totalJobC = 0;
	// Adds queue size added from each each time unit
	int totalQueueSize = 0;
	// Records all assigned job's duration in queue
	int totalTimeJobsAssigned = 0;
	// Records all jobs that were in queue at least 1 time unit
	int lifetimeJobsInQueue = 0;
	// input data file
	queue<Job> jobList;
	inputJobsList(jobList);
	Processor processor[numOfProcessors];
	queue<Job> jobQueue;
	int maxQueueSize = 0;
	int time = 1;
	while (time <= runTime)
	{
		// Check for arrivals at time
		while (!jobList.empty() && time == jobList.front().arriveTime)
		{
			logFile << "Time " << setw(4) << time << ": " << "Arrival:" << "Overall Job : " << jobList.front().overallJobNumber << ", Job " <<
				jobList.front().type << ":" << jobList.front().typeJobNumber << ", ProcessingTime " << jobList.front().processTime << "; " << endl;
				// Record number of job arrivals by type
				switch (jobList.front().type)
				{
				case 'A':
					totalJobA++;
					break;
				case 'B':
					totalJobB++;
					break;
				case 'C':
					totalJobC++;
					break;
				}
			// Move arriving job to queue
			jobQueue.push(jobList.front());
			jobList.pop();
		}
		// Do processor logic or insertion
		for (int i = 0; i < numOfProcessors; i++)
		{
			if (!processor[i].isProcessing)
			{
				if (!jobQueue.empty())
				{
					// Assign job to processor
					processor[i].setJob(jobQueue.front());
					logFile << "Time " << setw(4) << time << ": " <<
						"Begin Processing" << " Job:" << jobQueue.front().overallJobNumber << ", Job "
						<< jobQueue.front().type << ":" <<
						jobQueue.front().typeJobNumber << " in " << processor[i].name << ";" << endl;
					jobQueue.pop();
					if (!(time == processor[i].currJob.arriveTime))
					{
						lifetimeJobsInQueue++;
						totalTimeJobsAssigned += (time -
							processor[i].currJob.arriveTime);
					}
				}
				else
				{
					// increment idle time
					processor[i].process();
				}
			}
			else
			{
				// increment run time
				processor[i].process();
				if (processor[i].isJobComplete())
				{
					// Processor becomes idle
					processor[i].completeJob();
					logFile << "Time " << setw(4) << time << ": " <<
						"Complete Processing" << " Job:" << processor[i].currJob.overallJobNumber << ", Job"
						<< processor[i].currJob.type << ":" <<
						processor[i].currJob.typeJobNumber << " in " << processor[i].name << ";" << endl;
					if (!jobQueue.empty())
					{
						// Assign job to processor
						processor[i].setJob(jobQueue.front());
						logFile << "Time " << setw(4) << time << ": "
							<< "Begin Processing" << " Job:" << jobQueue.front().overallJobNumber << ", Job "
							<< jobQueue.front().type << ":" <<
							jobQueue.front().typeJobNumber << " in " << processor[i].name << ";" << endl;
						jobQueue.pop();
						// add Job assigned after arrival time and time job was in queue
							if (!(time == processor[i].currJob.arriveTime))
							{
								lifetimeJobsInQueue++;
								totalTimeJobsAssigned += (time -
									processor[i].currJob.arriveTime);
							}
					}
				}
			}
		}
		// CPU and queue status
		logFile << "Time " << setw(4) << time << ": Queue:" << jobQueue.size()
			<< "; ";
		for (int i = 0; i < numOfProcessors; i++)
		{
			logFile << processor[i].name << " ";
			if (processor[i].isProcessing)
			{
				logFile << "Run Time:" << processor[i].currentExecutionTime
					<< "; ";
			}
			else
			{
				logFile << "Idle Time:" <<
					processor[i].currentExecutionTime << "; ";
			}
		}
		logFile << endl;
		// add queue size
		totalQueueSize += jobQueue.size();
		// update maxQueueSize
		if (jobQueue.size() > maxQueueSize)
		{
			maxQueueSize = jobQueue.size();
		}
		time++;
	}
	logFile.close();
	// Metric Calculations
	// Calculate total time CPU(s) were processing
	// Calculate total time CPU(s) were idling
	// Calculate total jobs completed
	int totalTimeProcessing = 0;
	int totalTimeIdling = 0;
	int totalJobsCompleted = 0;
	for (int i = 0; i < numOfProcessors; i++)
	{
		totalTimeProcessing += processor[i].allRunTime;
		totalTimeIdling += processor[i].allIdleTime;
		totalJobsCompleted += processor[i].totalJobsCompleted;
	}
	// Metrics
	cout << "Number of processor(s) being used: " << numOfProcessors << endl;
	cout << "Current queue size: " << jobQueue.size() << endl;
	cout << "Average queue size: " << double(totalQueueSize) / runTime << endl;
	cout << "Maximum jobs in queue: " << maxQueueSize << endl;
	cout << "Total time jobs in queue: " << totalTimeJobsAssigned << " time units" << endl;
		cout << "Average time in queue: " << double(totalTimeJobsAssigned) /
		lifetimeJobsInQueue << " time units" << endl;
	cout << "Total number of jobs A arrived: " << totalJobA << endl;
	cout << "Total number of jobs B arrived: " << totalJobB << endl;
	cout << "Total number of jobs C arrived: " << totalJobC << endl;
	cout << "Total jobs completed: " << totalJobsCompleted << endl;
	cout << "Total time CPU(s) were processing: " << totalTimeProcessing << " time units" << endl;
		cout << "Total time CPU(s) were idle: " << totalTimeIdling << " time units"
		<< endl;
	return 0;
}

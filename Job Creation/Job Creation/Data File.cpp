#include <fstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
using namespace std;
struct Jobs
{
	char type;
	int arriveTime;
	int processTime;
};
// Returns sorted Jobs
vector<Jobs> sortByArrival(vector <Jobs> jobs)
{
	int count = 1;
	vector <Jobs> sortedJobs(jobs.size());
	while (jobs.size() != 0)
	{
		int maxIndex = 0;
		for (int i = 1; i < jobs.size(); i++)
		{
			if (jobs.at(i).arriveTime >= jobs.at(maxIndex).arriveTime)
			{
				maxIndex = i;
			}
		}
		// insert to end of temp vector <Jobs>
		sortedJobs.at(sortedJobs.size() - count) = jobs.at(maxIndex);
		jobs.erase(jobs.begin() + maxIndex);
		count++;
	}
	return sortedJobs;
}
int main()
{
	srand(time(0));
	const int numOfJobA = 2500;
	const int numOfJobB = 1200;
	const int numOfJobC = 450;
	const int numJobs = numOfJobA + numOfJobB + numOfJobC;
	int jobAarrival = 0;
	int jobBarrival = 0;
	int jobCarrival = 0;
	int jobCounter = 0;
	vector <Jobs> jobs(numJobs);
	vector <Jobs> sortedJobs;
	for (int i = 0; i < numOfJobA; i++)
	{
		jobAarrival += rand() % 3 + 4;
		jobs.at(jobCounter).type = 'A';
		jobs.at(jobCounter).arriveTime = jobAarrival;
		jobs.at(jobCounter).processTime = rand() % 5 + 1;
		jobCounter++;
	}
	for (int i = 0; i < numOfJobB; i++)
	{
		jobBarrival += rand() % 3 + 9;
		jobs.at(jobCounter).type = 'B';
		jobs.at(jobCounter).arriveTime = jobBarrival;
		jobs.at(jobCounter).processTime = rand() % 5 + 6;
		jobCounter++;
	}
	for (int i = 0; i < numOfJobC; i++)
	{
		jobCarrival += rand() % 3 + 24;
		jobs.at(jobCounter).type = 'C';
		jobs.at(jobCounter).arriveTime = jobCarrival;
		jobs.at(jobCounter).processTime = rand() % 5 + 9;
		jobCounter++;
	}
	sortedJobs = sortByArrival(jobs);
	ofstream outputFile("job.txt");
		for (int i = 0; i < numJobs; i++)
		{
			outputFile << left << sortedJobs.at(i).type << right << setw(7) <<
				sortedJobs.at(i).arriveTime << setw(4) << sortedJobs.at(i).processTime
				<< endl;
		}
	outputFile.close();
	return 0;
}

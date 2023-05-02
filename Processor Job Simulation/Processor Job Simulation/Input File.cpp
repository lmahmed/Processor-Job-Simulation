#include "Header.h"
void inputJobsList(queue <Job>& jobList)
{
	ifstream inputFile("job.txt");
	int typeA = 1;
	int typeB = 1;
	int typeC = 1;
	int overallJobNumber = 1;
	while (!inputFile.eof())
	{
		Job temp;
		inputFile >> temp.type >> temp.arriveTime >> temp.processTime;
		temp.overallJobNumber = overallJobNumber++;
		switch (temp.type)
		{
		case 'A':
			temp.typeJobNumber = typeA++;
			break;
		case 'B':
			temp.typeJobNumber = typeB++;
			break;
		case 'C':
			temp.typeJobNumber = typeC++;
			break;
		}
		jobList.push(temp);
	}
	inputFile.close();
}

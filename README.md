# Processor-Job-Simulation

Job Creation creates a file with a list of jobs consisting of 3 types with their arrival time, time where the job joins the queue to be assigned to a processor
, and processing time, time it takes for a processor to complete a job once assigned.
The 3 types of jobs have different ranges for arrival time increments (for that job type) and processing time.
Job A:   Arrival time increment: 4 - 6 time units      Processing time: 1 - 5 time units
Job B:   Arrival time increment: 9 - 11 time units     Processing time: 6 - 10 time units
Job C:   Arrival time increment: 24- 26 time units     Processing time: 9 - 13 time units
List is sorted by arrival time.

File should then be copied into the Processor Job Simulation's directory. 

The number of processors is determined by a constant global variable. By comparing the total idle and processing time of using different amounts of processers,
I concluded that using 2 processors was the most efficient (most jobs completed with minimal idle time) for these set of jobs.

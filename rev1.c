#include<stdio.h> 
struct process
{
      char process_name;
      int arrival_time, burst_time, ct, waiting_time, turnaround_time, priority;
      int status;
}process_queue[10];
 

# OS-project
Operating System project on Banker's Algorithm (Avoiding Deadlock)


This is a multithreaded program that implements the banker's algorithm.
n threads are created that request and release resources from the bank. 
The banker then grants the request only if it leaves the system in a safe state. 
It is important that shared data be safe from concurrent access. 
To ensure safe access to shared data mutex locks are used.

1. The program is dynamic such that the threads are created at run time based on 
the input from the user. 
2. The resources are diaplaced after each allocation. 
3. The system state is visible after each allocation



Output:-

 The number of processes are: 3

 The number of resources: 5

 The resources available currently (R1, R2 ...): R3


 Resourcees allocated to process 1 (R1, R2 ...):  
 Resourcees allocated to process 2 (R1, R2 ...):  
 Resourcees allocated to process 3 (R1, R2 ...):  

 Maximum resources required by process 1 (R1, R2, ...): 
 Maximum resources required by process 2 (R1, R2, ...): 
 Maximum resources required by process 3 (R1, R2, ...): 


Safe Sequence: 1  2  3  
Process execution.. 


--> Process 1
	 Allocated :   0  0  0  0  0
	 Need:   0  0  0  0  0
	Available :   4  5  0  0  0
	 Resource Allocated
	Process code is running.. 
	Process code completed.. 
	 Releasing Resource.. 
	 Resource Released 
	 Availability:   4  5  0  0  0
 

--> Process 2
	 Allocated :   0  0  0  0  0
	 Need:   0  0  0  0  0
	Available :   4  5  0  0  0
	 Resource Allocated
	Process code is running.. 
	Process code completed.. 
	 Releasing Resource.. 
	 Resource Released 
	 Availability:   4  5  0  0  0
 

--> Process 3
	 Allocated :   0  0  0  0  0
	 Need:   0  0  0  0  0
	Available :   4  5  0  0  0
	 Resource Allocated
	Process code is running.. 
	Process code completed.. 
	 Releasing Resource.. 
	 Resource Released 
	 Availability:   4  5  0  0  0
 

Processes Completed 

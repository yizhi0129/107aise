#include <stdio.h>
#include <signal.h> //for handling signals
#include <time.h> //for time-related functions
#include <unistd.h> //for POSIX operating system API functions (including alarm)
#include <stdlib.h>

void alarmPrint(int signum){ //to handle the SIGALRM signal
	time_t curtime;
	time(&curtime); //retrieves the current time
	printf("current time is %s", ctime(&curtime));
	alarm(1); //set another alarm to trigger after 1 second
} //print the current time at regular intervals

int main(){
	signal(SIGALRM, alarmPrint); //This line sets up the SIGALRM signal handler to be the function alarmPrint. 
	//It associates the alarmPrint function with the SIGALRM signal.
	alarm(1); //set the initial alarm to trigger after 1 second

	while(1) {
	} //This is an infinite loop that keeps the program running. 
	//The only way to exit the program is through external intervention, such as using signals (Ctrl C).

	return 0;
}




#include <stdio.h>
#include <signal.h>
#include <sys/ioctl.h>


void sig_handler(int sig)
{
	struct winsize  ws;
	ioctl(0, TIOCGWINSZ, &ws);
	
	printf("WIN changed (%d , %d)\n", ws.ws_row, ws.ws_col);
}



int main(int argc, char ** argv)
{
	signal(SIGWINCH, sig_handler);


	while(1){}

	return 0;
}

#include <sys/types.h>
#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>


void	sigint_handler(int signum)
{
	printf("signal parent int\n");
	(void)signum;
	exit(0);
}

void	sigquit_handler(int signum)
{
	printf("signal parent quit\n");
	(void)signum;
	exit(0);
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sigintc_handler(int signum)
{
	printf("signal child int\n");
	(void)signum;
	exit(0);
}

void	sigquitc_handler(int signum)
{
	printf("signal child quit\n");
	(void)signum;
	exit(0);
}

void	signals_child(void)
{
	signal(SIGINT, sigintc_handler);
	signal(SIGQUIT, sigquitc_handler);
}

int main(void)
{
	pid_t child;
	int fd;
	int status;
	struct sigaction parent;
	struct sigaction child_h;

	parent.sa_handler = &sigint_handler;
	sigaction(SIGINT, &parent, NULL);
while(1)
{
	//signals();
	child = fork();
	if (child == 0)
	{
		printf("CHILD\n");
		// signals_child();
		// child_h.sa_handler = &sigintc_handler;
		// sigaction(SIGINT, &child_h, NULL);
		while(1)
		{


		}
	}
 	else if (child > 0)
	{
		waitpid(child, &status, 0);
		printf("PARENT\n");
		printf("CHILD DIED, status = %d\n", status);
	}
	else
		printf("ERROR\n");
	return(0);
}
}

// #include <signal.h>
// #include <stdio.h>
// void mysig(int a) { printf("In mysig\n"); }

// int main(void) 
// {
//    struct sigaction info, newhandler;

//    if (sigaction(SIGCHLD,NULL,&info) != -1)
//    {
//        if (info.sa_handler == SIG_IGN)
//            printf("SIGCHLD being ignored.\n");
//        else if(info.sa_handler == SIG_DFL)
//            printf("SIGCHLD being defaulted.\n");
//    }

//    newhandler.sa_handler = &mysig;
//    sigemptyset(&(newhandler.sa_mask));
//    newhandler.sa_flags = 0;
//    if (sigaction(SIGCHLD,&newhandler,&info) != -1)
//        printf("New handler set.\n"); 
// return (0);
// }
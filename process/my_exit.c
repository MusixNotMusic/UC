#include "apue.h"
#include <sys/wait.h>
#include <sys/times.h> 


void
pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n",
                WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
                WTERMSIG(status),
        #ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
        #else
                "");
        #endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",
                WSTOPSIG(status));
}


void
pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck = 0;
    if(clktck == 0)
        if((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("sysconf error");

    printf("  real:         %7.2f\n",real / (double)clktck);
    printf("  user:         %7.2f\n",
        (tmsend->tms_utime - tmsstart->tms_utime)/(double)clktck);
    printf("  sys:          %7.2f\n", 
        (tmsend->tms_stime - tmsstart->tms_stime)/(double)clktck);
    printf("  child user:   %7.2f\n", 
        (tmsend->tms_cutime - tmsstart->tms_cutime)/(double)clktck);
    printf("  child sys:    %7.2f\n", 
        (tmsend->tms_cstime - tmsstart->tms_cstime)/(double)clktck);
}
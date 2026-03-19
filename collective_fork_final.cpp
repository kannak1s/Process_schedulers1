#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
void random_task(int id)
{
    srand(time(0));
    int delay = 1 + rand() % 3;

    std::cout << "PID " << getpid()
              << " PPID " << getppid()
              << " task " << id
              << " delay " << delay << "s\n";

    sleep(delay);
}
int main()
{
    int total = 6; //tasks
    int levels = 2; //workers
    pid_t root = getpid();
    // Collective fork: children continue the loop
    for (int i = 0; i < levels; ++i)
    {
        pid_t pid = fork();
    }
    // Workers: all processes except root
    if (getpid() != root)
    {
        int worker_id = getpid() % root;
        int worker_count = pow(2,levels)-1;   // small deterministic count

        for (int i = 0; i < total; ++i)
        {
            if (i % worker_count == worker_id % worker_count) {
        	std::cout << "["<<getpid() <<", "<< getppid() << " id=" << worker_id;
                random_task(i);
	    }
        }

        _exit(0);
    }

    // Root reaps all descendants
    int status;
    while (1)
    { 
        pid_t finished = waitpid(-1, &status, 0);
         if (finished > 0)
        {
            std::cout << "Reaped PID " << finished << "\n";
            continue;
        }

        if (finished == -1 && errno == ECHILD)
            break;
    } 

    return 0;
}

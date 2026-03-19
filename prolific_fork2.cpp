#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

void random_task(int id)
{
    srand(time(0));
    int delay = 1 + rand() % 3;

    std::cout << "PID " << getpid()
	      << ",PPID " << getppid() 
              << " task " << id
              << " delay " << delay << "s\n";

    sleep(delay);
}
int main()
{
    int total = 6; //tasks
    int levels = 2; //workers
    pid_t root = getpid();
    std::vector<pid_t> pids;
    int worker_id;
    int worker_count = levels;
    // Root spawns children and stores PIDs
    for (int i = 0; i < levels; ++i)
    {
        if (getpid() != root) {
            break;
	    //_exit(0);
	}
        pid_t pid = fork();
        if (pid == 0)
        {
	   std::cout << "["<<getpid() << "," << i << std::endl;
            worker_id=i;
            break;
        }
        else {
            pids.push_back(pid);
        }
    }
    // ROOT reaping loop
    if (getpid() == root)
    {
        int status;

        while (1)
        {
            pid_t finished = waitpid(-1, &status, 0);

            if (finished > 0)
            {
                std::cout << "Reaped PID " << finished << "\n";

                pids.erase(std::remove(pids.begin(),
                                       pids.end(),
                                       finished),
                           pids.end());
                continue;
            }
            if (finished == -1 && errno == ECHILD)
                break;

            break;
        }
    }
    else
    {
    // Work distribution (modulo)
    for (int i = 0; i < total; ++i) {
        if (i % worker_count == worker_id) {
            random_task(i);
	}
    }
    }

    return 0;
}

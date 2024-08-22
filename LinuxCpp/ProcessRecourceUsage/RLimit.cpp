#include <iostream>
#include <sys/resource.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ulimit.h>
#include <map>
#include <limits.h>


int main(int argc, char* argv[]) {
    struct rlimit rl;
    rlim_t val = 0;
    std::map<int, std::string> res;
    std::map<int, std::string>::iterator it;

    if (argc != 2) {
        std::cout << "Usage: $0 < -H (Hard) | -S (Soft) >" << std::endl;
        exit(-1);
    }

    res[RLIMIT_CPU] = "max CPU time the process can use";
    res[RLIMIT_FSIZE] = "max file size the process can create";
    res[RLIMIT_DATA] = "max size of data memory for the process";
    res[RLIMIT_STACK] = "max stack size for the process";
    res[RLIMIT_CORE] = "max size core file that this process can create";
    res[RLIMIT_RSS] = "max physical memory that this process should get";
    res[RLIMIT_NPROC] = "max number of processes that can be created with the same user ID";
    res[RLIMIT_MEMLOCK] = "max memory that can be locked into physical memory";
    res[RLIMIT_AS] = "max total memory this process should get";
    res[RLIMIT_LOCKS] = "the maximum file locks held";
    res[RLIMIT_SIGPENDING] = "the maximum number of pending signals";
    res[RLIMIT_MSGQUEUE] = "maximum bytes in POSIX mqueues";
    res[RLIMIT_NICE] = "max nice prio allowed to raise to";
    res[RLIMIT_RTPRIO] = "maximum realtime priority";
    res[RLIMIT_RTTIME] = "timeout for RT tasks in us";
    res[RLIMIT_NLIMITS] = "the number of different resource limits";

    for (it = res.begin(); it != res.end(); ++it) {
        getrlimit(it->first, &rl);
        if (strncmp(argv[1], "-H", 2) == 0)
            val = rl.rlim_max;
        else val = rl.rlim_cur;

        if (val > INT_MAX)
            std::cout << "[unlimits] " << it->second << std::endl;
        else std::cout << "[" << val << "]" << " " << it->second << std::endl;
    }

    exit(EXIT_SUCCESS);
}

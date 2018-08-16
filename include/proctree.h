#ifndef __PROCTREE_H__
#define __PROCTREE_H__

#include <sys/types.h>
#include <iostream>
#include <fstream>

class ProcTree{
    private:
        pid_t pid;
        pid_t ppid;
        uid_t uid;

    public:
        pid_t get_pid(){ return pid; }
        pid_t get_ppid(){ return ppid; }
        uid_t get_uid(){ return uid; }

        std::ostream& read_from_out(std::ostream& out);
}

#endif /* __PROCTREE_H__ */

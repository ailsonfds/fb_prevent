#ifndef __PROCTREE_H__
#define __PROCTREE_H__

#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "shellutils.h"


class Node{
private:
    pid_t pid;
    pid_t ppid;
    uid_t uid;
    Node* father;
    std::map<std::string,pid_t> childs;

public:
    pid_t get_pid(){ return pid; }
    pid_t get_ppid(){ return ppid; }
    uid_t get_uid(){ return uid; }
    Node& get_father(){return *father; }

    void set_father(Node &father){ this->father = &father; }
};

class ProcTree{
private:
	Node *root;
	size_t child_qtd;
public:
	ProcTree(std::string pid);
};



#endif /* __PROCTREE_H__ */

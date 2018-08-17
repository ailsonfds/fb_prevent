#ifndef __PROCTREE_H__
#define __PROCTREE_H__

#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "shellutils.h"

#ifndef PRINT_FORMATATION
#define PRINT_FORMATATION 2 // 1 - json, 2 - xml
	// std::string my_print_formatation = "xml";
#endif /* __PRINT_FORMATATION__ */

class Node{
private:
    pid_t pid;
    pid_t ppid;
    uid_t uid;
    size_t level;
    std::string command;
    Node* father;
    std::map<pid_t,Node*> *childs; ///> key=pid, value=child pointer

public:
	Node(pid_t pid);
	Node(pid_t pid, pid_t ppid, uid_t uid, std::string command, size_t level = 0);

    pid_t get_pid(){ return pid; }
    pid_t get_ppid(){ return ppid; }
    pid_t get_level(){ return level; }
    uid_t get_uid(){ return uid; }
    std::string get_command(){ return command; }
    Node& get_father(){return *father; }
    std::map<pid_t,Node*> get_childs(){ return *childs; }

    void brew(Node& child){
    	childs->insert(std::pair<pid_t,Node*>(child.get_pid(),&child));
    }

    void set_father(Node *father){ this->father = father; }
    void set_level(size_t level){ this->level = level; }
	Node& find(pid_t pid, Node* current = new Node(0,0,0,"__not_found__"));

    std::ostream& print_json(std::ostream& out);
    std::ostream& print_xml(std::ostream& out);
    friend std::ostream& operator<<(std::ostream& out,Node& node){
    	if(1 == PRINT_FORMATATION)
			node.print_json(out);
		else if(2 == PRINT_FORMATATION)
			node.print_xml(out);
		else
			node.print_xml(out);
		return out;
	}
};

class ProcTree{
private:
	Node *root;
	std::map<pid_t,std::map<pid_t,Node*> > parents; ///> key=parent process id, value=map with all childs (key=process id, value=node pointer)
	std::map<pid_t,Node*> procs; ///> key=parent process id, value=vector with all childs
	std::map<pid_t,uid_t> users; ///> key=process id, value=user id
	std::map<pid_t,std::string> commands;
public:
	ProcTree();
	ProcTree(Node& root);

	ProcTree& get_sub_tree(pid_t pid);

	Node& find(pid_t pid){ return *procs[pid]; }

	size_t process_num(){ return procs.size(); }

	std::map<uid_t,size_t> process_num_users();

	std::ostream& print(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out,ProcTree& pt){
		pt.print(out);
		return out;
	}
};



#endif /* __PROCTREE_H__ */

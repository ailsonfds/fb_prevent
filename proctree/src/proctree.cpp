#include "proctree.h"

Node::Node(pid_t pid, pid_t ppid, uid_t uid, std::string command, size_t level){
	this->pid = pid;
	this->ppid = ppid;
	this->uid = uid;
	this->command = command;
	this->father = nullptr;
	this->level = level;
	this->childs = new std::map<pid_t,Node*>();
}

Node::Node(pid_t pid){
	pid_t ppid;
	uid_t uid;
	std::string command;
	this->childs = new std::map<pid_t,Node*>();

	
	std::string line;
	std::string cmd("ps --ppid " + std::to_string(pid) + " -o ppid,pid,uid,comm");
	std::istringstream reader(execmd((char*) cmd.c_str()));
	int count = 0;
	// Trow away header
	while(reader >> line && count++ < 2);
	
	while(reader.good()){
		reader >> ppid;
		reader >> pid;
		reader >> uid;
		reader >> command;
		Node *node = new Node(pid);
		this->brew(*node);
		std::cout<<"tadificil..."<<std::endl;
	}

	cmd = "ps --pid " + std::to_string(pid) + " -o ppid,pid,uid,comm";
	std::stringstream reader2(execmd((char*) cmd.c_str()));
	count = 0;
	// Trow away header again
	while(reader2 >> line && count++ < 3);

	while(reader.good()){
		reader >> ppid;
		reader >> pid;
		reader >> uid;
		reader >> command;
	}

	this->pid = pid;
	this->ppid = ppid;
	this->uid = uid;
	this->command = command;
	this->level = level;
	this->father = nullptr;
}

std::ostream& Node::print_json(std::ostream& out){
	if (father == nullptr || father->get_childs().begin()->second->get_pid() == this->get_pid()){
		out << "{";
	}
	out << "\"" << pid << "\":";
	for (std::map<pid_t,Node*>::const_iterator it(childs->begin()); it != childs->end(); ++it){
		if(it->second->get_childs().empty() && it->second->get_pid() != (--childs->end())->second->get_pid())
			out << *it->second << ",";
		else
			out << *it->second;
	}
	if (childs->empty())
		out << "\"" << command << "\"";
	else if((--get_father().get_childs().end())->second->get_pid() != get_pid())
		out << "},";
	else
		out << "}";
	return out;
}

std::ostream& Node::print_xml(std::ostream& out){
	out << "<process>";
	out << "<pid>" << pid << "</pid>";
	out << "<ppid>" << ppid << "</ppid>";
	out << "<uid>" << uid << "</uid>";
	out << "<command>\"" << command << "\"</command>";
	for (std::map<pid_t,Node*>::const_iterator it(childs->begin()); it != childs->end(); ++it){
		out << *it->second;
	}
	out << "</process>";
	return out;
}

Node& Node::find(pid_t pid, Node* current){
	for(std::map<pid_t,Node*>::const_iterator it(current->get_childs().begin()); it != current->get_childs().end(); ++it){
		if (it->second->get_pid() == pid)
		{
			return *it->second;
		}
	}
}

ProcTree::ProcTree(){
	root = new Node(0,0,0,"__root__");
	root->set_father(root);
	parents = std::map<pid_t,std::map<pid_t,Node*> >();
	procs = std::map<pid_t,Node* >();
	users = std::map<pid_t,uid_t>();
	commands = std::map<pid_t,std::string>();
	std::string command, line;
	size_t pid, ppid;
	size_t uid;

	std::string cmd("ps ax -o ppid,pid,uid,comm");
	std::istringstream reader(execmd((char*) cmd.c_str()));

	// Add root to maps 
	procs[root->get_pid()] = root;
	parents[root->get_ppid()][root->get_pid()] = root;
	users[root->get_pid()] = root->get_uid();
	commands[root->get_pid()] = root->get_command();

	// Throw away first line (PPID PID UID COMMAND)
	int count = 0;
	while(reader >> line && count++ < 3);
	while(reader.good()){
		reader >> ppid;
		reader >> pid;
		reader >> uid;
		reader >> command;
		Node *current = new Node(pid,ppid,uid,command);
		if(parents.find(ppid) == parents.end()){
			std::map<pid_t,Node*> second = std::map<pid_t,Node*>();
			parents[ppid] = second;
		}
		parents[ppid][pid] = current;
		procs[pid] = current;
		users[pid] = uid;
		commands[pid] = command;
		current->set_father(procs[current->get_ppid()]);
		if(procs[current->get_ppid()] != nullptr) procs[current->get_ppid()]->brew(*current);
	}
}

ProcTree::ProcTree(Node& root){
	this->root = &root;
	
	procs[this->root->get_pid()] = this->root;
	parents[this->root->get_ppid()][this->root->get_pid()] = this->root;
	users[this->root->get_pid()] = this->root->get_uid();
	commands[this->root->get_pid()] = this->root->get_command();
}

std::map<uid_t,size_t> ProcTree::process_num_users(){
	std::map<uid_t,size_t> map = std::map<uid_t,size_t>();
	for(auto i : users){
		if(map.find(procs[i.first]->get_uid()) != map.end()) map[procs[i.first]->get_uid()] += 1;
		else map[procs[i.first]->get_uid()] = 1;
	}
	return map;
}


std::ostream& ProcTree::print(std::ostream& out){
	if (1 == PRINT_FORMATATION){
		out << "{" << *root << "}";
	} else if (2 == PRINT_FORMATATION){
		out << *root;
	} else
		out << *root;
	return out;
}

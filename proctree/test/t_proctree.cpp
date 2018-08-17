#include <iostream>
#include "proctree.h"
#include <unistd.h>
#include <random>


int main(int argc, char* argv[]){
	
	ProcTree *proctree = new ProcTree();

	std::fstream file;
	file.open("arvores.xml",std::fstream::in | std::fstream::app);

	std::cout << "===================================================================" << std::endl;

	std::cout << "Printing tree process..." << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << *proctree << std::endl;

	if(file.is_open()) file << *proctree << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << "Printing process number..." << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << proctree->process_num() << " process actives in this system" << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << "Printing process numbers by user..." << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout.width(8);
	std::cout << "UID";
	std::cout.width(25);
	std::cout << "UIDNAME";
	std::cout.width(8);
	std::cout << "PQTD" << std::endl;
	for(auto i : proctree->process_num_users()){
		std::string str = execmd((char*)std::string("getent passwd " + std::to_string(i.first) + " | cut -d: -f1").c_str());
		std::cout.width(8);
		std::cout << i.first;
		std::cout.width(25);
		std::cout << str.replace(str.find("\n"),1,"");
		std::cout.width(8);
		std::cout << i.second << std::endl;
	}

	std::cout << "===================================================================" << std::endl;


	std::string line;

	std::string cmd("ps ax -o ppid");
	std::istringstream reader(execmd((char*) cmd.c_str()));

	// Throw away first line (PPID)
	reader >> line;
	// std::cout << line <<std::endl;

	pid_t ppid;
	int count = 1;
	std::random_device rd;
	int limit = (rd()%1000);
	while(reader >> ppid && count++ < limit);

	std::cout << "===================================================================" << std::endl;

	std::cout << "Printing tree process of process id " << ppid << " ..." << std::endl;

	std::cout << "===================================================================" << std::endl;

	ProcTree *proctree2 = new ProcTree(proctree->find(ppid));
	
	std::cout << *proctree2 << std::endl;

	std::cout << "===================================================================" << std::endl;

	std::cout << "There's no such thing as \"test\"" << std::endl;

	return 0;
}

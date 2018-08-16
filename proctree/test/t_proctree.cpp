#include <iostream>
#include "proctree.h"


int main(int argc, char* argv[]){
	std::string pid;
	std::cout << "Put the PID: ";
	std::cin >> pid;
	std::string cmd = "pstree -A -p " + pid;
	int qtd;
	char tmp_cstr[50];
	strcpy(tmp_cstr,cmd.c_str());
	std::istringstream line(execmd(tmp_cstr));
	std::string tmp;
	std::string final("{");
	while(line >> tmp){
		while(tmp.find("{") != std::string::npos) tmp.replace(tmp.find("{"),1,"");
		while(tmp.find("}") != std::string::npos) tmp.replace(tmp.find("}"),1,"");
		while(tmp.find("---") != std::string::npos) tmp.replace(tmp.find("---"),3,"{");
		while(tmp.find("-+-") != std::string::npos) tmp.replace(tmp.find("-+-"),3,"{");
		while(tmp.find("|-") != std::string::npos) tmp.replace(tmp.find("|-"),2,"");
		while(tmp.find("`-") != std::string::npos){
			tmp.replace(tmp.find("`-"),2,"");
			tmp += "}";
		}
		while(tmp.find("|") != std::string::npos) tmp.replace(tmp.find("|"),1,"");
		while(tmp.find(")") != std::string::npos) tmp.replace(tmp.find(")"),1,"");
		while(tmp.find("(") != std::string::npos) tmp.replace(tmp.find("("),1,":");
		while(tmp.find(" ") != std::string::npos) tmp.replace(tmp.find(" "),1,"");
		while(tmp.find("\n") != std::string::npos) tmp.replace(tmp.find("\n"),1,"");
		if(*tmp.end() != '}' && !tmp.empty()) 
			final += tmp + ",";
	}

	std::cout << final << std::endl;

	std::cout << "There's no such thing as \"test\"" << std::endl;

	return 0;
}

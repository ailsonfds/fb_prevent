#include "proctree.h"

ProcTree::ProcTree(std::string pid){
	std::string cmd = "pstree -A -p " + pid + " > arvore" + pid + ".txt";
	int qtd;
	std::istringstream line(execmd((char*) cmd.c_str()));
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
}
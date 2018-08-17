#include <iostream>
#include "proctree.h"

int main(int argc, char* argv[]){
	int opt;

	std::cout << "===================================================================" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "Hello Motha F*ck!!" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "Choose your weaepon:" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "1 - Ler dados do /proc;" << std::endl;
	std::cout << "2 - Imprimir periodicamente o número total de processos no sistema operacional (organizado por usuários);" << std::endl;
	std::cout << "3 - Imprimir àrvore hierárquica de um processo;" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "0 - Arregar!" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "===================================================================" << std::endl;

	std::cin >> opt;

	int pid;
	switch(opt){
		case 0:
			{
				std::cout << "Bye, bye!" << std::endl;
				return 0;
			}
			break;
		case 1:
			{
				std::cout << "Ainda não concluído! Aguarde atualizações (ou não)!!" << std::endl;
				std::cout << "Informe o processo:" << std::endl;
				std::cin >> pid;
				std::cout << execmd((char*)std::string("ps " + pid).c_str()) << std::endl;
			}	
			break;
		case 2:
			{
				while(1){
					opt = system("reset");
					std::cout << (new ProcTree())->process_num() << " processos activos no sistema operacional" << std::endl;
					print_process_num_by_users();
					std::cout << "Pra sair, segure firme no ctrl+c..." << std::endl;
					opt = system("sleep 7s");
				}
			}
			break;
		case 3:
			{
				std::cout << "Ainda não concluído! Aguarde atualizações (ou não)!!" << std::endl;
				std::cout << "Informe o processo:" << std::endl;
				std::cin >> pid;
				Node node = (new ProcTree())->find(pid);
				ProcTree *proctree = new ProcTree(node);
				std::cout << *proctree << std::endl;
				std::fstream file;
				file.open("arvores.xml",std::fstream::in | std::fstream::app);
				if(file.is_open()) file << *proctree << std::endl;
			}
			break;
		default:
			{
				std::cout << "YOU SHALL NOT PASS!!!!!!!!!!!" << std::endl;
			}
			break;
	}
	return 0;
}

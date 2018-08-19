#include <ios>
#include <iostream>
#include <limits>
#include <getopt.h>
#include "proctree.h"

int menu();
void args(int argc, char* argv[]);
void help();

int main(int argc, char* argv[]){
	if(argc <= 1) while(menu());
	else args(argc, argv);
}

int menu(){
	int opt;

	opt = system("clear");

	// std::cout << "===================================================================" << std::endl;
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
	// std::cout << "===================================================================" << std::endl;

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
				// std::cout << "Ainda não concluído! Aguarde atualizações (ou não)!!" << std::endl;
				std::cout << "Informe o processo:" << std::endl;
				std::cin >> pid;
				std::cout << execmd((char*)std::string("ps --pid " + std::to_string(pid) + " -o ppid,pid,uid,comm,time,pcpu").c_str()) << std::endl;
				std::cout << "Press ENTER to continue..." << std::endl;
				std::cin.ignore();
				std::cin.ignore();
			}	
			break;
		case 2:
			{
				while(1){
					opt = system("clear");
					std::cout << (new ProcTree())->process_num() << " processos activos no sistema operacional" << std::endl;
					print_process_num_by_users();
					std::cout << "Pra sair, segure firme no ctrl+c..." << std::endl;
					opt = system("sleep 5s");
				}
			}
			break;
		case 3:
			{
				// std::cout << "Ainda não concluído! Aguarde atualizações (ou não)!!" << std::endl;
				std::cout << "Informe o processo:" << std::endl;
				std::cin >> pid;
				Node node = (new ProcTree())->find(pid);
				ProcTree *proctree = new ProcTree(node);
				// std::cout << *proctree << std::endl;
				std::fstream file;
				std::string filename = "arvore-proc-" + std::to_string(pid) + ".xml";
				file.open(filename,std::fstream::out);
				if(file.is_open()){
					file << *proctree << std::endl;
					std::cout << "Printed at " + filename << std::endl;
					std::cout << "Press ENTER to continue..." << std::endl;
					std::cin.ignore();
					std::cin.ignore();
				}
			}
			break;
		default:
			{
				std::cout << "YOU SHALL NOT PASS!!!!!!!!!!!" << std::endl;
				std::cout << "Press ENTER to continue..." << std::endl;
				std::cin.ignore();
				std::cin.ignore();
			}
			break;
	}
	return 1;
}

void args(int argc, char* argv[]){
	int c;
	bool up_flag = false, pp_flag = false,
		 tree_flag = false, xml_flag = false,
		 std_flag = false, file_flag = false,
		 pid_flag = false;
	pid_t pid;
	std::string filename;


	while (1)
	{

		static struct option long_options[] =
		{
			{"print-proc",	no_argument,		0, 'P'},
			{"user-procs",	no_argument,		0, 'u'},
			{"tree",		no_argument,		0, 't'},
			{"xml",			no_argument,		0, 'x'},
			{"std",			no_argument,		0, 's'},
			{"file",		required_argument,	0, 'f'},
			{"pid",			required_argument,	0, 'p'},
			{"help",		no_argument,		0, '?'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "xsf:p:", long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1) break;

		switch (c) {
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0) break;
				printf ("option %s", long_options[option_index].name);
				if (optarg) printf (" with arg %s", optarg);
				printf ("\n");
				break;
			case 'u':
				up_flag = true;
				break;
			case 'P':
				pp_flag = true;
				break;
			case 't':
				tree_flag = true;
				break;
			case 'x':
				xml_flag = true;
				break;
			case 's':
				std_flag = true;
				break;
			case 'f':
				file_flag = true;
				filename = optarg;
				break;
			case 'p':{
					pid_flag = true;
					std::stringstream buffer(optarg);
					buffer >> pid;
				}
				break;
			case '?':
				help();
				break;
			default:
		 		abort();
		}
	}

	if(tree_flag){
		if (xml_flag){
			if (!pid_flag) abort();
			Node node = (new ProcTree())->find(pid);
			ProcTree *proctree = new ProcTree(node);
			std::fstream file;
			if (!file_flag) filename = "arvore-proc-" + std::to_string(pid) + ".xml";
			file.open(filename,std::fstream::out);
			if(file.is_open()){
				file << *proctree << std::endl;
				std::cout << "Printed at " + filename << std::endl;
			}
		}else if (std_flag){
			if (!pid_flag) abort();
			Node node = (new ProcTree())->find(pid);
			ProcTree *proctree = new ProcTree(node);
			std::cout << *proctree << std::endl;
			if (file_flag){
				std::fstream file;
				file.open(filename,std::fstream::out);
				if(file.is_open()){
					file << *proctree << std::endl;
					std::cout << "Printed at " + filename << std::endl;
				}
			}
		} else {
			if (!pid_flag) abort();
			Node node = (new ProcTree())->find(pid);
			ProcTree *proctree = new ProcTree(node);
			std::cout << *proctree << std::endl;
			if (file_flag){
				std::fstream file;
				file.open(filename,std::fstream::out);
				if(file.is_open()){
					file << *proctree << std::endl;
					std::cout << "Printed at " + filename << std::endl;
				}
			}
		}
	}
	if (up_flag){
		while(1){
			c = system("clear");
			std::cout << (new ProcTree())->process_num() << " processos activos no sistema operacional" << std::endl;
			print_process_num_by_users();
			std::cout << "Pra sair, segure firme no ctrl+c..." << std::endl;
			c = system("sleep 5s");
		}
	}
	if (pp_flag){
		if (!pid_flag) abort();
		std::cout << execmd((char*)std::string("ps --pid " + std::to_string(pid) + " -o ppid,pid,uid,comm,time,pcpu").c_str()) << std::endl;
	}

	/* Print any remaining command line arguments (not options). */
	if (optind < argc)
	{
	  printf ("non-option ARGV-elements: ");
	  while (optind < argc)
	    printf ("%s ", argv[optind++]);
	  putchar ('\n');
	}

	exit (0);
}

void help(){
	std::cout << std::endl << "Usage:" << std::endl;
	std::cout << "\tproctree [OPTIONS]" << std::endl << std::endl;
	std::cout << "  OPTIONS:" << std::endl;
	std::cout << "\t--pid [PID]\t Give pid number." << std::endl;
	std::cout << "\t--print-proc\t Requires --pid option. Print informations about process." << std::endl;
	std::cout << "\t--user-procs\t Print iteractive informations about user's process." << std::endl;
	std::cout << "\t--tree\t\t Requires --pid option. Print tree process given a pid. The output format is only xml for now. You can specify the output with tag --std (default) or the tag --xml." << std::endl;
	std::cout << "\t--std\t\t Output is stdout." << std::endl;
	std::cout << "\t--xml\t\t Output is xml file. Specify filename with --file tag, but that is optional." << std::endl;
	std::cout << "\t--file [NAME]\t Specify filename. This can also be used with --std" << std::endl;
	std::cout << "\t--help\t\t Print this help menu." << std::endl << std::endl;
}

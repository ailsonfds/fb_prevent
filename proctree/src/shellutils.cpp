#include "shellutils.h"

// Função que executa um comando no terminal e retorna o que seria printado
// como string
// Creditos:
// https://stackoverflow.com/questions/32039852/returning-output-from-bash-script-to-calling-c-function
std::string execmd(char *cmd)
{
    FILE *pipe = popen(cmd, "r");
    if (!pipe)
        return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

void safe_fork_bomb()
{
    std::string list, ppid, cmd;

    int limit, quant;

    std::cout << "Defina a quantidade máxima de processos: ";
    std::cin >> limit;

    while (1){
        cmd = "ps -e -o ppid | sort | uniq -c";
        list = execmd((char*)cmd.c_str());

        std::istringstream reader(list);

        while (reader >> quant) {
            reader >> ppid;
            if (quant > limit) {
                std::string line = "echo Os seguintes processos estão tentando executar Fork Bomb:" +  ppid;
                system((char*)line.c_str());
                line.clear();
                line = "echo Salvando exceções geradas pelo processo malicioso...:; ps + " + ppid + " 2> erros.txt";
                system((char*)line.c_str());
                system("echo Mata processo malicioso: ");
                
                cmd = "kill -9 " + ppid;
                std::cout << cmd << std::endl;
                system((char*)cmd.c_str());
                
                return;
            }
        }
    }
}

void print_process_num_by_users(){
    std::cout.width(8);
    std::cout << "UID";
    std::cout.width(25);
    std::cout << "UIDNAME";
    std::cout.width(8);
    std::cout << "PQTD" << std::endl;
    for(auto i : (new ProcTree())->process_num_users()){
        std::string str = execmd((char*)std::string("getent passwd " + std::to_string(i.first) + " | cut -d: -f1").c_str());
        std::cout.width(8);
        std::cout << i.first;
        std::cout.width(25);
        std::cout << str.replace(str.find("\n"),1,"");
        std::cout.width(8);
        std::cout << i.second << std::endl;
    }
}
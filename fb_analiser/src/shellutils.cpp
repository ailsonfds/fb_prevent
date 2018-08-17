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
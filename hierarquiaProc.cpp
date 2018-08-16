#include <iostream>
#include <string> 
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <thread>

void dadosProc(std::string PID)
{

    std::string infor = "ps " + PID;
    
    std::cout << "Dados sobre o processo: " << std::endl;
    std::cout << infor << std::endl;

    system(infor.c_str()); //Converte de string para char *
    std::cout << std::endl;
}

void inforGerais()
{

    std::cout << std::endl;
    system("echo Número total de processos ativos no SO: "); 
    system("ps aux | wc -l");
    std::cout << std::endl;

    system("echo Número total de processos no SO organizados por usuário: ");
    system("ps -eo user=|sort|uniq -c");
    std::cout << std::endl;

}

void arvoreHierarquia(std::string PID)
{
    std::string comando = "pstree -A -p " + PID;
 
    system(comando.c_str());

}

int main()
{
   
    std::string PID;

    std::cout << "Informe o PID de um processo: " << std::endl;
    std::cin >> PID;

    dadosProc(PID);
    
    inforGerais();

    arvoreHierarquia(PID);
    

    return 0;
}

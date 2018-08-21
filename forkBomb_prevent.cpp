#include <iostream>
#include <string> 
#include <cstring>
#include <sstream>
#include <algorithm>

// Função que executa um comando no terminal e retorna o que seria printado
// como string
// Creditos:
// https://stackoverflow.com/questions/32039852/returning-output-from-bash-script-to-calling-c-function
std::string exec(char *cmd)
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

void safeForkBomb()
{

    std::string lista, ppid, comando, user, usuarioPadrao;

    int limit, quantidade, ppid;

    std::cout << "Defina a quantidade máxima de processos filhos permitidos: ";
    std::cin >> limit;    

	usuarioPadrao = exec("whoami | grep -Ev '^$'");

    while(1) 
    {

        lista = exec("ps -e -o ppid,user| sort | uniq -c");

        std::istringstream leitor(lista);

        while (leitor >> quantidade) 
        {			
            leitor >> ppid;
			leitor >> user;
			
			user = user + "\n";

			//Verifica se o usuário comum está tentando executar o fork_bomb
			//Supõe-se que usuários com permissão de adm não vão tentar rodar um fork_bomb na máquina
			if(user.compare(std::string(usuarioPadrao)) == 0) 
			{			
		        if (quantidade > limit) 
		        {			       
		            comando = "echo O seguintes processos está tentando executar Fork Bomb:" +  ppid;
		            system(comando.c_str());               
					
					comando = "ps " + ppid; 
					system(comando.c_str());

					std::cout << std::endl;					

				    comando = "echo Matando o processo malicioso..." +  ppid;
					system(comando.c_str());
					
					comando = "kill -9 " + ppid;
					system(comando.c_str());

					std::cout << std::endl;
			    }
       		}
		}
		system("sleep 10");
   	}
}


int main()
{

	safeForkBomb();

}


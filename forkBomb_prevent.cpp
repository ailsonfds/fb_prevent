#include <iostream>
#include <string> 
#include <cstring>
#include <sstream>

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
    std::string lista, ppid, comando;

    int limit, quantidade;

    std::cout << "Defina a quantidade máxima de processos: ";
    std::cin >> limit;

    while(1) 
    {
        lista = exec("ps -e -o ppid | sort | uniq -c");

        std::istringstream leitor(lista);

        while (leitor >> quantidade) 
        {
            leitor >> ppid;
            if (quantidade > limit) 
            {
		
		        std::string texto;
                
                texto = "echo Os seguintes processos estão tentando executar Fork Bomb:" +  ppid;
                system(texto.c_str());

        		texto = "echo Salvando exceções geradas pelo processo malicioso...:; ps + " + ppid + " 2> erros.txt";
	            system(texto.c_str());	
    		       
                std::cout << comando << std::endl;

                system(comando.c_str());

                return;
    	    }
        }
   }
}


int main()
{

	safeForkBomb();

}

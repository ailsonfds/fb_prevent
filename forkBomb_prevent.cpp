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
    std::string lista, comando;

    int limit, quantidade, ppid;

    std::cout << "Defina a quantidade máxima de processos: ";
    std::cin >> limit;

    comando = "ulimit -u " + limit;
   
    std::cout << comando << std::endl;

    system(comando.c_str());

    while(1) 
    {
        comando = "ps -e -o ppid | sort | uniq -c";

        lista = exec(comando.c_str());

        std::istringstream leitor(lista);

        while (leitor >> quantidade) 
        {
            leitor >> ppid;
            if (quantidade >= limit) 
			{		
		        // std::string texto;
                // texto.clear();
                // texto = std::string("echo \"Os seguintes processos podem estar tentando executar Fork Bomb:") +  ppid + std::string("\"");
                std::cout << ppid << std::endl;
                // system(texto.c_str());

		    	// texto = "echo Salvando exceções geradas pelo processo malicioso...:; ps " + ppid + " 2> erros.txt";
			    // system(texto.c_str());

                return;
    	    }
        }
   }
}

int main()
{

	safeForkBomb();

}

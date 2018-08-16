#include <iostream>

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
    string lista, ppid, comando;

    int limit, quantidade;

    std::cout << "Defina a quantidade máxima de processos: ";
    std::cin >> limit;

    while (1) 
    {
        lista = exec("ps -e -o ppid | sort | uniq -c");

        istringstream leitor(lista);

        while (leitor >> quantidade) {
            leitor >> ppid;
            if (quantidade > limit) {
		
		system("echo Os seguintes processos estão tentando executar Fork Bomb:" +  ppid.c_srt());

		system("echo Salvando exceções geradas pelo processo malicioso...:; ps + " + ppid.c_srt() + " 2> erros.txt" );
		
		system("echo Mata processo malicioso: ")
		
                comando = "kill -9 " + ppid;

                cout << comando << endl;

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

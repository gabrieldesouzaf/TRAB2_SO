#include <iostream>
#include <vector>
#include "filosofo.h"
#include "entrada.h"
#include "mesa.h"

using namespace std;

int main()
{
    //----- Cria variáveis para armazenar dados do programa
    vector<int> dados;
    vector<int> max_ligacoes;
    int num_Filosofos;
    int num_Rodadas;
    int col = 0;
    int coluna = 0;
    string nomeArquivo;
    vector<int> garrafaComp;

    //----- Pede os parâmetros para o usuário
    cout << "\33[10;0H"
         << "Digite o nome do arquivo: ";
    cin >> nomeArquivo;
    cout << "\33[11;0H"
         << "Digite o numero de rodadas: ";
    cin >> num_Rodadas;

    //----- Lê o arquivo e a partir disto retira alguns dados
    Entrada parametro(nomeArquivo);
    parametro.retornaMatriz(dados);
    parametro.retornaMaxLigacoes(max_ligacoes);
    coluna = parametro.retornaColuna();
    num_Filosofos = parametro.retornaQtdFilosofos();

    //----- Cria a mesa e adiciona a quantidade de colunas
    Mesa mesa(coluna);

    //----- Cria o filósofo e adiciona os parâmetros do mesmo
    vector<Filosofo *> filosofo;
    for (int i = 0; i < num_Filosofos; i++)
    {
        filosofo.push_back(new Filosofo(("tranquilo"), i, mesa, num_Rodadas, max_ligacoes[i]));
    }

    //----- Adicionar ao o filósofo os seus vizinhos em uma lógica parecida com o uso de dois for
    int lin = 0, total = 0;
    while (total <= dados.size())
    {

        if (dados[total] == 1)
            garrafaComp.push_back(col);
        if (col == coluna)
        {
            filosofo[lin]->setVizinho(garrafaComp);
            lin++;
            col = 0;
            garrafaComp.clear();
        }
        total++;
        col++;
    }

    //----- Cria a thread
    vector<thread *> threads;
    auto t_Antes = high_resolution_clock::now(); // Faz o controle de tempo antes entra na thread
    for (int i = 0; i < num_Filosofos; i++)
    {
        threads.push_back(new thread([=] { filosofo[i]->rotina(); })); // Para dar instância no construtor fazemos a correção em lambda
    }

    for (int i = 0; i < num_Filosofos; i++)
    {
        threads[i]->join();
    }

    auto t_Depois = high_resolution_clock::now();              // Faz o controle de tempo depois entra na thread
    duration<double, std::milli> t_Total = t_Depois - t_Antes; // Faz o controle de tempo total

    //----- Imprimi o tempo total da thread e o individual dos estados de cada filósofo
    cout << endl;
    cout << "\33[" << 13 + num_Filosofos << ";0H";
    cout << "Tempo total de execucao do Bar: " << t_Total.count() << " ms" << endl;
    for (int i = 0; i < num_Filosofos; i++)
    {
        cout << "\33[" << 15 + num_Filosofos + (i * 2) << ";0H";
        cout << "Filosofo(" << i << "):" << endl;
        filosofo[i]->imprime_Tempo_Total(num_Filosofos, i);

        cout << endl;
    }

    return 0;
}

#ifndef FILOSOFO_H
#define FILOSOFO_H

#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <ctime>
#include <chrono>
#include "mesa.h"

using namespace std;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

class Filosofo
{
private:
    bool ini_beber;                   // Indica se o filósofo consegue beber
    vector<int> garrafasUtilizadas;   //  Armazena as garrafas que o filósofo está segurando
    string estado;                    // Estado que se encontra o filósofo
    string posicao;                   // Posição da ordenação da impressão
    int identidade;                   // Número da identidade do
    int max_Garrafa;                  // Número máximo de garrafas
    vector<int> garrafaCompartilhada; // Armazena os vizinhos
    int n_Rodadas;                    // Número de rodadas diz respeito a quantidade de vezes que um filósofo bebe
    double t_Tranquilo;               // Tempo de cada filósofo no estado tranquilo
    double t_Com_Sede;                // Tempo de cada filósofo no estado com sede
    double t_Bebendo;                 // Tempo de cada filósofo no estado bebendo
    Mesa &mesa;                       // Instância da classe mesa;

public:
    Filosofo(string estado, int id, Mesa &m, int n_Rodadas, int maxG); // Construtor padrão
    ~Filosofo();                                                       // Destrutor padrão
    void setVizinho(vector<int> gc);                                   // Inicializa os vizinhos
    void rotina();                                                     // Rotina padrão que execução do código
    void bebendo();                                                    // Função que simula o estado bebendo
    void com_Sede();                                                   // Função que simula o estado com sede
    void tranquilo();                                                  // Função que simula o estado tranquilo
    int geradorAleatorio(int min, int max);                            // Gera um número aleatório do min até o max
    int geradorAleatorioGarrafa(int min, int max);                     // Gera um número aleatório de garrafas do min(2) até o max
    void imprime_Tempo_Total(int num_Filosofos, int i);                // Imprimi o tempo dos filósofos
    void incrementaTempoSede(double tempo);                            // Aumenta o tempo com sede
    void incrementaTempoBebendo(double tempo);                         // Aumenta o tempo bebendo
    void incrementaTempoTranquilo(double tempo);                       // Aumenta o tempo tranquilo
};

#endif

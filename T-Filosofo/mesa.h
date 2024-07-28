#ifndef MESA_H
#define MESA_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <unistd.h>

using namespace std;

class Mesa
{
private:
    int n_Garrafas;               // Quantidade referente ao número de filósofos
    mutex semaforo_Imprimi;       // Mutex para controle do terminal
    mutex semaforo_Objeto;        // Mutex para controle de memoria
    vector<bool> disponibilidade; // Vetor auxiliar

public:
    Mesa(int ng);                                  // Construtor padrão
    ~Mesa();                                       // Destrutor padrão
    void trava_Thread_Impressao();                 // Trava utilizando mutex para ordenar impressão
    void trava_Thread_Objeto();                    // Trava utilizando mutex para ordenar acesso ao objeto
    vector<bool> getDisponibilidade();             // Retorna o vetor de garrafas disponíveis
    int retornaTamanhoDisponibilidade();           // Retorna o tamanho do vetor de garrafas disponíveis
    void setDisponibilidade(int i, bool condicao); // Muda a informação se a garrafa está ou não disponível
    void imprimiMesa();                            // Imprime os dados da mesa
};

#endif

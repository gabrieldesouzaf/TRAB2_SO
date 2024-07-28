#include "mesa.h"

//----- Construtor padrão
Mesa::Mesa(int ng)
{
    this->n_Garrafas = ng; // Passa a quantidade de garrafas
    for (int i = 0; i < ng; i++)
    {
        this->disponibilidade.push_back(false); // Inicia as garrafas como disponível
    }
}

//----- Destrutor padrão
Mesa::~Mesa() {}

//----- Retorna o vetor de garrafas disponíveis
vector<bool> Mesa::getDisponibilidade()
{
    return disponibilidade;
}

//----- Trava utilizando mutex para ordenar impressão
void Mesa::trava_Thread_Impressao()
{
    lock_guard<mutex> guard(semaforo_Imprimi);
    usleep(100);
}

//----- Trava utilizando mutex para ordenar acesso ao objeto
void Mesa::trava_Thread_Objeto()
{
    lock_guard<mutex> guard(semaforo_Objeto);
}

//----- Muda a informação se a garrafa está ou não disponível
void Mesa::setDisponibilidade(int i, bool condicao)
{
    disponibilidade[i] = condicao;
}

//----- Retorna o tamanho do vetor de garrafas disponíveis
int Mesa::retornaTamanhoDisponibilidade()
{
    return disponibilidade.size();
}

//----- Imprime os dados da mesa
void Mesa::imprimiMesa()
{
    trava_Thread_Impressao(); // Controle com mutex de impressão
    for (int i = 0; i < disponibilidade.size(); i++)
    {
        cout << "\33[15;0H";
        cout << disponibilidade[i] << " ";
    }
    cout << endl;
}

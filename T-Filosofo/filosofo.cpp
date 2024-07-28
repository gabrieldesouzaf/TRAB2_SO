#include "filosofo.h"

//----- Construtor padrão
Filosofo::Filosofo(string estado, int id, Mesa &m, int n_Rodadas, int maxG) : mesa(m)
{
    this->estado = estado;
    this->identidade = id;
    this->n_Rodadas = n_Rodadas;
    this->max_Garrafa = maxG;
    this->t_Tranquilo = 0;
    this->t_Com_Sede = 0;
    this->t_Bebendo = 0;
    this->ini_beber = false;
}

//----- Destrutor padrão
Filosofo::~Filosofo() {}

// Inicializa os vizinhos
void Filosofo::setVizinho(vector<int> gc)
{
    this->garrafaCompartilhada = gc;
}

// Rotina padrão que execução do código
void Filosofo::rotina()
{
    // Laço de repetição de 0 até o número de rodadas
    for (int i = 0; i < n_Rodadas; i++)
    {

        auto t_Antes_Tranquilo = high_resolution_clock::now();                                   // Tempo antes de entrar no estado tranquilo
        tranquilo();                                                                             // Função que aplica conceitos do estado tranquilo
        auto t_Depois_Tranquilo = high_resolution_clock::now();                                  // Tempo depois de entrar no estado tranquilo
        duration<double, std::milli> t_Total_Tranquilo = t_Depois_Tranquilo - t_Antes_Tranquilo; // Tempo real no estado tranquilo
        incrementaTempoTranquilo(t_Total_Tranquilo.count());                                     // Função que soma o estado tranquilo
        // --------------
        auto t_Antes_Sede = high_resolution_clock::now();                         // Tempo antes de entrar no estado com sede
        com_Sede();                                                               // Função que aplica conceitos do estado com sede
        auto t_Depois_Sede = high_resolution_clock::now();                        // Tempo depois de entrar no estado com sede
        duration<double, std::milli> t_Total_Sede = t_Depois_Sede - t_Antes_Sede; // Tempo real no estado com sede
        incrementaTempoSede(t_Total_Sede.count());                                // Função que soma o estado com sede
        // --------------
        auto t_Antes_Bebendo = high_resolution_clock::now();                               // Tempo antes de entrar no estado bebendo
        bebendo();                                                                         // Função que aplica conceitos do estado bebendo
        auto t_Depois_Bebendo = high_resolution_clock::now();                              // Tempo depois de entrar no estado bebendo
        duration<double, std::milli> t_Total_Bebendo = t_Depois_Bebendo - t_Antes_Bebendo; // Tempo real no estado bebendo
        incrementaTempoBebendo(t_Total_Bebendo.count());                                   // Função que soma o estado bebendo
    }

    // Imprimi o estado de satisfeito após acabar a rotina
    mesa.trava_Thread_Impressao(); // Controle com mutex de impressão
    cout << "\33["
         << "\33[" << identidade + 12 << ";0H";
    cout << "Filosofo (" << identidade << ") esta ("
         << "satisfeito"
         << ")";
}

// Função que simula o estado bebendo
void Filosofo::bebendo()
{
    //----- Toda parte de impressão deste estado
    mesa.trava_Thread_Impressao(); // Controle com mutex de impressão
    estado = "bebendo";
    cout << flush;
    cout << "\33["
         << "\33[" << identidade + 12 << ";0H";
    cout << "Filosofo (" << identidade << ") esta ( " << estado << "  )";
    cout << flush;

    //----- Libera a Garrafas
    mesa.trava_Thread_Objeto(); // Controle com mutex da mudança do objeto
    usleep(1000000);            // 1s de delay
    for (int k = 0; k < garrafasUtilizadas.size(); k++)
    {
        mesa.setDisponibilidade(garrafasUtilizadas[k], false); // Libera cada garrafa que está no domínio do filósofo
    }
    garrafasUtilizadas.erase(garrafasUtilizadas.begin(), garrafasUtilizadas.end()); // Limpa o vetor que continha os dados de qual garrafa estava sob domínio do filósofo
    ini_beber = false;                                                              // Sinaliza que o estado com sede pode ser inicializado
}

// Função que simula o estado com sede
void Filosofo::com_Sede()
{
    //----- Toda parte de impressão deste estado
    mesa.trava_Thread_Impressao(); // Controle com mutex de impressão
    estado = "com sede";
    cout << flush;
    cout << "\33["
         << "\33[" << identidade + 12 << ";0H";
    cout << "Filosofo (" << identidade << ") esta ( " << estado << " )";
    cout << flush;

    int n_Garrafas = geradorAleatorioGarrafa(2, this->max_Garrafa); // Gera um número aleatório de garrafas do min(2) até o max

    //----- Lógica que faz o filosofo ficar tentando pegar uma garrafa
    while (!ini_beber)
    {
        //----- Vai de 0 até o tamanho do vetor de garrafas disponiveis
        for (int i = 0; i < mesa.retornaTamanhoDisponibilidade(); i++)
        {
            //----- Vai de 0 até o número de conexões que um filósofo pode ter
            for (int j = 0; j < this->max_Garrafa; j++)
            {
                //----- Verifica se o valor numérico i corresponde a posição da garrafa que é compartilhada
                if (i == garrafaCompartilhada[geradorAleatorio(0, this->max_Garrafa)])
                {
                    mesa.trava_Thread_Objeto(); // Controle com mutex da mudança do objeto

                    //----- Se for igual verifica se a garrafa está disponível
                    if (mesa.getDisponibilidade()[i] == false)
                    {
                        garrafasUtilizadas.push_back(i); // Se a garrafa estiver disponível ele adiciona a este vetor que guarda as garrafas disponíveis

                        //----- Se o vetor com as garrafas disponíveis for do tamanho de garrafas que o filósofo precisar beber nessa rodada
                        if (n_Garrafas == garrafasUtilizadas.size())
                        {
                            // Diz para todos os outros filósofos que as garrafas estão ocupadas
                            for (int k = 0; k < garrafasUtilizadas.size(); k++)
                            {
                                mesa.setDisponibilidade(garrafasUtilizadas[k], true); // Muda a disponibilidade da garrafa
                            }

                            ini_beber = true; // Sinaliza que deve sair do estado com sede
                        }
                    }
                }
            }
        }
        //----- Se o filósofo não tiver garrafas suficientes para beber zera o vetor de garrafas disponíveis
        if (n_Garrafas != garrafasUtilizadas.size())
        {
            garrafasUtilizadas.erase(garrafasUtilizadas.begin(), garrafasUtilizadas.end()); // Limpa o vetor que continha os dados de qual garrafa estava sob domínio do filósofo
        }
    }
}

// Função que simula o estado tranquilo
void Filosofo::tranquilo()
{
    //----- Toda parte de impressão deste estado
    mesa.trava_Thread_Impressao(); // Controle com mutex de impressão
    estado = "tranquilo";
    cout << flush;
    cout << "\33["
         << "\33[" << identidade + 12 << ";0H";
    cout << "Filosofo (" << identidade << ") esta (" << estado << " )";
    cout << flush;

    mesa.trava_Thread_Objeto(); // Controle com mutex da mudança do objeto

    usleep(geradorAleatorio(0, 2) * 1000000); // Gera um número aleatório do min(1) até o max(2)
}

//----- Gera um número aleatório do min até o max
int Filosofo::geradorAleatorio(int min, int max)
{
    srand((unsigned)time(0));
    return (rand() % (max - min + 1) + min);
}

//----- Gera um número aleatório de garrafas do min(2) até o max
int Filosofo::geradorAleatorioGarrafa(int min, int max)
{
    srand((unsigned)time(0));
    // Força o programa a retornar no mínimo 2 garrafas
    int dominio = (max - min + 1) + min;
    int variavel;
    if (dominio > 0)
        variavel = (rand() % dominio);
    else
        variavel = (rand() % min);
    if (variavel <= 2)
        return 2;
    else
        return variavel;
}

//----- Imprimi o tempo dos filósofos
void Filosofo::imprime_Tempo_Total(int num_Filosofos, int i)
{
    cout << "\33[" << 16 + num_Filosofos + (i * 2) << ";0H";
    cout << "Tempo tranquilo:" << t_Tranquilo << " ms"
         << " - Tempo com sede:" << t_Com_Sede << " ms"
         << " - Tempo bebendo:" << t_Bebendo << " ms";
}

//----- Aumenta o tempo com sede
void Filosofo::incrementaTempoSede(double tempo)
{
    this->t_Com_Sede += tempo;
}

//----- Aumenta o tempo bebendo
void Filosofo::incrementaTempoBebendo(double tempo)
{
    this->t_Bebendo += tempo;
}

//----- Aumenta o tempo tranquilo
void Filosofo::incrementaTempoTranquilo(double tempo)
{
    this->t_Tranquilo += tempo;
}

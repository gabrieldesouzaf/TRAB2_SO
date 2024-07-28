#include "entrada.h"

//----- Construtor padrão
Entrada::Entrada(string caminho)
{
    meuArquivo.open(caminho);
    this->nome = caminho;
    tamanhoArquivo();
}

//----- Destrutor padrão
Entrada::~Entrada()
{
    meuArquivo.close();
}

//----- Imprime no terminal o arquivo
void Entrada::imprimeArquivo()
{
    if (meuArquivo.is_open())
    {
        string linha;
        while (getline(meuArquivo, linha))
        {
            cout << linha << endl;
        }
    }
    else
    {
        cout << "Impossivel Abrir o Arquivo ( " << nome << " )!" << endl;
    }
    setPonteiro();
    cout << "linha: " << this->linha << " | coluna: " << this->coluna << endl;
}

//----- Retorna o número de linhas e colunas
void Entrada::tamanhoArquivo()
{
    int lin = 0, col = 0;

    if (meuArquivo.is_open())
    {
        string aux;
        char caractere;
        while (getline(meuArquivo, aux))
        {
            lin++;
        }
        setPonteiro();
        while (meuArquivo >> noskipws >> caractere)
        {
            if (caractere == '1' || caractere == '0')
            {
                col++;
            }
        }
    }
    else
    {
        cout << "Impossivel Abrir o Arquivo ( " << nome << " )!" << endl;
    }
    setPonteiro();

    this->coluna = col / lin;
    this->linha = lin;
}

//----- Elimina e retorna o marcador para posicao inicial do arquivo
void Entrada::setPonteiro()
{
    meuArquivo.clear();
    meuArquivo.seekg(0);
}

//----- Retorna o arquivo em forma de matriz
void Entrada::retornaMatriz(vector<int> &dados)
{
    char caractere;
    while (meuArquivo >> noskipws >> caractere)
    {
        if (caractere == '1')
        {
            dados.push_back(1);
        }
        else if (caractere == '0')
        {
            dados.push_back(0);
        }
    }
    setPonteiro();
}

//----- Retorna a quantidade de filósofos do arquivo
int Entrada::retornaQtdFilosofos()
{
    return linha;
}

//----- Retorna com quantos faz conexões (1)
void Entrada::retornaMaxLigacoes(vector<int> &max)
{
    char caractere;
    int contadorTotal = 0, contadorUm = 0;

    while (meuArquivo >> noskipws >> caractere)
    {
        if (caractere == '1')
        {
            contadorUm++;
            contadorTotal++;
        }
        if (caractere == '0')
        {
            contadorTotal++;
        }
        if (contadorTotal == this->linha)
        {
            max.push_back(contadorUm);
            contadorUm = 0;
            contadorTotal = 0;
        }
    }
    setPonteiro();
    cout << endl;
}

//----- Retorna a coluna que representa a quantidade de garrafas
int Entrada::retornaColuna()
{
    return coluna;
}

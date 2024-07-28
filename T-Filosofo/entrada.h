#ifndef ENTRADA_H
#define ENTRADA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Entrada
{
private:
    ifstream meuArquivo; // Objeto padrão de <fstream>
    string nome;         // Recebe o nome do arquivo
    int linha;           // Número de linhas
    int coluna;          // Número de colunas

public:
    Entrada(string caminho); // Construtor padrão
    ~Entrada();              // Destrutor padrão

    void imprimeArquivo();                     // Imprime no terminal o arquivo
    void tamanhoArquivo();                     // Retorna o número de linhas e colunas
    void setPonteiro();                        // Elimina e retorna o marcador para posicao inicial do arquivo
    void retornaMatriz(vector<int> &dados);    // Retorna o arquivo em forma de matriz
    int retornaQtdFilosofos();                 // Retorna a quantidade de filósofos do arquivo
    void retornaMaxLigacoes(vector<int> &max); // Retorna com quantos faz conexões (1)
    int retornaColuna();                       // Retorna a coluna que representa a quantidade de garrafas
};

#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <boost/regex.hpp> //lembrar de colocar no relatório que a gente tá usando essa biblioteca
#include <boost/algorithm/string/regex.hpp>
#include "classes.hpp"
 
using namespace std;
using namespace boost;

void arquivo_registro(Artigo a){
        FILE *arquivo;
        arquivo = fopen("registro.bin", "wb");
        fseek(arquivo, 0, SEEK_END);
        fwrite(&a, sizeof(Artigo), 1, arquivo);
        fclose(arquivo);
}

void parser(string arq, Hash table){
    ifstream arquivo;
    string line;
    vector<string> linha;
    arquivo.open(arq);
   // Hash table = Hash();

 
    if(arquivo.is_open()){
        while(getline(arquivo, line)){
            split_regex(linha, line, regex("(\";\"|(;\"){2}|\";|;\")")); //  vai splitar por esse regex.
            
            Artigo a = Artigo();
            linha[0].erase(linha[0].begin());
          
            if(linha.size() < 7){
                getline(arquivo, line);
              
                vector<string> linha2;
                split_regex(linha2, line, regex("(\";\"|(;\"){2}|\";|;\")"));            
                string x = linha[linha.size()-1];
                string b = linha2[0];
                  
                if((b[0] != '\"') && (x[x.size()-1] != ';') && (b[0] != ';') && (x[x.size()-1] != '\"')){
                    linha[linha.size()-1] = linha[linha.size()-1]+linha2[0];
                    linha2.erase(linha2.begin());

                    linha.reserve(linha2.size());
                    linha.insert(linha.end(), linha2.begin(), linha2.end());
                    
                    a.id = stoi(linha[0]);
                    linha[1].copy(a.titulo, 300);
                    a.ano = stoi(linha[2]);
                    linha[3].copy(a.autores, 150);
                    a.citacao= stoi(linha[4]);
                    linha[4].copy(a.atualizacao, 20);
                    linha[6].copy(a.resumo, 1024);
                }
                table.insert_hash(a);
                arquivo_registro(a);
            }

            else if(linha.size() > 7){
                string y = linha[2];
                if(y[0] == 22){
                    y = ";\"" + y;
                    linha.erase(linha.begin()+2);
                    linha[1] = linha[1] + y;

                    a.id = stoi(linha[0]);
                    linha[1].copy(a.titulo, 300);
                    a.ano = stoi(linha[2]);
                    linha[3].copy(a.autores, 150);
                    a.citacao= stoi(linha[4]);
                    linha[4].copy(a.atualizacao, 20);
                    linha[6].copy(a.resumo, 1024);
                    //cout<<a.id<<endl;
                    table.insert_hash(a);
                    arquivo_registro(a);
                }
            }
 
            else{
                              
                a.id = stoi(linha[0]);
                linha[1].copy(a.titulo, 300);
                a.ano = stoi(linha[2]);
                linha[3].copy(a.autores, 150);
                a.citacao= stoi(linha[4]);
                linha[4].copy(a.atualizacao, 20);
                linha[6].copy(a.resumo, 1024);
                arquivo_registro(a);
                table.insert_hash(a);
            } 
            //coloca na árvore 1
            //coloca na árvore 2
        }

        
        arquivo.close();
        table.insert_arquivo();
        cout << "Arquivo Hash Criado." << endl;

     	//table.findrec(32);

    }

    else{
        cout << "Nao conegui abrir o arquivo!" << endl;
    }
}
 
int main(){
    Hash table = Hash();
    
    int opcao;
    cout << " ***** Bem - Vindx ***** " << endl;
    
    while(1){
        cout << "0 - Sair." << endl;
        cout << "1 - upload(FILE), carrega do arquivo inicial para o arquivo Hash e arquivos de Índice. Entrada: FILE - string com o nome do arquivo." << endl;
        cout << "2 - findrec(ID), pesquisar no arquivo Hash por um artigo. Entrada: ID - tipo Inteiro." << endl;

        cout << "\n";
        cout << "Insira a opcao >> ";
        cin >> opcao;
        cout << "\n";
        

        if(opcao == 0){
            cout << "Saindo......" << endl;
            break;
        }

        else if(opcao == 1){
            string arquivo;
            // cout << "Insira o nome do arquivo >> ";
            // cin >> arquivo;
            cout << "Criando arquivos......." << endl;
            //parser(arquivo, table);
            cout << "\n";
            
            parser("artigo.csv", table);
        }

        else if (opcao == 2){
            int id;
            cout << "Insira o ID do artigo >> ";
            cin >> id;
            cout << "\n";
            table.findrec(id);
        }

        else{
            cout << "Opcao invalida, tente novamente :)" << endl;

        }
        
        cout << "\n";

    }
     
    return 0;
}

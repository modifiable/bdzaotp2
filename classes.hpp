#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>

using namespace std;
 


#ifndef CLASSES
#define CLASSES

class ArvoreB{
	int m = 124;
	int mm = 2*m+1;
};

class Formato{
	int indice_registro;
	int chave;
	int indice_nodo;
};

class Nodo{
	vector<Formato> nodo; // o tamanho n pode passar de 2 m
};

class Artigo{
    public:
    
    int id;
    char titulo[300];
    unsigned short int ano;
    char autores[150];
    unsigned short int citacao;
    char atualizacao[20];
    char resumo[1024];
    
};
 
class Bloco{
    public:
    
    char cabecalho[1088];
    vector<Artigo> block;
  
};
 
class Hash{
    public:
    const int TAM = 766079;  
    vector<Artigo> overflow;
    vector <Bloco> hash;

    Hash(){
      hash.resize(TAM);
    }
  
  
    void insert_hash(Artigo a){
       if(hash[a.id%TAM].block.size() < 2){
         hash[a.id%TAM].block.push_back(a);
       } 
       else{
       //cout << "entrei overflow";    
         overflow.push_back(a);
       }
    }   

    void insert_arquivo(){
  //   	std::ofstream os ("hash.bin", std::ofstream::binary);

    	  FILE *arquivo, *overfl;
    	  arquivo = fopen("hash.bin", "wb");
    	  overfl = fopen("over.bin", "wb");
    	  //cout << "oi" << endl;
    	  for(int i = 0; i < hash.size(); i++){
    	  	//cout << "vou tentar escrever" << endl;
    	  	fwrite(hash[i].block.data(), sizeof(Artigo), hash[i].block.size(), arquivo);
    	  	//fwrite(&hash[i].block[1], 1504, 1, arquivo);
    	  	//cout << "escrevi" << endl;
    	  }
    	  fclose(arquivo);
    	  //cout << "oi2" << endl;
    	  
    	  fwrite(overflow.data(), 1504, overflow.size(), overfl);
    	  
    	  //cout << "escreveu no overflow" << endl;

    	  fclose(overfl);

    	  //return arquivo;
    }

    void findrec(int id){ 	
  //   	std::ifstream is("hash.bin", std::ios::binary);
    	int finder = 0;
    	int cont_artigos = 0;
    	FILE *arquivo = fopen("hash.bin", "rb");
		int pos = (id%TAM) * 3008;
		std::vector<Artigo> b(2);
		fseek(arquivo, pos, SEEK_SET);
		size_t sz = fread(b.data(), sizeof b[0], b.size(), arquivo);
		fclose(arquivo);
		
		for(int i = 0; i < b.size(); i++){
			if(id == b[i].id){
				cout << "Id: "<< b[i].id << endl;
				cout << "Titulo: "<< b[i].titulo << endl;
				cout << "Ano: "<< b[i].ano << endl;
				cout << "Autores: "<< b[i].autores << endl;
				cout << "Citacoes: "<< b[i].citacao << endl;
				cout << "Atualizacao: "<< b[i].atualizacao << endl;
				cout << "Snippet: "<< b[i].resumo << endl;

				cout << endl << "Quantidade de Artigos no bloco: "<< b.size() << endl;
				cout << "Total de Blocos Lidos: 1" << endl;

				finder = 1;
				break;
			}
		}

		if(finder == 0){
			FILE *arquivo2 = fopen("over.bin", "rb");
			Artigo b = Artigo();
			while(fread(&b, sizeof(Artigo), 1, arquivo2)){
				cont_artigos++;

				if(id = b.id){
					cout << "Id: "<< b.id << endl;
					cout << "Titulo: "<< b.titulo << endl;
					cout << "Ano: "<< b.ano << endl;
					cout << "Autores: "<< b.autores << endl;
					cout << "Citacoes: "<< b.citacao << endl;
					cout << "Atualizacao: "<< b.atualizacao << endl;
					cout << "Snippet: "<< b.resumo << endl;

					finder = 1;
					cout << endl << "Total de Blocos Lidos no Arquivo de Hash: 1" << endl;
					cout << "Total de Arquivos Lidos no Arquivo Overflow: " << cont_artigos << endl;
					break;
				}
			}
		}

		if(finder == 0){
			cout << "Artigo não encontrado" << endl;
		}
    }

    // void printa_hash(){
    //   for(int i = 0; i < TAM; i++){
    //     if(hash[i].block.size() > 0){
    //       cout <<"Bloco "<< i << endl; 
    //       for(int j = 0; j < hash[i].block.size(); j++){
    //         cout << hash[i].block[j].id << endl;
    //       }        
    //     }
    //   }
    // } 
};

#endif

/*
Autor: Joao Paulo de Lima Barbosa <joao@barbosa.net.br> - Professor de Estruturas de Dados I

Este é o exemplo de código feito em sala no dia 19/03/2015, na aula de estruturas de dados.

O objetivo do código éra demonstrar o funcionamento de arquivos binarios (arquivos estruturados)

Ao final da aula a funcao de sobscrever um registro nao estava funcionando, pois o novo regstro
que deveria substituir um registro existente (gravar por cima) era gravado sempre no final do
arquivo, mesmo após o posicionamento do cursor através de feek.

Após a análise do código, obervei que o problema estava relacionado a forma de abertura do arquivo,
pois o arquivo estava sendo aberto com 'a+w', a abertura com 'a' implica em somente aceitar
inserções ao final do arquivo (append). Para corrigir isso, basta apenas abrir o arquivo com 'r+b'
ver maiores detalhes na funcao 'gravar_carro'

################## Continuar exercicio ##################

Os alunos devem continuar esta implementacao, e desenvolver os seguintes recursos:

a) paginacão na tela que lista todos os carros, mostrar registros de 3 em 3, pausando a listagem

b) Implementar a navegacao para frente e para trás no arquivo, de forma que o usuario possa navengar entre os registros



############# Usando Linux / Mac / Windows #############
Para permitir que este codgo seja compilado nos três sistemas operacionais, coloque abaixo
alguns #defines especificos para windows, linux ou mac, basta descomentar o que corresponde ao
seu sistema operacional e manter os demais comentados.
Veja tambem a funcao limpa_buffer(), pois ela tem opcao para a limpeza de buffer nos tres sistemas


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARROS_DAT "mycars.dat"

// Descomentar o bloco abaixo para Linux/Mac
#define CLEAR "clear"
#define PAUSE "read a"

// Descomentar o bloco abaixo para Windows
//#define CLEAR "cls"
//#define PAUSE "pause"


typedef struct _carro {
	char placa[9];
	char modelo[32];
	char marca[32];
	char cor[16];
	int ano;
} tpCarro;


void limpa_buffer(){
	// Limpeza do buffer do teclado para Linux/Mac
	__fpurge(stdin);
	// Limpeza do buffer do teclado para Windows
	//fflush(stdin);
}


void ler_carro(tpCarro *carro){
	printf("Informe a placa: ");
	limpa_buffer();
	scanf("%s",carro->placa);

	printf("Informe o modelo : ");
	limpa_buffer();
	scanf("%[^\n]s",carro->modelo);

	printf("Informe a marca: ");
	limpa_buffer();
	scanf("%[^\n]s",carro->marca);

	printf("Informe o ano: ");
	limpa_buffer();
	scanf("%d",&carro->ano);

	printf("Informe a cor: ");
	limpa_buffer();
	scanf("%[^\n]s",carro->cor);
}

void imprime_carro(tpCarro carro){
	printf("--------------------------------\n");
	printf("Placa.: %s\n", carro.placa);
	printf("Modelo: %s\n", carro.modelo);
	printf("Marca.: %s\n", carro.marca);
	printf("Ano...: %d\n", carro.ano);
	printf("Cor...: %s\n", carro.cor);
	printf("--------------------------------\n");
}

void print_erros(int cod,char erro[]){
	switch (cod){
	     case 1: {
			  printf("Erro ao abrir arquivo %s\n", erro);
			  break;
					}
	     case 2: {
			  printf("Erro ao escrever no arquivo %s\n", erro);
			  break;
					}
		}
}

void gravar_carro(tpCarro carro, long pos_cursor, int SEEK){
	FILE *arq;

	// O erro estava aqui, pois aberturas com 'a' fazer SOMENTE append, ou seja inserçoes ao final
	// Logo, nao eh permitido reposicionamento de cursor para gravacao (fwrite), aceitando apenas
	// reposicionamento de cursor para leitura. Para currigir basta fazer a abertura com 'r+w'
	//if (arq = fopen(CARROS_DAT,"a+b")){
	if (arq = fopen(CARROS_DAT,"r+b")){

		fseek(arq,pos_cursor,SEEK);

		fwrite(&carro,sizeof(tpCarro),1,arq);

		if(ferror(arq)){
			print_erros(2,CARROS_DAT);
		}

		fclose(arq);
	}	else	{
			print_erros(1,CARROS_DAT);
	}
}

void ler_todos_carros(){
	tpCarro carro;
	FILE *arq;

	if (arq = fopen(CARROS_DAT,"rb")){

		fread(&carro,sizeof(tpCarro),1,arq);

		while (!feof(arq)){
			imprime_carro(carro);

			fread(&carro,sizeof(tpCarro),1,arq);
		}

		fclose(arq);

	}else{
		print_erros(1,CARROS_DAT);
	}

}

long pesquisar_placa(char placa[]){
	tpCarro carro;
	FILE *arq;
	long pos_cursor = -1;

	if (arq = fopen(CARROS_DAT,"rb")){

		fread(&carro,sizeof(tpCarro),1,arq);

		while (!feof(arq)){
			if(strcmp(carro.placa,placa) == 0){
			     fseek(arq, -1 * sizeof(tpCarro),SEEK_CUR);
			     pos_cursor = ftell(arq);
			     //pos_cursor = ftell(arq) - sizeof(tpCarro);
			     break;

			}
			fread(&carro,sizeof(tpCarro),1,arq);
		}

		fclose(arq);

		return pos_cursor;

	}else{
		print_erros(1,CARROS_DAT);
	}

}

void sobresver_registro(){
     	char placa[9];
	long pos_cursor;
	tpCarro car;

	printf("Informe a placa do carro a ser sobscrito: ");
	limpa_buffer();
	scanf("%s",placa);

	pos_cursor = pesquisar_placa(placa);

	if (pos_cursor != -1){
	     printf("\nPlaca encondrada! Digite os dados do novo carro\n");
	     ler_carro(&car);
	     gravar_carro(car,pos_cursor,SEEK_SET);
	     printf("Carro sobscrito com sucesso!\n");

	}else{
		printf("Placa nao encontrada\n\n");
	}

}

int menu(){
     	int opc;

	system(CLEAR);
	printf("##################################\n");
	printf("              MENU                \n");
	printf("1 - Cadastrar carro\n");
	printf("2 - Listar todos os carros\n");
	printf("3 - Sobrescrever\n\n");
	printf("0 - Sair\n\n");
	printf("Escolha uma opcao: ");

	scanf("%d",&opc);

	return opc;
}



int main(void){
	tpCarro car;
	int opc = 1;

	while (opc){
		opc = menu();

		switch(opc){
			case 1: {
				     system(CLEAR);
				     ler_carro(&car);
				     gravar_carro(car,0,SEEK_END);
				     break;
				}
			case 2: {
				     system(CLEAR);
				     ler_todos_carros();
				     system(PAUSE);
				     break;
				}
			case 3: {
				     system(CLEAR);
				     sobresver_registro();
				     system(PAUSE);
				     break;
				}

		}

	}

	return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"



//! @brief Função que cria uma lista ligada para os clientes
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_  NIF do Cliente a ser inserido
//! @param nome_ Nome do Cliente a ser inserido
//! @param idade_ Idade do Cliente a ser inserido
//! @param morada_ Morada do Cliente a ser inserido
//! @param saldo Saldo do Cliente a ser inserido
//! @return 
Clientes* inserir_cliente(Clientes* inicio, int NIF_, char nome_[], int idade_,char morada_[], int saldo, char localizacao[]) { 
	
	
		Clientes* Novo = malloc(sizeof(struct registo_clientes));
		if (Novo != NULL) {
			Novo->NIF = NIF_;
			Novo->idade = idade_;
			Novo->saldo = saldo;
			strcpy(Novo->nome, nome_);
			strcpy(Novo->morada, morada_);
			strcpy(Novo->localizacao,localizacao);
			Novo->proximo_cliente = inicio;
			return Novo;
		}
		else {
			return inicio;
		}
} 
//! @brief Função que imprime os dados inseridos na lista ligada para os clientes anteriormente criada
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @return 

Clientes* imprimir_clientes(Clientes* inicio) { 

	while (inicio != NULL) {
		printf("%d %s %d %s %d %s\n",inicio->NIF, inicio->nome, inicio->idade, inicio->morada, inicio->saldo, inicio->localizacao);
		inicio = inicio->proximo_cliente;
	}
}

//! @brief Dado uma lista ligada, esta função permite remover um determinado elemento da lista, dado o seu NIF
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param code NIF do cliente a ser removido 
//! @return 
Clientes* remover_clientes(Clientes* inicio, int code) {
	
	
		Clientes* anterior = inicio, *atual = inicio, *aux;

		if (atual == NULL){
			return(NULL);
		}
		else if (atual->NIF == code) 
		{
			aux = atual->proximo_cliente;
			free(atual);
			return(aux);
		}
		else
		{
			for (atual; atual != NULL && atual->NIF != code;atual=atual->proximo_cliente){
				
				anterior = atual;
				
			}
				if (atual == NULL) {
					return(inicio);
				}
				else
				{
					anterior->proximo_cliente = atual->proximo_cliente;
					free(atual);
					return(inicio);
				}
		}
	
}

//! @brief Função que dado o NIF de um utilizador, carrega o saldo no parametro saldo
//! @param inicio  Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_procurado NIF do utilizador a carregar o saldo
//! @return 
int saldo(Clientes* inicio, int NIF_procurado, int valor){ 


	Clientes* currentt = inicio;

	
	for (currentt; currentt != NULL; currentt = currentt->proximo_cliente) {
		if (NIF_procurado == currentt->NIF) {
			currentt->saldo = currentt->saldo + valor;
			return 1;
		}
	
}
	return 0;

}

//! @brief Esta função percorre a lista ligada de clientes, verificando se o username e a password digitadas pelo utilizador encontram-se na lista, se sim o login dá certo
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param username Username do cliente a verificar se existe no sistema
//! @param code Codigo do cliente a verificar se existe no sistema
//! @return 
int login_clientes(Clientes* inicio, char* username, int* code) { 
	Clientes* current = inicio;
	for (current; current != NULL; current = current->proximo_cliente) {
		if (strcmp(current->nome, username) == 0 && code == current->NIF) {
			return 1;
		}

	} return 0;
}

//! @brief Função que ordena os clientes os na lista ligada clientes por ordem crescente do seu NIF
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
void ordenacao_clientes(Clientes* inicio) { 

	Clientes* pi = inicio;
	Clientes* pj = NULL;
	int aux;


	for (pi; pi != NULL; pi = pi->proximo_cliente) {
		for (pj = pi->proximo_cliente; pj != NULL; pj = pj->proximo_cliente) {
			if (pi->NIF > pj->NIF) {
				aux = pi->NIF;
				pi->NIF = pj->NIF;
				pj->NIF = aux;
			}
		}
	}
}

//! @brief Esta função guarda os dados presentes na lista ligada num ficheiro de texto, com o nome "Clientes"
//! @param inicio 
void GuardarClientes(Clientes* inicio) 
{
	FILE* fp;
	fp = fopen("Clientes.txt", "w");
	if (fp != NULL)
	{
		Clientes* aux = inicio;
		for (aux; aux != NULL; aux = aux->proximo_cliente) {
			fprintf(fp, "%d;%s;%d;%s;%s;%d\n", aux->NIF, aux->nome,aux->idade, aux->morada, aux->localizacao,aux->saldo);
		}
		fclose(fp);
		

	}
	
}
//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro de texto "Clientes", inserindo-os na lista ligada novamente
//! @return 
Clientes* LerClientes() {
	FILE* fp;
	int NIF, idade, saldo;
	char nome[50], morada[50],localizacao[50];
	Clientes* aux = NULL;
	fp = fopen("Clientes.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%d;%[^;];%[^;];%d\n", &NIF, nome, &idade, morada, localizacao,&saldo);
			aux = inserir_cliente(aux, NIF, nome, idade, morada, saldo,localizacao);
		}
		fclose(fp);
	}
	return(aux);
}
//! @brief Esta função guarda os dados presentes na lista ligada num ficheiro binário, com o nome "Clientes"
//! @param inicio 
void GuardarClientes_Binario(Clientes* inicio) 
{
	FILE* fp;
	fp = fopen("Clientes.bin", "wb");
	if (fp != NULL)
	{
		Clientes* aux = inicio;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Clientes), 1, fp);
			aux = aux->proximo_cliente;
		}
		fclose(fp);
	}
}

//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro binário "Clientes", inserindo-os na lista ligada novamente
//! @return 
Clientes* LerClientes_Binario()
{
	FILE* fp;
	Clientes* aux = NULL;
	fp = fopen("Clientes.bin", "rb");

	if (fp != NULL)
	{
		Clientes current;
		while (fread(&current, sizeof(Clientes), 1, fp) == 1)
		{
			aux = inserir_cliente(aux, current.NIF, current.nome, current.idade, current.morada, current.saldo,current.localizacao);
		}
		fclose(fp);
	}
	return aux;

}

//! @brief Esta função percorre a lista ligada clientes e verifica se o NIF do cliente já se encontra lá
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF NIF a verificar se existe no sistema
//! @return 
int verificar_registo_clientes(Clientes* inicio, int NIF) { 



	for (inicio; inicio != NULL; inicio = inicio->proximo_cliente) {
		if (inicio->NIF == NIF) {
			return 1;
		}
		
			
		
	}
	return 0;
}

//! @brief sta função permite alterar os dados de um clientes, substituindo na lista ligada os novos dados nos parametros escolhidos pelo utilizador
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_procurado NIF do utilizador a alterar os dados
void AlterarDados(Clientes* inicio, int NIF_procurado) {

	int opcao;
	char novo_nome[50], nova_morada[50];
	Clientes* current = inicio;

	menu_definicoes();

	printf("Que parametro deseja alterar?\n");
	scanf("%d", &opcao);

	if (opcao == 1) {
		scanf("%*c");
		printf("Digite o novo nome de usuario\n");
		gets(novo_nome);
		for (current; current != NULL; current = current->proximo_cliente) {
			if (NIF_procurado == current->NIF) {
				strcpy(current->nome, novo_nome);
				clear();
				printf("Dados atualizados com sucesso\n");
			}
		
		}
	}
	else if (opcao == 2) {
		scanf("%*c");
		printf("Digite a sua nova morada\n");
		gets(nova_morada);
		for (current; current != NULL; current = current->proximo_cliente) {
			if (NIF_procurado == current->NIF) {
				strcpy(current->morada, nova_morada);
				clear();
			}
			
		}
	}
	
	

}
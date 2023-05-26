#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"

//! @brief Função que cria uma lista ligada para os veiculos
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param codigo_ Codigo do meio a ser inserido
//! @param bateria_ Bateria do meio a ser inserido
//! @param localizacao_ 
//! @param custo_ Custo por Km do meio a ser inserido
//! @param tipo_ Tipo do meio a ser inserido
//! @param reserva_ 1 se tiver reservado ou 0 se nao tiver
//! @param NIF_reserva_ 0 se nao tiver reservado ou NIF do cliente que a reservou
//! @return 

Veiculos* inserir_veiculos(Veiculos* inicio, int codigo_, int bateria_, char localizacao_[], int custo_, char tipo_[], int reserva_,int NIF_reserva_, time_t horario_reserva) { 
	Veiculos* Novo = malloc(sizeof(struct registo_veiculos));

	if (Novo != NULL) {
		Novo->bateria = bateria_;
		Novo->codigo = codigo_;
		Novo->custo = custo_;
		Novo->reserva = reserva_;
		Novo->NIF_reserva = NIF_reserva_;
		strcpy(Novo->localizacao, localizacao_);
		strcpy(Novo->tipo, tipo_);
		Novo->horario_reserva = horario_reserva;
		Novo->proximo_veiculo = inicio;

		return Novo;
	}
	else {
		return inicio;
	}
}

//! @brief Função que imprime os dados inseridos na lista ligada para os veiculos anteriormente criada
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @return 
Veiculos* imprimir_veiculos(Veiculos* inicio) { 
	while (inicio != NULL) {
		
		printf("%d %d %s %d %s\n", inicio->codigo, inicio->bateria, inicio->localizacao, inicio->custo, inicio->tipo);
		inicio = inicio->proximo_veiculo;
	}
}
//! @brief Dado uma lista ligada, esta função permite remover um determinado elemento da lista, dado o seu código
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param code Codigo do veiculo a remover
//! @return 
Veiculos* remover_veiculos(Veiculos* inicio, int code) { 

	Veiculos* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) {
		return(NULL);
	}
	else if (atual->codigo == code)
	{
		aux = atual->proximo_veiculo;
		free(atual);
		return(aux);
	}
	else
	{
		for (atual; atual != NULL && atual->codigo != code; atual = atual->proximo_veiculo) {

			anterior = atual;
		}
		if (atual == NULL) {
			return(inicio);
		}
		else
		{
			anterior->proximo_veiculo = atual->proximo_veiculo;
			free(atual);
			return(inicio);
		}
	}

}

//! @brief Função que ordena os veiculos inseridos na lista ligada veiculos por ordem decrescente da sua bateria
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
void ordenacao_veiculos(Veiculos* inicio) { 

	Veiculos* pi = inicio;
	Veiculos* pj = NULL;
	int aux1, aux2;
	int aux;
	char loca[50], tipo[50];


	for (pi; pi != NULL; pi = pi->proximo_veiculo) {
		for (pj = pi->proximo_veiculo; pj != NULL; pj = pj->proximo_veiculo) {
			if (pi->bateria < pj->bateria) {
				aux = pi->bateria;
				pi->bateria = pj->bateria;
				pj->bateria = aux;
				aux1 = pi->codigo;
				pi->codigo = pj->codigo;
				pj->codigo = aux1;
				aux2 = pi->custo;
				pi->custo = pj->custo;
				pj->custo = aux2;
				strcpy(loca, pi->localizacao);
				strcpy(pi->localizacao, pj->localizacao);
				strcpy(pj->localizacao, loca);
				strcpy(tipo, pi->tipo);
				strcpy(pi->tipo, pj->tipo);
				strcpy(pj->tipo, tipo);
				
			}
		}
	}
}

//! @brief sta função guarda os dados presentes na lista ligada num ficheiro de texto, com o nome "Veiculos"
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
void GuardarVeiculos(Veiculos* inicio) 
{
	FILE* fp;
	fp = fopen("Veiculos.txt", "w");
	if (fp != NULL)
	{
		Veiculos* aux = inicio;
		for (aux; aux != NULL; aux = aux->proximo_veiculo) {
			fprintf(fp, "%d;%d;%s;%d;%s;%d;%d;%ld\n", aux->codigo, aux->bateria,
				aux->localizacao, aux->custo, aux->tipo, aux->reserva, aux->NIF_reserva,aux->horario_reserva);
		}
		fclose(fp);


	}

}
//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro de texto "Veiculos", inserindo-os na lista ligada novamente
//! @return 
Veiculos* LerVeiculos() { 
	FILE* fp;
	int code,cust, reserva, NIF_reserva;
	int bat;
	char tipo[50], loca[50];
	time_t horario_reserva;
	Veiculos* aux = NULL;
	fp = fopen("Veiculos.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%[^;];%d;%[^;];%d;%d;%ld\n", &code, &bat, loca, &cust, tipo, &reserva, &NIF_reserva, &horario_reserva);
			aux = inserir_veiculos(aux, code, bat, loca, cust, tipo, reserva, NIF_reserva, horario_reserva);
		}
		fclose(fp);
	}
	return(aux);
}

//! @brief Esta função guarda os dados presentes na lista ligada num ficheiro binário, com o nome "Veiculos"
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
void GuardarVeiculos_Binario(Veiculos* inicio) 
{
	FILE* fp;
	fp = fopen("Veiculos.bin", "wb");
	if (fp != NULL)
	{
		Veiculos* aux = inicio;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Veiculos), 1, fp);
			aux = aux->proximo_veiculo;
		}
		fclose(fp);
	}
}

//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro binário "Veiculos", inserindo-os na lista ligada novamente
//! @return 
Veiculos* LerVeiculos_Binario() 
{
	FILE* fp;
	Veiculos* aux = NULL;
	fp = fopen("Veiculos.bin", "rb");

	if (fp != NULL)
	{
		Veiculos current;
		while (fread(&current, sizeof(Veiculos), 1, fp) == 1)
		{
			aux = inserir_veiculos(aux, current.codigo, current.bateria, current.localizacao, current.custo, current.tipo, current.reserva, current.NIF_reserva, current.horario_reserva);
		}
		fclose(fp);
	}
	return aux;

}

//! @brief Esta função percorre a lista ligada veiculos e verifica se o codigo do veiculo já se encontra lá
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param codigo Codigo a verificar se existe no sistema
//! @return 
int verificar_registo_veiculos(Veiculos* inicio, int codigo){ 



	for (inicio; inicio != NULL; inicio = inicio->proximo_veiculo) {
		if (inicio->codigo == codigo){
			return 1;
		}



	}
	return 0;
}

//! @brief Função que percorre a lista ligada veiculos e verifica o parametro localização, se o parametro contiver o mesmo conteudo do que o utilizador pediu, mostra somente essa localização
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @return 
Veiculos* LocalizarVeiculos(Veiculos* inicio, char localizacao_pretendida[]) {

	
		for(inicio; inicio != NULL; inicio = inicio->proximo_veiculo){
			if ((strcmp(inicio->localizacao, localizacao_pretendida) == 0) && inicio->reserva == 0 && inicio->NIF_reserva == 0) {
				printf("%d %d %s %d %s\n", inicio->codigo, inicio->bateria, inicio->localizacao, inicio->custo, inicio->tipo);
				
			
		}
	

}
}

char* verLocalizacao(Veiculos* inicio, int code){
	Veiculos* aux= inicio;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		if(aux->codigo == code){
			return aux->localizacao;
		}
	}
	return 0;
}

int gerarCode(Veiculos* inicio){

	Veiculos* aux = inicio;
	int count = 1;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		count++;
		
	}
	return count;
}


int retiraBateria(Veiculos* inicio, double tempoReserva, int code){

	Veiculos* aux = inicio;

	double bateriaaRemover = tempoReserva * 0.50;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		if(aux->codigo == code){
			aux->bateria = aux->bateria - bateriaaRemover;
			return aux->bateria;
		}
	}
}

char* verTipo(Veiculos* inicio, int code){

	Veiculos* aux = inicio;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		if(aux->codigo == code){
			return aux->tipo;
		}
	}
}


int atualizaLocalizacao(Veiculos* inicio,int code,char novaLocalizacao[]){

	Veiculos* aux = inicio;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		if(aux->codigo == code){
			strcpy(aux->localizacao, novaLocalizacao);
			return 1;

		}

	}
	return 0;
}



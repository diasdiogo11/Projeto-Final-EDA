#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "structs.h"



//! @brief Função que cria uma lista ligada para os clientes
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_  NIF do Cliente a ser inserido
//! @param nome_ Nome do Cliente a ser inserido
//! @param idade_ Idade do Cliente a ser inserido
//! @param morada_ Morada do Cliente a ser inserido
//! @param saldo Saldo do Cliente a ser inserido
//! @return 
Clientes* inserir_cliente(Clientes* inicio, int NIF_, char nome_[], int idade_,char morada_[], int saldo) { 
	
	
		Clientes* Novo = malloc(sizeof(struct registo_clientes));
		if (Novo != NULL) {
			Novo->NIF = NIF_;
			Novo->idade = idade_;
			Novo->saldo = saldo;
			strcpy(Novo->nome, nome_);
			strcpy(Novo->morada, morada_);
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
		printf("%d %s %d %s %d\n",inicio->NIF, inicio->nome, inicio->idade, inicio->morada, inicio->saldo);
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

Veiculos* inserir_veiculos(Veiculos* inicio, int codigo_, int bateria_, char localizacao_[], int custo_, char tipo_[], int reserva_,int NIF_reserva_) { 
	Veiculos* Novo = malloc(sizeof(struct registo_veiculos));

	if (Novo != NULL) {

		Novo->bateria = bateria_;
		Novo->codigo = codigo_;
		Novo->custo = custo_;
		Novo->reserva = reserva_;
		Novo->NIF_reserva = NIF_reserva_;
		strcpy(Novo->localizacao, localizacao_);
		strcpy(Novo->tipo, tipo_);
		Novo->proximo_veiculo = inicio;

		return Novo;
	}
	else {
		return inicio;
	}

}

void criarmatriz(Veiculos* inicio) {

	int count = 0, i, j, G[50][50];
	while (inicio != NULL) {

		count++;
		inicio = inicio->proximo_veiculo;
	}

	printf("\nEnter the adjacency matrix:\n");
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scanf("%d", &G[i][j]);
	FILE* fp;
	fp = fopen("matriz.txt", "w");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			fprintf(fp, "%d", G[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

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

//! @brief Função que dado um NIF, imprime as reservas atuais de um utilizador
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF NIF do cliente que desejamos ver as reservas ativas
//! @return 
Veiculos* imprimir_reservas(Veiculos* inicio, int NIF) { 

	Veiculos* current = inicio;

	for(current; current != NULL; current= current->proximo_veiculo) {
		if (current->NIF_reserva == NIF) {
			printf("%d %d %s %d %s\n", current->codigo, current->bateria, current->localizacao, current->custo, current->tipo);
		}

		
	}
}

//! @brief Função que cria uma lista ligada para os gestores
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param email_  Email do Gestor a ser inserido
//! @param password_ Password do Gestor a ser inserido
//! @return 
Gestores* inserir_gestores(Gestores* inicio, char email_[], char password_[]) {  
	Gestores* Novo = malloc(sizeof(struct registo_gestores));

	if (Novo != NULL) {

		strcpy(Novo->email, email_);
		strcpy(Novo->password, password_);
		Novo->proximo_gestor = inicio;

		return Novo;
	}
	else {
		return inicio;
	}

}
//! @brief Função que imprime os dados inseridos na lista ligada para os gestores anteriormente criada
//! @param inicio  Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @return 
Gestores* imprimir_gestores(Gestores* inicio) { 

	while (inicio != NULL) {
		printf("%s %s\n", inicio->email, inicio->password);
		inicio = inicio->proximo_gestor;
	}
}
//! @brief Dado uma lista ligada, esta função permite remover um determinado elemento da lista, dado o seu código
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param email Email do gestor a remover
//! @return 
Gestores* remover_gestores(Gestores* inicio, char email[]) { 


	Gestores* anterior = inicio, * atual = inicio, * aux;
	
	if (atual == NULL) {
		return(NULL);
	}
	else if (strcmp(atual->email, email) == 0)
	{
		aux = atual->proximo_gestor;
		free(atual);
		return(aux);
	}
	else
	{
		for (atual; atual != NULL && strcmp(atual->email, email) == 0; atual = atual->proximo_gestor) {

			anterior = atual;

		}
		if (atual == NULL) {
			return(inicio);
		}
		else
		{
			anterior->proximo_gestor = atual->proximo_gestor;
			free(atual);
			return(inicio);
		}
	}

}

//! @brief Função que dado o NIF de um utilizador, carrega o saldo no parametro saldo
//! @param inicio  Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_procurado NIF do utilizador a carregar o saldo
//! @return 
int saldo(Clientes* inicio, int NIF_procurado){ 

	int valor;

	printf("Qual a quantia a adicionar?\n");
	scanf("%d", &valor);
	Clientes* current = inicio;

	
	for (current; current != NULL; current = current->proximo_cliente) {
		if (NIF_procurado == current->NIF) {
			current->saldo = current->saldo + valor;
			return 1;
		}
	
}
	return 0;

}
//! @brief Esta função percorre a lista ligada de gestores, verificando se o username e a password digitadas pelo utilizador encontram-se na lista, se sim o login dá certo
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param username Username do gestor a verificar se existe no sistema
//! @param password  Password do gestor a verificar se existe no sistema
//! @return 
int login_gestores(Gestores* inicio, char* username, char* password) {
	Gestores* current = inicio;
	for (current; current != NULL; current = current->proximo_gestor) {
		if (strcmp(current->email, username) == 0 && strcmp(current->password, password) == 0) {
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

//! @brief Função que ordena os veiculos inseridos na lista ligada veiculos por ordem decrescente da sua bateria
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
void ordenacao_veiculos(Veiculos* inicio) { 

	Veiculos* pi = inicio;
	Veiculos* pj = NULL;
	int aux, aux1, aux2;
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
			fprintf(fp, "%d;%d;%s;%d;%s;%d;%d\n", aux->codigo, aux->bateria,
				aux->localizacao, aux->custo, aux->tipo, aux->reserva, aux->NIF_reserva);
		}
		fclose(fp);


	}

}
//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro de texto "Veiculos", inserindo-os na lista ligada novamente
//! @return 
Veiculos* LerVeiculos() { 
	FILE* fp;
	int code, bat, cust, reserva, NIF_reserva;
	char tipo[50], loca[50];
	Veiculos* aux = NULL;
	fp = fopen("Veiculos.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%[^;];%d;%[^;];%d;%d\n", &code, &bat, loca, &cust, tipo, &reserva, &NIF_reserva);
			aux = inserir_veiculos(aux, code, bat, loca, cust, tipo, reserva, NIF_reserva);
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
			aux = inserir_veiculos(aux, current.codigo, current.bateria, current.localizacao, current.custo, current.tipo, current.reserva, current.NIF_reserva);
		}
		fclose(fp);
	}
	return aux;

}
//! @brief Esta função guarda os dados presentes na lista ligada num ficheiro binário, com o nome "Gestores"
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
void GuardarGestores_Binario(Gestores* inicio) 
{
	FILE* fp;
	fp = fopen("Gestores.bin", "wb");
	if (fp != NULL)
	{
		Gestores* aux = inicio;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Gestores), 1, fp);
			aux = aux->proximo_gestor;
		}
		fclose(fp);
	}
}
void GuardarGestores(Gestores* inicio) 
{
	FILE* fp;
	fp = fopen("Gestores.txt", "w");
	if (fp != NULL)
	{
		Gestores* aux = inicio;
		for (aux; aux != NULL; aux = aux->proximo_gestor) {
			fprintf(fp, "%s;%s\n", aux->email, aux->password);
		}
		fclose(fp);


	}

}
//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro binário "Gestores", inserindo-os na lista ligada novamente
//! @return 
Gestores* LerGestores_Binario() 
{
	FILE* fp;
	Gestores* aux = NULL;
	fp = fopen("Gestores.bin", "rb");

	if (fp != NULL)
	{
		Gestores current;
		while (fread(&current, sizeof(Gestores), 1, fp) == 1)
		{
			aux = inserir_gestores(aux, current.email, current.password);
		
	}
		fclose(fp);
	

}
	return aux;
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
			fprintf(fp, "%d;%s;%d;%s;%d\n", aux->NIF, aux->nome,aux->idade, aux->morada, aux->saldo);
		}
		fclose(fp);
		

	}
	
}
//! @brief Posteriormente, esta função lê os dados inseridos no ficheiro de texto "Clientes", inserindo-os na lista ligada novamente
//! @return 
Clientes* LerClientes() {
	FILE* fp;
	int NIF, idade, saldo;
	char nome[50], morada[50];
	Clientes* aux = NULL;
	fp = fopen("Clientes.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%d;%[^;];%d\n", &NIF, nome, &idade, morada, &saldo);
			aux = inserir_cliente(aux, NIF, nome, idade, morada, saldo);
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
			aux = inserir_cliente(aux, current.NIF, current.nome, current.idade, current.morada, current.saldo);
		}
		fclose(fp);
	}
	return aux;

}

//! @brief cabeçalho do menu principal
void menu_principal() { 
	int opcao;
	printf("*---------------- MENU PRINCIPAL ----------------*\n");
	printf("| 1.REGISTAR                                     |\n");
	printf("| 2.LOGIN                                        |\n");
	printf("| 0.EXIT                                         |\n");
	printf("*------------------------------------------------*\n");
	

}
//! @brief Cabeçalho menu de resgisto
void cabecalho_registar() { 
	
	printf("*------------------------------------*\n");
	printf("|               REGISTO              |\n");
	printf("*------------------------------------*\n");


}
//! @brief Cabeçalho do menu de login
void menu_login() { 


	
		printf("*--------------------------------------*\n");
		printf("| 1.ADMINISTRADOR                      |\n");
		printf("| 2.CLIENTE                            |\n");
		printf("*--------------------------------------*\n");
		
		
	
}
//! @brief Cabeçalho do menu de gestores
void menu_gestores() { 

	
	printf("*---------------- MENU GESTORES ----------------*\n");
	printf("| 1.INSERIR CLIENTE                             |\n");
	printf("| 2.REMOVER CLIENTE                             |\n");
	printf("| 3.LISTAR CLIENTES                             |\n");
	printf("| 4.INSERIR VEICULO                             |\n");
	printf("| 5.REMOVER VEICULO                             |\n");
	printf("| 6.LISTAR VEICULOS                             |\n");
	printf("| 7.GESTOR MASTER (ACESSO RESTRITO)             |\n");
	printf("| 0.EXIT                                        |\n");
	printf("*-----------------------------------------------*\n");
	
}
//! @brief Cabeçalho do menu do gestor "Master"
void menu_mastergestor() { 
	printf("*---------------- MENU GESTORES ----------------*\n");
	printf("| 1.ADICIONAR GESTOR                            |\n");
	printf("| 2.REMOVER GESTOR                              |\n");
	printf("| 3.ALTERAR DADOS GESTOR                        |\n");
	printf("| 0.VOLTAR                                      |\n");
	printf("*-----------------------------------------------*\n");



}
//! @brief Cabeçalho do menu de clientes
void menu_clientes() { 
	
	printf("*---------------- MENU CLIENTES ----------------*\n");
	printf("| 1.RESERVAR VEICULO                            |\n");
	printf("| 2.CANCELAR RESERVA                            |\n");
	printf("| 3.CARREGAR SALDO                              |\n");
	printf("| 4.DEFINICOES                                  |\n");
	printf("| 5.RESERVAS ATIVAS                             |\n");
	printf("| 0.EXIT                                        |\n");
	printf("*-----------------------------------------------*\n");
	
	
}
//! @brief Cabeçalho do menu de definições do clientes
void menu_definicoes() { 

	
	printf("*---------------- DEFINICOES ----------------*\n");
	printf("| 1.ALTERAR NOME DE USUARIO                  |\n");
	printf("| 2.ALTERAR MORADA                           |\n");
	printf("| 0.VOLTAR MENU CLIENTES                     |\n");
	printf("*--------------------------------------------*\n");

}
//! @brief Cabeçalho Admin
void cabecalho_admin() { 
	printf("*------------------------------------*\n");
	printf("|            ADMINISTRADOR           |\n");
	printf("*------------------------------------*\n");
}
//! @brief Cabeçalho clientes
void cabecalho_cliente() { 
	printf("*------------------------------------*\n");
	printf("|               CLIENTE              |\n");
	printf("*------------------------------------*\n");
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
//! @brief Esta função percorre a lista ligada gestores e verifica se o email do gestor já se encontra lá
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param email Email a verificar se existe no sistema
//! @return 
int verificar_registo_gestores(Gestores* inicio, char email[]) { 



	for (inicio; inicio != NULL; inicio = inicio->proximo_gestor) {
		if (strcmp(inicio->email, email) == 0) {
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

//! @brief Esta função foi feita para a reserva de veiculos, a função percorre a lista ligada veiculos e verifica se nos parametros "reserva" e "NIF_reserva" os valores estão a zero, se sim, permite ao utilizador reservar esse veiculos, alterando esses parametros para 1 e o NIF do utilizador, respetivamente
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_reserva NIF do utilizador que vai reservar o veiculo
//! @param code Codigo do veiculo a reservar
//! @return 
int Reservar_Veiculo(Veiculos* inicio,int NIF_reserva, int code) {
	Veiculos* current = inicio;


	for(current; current != NULL; current = current->proximo_veiculo){
		if (current->codigo == code && current->reserva == 0 && current->NIF_reserva == 0) {
			current->reserva = 1;
			current->NIF_reserva = NIF_reserva;
			return 1;
					
				}
				
			}

	return 0;
}

//! @brief Dado um codigo do veiculo, esta função percorre a lista e verifica se no parametro "NIF_reserva" o valor é o do NIF do utilizador, se sim ele cancela a reserva alterando os dados para 0
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_reserva NIF do utilizador que reservou o veiculo e deseja cancelar a reserva
//! @return 
int Cancelar_Reserva(Veiculos* inicio, int NIF_reserva) { 
	int code;
	
	printf("Qual o codigo do veiculo\n");
	scanf("%d", &code);
	Veiculos* current = inicio;
	for (current; current != NULL; current = current->proximo_veiculo) {
		if (current->reserva == 1 && current->codigo == code && current->NIF_reserva == NIF_reserva) {
			printf("%d %d %s %d %s\n", current->codigo, current->bateria, current->localizacao, current->custo, current->tipo);
			current->reserva = 0;
			current->NIF_reserva = 0;
			return 1;
		}
		
	
		
	}
	return 0;
}


//! @brief Função que limpa tudo o que está antes no terminal
void clear() { 

	system("@cls || clear");
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
//! @brief Esta função permite alterar os dados de um gestor, substituindo na lista ligada os novos dados nos parametros escolhidos pelo utilizador
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param email_procurado Email do gestor a alterar dados
void AlterarDadosGestores(Gestores* inicio, char email_procurado[]) {
	int opcao;
	char novoemail[50], novapassword[50];
	Gestores* current = inicio;


	printf("Que parametro deseja alterar?\n");
	scanf("%d", &opcao);

	if (opcao == 1) {
		scanf("%*c");
		printf("Digite o novo email\n");
		gets(novoemail);
		
			for (current; current != NULL; current = current->proximo_gestor) {
				if (strcmp(current->email, email_procurado) == 0) {
					strcpy(current->email, novoemail);
					GuardarGestores_Binario(inicio);

						
					
					
				}
			}
		
		
	}
	else if (opcao == 2) {
		scanf("%*c");
		printf("Digite a sua nova password\n");
		gets(novapassword);
		for (current; current != NULL; current = current->proximo_gestor) {
			if (strcmp(current->email, email_procurado) == 0) {
				strcpy(current->password, novapassword);
				GuardarGestores_Binario(inicio);
			}

		}
	}

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"



/**
 * This function inserts a new client into a linked list of clients.
 * 
 * @param inicio a pointer to the beginning of a linked list of clients
 * @param NIF_ The NIF (Número de Identificação Fiscal) is a unique identification number assigned to
 * individuals and companies in Portugal for tax purposes.
 * @param nome_ It is a character array that represents the name of the client being inserted.
 * @param idade_ The parameter "idade_" represents the age of the client being inserted into the linked
 * list.
 * @param morada_ The parameter "morada_" is a character array that represents the address of the
 * client.
 * @param saldo saldo refers to the amount of money a client has in their account.
 * @param localizacao The parameter "localizacao" is a string that represents the location of the
 * client, such as a city or a specific address.
 * @param nickname The parameter "nickname" is a character array that represents the chosen username or
 * nickname of the client.
 * @param password The parameter "password" is a string variable that stores the password of a client.
 * @param locaAtual The parameter "locaAtual" is a string that represents the current location of the
 * client.
 * 
 * @return a pointer to the beginning of the linked list of clients, which may be the newly created
 * node or the original beginning node if the memory allocation for the new node fails.
 */
Clientes* inserir_cliente(Clientes* inicio, int NIF_, char nome_[], int idade_,char morada_[], int saldo, char localizacao[], char nickname[], char password[], char locaAtual[]) { 
	
	
		Clientes* Novo = malloc(sizeof(struct registo_clientes));
		if (Novo != NULL) {
			Novo->NIF = NIF_;
			Novo->idade = idade_;
			Novo->saldo = saldo;
			strcpy(Novo->nome, nome_);
			strcpy(Novo->morada, morada_);
			strcpy(Novo->localizacao,localizacao);
			strcpy(Novo->nickname,nickname);
			strcpy(Novo->password,password);
			strcpy(Novo->localizacaoAtual, locaAtual);
			Novo->proximo_cliente = inicio;
			return Novo;
		}
		else {
			return inicio;
		}
} 

/**
 * The function prints the information of all clients in a linked list.
 * 
 * @param inicio The parameter "inicio" is a pointer to the first node of a linked list of clients.
 */
Clientes* imprimir_clientes(Clientes* inicio) { 

	while (inicio != NULL) {
		printf("%d %s %d %s %d %s %s\n",inicio->NIF, inicio->nome, inicio->idade, inicio->morada, inicio->saldo, inicio->localizacao, inicio->nickname, inicio->password);
		inicio = inicio->proximo_cliente;
	}
}


/**
 * The function removes a client from a linked list of clients based on their NIF code.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param code The code parameter is an integer that represents the NIF (Número de Identificação
 * Fiscal) of the client that needs to be removed from the linked list.
 * 
 * @return a pointer to the beginning of the linked list of clients after removing the client with the
 * specified code.
 */
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


/**
 * The function updates the balance of a client with a given NIF by adding a specified value.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param NIF_procurado The NIF (Número de Identificação Fiscal) of the client whose balance is being
 * updated.
 * @param valor The amount of money to be added to the client's balance.
 * 
 * @return an integer value, either 1 or 0. If the NIF_procurado (tax identification number) is found
 * in the linked list of clients (represented by the pointer "inicio"), the function updates the
 * client's saldo (balance) by adding the given "valor" (value) and returns 1. If the NIF_procurado is
 * not found, the function
 */
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


/**
 * The function checks if a client's login credentials match their stored information in a linked list.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param nickname a string representing the nickname of a client trying to log in
 * @param password The password input parameter is a character array (string) that represents the
 * password entered by the user trying to log in.
 * @param NIF NIF stands for "Número de Identificação Fiscal" which is a tax identification number used
 * in Portugal. It is similar to a social security number in the United States. In this function, it is
 * used as a parameter to identify a specific client when logging in.
 * 
 * @return an integer value, either 1 or 0. A value of 1 indicates that the login credentials
 * (nickname, password, and NIF) match those of a client in the linked list, while a value of 0
 * indicates that there is no match.
 */
int login_clientes(Clientes* inicio, char* nickname, char* password, int NIF) { 
	Clientes* current = inicio;
	for (current; current != NULL; current = current->proximo_cliente) {
		if (strcmp(current->nickname, nickname) == 0 && strcmp(current->password, password) == 0 && current->NIF == NIF) {
			return 1;
		}

	} return 0;
}


/**
 * The function sorts a linked list of clients by their NIF number in ascending order.
 * 
 * @param inicio a pointer to the first node of a linked list of clients.
 */
void ordenacao_clientes(Clientes* inicio) { 

	Clientes* pi = inicio;
	Clientes* pj = NULL;
	int aux, aux1,aux2;
	char loca[50], loca1[50], morada[50], nickname[50], nome[50], password[50];


	for (pi; pi != NULL; pi = pi->proximo_cliente) {
		for (pj = pi->proximo_cliente; pj != NULL; pj = pj->proximo_cliente) {
			if (pi->NIF > pj->NIF) {
				aux = pi->NIF;
				pi->NIF = pj->NIF;
				pj->NIF = aux;
				aux1 = pi->idade;
				pi->idade = pj->idade;
				pj->idade = aux1;
				aux2 = pi->saldo;
				pi->saldo = pj->saldo;
				pj->saldo = aux2;
				strcpy(loca,pi->localizacao);
				strcpy(pi->localizacao, pj->localizacao);
				strcpy(pj->localizacao, loca);
				strcpy(loca1, pi->localizacaoAtual);
				strcpy(pi->localizacaoAtual, pj->localizacaoAtual);
				strcpy(pj->localizacaoAtual, loca1);
				strcpy(morada,pi->morada);
				strcpy(pi->morada, pj->morada);
				strcpy(pj->morada, morada);
				strcpy(nickname,pi->nickname);
				strcpy(pi-> nickname, pj-> nickname);
				strcpy(pj-> nickname, nickname);
				strcpy(nome,pi->nome);
				strcpy(pi->nome, pj->nome);
				strcpy(pj->nome, nome);
				strcpy(password,pi->password);
				strcpy(pi->password, pj->password);
				strcpy(pj->password, password);
			}
		}
	}
}


/**
 * The function saves client information to a text file.
 * 
 * @param inicio a pointer to the first node of a linked list of Clients.
 */
void GuardarClientes(Clientes* inicio) 
{
	FILE* fp;
	fp = fopen("Clientes.txt", "w");
	if (fp != NULL)
	{
		Clientes* aux = inicio;
		for (aux; aux != NULL; aux = aux->proximo_cliente) {
			fprintf(fp, "%d;%s;%d;%s;%s;%s;%s;%d;%s\n", aux->NIF, aux->nome,aux->idade, aux->morada, aux->localizacao,aux->nickname, aux->password,aux->saldo, aux->localizacaoAtual);
		}
		fclose(fp);
		

	}
	
}

/**
 * The function reads client information from a file and creates a linked list of clients.
 * 
 * @return The function `LerClientes` returns a pointer to a `Clientes` struct, which is a linked list
 * of clients read from a file.
 */
Clientes* LerClientes() {
	FILE* fp;
	int NIF, idade, saldo;
	char nome[50], morada[50],localizacao[50], nickname[50], password[50], locaAtual[50];
	Clientes* aux = NULL;
	fp = fopen("Clientes.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%d;%[^;];%[^;];%[^;];%s;%d;%s\n", &NIF, nome, &idade, morada, localizacao,nickname,password,&saldo, locaAtual);
			aux = inserir_cliente(aux, NIF, nome, idade, morada, saldo,localizacao, nickname,password,locaAtual);
		}
		fclose(fp);
	}
	return(aux);
}

/**
 * The function saves a linked list of clients to a binary file.
 * 
 * @param inicio a pointer to the first node of a linked list of Clients.
 */
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


/**
 * This function reads client data from a binary file and returns a linked list of clients.
 * 
 * @return a pointer to a linked list of clients (Clientes).
 */
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
			aux = inserir_cliente(aux, current.NIF, current.nome, current.idade, current.morada, current.saldo, current.localizacao, current.nickname, current.password,current.localizacaoAtual);
		}
		fclose(fp);
	}
	return aux;

}


/**
 * The function checks if a given NIF exists in a linked list of clients.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param NIF NIF stands for "Número de Identificação Fiscal" which is a unique identification number
 * assigned to individuals and companies in Portugal. In this function, it is used as a parameter to
 * check if a client with the given NIF already exists in a linked list of clients.
 * 
 * @return an integer value. If the NIF (tax identification number) passed as a parameter is found in
 * the linked list of clients (represented by the pointer "inicio"), the function returns 1. Otherwise,
 * it returns 0.
 */
int verificar_registo_clientes(Clientes* inicio, int NIF) { 



	for (inicio; inicio != NULL; inicio = inicio->proximo_cliente) {
		if (inicio->NIF == NIF) {
			return 1;
		}
		
			
		
	}
	return 0;
}


/**
 * The function allows the user to alter their personal information such as nickname, password, and
 * address.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param NIF_procurado This parameter is an integer representing the NIF (Número de Identificação
 * Fiscal) of the client whose data needs to be altered.
 */
void AlterarDados(Clientes* inicio, int NIF_procurado) {

	int opcao;
	char novoNickname[50], nova_morada[50], novaPassword[50];
	Clientes* current = inicio;

	menu_definicoes();

	printf("Que parametro deseja alterar?\n");
	scanf("%d", &opcao);

	if (opcao == 1) {
		scanf("%*c");
		printf("Digite o novo nickname\n");
		gets(novoNickname);
		for (current; current != NULL; current = current->proximo_cliente) {
			if (NIF_procurado == current->NIF) {
				strcpy(current->nickname, novoNickname);
				clear();
				printf("Dados atualizados com sucesso\n");
			}
		
		}
	}
	else if (opcao == 2) {
		scanf("%*c");
		printf("Digite a sua nova password\n");
		gets(novaPassword);
		for (current; current != NULL; current = current->proximo_cliente) {
			if (NIF_procurado == current->NIF) {
				strcpy(current->password, novaPassword);
				clear();
			}
			
		}
	}else if(opcao == 3){
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

/**
 * The function "verlocaAtual" returns the current location of a client with a given NIF from a linked
 * list of clients.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param NIF NIF stands for "Número de Identificação Fiscal" which is a unique identification number
 * assigned to individuals and companies in Portugal. In this context, it is used as a parameter to
 * search for a specific client in a linked list of clients and return their current location.
 * 
 * @return a pointer to a character (char*) which represents the current location of a client with a
 * given NIF (tax identification number) in a linked list of clients.
 */
char* verlocaAtual(Clientes* inicio, int NIF){

	Clientes* aux = inicio;

	for(aux; aux != NULL; aux = aux->proximo_cliente){
		if(aux->NIF == NIF){
			return aux->localizacaoAtual;
		}
	}
	
}

/**
 * The function updates the location of a client with a given NIF in a linked list of clients.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param NIF The NIF (Número de Identificação Fiscal) is a unique identification number assigned to
 * individuals and companies in Portugal for tax purposes.
 * @param novoGeocode a string representing the new location code to be updated for a specific client
 * 
 * @return an integer value, either 1 or 0. The value 1 is returned if the function successfully
 * updates the address of a client with the given NIF, and 0 is returned if the client with the given
 * NIF is not found in the linked list.
 */
int atualizaMorada(Clientes* inicio, int NIF, char novoGeocode[]){

	Clientes* aux = inicio;

	for(aux; aux != NULL; aux = aux->proximo_cliente){
		if(aux->NIF == NIF){
			strcpy(aux->localizacaoAtual, novoGeocode);
			return 1;

		}

	}
	return 0;
	

}

/**
 * The function checks if a given nickname exists in a linked list of clients.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param nickname A character array representing the nickname to be verified.
 * 
 * @return an integer value. If the nickname is found in the linked list of clients, it returns 1.
 * Otherwise, it returns 0.
 */
int verificarNickname(Clientes* inicio, char nickname[]){
	Clientes* aux = inicio;

	for(aux; aux != NULL ; aux = aux->proximo_cliente){
		if(strcmp(aux->nickname, nickname) == 0){
			return 1;
		}
	}
	return 0;
}

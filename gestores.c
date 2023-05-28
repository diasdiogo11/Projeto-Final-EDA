#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"




 
/**
 * This function inserts a new node with email and password information into a linked list of managers.
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers)
 * @param email_ a string containing the email of the new manager being added to the linked list.
 * @param password_ A string variable that represents the password of a Gestor (manager) in a system.
 * 
 * @return a pointer to a struct of type Gestores. If memory allocation is successful, it returns a
 * pointer to the newly created struct with the email and password values copied into it, and the next
 * pointer pointing to the previous head of the linked list. If memory allocation fails, it returns the
 * original head of the linked list.
 */
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
 
/**
 * The function prints the email and password of each Gestor in a linked list.
 * 
 * @param inicio The parameter "inicio" is a pointer to the first node of a linked list of "Gestores"
 * (managers).
 */
Gestores* imprimir_gestores(Gestores* inicio) { 

	while (inicio != NULL) {
		printf("%s %s\n", inicio->email, inicio->password);
		inicio = inicio->proximo_gestor;
	}
}

/**
 * The function removes a node from a linked list of managers based on their email address.
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers)
 * @param email The email of the Gestor (manager) that needs to be removed from the linked list.
 * 
 * @return a pointer to the updated linked list of "Gestores" after removing the node with the
 * specified email address.
 */
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



/**
 * The function checks if a given username and password match those of a Gestor in a linked list.
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers)
 * @param username A string representing the email address of a Gestor (manager) trying to log in.
 * @param password The password that the user is trying to use to log in.
 * 
 * @return an integer value. If the username and password match with any of the gestores in the linked
 * list, it returns 1. Otherwise, it returns 0.
 */
int login_gestores(Gestores* inicio, char* username, char* password) {
	Gestores* current = inicio;
	for (current; current != NULL; current = current->proximo_gestor) {
		if (strcmp(current->email, username) == 0 && strcmp(current->password, password) == 0) {
			return 1;
		}


	}
	return 0;
}




/**
 * The function saves a linked list of Gestores structs into a binary file named "Gestores.bin".
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers).
 */
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
/**
 * The function saves a linked list of Gestores to a text file.
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers) containing their
 * email and password information.
 */
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

/**
 * This function reads binary data from a file and creates a linked list of Gestores structures.
 * 
 * @return The function `LerGestores_Binario()` returns a pointer to a linked list of `Gestores`
 * structures.
 */
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



/**
 * The function displays a menu with options for registering, logging in, or exiting.
 */
void menu_principal() { 
	int opcao;
	printf("*---------------- MENU PRINCIPAL ----------------*\n");
	printf("| 1.REGISTAR                                     |\n");
	printf("| 2.LOGIN                                        |\n");
	printf("| 0.EXIT                                         |\n");
	printf("*------------------------------------------------*\n");
	

}

/**
 * The function "cabecalho_registar" prints a header for a registration section.
 */
void cabecalho_registar() { 
	
	printf("*------------------------------------*\n");
	printf("|               REGISTO              |\n");
	printf("*------------------------------------*\n");


}

/**
 * The function displays a menu for selecting between administrator and client login options.
 */
void menu_login() { 


	
		printf("*--------------------------------------*\n");
		printf("| 1.ADMINISTRADOR                      |\n");
		printf("| 2.CLIENTE                            |\n");
		printf("*--------------------------------------*\n");
		
		
	
}

/**
 * The function displays a menu for managing clients, vehicles, reservations, and locations.
 */
void menu_gestores() { 

	
	printf("*---------------- MENU GESTORES ----------------*\n");
	printf("| 1.INSERIR CLIENTE                             |\n");
	printf("| 2.REMOVER CLIENTE                             |\n");
	printf("| 3.LISTAR CLIENTES                             |\n");
	printf("| 4.INSERIR VEICULO                             |\n");
	printf("| 5.REMOVER VEICULO                             |\n");
	printf("| 6.LISTAR VEICULOS                             |\n");
	printf("| 7.HISTORICO RESERVAS                          |\n");
	printf("| 8.GESTOR MASTER (ACESSO RESTRITO)             |\n");
	printf("| 9.ADICIONAR LOCALIZACAO                       |\n");
	printf("| 10.ADICIONAR LIGACACAO                        |\n");
	printf("| 0.EXIT                                        |\n");
	printf("*-----------------------------------------------*\n");
	
}

/**
 * The function displays a menu for managing gestors with options to add, remove, or alter their data.
 */
void menu_mastergestor() { 
	printf("*---------------- MENU GESTORES ----------------*\n");
	printf("| 1.ADICIONAR GESTOR                            |\n");
	printf("| 2.REMOVER GESTOR                              |\n");
	printf("| 3.ALTERAR DADOS GESTOR                        |\n");
	printf("| 0.VOLTAR                                      |\n");
	printf("*-----------------------------------------------*\n");



}

/**
 * The function displays a menu for managing clients in a car rental system.
 */
void menu_clientes() { 
	
	printf("*---------------- MENU CLIENTES ----------------*\n");
	printf("| 1.RESERVAR VEICULO                            |\n");
	printf("| 2.TERMINAR RESERVA                            |\n");
	printf("| 3.CARREGAR SALDO                              |\n");
	printf("| 4.DEFINICOES                                  |\n");
	printf("| 5.RESERVAS ATIVAS                             |\n");
	printf("| 0.EXIT                                        |\n");
	printf("*-----------------------------------------------*\n");
	
	
}

/**
 * The function "menu_definicoes" displays a menu with options to alter the user's nickname, password,
 * and address, or return to the main menu for clients.
 */
void menu_definicoes() { 

	
	printf("*---------------- DEFINICOES ----------------*\n");
	printf("| 1.ALTERAR NICKNAME                         |\n");
	printf("| 2.ALTERAR PASSWORD                         |\n");
	printf("| 3.ALTERAR MORADA                           |\n");
	printf("| 0.VOLTAR MENU CLIENTES                     |\n");
	printf("*--------------------------------------------*\n");

}

/**
 * The function prints a header for an administrator section.
 */
void cabecalho_admin() { 
	printf("*------------------------------------*\n");
	printf("|            ADMINISTRADOR           |\n");
	printf("*------------------------------------*\n");
}

/**
 * The function "cabecalho_cliente()" prints a header for the client section.
 */
void cabecalho_cliente() { 
	printf("*------------------------------------*\n");
	printf("|               CLIENTE              |\n");
	printf("*------------------------------------*\n");
}

/**
 * The function "menuReservas" displays a menu with two options for searching vehicles by location.
 */
void menuReservas(){
	printf("*---------------- DEFINICOES ----------------*\n");
	printf("| 1.Pesquisar Veiculos Por Localizacao        |\n");
	printf("| 2.Pesquisar Veiculos Num Raio               |\n");
	printf("*--------------------------------------------*\n");

}



/**
 * The function checks if a given email exists in a linked list of Gestores.
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers)
 * @param email A string representing the email address to be searched for in the linked list of
 * Gestores.
 * 
 * @return an integer value. It returns 1 if the email passed as a parameter is found in the linked
 * list of Gestores, and 0 if it is not found.
 */
int verificar_registo_gestores(Gestores* inicio, char email[]) { 



	for (inicio; inicio != NULL; inicio = inicio->proximo_gestor) {
		if (strcmp(inicio->email, email) == 0) {
			return 1;
		}



	}
	return 0;
}






/**
 * The function clears the console screen in C programming language.
 */
void clear() { 

	system("@cls || clear");
}


/**
 * The function allows for the alteration of email and password parameters for a specific Gestor in a
 * linked list.
 * 
 * @param inicio a pointer to the first node of a linked list of Gestores (managers)
 * @param email_procurado a string representing the email address of the Gestor (manager) whose data
 * needs to be altered.
 */
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






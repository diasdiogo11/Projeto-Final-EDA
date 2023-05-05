#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"




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





//! @brief Função que limpa tudo o que está antes no terminal
void clear() { 

	system("@cls || clear");
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






#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"


/**
 * This function inserts a new vehicle into a linked list of vehicles.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param codigo_ an integer representing the code of the vehicle being inserted
 * @param bateria_ an integer representing the battery level of the vehicle
 * @param localizacao_ a string that represents the location of the vehicle
 * @param custo_ The parameter "custo_" represents the cost of renting the vehicle.
 * @param tipo_ The parameter "tipo_" is a character array that represents the type of the vehicle
 * being inserted.
 * @param reserva_ The parameter "reserva_" is an integer that represents whether the vehicle is
 * currently reserved or not. If the value is 1, it means the vehicle is reserved, and if the value is
 * 0, it means the vehicle is available for rent.
 * @param NIF_reserva_ NIF_reserva_ is an integer variable that represents the NIF (Número de
 * Identificação Fiscal) of the person who made the reservation for the vehicle.
 * @param horario_reserva The parameter "horario_reserva" is a variable of type "time_t" that
 * represents the date and time when a vehicle is reserved.
 * 
 * @return a pointer to the beginning of the linked list of Veiculos. If a new node was successfully
 * created and added to the list, the function returns a pointer to the new node. If the allocation of
 * memory for the new node failed, the function returns the original pointer to the beginning of the
 * list.
 */
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


/**
 * The function prints the information of all vehicles in a linked list.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles) structure.
 */
Veiculos* imprimir_veiculos(Veiculos* inicio) { 
	while (inicio != NULL) {
		
		printf("%d %d %s %d %s\n", inicio->codigo, inicio->bateria, inicio->localizacao, inicio->custo, inicio->tipo);
		inicio = inicio->proximo_veiculo;
	}
}

/**
 * The function removes a vehicle from a linked list of vehicles based on its code.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param code an integer representing the code of the vehicle to be removed from the linked list of
 * vehicles.
 * 
 * @return a pointer to the beginning of the linked list of vehicles after removing the vehicle with
 * the specified code.
 */
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


/**
 * This function sorts a linked list of vehicles by battery level, and if two vehicles have the same
 * battery level, it sorts them by their code, cost, location, and type.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles) structures.
 */
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


/**
 * The function saves information about vehicles to a file named "Veiculos.txt".
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles) structures.
 */
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
 
/**
 * The function reads vehicle information from a file and returns a linked list of vehicles.
 * 
 * @return The function `LerVeiculos` returns a pointer to a linked list of `Veiculos` structures.
 */
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


/**
 * This function saves a linked list of vehicles to a binary file.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles) structures.
 */
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

 
/**
 * This function reads binary data from a file and creates a linked list of Veiculos structures.
 * 
 * @return a pointer to a linked list of Veiculos (vehicles) that were read from a binary file.
 */
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

/**
 * The function checks if a given vehicle code exists in a linked list of vehicles.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param codigo The parameter "codigo" is an integer variable representing the code of a vehicle that
 * needs to be checked for existence in a linked list of vehicles.
 * 
 * @return an integer value. If the given "codigo" is found in the linked list of "Veiculos" pointed by
 * "inicio", the function returns 1. Otherwise, it returns 0.
 */
int verificar_registo_veiculos(Veiculos* inicio, int codigo){ 



	for (inicio; inicio != NULL; inicio = inicio->proximo_veiculo) {
		if (inicio->codigo == codigo){
			return 1;
		}



	}
	return 0;
}


/**
 * The function "LocalizarVeiculos" searches for available vehicles with a specific location and prints
 * their information.
 * 
 * @param inicio a pointer to the first node of a linked list of vehicles
 * @param localizacao_pretendida It is a string variable that represents the desired location to search
 * for vehicles. The function searches for vehicles in the linked list that have the same location as
 * the one provided in this parameter.
 */
Veiculos* LocalizarVeiculos(Veiculos* inicio, char localizacao_pretendida[]) {

	
		for(inicio; inicio != NULL; inicio = inicio->proximo_veiculo){
			if ((strcmp(inicio->localizacao, localizacao_pretendida) == 0) && inicio->reserva == 0 && inicio->NIF_reserva == 0) {
				printf("%d %d %s %d %s\n", inicio->codigo, inicio->bateria, inicio->localizacao, inicio->custo, inicio->tipo);
				
			
		}
	

}
}

/**
 * The function "verLocalizacao" returns the location of a vehicle with a given code from a linked list
 * of vehicles.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param code an integer representing the code of the vehicle whose location is to be retrieved.
 * 
 * @return a pointer to a character array (string) that represents the location of a vehicle with the
 * given code. If the vehicle is not found, it returns a null pointer (0).
 */
char* verLocalizacao(Veiculos* inicio, int code){
	Veiculos* aux= inicio;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		if(aux->codigo == code){
			return aux->localizacao;
		}
	}
	return 0;
}

/**
 * The function "gerarCode" returns the number of nodes in a linked list of vehicles.
 * 
 * @param inicio The parameter "inicio" is a pointer to the first node of a linked list of "Veiculos"
 * (vehicles) data type.
 * 
 * @return The function `gerarCode` is returning an integer value, which is the count of the number of
 * nodes in the linked list of `Veiculos`. This count represents the code that will be assigned to the
 * next `Veiculo` added to the list.
 */
int gerarCode(Veiculos* inicio){

	Veiculos* aux = inicio;
	int count = 1;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		count++;
		
	}
	return count;
}


/**
 * The function "retiraBateria" removes a certain amount of battery from a vehicle based on the
 * reservation time and updates its battery level.
 * 
 * @param inicio a pointer to the first node of a linked list of vehicles
 * @param tempoReserva The amount of time the vehicle is reserved for, in hours.
 * @param code an integer representing the code of the vehicle whose battery needs to be removed.
 * 
 * @return the updated value of the battery of the vehicle with the given code after removing the
 * amount of battery used during the given reservation time.
 */
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

/**
 * The function "verTipo" returns the type of a vehicle based on its code.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param code an integer representing the code of a vehicle
 * 
 * @return a pointer to a character (char*) which represents the type of a vehicle with a given code.
 */
char* verTipo(Veiculos* inicio, int code){

	Veiculos* aux = inicio;

	for(aux; aux != NULL; aux = aux->proximo_veiculo){
		if(aux->codigo == code){
			return aux->tipo;
		}
	}
}


/**
 * The function updates the location of a vehicle with a given code in a linked list of vehicles.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param code an integer representing the code of the vehicle whose location needs to be updated
 * @param novaLocalizacao a string representing the new location to be updated for a vehicle
 * 
 * @return an integer value. It returns 1 if it successfully updates the location of the vehicle with
 * the given code, and returns 0 if it fails to find the vehicle with the given code.
 */
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



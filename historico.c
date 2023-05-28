#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"

/**
 * The function inserts a new element into a linked list of historical records.
 * 
 * @param inicio a pointer to the beginning of a linked list of historical records
 * @param idc an integer representing the ID of the client who made the reservation
 * @param idm idm stands for "idMeio" which is the identifier for a means of transportation (e.g. bike,
 * scooter, car) in a rental system.
 * @param custof The cost of the rental, including any additional fees or charges.
 * @param tempoReserva The amount of time the vehicle was reserved for.
 * @param bateria The parameter "bateria" represents the battery level of a vehicle in a car-sharing
 * system.
 * @param tipo tipo is a character array that represents the type of vehicle used in the rental. It
 * could be a car, bike, scooter, or any other type of vehicle.
 * 
 * @return a pointer to a struct of type Historico.
 */
Historico* inserirHis(Historico* inicio, int idc, int idm, double custof, double tempoReserva, int bateria, char tipo[]) { 
	

		Historico* Novo = malloc(sizeof(struct historico));
		if (Novo != NULL) {
			Novo->idCliente = idc;
			Novo->idMeio = idm;
			Novo->custoFinal = custof;
			Novo->tempoReserva = tempoReserva;
			Novo->bateria = bateria;
			Novo->proximoHis = inicio;
			strcpy(Novo->tipo, tipo);
			return Novo;
		}
		else {
			return inicio;
		}
} 

 

/**
 * This function saves the historical data of a system into a text file.
 * 
 * @param inicio a pointer to the first node of a linked list of type Historico, representing a history
 * of reservations.
 */
void GuardarHistorico(Historico* inicio) 
{
	FILE* fp;
	fp = fopen("Historico.txt", "w");
	if (fp != NULL)
	{
		Historico* hist = inicio;
		for (hist; hist != NULL; hist = hist->proximoHis) {
			fprintf(fp,"%d %d %.2f %.2f %d %s\n",hist->idCliente, hist->idMeio, hist->custoFinal, hist->tempoReserva, hist->bateria, hist->tipo);
		}
		fclose(fp);
		

	}
	
}

/**
 * The function reads data from a file and creates a linked list of historical records.
 * 
 * @return The function `LerHistorico()` returns a pointer to a `Historico` struct.
 */
Historico* LerHistorico() {
	FILE* fp;
	int idc, idm, bateria;
	double custof, tempoReserva;
	char tipo[50];
	Historico* aux = NULL;
	fp = fopen("Historico.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d %d %lf %lf %d %s\n", &idc, &idm, &custof, &tempoReserva, &bateria, tipo);
			    aux = inserirHis(aux,idc, idm, custof, tempoReserva, bateria, tipo);
		}
		fclose(fp);
	}
	return(aux);
}

/**
 * The function "imprimirHistorico" prints out a table of historical data for a given linked list of
 * "Historico" structs.
 * 
 * @param inicio a pointer to the first node of a linked list of type Historico, representing the
 * beginning of the historical records.
 */
void imprimirHistorico(Historico* inicio){

	Historico* aux = inicio;


	for(aux; aux != NULL; aux = aux->proximoHis){
		printf("  %d                  %d                      %.2f MIN                 %.2f EUROS                  %d %%                      %s\n",aux->idCliente, aux->idMeio,aux->tempoReserva,aux->custoFinal, aux->bateria, aux->tipo);
	}
}

/**
 * This function prints the rental history of a specific client.
 * 
 * @param inicio a pointer to the first node of a linked list of historical records
 * @param NIF NIF stands for "Número de Identificação Fiscal" which is a unique identification number
 * assigned to individuals and companies in Portugal for tax purposes. In this function, NIF is used as
 * a parameter to filter and print the historical data of a specific client based on their NIF.
 */
void imprimirHistoricoCliente(Historico* inicio,int NIF){

	Historico* aux = inicio;

			for(aux; aux != NULL; aux = aux->proximoHis){
				if(aux->idCliente == NIF){
					printf("  %d                  %d                      %.2f MIN                 %.2f EUROS                  %d %%                      %s\n",aux->idCliente, aux->idMeio,aux->tempoReserva,aux->custoFinal, aux->bateria, aux->tipo);
				}
			
	}
	
}

/**
 * The function calculates the total revenue from a linked list of historical data.
 * 
 * @param inicio a pointer to the first node of a linked list of type Historico, representing a history
 * of transactions.
 * 
 * @return a double value, which represents the total revenue calculated from the historical data
 * stored in the linked list.
 */
int estatisticas(Historico* inicio){

	Historico* aux = inicio;
	double receitaTotal;

	for(aux; aux != NULL; aux = aux->proximoHis){
		receitaTotal = receitaTotal + aux->custoFinal;
	}

	return receitaTotal;

}





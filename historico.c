#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"

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

void imprimirHistorico(Historico* inicio){

	Historico* aux = inicio;


	for(aux; aux != NULL; aux = aux->proximoHis){
		printf("NIF CLIENTE -> %d\nCODIGO VEICULO -> %d\nTIPO -> %s\nTEMPO DE RESERVA -> %.2f MINUTOS\nCUSTO FINAL -> %.2f EUROS\nBATERIA FINAL -> %d\n",aux->idCliente, aux->idMeio,aux->tipo,aux->tempoReserva,aux->custoFinal, aux->bateria);
		printf("\n");
	}
}

int estatisticas(Historico* inicio){

	Historico* aux = inicio;
	double receitaTotal;

	for(aux; aux != NULL; aux = aux->proximoHis){
		receitaTotal = receitaTotal + aux->custoFinal;
	}

	return receitaTotal;

}



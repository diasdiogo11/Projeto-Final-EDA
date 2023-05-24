#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"

Historico* inserirHis(Historico* inicio, int idc, int idm, double custof, double tempoReserva, double bateria) { 
	

		Historico* Novo = malloc(sizeof(struct historico));
		if (Novo != NULL) {
			Novo->idCliente = idc;
			Novo->idMeio = idm;
			Novo->custoFinal = custof;
			Novo->tempoReserva = tempoReserva;
			Novo->bateria = bateria;
			Novo->proximoHis = inicio;
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
			fprintf(fp,"%d %d %.2f %.2f %.2f\n",hist->idCliente, hist->idMeio, hist->custoFinal, hist->tempoReserva, hist->bateria);
		}
		fclose(fp);
		

	}
	
}

Historico* LerHistorico() {
	FILE* fp;
	int idc, idm;
	double custof, tempoReserva,bateria;
	Historico* aux = NULL;
	fp = fopen("Historico.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d %d %lf %lf\n", &idc, &idm, &custof, &tempoReserva, &bateria);
			    aux = inserirHis(aux,idc, idm, custof, tempoReserva, bateria);
		}
		fclose(fp);
	}
	return(aux);
}

void imprimirHistorico(Historico* inicio){

	Historico* aux = inicio;

	for(aux; aux != NULL; aux = aux->proximoHis){
		printf("NIF CLIENTE -> %d\nCODIGO VEICULO -> %d\nTEMPO DE RESERVA -> %.2f MINUTOS\nCUSTO FINAL -> %.2f EUROS\nBATERIA FINAL -> %.2f",aux->idCliente, aux->idMeio, aux->tempoReserva,aux->custoFinal, aux->bateria);
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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"

Historico* inserirHis(Historico* inicio, int idc, int idm, double custof,struct tm start, struct tm end) { 
	

		Historico* Novo = malloc(sizeof(struct historico));
		if (Novo != NULL) {
			Novo->idCliente = idc;
			Novo->idMeio = idm;
			Novo->custoFinal = custof;
            Novo->inicio = start;
            Novo->fim = end;
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
			fprintf(fp,"%d %d %.2f %02d/%02d/%02d %02d/%02d/%02d\n",hist->idCliente, hist->idMeio, hist->custoFinal,
                hist->inicio.tm_year+1900, hist->inicio.tm_mon+1, hist->inicio.tm_mday,
                hist->fim.tm_year+1900, hist->fim.tm_mon+1, hist->fim.tm_mday);
		}
		fclose(fp);
		

	}
	
}

Historico* LerHistorico() {
	FILE* fp;
	int idc, idm;
	double custof;
	struct tm start, end;
	Historico* aux = NULL;
	fp = fopen("Historico.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d %d %lf %d/%d/%d %d/%d/%d\n", &idc, &idm, &custof, 
                &start.tm_year, &start.tm_mon, &start.tm_mday,
                &end.tm_year, &end.tm_mon, &end.tm_mday);
                start.tm_year -= 1900;
                end.tm_year -= 1900;
                start.tm_mon -= 1;
                end.tm_mon -= 1;
			    aux = inserirHis(aux,idc, idm, custof, start, end);
		}
		fclose(fp);
	}
	return(aux);
}


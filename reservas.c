#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"

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

int PrecoFinal(Clientes* inicio, int NIF_procurado, int valor){ 


	Clientes* currentt = inicio;

	
	for (currentt; currentt != NULL; currentt = currentt->proximo_cliente) {
		if (NIF_procurado == currentt->NIF) {
			currentt->saldo = currentt->saldo - valor;
			return 1;
		}
	
}
	return 0;

}

//! @brief Esta função foi feita para a reserva de veiculos, a função percorre a lista ligada veiculos e verifica se nos parametros "reserva" e "NIF_reserva" os valores estão a zero, se sim, permite ao utilizador reservar esse veiculos, alterando esses parametros para 1 e o NIF do utilizador, respetivamente
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_reserva NIF do utilizador que vai reservar o veiculo
//! @param code Codigo do veiculo a reservar
//! @return 
int Reservar_Veiculo(Veiculos* inicio,int NIF_reserva, int code) { 
    Veiculos* current = inicio;
    for (current; current != NULL; current = current->proximo_veiculo) {
            if (current->codigo == code && current->reserva == 0 && current->NIF_reserva == 0) {
            current->reserva = 1;
            current->NIF_reserva = NIF_reserva;
            current->horario_reserva = time(NULL);
            return 1;
        }
        
    }
    return 0;   
}


//! @brief Dado um codigo do veiculo, esta função percorre a lista e verifica se no parametro "NIF_reserva" o valor é o do NIF do utilizador, se sim ele cancela a reserva alterando os dados para 0
//! @param inicio Apontador para a variavel que guarda a cabeça da lista ligada dos Veiculos
//! @param inicioo Apontador para a variavel que guarda a cabeça da lista ligada dos Clientes
//! @param NIF_reserva NIF do utilizador que reservou o veiculo e deseja cancelar a reserva
//! @return 
int Cancelar_Reserva(Veiculos* inicio, Historico* inicio1, Clientes* inicio2, int NIF_reserva, int code) { 
    Veiculos* current = inicio;
    for (current; current != NULL; current = current->proximo_veiculo) {
        if (current->reserva == 1 && current->codigo == code && current->NIF_reserva == NIF_reserva) {
            time_t horario_atual = time(NULL);
            double tempo_decorrido = difftime(horario_atual, current->horario_reserva);
			double tempo_decorrido_minutos = tempo_decorrido / 60;
			double CustoFinal = tempo_decorrido_minutos * current->custo;
			int bateriaFinal = retiraBateria(inicio, tempo_decorrido_minutos, code);
			inicio1 = inserirHis(inicio1, NIF_reserva, code,CustoFinal,tempo_decorrido_minutos,bateriaFinal);
			GuardarHistorico(inicio1);
            printf("Tempo decorrido: %.2f segundos ou %.2f minutos\n", tempo_decorrido, tempo_decorrido_minutos);
            if(PrecoFinal(inicio2, current->NIF_reserva, CustoFinal)){
                printf("Deu certo cara\n");
            }
            current->reserva = 0;
            current->NIF_reserva = 0;
			current->horario_reserva = 0;
            return 1;
        }
    }
    return 0;
}

int VerificarNumReservas(Veiculos* inicio, int NIF){
	int count=1;

	Veiculos* current = inicio;

	for(current; current != NULL; current = current->proximo_veiculo){
		if(current->NIF_reserva == NIF){
			count++;
		}
	}


	if(count <= 1){
		return 2;
	}else{
		return 0;
	}



}

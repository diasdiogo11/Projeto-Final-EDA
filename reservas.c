#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"
 
/**
 * The function checks if a given NIF has any reservations in a linked list of vehicles.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param NIF NIF stands for "Número de Identificação Fiscal" which is a unique identification number
 * assigned to individuals and companies in Portugal for tax purposes. In this function, it is used as
 * a parameter to search for reservations made by a specific individual or company.
 * 
 * @return an integer value. If there is at least one vehicle reserved by the NIF provided as an
 * argument, the function returns 1. Otherwise, it returns 0.
 */
int imprimir_reservas(Veiculos* inicio, int NIF) { 

	Veiculos* current = inicio;

	for(current; current != NULL; current= current->proximo_veiculo) {
		if (current->NIF_reserva == NIF) {
			return 1;
		}
	}
	return 0;
}

/**
 * The function updates the balance of a client with a given NIF by subtracting a given value.
 * 
 * @param inicio a pointer to the first node of a linked list of clients
 * @param NIF_procurado The NIF (Número de Identificação Fiscal) of the client whose balance needs to
 * be updated. It is used to search for the client in the linked list of clients.
 * @param valor The value of the purchase made by the customer.
 * 
 * @return an integer value, either 1 or 0. If the NIF_procurado (tax identification number) is found
 * in the linked list of clients (represented by the pointer "inicio"), the function subtracts the
 * "valor" (value) from the client's "saldo" (balance) and returns 1. If the NIF_procurado is not found
 * in the
 */
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


/**
 * This function reserves a vehicle by setting its reservation status, NIF, and reservation time if it
 * meets certain conditions.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param NIF_reserva The NIF (Número de Identificação Fiscal) is a unique identification number
 * assigned to individuals and companies in Portugal. In this context, it is likely being used as a way
 * to identify the person who is reserving the vehicle.
 * @param code The code parameter is an integer that represents the unique code of the vehicle that the
 * user wants to reserve.
 * 
 * @return an integer value, either 1 or 0. The value 1 is returned if a vehicle with the given code is
 * found and is available for reservation (not already reserved, not out of battery), and the
 * reservation is successfully made. The value 0 is returned if no suitable vehicle is found or if the
 * reservation cannot be made for some reason.
 */
int Reservar_Veiculo(Veiculos* inicio,int NIF_reserva, int code) { 
    Veiculos* current = inicio;
    for (current; current != NULL; current = current->proximo_veiculo) {
            if (current->codigo == code && current->reserva == 0 && current->NIF_reserva == 0 && current->bateria > 0) {
            current->reserva = 1;
            current->NIF_reserva = NIF_reserva;
            current->horario_reserva = time(NULL);
            return 1;
        }
        
    }
    return 0;   
}


 
/**
 * The function cancels a reservation made by a client for a specific vehicle and calculates the final
 * cost based on the time elapsed and the vehicle's rental cost.
 * 
 * @param inicio a pointer to the beginning of a linked list of vehicles
 * @param inicio1 The pointer to the start of the linked list of historical records.
 * @param inicio2 The parameter "inicio2" is a pointer to the start of a linked list of type
 * "Clientes", which contains information about the clients who have made reservations for the
 * vehicles.
 * @param NIF_reserva The NIF (Número de Identificação Fiscal) of the client who made the reservation.
 * @param code The code parameter is an integer that represents the unique code of the vehicle that the
 * reservation is associated with.
 * 
 * @return an integer value, either 1 or 0.
 */
int Cancelar_Reserva(Veiculos* inicio, Historico* inicio1, Clientes* inicio2, int NIF_reserva, int code) { 
    Veiculos* current = inicio;
    for (current; current != NULL; current = current->proximo_veiculo) {
        if (current->reserva == 1 && current->codigo == code && current->NIF_reserva == NIF_reserva) {
            time_t horario_atual = time(NULL);
            double tempo_decorrido = difftime(horario_atual, current->horario_reserva);
			double tempo_decorrido_minutos = tempo_decorrido / 60;
			double CustoFinal = tempo_decorrido_minutos * current->custo;
			int bateriaFinal = retiraBateria(inicio, tempo_decorrido_minutos, code);
			char* tipo = verTipo(inicio, code);
			inicio1 = inserirHis(inicio1, NIF_reserva, code,CustoFinal,tempo_decorrido_minutos,bateriaFinal, tipo);
			GuardarHistorico(inicio1);
            printf("Tempo decorrido: %.2f segundos ou %.2f minutos\n", tempo_decorrido, tempo_decorrido_minutos);
            if(PrecoFinal(inicio2, current->NIF_reserva, CustoFinal)){
            }
            current->reserva = 0;
            current->NIF_reserva = 0;
			current->horario_reserva = 0;
            return 1;
        }
    }
    return 0;
}

/**
 * The function checks the number of reservations made by a specific NIF and returns a value based on
 * the count.
 * 
 * @param inicio a pointer to the first node of a linked list of Veiculos (vehicles)
 * @param NIF The NIF (Número de Identificação Fiscal) is a unique identification number assigned to
 * individuals and companies in Portugal. In this function, it is used to check how many reservations a
 * specific person (identified by their NIF) has made for vehicles.
 * 
 * @return an integer value. If the count of reservations made by a certain NIF is less than or equal
 * to 1, the function returns 2. Otherwise, it returns 0.
 */
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

int imprimirReservasAtivas(Veiculos* inicio, int NIF){

	Veiculos* current = inicio;

	for(current; current != NULL; current = current->proximo_veiculo) {
		if (current->NIF_reserva == NIF && current->reserva == 1) {
			printf("%d %d %s %d %s\n", current->codigo, current->bateria, current->localizacao, current->custo, current->tipo);
			return 1;
		}
	}
	return 0;
}


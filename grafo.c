#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"

Vertice* adicionarVertice(Vertice* listaVertices, int novoVertice, char geocode[]) {
    Vertice* novo = (Vertice*) malloc(sizeof(Vertice));

    if(novo != NULL){
        novo->vertice = novoVertice;
        strcpy(novo->geocode, geocode);
        novo->adj = NULL;
        novo->proximoVert = listaVertices;
    
    return novo;

    }else{
        return listaVertices;
    }
    
}

int adicionarAresta(Vertice *v, int inicio, int fim, float peso){

    if (v == NULL)
        return 0;

    if ((existeVertice(v, inicio) != 1) || (existeVertice(v, fim) != 1))
        return 0;

    while(v->vertice != inicio){
        v = v->proximoVert;
    }
    
    Adjacente *new = (Adjacente*)malloc(sizeof(Adjacente));
    new->peso = peso;
    new->vertice = fim;
    new->proximoAdja = NULL;
    
    if(v->adj != NULL){
        Adjacente *aux = v->adj;    
        while(aux->proximoAdja != NULL){
            aux = aux->proximoAdja;
        }
        aux->proximoAdja = new;
    }else
        v->adj = new;

    return 1;
}






int existeVertice(Vertice* inicio, int idvertice){

    for(inicio; inicio != NULL; inicio = inicio->proximoVert){
        if (inicio->vertice == idvertice){
            return 1;
        }
    }
    return 0;
   
}

void listarAdjacentes(Vertice *v, int idvertice){


    while(v != NULL && v->vertice != idvertice){
        v = v->proximoVert;
    }

    if(v != NULL){

        printf("Adjacentes de %d: ", idvertice);

        Adjacente *aux = v->adj;

        while(aux != NULL){
            printf("\n%d Peso: %d\n", aux->vertice, aux->peso);
            aux = aux->proximoAdja;
        }

        printf("\n");

    }else{
        printf("Vertice nao encontrado!\n");
    }

}


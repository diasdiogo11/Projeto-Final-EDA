#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"
#include "help.h"
#include <limits.h>

#define INFINITO INT_MAX

Vertice* adicionarVertice(Vertice* listaVertices, int novoVertice, char geocode[], char local[]) {
    Vertice* novo = (Vertice*) malloc(sizeof(Vertice));

    if(novo != NULL){
        novo->vertice = novoVertice;
        strcpy(novo->geocode, geocode);
        strcpy(novo->local, local);
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


int corresponderLocalizacaoaID(Vertice* inicio, char localizacao[]){
    Vertice* aux = inicio;
    
    for(aux; aux != NULL; aux = aux->proximoVert){
        if(strcmp(aux->local, localizacao) == 0){
            return aux->vertice;
        }
    }
}

char* corresponderIDaLocalizacao(Vertice* inicio, int id){
    Vertice* aux = inicio;

    
    for(aux; aux != NULL; aux = aux->proximoVert){
        if(aux->vertice == id){
           return aux->local;
        }
    }
    
}



void guardarVertices(Vertice* v){
    FILE* fp;
    Vertice *head = v;
    Adjacente *aux;
    fp = fopen("Vertices.txt","w");

    if (fp!=NULL){      

        while(v != NULL){  
            fprintf(fp,"%d;%s;%s;\n", v->vertice, v->geocode,v->local);
            v = v->proximoVert;
        }
        fclose(fp);

}
}


void guardarArestas(Vertice* v){
    FILE* fp;
    Vertice* head = v;
    Adjacente* aux;
    fp = fopen("Arestas.txt", "w");


    for(v = head; v != NULL ;v = v->proximoVert){
            fprintf(fp,"%d;",v->vertice);
            for(aux = v->adj; aux != NULL; aux = aux->proximoAdja){
                fprintf(fp,"%d;%.2f;",aux->vertice, aux->peso);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
    
}

int numVertices(Vertice  *v){
    int i = 1;

    if (v == NULL)
        return i;
    
    while(v != NULL){
        i++;
        v = v->proximoVert;
    }

    return i;
}

int visitado(int sequencia[],int pos, int id){
  int i;
  for(i=0;i<pos;i++) {
    if (sequencia[i]==id){
        return(1);
    } 
  }
  return(0);
}

void listarCaminhosAux(Vertice *v, int origem, int destino, int sequencia[], int posicao, int pesoTotal){
    int i;
    Vertice *head = v;
    Adjacente *aux;  \
    sequencia[posicao] = origem;
    if (origem==destino) {
        for(i=0;i<posicao;i++) printf("%d->",sequencia[i]);
        printf("%d (%d)\n",destino,pesoTotal);
    }
    else {
        while(v->vertice != origem && v != NULL)
            v = v->proximoVert;
        aux = v->adj; 
        while (aux != NULL){
        if (!visitado(sequencia,posicao,aux->vertice)) 
            listarCaminhosAux(head,aux->vertice,destino,sequencia,posicao+1,
            pesoTotal+aux->peso);

        aux = aux->proximoAdja;
    }
    }
}

void listarCaminhos(Vertice *v, int origem, int destino){
  int sequencia[numVertices(v)];
  listarCaminhosAux(v,origem,destino,sequencia,0,0);


}


void listarCaminhosAuxLimite(Veiculos* vi, Vertice* v, int origem, int destino, int sequencia[], int posicao, int pesoTotal, int limite, char tipo[]) {
    int i;
    Vertice* head = v;
    Veiculos* teste1 = vi;
    Adjacente* aux;
    sequencia[posicao] = origem;

    if (origem == destino) {
        if (pesoTotal <= limite) {
            for (i = 0; i < posicao; i++) {
                char* localizacao = corresponderIDaLocalizacao(head, sequencia[i]);
                printf("%s->", localizacao);
            }
            char* destinoNome = corresponderIDaLocalizacao(head, destino);
            printf("%s %d METROS\n", destinoNome, pesoTotal);
            teste(vi, destinoNome, tipo);
        }
    } else {
        while (v->vertice != origem && v != NULL) {
            v = v->proximoVert;
        }
        aux = v->adj;
        while (aux != NULL) {
            if (!visitado(sequencia, posicao, aux->vertice)) {
                listarCaminhosAuxLimite(teste1, head, aux->vertice, destino, sequencia, posicao + 1, pesoTotal + aux->peso, limite, tipo);
            }
            aux = aux->proximoAdja;
        }
    }
}

void listarCaminhosLimite(Veiculos* vi, Vertice* v, int origem, int destino, int limite, char tipo[]) {
    int sequencia[numVertices(v)];
    listarCaminhosAuxLimite(vi, v, origem, destino, sequencia, 0, 0, limite, tipo);
}

void teste(Veiculos* i, char loca[], char tipo[]) {
    int encontrado = 0;

    while (i != NULL) {
        if (strcmp(i->localizacao, loca) == 0 && strcmp(i->tipo, tipo) == 0) {
            encontrado = 1;
            break;
        }
        i = i->proximo_veiculo;
    }

    if (encontrado) {
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        printf(" CODIGO                      BATERIA                     LOCALIZACAO                     CUSTO P/MIN                 TIPO        \n");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        for (i; i != NULL; i = i->proximo_veiculo) {
            if (strcmp(i->localizacao, loca) == 0 && strcmp(i->tipo, tipo) == 0) {
                printf("   %d                          %d %%                   %s                     %d                   %s\n", i->codigo,i->bateria, i->localizacao, i->custo, i->tipo);
            }
        }
    } else {
        printf("Localizacao dentro do raio pretendido, porem, nao existe nenhum/a %s em %s\n", tipo, loca);
    }

    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
}

int obterMenorDistancia(int distancias[], int visitado[], int numVertices) {
    int min = INFINITO;
    int indiceMin = -1;

    for (int i = 0; i < numVertices; i++) {
        if (visitado[i] == 0 && distancias[i] <= min) {
            min = distancias[i];
            indiceMin = i;
        }
    }

    return indiceMin;
}

void imprimirCaminho(Vertice* listaVertices, int caminho[], int verticeAtual) {
    char* locaAtual = corresponderIDaLocalizacao(listaVertices, verticeAtual);
    if (caminho[verticeAtual] == -1) {
        printf("%d(%s) -> ", verticeAtual, locaAtual);
        return;
    }

    imprimirCaminho(listaVertices,caminho, caminho[verticeAtual]);
    printf("%d(%s) -> ", verticeAtual, locaAtual);
}

void imprimirCaminhoMaisCurto(Vertice* listaVertices,int caminho[], int distancias[], int inicio, int fim) {
    char* verticeInicio = corresponderIDaLocalizacao(listaVertices, inicio);
    char* verticeFim = corresponderIDaLocalizacao(listaVertices, fim);
    printf("Caminho mais curto entre %d(%s) e %d(%s):\n", inicio,verticeInicio,fim,verticeFim);
    imprimirCaminho(listaVertices,caminho, fim);
    printf("\nDistancia total: %d METROS\n", distancias[fim]);
}

void encontrarCaminhoMaisCurto(Vertice* listaVertices, Veiculos* teste15, int numVertices, int inicio, int fim, int limite, char tipo[]) {
    int distancias[numVertices];
    int visitado[numVertices];
    int caminho[numVertices];

   if ((existeVertice(listaVertices, inicio) != 1) || (existeVertice(listaVertices, fim) != 1)){
        printf("Vertice nao encontrado\n");

    }
    for (int i = 0; i < numVertices; i++) {
        distancias[i] = INFINITO;
        visitado[i] = 0;
        caminho[i] = -1;
    }

    distancias[inicio] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int verticeAtual = obterMenorDistancia(distancias, visitado, numVertices);
        visitado[verticeAtual] = 1;

        Vertice* v = listaVertices;
        while (v != NULL) {
            if (v->vertice == verticeAtual) {
                Adjacente* adj = v->adj;
                while (adj != NULL) {
                    int verticeAdjacente = adj->vertice;
                    int pesoAresta = adj->peso;

                    if (!visitado[verticeAdjacente] && distancias[verticeAtual] != INFINITO &&
                        distancias[verticeAtual] + pesoAresta < distancias[verticeAdjacente]) {
                        distancias[verticeAdjacente] = distancias[verticeAtual] + pesoAresta;
                        caminho[verticeAdjacente] = verticeAtual;
                    }

                    adj = adj->proximoAdja;
                }
                break;
            }
            v = v->proximoVert;
        }
    }

if (distancias[fim] <= limite) {
        imprimirCaminhoMaisCurto(listaVertices,caminho, distancias, inicio, fim);
        char* eu = corresponderIDaLocalizacao(listaVertices, fim);
        teste(teste15, eu, tipo);
}

}



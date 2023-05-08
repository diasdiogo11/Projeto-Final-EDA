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


void corresponderLocalizacaoaID(Vertice* inicio, char localizacao[]){
    Vertice* aux = inicio;
    
    for(aux; aux != NULL; aux = aux->proximoVert){
        if(strcmp(aux->geocode, localizacao) == 0){
            printf("%d", aux->vertice);
        }
    }
}

void corresponderIDaLocalizacao(Vertice* inicio, int id){
    Vertice* aux = inicio;
    
    for(aux; aux != NULL; aux = aux->proximoVert){
        if(aux->vertice == id){
            printf("%s", aux->geocode);
        }
    }
}

int existelocalizacao(Vertice* inicio, char localizacao[]){
    Vertice* aux = inicio;

    for(aux; aux != NULL; aux = aux->proximoVert){
        if(strcmp(aux->geocode, localizacao) == 0){
            return 1;
        }
    }
    return 0;


}

void guardarGrafo(Vertice* v){
    FILE* fp;
    Vertice *head = v;
    Adjacente *aux;
    fp = fopen("grafos.txt","w");

    if (fp!=NULL){      

        while(v != NULL){  
            fprintf(fp,"%d;%s;\n", v->vertice, v->geocode);
            v = v->proximoVert;
        }
        fprintf(fp,"\n");
        for(v = head; v != NULL ;v = v->proximoVert){
            fprintf(fp,"%d-",v->vertice);
            for(aux = v->adj; aux != NULL; aux = aux->proximoAdja){
                fprintf(fp,"%d(%d);",aux->vertice, aux->peso);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);

        printf("Grafo guardado com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro Grafo\n");
}

int numVertices(Vertice  *v){
    int i = 0;

    if (v == NULL)
        return i;
    
    while(v != NULL){
        i++;
        v = v->proximoVert;
    }

    return i;
}
// Determinar se vértice 'id' já foi visitado
int visitado(int sequencia[],int pos, int id){
  int i;
  for(i=0;i<pos;i++) if (sequencia[i]==id) return(1);
  return(0);
}

// Listar os caminhos existentes entre dois vértices passados
// por parâmetro
void listarCaminhosAux(Vertice *v, int origem, int destino, int sequencia[], int posicao, int pesoTotal){
    int i;
    Vertice *head = v;
    Adjacente *aux;  \
    sequencia[posicao] = origem;
    if (origem==destino) {
        for(i=0;i<posicao;i++) printf("%d->",sequencia[i]); // escrita de um caminho
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






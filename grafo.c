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

/**
 * This function adds a new vertex to a linked list of vertices, with specified geocode and location.
 * 
 * @param listaVertices A pointer to the first node of a linked list of vertices.
 * @param novoVertice An integer representing the new vertex to be added to the list of vertices.
 * @param geocode A string representing the geographic code of the vertex being added.
 * @param local The "local" parameter is a string that represents the name or description of a location
 * associated with a vertex in a graph.
 * 
 * @return a pointer to a Vertice struct. If the memory allocation for the new Vertice was successful,
 * it returns a pointer to the new Vertice. Otherwise, it returns the original pointer to the list of
 * Vertices passed as a parameter.
 */
Vertice* adicionarVertice(Vertice* listaVertices, int novoVertice, char geocode[], char local[]) {
    Vertice* novo = malloc(sizeof(struct Vertices));

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

/**
 * This function adds an edge between two vertices with a given weight in a graph represented by an
 * adjacency list.
 * 
 * @param v a pointer to the first vertex in the graph
 * @param inicio The starting vertex of the edge to be added.
 * @param fim The "fim" parameter in the "adicionarAresta" function represents the ending vertex of the
 * edge being added to the graph.
 * @param peso The weight of the edge being added between two vertices.
 * 
 * @return an integer value, either 0 or 1.
 */
int adicionarAresta(Vertice *v, int inicio, int fim, float peso){

    if (v == NULL)
        return 0;

    if ((existeVertice(v, inicio) != 1) || (existeVertice(v, fim) != 1))
        return 0;

    while(v->vertice != inicio){
        v = v->proximoVert;
    }
    
    Adjacente *new = malloc(sizeof(struct Adjacentes));
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

/**
 * The function checks if a vertex with a given ID exists in a linked list of vertices.
 * 
 * @param inicio a pointer to the first node of a linked list of vertices.
 * @param idvertice The id of the vertex that we are checking for existence in the linked list of
 * vertices starting from the "inicio" vertex.
 * 
 * @return The function `existeVertice` returns an integer value of 1 if a vertex with the given
 * `idvertice` exists in the linked list starting from `inicio`, and returns 0 otherwise.
 */
int existeVertice(Vertice* inicio, int idvertice){

    for(inicio; inicio != NULL; inicio = inicio->proximoVert){
        if (inicio->vertice == idvertice){
            return 1;
        }
    }
    return 0;
   
}

/**
 * The function checks if a given location exists in a linked list of vertices.
 * 
 * @param inicio a pointer to the first node of a linked list of vertices.
 * @param loca loca is a character array (string) representing the name of a location that we want to
 * check if it exists in a linked list of vertices.
 * 
 * @return The function `existeLocalizacao` returns an integer value of either 1 or 0. It returns 1 if
 * the given location (loca) is found in the linked list of vertices starting from the given starting
 * vertex (inicio), and returns 0 if the location is not found.
 */
int existeLocalizacao(Vertice* inicio, char loca[]){

    for(inicio; inicio != NULL; inicio = inicio->proximoVert){
        if(strcmp(inicio->local, loca) == 0){
            return 1;
        }
    }
    return 0;
}

/**
 * The function lists the adjacent vertices and their weights of a given vertex in a graph.
 * 
 * @param v a pointer to a Vertice struct, which represents a vertex in a graph
 * @param idvertice The ID of the vertex whose adjacent vertices are to be listed.
 */
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


/**
 * The function "corresponderLocalizacaoaID" returns the ID of a vertex based on its location name.
 * 
 * @param inicio a pointer to the first node of a linked list of vertices.
 * @param localizacao localizacao is a character array (string) that represents the name of a location.
 * 
 * @return an integer value, which is the ID corresponding to the given location.
 */
int corresponderLocalizacaoaID(Vertice* inicio, char localizacao[]){
    Vertice* aux = inicio;
    
    for(aux; aux != NULL; aux = aux->proximoVert){
        if(strcmp(aux->local, localizacao) == 0){
            return aux->vertice;
        }
    }
}

/**
 * The function "corresponderIDaLocalizacao" takes a starting vertex and an ID, and returns the
 * corresponding location of the vertex with that ID.
 * 
 * @param inicio A pointer to the first vertex in a linked list of vertices.
 * @param id The ID of the vertex whose location needs to be found.
 * 
 * @return a pointer to a character array (string) that represents the location corresponding to the
 * given vertex ID.
 */
char* corresponderIDaLocalizacao(Vertice* inicio, int id){
    Vertice* aux = inicio;

    
    for(aux; aux != NULL; aux = aux->proximoVert){
        if(aux->vertice == id){
           return aux->local;
        }
    }
    
}



/**
 * The function "guardarVertices" saves the information of vertices into a text file.
 * 
 * @param v A pointer to the first node of a linked list of vertices. Each node contains information
 * about a vertex, such as its ID, geocode, and local. The function saves this information to a file
 * named "Vertices.txt".
 */
void guardarVertices(Vertice* v){
    FILE* fp;
    Vertice *head = v;
    Adjacente *aux;
    fp = fopen("Vertices.txt","w");

    if (fp!=NULL){      

        while(v != NULL){  
            fprintf(fp,"%d;%s;%s\n", v->vertice, v->geocode,v->local);
            v = v->proximoVert;
        }
        fclose(fp);

}
}

/**
 * The function reads vertices from a file and adds them to a linked list.
 * 
 * @return The function `lerVertices()` is returning a pointer to a `Vertice` struct, which represents
 * a linked list of vertices read from a file named "Vertices.txt".
 */
Vertice* lerVertices() {
	FILE* fp;
	Vertice* aux = NULL;
    int id;
    char geocode[50], local[50];
	fp = fopen("Vertices.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^\n]\n",&id, geocode, local);
			aux = adicionarVertice(aux, id, geocode, local);
		}
		fclose(fp);
	}
	return(aux);
}


/**
 * The function saves a linked list of vertices to a binary file.
 * 
 * @param inicio a pointer to the first node of a linked list of vertices.
 */
void guardarVerticesBin(Vertice* inicio) 
{
	FILE* fp;
	fp = fopen("Vertices.bin", "wb");
	if (fp != NULL)
	{
		Vertice* aux = inicio;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Vertice), 1, fp);
			aux = aux->proximoVert;
		}
		fclose(fp);
	}
}

/**
 * The function reads vertices from a binary file and returns a linked list of vertices.
 * 
 * @return a pointer to a linked list of vertices read from a binary file.
 */
Vertice* lerVerticesBin()
{
	FILE* fp;
	Vertice* aux = NULL;
	fp = fopen("Vertices.bin", "rb");

	if (fp != NULL)
	{
		Vertice current;
		while (fread(&current, sizeof(Vertice), 1, fp) == 1)
		{
			aux = adicionarVertice(aux, current.vertice, current.geocode, current.local);
		}
		fclose(fp);
	}
	return aux;

}


/**
 * The function saves the vertices and their adjacent vertices with their respective weights to a file
 * named "Arestas.txt".
 * 
 * @param v a pointer to the first vertex in a linked list of vertices.
 */
void guardarArestas(Vertice* v){
    FILE* fp;
    Vertice* head = v;
    Adjacente* aux;
    fp = fopen("Arestas.txt", "w");


    for(v = head; v != NULL ;v = v->proximoVert){
            fprintf(fp,"%d;",v->vertice);
            for(aux = v->adj; aux != NULL; aux = aux->proximoAdja){
                fprintf(fp,"%d;%d;",aux->vertice, aux->peso);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
    
}

/**
 * The function counts the number of vertices in a linked list.
 * 
 * @param v a pointer to the first vertex in a linked list of vertices.
 * 
 * @return the number of vertices in a linked list of vertices.
 */
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

/**
 * The function checks if a given ID has already been visited in a sequence up to a certain position.
 * 
 * @param sequencia an array of integers representing a sequence of IDs that have been visited
 * @param pos The parameter "pos" represents the current position in the sequence array up to which the
 * function should check for the presence of the "id" value.
 * @param id The parameter "id" represents the value that we are searching for in the "sequencia"
 * array. The function "visitado" checks if the value "id" has already been visited (i.e., exists) in
 * the "sequencia" array up to the position "pos".
 * 
 * @return an integer value, either 1 or 0.
 */
int visitado(int sequencia[],int pos, int id){
  int i;
  for(i=0;i<pos;i++) {
    if (sequencia[i]==id){
        return(1);
    } 
  }
  return(0);
}

/**
 * The function recursively lists all possible paths between two vertices in a graph.
 * 
 * @param v A pointer to the starting vertex of the graph.
 * @param origem The starting vertex for the path being searched.
 * @param destino The destination vertex that we want to reach in the graph.
 * @param sequencia an array that stores the sequence of vertices visited in a path from the origin to
 * the destination vertex.
 * @param posicao The position in the sequence array where the current vertex is being added.
 * @param pesoTotal The total weight or cost of the path from the starting vertex to the current
 * vertex.
 */
void listarCaminhosAux(Vertice *v, Veiculos* vi, int origem, int destino, int sequencia[], int posicao, int pesoTotal){
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
            listarCaminhosAux(head,vi,aux->vertice,destino,sequencia,posicao+1,
            pesoTotal+aux->peso);

        aux = aux->proximoAdja;
    }
    }
}

/**
 * The function "listarCaminhos" lists all possible paths between a given origin and destination vertex
 * in a graph.
 * 
 * @param v a pointer to the graph's starting vertex
 * @param origem The starting vertex for finding all possible paths from it to the destination vertex.
 * @param destino The parameter "destino" represents the destination vertex in a graph. It is the
 * vertex where the path or paths from the source vertex (represented by "origem") terminates. The
 * function "listarCaminhos" is used to list all possible paths from the source vertex to the
 * destination vertex
 */
void listarCaminhos(Vertice *v,Veiculos* vi, int origem, int destino){
    char* loca = corresponderIDaLocalizacao(v, destino);
    int sequencia[numVertices(v)];
    listarCaminhosAux(v,vi,origem,destino,sequencia,0,0);
    listarVeiculos(vi, loca);


}


/**
 * The function recursively lists all paths from a given origin to a given destination within a certain
 * weight limit.
 * 
 * @param vi a pointer to a struct containing information about vehicles
 * @param v A pointer to a Vertice struct, which represents a vertex in a graph.
 * @param origem The starting vertex for the path.
 * @param destino The destination vertex ID to which the paths are being searched for.
 * @param sequencia an array that stores the sequence of vertices visited in a path
 * @param posicao posicao is the current position in the sequence array, which is used to keep track of
 * the vertices visited in the path being explored.
 * @param pesoTotal The total weight or distance of the path from the starting vertex to the current
 * vertex. It is updated recursively as the function explores different paths.
 * @param limite The parameter "limite" represents the maximum weight limit for a path to be considered
 * valid. The function "listarCaminhosAuxLimite" is recursively searching for all possible paths
 * between a given origin and destination vertices, and it will only print the paths that have a total
 * weight (sum
 * @param tipo The parameter "tipo" is a string that represents the type of vehicle being used for the
 * pathfinding algorithm. It is used in the function "teste" to calculate the time and cost of the trip
 * based on the vehicle type.
 */
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
            listarVeiculosRaio(vi, destinoNome, tipo);
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

/**
 * The function "listarCaminhosLimite" lists all paths between two vertices with a given limit on the
 * number of edges, based on a graph and a type of vehicle.
 * 
 * @param vi a pointer to a struct of type Veiculos, which likely contains information about vehicles
 * such as their capacity or availability.
 * @param v A pointer to a Vertice struct, which represents a graph.
 * @param origem The starting vertex for the path.
 * @param destino The "destino" parameter is an integer representing the destination vertex in a graph.
 * It is used in the function "listarCaminhosLimite" to specify the vertex to which the paths are to be
 * found from the source vertex.
 * @param limite The "limite" parameter represents the maximum number of edges (or vertices) that a
 * path can have in order to be considered in the search for paths between the "origem" (source) and
 * "destino" (destination) vertices. In other words, it limits the length of the
 * @param tipo The "tipo" parameter is a string that specifies the type of vehicle to consider when
 * finding paths between the origin and destination vertices. It is likely used to filter out paths
 * that are not accessible by the specified type of vehicle.
 */
void listarCaminhosLimite(Veiculos* vi, Vertice* v, int origem, int destino, int limite, char tipo[]) {
    int sequencia[numVertices(v)];
    listarCaminhosAuxLimite(vi, v, origem, destino, sequencia, 0, 0, limite, tipo);
}

/**
 * The function lists all vehicles within a certain radius that match a given location and type.
 * 
 * @param i a pointer to the first element of a linked list of Veiculos (vehicles)
 * @param loca The location within a certain radius where the vehicles should be listed.
 * @param tipo The type of vehicle (e.g. car, bike, scooter) that the function is searching for.
 */
void listarVeiculosRaio(Veiculos* i, char loca[], char tipo[]) {
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
        printf(" CODIGO                      BATERIA                     LOCALIZACAO                     CUSTO P/MIN                 TIPO      \n");
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

void listarVeiculos(Veiculos* i, char loca[]) {
    int encontrado = 0;

    while (i != NULL) {
        if (strcmp(i->localizacao, loca) == 0) {
            encontrado = 1;
            break;
        }
        i = i->proximo_veiculo;
    }

    if (encontrado) {
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        printf(" CODIGO                      BATERIA                     LOCALIZACAO                     CUSTO P/MIN                 TIPO      \n");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        for (i; i != NULL; i = i->proximo_veiculo) {
            if (strcmp(i->localizacao, loca) == 0) {
                printf("   %d                          %d %%                   %s                     %d                   %s\n", i->codigo,i->bateria, i->localizacao, i->custo, i->tipo);
            }
        }
    } else {
        printf("Localizacao dentro do raio pretendido, porem, nao existe nenh %s\n", loca);
    }

    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
}

/**
 * The function returns the index of the vertex with the smallest distance that has not been visited
 * yet.
 * 
 * @param distancias an array of integers representing the distances from a starting vertex to each
 * vertex in a graph.
 * @param visitado An array of integers representing whether a vertex has been visited or not. If
 * visitado[i] is 0, it means that the vertex i has not been visited yet. If visitado[i] is 1, it means
 * that the vertex i has already been visited.
 * @param numVertices The number of vertices in the graph.
 * 
 * @return the index of the vertex with the smallest distance value that has not been visited yet.
 */
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

/**
 * The function recursively prints the path from a starting vertex to an ending vertex in a graph.
 * 
 * @param listaVertices a pointer to the first node of a linked list containing all the vertices in a
 * graph, where each node contains information about a vertex such as its ID and location.
 * @param caminho An array that stores the shortest path from a source vertex to all other vertices in
 * a graph. Each element in the array represents the previous vertex in the path to the corresponding
 * vertex.
 * @param verticeAtual The current vertex being processed in the function.
 * 
 * @return The function does not return anything, it only prints the path from a starting vertex to an
 * ending vertex in a graph.
 */
void imprimirCaminho(Vertice* listaVertices, int caminho[], int verticeAtual) {
    char* locaAtual = corresponderIDaLocalizacao(listaVertices, verticeAtual);
    if (caminho[verticeAtual] == -1) {
        printf("%d(%s) -> ", verticeAtual, locaAtual);
        return;
    }

    imprimirCaminho(listaVertices,caminho, caminho[verticeAtual]);
    printf("%d(%s) -> ", verticeAtual, locaAtual);
}

/**
 * The function prints the shortest path and total distance between two vertices in a graph.
 * 
 * @param listaVertices a pointer to the list of vertices in the graph
 * @param caminho An array that stores the shortest path from the starting vertex to the ending vertex.
 * @param distancias An array that stores the shortest distance from the starting vertex to each vertex
 * in the graph.
 * @param inicio The ID of the starting vertex for the shortest path.
 * @param fim The parameter "fim" represents the ID of the destination vertex in a graph. It is used in
 * the function "imprimirCaminhoMaisCurto" to print the shortest path and total distance between a
 * starting vertex and the destination vertex.
 */
void imprimirCaminhoMaisCurto(Vertice* listaVertices,int caminho[], int distancias[], int inicio, int fim) {
    char* verticeInicio = corresponderIDaLocalizacao(listaVertices, inicio);
    char* verticeFim = corresponderIDaLocalizacao(listaVertices, fim);
    printf("Caminho mais curto entre %d(%s) e %d(%s):\n", inicio,verticeInicio,fim,verticeFim);
    imprimirCaminho(listaVertices,caminho, fim);
    printf("\nDistancia total: %d METROS\n", distancias[fim]);
}

/**
 * This function finds the shortest path between two vertices in a graph and lists the vehicles within
 * a certain radius of the destination vertex.
 * 
 * @param listaVertices a pointer to the first node of a linked list containing all the vertices in the
 * graph
 * @param teste15 It is a pointer to a struct Veiculos, which likely contains information about
 * vehicles.
 * @param numVertices The total number of vertices in the graph.
 * @param inicio The starting vertex for finding the shortest path.
 * @param fim "fim" is the index of the vertex representing the destination in the graph.
 * @param limite The maximum distance allowed for the shortest path between the starting vertex
 * (inicio) and the ending vertex (fim). If the shortest path between the two vertices is greater than
 * the limit, the function will not print the path and the nearby vehicles.
 * @param tipo The parameter "tipo" is a string that represents the type of vehicle to be used for the
 * shortest path calculation. It is used to filter the available vehicles based on their type and find
 * the ones that are suitable for the given task.
 */
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
        listarVeiculosRaio(teste15, eu, tipo);
}

}




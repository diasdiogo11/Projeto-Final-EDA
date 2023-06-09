#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>




typedef struct registo_clientes {

	int idade;
	int NIF;
	int saldo;
	char morada[50], localizacao[50];
	char nome[50];
	char password[50];
	char nickname[50];
	char localizacaoAtual[50];
	struct registo_clientes* proximo_cliente;

}Clientes;

typedef struct registo_gestores {

	char email[50];
	char password[50];
	struct registo_gestores* proximo_gestor;

}Gestores;

typedef struct registo_veiculos {

	int codigo;
	int bateria;
	int custo;
	int reserva;
	int NIF_reserva;
	char localizacao[50];
	char tipo[50];
	time_t horario_reserva;
	struct registo_veiculos* proximo_veiculo;

}Veiculos;

typedef struct historico{
    int idCliente, idMeio, bateria;
    double custoFinal,tempoReserva;
	char tipo[50];
    struct historico *proximoHis;
}Historico;

typedef struct Adjacentes
{
    int vertice;
    int peso;
	char geocode[50];
    struct Adjacentes* proximoAdja;
}Adjacente;

typedef struct Vertices{
    int vertice;
	char geocode[50];
	char local[50];
    Adjacente *adj;
    struct Vertices* proximoVert;
}Vertice;



Clientes* inserir_cliente(Clientes* inicio, int NIF_, char nome_[], int idade_,char morada_[], int saldo, char localizacao[], char nickname[], char password[], char locaAtual[]); //Inserção de novos clientes
Clientes* imprimir_clientes(Clientes* inicio); //Imprime os clientes registados
Clientes* remover_clientes(Clientes* inicio, int code); //Remove um cliente através do seu NIF
Veiculos* inserir_veiculos(Veiculos* inicio, int codigo_, int bateria_, char localizacao_[], int custo_, char tipo_[], int reserva_, int NIF_reserva_, time_t horario_reserva); // Inserção de novos veiculos
Veiculos* imprimir_veiculos(Veiculos* inicio); //Imprimie os veiculos disponiveis
Veiculos* remover_veiculos(Veiculos* inicio, int code);
Gestores* inserir_gestores(Gestores* inicio, char email_[], char password_[]); //Inserção dos gestores
int Reservar_Veiculo(Veiculos* inicio,int NIF_reserva, int code);
void Historico_reservas(Veiculos* inicio);
int imprimir_reservas(Veiculos* inicio, int NIF);
Gestores* remover_gestores(Gestores* inicio, char email[]);
int saldo(Clientes* inicio, int NIF_procurado, int valor);
int login_gestores(Gestores* inicio, char* username, char* password);
int login_clientes(Clientes* inicio, char* nickname, char* password, int NIF);
void ordenacao_veiculos(Veiculos* inicio);
void ordenacao_clientes(Clientes* inicio);
void GuardarVeiculos(Veiculos* inicio);
Veiculos* LerVeiculos();
void GuardarVeiculos_Binario(Veiculos* inicio);
Veiculos* LerVeiculos_Binario();
void GuardarGestores_Binario(Gestores* inicio);
Gestores* LerGestores_Binario();
void GuardarClientes(Clientes* inicio);
Clientes* LerClientes();
void GuardarClientes_Binario(Clientes* inicio);
Clientes* LerClientes_Binario();
int verificar_registo_clientes(Clientes* inicio, int NIF);
int verificar_registo_veiculos(Veiculos* inicio, int codigo);
int verificar_registo_gestores(Gestores* inicio, char email[]);
void AlterarDados(Clientes* inicio, int NIF_procurado);
int Cancelar_Reserva(Veiculos* inicio, Historico* inicio1, Clientes* inicio2, int NIF_reserva, int code);
Veiculos* LocalizarVeiculos(Veiculos* inicio,char localizacao_pretendida[]);
void AlterarDadosGestores(Gestores* inicio, char email_procurado[]);
void GuardarGestores(Gestores* inicio);
int PrecoFinal(Clientes* inicio, int NIF_procurado, int valor);
int VerificarNumReservas(Veiculos* inicio, int NIF);
void GuardarHistorico(Historico* inicio);
Historico* LerHistorico();
Vertice* adicionarVertice(Vertice* listaVertices, int novoVertice, char geocode[], char local[]);
int adicionarAresta(Vertice *v, int inicio, int fim, float peso);
int existeVertice(Vertice* inicio, int idvertice);
void listarAdjacentes(Vertice *v, int idvertice);
int corresponderLocalizacaoaID(Vertice* inicio, char localizacao[]);
char* corresponderIDaLocalizacao(Vertice* inicio, int id);
void guardarVertices(Vertice* v);
void guardarArestas(Vertice* v);
int numVertices(Vertice  *v);
int visitado(int sequencia[],int pos, int id);
void listarCaminhosAux(Vertice *v, Veiculos* vi, int origem, int destino, int sequencia[], int posicao, int pesoTotal);
void listarCaminhos(Vertice *v,Veiculos* vi, int origem, int destino);
char* verlocaAtual(Clientes* inicio, int NIF);
int atualizaMorada(Clientes* inicio, int NIF, char novoGeocode[]);
char* verLocalizacao(Veiculos* inicio, int code);
int verificarNickname(Clientes* inicio, char nickname[]);
void imprimirHistorico(Historico* inicio);
void imprimirHistoricoCliente(Historico* inicio,int NIF);
int gerarCode(Veiculos* inicio);
void listarCaminhosAuxLimite(Veiculos* vi,Vertice *v, int origem, int destino, int sequencia[], int posicao, int pesoTotal, int limite, char tipo[]);
void listarCaminhosLimite(Veiculos* vi,Vertice *v, int origem, int destino, int limite, char tipo[]);
void listarVeiculosRaio(Veiculos* i, char loca[], char tipos[]);
int obterMenorDistancia(int distancias[], int visitado[], int numVertices);
void imprimirCaminho(Vertice* listaVertices, int caminho[], int verticeAtual);
void imprimirCaminhoMaisCurto(Vertice* listaVertices,int caminho[], int distancias[], int inicio, int fim);
void encontrarCaminhoMaisCurto(Vertice* listaVertices, Veiculos* teste15, int numVertices, int inicio, int fim, int limite, char tipo[]);
int estatisticas(Historico* inicio);
int retiraBateria(Veiculos* inicio, double tempoReserva, int code);
Historico* inserirHis(Historico* inicio, int idc, int idm, double custof, double tempoReserva, int bateria, char tipo[]);
char* verTipo(Veiculos* inicio, int code);
int atualizaLocalizacao(Veiculos* inicio,int code,char novaLocalizacao[]);
Vertice* lerVertices();
void guardarVerticesBin(Vertice* inicio);
Vertice* lerVerticesBin();
Vertice* encontrarVertice(Vertice* head, int id);
void lerArestas(Vertice* v);
int existeLocalizacao(Vertice* inicio, char loca[]);
int imprimirReservasAtivas(Veiculos* inicio, int NIF);
void listarVeiculos(Veiculos* i, char loca[]);
void todasLocalizacoes(Vertice* inicio);
#define TAM 50
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <limits.h>
#include "structs.h"
#include "help.h"





void main() {

	char usuario[50], password[50], nome[50], morada[50], localizacao[50], tipo[50],novo_nome[50], nova_morada[50], gestor1[50], email[50], localizacao_pretendida[50], cidadeCliente[50], nickname[50], atual[50];
	int NIF, idade, opcao, NIF_, opcao1, codigo,opcao2,opcao3,opcao6,custo, quantia, saldo_inicial = 0, reserva = 0, NIF_reserva = 0, code, bateria, auxvertice;



	Clientes* clientes = NULL;
	Veiculos* veiculos = NULL;
	Gestores* gestores = NULL;
	Historico* historico = NULL;
	Vertice* grafo = NULL;


	clientes = LerClientes_Binario();
	veiculos = LerVeiculos();
	gestores = LerGestores_Binario();
	historico = LerHistorico();
	grafo = lerVertices();
	gestores = inserir_gestores(gestores, "diogo1234", "lesi");

	adicionarAresta(grafo, 1,2,45);
	adicionarAresta(grafo, 1,3,1000);
	adicionarAresta(grafo, 1,8,1900);
	adicionarAresta(grafo, 2,8,1900);
	adicionarAresta(grafo, 2,5,2000);
	adicionarAresta(grafo, 2,4,950);
	adicionarAresta(grafo, 2,10,2500);
	adicionarAresta(grafo, 3,1,1000);
	adicionarAresta(grafo, 3,4,93);
	adicionarAresta(grafo, 3,5,1000);
	adicionarAresta(grafo, 3,7,650);
	adicionarAresta(grafo, 4,2,950);
	adicionarAresta(grafo, 4,3,93);
	adicionarAresta(grafo, 5,2,2000);
	adicionarAresta(grafo, 5,3,1000);
	adicionarAresta(grafo, 5,6,1300);
	adicionarAresta(grafo, 6,2,877);
	adicionarAresta(grafo, 6,5,683);
	adicionarAresta(grafo, 6,10,1081);
	adicionarAresta(grafo, 7,9,1910);
	adicionarAresta(grafo, 7,4,1810);
	adicionarAresta(grafo, 7,1,1675);
	adicionarAresta(grafo, 7,10,618);
	adicionarAresta(grafo, 8,2,1069);
	adicionarAresta(grafo, 8,6,1980);
	adicionarAresta(grafo, 8,9,610);
	adicionarAresta(grafo, 9,1,770);
	adicionarAresta(grafo, 9,4,324);
	adicionarAresta(grafo, 10,9,83);
	adicionarAresta(grafo, 10,3,1736);
	adicionarAresta(grafo, 10,2,719);
	guardarArestas(grafo);


	do {
		menu_principal();
		printf("OPCAO:\n");
		scanf("%d", &opcao);
		
		if (opcao == 1) {
			clear();
			cabecalho_registar();
			printf("NIF:\n");
			scanf("%d", &NIF);
			if (!verificar_registo_clientes(clientes, NIF)) {
				scanf("%*c");
				printf("Nome(First and last):\n");
				gets(nome);
				printf("Nickname:\n");
				gets(nickname);
				if(!verificarNickname(clientes, nickname)){
					printf("Password:\n");
					gets(password);
					printf("Idade:\n");
					scanf("%d", &idade);
					scanf("%*c");
					printf("Morada:\n");
					gets(morada);
					printf("Cidade\n");
					gets(cidadeCliente);
					clientes = inserir_cliente(clientes, NIF, nome, idade, morada, saldo_inicial,cidadeCliente, nickname, password, "");
					GuardarClientes_Binario(clientes);
					GuardarClientes(clientes);
					clear();
					printf("Registo efetuado com sucesso!\n");
					

				}else{
					printf("Este nickname, ja se encontra registado\n");
				}	
			}
			else {
				clear();
				printf("Utilizador ja se encontra registado\n");
				
			}
		}
		else if (opcao == 2) {
			clear();
			menu_login();
			printf("OPCAO:\n");
			scanf("%d", &opcao1);
			clear();
			if (opcao1 == 1) {
				cabecalho_admin();
				printf("Email:\n");
				scanf("%s", usuario);
				printf("Password:\n");
				scanf("%s", password);
				
					if (login_gestores(gestores, usuario, password)) {
						clear();
						printf("Bem-vindo, %s!\n", usuario);
						do {
							menu_gestores();
							scanf("%d", &opcao2);
								if (opcao2 == 1) {
								clear();
								printf("NIF:\n");
								scanf("%d", &NIF);
								if (!verificar_registo_clientes(clientes, NIF)) {
									scanf("%*c");
									printf("Nome(First and last):\n");
									gets(nome);
									printf("Nickname:\n");
									gets(nickname);
									if(!verificarNickname(clientes, nickname)){
										printf("Password:\n");
										gets(password);
										printf("Idade:\n");
										scanf("%d", &idade);
										scanf("%*c");
										printf("Morada:\n");
										gets(morada);
										printf("Cidade\n");
										gets(cidadeCliente);;
										clientes = inserir_cliente(clientes, NIF, nome, idade, morada, saldo_inicial,cidadeCliente, nickname, password,"");
										GuardarClientes_Binario(clientes);
										GuardarClientes(clientes);
										clear();
										printf("Registo efetuado com sucesso!\n");
										
									

										}else{
											printf("Este nickname, ja se encontra registado\n");
										}
									
									
								}
								else {
									clear();
									printf("Utilizador ja se encontra registado\n");
								}

							}

							else if (opcao2 == 2) {
								clear();
								printf("NIF do utilizador a remover do sistema\n");
								scanf("%d", &NIF_);
								if (verificar_registo_clientes(clientes, NIF_)){
									clientes = remover_clientes(clientes, NIF_);
									GuardarClientes_Binario(clientes);
									GuardarClientes(clientes);
									printf("Utilizador removido com sucesso\n");
								}
								else {
									clear();
									printf("Utilizador nao registado no nosso sistema\n");
								}
								
							}
							else if (opcao2 == 3) {
								clear();
								ordenacao_clientes(clientes);
								imprimir_clientes(clientes);
							}
							else if (opcao2 == 4) {
								clear();
								int codigo = gerarCode(veiculos);
								if (!verificar_registo_veiculos(veiculos, codigo)) {
									printf("Bateria:\n");
									scanf("%d", &bateria);
									scanf("%*c");
									printf("Localizacao:\n");
									gets(localizacao);
									if(existeLocalizacao(grafo, localizacao)){
										printf("Custo:\n");
										scanf("%d", &custo);
										scanf("%*c");
										printf("Tipo:\n");
										gets(tipo);
										veiculos = inserir_veiculos(veiculos, codigo, bateria, localizacao, custo, tipo, reserva, NIF_reserva, 0);
										GuardarVeiculos_Binario(veiculos);
										GuardarVeiculos(veiculos);
										clear();
										printf("Registo efetuado com sucesso!\n");		
									}else{
										printf("Localizacao invalida\n");
									}
								}
								else {
									clear();
									printf("Este veiculo ja se encontra registado\n");
								}
							}
							else if (opcao2 == 5) {
								clear();
								ordenacao_veiculos(veiculos);
								imprimir_veiculos(veiculos);
								printf("Codigo do veiculo a remover do sistema\n");
								scanf("%d", &code);
								if (verificar_registo_veiculos(veiculos, code)) {
									veiculos = remover_veiculos(veiculos, code);
									GuardarVeiculos_Binario(veiculos);
									GuardarVeiculos(veiculos);
									printf("Veiculo removido com sucesso\n");
								
								}
								else {
									clear();
									printf("Veiculo nao registado no nosso sistema\n");
								}
							}
							else if (opcao2 == 6) {
								clear();
								ordenacao_veiculos(veiculos);
								imprimir_veiculos(veiculos);
							}else if(opcao2 == 7){
								clear();
								printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
								printf(" NIF               CODIGO                TEMPO DE RESERVA            CUSTO FINAL             BATERIA FINAL                   TIPO     \n");
								printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
								imprimirHistorico(historico);
								printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
							}
							else if (opcao2 == 8) {
								clear();
								if (strcmp(usuario, "diogo1234") == 0) {
									menu_mastergestor();
									scanf("%d", &opcao6);
									clear();
									if (opcao6 == 1) {
										clear();
										printf("Digite o email do novo gestor\n");
										scanf("%s", email);
										if (!verificar_registo_gestores(gestores, email)) {
											printf("Digite a password do novo gestor\n");
											scanf("%s", password);
											gestores = inserir_gestores(gestores, email, password);
											GuardarGestores_Binario(gestores);
                                            GuardarGestores(gestores);
											clear();
											printf("Registo efetuado com sucesso!\n");
										}
										else {
											clear();
											printf("Este gestor ja se encontra registado\n");
										}
										
										
									}
									else if (opcao6 == 2) {
										clear();
										printf("Digite o email do gestor a remover do sistema\n");
										scanf("%s", email);
										if (verificar_registo_gestores(gestores, email)) {
											if (strcmp(gestores->email, email) == 0) {
												gestores = remover_gestores(gestores, email);
												GuardarGestores_Binario(gestores);
												clear();
												printf("Gestor removido com sucesso\n");
											}
											else {
												clear();
												printf("Gestor impossivel de remover\n");
											}
											
										}
										else {
											clear();
											printf("Gestor nao registado no nosso sistema\n");
										}
										
									}
									else if (opcao6 == 3) {
										clear();
										printf("Qual o gestor a alterar dados\n");
										scanf("%s", email);
										if (verificar_registo_gestores(gestores, email)) {
											clear();
											printf("1.ALTERAR EMAIL\n");
											printf("2.ALTERAR PASSWORD\n");
											AlterarDadosGestores(gestores, email);
											
											printf("*--------------------------------------------*\n");
											printf("|              DADOS ATUALIZADOS             |\n");
											printf("|                 FACA LOGIN!                |\n");
											printf("*--------------------------------------------*\n");
											break;
										}
										else {
											printf("Gestor nao registado no nosso sistema\n");
										}
										
									}
									
								}
								else {
									clear();
									printf("ACESSO NAO AUTORIZADO\n");
								}

							}
							else if (opcao2 == 8) {
								imprimirHistorico(historico);
							}
							else if(opcao2 == 9){
								int id = numVertices(grafo);
								char geocode[50], local[50];
								scanf("%*c");
								printf("Digite o geocode do vertice a inserir\n");
								gets(geocode);
								printf("Digite o local do vertice a inserir\n");
								gets(local);
								if(!existeLocalizacao(grafo, local)){
									grafo = adicionarVertice(grafo, id, geocode, local);
									guardarVertices(grafo);
									guardarVerticesBin(grafo);
								}
							}else if(opcao2 == 10){

								char origem[50], destino[50];
								int peso;
								scanf("%*c");
								printf("Digite a localizacao de origem\n");
								gets(origem);
								if(existeLocalizacao(grafo, origem)){
									printf("Digite a localizacao de destino\n");
									gets(destino);
									if(existeLocalizacao(grafo, destino)){
										printf("Digite a distancia entre ambos\n");
										scanf("%d", &peso);
										int idOrigem = corresponderLocalizacaoaID(grafo, origem);
										int idDestino = corresponderLocalizacaoaID(grafo, destino);
										adicionarAresta(grafo, idOrigem, idDestino, peso);
										guardarArestas(grafo);
									}else{
										printf("Localizacao nao registada\n");
									}

								}else{
									printf("Localizacao nao registada\n");
								}
								
								
							}
						} while (opcao2 != 0);
					}
					
					
					
					else {
						clear();
						printf("Nome de usuario ou senha incorretos.\n");
					}
					
					
			}
			else if(opcao1 == 2) {
				clear();
				cabecalho_cliente();
				scanf("%*c");
				printf("Nickname:\n");
				gets(usuario);
				printf("Password:\n");
				gets(password);
				printf("NIF:\n");
				scanf("%d", &NIF);
				
				if (login_clientes(clientes, usuario, password,NIF)) {
					clear();
					time_t t = time(NULL);
					int escolha, dist, teste;
					char localizacao[50], tipo[50], atual[50];
						printf("Bem vindo %s\n", usuario);
						do {
							menu_clientes();
							scanf("%d", &opcao3);
							if (opcao3 == 1) {
								clear();
								if(VerificarNumReservas(veiculos, NIF)){
									menuReservas();
									printf("OPCAO:\n");
									scanf("%d", &escolha);
									if(escolha == 1){
										char* loca = verlocaAtual(clientes, NIF);
										if(strcmp(loca, "") == 0){
											todasLocalizacoes(grafo);
											scanf("%*c");
											printf("Insira a sua localizacao atual\n");
											gets(atual);
											if(existeLocalizacao(grafo, atual)){
												int idVertice = corresponderLocalizacaoaID(grafo, atual);
												int numvertices = numVertices(grafo);
												printf("Onde deseja reservar Veiculos?\n");
												gets(localizacao);
												int idLoca = corresponderLocalizacaoaID(grafo,localizacao);
												clear();
												listarCaminhos(grafo,veiculos, idVertice,idLoca);
											}else{
												printf("Localizacao invalida\n");
												break;
											}
										}else{
											char* loca = verlocaAtual(clientes, NIF);
											printf("Ficou registado no nosso sistema a seguinte localizacao: %s\n", loca);
											printf("Corresponde a sua localizacao atual?\n");
											scanf("%d", &teste);
											if(teste == 1){
												todasLocalizacoes(grafo);
												int idVertice = corresponderLocalizacaoaID(grafo, loca);
												scanf("%*c");
												printf("Onde deseja reservar Veiculos?\n");
												gets(localizacao);
												int idLoca = corresponderLocalizacaoaID(grafo,localizacao);
												clear();
												listarCaminhos(grafo,veiculos, idVertice,idLoca);

											}else if(teste == 2){
												todasLocalizacoes(grafo);
												scanf("%*c");
												printf("Insira a sua localizacao atual\n");
												gets(atual);
												if(existeLocalizacao(grafo, atual)){
													int idVertice = corresponderLocalizacaoaID(grafo, atual);
													printf("Onde deseja reservar Veiculos?\n");
													gets(localizacao);
													int idLoca = corresponderLocalizacaoaID(grafo,localizacao);
													listarCaminhos(grafo,veiculos, idVertice, idLoca);
												}else{
													printf("Localizacao invalida\n");
													break;
												}
												
											}
										}
									}else if(escolha == 2){
										char* loca = verlocaAtual(clientes, NIF);
										if(strcmp(loca, "") == 0){
											todasLocalizacoes(grafo);
											scanf("%*c");
											printf("Insira a sua localizacao atual\n");
											gets(atual);
											if(existeLocalizacao(grafo, atual)){
												int idVertice = corresponderLocalizacaoaID(grafo, atual);
												int numvertices = numVertices(grafo);
												clear();
												printf("Digite a distancia em que deseja encontrar um veiculo\n");
												scanf("%d", &dist);
													scanf("%*c");
													printf("Que tipo de veiculo pretende reservar?\n");
													gets(tipo);
													clear();
													printf("******************************************************\n");
													printf("Voce encontra-se aqui -> %d %s\n", idVertice, atual);
													printf("******************************************************\n");
													int i = 1;
													for(i;i < numvertices;i++){
														encontrarCaminhoMaisCurto(grafo, veiculos, 10, idVertice, i, dist, tipo);
											
													}
											}else{
												printf("Localizacao invalida\n");
												break;
											}
											
											}else{
												printf("Ficou registado no nosso sistema a seguinte localizacao: %s\n", loca);
												printf("Corresponde a sua localizacao atual?\n");
												scanf("%d", &teste);
												if(teste == 1){
													int idVertice = corresponderLocalizacaoaID(grafo, loca);
													int numvertices = numVertices(grafo);
													clear();
													printf("Digite a distancia em que deseja encontrar um veiculo\n");
													scanf("%d", &dist);	
													scanf("%*c");
													printf("Que tipo de veiculo pretende reservar?\n");
													gets(tipo);
													clear();
													printf("******************************************************\n");
													printf("Voce encontra-se aqui -> %d %s\n", idVertice, loca);
													printf("******************************************************\n");
													int i = 1;
													for(i;i < numvertices;i++){
														encontrarCaminhoMaisCurto(grafo, veiculos, 10, idVertice, i, dist, tipo);
											
													}
												}else{
													todasLocalizacoes(grafo);
													scanf("%*c");
													printf("Insira a sua localizacao atual\n");
													gets(atual);
													if(existeLocalizacao(grafo, atual)){
														int idVertice = corresponderLocalizacaoaID(grafo, atual);
														int numvertices = numVertices(grafo);
														clear();
														printf("Digite a distancia em que deseja encontrar um veiculo\n");
														scanf("%d", &dist);
														scanf("%*c");
														printf("Que tipo de veiculo pretende reservar?\n");
														gets(tipo);
														clear();
														printf("******************************************************\n");
														printf("Voce encontra-se aqui -> %d %s\n", idVertice, atual);
														printf("******************************************************\n");
														int i = 1;
														for(i;i < numvertices;i++){
															encontrarCaminhoMaisCurto(grafo, veiculos, 10, idVertice, i, dist, tipo);
											
														}

													}else{
														printf("Localizacao invalida\n");
														break;
													}
												
												}

											}
										
									}else{
										printf("Digite uma opcao valida\n");
										break;
									}
									printf("--------------------------------------------------------------------------------------------------------------------------\n");
									printf("Deseja reservar algum veiculo?\n");
									scanf("%d", &escolha);
									if(escolha == 1){
										printf("Qual o codigo do veiculo a reservar\n");
										scanf("%d", &code);
										char* teste1 = verlocaAtual(clientes, NIF);
										int teste = corresponderLocalizacaoaID(grafo, localizacao);
										int teste2 = corresponderLocalizacaoaID(grafo, teste1);
										printf("Deseja prosseguir com a reserva?(1-Sim/ 2-Nao)\n");
										scanf("%d", &escolha);
										if(escolha == 1){
											if (Reservar_Veiculo(veiculos, NIF, code)) {
											clear();
											GuardarClientes(clientes);
											GuardarClientes_Binario(clientes);
											printf("Reserva bem sucedida\n");
											GuardarVeiculos_Binario(veiculos);
											GuardarVeiculos(veiculos);
											printf("*--------------------------------------------*\n");
											printf("|              DADOS ATUALIZADOS             |\n");
											printf("|                 FACA LOGIN!                |\n");
											printf("*--------------------------------------------*\n");
											break;
											}else {
												clear();
												printf("Veiculo indisponivel\n");
											}

									}else{
											printf("Voltando para o menu...\n");
										}
									}else{
										printf("Voltando para o menu...\n");
									}
									
									}else{
										printf("Atingiu o numero maximo de reservas\n");
									}
							}
							else if (opcao3 == 2) {
								char locaAtual[50];
								clear();
								imprimirReservasAtivas(veiculos, NIF);
								printf("Qual o codigo do veiculo\n");
   							 	scanf("%d", &code);
								scanf("%*c");
								printf("Qual a sua localizacao atual?\n");
								gets(locaAtual);
								if(existeLocalizacao(grafo, locaAtual)){
									char* geocode = verLocalizacao(veiculos, code);

									if (Cancelar_Reserva(veiculos,historico,clientes,NIF,code)) {
										atualizaLocalizacao(veiculos,code,locaAtual);
										atualizaMorada(clientes,NIF,geocode);
										GuardarVeiculos_Binario(veiculos);
										GuardarVeiculos(veiculos);
										GuardarClientes(clientes);
										GuardarClientes_Binario(clientes);
										printf("*--------------------------------------------*\n");
										printf("|              DADOS ATUALIZADOS             |\n");
										printf("|                 FACA LOGIN!                |\n");
										printf("*--------------------------------------------*\n");
										break;
									}
									else {
										printf("*---------------------------------------------*\n");
										printf("|   ESTE VEICULO JA SE ENCONTRA DISPONIVEL    |\n");
										printf("*---------------------------------------------*\n");
									}
								}else{
									printf("Localizacao invalida\n");
									break;
								}
								
							}
							else if (opcao3 == 3) {
								clear();
								int valor;
								printf("Qual a quantia a adicionar?\n");
								scanf("%d", &valor);
								if (saldo(clientes, NIF, valor)) {
									GuardarClientes_Binario(clientes);
									GuardarClientes(clientes);
									clear();
									printf("Saldo carregado com sucesso\n");
									
								}
								else {
									clear();
									printf("Erro ao carregar saldo\n");
								}
									
								
								

							}
							else if (opcao3 == 4) {
								clear();
								AlterarDados(clientes, NIF);
								GuardarClientes_Binario(clientes);
								GuardarClientes(clientes);
								printf("*--------------------------------------------*\n");
								printf("|              DADOS ATUALIZADOS             |\n");
								printf("|                 FACA LOGIN!                |\n");
								printf("*--------------------------------------------*\n");
								break;
								
							}
							else if (opcao3 == 5) {
								imprimir_reservas(veiculos, NIF);
								


							}else if(opcao3 == 6){
								clear();
								printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
								printf(" NIF               CODIGO                TEMPO DE RESERVA            CUSTO FINAL             BATERIA FINAL                   TIPO     \n");
								printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
								imprimirHistoricoCliente(historico, NIF);
								
							}
							
						} while (opcao3 != 0);
						


					}
					else {
						clear();
						printf("Nome de usuario ou NIF incorretos.\n");
					}
				
				

			}else{
				clear();
				printf("Digite uma opcao valida\n");
			}

		}
		else if (opcao == 0) {
			clear();
			printf("Obrigado pela sua visita...\n");

		}else{
			clear();
			printf("Digite uma opcao valida\n");
		}


	} while (opcao != 0);








}
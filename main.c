#define TAM 50
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include "structs.h"





void main() {

	char usuario[50], password[50], nome[50], morada[50], localizacao[50], tipo[50],novo_nome[50], nova_morada[50], gestor1[50], email[50], localizacao_pretendida[50], cidadeCliente[50];
	int NIF, idade, opcao, NIF_, opcao1, codigo,opcao2,opcao3,opcao6,custo, quantia, saldo_inicial = 0, reserva = 0, NIF_reserva = 0, code, bateria, auxvertice;



	Clientes* clientes = NULL;
	Veiculos* veiculos = NULL;
	Gestores* gestores = NULL;
	Historico* historico = NULL;
	Vertice* grafo = NULL;

	clientes = LerClientes_Binario();
	veiculos = LerVeiculos_Binario();
	gestores = LerGestores_Binario();
	historico = LerHistorico();
	gestores = inserir_gestores(gestores, "diogo1234", "lesi");

grafo = adicionarVertice(grafo,1,"Porto");
grafo = adicionarVertice(grafo,2,"Santo Tirso");
grafo = adicionarVertice(grafo,3,"Barcelos");
grafo = adicionarVertice(grafo,4,"Braga");
adicionarAresta(grafo, 1,3,15);
adicionarAresta(grafo, 3,4,20);
adicionarAresta(grafo, 4,2,25);
adicionarAresta(grafo, 1,4,100);
guardarGrafo(grafo);

listarAdjacentes(grafo, 3);

int x;




char* teste = verGeocode(clientes, 10);
printf("%s", teste);
x = corresponderLocalizacaoaID(grafo, teste);
printf("%d\n", x);
listarCaminhos(grafo, 1 ,x);


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
				printf("Nome:\n");
				gets(nome);
				printf("Idade:\n");
				scanf("%d", &idade);
				scanf("%*c");
				printf("Cidade\n");
				gets(cidadeCliente);
				scanf("%*c");
				printf("Morada:\n");
				gets(morada);
				clientes = inserir_cliente(clientes, NIF, nome, idade, morada, saldo_inicial,cidadeCliente);
				GuardarClientes_Binario(clientes);
				GuardarClientes(clientes);
				clear();
				printf("Registo efetuado com sucesso!\n");
				
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
									printf("Nome:\n");
									gets(nome);
									printf("Idade:\n");
									scanf("%d", &idade);
									printf("Cidade\n");
									gets(cidadeCliente);
									scanf("%*c");
									printf("Morada:\n");
									gets(morada);
									clientes = inserir_cliente(clientes, NIF, nome, idade, morada, saldo_inicial,cidadeCliente);
									GuardarClientes_Binario(clientes);
									GuardarClientes(clientes);
									clear();
									printf("Registo efetuado com sucesso!\n");
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
								printf("Codigo:\n");
								scanf("%d", &codigo);
								if (!verificar_registo_veiculos(veiculos, codigo)) {
									printf("Bateria:\n");
									scanf("%d", &bateria);
									scanf("%*c");
									printf("Localizacao:\n");
									gets(localizacao);
									if(existelocalizacao(grafo, localizacao)){
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
										printf("A localizacao inserida nao se encontra no sistema\n");
									}
										
								}
								else {
									clear();
									printf("Este veiculo ja se encontra registado\n");
								}
							}
							else if (opcao2 == 5) {
								clear();
								veiculos = imprimir_veiculos(veiculos);
								printf("Codigo do veiculo a remover do sistema\n");
								scanf("%d", &codigo);
								if (verificar_registo_veiculos(veiculos, codigo)) {
									veiculos = remover_veiculos(veiculos, codigo);
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
							}
							else if (opcao2 == 7) {
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
								
							}
						} while (opcao2 != 0);
					}
					
					
					
					else {
						clear();
						printf("Nome de usuario ou senha incorretos.\n");
					}
					
					
			}
			else {
				clear();
				cabecalho_cliente();
				printf("NIF:\n");
				scanf("%d", &NIF);
				scanf("%*c");
				printf("Nome:\n");
				gets(usuario);
				
				if (login_clientes(clientes, usuario, NIF)) {
					clear();
					time_t t = time(NULL);
					char localizacao[50];
						printf("Bem vindo %s\n", usuario);
						do {
							menu_clientes();
							scanf("%d", &opcao3);
							if (opcao3 == 1) {
								clear();
								if(VerificarNumReservas(veiculos, NIF)){
									scanf("%*c");
									printf("Em que zona deseja alugar veiculos?\n");
									gets(localizacao);
									if(existelocalizacao(grafo, localizacao)){
										LocalizarVeiculos(veiculos,localizacao);
										printf("Qual o codigo do veiculo\n");
										scanf("%d", &code);
								
										if (Reservar_Veiculo(veiculos, NIF, code)) {
											clear();
											printf("Reserva bem sucedida\n");
											historico = inserirHis(historico, NIF, code, 0,*localtime(&t), *localtime(&t));
											GuardarHistorico(historico);
											GuardarVeiculos_Binario(veiculos);
											GuardarVeiculos(veiculos);
											printf("*--------------------------------------------*\n");
											printf("|              DADOS ATUALIZADOS             |\n");
											printf("|                 FACA LOGIN!                |\n");
											printf("*--------------------------------------------*\n");
											break;
										}
										else {
											clear();
											printf("Veiculo indisponivel\n");

										}

									}
									

								}else{
									printf("Deu errado carita\n");
								}
								
								
								

							}
							else if (opcao3 == 2) {
								clear();

								if (Cancelar_Reserva(veiculos,clientes,NIF)) {
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
								veiculos = imprimir_reservas(veiculos, NIF);


							}
							
						} while (opcao3 != 0);
						


					}
					else {
						clear();
						printf("Nome de usuario ou NIF incorretos.\n");
					}
				
				

			}

		}
		else if (opcao == 0) {
			clear();
			printf("Obrigado pela sua visita...\n");

		}


	} while (opcao != 0);








}
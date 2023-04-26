#define TAM 50
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "structs.h"




void main() {

	char usuario[50], password[50], nome[50], morada[50], localizacao[50], tipo[50],novo_nome[50], nova_morada[50], gestor1[50], email[50], localizacao_pretendida[50];
	int NIF, idade, opcao, NIF_, opcao1, codigo,opcao2,opcao3,opcao6, bateria, custo, quantia, saldo_inicial = 0, reserva = 0, NIF_reserva = 0, code;

	Clientes* clientes = NULL;
	Veiculos* veiculos = NULL;
	Gestores* gestores = NULL;

	clientes = LerClientes_Binario();
	veiculos = LerVeiculos_Binario();
	gestores = LerGestores_Binario();
	gestores = inserir_gestores(gestores, "diogo1234", "lesi");





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
				printf("Morada:\n");
				gets(morada);
				clientes = inserir_cliente(clientes, NIF, nome, idade, morada, saldo_inicial);
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
									scanf("%*c");
									printf("Morada:\n");
									gets(morada);
									clientes = inserir_cliente(clientes, NIF, nome, idade, morada, saldo_inicial);
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
									printf("Custo:\n");
									scanf("%d", &custo);
									scanf("%*c");
									printf("Tipo:\n");
									gets(tipo);
									veiculos = inserir_veiculos(veiculos, codigo, bateria, localizacao, custo, tipo, reserva, NIF_reserva);
									GuardarVeiculos_Binario(veiculos);
									GuardarVeiculos(veiculos);
									clear();
									printf("Registo efetuado com sucesso!\n");
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
								criarmatriz(veiculos);
								GuardarVeiculos(veiculos);
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
						printf("Bem vindo %s\n", usuario);
						do {
							menu_clientes();
							scanf("%d", &opcao3);
							if (opcao3 == 1) {
								clear();
								ordenacao_veiculos(veiculos);
								


								scanf("%*c");
								printf("Onde deseja encontrar veiculos disponiveis?\n");
								gets(localizacao_pretendida);
								LocalizarVeiculos(veiculos, localizacao_pretendida);
								printf("Qual o codigo do veiculo\n");
								scanf("%d", &code);
								
								if (Reservar_Veiculo(veiculos,NIF, code)) {
									clear();
									printf("Reserva bem sucedida\n");
									GuardarVeiculos_Binario(veiculos);
									GuardarVeiculos(veiculos);
									printf("*--------------------------------------------*\n");
									printf("|              DADOS ATUALIZADOS             |\n");
									printf("|                 FACA LOGIN!                |\n");
									printf("*--------------------------------------------*\n");
									break;
									clear();
								}
								else {
									clear();
									printf("Veiculo indisponivel\n");

								}
								
								

							}
							else if (opcao3 == 2) {
								clear();
								int code;

								printf("Qual o codigo do veiculo\n");
								scanf("%d", &code);
								if (Cancelar_Reserva(veiculos,NIF)) {
									GuardarVeiculos_Binario(veiculos);
									GuardarVeiculos(veiculos);
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
								if (saldo(clientes, NIF)) {
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
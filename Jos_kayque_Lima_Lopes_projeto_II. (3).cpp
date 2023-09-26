#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define N 200 // tamanho e quantidade 
#define MAXIMO 1000 //n�mero m�ximo de e-mails.
#define MAX_PRODUTOS 200 //n�mero m�ximo de produtos.
struct Email
{
	char endereco[80];/// n�mero m�ximo de caracteres para endere�o de e-mail.
};
//valida��o do e-mail
int validade(char endereco[], struct Email emails[], int nemails)
{
	if (strlen(endereco) <= 79)   //tamanho do endere�o.
	{
		for (int i = 0; i < nemails; i++)
		{
			if (strcmp(endereco, emails[i].endereco) == 0)
			{
				return 0; //se o e-mail j�  existe no site.
			}
		}// Verifica��o das partes essenciais .
		if (strstr(endereco, "@") != NULL && (strstr(endereco, "hotmail") || strstr(endereco, "gmail")) && strstr(endereco, ".com"))
		{
			return 1; //e-mail for v�lido.
		}
	}
	else
	{
		return 0;// caso o tamanho do endere�o ser que  80 caracteres.
	}
}
// defini��o da estrutura do cliente ou usu�rio.
struct Cliente
{
	int idade;
	char pessoa[30];
	float valorgasto;
	int cadastrado; //registrar cliente.
};
// fun��o para exibir o menu.
void exibirMenu()
{
	printf("== Menu ==\n");
	printf("1 - Setores do supermercado\n");
	printf("2 - Cadastrar-se para o sorteio\n");
	printf("3 - Editar nome\n");
	printf("4 - Excluir nome\n");
	printf("5 - Listar produtos comprados pelo usu�rio\n");
	printf("6 - Sorteio online\n");
	printf("7 - Sair\n");
}
void limpartela()
{
	system("cls");
//comando para limpar a tela depois do usuario sair do setor do supermercado.
}
// vari�veis globais.
int opcao;
struct Cliente clientes[1000];//armazenar 1000 clientes.
int qtd = 0;
int escolha;
int opcao_submenu;
int qtdClientes = 0;
// estrutura do produto.
struct Produto
{
	char nome[1000];
	float preco;
	int quantidade;

};

void listagem(struct Produto carrinho[], int quantidade)
{
	printf("NOMES DOS PRODUTOS E SEUS N�MEROS CORRESPONDENTES");
	printf("Voc� selecionou o SETOR LATIC�NIOS.\n");
	char* produtos[] =
	{//cada nome tem seu ponteiro e sua posi��o na lista.
		"Leite", "Sorvete", "Manteiga", "Ovos", "Creme de leite",
		"Requeij�o", "Iogurte natural", "Abacaxi", "Cenoura", "Goiaba",
		"Uva", "Alface", "Morango", "Banana", "Sabonete",
		"Detergentes", "Desinfetantes", "Papel Higi�nico", "Escovas", "Vassouras",
		"Esponjas ", "Bolo", "Donuts ", "Torta",
		"P�es ", "Brigadeiros ", "Biscoitos ", "Croissants ",
		"Cerveja", "Refrigerante", "Carne", "Peito de Frango",
		"Massa de pastel", "Salsicha", "Suco de fruta", "Arroz",
		"Flocos de aveia", "Feij�o", "Farinha de trigo", "Cereal matinal",
		"Massa sem fermento", "Pipoca de milho"
	};//Vai listar os produtos, para o usu�rio ver-los.

	for (int i = 0; i < 42; i++)
	{
		printf("|====================== %d. %s\n", i + 1, produtos[i]);
	}// vai mostrar o pre�o, a quantidade, o nome que ser� o n�mero , tudo isso dentro do carinho.
	printf("Produtos comprados:\n");
	for (int i = 0; i < quantidade; i++)
	{
		printf("Nome: %s\n", carrinho[i].nome);
		printf("Pre�o unit�rio: R$%.2f\n", carrinho[i].preco);
		printf("Quantidade: %d\n", carrinho[i].quantidade);
		printf("Subtotal: R$%.2f\n", carrinho[i].preco * carrinho[i].quantidade);
		printf("------------------------------------------------------------\n");
	}
}

void shuffleArray(int array[], int s)
{
	for (int i = s - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}
//sorteio com rand para ser aleat�rio.
void realizarSorteio()
{
	srand(time(NULL));
	char nomes[15][20] =
	{
		"AMARELO",
		"AZUL",
		"VERDE",
		"VERMELHO",
		"BRANCO",
		"PRETO",
		"ROSA",
		"ROXA",
		"LARANJA",
		"MARRON",
		"CIANO",
		"ESMERALDA",
		"DOURADO",
		"CINSA",
		"BEGE"
	};//cada cor associada a um n�mero.

	int numerosPossiveis[15];
	for (int i = 0; i < 15; i++)
	{
		numerosPossiveis[i] = i + 1;
	}

	shuffleArray(numerosPossiveis, 15);

	int matriz[3][5];
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			matriz[i][j] = numerosPossiveis[count++];
		}
	}//o n�mero possivel vai sendo mudado a cada intera��o.

	printf("Matriz 3x5 com n�meros diferentes:\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%2d - %s\t", matriz[i][j], nomes[matriz[i][j] - 1]);
		}
		printf("\n");
	}

	int numeroEscolhido;
	int numeroSorteado;
	int tentativas = 0;
//duas tentativas apenas.
	while (tentativas < 2)
	{
		int linhaSorteada = rand() % 3;
		int colunaSorteada = rand() % 5;
		numeroSorteado = matriz[linhaSorteada][colunaSorteada];
//ESCOLHER N�MERO DEACORDO COM A COR
		printf("Tentativa %d: Escolha um n�mero da matriz (1 a 15): ", tentativas + 1);
		scanf("%d", &numeroEscolhido);

		if (numeroEscolhido >= 1 && numeroEscolhido <= 15)
		{
			if (numeroEscolhido == numeroSorteado)
			{
				printf("\nN�mero sorteado: %d - %s\n", numeroSorteado, nomes[numeroEscolhido - 1]);
				printf("Parab�ns, voc� � o vencedor!\n");
				printf("Voc� ganhou um CELULAR DA CARRO TESLA!!!!!!");
				break;
			}
			else
			{
				printf("N�mero n�o sorteado, TENTE NOVAMENTE VOC� CONSEGUE!!!!.\n");
				tentativas++;
			}
		}
		else
		{
			printf("N�mero fora do intervalo (1 a 15). Tente novamente .\n");
		}
	}

	if (tentativas == 2)  //duas tentativas apenas.
	{
		printf("Suas tentativas acabaram. O n�mero sorteado era %d - %s.\n", numeroSorteado, nomes[numeroSorteado - 1]);
	}
}

// Fun��o para adicionar os produto ao carrinho

int adicionarProduto(struct Produto carrinho[], int quantidadee, char nome[], float preco, int quantidade_produto)
{
	if (quantidadee < MAX_PRODUTOS)
	{
		strcpy(carrinho[quantidadee].nome, nome);
		carrinho[quantidadee].preco = preco ;
		carrinho[quantidadee].quantidade = quantidade_produto; // Definir a quantidade.
		printf("Produto \"%s\" adicionado ao carrinho.\n", nome);
		quantidadee++; // adi��o da  quantidade de produtos no carrinho.
	}
	else
	{
		printf("O carrinho est� cheio. N�o � poss�vel adicionar mais produtos.\n");
	}
	return quantidadee; // Retornar a nova quantidade de produtos no carrinho.
}// pre�os dos produtos.
// Declara��o da fun��o para o pagamento no caixa.
void realizarPagamento(struct Produto carrinho[], int quantidade)
{
	// Calcular o total das compras para o caixa.
	float calcularTotal(struct Produto carrinho[], int quantidade) ;
	float total = 0;
	for (int i = 0; i < quantidade; i++)
	{
		total += carrinho[i].preco * carrinho[i].quantidade; // Multiplica o pre�o pela quantidade
	}




	// Solicita o valor pago pelo cliente
	float valorPago;
	printf("Total da compra: R$%.2f\n", total);
	printf("Insira o valor pago: R$");
	scanf("%f", &valorPago);


	// Verifica se o valor pago � suficiente e repete ate ficar correto
	while (valorPago < total)
	{
		printf("Valor insuficiente. O pagamento n�o pode ser conclu�do.\n");
		printf("insira o valor deacordo com o Total da compra: R$");
		scanf("%f", &valorPago);

	}

	// Calcula o troco da compra
	float troco = valorPago - total;

	printf("Pagamento efetuado com sucesso!\n");
	printf("Troco: R$%.2f\n", troco);

	// Limpa o carrinho depois o pagamento ser conclu�do
	quantidade = 0;
}


float precos[] =
{
	3.00, 15.00, 7.00, 12.00, 5.50, 11.00, 6.00,      // Pre�os LATIC�NIOS.
	2.00, 3.00, 8.00, 4.00, 5.00, 2.00, 2.00,        // Pre�os FRUTAS, VERDURAS E LEGUMES.
	2.00, 3.00, 7.00, 4.00, 2.00, 18.00, 2.00,      // pre�os  HEGIENE E LIMPEZA.
	7.00, 6.00, 13.00, 3.00, 14.00, 6.00, 9.00,    // Pre�os  PADARIA E CONFEITARIA.
	11.00, 6.00, 13.00, 8.00, 10.00, 6.00, 5.00,  // Pre�os  SETOR BEBIDAS E FRIOS.
	7.00, 4.00, 5.00, 8.00, 16.00, 6.00, 9.00    // Pre�os SETOR CEREAIS.
};
// Fun��o para calcular o total do carrinho
//Produto carrinho[]  para representar os pre�os
float calcularTotal(struct Produto carrinho[], int quantidade)
{
	float total = 0;
	for (int i = 0; i < quantidade; i++)
	{
		total += carrinho[i].preco * carrinho[i].quantidade; // Multiplica o pre�o pela quantidade
	}
	return total;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	char login[50], senha[50], usuario[50], pass[50];

	printf("-------------------------------------------------------------\n");
	printf("----------------  CADASTRAMENTO  -----------------\n");
	printf("-------------------------------------------------\n");
	printf("-------INFORME SEUS DADOS PARA PROSSEGUIR -------\n");
	printf("Cadastre um nome para o usu�rio: ");
	scanf("%s", login);
	printf("Cadastre uma senha para o usuario %s: ", login);
	scanf("%s", senha);
	printf("\n%s, Voc� foi cadastrado no sistema!\n\n", login);
	printf("--------------------------------------------------------------\n");
	printf("------------------------- FA�A SEU LOGIN ----------------------\n");
	printf("Informe seu usu�rio: ");
	scanf("%s", usuario);
	printf("Informe sua senha: ");
	scanf("%s", pass);
	printf("-----------------------------------------------------------------\n");
	printf("Verificando usu�rio e senha....\n");
	// compara��o entre usuario e login , pass e senha
	while (strcmp(usuario, login) != 0 || strcmp(pass, senha) != 0)
	{
		printf("Usuario ou senha incorretos, informe as informa��es novamente\n\n");
		printf("Informe o usu�rio: ");
		scanf("%s", usuario);
		printf("Informe a senha: ");
		scanf("%s", pass);
	}

	printf("LOGIN FOI CONCLUIDO\n");
	printf("--------------------PARA FINALIZAR O CADASTRO-----------------------\n");
	printf("----------INFORME UM ENDERE�O DE E-MAIL V�LIDO----------------------\n");

	struct Email emails[MAXIMO];
	int nemails = 0;
	char endereco[70];
	char resp;//s ou n para criar novo e-mail.

	printf("--------------------- CADASTRO DE E-MAILS ---------------------------\n");

	do
	{
		printf("Informe o seu email ou cadastre um novo EMAIL para %s: ", login);
		scanf("%s", endereco);
// se o e-mail tiver j� sido cadastrado no sistema.
		while (!validade(endereco, emails, nemails))
		{
			printf("E-mail inv�lido ou j� cadastrado. Por favor, insira um e-mail v�lido: ");
			scanf("%s", endereco);
		}

		strcpy(emails[nemails].endereco, endereco);
		nemails++;
		printf("===== E-MAIL CADASTRADO COM SUCESSO !!!! ====\n");
		printf("Deseja adicionar outro e-mail? (S/N): ");
		scanf(" %c", &resp);
	}
	while ((resp == 'S' || resp == 's') && nemails < MAXIMO);

	if (nemails == MAXIMO)
	{
		printf("Limite m�ximo de e-mails cadastrados atingido.\n");
	}
	else
	{
		printf("Cadastro de e-mails encerrado.\n");
	}
//mensagem de boas-vindas ,apresentei o projeto e tamb�m descrevi o objetivo dele.
	printf("================================== LOGIN FOI CONCLU�DO ====================================\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("--------------------  BEM-VINDO %s AO MULTI-SUPERMERCADO VIRTUAL  -------------------------\n", login);
	printf("-------  NOSSO SUPERMERCADO FOI PROJETADO PARA AJUDAR A HUMANIDADE E PRINCIPALMENTE -------\n");
	printf("---PARA AQUELAS PESSOAS QUE N�O PODEM SE LOCOMOVER, POR MOTIVOS PESSOAIS OU LOCACIONAIS.---\n");
	printf("----- VOC� VAI ENCONTRAR MUITOS PRODUTOS NESSE SITE, POIS NOSSA EMPRESA TEM PARCERIAS------\n");
	printf("----- COM OUTRAS INSTITUI��ES RELACIONADAS AO TRANSPORTE DE TODOS OS NOSSOS PRODUTOS. -----\n");
	printf("---- CONFIABILIDADE, PROTE��O E SEGURAN�A, S�O AS PRINCIPAIS PALAVRAS CHAVE QUE DEFINEM----\n");
	printf("NOSSO SUPERMERCADO VIRTUAL, ESTAMOS FELIZES EM RECEB�-LO(A) AQUI, EXPLORE NOSSOS CORREDORES\n");
	printf("--------------- REPLETOS DE PRODUTOS DE ALTA QUALIDADE, TENHA UM BOM DIA.------------------\n");

	struct Produto carrinho[MAX_PRODUTOS];  // Inicialize o carrinho
	int quantidade = 0;//quantidade dos produtos

	do  //exibir menu para ir para o sub menu
	{
		exibirMenu();
		scanf("%d", &opcao);

		switch (opcao)
		{
		case 1:
			do
			{


				// Submenu para o Op��o 1
				printf("SETORES DO SUPERMERCADO\n");
				printf("SELECIONE A LETRA CORRESPONDENTE AO SETOR:\n");
				printf("a - SETOR LATIC�NIOS\n");
				printf("b - SETOR FRUTAS, VERDURAS E LEGUMES\n");
				printf("c - SETOR HEGIENE E LIMPEZA\n");
				printf("d - SETOR PADARIA E CONFEITARIA\n");
				printf("e - SETOR BEBIDAS E FRIOS\n");
				printf("f - SETOR CEREAIS\n");
				printf("g - CAIXA ELETR�NICO PARA FINALIZAR A COMPRA\n");
				printf("r. Voltar ao menu principal\n");
				printf("Escolha uma subop��o: ");
				scanf(" %c", &opcao_submenu);

				switch (opcao_submenu)
				{
				case 'a'://TABELA DE PRODUTOS E PRE�OS.
					printf("Voc� selecionou o SETOR LATIC�NIOS.\n");
					printf("====================================================================================\n");
					printf("|----------------------------- PRODUTOS NA PRATELEIRA ------------------------------|\n");
					printf("====================================================================================\n");
					printf("|====================== 1. Leite           - R$ 3.00/emb.   ========================|\n");
					printf("|====================== 2. Sorvete         - R$ 15.00/caixa  ========================|\n");
					printf("|====================== 3. Manteiga        - R$ 7.00/emb.   ========================|\n");
					printf("|====================== 4. Ovos            - R$ 12.00/caixa ========================|\n");
					printf("|====================== 5. Creme de leite  - R$ 5.50/garr.  ========================|\n");
					printf("|====================== 6. Requeij�o       - R$ 11.00/kg    ========================|\n");
					printf("|====================== 7. Iogurte natural - R$ 6.00/caixa  ========================|\n");
					printf("|__________________________________________________________________________________|\n");
					break;
				case 'b'://TABELA DE PRODUTOS E PRE�OS.
					printf("Voc� selecionou o SETOR FRUTAS, VERDURAS E LEGUMES.\n");
					printf("====================================================================================\n");
					printf("|----------------------------- PRODUTOS NA PRATELEIRA ------------------------------|\n");
					printf("====================================================================================\n");
					printf("|======================== 8. Abacaxi    - R$ 2.00/kg     ==========================\n");
					printf("|======================== 9. Cenoura    - R$ 3.00/kg     ==========================\n");
					printf("|======================== 10. Goiaba     - R$ 8.00/caixa  ==========================\n");
					printf("|======================== 11. Uva        - R$ 4.00/caixa  ==========================\n");
					printf("|======================== 12. Alface     - R$ 5.00/emb.   ==========================\n");
					printf("|======================== 13. Morango    - R$ 2.00/caixa  ==========================\n");
					printf("|======================== 14. Banana     - R$ 2.00/caixa  ==========================\n");
					printf("|__________________________________________________________________________________|\n");
					break;
				case 'c'://TABELA DE PRODUTOS E PRE�OS.
					printf("Voc� selecionou o SETOR HIGIENE E LIMPEZA.\n");
					printf("====================================================================================\n");
					printf("|----------------------------- PRODUTOS NA PRATELEIRA ------------------------------|\n");
					printf("====================================================================================\n");
					printf("|======================== 15. Sabonete        - R$ 2.00/caixa  =======================\n");
					printf("|======================== 16. Detergentes     - R$ 3.00/emb.   =======================\n");
					printf("|======================== 17. Desinfetantes   - R$ 7.00/emb.   =======================\n");
					printf("|======================== 18. Papel Higi�nico - R$ 4.00/emb.   =======================\n");
					printf("|======================== 19. Escovas         - R$ 2.00/emb.   =======================\n");
					printf("|======================== 20. Vassouras       - R$ 18.00/emb.   =======================\n");
					printf("|======================== 21. Esponjas        - R$ 2.00/caixa  =======================\n");
					printf("|__________________________________________________________________________________|\n");
					break;
				case 'd'://TABELA DE PRODUTOS E PRE�OS.
					printf("Voc� selecionou o SETOR PADARIA E CONFEITARIA.\n");
					printf("====================================================================================\n");
					printf("|----------------------------- PRODUTOS NA PRATELEIRA ------------------------------|\n");
					printf("====================================================================================\n");
					printf("|======================== 22. Bolo        - R$ 7.00/caixa  ==========================\n");
					printf("|======================== 23. Donuts      - R$ 6.00/emb.   ==========================\n");
					printf("|======================== 24. Torta       - R$ 13.00/emb.  ==========================\n");
					printf("|======================== 25. P�es        - R$ 3.00/kg.    ==========================\n");
					printf("|======================== 26. Brigadeiros - R$ 14.00/caixa ==========================\n");
					printf("|======================== 27. Biscoitos   - R$ 6.00/caixa  ==========================\n");
					printf("|======================== 28. Croissants  - R$ 9.00/caixa  ==========================\n");
					printf("|__________________________________________________________________________________|\n");
					break;
				case 'e'://TABELA DE PRODUTOS E PRE�OS.
					printf("Voc� selecionou o SETOR BEBIDAS E FRIOS.\n");
					printf("====================================================================================\n");
					printf("|----------------------------- PRODUTOS NA PRATELEIRA ------------------------------|\n");
					printf("====================================================================================\n");
					printf("|====================== 29. Cerveja          - R$ 11.00/caixa  =======================\n");
					printf("|====================== 30. Refrigerante     - R$ 6.00/emb.    =======================\n");
					printf("|====================== 31. Carne            - R$ 13.00/kg.    =======================\n");
					printf("|====================== 32. Peito de Frango  - R$ 8.00/kg.     =======================\n");
					printf("|====================== 33. Massa de pastel  - R$ 10.00/emb.   =======================\n");
					printf("|====================== 34. Salsicha         - R$ 6.00/kg.     =======================\n");
					printf("|====================== 35. Suco de fruta    - R$ 5.00/kg.     =======================\n");
					printf("|__________________________________________________________________________________|\n");
					break;
				case 'f'://TABELA DE PRODUTOS E PRE�OS.
					printf("Voc� selecionou o SETOR CEREAIS.\n");
					printf("====================================================================================\n");
					printf("|----------------------------- PRODUTOS NA PRATELEIRA ------------------------------|\n");
					printf("====================================================================================\n");
					printf("|====================== 36. Arroz               - R$ 7.00/emb.   ==========================\n");
					printf("|====================== 37. Flocos de aveia     - R$ 4.00/emb.   =========================\n");
					printf("|====================== 38. Feij�o              - R$ 5.00/emb.   ==========================\n");
					printf("|====================== 39. Farinha de trigo    - R$ 8.00/kg.    ==========================\n");
					printf("|====================== 40. Cereal matinal      - R$ 16.00/emb.  ==========================\n");
					printf("|====================== 41. Massa sem fermento  - R$ 6.00/caixa  ==========================\n");
					printf("|====================== 42. Pipoca de milho     - R$ 9.00/caixa  ==========================\n");
					printf("|__________________________________________________________________________________|\n");
					break;
				case 'g': // Novo case para pagamentos
					realizarPagamento(carrinho, quantidade);
					break;
				case 'r':
					printf("Voltando ao menu principal.\n");
					limpartela();
					break;
				default:
					printf("Op��o inv�lida.\n");
					break;
				}

				while (opcao_submenu != 'r')
				{
					char nome_produto[100];
					float preco_produto = 0.0;
					int quantidade_produto;
					//Permite escolher os produtos e solicita ao usu�rio que insira o n�mero
					//do produto ou 'r' para sair do setor e tamb�m a quantidade desejada.


					printf("Escolha um produto pelo n�mero ou digite 'r' para sair deste setor: ");
					scanf(" %s", nome_produto);

// Solicita ao usu�rio para escolher produtos pelo n�mero.
					if (nome_produto[0] == 'r' && nome_produto[1] == '\0')
					{
						break; // Voltar ao menu principal
					}
// / Solicita ao usu�rio para escolher produtos e quantidade
					// ...
					printf("Informe a quantidade desejada: \n");
					printf("OU SE DESEJA RETIRAR O PRODUTO AGORA DO SEU CARINHO DIGITE 0 AQUI:");
					scanf("%d", &quantidade_produto);


// Verifica se o usu�rio quer voltar ao menu principal
					if (nome_produto[0] == 'r' && nome_produto[1] == '\0')
					{
						break; // Voltar ao menu principal
					}
//Converte a string nome_produto em um valor inteiro usando atoi, para melhor funcionamento 
					int produto_index = atoi(nome_produto) - 1; 
					// a subtra��o ajusta o indice , assim a lista come�a um 1.
//Asssim , o atoi converte a string  em valores inteiros que representa o �ndice do produto no vetor de pre�os, de acordo com o produto da lista , tipo leite = 1 = 3,00.
// O (index) � usado  acessar o vetor precos e obter o pre�o correspondente ao produto escolhido pelo usu�rio.
					if (produto_index >= 0 && produto_index < N)
					{
						preco_produto = precos[produto_index];
						// Adiciona o produto ao carrinho
						quantidade = adicionarProduto(carrinho, quantidade, nome_produto, preco_produto, quantidade_produto);
					}
					else
					{
						printf("Produto n�o encontrado.\n");
					}
// Verifica se o nome do produto � v�lido .

				}

				// Calcular o total do carrinho.
				float total = calcularTotal(carrinho, quantidade);
				printf("Total do carrinho: R$%.2f\n", total);
//formata��o em duas casas decimais .
			}
			while (opcao_submenu != 'r');
			break;

		case 2:
			//cadastramento para sorteio idade e nome.
			printf("Op��o 2 selecionada Cadastro.\n");
			printf("Informe primeiro seu nome para o sistema te cadastrar no sorteio\n");
			scanf("%s", clientes[qtd].pessoa);

			printf("Informe sua idade:\n");
			scanf("%d", &clientes[qtd].idade);
			clientes[qtdClientes].cadastrado = 1;

			// Aumente a quantidade de clientes cadastrados.
			qtdClientes++;
			// finalizar cadastro.
			printf("Voc� est� cadastrado no sorteio!!!!\n");
			printf("Selecione o n�memo correspondente ao menu sorteio e Boa sorte !!!!!!\n");
			break;

		case 3:
			// submenu para edi��o de nome ou idade.
			printf("Escolha o que deseja editar:\n");
			printf("1 - Editar nome\n");
			printf("2 - Editar idade\n");
			scanf("%d", &escolha);

			switch (escolha)
			{
			case 1:// para mudar o nome.
				printf("Digite o novo nome: ");
				scanf("%s", clientes[qtd - 1].pessoa);
				printf("Nome atualizado com sucesso!\n");
				break;
			case 2:// para mudar a idade.
				printf("Digite a nova idade: ");
				scanf("%d", &clientes[qtd - 1].idade);
				printf("Idade atualizada com sucesso!\n");
				break;
			default:
				printf("Op��o inv�lida.\n");
			}
			break;


		case 4:
			printf("Op��o 4 selecionada Excluir.\n");
			if (qtdClientes > 0)
			{
				printf("Informe o nome do cliente que deseja excluir: ");
				char nomeexcluir[30];
				scanf("%s", nomeexcluir);

				int clienteEncontrado = -1;

				for (int i = 0; i < qtdClientes; i++)
				{
					if (strcmp(nomeexcluir, clientes[i].pessoa) == 0)
					{
						clienteEncontrado = i;
						break;
					}
				}

				if (clienteEncontrado != -1)
				{
					if (clientes[clienteEncontrado].cadastrado == 1)
					{
						// Remova o cliente, movendo todos os clientes subsequentes para tr�s
						for (int i = clienteEncontrado; i < qtdClientes - 1; i++)
						{
							clientes[i] = clientes[i + 1];
						}
						// Atualize a quantidade de clientes
						qtdClientes--;
						printf("Cliente %s exclu�do com sucesso.\n", nomeexcluir);
					}
					else
					{
						printf("Cliente n�o estava cadastrado para o sorteio,ent�o ele n�o pode ser exclu�do.\n");
					}
				}
				else
				{
					printf("Cliente n�o encontrado.\n");
				}
			}
			else
			{
				printf("N�o tem nenhum clientes cadastrados.\n");
			}
			break;


		case 5:
			//listagem dos produtos comprados
			printf("Op��o 5 selecionada Listar produtos comprados.\n");
			listagem(carrinho, quantidade);

			break;


		case 6:
			//chamar a fun��o do sorteio.
			printf("Op��o 6 selecionada (Sorteio).\n");
			printf("OL� %s SEJA BEM VINDO AO NOSSO SORTEIO DI�RIO!!!\n" , clientes[qtd].pessoa);
			realizarSorteio();
			break;
		case 7:
			printf("Op��o 7 selecionada (Sair).\n");
			break;
		default:
			printf("Op��o inv�lida. Tente novamente.\n");
		}

	}
	while (opcao != 7);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar os dados do investidor
typedef struct {
  char nome[100];
  char cpf[12];
  char senha[7];
  double saldo;
  double bitcoin;
  double ethereum;
  double ripple;
} Investidor;

// Estrutura para armazenar as informações de criptomoeda
typedef struct {
  char nome[20];
  double cotacao;
  double taxa_compra;
  double taxa_venda;
} Criptomoeda;

// Funções
void painel_inicial();
void menu_administrador();
void menu_investidor(Investidor *investidor);
void login_administrador();
void login_investidor();
void cadastrar_investidor();
void excluir_investidor();
void consultar_saldo_investidor();
void consultar_extrato_investidor();
void cadastrar_criptomoeda();
void excluir_criptomoeda();
void atualizar_cotacao(Investidor *conta);
void carregar_dados_investidor(Investidor *investidor, const char *cpf);
void salvar_dados_investidor(const Investidor *investidor);
void salvar_transacao(const char *cpf, const char *tipo, const char *detalhes);
double random_double(double min, double max);

// Função para gerar um valor aleatório entre min e max
double random_double(double min, double max) {
  return min + (rand() / (RAND_MAX / (max - min)));
}

// Função inicial para escolher o painel de acesso
void painel_inicial() {
  int escolha;

  printf("\n--- SISTEMA DE INVESTIMENTOS ---\n");
  printf("1. Painel Administrador\n");
  printf("2. Painel Investidor\n");
  printf("Escolha uma opção: ");
  scanf("%d", &escolha);

  switch (escolha) {
    case 1:
      login_administrador();
      break;
    case 2:
      login_investidor();
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      painel_inicial();
  }
}

// Função de login do administrador
void login_administrador() {
  char cpf[12], senha[7];

  printf("Insira seu CPF de administrador: ");
  scanf("%11s", cpf);
  printf("Insira sua senha de administrador: ");
  scanf("%6s", senha);

  if (strcmp(cpf, "adminCPF") == 0 && strcmp(senha, "adminSenha") == 0) {
    printf("Login de administrador bem-sucedido.\n");
    menu_administrador();
  } else {
    printf("CPF ou senha de administrador inválidos.\n");
    painel_inicial();
  }
}

// Função de login do investidor
void login_investidor() {
  char cpf[12], senha[7];
  Investidor investidor;

  printf("Insira seu CPF: ");
  scanf("%11s", cpf);
  printf("Insira sua senha de 6 dígitos: ");
  scanf("%6s", senha);

  carregar_dados_investidor(&investidor, cpf);

  if (strlen(investidor.cpf) != 0 && strcmp(investidor.senha, senha) == 0) {
    printf("Login de investidor bem-sucedido.\n");
    menu_investidor(&investidor);
  } else {
    printf("CPF ou senha de investidor inválidos.\n");
    painel_inicial();
  }
}

// Função para exibir o menu do administrador
void menu_administrador() {
  int opcao;

  while (1) {
    printf("\n--- MENU ADMINISTRADOR ---\n");
    printf("1. Cadastrar novo investidor\n");
    printf("2. Excluir investidor\n");
    printf("3. Consultar saldo de um investidor\n");
    printf("4. Consultar extrato de um investidor\n");
    printf("5. Cadastrar nova criptomoeda\n");
    printf("6. Excluir criptomoeda\n");
    printf("7. Atualizar cotação das criptomoedas\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        cadastrar_investidor();
        break;
      case 2:
        excluir_investidor();
        break;
      case 3:
        consultar_saldo_investidor();
        break;
      case 4:
        consultar_extrato_investidor();
        break;
      case 5:
        cadastrar_criptomoeda();
        break;
      case 6:
        excluir_criptomoeda();
        break;
      case 7:
        atualizar_cotacao(NULL);
        break;
      case 8:
        printf("Saindo...\n");
        exit(0);
      default:
        printf("Opção inválida.\n");
    }
  }
}

// Função para exibir o menu do investidor
void menu_investidor(Investidor *investidor) {
  int opcao;

  while (1) {
    printf("\n--- MENU INVESTIDOR ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("5. Comprar criptomoedas\n");
    printf("6. Vender criptomoedas\n");
    printf("7. Atualizar cotação\n");
    printf("8. Sair\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        printf("Saldo atual: R$%.2f\n", investidor->saldo);
        break;
      case 2:
        consultar_extrato_investidor();
        break;
      case 3:
        // Função de depósito para investidor
        break;
      case 4:
        // Função de saque para investidor
        break;
      case 5:
        // Função de compra de criptomoedas para investidor
        break;
      case 6:
        // Função de venda de criptomoedas para investidor
        break;
      case 7:
        atualizar_cotacao(investidor);
        break;
      case 8:
        printf("Saindo do painel de investidor...\n");
        painel_inicial();
        break;
      default:
        printf("Opção inválida.\n");
    }
  }
}

// Função para cadastrar um novo investidor
void cadastrar_investidor() {
  Investidor investidor;
  FILE *arquivo = fopen("investidores.txt", "a");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de investidores.\n");
    return;
  }

  printf("Informe o nome do investidor: ");
  scanf(" %[^\n]", investidor.nome);
  printf("Informe o CPF do investidor: ");
  scanf("%11s", investidor.cpf);
  printf("Informe a senha de 6 dígitos: ");
  scanf("%6s", investidor.senha);

  investidor.saldo = 0;
  investidor.bitcoin = 0;
  investidor.ethereum = 0;
  investidor.ripple = 0;

  fprintf(arquivo, "%s,%s,%s,%.2f,%.4f,%.4f,%.4f\n", investidor.nome, investidor.cpf, investidor.senha, investidor.saldo, investidor.bitcoin, investidor.ethereum, investidor.ripple);
  fclose(arquivo);

  printf("Investidor cadastrado com sucesso.\n");
}

// Função para excluir um investidor
void excluir_investidor() {
  char cpf[12];
  char confirma;
  Investidor investidor;
  FILE *arquivo, *temp;

  printf("Informe o CPF do investidor a ser excluído: ");
  scanf("%11s", cpf);

  carregar_dados_investidor(&investidor, cpf);
  if (strlen(investidor.cpf) == 0) {
    printf("Investidor não encontrado.\n");
    return;
  }

  printf("Confirma a exclusão de %s (CPF: %s)? (s/n): ", investidor.nome, investidor.cpf);
  scanf(" %c", &confirma);

  if (confirma == 's') {
    arquivo = fopen("investidores.txt", "r");
    temp = fopen("temp.txt", "w");

    while (fscanf(arquivo, "%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf\n", investidor.nome, investidor.cpf, investidor.senha, &investidor.saldo, &investidor.bitcoin, &investidor.ethereum, &investidor.ripple) != EOF) {
      if (strcmp(investidor.cpf, cpf) != 0) {
        fprintf(temp, "%s,%s,%s,%.2f,%.4f,%.4f,%.4f\n", investidor.nome, investidor.cpf, investidor.senha, investidor.saldo, investidor.bitcoin, investidor.ethereum, investidor.ripple);
      }
    }

    fclose(arquivo);
    fclose(temp);

    remove("investidores.txt");
    rename("temp.txt", "investidores.txt");

    printf("Investidor excluído com sucesso.\n");
  } else {
    printf("Operação cancelada.\n");
  }
}

// Função para consultar o saldo de um investidor
void consultar_saldo_investidor() {
  char cpf[12];
  Investidor investidor;

  printf("Informe o CPF do investidor: ");
  scanf("%11s", cpf);

  carregar_dados_investidor(&investidor, cpf);
  if (strlen(investidor.cpf) == 0) {
    printf("Investidor não encontrado.\n");
    return;
  }

  printf("Saldo de %s (CPF: %s): R$%.2f\n", investidor.nome, investidor.cpf, investidor.saldo);
}

// Função para consultar o extrato de um investidor
void consultar_extrato_investidor() {
  char cpf[12];
  char linha[256];
  FILE *arquivo;

  printf("Informe o CPF do investidor: ");
  scanf("%11s", cpf);

  snprintf(linha, sizeof(linha), "%s_extrato.txt", cpf);
  arquivo = fopen(linha, "r");

  if (arquivo == NULL) {
    printf("Extrato não encontrado para o CPF informado.\n");
    return;
  }

  printf("\n--- EXTRATO DE %s ---\n", cpf);
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    printf("%s", linha);
  }
  fclose(arquivo);
}

// Função para carregar os dados de um investidor
void carregar_dados_investidor(Investidor *investidor, const char *cpf) {
  FILE *arquivo = fopen("investidores.txt", "r");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de investidores.\n");
    return;
  }

  while (fscanf(arquivo, "%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf\n", investidor->nome, investidor->cpf, investidor->senha, &investidor->saldo, &investidor->bitcoin, &investidor->ethereum, &investidor->ripple) != EOF) {
    if (strcmp(investidor->cpf, cpf) == 0) {
      fclose(arquivo);
      return;
    }
  }

  fclose(arquivo);
  investidor->cpf[0] = '\0';  // Indica que o investidor não foi encontrado
}

// Função para cadastrar uma nova criptomoeda
void cadastrar_criptomoeda() {
  Criptomoeda cripto;
  FILE *arquivo = fopen("criptomoedas.txt", "a");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  printf("Informe o nome da criptomoeda: ");
  scanf("%19s", cripto.nome);
  printf("Informe a cotação inicial: ");
  scanf("%lf", &cripto.cotacao);
  printf("Informe a taxa de compra (em decimal, ex: 0.02 para 2%%): ");
  scanf("%lf", &cripto.taxa_compra);
  printf("Informe a taxa de venda (em decimal, ex: 0.02 para 2%%): ");
  scanf("%lf", &cripto.taxa_venda);

  fprintf(arquivo, "%s,%.2f,%.2f,%.2f\n", cripto.nome, cripto.cotacao, cripto.taxa_compra, cripto.taxa_venda);
  fclose(arquivo);

  printf("Criptomoeda cadastrada com sucesso.\n");
}

// Função para excluir uma criptomoeda
void excluir_criptomoeda() {
  char nome[20];
  char confirma;
  Criptomoeda cripto;
  FILE *arquivo, *temp;

  printf("Informe o nome da criptomoeda a ser excluída: ");
  scanf("%19s", nome);

  arquivo = fopen("criptomoedas.txt", "r");
  temp = fopen("temp.txt", "w");

  if (!arquivo || !temp) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  int encontrou = 0;
  while (fscanf(arquivo, "%[^,],%lf,%lf,%lf\n", cripto.nome, &cripto.cotacao, &cripto.taxa_compra, &cripto.taxa_venda) != EOF) {
    if (strcmp(cripto.nome, nome) == 0) {
      printf("Criptomoeda encontrada: %s - Cotação: %.2f - Taxa Compra: %.2f - Taxa Venda: %.2f\n", cripto.nome, cripto.cotacao, cripto.taxa_compra, cripto.taxa_venda);
      printf("Confirma a exclusão? (s/n): ");
      scanf(" %c", &confirma);

      if (confirma == 's') {
        encontrou = 1;
        printf("Criptomoeda excluída com sucesso.\n");
      } else {
        fprintf(temp, "%s,%.2f,%.2f,%.2f\n", cripto.nome, cripto.cotacao, cripto.taxa_compra, cripto.taxa_venda);
      }
    } else {
      fprintf(temp, "%s,%.2f,%.2f,%.2f\n", cripto.nome, cripto.cotacao, cripto.taxa_compra, cripto.taxa_venda);
    }
  }

  if (!encontrou) {
    printf("Criptomoeda não encontrada.\n");
  }

  fclose(arquivo);
  fclose(temp);
  remove("criptomoedas.txt");
  rename("temp.txt", "criptomoedas.txt");
}

// Função para atualizar a cotação das criptomoedas
void atualizar_cotacao(Investidor *conta) {
  FILE *arquivo = fopen("criptomoedas.txt", "r+");
  Criptomoeda cripto;

  if (!arquivo) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  printf("Atualizando cotações das criptomoedas...\n");

  while (fscanf(arquivo, "%[^,],%lf,%lf,%lf\n", cripto.nome, &cripto.cotacao, &cripto.taxa_compra, &cripto.taxa_venda) != EOF) {
    fseek(arquivo, -((long)sizeof(cripto)), SEEK_CUR);
    cripto.cotacao = random_double(cripto.cotacao * 0.9, cripto.cotacao * 1.1);
    fprintf(arquivo, "%s,%.2f,%.2f,%.2f\n", cripto.nome, cripto.cotacao, cripto.taxa_compra, cripto.taxa_venda);
  }

  fclose(arquivo);
  printf("Cotações atualizadas com sucesso.\n");
}

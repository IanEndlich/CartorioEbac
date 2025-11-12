#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// ----------------------
// Função: Registrar novo usuário
// ----------------------
int registro() 
{
    char cpf[40], nome[100], sobrenome[100], cargo[100], arquivo[50];
    FILE *file;

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%39s", cpf);
    fflush(stdin); // limpa buffer (não padronizado, mas comum no Windows)

    // Cria nome do arquivo (ex: "12345678900.txt")
    sprintf(arquivo, "%s.txt", cpf);

    file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo!\n");
        system("pause");
        return 1;
    }

    // Limpar a linha remanescente antes de usar fgets
    getchar(); // remove o '\n' deixado por scanf

    printf("Digite o nome a ser cadastrado: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // remove \n

    printf("Digite o sobrenome a ser cadastrado: ");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    sobrenome[strcspn(sobrenome, "\n")] = 0;

    printf("Digite o cargo a ser cadastrado: ");
    fgets(cargo, sizeof(cargo), stdin);
    cargo[strcspn(cargo, "\n")] = 0;

    // Grava tudo em uma linha
    fprintf(file, "CPF:%s, Nome:%s, Sobrenome:%s, Cargo:%s", cpf, nome, sobrenome, cargo);
    fclose(file);

    printf("\nCadastro salvo com sucesso no arquivo '%s'!\n\n", arquivo);
    system("pause");
    return 0;
}

// ----------------------
// Função: Consultar usuário por CPF
// ----------------------
int consulta() {
    char cpf[40], arquivo[50], conteudo[300];
    FILE *file;

    printf("Digite o CPF a ser consultado: ");
    scanf("%39s", cpf);

    sprintf(arquivo, "%s.txt", cpf);

    file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("\n? Usuário com CPF '%s' não encontrado!\n\n", cpf);
        system("pause");
        return 1;
    }

    printf("\n?? Informações do usuário:\n");
    while (fgets(conteudo, sizeof(conteudo), file) != NULL) {
        printf("%s\n", conteudo);
    }

    fclose(file);
    printf("\nConsulta concluída!\n\n");
    system("pause");
    return 0;
}

// ----------------------
// Função: Deletar registro
// ----------------------
int deletar() 
{
    char cpf[40], arquivo[50];

    printf("Digite o CPF a ser deletado: ");
    scanf("%39s", cpf);

    sprintf(arquivo, "%s.txt", cpf);

    if (remove(arquivo) == 0) {
        printf("\n? Registro com CPF '%s' foi deletado com sucesso!\n\n", cpf);
    } else {
        printf("\n? Erro: Registro com CPF '%s' não foi encontrado!\n\n", cpf);
    }

    system("pause");
    return 0;
}

// ----------------------
// Função principal (Menu)
// ----------------------
int main() {
    int opcao = 0;
    char senhadigitada[20];

    printf("===== CARTÓRIO DE MANGUINHOS =====\n\n");
    printf("Login de administrador\n\nDigite a sua senha: ");
    scanf("%s", senhadigitada);

    // Correção da comparação de strings
    if (strcmp(senhadigitada, "admin") == 0) {
        // Senha correta
        setlocale(LC_ALL, "Portuguese");

        do {
            system("cls");

            printf("===== CARTÓRIO DE MANGUINHOS =====\n\n");
            printf("1 - Registrar Nomes\n");
            printf("2 - Consultar Nomes\n");
            printf("3 - Deletar Nomes\n");
            printf("0 - Sair\n");
            printf("\nEscolha uma opção: ");
            if (scanf("%d", &opcao) != 1) {
                // entrada inválida: limpar buffer e continuar
                while (getchar() != '\n');
                opcao = -1;
            }

            system("cls");

            switch (opcao) {
                case 1:
                    registro();
                    break;
                case 2:
                    consulta();
                    break;
                case 3:
                    deletar();
                    break;
                case 0:
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                    system("pause");
                    break;
            }
        } while (opcao != 0);
    } 
    else {
        // Senha incorreta
        printf("\nSenha incorreta! Acesso negado.\n");
        system("pause");
    }

    return 0;
}




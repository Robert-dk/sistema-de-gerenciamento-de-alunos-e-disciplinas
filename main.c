/*
 * Sistema de gerenciamento de alunos e disciplinas
 * Autor: Robert Emanuel
 * Data de Criação: 12-06-2024
 * Versão: 2.0
 * Descrição: Neste projeto, o sistema funciona gerenciando os alunos com alocação dinâmica de memória e,
listas encadeadas para as disciplinas. Implementei tratamento de erros, ordenação por RGM (bubblesort) e,
me atentei às boas práticas de gerenciamento de memória para evitar vazamentos.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define TAMANHO_NOME 50
#define TAMANHO_RGM 50
#define CAPACIDADE_INICIAL 10

// estruturas
typedef struct {
    char nome[TAMANHO_NOME];
    float nota;
} Dados_disciplina;

typedef struct Disciplina {
    Dados_disciplina disciplina;
    struct Disciplina *prox;
} Disciplinas;

typedef struct {
    char rgm[TAMANHO_RGM];
    char nome[TAMANHO_NOME]; 
    Disciplinas *disciplinas;
} Dados_aluno;

typedef struct {
    Dados_aluno *pessoas;
    int contador;
    int capacidade;
} Alunos;

// funcoes para alunos
Alunos criarLista();
int inserirAluno(Alunos *lista, Dados_aluno aluno);
int removerAluno(Alunos *lista, int pos);
void mostrarTodasPessoas(Alunos *lista);
void limparListaAlunos(Alunos *lista);

// funcoes para disciplinas
Disciplinas *criarListaDisciplinas();
Disciplinas *inserirDisciplina(Disciplinas *lista, Dados_disciplina disciplina);
int removerDisciplina(Disciplinas **lista, const char *nomeDisciplina); // Remoção por nome
void mostrarDisciplinasAluno(Disciplinas *lista);
void limparListaDisciplinas(Disciplinas *lista);

// funcoes auxiliares
int encontrarAlunoPorRGM(Alunos *lista, const char *rgm);
void loopAdicionarAlunos(Alunos *lista);
void loopRemoverAlunos(Alunos *lista);
void loopAdicionarDisciplinas(Alunos *lista);
void loopMostrarDisciplinas(Alunos *lista);
void loopRemoverDisciplinas(Alunos *lista);
void bubblesort(Alunos *listaAlunos);

// codigo principal, onde ficara o menu
int main() {
    Alunos alunos = criarLista();
    int opcao;
    printf("-----------------\n");
    printf("--- BEM VINDO ---\n");
    printf("-----------------\n");
    do {
        printf("\n----- MENU -----\n");
        printf("1. Adicionar Aluno\n");
        printf("2. Remover Aluno\n");
        printf("3. Listar Alunos\n");
        printf("4. Adicionar Disciplina\n");
        printf("5. Remover Disciplina\n");
        printf("6. Listar Disciplinas de um Aluno\n");
        printf("0. Sair\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Digite um número.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            opcao = -1; // Força a repetição do loop
            continue;
        }

        switch (opcao) {
            case 0:
                printf("Encerrando o programa.\n");
                break;
            case 1:
                loopAdicionarAlunos(&alunos);
                break;
            case 2:
                loopRemoverAlunos(&alunos);
                break;
            case 3:
                mostrarTodasPessoas(&alunos);
                sleep(3);
                break;
            case 4:
                loopAdicionarDisciplinas(&alunos);
                break;
            case 5:
                loopRemoverDisciplinas(&alunos);
                break;
            case 6:
                loopMostrarDisciplinas(&alunos);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    limparListaAlunos(&alunos); 
    return 0;
}

// funcoes para alunos
// criar a lista de alunos
Alunos criarLista() {
    Alunos lista;
    lista.contador = 0;
    lista.capacidade = CAPACIDADE_INICIAL;
    lista.pessoas = (Dados_aluno *)malloc(lista.capacidade * sizeof(Dados_aluno));
    if (lista.pessoas == NULL) {
        perror("Erro crítico: Memória insuficiente para armazenar os alunos.");
        exit(1);
    }
    return lista;
}

// codigo da funcao para inserir alunos
int inserirAluno(Alunos *lista, Dados_aluno aluno) {
    if (lista->contador == lista->capacidade) {
        lista->capacidade *= 2;
        Dados_aluno *temp = (Dados_aluno *)realloc(lista->pessoas, lista->capacidade * sizeof(Dados_aluno));
        if (temp == NULL) {
            perror("Erro ao realocar memória para a lista de alunos");
            exit(1);
        }
        lista->pessoas = temp;
    }
    lista->pessoas[lista->contador] = aluno;
    lista->contador++;
    return 1;
}

// codigo da funcao para remover alunos
int removerAluno(Alunos *lista, int pos) {
    if (pos < 0 || pos >= lista->contador) {
        return -1;
    }

    limparListaDisciplinas(lista->pessoas[pos].disciplinas); // Libera as disciplinas do aluno removido
    if (pos < lista->contador - 1) {
        lista->pessoas[pos] = lista->pessoas[lista->contador - 1];
    }
    lista->contador--;
    return 0;
}

// codigo da funcao para mostrar os alunos
void mostrarTodasPessoas(Alunos *lista) {
    if (lista->contador == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n--- LISTA DE ALUNOS ---\n");
    for (int i = 0; i < lista->contador; i++) {
        printf("Nome: %s\n", lista->pessoas[i].nome);
        printf("RGM: %s\n", lista->pessoas[i].rgm);
        printf("Disciplinas:\n");
        mostrarDisciplinasAluno(lista->pessoas[i].disciplinas);
        printf("\n");
    }
}

// codigo da funcao para limpar a lista de alunos
void limparListaAlunos(Alunos *lista) {
    if (lista->pessoas != NULL) {
        for (int i = 0; i < lista->contador; i++) {
            limparListaDisciplinas(lista->pessoas[i].disciplinas);
        }
        free(lista->pessoas);
    }
}

// funcoes para disciplinas
// criar lista das disciplinas
Disciplinas *criarListaDisciplinas() {
    return NULL;
}

// codigo da funcao para inserir disciplinas
Disciplinas *inserirDisciplina(Disciplinas *lista, Dados_disciplina disciplina) {
    Disciplinas *novoNo = (Disciplinas *)malloc(sizeof(Disciplinas));
    if (novoNo == NULL) {
        perror("Erro crítico: Memória insuficiente para armazenar as disciplinas.");
        exit(1);
    }
    novoNo->disciplina = disciplina;
    novoNo->prox = lista;
    return novoNo;
}

// codigo da funcao para remover disciplinas
int removerDisciplina(Disciplinas **lista, const char *nomeDisciplina) {
    Disciplinas *atual = *lista;
    Disciplinas *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->disciplina.nome, nomeDisciplina) == 0) {
            if (anterior == NULL) {
                *lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return 0; 
        }
        anterior = atual;
        atual = atual->prox;
    }
    return -1; 
}

// codigo da funcao para mostrar as disciplinas
void mostrarDisciplinasAluno(Disciplinas *lista)
{
    if (lista == NULL) {
        printf("Nenhuma disciplina cadastrada para este aluno.\n");
        return;
    }

    while (lista != NULL) {
        printf("- Disciplina: %s, Nota: %.2f\n", lista->disciplina.nome, lista->disciplina.nota);
        lista = lista->prox;
    }
}

// codigo da funcao para limpar a lista de disciplinas
void limparListaDisciplinas(Disciplinas *lista) {
    while (lista != NULL) {
        Disciplinas *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

//funcoes auxiliares
// codigo da funcao para procurar aluno pelo rgm
int encontrarAlunoPorRGM(Alunos *lista, const char *rgm) {
    for (int i = 0; i < lista->contador; i++) {
        if (strcmp(lista->pessoas[i].rgm, rgm) == 0) {
            return i;
        }
    }
    return -1;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// codigo da funcao para adicionar alunos
void loopAdicionarAlunos(Alunos *lista) {
    Dados_aluno tempAluno;
    int continuar = 1;

    while (continuar) {
        printf("Digite o RGM do aluno: ");
        if (scanf(" %49s", tempAluno.rgm) != 1) {
            printf("Entrada inválida para RGM.\n");
            limparBuffer(); // Limpa o buffer em caso de erro de scanf
            continue;
        }
        limparBuffer(); // Limpa o buffer APÓS o scanf do RGM

        printf("Digite o nome do aluno: ");
        if (fgets(tempAluno.nome, TAMANHO_NOME, stdin) == NULL) {
            perror("Erro ao ler o nome do aluno");
            exit(1); // Ou trate o erro de outra forma apropriada
        }
        tempAluno.nome[strcspn(tempAluno.nome, "\n")] = 0;

        tempAluno.disciplinas = criarListaDisciplinas();

        if (inserirAluno(lista, tempAluno)) {
            printf("Aluno inserido com sucesso!\n");
        } else {
            printf("Erro ao inserir aluno.\n");
            limparListaDisciplinas(tempAluno.disciplinas);
            break;
        }

        printf("Digite 1 para adicionar outro aluno ou 0 para voltar ao menu: ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada inválida.\n");
            limparBuffer(); // Limpa o buffer em caso de erro no scanf
            continuar = 0;
        }
        limparBuffer(); // Limpa o buffer APÓS o scanf da opção continuar
    }
    if (lista->contador > 1) {
        bubblesort(lista);
    }
}

// codigo da funcao para remover alunos
void loopRemoverAlunos(Alunos *lista) {
    char rgm[TAMANHO_RGM];
    int continuar = 1;

    while (continuar) {
        printf("Digite o RGM do aluno que deseja remover: ");
        if (scanf(" %49s", rgm) != 1) {
            printf("Entrada inválida para RGM.\n");
            while (getchar() != '\n'); 
            continue;
        }

        int pos = encontrarAlunoPorRGM(lista, rgm);
        if (pos != -1) {
            if(removerAluno(lista, pos) == 0){ 
                printf("Aluno removido com sucesso!\n");
            }
        } else {
            printf("RGM não encontrado!\n");
        }

        printf("Digite 1 para remover outro aluno ou 0 para voltar ao menu: ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n');
            continuar = 0;
        }
    }
}

// codigo da funcao para adicionar disciplinas
void loopAdicionarDisciplinas(Alunos *lista) {
    Dados_disciplina tempDisciplina;
    char rgm[TAMANHO_RGM];

    printf("Digite o RGM do aluno que deseja adicionar disciplinas: ");
    if (scanf(" %49s", rgm) != 1) {
        printf("Entrada inválida para RGM.\n");
        while (getchar() != '\n');
        return;
    }

    int posAluno = encontrarAlunoPorRGM(lista, rgm);
    if (posAluno == -1) {
        printf("RGM não encontrado.\n");
        return;
    }

    int continuar = 1;
    while (continuar) {
        printf("Digite o nome da disciplina: ");
        if (scanf(" %49s", tempDisciplina.nome) != 1) {
            printf("Entrada inválida para o nome da disciplina.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Digite a nota da disciplina: ");
        if (scanf("%f", &tempDisciplina.nota) != 1) {
            printf("Entrada inválida para a nota.\n");
            while (getchar() != '\n');
            continue;
        }

        lista->pessoas[posAluno].disciplinas = inserirDisciplina(lista->pessoas[posAluno].disciplinas, tempDisciplina);
        mostrarDisciplinasAluno(lista->pessoas[posAluno].disciplinas);

        printf("Digite 1 para adicionar outra disciplina ou 0 para voltar ao menu: ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n');
            continuar = 0;
        }
    }
}

// codigo da funcao para mostrar disciplinas
void loopMostrarDisciplinas(Alunos *lista) {
    char rgm[TAMANHO_RGM];

    printf("Digite o RGM do aluno que deseja mostrar disciplinas: ");
    if (scanf(" %49s", rgm) != 1) {
        printf("Entrada inválida para RGM.\n");
        while (getchar() != '\n');
        return;
    }

    int posAluno = encontrarAlunoPorRGM(lista, rgm);
    if (posAluno == -1) {
        printf("RGM não encontrado.\n");
        return;
    }

    mostrarDisciplinasAluno(lista->pessoas[posAluno].disciplinas);
}

// codigo da funcao para remover dsciplinas
void loopRemoverDisciplinas(Alunos *lista) {
    char rgm[TAMANHO_RGM];
    char nomeDisciplina[TAMANHO_NOME];
    int continuar = 1;

    while (continuar) {
        printf("Digite o RGM do aluno que deseja REMOVER disciplinas: ");
        if (scanf(" %49s", rgm) != 1) {
            printf("Entrada inválida para RGM.\n");
            while (getchar() != '\n'); 
            continue;
        }

        int posAluno = encontrarAlunoPorRGM(lista, rgm);
        if (posAluno == -1) {
            printf("RGM não encontrado.\n");
            continue; 
        }

        printf("Digite o nome da disciplina a ser removida: ");
        if (scanf(" %49s", nomeDisciplina) != 1) {
            printf("Entrada inválida para o nome da disciplina.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (removerDisciplina(&lista->pessoas[posAluno].disciplinas, nomeDisciplina) == 0) {
            printf("Disciplina %s removida com sucesso!\n", nomeDisciplina);
        } else {
            printf("Disciplina não encontrada.\n");
        }
        printf("Digite 1 para remover outra disciplina ou 0 para voltar ao menu: ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n'); 
            continuar = 0;
        }
    }
}

// codigo da funcao para organizar lista de alunos
void bubblesort(Alunos *listaAlunos) {
    int n = listaAlunos->contador;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(listaAlunos->pessoas[j].rgm, listaAlunos->pessoas[j + 1].rgm) > 0) {
                Dados_aluno temp = listaAlunos->pessoas[j];
                listaAlunos->pessoas[j] = listaAlunos->pessoas[j + 1];
                listaAlunos->pessoas[j + 1] = temp;
            }
        }
    }
}


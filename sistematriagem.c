#include <stdio.h>
#include <string.h>
 
#define MAX 30
 
typedef struct {
    char nomes[MAX][30];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializarFila(Fila* fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
}

int filaCheia(Fila* fila) {
    return fila->tamanho == MAX;
}

int filaVazia(Fila* fila) {
    return fila->tamanho == 0;
}

void adicionarPaciente(Fila* fila, char* nome) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível adicionar mais pacientes.\n");
        return;
    }
    fila->fim = (fila->fim + 1) % MAX;
    strcpy(fila->nomes[fila->fim], nome);
    fila->tamanho++;
}

char* atenderPaciente(Fila* fila) {
    if (filaVazia(fila)) {
        return NULL;
    }
    char* nome = fila->nomes[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->tamanho--;
    return nome;
}

void visualizarFila(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }
    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % MAX;
        printf("%s -> ", fila->nomes[indice]);
    }
    printf("NULL\n");
}

int main() {
    Fila filaNormal;
    Fila filaEmergencia;
    inicializarFila(&filaNormal);
    inicializarFila(&filaEmergencia);
    int opcao;
    char nome[30];
    do {
        printf("\nMenu:\n");
        printf("1. adicionar paciente na fila normal\n");
        printf("2. adicionar paciente na fila de emergencia\n");
        printf("3. atender o proximo paciente\n");
        printf("4. visualizar filas\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Nome do paciente: ");
                scanf("%s", nome);
                adicionarPaciente(&filaNormal, nome);
                break;
            case 2:
                printf("Nome do paciente: ");
                scanf("%s", nome);
                adicionarPaciente(&filaEmergencia, nome);
                break;
            case 3: {
                char* nomeAtendido = atenderPaciente(&filaEmergencia);
                if (nomeAtendido == NULL) {
                    nomeAtendido = atenderPaciente(&filaNormal);
                }
                if (nomeAtendido != NULL) {
                    printf("Paciente atendido: %s\n", nomeAtendido);
                } else {
                    printf("Nao ha pacientes para atender.\n");
                }
                break;
            }
            case 4:
                printf("Fila de emergencia: ");
                visualizarFila(&filaEmergencia);
                printf("Fila normal: ");
                visualizarFila(&filaNormal);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
    return 0;
}

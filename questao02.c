/*
Autor: Octavio e Rodrigo

Questao 02:
    Voce esta desenvolvendo um sistema de controle de entradas de pacientes para uma grande
    rede de hospitais. Atualmente, os pacientes que chegam ficam em uma fila indiana, ate serem
    chamados. Desenvolva um sistema gerador de senhas para o hospital, ressaltando que existem
    as senhas comuns e as senhas prioritarias. Crie a funcionalidade chamar proximo, que retira
    o primeiro elemento da fila, e o envia para o atendimento, mas, sao chmados dois pacientes
    prioritarios para cada paciente comum.
*/
#include <stdio.h>
#include <stdlib.h>

//FILA
typedef struct node {
    int senha;
    struct node* proximo;
} No;

typedef struct {
    int tamanho;
    No* primeiro;
    No* ultimo;
} Fila;

//FUNCOES
Fila* criarFila() {
    Fila* fila = NULL;

    fila = (Fila*) malloc(sizeof(Fila));

    if (fila != NULL) {
        fila->primeiro = NULL;
        fila->ultimo = NULL;
        fila->tamanho = 0;
    }

    return fila;
}

void adicionarPaciente(Fila* fila, int senha) {
    if (fila != NULL) {
        No* novo = (No*) malloc(sizeof(No));

        if (novo != NULL) {
            novo->senha = senha;
            novo->proximo = NULL;

            if (fila->tamanho == 0) {
                fila->primeiro = novo;
                fila->ultimo = novo;
            } else {
                fila->ultimo->proximo = novo;
                fila->ultimo = novo;
            }

            fila->tamanho++;
        }
    }
}

int senhaUltimoPacienteFila(Fila* fila) {
    if (fila != NULL) {
        if (fila->tamanho != 0) 
            return fila->ultimo->senha;
    }

    return 0;
}

int proximo(Fila* fila) {
    int senha = 0;
    No* tmp;

    if (fila != NULL) {
        if (fila->tamanho > 0) {
            senha = fila->primeiro->senha;
            fila->tamanho--;

            if (fila->tamanho == 0) {
                free(fila->primeiro);
                fila->primeiro = NULL;
                fila->ultimo = NULL;
            } else {
                tmp = fila->primeiro;
                fila->primeiro = fila->primeiro->proximo;
                free(tmp);
            }
        }
    }

    return senha;
}

void destruirFila(Fila* fila) {
    if (fila != NULL) {
        while (fila->primeiro != NULL) {
            proximo(fila);
        }

        free(fila);
    }
}
 
//PROGRAMA PRINCIPAL
int main() {
    Fila* normal = NULL;
    Fila* prioritario = NULL;

    int opcao = 0;

    normal = criarFila();
    prioritario = criarFila();

    int qtd_normal_ja_atendidos = 0;
    int senha = 0;
    

    while (1) {
        do  {
            printf("\n---MENU---\n");
            printf("[1] - Adicionar a fila normal.\n");
            printf("[2] - Adicionar a fila prioritario.\n");
            printf("[3] - Chamar proximo paciente.\n");
            printf("[0] - Sair.\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            //error
            if (opcao < 0 || opcao > 3)
                printf("Error: opcao invalida!\n");
        } while (opcao < 0 || opcao > 3);

        if (opcao == 0)
            break;
        else if (opcao == 1) {
            adicionarPaciente(normal, senhaUltimoPacienteFila(normal) + 1);
        } else if (opcao == 2) {
            adicionarPaciente(prioritario, senhaUltimoPacienteFila(prioritario) + 1);
        } else if (opcao == 3) {
            if (normal->tamanho == 0 && prioritario->tamanho == 0) {
                printf("Nao ha pacientes para serem atendidos.\n");
            } else if ((qtd_normal_ja_atendidos < 2) && (normal->tamanho != 0)) {
                senha = proximo(normal);
                printf("Normal: %d\n", senha);
                qtd_normal_ja_atendidos++;
            } else {
                qtd_normal_ja_atendidos = 0;
                if (prioritario->tamanho != 0) {
                    senha = proximo(prioritario);
                    printf("Prioritario: %d\n", senha);
                }
            }
        }
    }

    destruirFila(normal);
    destruirFila(prioritario);

    return 0;
}

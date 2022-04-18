/*
Autor: Octavio e Rodrigo

Questao 01:
    Voce foi chamado para uma entrevista de emprego na Mozilla Foundation, e o seu teste consiste
    na implementacao dos botoes de avancar e voltar do navegador. Estes botoes possuem o 
    seguinte comportamento:

    (a) Ao iniciar o navegador, as duas pilhas estarao vazias e criadas com um numero de elementos
    definidos por voce.
    
    (b) Ao digitar o primeiro endereco, o navegador adiciona a pagina inicial a pilha do voltar e
    ativa este botao.

    (c) Ao voltar, o topo desta pilha sera enviado para a pilha de avancar e ativa este botao,
    desativando o anterior, caso a pilha esteja vazia.

    (d) Ao avancar, o topo desta pilha sera enviado para a pilha do voltar e, o botao sera desati-
    vado, caso, a pilha esteja vazia.
*/
#include <stdio.h>
#include <string.h>

#define MAX_PAGINAS 10
#define MAX_URL 100

typedef struct {
    int topo;
    char paginas[MAX_PAGINAS][MAX_URL];
} Pilha;

int main() {
    Pilha voltar, avancar;
    char url[MAX_URL];
    int opcao;
    
    voltar.topo = 0;
    avancar.topo = 0;

    while (1) {
        do {
            printf("\n---MENU---\n");
            printf("[1] - Voltar.\n");
            printf("[2] - Avancar.\n");
            printf("[3] - URL.\n");
            printf("[0] - Sair.\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            //error
            if (opcao < 0 || opcao > 3)
                printf("Error: opcao invalida!\n");
        } while (opcao < 0 || opcao > 3);

        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            if (voltar.topo != 0) {
                strcpy(avancar.paginas[avancar.topo], voltar.paginas[voltar.topo - 1]);
                strcpy(url, voltar.paginas[voltar.topo - 1]);
                avancar.topo++;
                voltar.topo--;
            }
        } else if (opcao == 2) {
            if (avancar.topo != 0) {
                strcpy(voltar.paginas[voltar.topo], avancar.paginas[avancar.topo - 1]);
                strcpy(url, avancar.paginas[avancar.topo - 1]);
                voltar.topo++;
                avancar.topo--;
            }
        } else if (opcao == 3) {
            printf("URL: ");
            scanf("%s", url);
            strcpy(voltar.paginas[voltar.topo], url);
            voltar.topo++;
        }

        printf("URL: %s\n", url); 
        if (voltar.topo != 0)
            printf("Voltar: %s\n", voltar.paginas[voltar.topo - 1]);
        if (avancar.topo != 0)
            printf("Avancar: %s\n", avancar.paginas[avancar.topo - 1]);
    }

    return 0;
}

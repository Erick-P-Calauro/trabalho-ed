/*
    Modificado em 30/05/2026 por : 
     - Érick Pereira Calauro
     - Gustavo Machado Borges Daniel
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

void pre_order(BNode* root);

int main() {

    // Padrão
    BTree tree;
    tree.root = NULL;
    int opt = 0;

    // Busca
    BNode* pt = NULL;
    int f = 0, g = 0;
    char key[100];

    printf("Entre com a dimensao da arvore.\nD: ");
    scanf("%d", &tree.d);

    read_pokemon(&tree);

    do {

        printf("//----- //----- // ARVORE B //----- //----- //\n[1]- Buscar\n[2]- Inserir\n[9]- Finalizar\n------------------------------\nEntre com a sua opcao:");
        scanf("%d", &opt);

        switch(opt) {
            case 1:
                printf("Entre com a chave. \nChave: ");
                scanf("%s", key);
                b_search(&tree, key, &pt, &f, &g);

                if(f == 1) 
                    printf("A chave foi encontrada em %p.\n", pt);
                else 
                    printf("A chave não foi encontrada\n");

                f = 0;
                g = 0;
                strcpy(key, "");

                break;
            case 2:
                printf("Entre com a chave. \nChave: ");
                scanf("%s", key);

                b_insert(&tree, key);

                break;
            case 9:
                break;
            default:
                break;
        }

    }while(opt != 9);
    
    return 0;
}

void pre_order(BNode* root) {
    for(int i = 0; i < root->n_keys; i++) {
        printf("%s\n", root->keys[i]);   
    }

    for(int i = 0; i < root->m_children; i++) {
        if(root->children[i] != NULL) {
            pre_order(root->children[i]);
        }
    }
}
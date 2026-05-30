/*
    Modificado em 26/05/2026 por : 
     - Érick Pereira Calauro
     - Gustavo Machado Borges Daniel
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

BTree* b_create_tree(const int d, char* root_key) {
    BTree* tree = (BTree*) malloc(sizeof(BTree));

    tree->d = d;
    tree->root = b_create_node(1);
    tree->root->keys[1] = root_key;

    return tree;
}

BNode* b_create_node(const int n_keys) {
    BNode* node = (BNode*) malloc(sizeof(BNode));

    node->n_keys = n_keys;
    node->m_children = n_keys + 1;
    node->keys = (char**) malloc(sizeof(char*) * (n_keys+1));;
    node->children = (BNode**) malloc(sizeof(BNode*) * (n_keys + 2));

    return node;
}

// tree -> Árvore B 
// key -> Chave buscada (nome de um pokemon)
// pt -> Ponteiro  mantido fora da função
// f -> Argumento para sinalizar estado da busca
// g -> Posição da última página na árvore
void b_search(BTree* tree, char * key, BNode** pt, int* f, int* g) {

    BNode* p = tree->root;
    *pt = NULL;
    *f = 0;
    int cmp;
    int i;
    int m;

    while(p != NULL) {
        i = 1;
        *g = i;
        *pt = p;
        m = p->n_keys;

        while(i <= m) {
            cmp = strcmp(key, p->keys[i]);

            // key > p->keys[i]
            // Chave está para a direita
            if(cmp > 0) {
                i = i+1;
                *g = i;

            // key == p->keys[i]
            // Encontrou a chave
            }else if(cmp == 0) {
                p = NULL;
                *f = 1;
                return;
            
            // key < p->keys[i]
            // Chave está para a esquerda
            }else {
                p = p->children[i-1];
                i = m + 2;
            }
        }

        if(i == m + 1){
            p = p->children[m];
        }
    }

}
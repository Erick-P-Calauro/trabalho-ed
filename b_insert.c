#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"

void b_insert(BTree* tree, char* key){
    if(tree == NULL){ // verifica se a árvore existe
        return;
    }

    if(tree->root == NULL){ // verifica se a árvore está vazia

        // alocação de memória
        tree->root = (BNode*) malloc(sizeof(BNode));
        tree->root->keys = malloc(sizeof(char*) * (2 * tree->d));
        for(int i = 0; i < (2 * tree->d); i++){
            tree->root->keys[i] = malloc(sizeof(char) * 100);
        }
        tree->root->children = malloc(sizeof(BNode*) * (2 * tree->d + 1));
        tree->root->m_children = 0;

        tree->root->n_keys = 0;
        tree->root->leaf = 1;

        // inicializa filhos
        for(int i = 0; i < (2 * tree->d + 1); i++){
            tree->root->children[i] = NULL;
        }

        // copia primeira chave
        strcpy(tree->root->keys[0], key);

        // atualiza quantidade
        tree->root->n_keys = 1;

        return;
    }

    // verifica se raiz está cheia
    if(tree->root->n_keys == 2 * tree->d){

        // guarda raiz antiga
        BNode* old_root = tree->root;

        // cria nova raiz + alocação de memória
        BNode* new_root = (BNode*) malloc(sizeof(BNode));
        new_root->keys = malloc(sizeof(char*)*(2 * tree->d));
        for(int i = 0; i < (2 * tree->d); i++){
            new_root->keys[i] = malloc(sizeof(char) * 100);
        }
        new_root->children = malloc(sizeof(BNode*) * (2 * tree->d + 1));
        new_root->m_children = 1;

        new_root->leaf = 0;
        new_root->n_keys = 0;

        // inicializa filhos
        for(int i = 0; i < (2 * tree->d + 1); i++){
            new_root->children[i] = NULL;
        }

        // antiga raiz vira filha [0] da nova
        new_root->children[0] = old_root;

        // split
        b_split_child(tree, new_root, 0);

        // decide qual filho receberá a nova chave
        int i = 0;

        if(strcmp(key, new_root->keys[0]) > 0){
            i++;
        }

        // insere no filho correto
        b_insert_nonfull(tree, new_root->children[i], key);

        // atualiza raiz da árvore
        tree->root = new_root;
    }
    else{ // se raiz não está cheia:
        b_insert_nonfull(tree, tree->root, key);
    }
}
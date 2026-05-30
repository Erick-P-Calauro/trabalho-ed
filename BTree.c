/*
    Modificado em 30/05/2026 por : 
     - Érick Pereira Calauro
     - Gustavo Machado Borges Daniel
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

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

void b_split_child(BTree* tree, BNode* parent, int index){

    // filho cheio
    BNode* full_child = parent->children[index];

    // cria novo nó que ficará à direita
    BNode* new_child = (BNode*) malloc(sizeof(BNode));

    // configurando/alocação de memória de new_child
    new_child->leaf = full_child->leaf;
    new_child->n_keys = tree->d;
    new_child->keys = malloc(sizeof(char*)*(2 * tree->d));
    new_child->children = malloc(sizeof(BNode*)*(2 * tree->d + 1));

    //inicialização new_child
    for(int i = 0; i < (2 * tree->d); i++){
        new_child->keys[i] = malloc(sizeof(char) * 100);
    }
    for(int i = 0; i < (2 * tree->d + 1); i++){
        new_child->children[i] = NULL;
    }

    // copia a segunda metade das chaves para new_child
    for(int j = 0; j < tree->d; j++){
        strcpy(new_child->keys[j], full_child->keys[j + tree->d]);
    }

    // se não for folha:
    // copiar filhos também
    if(full_child->leaf == 0){
        for(int j = 0; j < tree->d + 1; j++){
            new_child->children[j] = full_child->children[j + tree->d];
        }
        new_child->m_children = tree->d + 1;
        full_child->m_children = tree->d;
    }else{
        new_child->m_children = 0;
        full_child->m_children = 0;
    }

    // reduz quantidade de chaves do nó cheio
    full_child->n_keys = tree->d - 1;

    // abre espaço para novo filho no pai
    for(int j = parent->n_keys; j >= index + 1; j--){
        parent->children[j + 1] = parent->children[j];
    }

    // conecta novo filho ao pai
    parent->children[index + 1] = new_child;

    // abre espaço para nova chave no pai
    for(int j = parent->n_keys - 1; j >= index; j--){
        strcpy(parent->keys[j + 1], parent->keys[j]);
    }

    // sobe chave da primeira metade para o pai
    strcpy(parent->keys[index], full_child->keys[tree->d - 1]);

    // atualiza quantidade de chaves do pai
    parent->n_keys++;
}

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

void b_insert_nonfull(BTree* tree, BNode* node, const char* key){

    // começa da última chave
    int i = node->n_keys - 1;

    // se folha:
    if(node->leaf == 1){
        // move chaves maiores uma posição para frente
        while(i >= 0 && strcmp(key, node->keys[i]) < 0){
            strcpy(node->keys[i + 1], node->keys[i]);
            i--;
        }

        // insere nova chave na posição correta
        strcpy(node->keys[i + 1], key);
        // atualiza quantidade de chaves
        node->n_keys++;
    }
    else{
        // encontra filho correto
        while(i >= 0 && strcmp(key, node->keys[i]) < 0){
            i--;
        }

        // avança para filho correto
        i++;

        // verifica se filho está cheio
        if(node->children[i]->n_keys == 2 * tree->d){
            // split
            b_split_child(tree, node, i);
            // decide qual dos dois filhos usar após split
            if(strcmp(key, node->keys[i]) > 0){
                i++;
            }
        }

        // continua inserção recursivamente
        b_insert_nonfull(tree, node->children[i], key);
    }
}
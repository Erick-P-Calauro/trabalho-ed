#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"

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
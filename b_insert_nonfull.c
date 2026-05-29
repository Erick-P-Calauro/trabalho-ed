#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"

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
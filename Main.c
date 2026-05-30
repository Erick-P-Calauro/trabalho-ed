/*
    Modificado em 26/05/2026 por : 
     - Érick Pereira Calauro
     - Gustavo Machado Borges Daniel
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

int main() {

    // TODO : Menu
    // TODO : Inserção automática dos nomes de pokemon

    // printf("%d %d %d \n", strcpy("Abra", "Alakazam"));

    char * b = "Bulbassaur";
    BTree* tree = b_create_tree(1, b);
    
    tree->root->children[0] = b_create_node(1);
    tree->root->children[0]->keys[1] = "Abra";

    tree->root->children[1] = b_create_node(1);
    tree->root->children[1]->keys[1] = "Charmander";

    printf("Dimension : %d \n", tree->d);
    printf("Root : %d %d \n", tree->root->n_keys, tree->root->m_children);
    printf("Key : %s \n", tree->root->children[0]->keys[1]);
    printf("Key : %s \n", tree->root->keys[1]);
    printf("Key : %s \n", tree->root->children[1]->keys[1]);

    BNode *pt;
    int f = 0, g = 0;

    b_search(tree, "Charmander", &pt, &f, &g);

    printf("Salve : %d %d\n", f, g);
    printf("%s", pt->keys[g]);

    return 0;
}
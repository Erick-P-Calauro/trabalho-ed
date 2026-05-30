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

    BTree tree;
    tree.d = 2;
    tree.root = NULL;

    b_insert(&tree, "Bulbassaur");
    b_insert(&tree, "Abra");
    b_insert(&tree, "Charmander");

    printf("Dimension : %d \n", tree.d);
    printf("Root : %d %d \n", tree.root->n_keys, tree.root->m_children);

    for(int i = 0; i < tree.root->n_keys; i++)
        printf("%s\n", tree.root->keys[i]);

    BNode *pt;
    int f = 0, g = 0;

    b_search(&tree, "Charmander", &pt, &f, &g);

    printf("Salve : %d %d\n", f, g);
    printf("%s", pt->keys[g]);

    return 0;
}
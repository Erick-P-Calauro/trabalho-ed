/*
    Modificado em 26/05/2026 por : 
     - Érick Pereira Calauro
     - Gustavo Machado Borges Daniel
*/

#ifndef __BTree_h
#define __BTree_h

struct BTree {
    int d;
    struct BNode* root;
};

struct BNode {
    int n_keys; // Número de chaves
    int m_children; // Número de filhos
    const char** keys;
    struct BNode** children; 
};

typedef struct BTree BTree;
typedef struct BNode BNode;

BTree* b_create_tree(const int d, const char* root_key);
BNode* b_create_node(const int n_keys);
void b_search(BTree* tree, const char* key, BNode** pt, int* f, int* g);
void b_insert(); // Definir

#endif
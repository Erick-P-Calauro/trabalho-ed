/*
    Modificado em 30/05/2026 por : 
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
    int leaf; // Booleano: 0- Folha; 1- Não folha
    int n_keys; // Número de chaves
    int m_children; // Número de filhos
    char** keys;
    struct BNode** children; 
};

typedef struct BTree BTree;
typedef struct BNode BNode;

void b_search(BTree* tree, char* key, BNode** pt, int* f, int* g);
void b_insert(BTree* tree, char* key);
void b_split_child(BTree* tree, BNode* parent, int index);
void b_insert_nonfull(BTree* tree, BNode* node, const char* key);
void read_pokemon(BTree* tree);

#endif
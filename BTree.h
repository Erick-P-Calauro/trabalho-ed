#ifndef __BTree_h
#define __BTree_h

struct BTree {
    int d;
    struct BNode* root;
};

struct BNode {
    int n_keys;
    char** keys;
    struct BNode** children; 
};

typedef struct BTree BTree;
typedef struct BNode BNode;

BNode* b_create(int n_keys, char** keys, BNode** children);
int b_comparator(const char* c1, const int l1, const char* c2, const int l2);
void b_search(const char* key, BNode* pt, int* f, int g);
void b_insert(); // Definir

#endif
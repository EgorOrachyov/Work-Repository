#include "SearchTree.h"

int main() {

    char name[MAXSIZE];
    printf("----- Building Search Tree ----- \n");

    int ok = 0;
    while (!ok) {
        printf("Write filename to create Optimal Balanced Tree.. \n");
        ok = scanf("%s",name);
    }

    SearchTree * STree = initSearchTree();
    createBalancedTreeFromFile(STree, name);

    ok = 0;
    while (!ok) {
        printf("Write filename to create \"dot\" file for Graphviz.. \n");
        ok = scanf("%s",name);
    }

    createDotGraphFile(STree, name);

    deleteSearchTree(STree);
    return 0;
}
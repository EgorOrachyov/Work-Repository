//
// Created by Egor Orachyov on 13.12.2017.
//

#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const int TRUE = 1;
const int FALSE = 0;

struct _NodeInfo {
    long key;
    long usage;
};
// Usage info about specific node of tree
typedef struct _NodeInfo NodeInfo;

struct _Node {
    long key;
    struct _Node * left;
    struct _Node * right;
};
// tree node
typedef struct _Node Node;

struct _SearchTree {
    Node * head;
    long size;
};
// Search tree with optimal cost of sum of deptt(Ni)*usage(Ni)
typedef struct _SearchTree SearchTree;

// Common structure for creating balanced tree
typedef struct {
    long weight;
    long cost;
    long root;
} Tree;

const int MAXSIZE = 256;

typedef NodeInfo data;

void swap(data * a, data * b) {
    data c = *a;
    *a = *b;
    *b = c;
}

void quickSort(data * a, long left, long right) {
    if (right - left > 0) {
        data centre = a[(left + right) / 2];
        long i = left;
        long j = right;
        while (i <= j) {
            while (a[i].key < centre.key) {
                i += 1;
            }
            while (a[j].key > centre.key) {
                j -= 1;
            }
            if (i <= j) {
                swap(&a[i], &a[j]);
                i += 1;
                j -= 1;
            }
        }
        quickSort(a, left, j);
        quickSort(a, i, right);
    }
}

long fromStringToLong(char * str, long len) {
    long result = 0;
    long dec, k;

    if (str[0] != '-') {
        k = 0;
        dec = 1;
    }
    else {
        k = 1;
        dec = -1;
    }

    for(long i = len - 1; i >= k; i--) {
        result = result + (str[i] - '0') * dec;
        dec *= 10;
    }

    return result;
};

NodeInfo * loadFromFile(char * filename, long * size) {
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    NodeInfo * nodeInfo = NULL;
    long nodeInfoSize = 0;

    char str[MAXSIZE];
    char tmp[MAXSIZE];

    while (!feof(file)) {
        fgets(str, MAXSIZE, file);

        long length = 0;
        long i = 0;

        while (str[i] != ' ') {
            tmp[i] = str[i];
            length += 1;
            i += 1;
        }

        long key = fromStringToLong(tmp, length);

        i += 3;
        length = 0;
        while ((str[i] >= '0') && (str[i] <= '9')) {
            tmp[length] = str[i];
            length += 1;
            i += 1;
        }

        long usage = fromStringToLong(tmp, length);

        nodeInfoSize += 1;
        nodeInfo = (NodeInfo *)realloc(nodeInfo, nodeInfoSize * sizeof(NodeInfo));

        nodeInfo[nodeInfoSize - 1].key = key;
        nodeInfo[nodeInfoSize - 1].usage = usage;

    }
    *size = nodeInfoSize;

    fclose(file);

    return nodeInfo;
};

SearchTree * initSearchTree() {
    SearchTree * STree = (SearchTree *)calloc(1, sizeof(SearchTree));

    STree->size = 0;
    STree->head = NULL;

    return STree;
};

Node * createSubTree(Tree ** tree, NodeInfo * nodeInfo, long left, long right) {
    if (left <= right) {
        Node * node = (Node *)calloc(1, sizeof(Node));
        if (node == NULL) {
            printf("Cannot allocate memory for Node \n");
            exit(1);
        }

        long m = tree[left][right].root;
        node->key = nodeInfo[m].key;

        //printf("l = %li, r = %li, m = %li \n", left, right, m);

        if (left == right) {
            node->left = NULL;
            node->right = NULL;
        }
        else if (m == right) {
            node->left = createSubTree(tree, nodeInfo, left, m - 1);
            node->right = NULL;
        }
        else if (m == left) {
            node->right = createSubTree(tree, nodeInfo, m + 1, right);
            node->left = NULL;
        }
        else {
            node->left = createSubTree(tree, nodeInfo, left, m - 1);
            node->right = createSubTree(tree, nodeInfo, m + 1, right);
        }

        return node;
    }
    else {
        return NULL;
    }
}

int createBalancedTreeFromFile(SearchTree * STree, char * filename) {
    long size;
    NodeInfo * nodeInfo = loadFromFile(filename, &size);
    if (nodeInfo == NULL) {
        return FALSE;
    }

    Tree ** tree = (Tree **)calloc(size, sizeof(Tree *));
    if (tree == NULL) {
        return FALSE;
    }
    for(long i = 0; i < size; i++) {
        tree[i] = (Tree *)calloc(size, sizeof(Tree));
        if (tree[i] == NULL) {
            return FALSE;
        }
    }

    quickSort(nodeInfo, 0, size-1);


    for(long i = 0; i < size; i++) {
        tree[i][i].weight = 0; //nodeInfo[i].usage;
        tree[i][i].cost = 0; //nodeInfo[i].usage;
        tree[i][i].root = i;
    }

    for(long l = 1; l < size; l++) {

        for(long i = 0; i < size - l; i++) {
            long j = i + l;  //l = j - i

            tree[i][j].weight = tree[i][j-1].weight + nodeInfo[j].usage;

            long m = i + 1;
            long min = tree[i][m - 1].cost + tree[m][j].cost;
            for(long k = i + 1; k <= j; k++) {
                long tmp = tree[i][k - 1].cost + tree[k][j].cost;
                if (min > tmp) {
                    m = k;
                    min = tmp;
                }
            }

            tree[i][j].cost = tree[i][j].weight + min;
            tree[i][j].root = m;
        }
    }

    STree->size = size;
    //printf("size = %li \n", size);
    STree->head = createSubTree(tree, nodeInfo, 0, size-1);

    for(long i = 0; i < size; i++) {
        free(tree[i]);
    }
    free(tree);
    free(nodeInfo);

    return TRUE;
};

char * longToString(long num) {
    char * s = (char *)calloc(MAXSIZE, sizeof(char));
    if (s == NULL) {
        printf("Cannot allocate memory for string \n");
        exit(1);
    }

    int len = 0;
    int isNeg = 0;
    if (num < 0) {
        isNeg = 1;
        num *= (-1);
    }

    while (num > 9) {
        len += 1;
        char c = num % 10 + '0';
        s[len-1] = c;
        num = num / 10;
    }
    len += 1;
    s[len - 1] = num + '0';

    if (isNeg) {
        len += 1;
        s[len - 1] = '-';
    }

    for(int i = 0; i < len / 2; i++) {
        char c = s[len - 1 - i];
        s[len - 1 - i] = s[i];
        s[i] = c;
    }
    s[len] = '\0';

    return s;
}

void writeUnit(Node * node, long * nullNum, FILE * file) {
    if (node != NULL) {
        char s[MAXSIZE];
        char * s1;
        s1 = longToString(node->key);

        s[0] = '\t';
        s[1] = '\0';

        if (node->left != NULL) {
            char * s2;
            s2 = longToString(node->left->key);

            strcat(s, s1);
            strcat(s, "->");
            strcat(s, s2);
            strcat(s, " [color=\"blue\"]; \n");

            fputs(s, file);
            free(s2);

            writeUnit(node->left, nullNum, file);
        }
        else {
            *nullNum += 1;
            char * s3 = longToString(*nullNum);

            s[1] = 'n';
            s[2] = '\0';
            strcat(s, s3);
            strcat(s, " [style=filled, fillcolor=\"grey\", label=\"null\"]; \n");
            fputs(s, file);

            s[0] = '\t';
            s[1] = '\0';
            strcat(s, s1);
            strcat(s, "->");
            strcat(s, "n");
            strcat(s, s3);
            strcat(s, " [color=\"blue\"]; \n");
            fputs(s, file);

            free(s3);
        }

        s[0] = '\t';
        s[1] = '\0';

        if (node->right != NULL) {
            char * s2;
            s2 = longToString(node->right->key);

            strcat(s, s1);
            strcat(s, "->");
            strcat(s, s2);
            strcat(s, " [color=\"red\"]; \n");

            fputs(s, file);
            free(s2);

            writeUnit(node->right, nullNum, file);
        }
        else {
            *nullNum += 1;
            char * s3 = longToString(*nullNum);

            s[1] = 'n';
            s[2] = '\0';
            strcat(s, s3);
            strcat(s, " [style=filled, fillcolor=\"grey\", label=\"null\"]; \n");
            fputs(s, file);

            s[0] = '\t';
            s[1] = '\0';
            strcat(s, s1);
            strcat(s, "->");
            strcat(s, "n");
            strcat(s, s3);
            strcat(s, " [color=\"red\"]; \n");
            fputs(s, file);

            free(s3);
        }

        free(s1);
    }
}

void createDotGraphFile(SearchTree * STree, char * filename) {
    FILE * file = fopen(filename, "w");

    fputs("digraph optimalSearchTree { \n", file);

    long nullNum = 0;

    writeUnit(STree->head, &nullNum, file);

    fputs("}", file);
    fclose(file);
};

void deleteTreeNode(Node * current) {
    if (current != NULL) {
        deleteTreeNode(current->left);
        deleteTreeNode(current->right);

        free(current);
    }
};

void deleteSearchTree(SearchTree * STree) {
    deleteTreeNode(STree->head);
    free(STree);
};

#endif //SEARCHTREE_H

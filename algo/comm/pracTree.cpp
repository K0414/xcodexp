#include <iostream>
#include <stack>
#include <exception>
#include <assert.h>
#include <cstring>
using namespace std;

typedef struct _Node {
    _Node* left;
    _Node* right;
    char name;
}Node;

Node *createBinaryTree()
{
    char c;
    Node *p;

    cin >> c;

    if('#' == c) {
        return NULL;
    } else {
        p = new Node;
        p->name = c;
        p->left = createBinaryTree();
        p->right = createBinaryTree();
    }

    return p;
}

void deleteBinaryTree(Node *pRoot)
{
    if(NULL != pRoot) {
        deleteBinaryTree(pRoot->left);
        deleteBinaryTree(pRoot->right);
        delete pRoot;
    }
}

void access(const Node *pNode)
{
    cout << pNode->name << " ";
}

/* 
 * recursivly traverse
 */
void preOrderTraverse(Node *pRoot)
{
    if(pRoot != NULL) {
        access(pRoot);
        preOrderTraverse(pRoot->left);
        preOrderTraverse(pRoot->right);
    }
}

void inOrderTraverse(Node *pRoot)
{
    if(pRoot != NULL) {
        inOrderTraverse(pRoot->left);
        access(pRoot);
        inOrderTraverse(pRoot->right);
    }
}

void postOrderTraverse(Node *pRoot)
{
    if(pRoot != NULL) {
        postOrderTraverse(pRoot->left);
        postOrderTraverse(pRoot->right);
        access(pRoot);
    }
}

/* 
 * traverse non-recursively
 */
void preOrderNonrecursive(Node *pRoot)
{
    if(pRoot == NULL)
        return;

    Node *p = pRoot;
    stack<Node *> stk;
    stk.push(p);
    while(!stk.empty()) {
        p = stk.top();
        stk.pop();
        access(p);
        if(p->right)
            stk.push(p->right);
        if(p->left)
            stk.push(p->left);
    }
}

void inOrderNonrecursive(Node *pRoot)
{
    stack<Node *> stk;
    Node *p;

    p = pRoot;
    while(p != NULL || !stk.empty()) {
        if(p != NULL) {
            stk.push(p);
            p = p->left;
        } else {
            p = stk.top();
            stk.pop();
            access(p);
            p = p->right;
        }
    }
}

void postOrderNonrecursive(Node *pRoot)
{
    stack<Node *> travs;
    stack<Node *> order;

    if(pRoot == NULL)
        return;

    Node *p = pRoot;
    travs.push(p);
    while(!travs.empty()) {
        p = travs.top();
        travs.pop();
        order.push(p);
        if(p->left)
            travs.push(p->left);
        if(p->right)
            travs.push(p->right);
    }

    while(!order.empty()) {
        access(order.top());
        order.pop();
    }
}

Node *rebuildBinaryTree(char *preStart, char *preEnd, char *inStart, char *inEnd)
{
    Node *pNode;
    char *ptr;

//    if(preStart == NULL || preEnd == NULL || inStart == NULL || inEnd == NULL) {
//        throw exception("Invalid input");
//        return NULL;
//    } else if(preEnd - preStart != inEnd - inStart) {
//        throw exception("Invalid input");
//        return NULL;
//    }
    assert(preStart != NULL);
    assert(preEnd != NULL);
    assert(inStart != NULL);
    assert(inEnd != NULL);

    pNode = NULL;
    if(preStart == preEnd && inStart == inEnd) {
//        if(*preStart != *inStart) {
//            throw exception("Invalid input");
//            return NULL;
//        }
        assert(*preStart == *inStart);
        pNode = new Node;
        pNode->name = *preStart;
        pNode->left = pNode->right = NULL;
    } else {
        pNode = new Node;
        pNode->name = *preStart;
        ptr = inStart;
        while(*ptr != *preStart && ptr <= inEnd)
            ptr++;
//        if(ptr > inEnd) {
//            throw exception("Invalid input");
//            return NULL;
//        }
        assert(ptr <= inEnd);
        pNode->left = rebuildBinaryTree(preStart + 1,
                preStart + (ptr - inStart),
                inStart, ptr - 1);
        pNode->right = rebuildBinaryTree(preStart + (ptr - inStart + 1),
                preEnd, ptr + 1, inEnd);
    }
}

int main()
{
    Node *pTree;
    pTree = createBinaryTree();

    preOrderTraverse(pTree);
    cout << endl;
    inOrderTraverse(pTree);
    cout << endl;
    postOrderTraverse(pTree);
    cout << endl;
    preOrderNonrecursive(pTree);
    cout << endl;
    inOrderNonrecursive(pTree);
    cout << endl;
    postOrderNonrecursive(pTree);
    cout << endl;

    deleteBinaryTree(pTree);

    char *preSeq = "1234567";
    char *inSeq = "3241675";
    pTree = rebuildBinaryTree(preSeq, preSeq + strlen(preSeq),
                inSeq, inSeq + strlen(inSeq));
    preOrderTraverse(pTree);
    cout << endl;
    inOrderTraverse(pTree);
    cout << endl;

    deleteBinaryTree(pTree);

    return 0;
}


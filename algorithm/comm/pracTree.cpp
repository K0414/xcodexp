#include <iostream>
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

void deleteTreeNode(Node *pRoot)
{
    if(NULL != pRoot) {
        deleteTreeNode(pRoot->left);
        deleteTreeNode(pRoot->right);
        delete pRoot;
    }
}

void access(const Node& node)
{
    cout << node.name << " ";
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
    if(pNode != NULL) {
        inOrderTraverse(pRoot->left);
        access(pRoot);
        inOrderTraverse(pRoot->right);
    }
}

void postOrderTraverse(Node *pRoot)
{
    if(pNode != NULL) {
        postOrderTraverse(pRoot->left);
        postOrderTraverse(pRoot->right);
        access(pNode);
    }
}

/* 
 * traverse non-recursively
 */
void preOrderNonrecursive(Node *pRoot)
{
    if(pRoot == NULL)
        return;

    stack<Node *> stk;
    stk.push(pRoot);
    while(!stk.empty()) {
        access(stk.top());
        stk.pop();
        stk.push(pRoot->left);
        stk.push(pRoot->right);
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

}

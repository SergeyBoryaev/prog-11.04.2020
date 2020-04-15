#include "h.h"

Node *add(Node *root, char a)
{
    if (!root)
    {
        Node *pnew = (Node *)malloc(sizeof(Node));
        pnew->num = a;
        pnew->left = NULL;
        pnew->right = NULL;
        root = pnew;
    }
    else if (root->num < a)
        root->right = add(root->right, a);
    else
        root->left = add(root->left, a);
    return root;
}

void in(Node *root)
{
    if (root)
    {
        in(root->left);
        printf("%c ", root->num);
        in(root->right);
    }
}

void pre(Node *root)
{
    if (root)
    {
        printf("%c ", root->num);
        pre(root->left);
        pre(root->right);
    }
}

void post(Node *root)
{
    if (root)
    {
        post(root->left);
        post(root->right);
        printf("%c ", root->num);
    }
}

STACK *Push(STACK *phead, char v)
{
    STACK *pnew = calloc(1, sizeof(STACK));
    pnew->pnext = phead;
    pnew->value = v;
    return pnew;
}

STACK *Pop(STACK *phead)
{
    STACK *pnew = phead->pnext;
    free(phead);
    return pnew;
}

int IsEmpty(STACK *phead)
{
    if (phead)
        return 0;
    return 1;
}

void print(Node *root, int level)
{
    if (root)
        print(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("   ");
    if (root)
        printf("%c   %d\n", root->num, level);
    else
        printf("#\n");
    if (root)
        print(root->left, level + 1);
}

Node *del(Node *root, char a)
{
    if (!root)
    {
        printf("No such element!\n");
        return NULL;
    }
    else if (root->num == a)
    {
        root = delNode(root);
        return root;
    }
    else if (root->num < a)
    {
        root->right = del(root->right, a);
        return root;
    }
    else
    {
        root->left = del(root->left, a);
        return root;
    }
}

Node *delNode(Node *elem)
{
    if (!elem->left && !elem->right)
    {
        free(elem);
        return NULL;
    }
    else if ((elem->left && !elem->right) || (!elem->left && elem->right))
    {
        Node *p = elem;
        if (elem->left)
        {
            elem = elem->left;
            p->left = NULL;
        }
        else
        {
            elem = elem->right;
            p->right = NULL;
        }
        free(p);
        return elem;
    }
    else
    {
        char a;
        replace(&(elem->right), &a);
        elem->num = a;
        return elem;
    }
}

void replace(Node **elem, char *a)
{
    if ((*elem)->left)
        replace(&((*elem)->left), a);
    else
    {
        *a = (*elem)->num;
        Node *p = *elem;
        *elem = (*elem)->right;
        p->right = NULL;
        free(p);
    }
}

BOOK *addBook(BOOK *phead, char name, int val)
{
    BOOK *pnew = (BOOK *)malloc(sizeof(BOOK));
    pnew->name = name;
    pnew->value = val;
    pnew->pnext = phead;
    return pnew;
}

int GetInt(BOOK *phead, char name)
{
    BOOK *pointer = phead;
    while (pointer->pnext != NULL && pointer->name != name)
    {
        pointer = pointer->pnext;
    }
    if (pointer->name == name)
        return pointer->value;
    return 0;
}

int HaveThisVar(BOOK *phead, char name)
{
    BOOK *pointer = phead;
    while (pointer)
    {
        if (pointer->name == name)
            return 1;
        pointer = pointer->pnext;
    }
    return 0;
}
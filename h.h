#ifndef H_H
#define H_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node
{
	char num;
	struct node* left;
	struct node* right;
}Node;

typedef struct h1
{
    char value;
    struct h1 *pnext;
} STACK;

typedef struct h
{
	struct h *pnext;
	char name;
	int value;
}BOOK;

BOOK *addBook(BOOK *phead, char name, int val);

int GetInt(BOOK *phead, char name);

int HaveThisVar(BOOK *phead, char name);

STACK *Push(STACK *phead, char v);

STACK *Pop(STACK *phead);

int IsEmpty(STACK *phead);

void replace(Node** elem, char* a);

Node *delNode(Node *elem);

Node *del(Node *root, char a);

void in(Node *root);

Node *add(Node *root, char a);

void pre(Node *root);

void post(Node *root);

void print(Node *root, int level);

#endif
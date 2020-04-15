#include "h.h"
#include <string.h>

int prior(char zn)
{
    if (zn == '(')
        return 1;
    if (zn == '+' || zn == '-')
        return 2;
    if (zn == '*' || zn == '/')
        return 3;
}

int rez(Node *root, BOOK *book)
{
    if (root->left && root->right)
    {
        if(root->num=='+')
            return rez(root->left, book) + rez(root->right, book);
        if(root->num=='-')
            return rez(root->left, book) - rez(root->right, book);
        if(root->num=='*')
            return rez(root->left, book) * rez(root->right, book);
        if(root->num=='/')
            return rez(root->left, book) / rez(root->right, book);
    }
    else
    {
        return GetInt(book, root->num); 
    }
}

int AddToTree(Node *tree, char var)
{
    int rez = 0;
    if (!(tree->right))
    {
        Node *pnew = (Node *)malloc(sizeof(Node));
        pnew->num = var;
        pnew->left = NULL;
        pnew->right = NULL;
        tree->right = pnew;
        return 1;
    }
    if (tree->right->num <= 'a' || tree->right->num >= 'z')
        rez = AddToTree(tree->right, var);
    if (!rez)
    {
        if (!(tree->left))
        {
            Node *pnew = (Node *)malloc(sizeof(Node));
            pnew->num = var;
            pnew->left = NULL;
            pnew->right = NULL;
            tree->left = pnew;
            return 1;
        }
        if (tree->left->num <= 'a' || tree->left->num >= 'z')
            return AddToTree(tree->left, var);
        else
            return 0;
    }
    else
        return 1;
}

int main()
{
    char str[100];
    printf("Primer:\n");
    scanf("%s", str);
    STACK *oper = 0;
    char vivod[100];
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            vivod[strlen(vivod)] = str[i];
            continue;
        }
        if (str[i] == '(')
        {
            oper = Push(oper, '(');
            continue;
        }
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            if (IsEmpty(oper) || prior(str[i]) > prior(oper->value))
            {
                oper = Push(oper, str[i]);
                continue;
            }
            else
            {
                while (!IsEmpty(oper) && prior(str[i]) <= prior(oper->value))
                {
                    vivod[strlen(vivod)] = oper->value;
                    oper = Pop(oper);
                }
                oper = Push(oper, str[i]);
                continue;
            }
        }
        if (str[i] == ')')
        {
            while (oper->value != '(')
            {
                vivod[strlen(vivod)] = oper->value;
                oper = Pop(oper);
            }
            oper = Pop(oper); // избавляемся от открывающейся скобки
        }
    }
    while (!IsEmpty(oper))
    {
        vivod[strlen(vivod)] = oper->value;
        oper = Pop(oper);
    }
    BOOK *book = NULL;
    for (int i = 0; i < strlen(vivod); i++)
    {
        if (vivod[i] >= 'a' && vivod[i] <= 'z' && !HaveThisVar(book, vivod[i]))
        {
            printf("Give val for %c:\n", vivod[i]);
            int val;
            scanf("%d", &val);
            book = addBook(book, vivod[i], val);
        }
    }
    printf("vivod: %s\n", vivod);
    Node *tree = NULL;
    tree = add(tree, vivod[strlen(vivod) - 1]);
    print(tree, 0);
    for (int i = strlen(vivod) - 2; i >= 0; i--)
        AddToTree(tree, vivod[i]);
    print(tree, 0);
    printf("\n%d\n", rez(tree, book));
    return 0;
}

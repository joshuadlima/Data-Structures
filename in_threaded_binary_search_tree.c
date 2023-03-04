#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)

struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
    int lthread;
    int rthread;
};

struct treenode *in_succ(struct treenode *ptr);
struct treenode *in_pre(struct treenode *ptr);

struct treenode *insert(struct treenode *root, int data);

struct treenode *del(struct treenode *root, int data);
struct treenode *caseA(struct treenode *root, struct treenode *parent, struct treenode *ptr);
struct treenode *caseB(struct treenode *root, struct treenode *parent, struct treenode *ptr);
struct treenode *caseC(struct treenode *root, struct treenode *parent, struct treenode *ptr);

void inorder(struct treenode *root);
void preorder(struct treenode *root);

int main()
{
    struct treenode *root = NULL;
    while (1)
    {
        printf("1 -> insert\n2 -> Delete\n3 -> inorder\n4 -> preorder\n5 -> exit\n");
        int sc, val;
        sint(sc);

        switch (sc)
        {
        case 1:
            sint(val), root = insert(root, val);
            break;

        case 2:
            sint(val), root = del(root, val);
            break;

        case 3:
            inorder(root);
            break;

        case 4:
            preorder(root);
            break;

        case 5:
            exit(1);

        default:
            exit(0);
        }
    }
    return 0;
}

struct treenode *in_succ(struct treenode *ptr)
{
    if (ptr->rthread == 1)
    {
        return ptr->right;
    }
    else
    {
        ptr = ptr->right;
        while (ptr->lthread == 0)
            ptr = ptr->left;

        return ptr;
    }
}

struct treenode *in_pre(struct treenode *ptr)
{
    if (ptr->lthread == 1)
    {
        return ptr->left;
    }
    else
    {
        ptr = ptr->left;
        while (ptr->rthread == 0)
            ptr = ptr->right;
        return ptr;
    }
}

struct treenode *insert(struct treenode *root, int data)
{
    struct treenode *parent = NULL, *ptr = root;
    int found = 0;

    // search the reqd node (under whom to insert)
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            found = 1;
            break;
        }

        parent = ptr;
        if (ptr->data < data)
        {
            if (ptr->rthread == 1)
                break;
            else
                ptr = ptr->right;
        }
        else
        {
            if (ptr->lthread == 1)
                break;
            else
                ptr = ptr->left;
        }
    }

    // insert node
    if (found)
        printf("node already exists\n");
    else
    {
        struct treenode *temp = (struct treenode *)malloc(sizeof(struct treenode));
        temp->data = data, temp->left = NULL, temp->right = NULL, temp->lthread = 1, temp->rthread = 1;

        if (parent == NULL) // case 1 : insert in empty tree
        {
            return temp;
        }
        else if (data < parent->data) // case 2 : insert on left
        {
            temp->left = parent->left;
            temp->right = parent;
            parent->lthread = 0;
            parent->left = temp;
        }
        else // case 3 : insert on right
        {
            temp->right = parent->right;
            temp->left = parent;
            parent->rthread = 0;
            parent->right = temp;
        }
    }

    return root;
}

struct treenode *del(struct treenode *root, int data)
{
    struct treenode *parent = NULL, *ptr = root;
    int found = 0;

    // search reqd node
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            found = 1;
            break;
        }

        parent = ptr;
        if (ptr->data < data)
        {
            if (ptr->rthread == 1)
                break;
            else
                ptr = ptr->right;
        }
        else
        {
            if (ptr->lthread == 1)
                break;
            else
                ptr = ptr->left;
        }
    }

    if (!found)
    {
        printf("Node doesnt exist in tree\n");
    }
    else
    {
        // parent == NULL => node to be Deleted is root
        if (ptr->lthread == 1 && ptr->rthread == 1)
            root = caseA(root, parent, ptr);
        else if (ptr->lthread == 1 || ptr->rthread == 1)
            root = caseB(root, parent, ptr);
        else
            root = caseC(root, parent, ptr);
    }

    return root;
}

struct treenode *caseA(struct treenode *root, struct treenode *parent, struct treenode *ptr)
{
    if (parent == NULL) // Delete root
    {
        root = NULL;
    }
    else if (parent->left == ptr)
    {
        parent->lthread = 1;
        parent->left = ptr->left;
    }
    else
    {
        parent->rthread = 1;
        parent->right = ptr->right;
    }

    free(ptr);
    return root;
}

struct treenode *caseB(struct treenode *root, struct treenode *parent, struct treenode *ptr)
{
    struct treenode *child = NULL;

    if (ptr->lthread == 0)
        child = ptr->left;
    else
        child = ptr->right;

    struct treenode *insuc = NULL, *inpre = NULL;
    insuc = in_succ(ptr), inpre = in_pre(ptr);

    if (parent == NULL) // Delete root
        root = child;
    else if (ptr->left == child)
        insuc->left = child;
    else
        inpre->right = child;

    free(ptr);
    return root;
}

struct treenode *caseC(struct treenode *root, struct treenode *parent, struct treenode *ptr)
{
    struct treenode *succ = NULL, *succparent = NULL;
    succparent = ptr, succ = ptr->right;

    while (succ->lthread != 1)
        succparent = succ, succ = succ->left;

    ptr->data = succ->data;

    if (succ->lthread == 1 && succ->rthread == 1)
        root = caseA(root, succparent, succ);
    else
        root = caseB(root, succparent, succ);

    return root;
}

void inorder(struct treenode *root)
{
    if (root == NULL)
    {
        printf("empty tree\n");
        return;
    }

    struct treenode *ptr = root;
    while (ptr->left != NULL)
        ptr = ptr->left;

    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = in_succ(ptr);
    }
}

void preorder(struct treenode *root)
{
    if (root == NULL)
    {
        printf("empty tree\n");
        return;
    }

    struct treenode *ptr = root;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);

        if (ptr->lthread == 0)
            ptr = ptr->left;
        else if (ptr->rthread == 0)
            ptr = ptr->right;
        else
        {
            // v v imp
            while (ptr != NULL && ptr->rthread != 1)
                ptr = ptr->right;
            if (ptr->right == 0)
                ptr = ptr->right;
        }
    }
}

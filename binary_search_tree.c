#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)

// BST
struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
};

// insert
struct treenode *insert_iterative(struct treenode *root, int data);
struct treenode *insert_recursive(struct treenode *root, int data);

// Delete
struct treenode *Delete_node_nrec(struct treenode *root, int data);
struct treenode *Delete_node_rec(struct treenode *root, int data);
struct treenode *case_A(struct treenode *root, struct treenode *parent, struct treenode *child); // 0 kids
struct treenode *case_B(struct treenode *root, struct treenode *parent, struct treenode *child); // 1 kid
struct treenode *case_C(struct treenode *root, struct treenode *parent, struct treenode *child); // 2 kids

// search
struct treenode *search(struct treenode *root, int skey);

// display
int tree_height(struct treenode *root);
void display_level(struct treenode *root, int level);
void display_level_order_recursive(struct treenode *root);

int main()
{
    struct treenode *root = NULL, *ptr = NULL;

    while (1)
    {
        printf("1 -> insert iterative\n2 -> insert recursive\n3 -> Delete\n4 -> search\n5 -> display level order\n6 -> exit");
        int sw, val;
        sint(sw);

        switch (sw)
        {
        case 1:
            sint(val), root = insert_iterative(root, val);
            break;

        case 2:
            sint(val), root = insert_recursive(root, val);
            break;

        case 3:
            sint(val), root = Delete_node_nrec(root, val);
            break;

        case 4:
            sint(val), ptr = search(root, val);
            break;

        case 5:
            display_level_order_recursive(root);
            break;

        case 6:
            exit(0);

        default:
            exit(1);
        }
    }
    return 0;
}

// BST

// insert
struct treenode *insert_iterative(struct treenode *root, int data)
{
    struct treenode *parent = NULL, *ptr = root;

    while (ptr != NULL)
    {
        parent = ptr;
        if (ptr->data < data)
            ptr = ptr->right;
        else if (ptr->data > data)
            ptr = ptr->left;
        else
        {
            printf("key is a duplicate\n");
            return NULL;
        }
    }

    struct treenode *temp = (struct treenode *)malloc(sizeof(struct treenode));
    temp->data = data, temp->left = NULL, temp->right = NULL;

    if (parent == NULL) // root is null
        return temp;
    else if (data < parent->data)
        parent->left = temp;
    else
        parent->right = temp;

    return root;
}

struct treenode *insert_recursive(struct treenode *root, int data)
{
    if (root == NULL)
    {
        root = (struct treenode *)malloc(sizeof(struct treenode));
        root->left = NULL, root->right = NULL, root->data = data;
    }
    else if (root->data < data)
    {
        root->right = insert_recursive(root->right, data);
    }
    else if (root->data > data)
    {
        root->left = insert_recursive(root->left, data);
    }
    else
    {
        printf("key is a duplicate\n");
    }

    return root;
}

// Delete
struct treenode *case_A(struct treenode *root, struct treenode *parent, struct treenode *ptr)
{
    // Delete leaf node

    if (root == ptr)
        root = NULL;
    else if (parent->left == ptr)
        parent->left = NULL;
    else
        parent->right = NULL;

    free(ptr);
    return root;
}

struct treenode *case_B(struct treenode *root, struct treenode *parent, struct treenode *ptr)
{
    struct treenode *successor = NULL;
    if (ptr->left == NULL)
        successor = ptr->right;
    else
        successor = ptr->left;

    if (root == ptr)
        root = successor;
    else if (parent->left == ptr)
        parent->left = successor;
    else
        parent->right = successor;

    free(ptr);
    return root;
}

struct treenode *case_C(struct treenode *root, struct treenode *parent, struct treenode *ptr)
{
    struct treenode *insucc = ptr->right, *insuccpar = ptr;
    while (insucc->left != NULL)
    {
        insuccpar = insucc;
        insucc = insucc->left;
    }

    // replace node to be Deleted by content of inorder successor
    // and Delete inorder successor
    ptr->data = insucc->data;

    if (insucc->left == NULL && insucc->right == NULL)
        root = case_A(root, insuccpar, insucc);
    else if (insucc->left == NULL)
        root = case_B(root, insuccpar, insucc);

    return root;
}

struct treenode *Delete_node_nrec(struct treenode *root, int data)
{
    struct treenode *parent = NULL, *ptr = root;

    while (ptr != NULL)
    {
        if (ptr->data == data)
            break;

        parent = ptr;
        if (ptr->data < data)
            ptr = ptr->right;
        else if (ptr->data > data)
            ptr = ptr->left;
    }

    if (ptr == NULL)
        printf("key not present\n");
    else if (ptr->left == NULL && ptr->right == NULL)
        root = case_A(root, parent, ptr);
    else if (ptr->left == NULL || ptr->right == NULL)
        root = case_B(root, parent, ptr);
    else
        root = case_C(root, parent, ptr);

    return root;
}

struct treenode *Delete_node_rec(struct treenode *root, int data)
{
}

// search
struct treenode *search(struct treenode *root, int skey)
{
    if (root == NULL)
    {
        printf("not found\n");
        return root;
    }
    else if (root->data == skey)
    {
        printf("found\n");
        return root;
    }
    else if (root->data < skey)
    {
        return search(root->right, skey);
    }
    else
    {
        return search(root->left, skey);
    }
}

// display
int tree_height(struct treenode *root)
{
    if (root == NULL)
        return 0;

    int optn1 = tree_height(root->left), optn2 = tree_height(root->right);
    return 1 + (optn1 > optn2 ? optn1 : optn2);
}

void display_level(struct treenode *root, int level)
{
    if (root == NULL)
        return;

    if (level == 1)
        printf("%d ", root->data);
    else
    {
        display_level(root->left, level - 1);
        display_level(root->right, level - 1);
    }
}

void display_level_order_recursive(struct treenode *root)
{
    int height = tree_height(root);

    for (int i = 1; i <= height; i++)
        display_level(root, i);
}

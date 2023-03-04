#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)

// GFG + CWH implementation

struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
};

// basic functions
int max(int a, int b);
int height(struct node *root);
int get_bf(struct node *root);
struct node *create_node(int data);
struct node *left_rotate(struct node *pptr);
struct node *right_rotate(struct node *pptr);

// insert
struct node *insert(struct node *root, int data);

// Delete
struct node *in_succ(struct node *root);
struct node *del(struct node *root, int data);

// display
void display_level(struct node *root, int level);
void display_level_order_recursive(struct node *root);

int main()
{
    struct node *root = NULL;

    while (1)
    {
        int sc, val;
        printf("1 -> insert\n2 -> Delete\n3 -> display\n4 -> exit\n"), sint(sc);

        switch (sc)
        {
        case 1:
            sint(val), root = insert(root, val);
            break;

        case 2:
            sint(val), root = del(root, val);
            break;

        case 3:
            display_level_order_recursive(root);
            break;

        case 4:
            exit(0);

        default:
            exit(1);
        }
    }
    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(struct node *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

struct node *create_node(int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->left = NULL, temp->right = NULL, temp->data = data, temp->height = 1;
    return temp;
}

int get_bf(struct node *root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

struct node *left_rotate(struct node *pptr)
{
    struct node *aptr = pptr->right;
    pptr->right = aptr->left;
    aptr->left = pptr;

    // update heights of aptr and pptr
    aptr->height = 1 + max(height(aptr->left), height(aptr->right));
    pptr->height = 1 + max(height(pptr->left), height(pptr->right));

    return aptr;
}

struct node *right_rotate(struct node *pptr)
{
    struct node *aptr = pptr->left;
    pptr->left = aptr->right;
    aptr->right = pptr;

    // update heights of aptr and pptr
    aptr->height = 1 + max(height(aptr->left), height(aptr->right));
    pptr->height = 1 + max(height(pptr->left), height(pptr->right));

    return aptr;
}

// Insert
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
        return create_node(data);
    else if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    // bcoz root's height isnt updated yet
    root->height = 1 + max(height(root->left), height(root->right));
    int bf = get_bf(root);

    // LL case
    if (bf > 1 && data < root->left->data)
    {
        root = right_rotate(root);
    }

    // RR case
    if (bf < -1 && data > root->right->data)
    {
        root = left_rotate(root);
    }

    // LR case
    if (bf > 1 && data > root->left->data)
    {
        root->left = left_rotate(root->left);
        root = right_rotate(root);
    }

    // RL case
    if (bf < -1 && data < root->right->data)
    {
        root->right = right_rotate(root->right);
        root = left_rotate(root);
    }

    return root;
}

// Delete
struct node *in_succ(struct node *root)
{
    struct node *succ = root->right;
    while (succ->left != NULL)
        succ = succ->left;

    return succ;
}

struct node *del(struct node *root, int data)
{
    if (root == NULL)
    {
        printf("data doesnt exist in tree\n");
        return root;
    }
    else if (data < root->data)
    {
        root->left = del(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = del(root->right, data);
    }
    else
    {
        struct node *temp = NULL;

        // 0 kids
        if (root->left == NULL && root->right == NULL)
        {
            temp = root;
            root = NULL;
        }
        // 1 kid
        else if (root->left == NULL)
        {
            temp = root;
            root = root->right;
        }
        else if (root->right == NULL)
        {
            temp = root;
            root = root->left;
        }
        // 2 kids
        else
        {
            struct node *suc = in_succ(root);
            root->data = suc->data;
            root->right = del(root->right, suc->data); // Delete succ
        }

        free(temp);
    }

    if (root == NULL) // tree has no content after deletion
        return root;

    // update height
    root->height = 1 + max(height(root->left), height(root->right));
    int bf = get_bf(root);

    // perform balancing

    // LL case
    if (bf > 1 && get_bf(root->left) >= 0)
    {
        root = right_rotate(root);
    }
    // RR case
    if (bf < -1 && get_bf(root->right) <= 0)
    {
        root = left_rotate(root);
    }
    // RL case
    if (bf < -1 && get_bf(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        root = left_rotate(root);
    }
    // LR case
    if (bf > 1 && get_bf(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        root = right_rotate(root);
    }

    return root;
}

// display
void display_level(struct node *root, int level)
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

void display_level_order_recursive(struct node *root)
{
    if (root == NULL)
    {
        printf("empty tree\n");
        return;
    }

    int height = root->height;

    for (int i = 1; i <= height; i++)
        display_level(root, i);

    printf("\n");
}

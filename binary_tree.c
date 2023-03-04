#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)
#define schar(x) scanf("%c", &x)

// linked list
struct listnode
{
    char data;
    struct listnode *next;
} *postorder = NULL, *inorder = NULL, *preorder = NULL;

struct listnode *insert_at_end(struct listnode *start, char data);
void dis(struct listnode *start);

// queue for level order traversal
struct node
{
    struct treenode *data;
    struct node *next;
};

struct node *enqueue(struct node *rear, struct node **front, struct treenode *data);
struct node *dequeue(struct node *rear, struct node **front);
struct treenode *queuepeek(struct node *rear);
int isQueueEmpty(struct node *rear, struct node *front);

// stack for spiral traversal
int isStackEmpty(struct node *top);
struct treenode *stackpeek(struct node *top);
struct node *push(struct node **top, struct treenode *data);
struct node *pop(struct node **top);

// tree
struct treenode
{
    char data;
    struct treenode *left;
    struct treenode *right;
};

struct treenode *create_tree_pre_in(struct listnode *inptr, struct listnode *preptr, int n);
struct treenode *create_tree_post_in(struct listnode *inptr, struct listnode *postptr, int n);
int tree_height(struct treenode *root);
int depth_node(struct treenode *root, char target, int depth);

// traversals
void display_inorder_recursive(struct treenode *root);
void display_inorder_iterative(struct treenode *root);
void display_preorder_recursive(struct treenode *root);
void display_preorder_iterative(struct treenode *root);
void display_postorder_recursive(struct treenode *root);
void display_postorder_iterative(struct treenode *root);
void display_level_order_recursive(struct treenode *root);
void display_level(struct treenode *root, int level);
void display_level_order_iterative(struct treenode *root);
void display_spiral_order(struct treenode *root);

int main()
{
    struct treenode *root = NULL, *rootinpre = NULL;
    int n;
    char v;

    printf("enter the number of elements "), sint(n);

    printf("enter the postorder: "), schar(v);
    for (int i = 0; i < n; i++)
        schar(v), postorder = insert_at_end(postorder, v), schar(v);

    printf("enter the preorder: ");
    for (int i = 0; i < n; i++)
        schar(v), preorder = insert_at_end(preorder, v), schar(v);

    printf("enter the inorder: ");
    for (int i = 0; i < n; i++)
        schar(v), inorder = insert_at_end(inorder, v), schar(v);

    root = create_tree_post_in(inorder, postorder, n);
    rootinpre = create_tree_pre_in(inorder, preorder, n);

    // display both trees in level order
    printf("tree using preorder and inorder is\n");
    display_level_order_recursive(rootinpre), printf("\n");

    printf("tree using postorder and inorder is\n");
    display_level_order_iterative(root), printf("\n");

    while (1)
    {
        int sc1, sc2;
        printf("1 -> display height of the tree\n2 -> return depth of a given node\n3 -> traversals\n4 -> exit\n"), sint(sc1);

        switch (sc1)
        {
        case 1:
            printf("the height of the tree is %d\n", tree_height(root));
            break;

        case 2:
            schar(v), printf("enter the reqd node "), schar(v);
            printf("\nthe depth of reqd node is %d\n", depth_node(root, v, 0));
            break;

        case 3:
            printf("1 -> inorder recursive\n2 -> inorder iterative\n3 -> preorder recursive\n");
            printf("4 -> preorder iterative\n5 -> postorder recursive\n6 -> postorder iterative\n");
            printf("7 -> levelorder recursive\n8 -> levelorder iterative\n9 -> spiralorder iterative\n");
            sint(sc2);

            switch (sc2)
            {
            case 1:
                display_inorder_recursive(root), printf("\n");
                break;

            case 2:
                display_inorder_iterative(root), printf("\n");
                break;

            case 3:
                display_preorder_recursive(root), printf("\n");
                break;

            case 4:
                display_preorder_iterative(root), printf("\n");
                break;

            case 5:
                display_postorder_recursive(root), printf("\n");
                break;

            case 6:
                display_postorder_iterative(root), printf("\n");
                break;

            case 7:
                display_level_order_recursive(root), printf("\n");
                break;

            case 8:
                display_level_order_iterative(root), printf("\n");
                break;

            case 9:
                display_spiral_order(root), printf("\n");
                break;
            }

            break;

        case 4:
            exit(0);

        default:
            exit(1);
        }
    }

    return 0;
}

// linked list
struct listnode *insert_at_end(struct listnode *start, char data)
{
    struct listnode *temp = (struct listnode *)malloc(sizeof(struct listnode));
    temp->data = data, temp->next = NULL;

    if (start == NULL)
        return temp;

    struct listnode *p = start;
    while (p->next != NULL)
        p = p->next;

    p->next = temp;
    return start;
}

void dis(struct listnode *start)
{
    while (start != NULL)
        printf("%c ", start->data), start = start->next;
}

// queue implementation
struct node *enqueue(struct node *start, struct node **top, struct treenode *d)
{
    // create node
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = d;
    temp->next = NULL;

    if (start == NULL)
        start = temp, (*top) = start;
    else
        (*top)->next = temp, (*top) = (*top)->next;

    return start;
}

struct node *dequeue(struct node *start, struct node **top)
{
    if (start == NULL)
        printf("queue underflow\n");
    else if (start == (*top))
        start = NULL, (*top) = NULL;
    else
    {
        struct node *temp = start;
        start = start->next, free(temp);
    }
    return start;
}

struct treenode *queuepeek(struct node *start)
{
    if (start != NULL)
        return start->data;
    else
        return NULL;
}

int isQueueEmpty(struct node *start, struct node *top)
{
    return (start == NULL && top == NULL);
}

// stack implementation
int isStackEmpty(struct node *top)
{
    return top == NULL;
}

struct node *push(struct node **top, struct treenode *data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));

    if (temp == NULL)
        printf("STACK OVERFLOW\n");
    else
    {
        temp->data = data, temp->next = NULL;
        temp->next = (*top);
        (*top) = temp;
    }

    return (*top);
}

struct treenode *stackpeek(struct node *top)
{
    if (isStackEmpty(top))
        return NULL;
    else
        return top->data;
}

struct node *pop(struct node **top)
{
    if (isStackEmpty((*top)))
        printf("STACK UNDERFLOW\n");
    else
    {
        struct node *temp = (*top);
        (*top) = (*top)->next;
        free(temp);
    }

    return (*top);
}

// tree
struct treenode *create_tree_pre_in(struct listnode *inptr, struct listnode *preptr, int n)
{
    if (n == 0)
        return NULL;

    // get root data and create root
    struct treenode *root = (struct treenode *)malloc(sizeof(struct treenode));
    root->data = preptr->data, root->left = NULL, root->right = NULL;

    if (n == 1)
        return root;

    // get left
    int i = 0;
    struct listnode *ptr = inptr;
    while (ptr->data != root->data)
        ptr = ptr->next, i++;
    root->left = create_tree_pre_in(inptr, preptr->next, i);

    // get right
    preptr = preptr->next; // overtaken current root
    for (int j = 1; j <= i; j++)
        preptr = preptr->next;
    root->right = create_tree_pre_in(ptr->next, preptr, n - i - 1);

    return root;
}

struct treenode *create_tree_post_in(struct listnode *inptr, struct listnode *postptr, int n)
{
    struct treenode *root = NULL;

    if (n == 0)
        return root;

    // get data of root
    struct listnode *ptr = postptr;
    for (int i = 1; i < n; i++)
        ptr = ptr->next;

    // create tree node
    root = (struct treenode *)malloc(sizeof(struct treenode));
    root->left = NULL, root->right = NULL, root->data = ptr->data;

    if (n == 1)
        return root;

    // get the left sub tree
    struct listnode *ptr2 = inptr;
    int left_ct = 0;
    for (; ptr2->data != ptr->data; left_ct++)
        ptr2 = ptr2->next;

    root->left = create_tree_post_in(inptr, postptr, left_ct);

    // get the right sub tree
    struct listnode *ptr3 = postptr;
    for (int i = 0; i < left_ct; i++)
        ptr3 = ptr3->next;

    root->right = create_tree_post_in(ptr2->next, ptr3, n - left_ct - 1);

    return root;
}

int tree_height(struct treenode *root)
{
    if (root == NULL)
        return 0;

    int optn1 = tree_height(root->left), optn2 = tree_height(root->right);
    return 1 + (optn1 > optn2 ? optn1 : optn2);
}

int depth_node(struct treenode *root, char target, int depth)
{
    if (root == NULL)
        return -1;
    else if (root->data == target)
        return depth;

    int optn1 = depth_node(root->left, target, depth + 1), optn2 = depth_node(root->right, target, depth + 1);
    return (optn1 > optn2) ? optn1 : optn2;
}

void display_inorder_recursive(struct treenode *root)
{
    if (root == NULL)
        return;

    display_inorder_recursive(root->left);
    printf("%c ", root->data);
    display_inorder_recursive(root->right);
}

void display_inorder_iterative(struct treenode *root)
{
    if (root == NULL)
        return;

    struct node *stack = NULL;

    struct treenode *temp = root;

    while (1)
    {
        if (temp != NULL)
        {
            stack = push(&stack, temp);
            temp = temp->left;
        }
        else
        {
            if (isStackEmpty(stack))
                return;

            temp = stackpeek(stack);
            stack = pop(&stack);

            printf("%c ", temp->data);
            temp = temp->right;
        }
    }
}

void display_preorder_recursive(struct treenode *root)
{
    if (root == NULL)
        return;

    printf("%c ", root->data);
    display_preorder_recursive(root->left);
    display_preorder_recursive(root->right);
}

void display_preorder_iterative(struct treenode *root)
{
    if (root == NULL)
        return;

    struct node *stack = NULL;
    stack = push(&stack, root);

    while (!isStackEmpty(stack))
    {
        struct treenode *current = stackpeek(stack);
        stack = pop(&stack);
        printf("%c ", current->data);

        if (current->right != NULL)
            stack = push(&stack, current->right);
        if (current->left != NULL)
            stack = push(&stack, current->left);
    }
}

void display_postorder_recursive(struct treenode *root)
{
    if (root == NULL)
        return;

    display_postorder_recursive(root->left);
    display_postorder_recursive(root->right);
    printf("%c ", root->data);
}

void display_postorder_iterative(struct treenode *root)
{
    if (root == NULL)
        return;

    // ON HOLD
    struct node *stack = NULL;
    struct treenode *temp = root;

    while (1)
    {
    }
}

void display_level(struct treenode *root, int level)
{
    if (root == NULL)
        return;

    if (level == 1)
        printf("%c ", root->data);
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

void display_level_order_iterative(struct treenode *root)
{
    if (root == NULL)
        return;

    struct node *queue = NULL, *top = NULL;
    queue = enqueue(queue, &top, root);

    while (!isQueueEmpty(queue, top))
    {
        struct treenode *element = queuepeek(queue);
        printf("%c ", element->data);

        if (element->left != NULL)
            queue = enqueue(queue, &top, element->left);
        if (element->right != NULL)
            queue = enqueue(queue, &top, element->right);

        queue = dequeue(queue, &top);
    }
    printf("\n");
}

void display_spiral_order(struct treenode *root)
{
    if (root == NULL)
        return;

    struct node *stack1 = NULL, *stack2 = NULL;
    stack1 = push(&stack1, NULL), stack2 = push(&stack2, NULL);
    stack1 = push(&stack1, root);

    while (stackpeek(stack1) != NULL || stackpeek(stack2) != NULL)
    {
        if (stackpeek(stack1) == NULL)
        {
            while (stackpeek(stack2) != NULL)
            {
                struct treenode *element = stackpeek(stack2);
                printf("%c ", element->data);

                if (element->right != NULL)
                    stack1 = push(&stack1, element->right);
                if (element->left != NULL)
                    stack1 = push(&stack1, element->left);

                stack2 = pop(&stack2);
            }
        }
        else
        {
            while (stackpeek(stack1) != NULL)
            {
                struct treenode *element = stackpeek(stack1);
                printf("%c ", element->data);

                if (element->left != NULL)
                    stack2 = push(&stack2, element->left);
                if (element->right != NULL)
                    stack2 = push(&stack2, element->right);

                stack1 = pop(&stack1);
            }
        }
    }

    printf("\n");
}

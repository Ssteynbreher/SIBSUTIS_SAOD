#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

Node *buildISDP(int L, int R)
{
    if (L > R)
        return NULL;
    int m = (L + R) / 2;
    Node *root = (Node *)malloc(sizeof(Node));
    if (!root)
    {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    root->data = 0;
    root->left = buildISDP(L, m - 1);
    root->right = buildISDP(m + 1, R);
    return root;
}

// нумерация
void numeration(Node *root, int n)
{
    if (!root)
        return;
    Node **queue = (Node **)malloc(n * sizeof(Node *));
    if (!queue)
    {
        fprintf(stderr, "Маллок не получився :(\n");
        exit(1);
    }
    int head = 0, tail = 0;
    queue[tail++] = root; // кладем корень в очередь
    int counter = 1;

    while (head < tail)
    {                              // пока не пусто
        Node *cur = queue[head++]; // берем эл
        cur->data = counter++;     // присваиваем
        if (cur->left)
            queue[tail++] = cur->left; // поддеревья
        if (cur->right)
            queue[tail++] = cur->right;
    }
    free(queue);
}

void slevanapravo(Node *root)
{
    if (!root)
        return;
    slevanapravo(root->left);
    printf("%d ", root->data);
    slevanapravo(root->right);
}

int size_tree(Node *root)
{
    if (!root)
        return 0;
    return 1 + size_tree(root->left) + size_tree(root->right);
}

long long checksum(Node *root)
{
    if (!root)
        return 0;
    return root->data + checksum(root->left) + checksum(root->right);
}

int height(Node *root)
{
    if (!root)
        return 0;
    int hl = height(root->left);
    int hr = height(root->right);
    return 1 + (hl > hr ? hl : hr);
}

void sumDepths(Node *root, int depth, long long *sum, int *count)
{
    if (!root)
        return;
    *sum += depth;
    (*count)++;
    sumDepths(root->left, depth + 1, sum, count);
    sumDepths(root->right, depth + 1, sum, count);
}

double averageHeight(Node *root)
{
    long long sum = 0;
    int count = 0;
    sumDepths(root, 1, &sum, &count);
    if (count == 0)
        return 0.0;
    return (double)sum / count;
}

void freeTree(Node *root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    int n = 100;
    Node *root = buildISDP(1, n);

    // Порядок уровней
    numeration(root, n);

    printf("Обход дерева слева направо (Л-К-П):\n");
    slevanapravo(root);
    printf("\n\n");

    int s = size_tree(root);
    long long cs = checksum(root);
    int h = height(root);
    double avg = averageHeight(root);

    printf("Размер дерева: %d\n", s);
    printf("Контрольная сумма: %lld\n", cs);
    printf("Высота дерева: %d\n", h);
    printf("Средняя высота: %.2f\n", avg);

    freeTree(root);
    return 0;
}
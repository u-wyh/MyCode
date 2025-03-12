#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新的节点
TreeNode* createNode(int v) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        return NULL;
    }
    newNode->val = v;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 先序遍历（递归）
void preOrder(TreeNode* head) {
    if (head == NULL) {
        return;
    }
    printf("%d ", head->val);
    preOrder(head->left);
    preOrder(head->right);
}

// 中序遍历（递归）
void inOrder(TreeNode* head) {
    if (head == NULL) {
        return;
    }
    inOrder(head->left);
    printf("%d ", head->val);
    inOrder(head->right);
}

// 后序遍历（递归）注意：你的代码中 `posOrder` 可能是个笔误，通常我们称为 `postOrder`
void postOrder(TreeNode* head) {
    if (head == NULL) {
        return;
    }
    postOrder(head->left);
    postOrder(head->right);
    printf("%d ", head->val);
}

// 主函数，创建并遍历二叉树
int main() {
    TreeNode* head = createNode(1);
    head->left = createNode(2);
    head->right = createNode(3);
    head->left->left = createNode(4);
    head->left->right = createNode(5);
    head->right->left = createNode(6);
    head->right->right = createNode(7);

    printf("先序遍历递归版: ");
    preOrder(head);
    printf("\n");

    printf("中序遍历递归版: ");
    inOrder(head);
    printf("\n");

    printf("后序遍历递归版: ");
    postOrder(head);
    printf("\n");

    // 清理分配的内存（实际代码中可能需要遍历整个树并释放每个节点的内存）
    // ...

    return 0;
}

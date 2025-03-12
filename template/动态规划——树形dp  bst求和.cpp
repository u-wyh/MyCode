// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树
// 测试链接 : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// 定义树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
//建立树状结构 包含左节点，右节点以及值大小

// 定义一个结构体来存储每个子树的信息
struct Info {
    int maxans;//搜索树中最大值
    int minans;//搜索书中最小值
    bool isBst;//以当前为首的数是否全部是一个符合条件的树
    int maxBstSum;//这棵树中最大的搜索树最大累加和有多大
    int sum;//整棵树的累加和

    Info(int a,int b, bool c, int d,int e) : maxans(a), minans(b), isBst(c), maxBstSum(d), sum(e) {}
};

// 递归函数，返回子树的信息
Info f(TreeNode* x) {
    if (x == nullptr) {
        return Info(INT_MIN, INT_MAX, true, 0, 0);
    }

    Info infol = f(x->left);//左树全集信息
    Info infor = f(x->right);//右树全集信息

    int maxVal = max(x->val, max(infol.maxans, infor.maxans));
    int minVal = min(x->val, min(infol.minans, infor.minans));
    bool isBST = infol.isBst && infor.isBst && infol.maxans < x->val && x->val < infor.minans;
    int sumans=infol.sum+infor.sum+x->val;
    //当前节点的全集信息
    int maxBSTSum = max(infol.maxBstSum, infor.maxBstSum);
    if (isBST) {
        maxBSTSum = max(maxBSTSum, sumans);
    }

    return Info(maxVal, minVal, isBST, maxBSTSum, sumans);
}

// 主函数，用于找到最大BST子树的大小
int largestBSTSubtree(TreeNode* root) {
    return f(root).maxBstSum;
}


int main() {
    // 创建一个示例树
    //       10
    //      /  \
    //     5    15
    //    / \    \
    //   1   8    7
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    // 找到最大BST子树的大小
    cout << "Largest BST Subtree Size: " << largestBSTSubtree(root) << endl;

    return 0;
}


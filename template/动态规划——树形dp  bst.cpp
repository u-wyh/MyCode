// 最大BST子树
// 给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，并返回该子树的大小
// 其中，最大指的是子树节点数最多的
// 二叉搜索树（BST）中的所有节点都具备以下属性：
// 左子树的值小于其父（根）节点的值
// 右子树的值大于其父（根）节点的值
// 注意：子树必须包含其所有后代
// BST是一种特殊的二叉树，其中每个节点的左子树中的所有节点都小于该节点的值，而右子树中的所有节点都大于该节点的值。
// 测试链接 : https://leetcode.cn/problems/largest-bst-subtree/
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
    long long maxans;//搜索树中最大值
    long long minans;//搜索书中最小值
    bool isBst;//以当前为首的数是否全部是一个符合条件的树
    int maxBstSize;//这棵树中最大的搜索树有多大

    Info(long long a, long long b, bool c, int d) : maxans(a), minans(b), isBst(c), maxBstSize(d) {}
};

// 递归函数，返回子树的信息
Info f(TreeNode* x) {
    if (x == nullptr) {
        return Info(LLONG_MIN, LLONG_MAX, true, 0);
    }

    Info infol = f(x->left);//左树全集信息
    Info infor = f(x->right);//右树全集信息

    long long maxVal = max((long long )x->val, max(infol.maxans, infor.maxans));
    long long minVal = min((long long )x->val, min(infol.minans, infor.minans));
    bool isBST = infol.isBst && infor.isBst && infol.maxans < x->val && x->val < infor.minans;
    int maxBSTSize = isBST ? infol.maxBstSize + infor.maxBstSize + 1 : max(infol.maxBstSize, infor.maxBstSize);
    //当前节点的全集信息

    return Info(maxVal, minVal, isBST, maxBSTSize);
}

// 主函数，用于找到最大BST子树的大小
int largestBSTSubtree(TreeNode* root) {
    return f(root).maxBstSize;
}


int main() {
    // 创建一个示例树
    //       10
    //      /  \
    //     5    15
    //    / \    \
    //   1   8    7
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(10);

    // 找到最大BST子树的大小
    cout << "Largest BST Subtree Size: " << largestBSTSubtree(root) << endl;

    return 0;
}

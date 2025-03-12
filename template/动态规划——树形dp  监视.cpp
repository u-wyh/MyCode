// 监控二叉树
// 给定一个二叉树，我们在树的节点上安装摄像头
// 节点上的每个摄影头都可以监视其父对象、自身及其直接子对象
// 计算监控树的所有节点所需的最小摄像头数量
// 测试链接 : https://leetcode.cn/problems/binary-tree-cameras/

#include<bits/stdc++.h>
using namespace std;
int ans;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 递归含义
// 假设x上方一定有父亲的情况下，这个假设很重要
// x为头的整棵树，最终想都覆盖，
// 并且想使用最少的摄像头，x应该是什么样的状态
// 返回值含义
// 0: x是无覆盖的状态，x下方的节点都已经被覆盖
// 1: x是覆盖状态，x上没摄像头，x下方的节点都已经被覆盖
// 2: x是覆盖状态，x上有摄像头，x下方的节点都已经被覆盖
int f(TreeNode* x) {
    if (x == nullptr) {
        return 1;
    }
    int left = f(x->left);
    int right = f(x->right);
    if (left == 0 || right == 0) {
        ans++;
        return 2;
    }
    if (left == 1 && right == 1) {
        return 0;
    }
    return 1;
}

int minCameraCover(TreeNode* root) {
    ans = 0;
    if (f(root) == 0) {
        //表示所有的都被覆盖  即两个儿子都是1  除了root节点
        ans++;
    }
    return ans;
}

int main()
{
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
//    root->left->left = new TreeNode(1);
//    root->left->right = new TreeNode(8);
//    root->right->right = new TreeNode(7);

    cout << "Largest Root Subtree Size: " << minCameraCover(root) << endl;
    return 0;
}

// 在二叉树中分配硬币
// 给你一个有 n 个结点的二叉树的根结点 root
// 其中树中每个结点 node 都对应有 node.val 枚硬币
// 整棵树上一共有 n 枚硬币
// 在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点
// 移动可以是从父结点到子结点，或者从子结点移动到父结点
// 返回使每个结点上 只有 一枚硬币所需的 最少 移动次数
// 测试链接 : https://leetcode.cn/problems/distribute-coins-in-binary-tree/
#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct Info {
    int cnt;//节点
    int moves;
    int sum;//币数

    Info(int a,int b,int c) :cnt(a),sum(b),moves(c) {}
};

Info f(TreeNode* x){
    if(x==nullptr){
        return Info(0,0,0);
    }

    Info infol = f(x->left);//左树全集信息
    Info infor = f(x->right);//右树全集信息

    int sum=infol.sum+infor.sum+x->val;
    int cnt=infol.cnt+infor.cnt+1;
    int moves=infol.moves+infor.moves+abs(infol.sum-infol.cnt)+abs(infor.cnt-infor.sum);

    return Info(cnt,sum,moves);
}

int movestree(TreeNode* root){
    return f(root).moves;
}

int main()
{
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(0);
    root->right = new TreeNode(0);
//    root->left->left = new treenode(1);
//    root->left->right = new treenode(8);
//    root->right->right = new treenode(7);

    cout << "Largest Moves Size: " << movestree(root) << endl;
    return 0;
}


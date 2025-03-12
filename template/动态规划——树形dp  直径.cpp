// 二叉树的直径
// 给你一棵二叉树的根节点，返回该树的直径
// 二叉树的 直径 是指树中任意两个节点之间最长路径的长度
// 这条路径可能经过也可能不经过根节点 root
// 两节点之间路径的 长度 由它们之间边数表示
// 测试链接 : https://leetcode.cn/problems/diameter-of-binary-tree/

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct Info {
    int diameter;
    int height;

    Info(int a,int b) :diameter(a),height(b) {}
};

Info f(TreeNode* x){
    if(x==nullptr){
        return Info(0,0);
    }

    Info infol = f(x->left);//左树全集信息
    Info infor = f(x->right);//右树全集信息

    int height=max(infol.height,infor.height)+1;
    int diameter=max(infol.diameter,infor.diameter);
    diameter=max(diameter,infol.height+infor.height);

    return Info(diameter,height);
}

int diametertree(TreeNode* root){
    return f(root).diameter;
}

int main()
{
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    cout << "Largest Diameter Size: " << diametertree(root) << endl;
    return 0;
}

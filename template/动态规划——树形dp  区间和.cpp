// 路径总和 III
// 给定一个二叉树的根节点 root ，和一个整数 targetSum
// 求该二叉树里节点值之和等于 targetSum 的 路径 的数目
// 路径 不需要从根节点开始，也不需要在叶子节点结束
// 但是路径方向必须是向下的（只能从父节点到子节点）
// 测试链接 : https://leetcode.cn/problems/path-sum-iii/

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
unordered_map<long, int> presum;//建立前缀和的哈希表
int target,ans;

void f(TreeNode* x, long sum) {
    if (x != nullptr) {
        sum += x->val; // 从头节点出发一路走到x的整体累加和
        ans += presum.find(sum-target)!=presum.end()?presum[sum-target]:0;
        presum[sum]= (presum.find(sum)!=presum.end()?presum[sum]:0) + 1;
        f(x->left, sum);
        f(x->right, sum);
        presum[sum]-=1;
    }
}
//这个是通过以某个点结尾求和
//ans第一次开始++实际上是在后面节点  然后消除自己的影响即presum[sum]-=1;

int pathSum(TreeNode* root) {
    presum[0]=1;
    f(root, 0);
    return ans;
}

int main()
{
    cin>>target;
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);
    cout<<pathSum(root);
    return 0;
}

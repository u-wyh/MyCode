// 移除子树后的二叉树高度
// 给你一棵 二叉树 的根节点 root ，树中有 n 个节点
// 每个节点都可以被分配一个从 1 到 n 且互不相同的值
// 另给你一个长度为 m 的数组 queries
// 你必须在树上执行 m 个 独立 的查询，其中第 i 个查询你需要执行以下操作：
// 从树中 移除 以 queries[i] 的值作为根节点的子树
// 题目所用测试用例保证 queries[i] 不等于根节点的值
// 返回一个长度为 m 的数组 answer
// 其中 answer[i] 是执行第 i 个查询后树的高度
// 注意：
// 查询之间是独立的，所以在每个查询执行后，树会回到其初始状态
// 树的高度是从根到树中某个节点的 最长简单路径中的边数
// 测试链接 : https://leetcode.cn/problems/height-of-binary-tree-after-subtree-removal-queries/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;

// 下标为节点的值
int dfn[MAXN];
// 下标为dfn序号
int deep[MAXN];
// 下标为dfn序号
int sz[MAXN];
int maxl[MAXN];//统计dfn序号小于i的最深高度
int maxr[MAXN];//统计dfn序号大于i的最深高度
int dfnCnt;
// 定义树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
int query[MAXN];
int ans[MAXN];
int n;

// 来到x节点，从头节点到x节点经过了k条边
void f(TreeNode* x, int k) {
    int i = ++dfnCnt;
    dfn[x->val] = i;//根据值做dfn
    deep[i] = k;//从头节点到如今节点边数就是深度
    sz[i] = 1;
    //根据dfn做deep  sz
    if (x->left != nullptr) {
        f(x->left, k + 1);
        sz[i] += sz[dfn[x->left->val]];//sz数组以dfn做序号
    }
    if (x->right != nullptr) {
        f(x->right, k + 1);
        sz[i] += sz[dfn[x->right->val]];
    }
}
//生成dfn  sz  deep 数组

void treeQueries(TreeNode* root) {
    dfnCnt = 0;
    f(root, 0);
    for (int i = 1; i <= dfnCnt; i++) {
        maxl[i] =max(maxl[i - 1], deep[i]);
    }
    maxr[dfnCnt + 1] = 0;
    for (int i = dfnCnt; i >= 1; i--) {
        maxr[i] =max(maxr[i + 1], deep[i]);
    }
    //完成maxl  maxr数组
    for (int i = 1; i <= n; i++) {
        int leftMax = maxl[dfn[query[i]] - 1];
        int rightMax = maxr[dfn[query[i]] + sz[dfn[query[i]]]];
        //每一次查询的时候  区间dfn[query[i]]到dfn[query[i]] + sz[dfn[query[i]]]-1不能算
        //那么查询一下左边和右边
        ans[i] =max(leftMax, rightMax);
    }
}

int main()
{
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(8);
    root->right = new TreeNode(9);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(7);
    root->left->left->right = new TreeNode(6);
    root->left->left->left = new TreeNode(4);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>query[i];
    }
    treeQueries(root);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}

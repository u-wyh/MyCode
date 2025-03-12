#include<bits/stdc++.h>
using namespace std;
//����ʵʱ��ѯ

const int MAXN = 500001;
int arr[MAXN];
int Sort[MAXN];
int tree[MAXN];
int n, m;

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= m) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i��Χ���ۼӺ�
long sum(int i) {
    long ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

// ����ԭʼֵv
// ��������ֵ(���򲿷�1~m�е��±�)
int Rank(int v) {
	int l = 1, r = m, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (Sort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

long compute() {
    sort(Sort+ 1,Sort+ n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] != Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    //������ȥ��
    for (int i = 1; i <= n; i++) {
        arr[i] = Rank(arr[i]);
        //��ԭ�������ֵ��Ϊ�����������еĴ�С����  ԭ�е����ݱ�����û��ʲô��
        //���������������  �Լ���Լ�ռ�
    }
    long ans = 0;
    for (int i = n; i >= 1; i--) {
        // �ұ��ж��������� <= ��ǰ��ֵ - 1
        ans += sum(arr[i] - 1);
        // ���ӵ�ǰ���ֵĴ�Ƶ
        add(arr[i], 1);
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        Sort[i]=arr[i];//��������  ���������ȥ��
    }
    cout<<compute();
    return 0;
}

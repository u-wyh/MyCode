// �����ظ�����
// ����һ������Ϊn����������nums�����������������50����ͬ��ֵ
// ͬʱ����m���˿͵Ķ���quantity����������quantity[i]�ǵ�iλ�˿Ͷ�������Ŀ
// �����ж��Ƿ��ܽ�nums�е������������Щ�˿ͣ������㣺
// ��iλ�˿�ǡ����quantity[i]����������iλ�˿��õ�������������ͬ��
// ÿλ�˿Ͷ�Ҫ������������Ҫ�󣬷����Ƿ��ܶ�����
// �������� : https://leetcode.cn/problems/distribute-repeating-integers/

#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[100005],quanity[15];
int dp[1<<11][55];

// ��ǰ���������֣����index������cnt[index]
// status : ����״̬��1����Ҫȥ���㣬0�Ѿ��������
bool f(int* cnt, int* sum, int status, int index) {
	if (status == 0) {
		return true;
	}
	// status != 0
	if (index == n) {
		return false;
	}
	if (dp[status][index] != 0) {
		return dp[status][index] == 1;
	}
	bool ans = false;
	int k = cnt[index];
	// ��������ʵ������ĵ�ö��
	// jö����status�������Ӽ�״̬
	// �����ס
	for (int j = status; j > 0; j = (j - 1) & status) {
		if (sum[j] <= k && f(cnt, sum, status ^ j, index + 1)) {
			ans = true;
			break;
		}
	}
	if (!ans) {
		ans = f(cnt, sum, status, index + 1);
	}
	dp[status][index] = ans ? 1 : -1;
	return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    sort(nums,nums+n);
    for(int i=0;i<m;i++){
        cin>>quanity[i];
    }
    int cunt = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] != nums[i]) {
            cunt++;
        }
    }
    int* cnt = new int[cunt];
    int c = 1;
    for (int i = 1, j = 0; i < n; i++) {
        if (nums[i - 1] != nums[i]) {
            cnt[j++] = c;
            c = 1;
        } else {
            c++;
        }
    }
    cnt[cunt - 1] = c;
    n=cunt;
//    for(int i=0;i<n;i++){
//        cout<<cnt[i]<<' ';
//    }
//    cout<<endl;
    //cout<<n<<endl;
    int* sum = new int[1 << m];
    for(int i=0;i<(1<<m);i++){
        sum[i]=0;
    }
    // �������ö��������quantity�е�ÿ���Ӽ�������Ҫ���ֵĸ���
    for (int i = 0, v, h; i < m; i++) {
        v = quanity[i];
        h = 1 << i;
        for (int j = 0; j < h; j++) {
            sum[h | j] = sum[j] + v;
        }
    }
//    for(int i=0;i<(1<<m);i++){
//        cout<<sum[i]<<' ';
//    }
//    cout<<endl;
    cout<<f(cnt, sum, (1 << m) - 1, 0);
    delete[] sum;
    delete[] cnt;
    return 0;
}

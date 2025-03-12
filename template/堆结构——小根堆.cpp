#include <bits/stdc++.h>
using namespace std;

int main() {
    // 使用lambda表达式创建一个小根堆
    priority_queue<int, vector<int>, greater<int>> pq;

    int n;
    cin>>n;
    for(int i=1,op;i<=n;i++){
        cin>>op;
        if(op==1){
            int d;
            cin>>d;
            pq.push(d);
            cout << "堆顶元素: " << pq.top() << endl;
        }else{
            if(!pq.empty()){
                pq.pop();
                if(!pq.empty()){
                    cout << "移除堆顶后，新的堆顶元素: " << pq.top() << endl;
                }else{
                    cout << "堆已空，请输入元素！"<<endl;
                }
            }else{
                cout << "堆已空，请输入元素！"<<endl;
            }
        }
    }

    return 0;
}

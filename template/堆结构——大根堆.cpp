#include <bits/stdc++.h>
using namespace std;

int main() {
    priority_queue<int> pq;

    int n;
    cin>>n;
    for(int i=1,op;i<=n;i++){
        cin>>op;
        if(op==1){
            int d;
            cin>>d;
            pq.push(d);
            cout << "�Ѷ�Ԫ��: " << pq.top() << endl;
        }else{
            if(!pq.empty()){
                pq.pop();
                if(!pq.empty()){
                    cout << "�Ƴ��Ѷ����µĶѶ�Ԫ��: " << pq.top() << endl;
                }else{
                    cout << "���ѿգ�������Ԫ�أ�"<<endl;
                }
            }else{
                cout << "���ѿգ�������Ԫ�أ�"<<endl;
            }
        }
    }

    return 0;
}


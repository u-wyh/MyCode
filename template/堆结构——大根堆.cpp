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
            cout << "¶Ñ¶¥ÔªËØ: " << pq.top() << endl;
        }else{
            if(!pq.empty()){
                pq.pop();
                if(!pq.empty()){
                    cout << "ÒÆ³ý¶Ñ¶¥ºó£¬ÐÂµÄ¶Ñ¶¥ÔªËØ: " << pq.top() << endl;
                }else{
                    cout << "¶ÑÒÑ¿Õ£¬ÇëÊäÈëÔªËØ£¡"<<endl;
                }
            }else{
                cout << "¶ÑÒÑ¿Õ£¬ÇëÊäÈëÔªËØ£¡"<<endl;
            }
        }
    }

    return 0;
}


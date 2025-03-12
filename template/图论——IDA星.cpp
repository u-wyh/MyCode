//https://acm.hdu.edu.cn/showproblem.php?pid=1560
//https://www.cnblogs.com/LuckyGlass-blog/p/9061081.html
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,depth;
int len[10],chr[10][4],mat[10];
char DNA[10][10];

//������������ڹ����޶ȵ�
inline int GetPri(){
	int ret=0;
	for(int j=0;j<4;j++){
		int Max=0;
		for(int i=0;i<n;i++)
			Max=max(Max,chr[i][j]);
		ret+=Max;
	}
	return ret;
}

bool ID_A_Star(int dep)
{
	int pri=GetPri();
	if(dep+pri>depth)
        return false;
	if(!pri){
        //��ʾ�����������  ����true
		return true;
    }
	for(int i=0;i<4;i++){
		char ch=i+'0';
        bool chg[10]={};//���ǻ��ݱ�־
        bool flag=true;
		for(int j=0;j<n;j++){
			if(DNA[j][mat[j]]==ch){
				chr[j][DNA[j][mat[j]]-'0']--;//��ʾ����ַ����������ĸ����1
				mat[j]++;//����ַ���ָ������һλ
				chg[j]=true;//���ڱ�� ׼������
				flag=false;//��ʾ�����Ч��
			}
		}
		if(!flag){
            //�����Ч��  ��ô���λ�þ��ǵ�ǰi����ĸ  ����������
            //���û��Ч�� ˵�����λ�������еĻ�������û�����õ�  �ǲ�Ӧ�õ�
			if(ID_A_Star(dep+1)){
				return true;
			}
		}
		for(int j=0;j<n;j++){
			if(chg[j]){
				mat[j]--,chr[j][DNA[j][mat[j]]-'0']++;
			}
		}
	}
	return false;
}

int main()
{
	int t;scanf("%d",&t);
	while(t--){
		memset(DNA,'\0',sizeof DNA);
		memset(chr,0,sizeof chr);
		memset(len,0,sizeof len);
		memset(mat,0,sizeof mat);
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%s",DNA[i]);
			len[i]=strlen(DNA[i]);
			for(int j=0;j<len[i];j++){
				switch(DNA[i][j]){
					case 'A': DNA[i][j]='0';chr[i][0]++;break;
					case 'C': DNA[i][j]='1';chr[i][1]++;break;
					case 'G': DNA[i][j]='2';chr[i][2]++;break;
					case 'T': DNA[i][j]='3';chr[i][3]++;break;
				}
			}
		}
		depth=GetPri();//��Ϊ���������ж�
		while(!ID_A_Star(0)){
			memset(mat,0,sizeof mat);
			depth++;
			//��ǰ��Ȳ��� ��Ҫ��һ
		}
		printf("%d\n",depth);
	}
	return 0;
}

//�����ļ���ز���
#ifndef TEXT_H
#define TETX_h

#include<iostream>
#include<fstream>
#include"Service.h"
#include"Manage.h"

string MENUTXT = "Menu.txt";//��ȫ�ֱ������� �������ֱ�Ӹ���Ϊ���ò˵�

void MenuLoad()
//���˵���Ϣ���ı��ж���  �������˵���ϵ
{
	ifstream f;
	f.open(MENUTXT);//�򿪲˵�
	if (!f.is_open()) {
		//�����ʧ��  ʹ�ñ��ò˵�
		MENUTXT = "ReliefPlan.txt";
		f.open(MENUTXT);
	}
	for (int i = 1; i <= 9; i++) {
		string kindname, kindstyle, num;//�����numҪװ����int
		int score, cnt;
		f.clear();
		getline(f, kindname);
		f.clear();
		getline(f, kindstyle);
		f.clear();
		getline(f, num);
		score = stoi(num);
		f.clear();
		getline(f, num);
		cnt = stoi(num);
		//����Ϣ���ļ��ж�ȡ����
		foodkind[i] = FOODKIND(kindname,kindstyle);
		for (int j = 1; j <= cnt; j++) {
			string id, name, num,need;
			int price, evalate;
			f.clear();
			getline(f, id);
			f.clear();
			getline(f, name);
			f.clear();
			getline(f, num);
			price = stoi(num);
			f.clear();
			getline(f, num);
			evalate = stoi(num);
			f.clear();
			getline(f, need);

			FOODKIND::addDish(foodkind[i],id,name,price,evalate,false);//��ɲ�Ʒ��Ϣ�ĳ�ʼ��
		}
	}
}

void MenuSave()
//�����޸ĺ���ļ�
{
	ofstream outFile(MENUTXT, ios::trunc);  // ���ļ����ضϣ���գ�����  
	ofstream outfile(MENUTXT, ios::app);
	for (int i = 1; i <= 9; i++) {
	    outfile << foodkind[i].nameprint() << endl;
	    outfile << foodkind[i].styleprint() << endl;
	    outfile << foodkind[i].evalateprint()<< endl;
	    outfile << foodkind[i].cntprint() << endl;

	    for (int j = 1; j <= foodkind[i].cntprint(); j++) {
	        //cout << foodkind[i].dish[j - 1].id << endl;
	        outfile << foodkind[i].dish[j - 1].id << endl;
	        outfile << foodkind[i].dish[j - 1].name << endl;
	        outfile << foodkind[i].dish[j - 1].price << endl;
	        outfile << foodkind[i].dish[j - 1].evaluate << endl;
	        outfile << foodkind[i].dish[j - 1].need << endl;
	    }
	}
	outfile.close();
	//����ļ���Ϣ�������޸� ��ô��������Ϣ���浽�ļ���  ���´�ʹ��
}



#endif // !TEXT_H

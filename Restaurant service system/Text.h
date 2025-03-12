//管理文件相关操作
#ifndef TEXT_H
#define TETX_h

#include<iostream>
#include<fstream>
#include"Service.h"
#include"Manage.h"

string MENUTXT = "Menu.txt";//以全局变量定义 有问题就直接更换为备用菜单

void MenuLoad()
//将菜单信息从文本中读入  并建立菜单关系
{
	ifstream f;
	f.open(MENUTXT);//打开菜单
	if (!f.is_open()) {
		//如果打开失败  使用备用菜单
		MENUTXT = "ReliefPlan.txt";
		f.open(MENUTXT);
	}
	for (int i = 1; i <= 9; i++) {
		string kindname, kindstyle, num;//这里的num要装换成int
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
		//将信息从文件中读取出来
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

			FOODKIND::addDish(foodkind[i],id,name,price,evalate,false);//完成菜品信息的初始化
		}
	}
}

void MenuSave()
//保存修改后的文件
{
	ofstream outFile(MENUTXT, ios::trunc);  // 打开文件并截断（清空）内容  
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
	//如果文件信息发生了修改 那么将所有信息保存到文件中  供下次使用
}



#endif // !TEXT_H

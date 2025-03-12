//管理系统头文件
#ifndef MANAGE_H
#define MANAGE_H

#include <iostream> 
#include <fstream>
#include <string>  
#include <iomanip>  
#include"Service.h"

using namespace std;

string PassWord;
int shift = 5;//将密码偏移定位5

// 加密函数，使用凯撒密码算法，将每个字母偏移shift位  
std::string encrypt(const std::string plainText, int shift) {
	std::string cipherText = "";
	for (char ch : plainText) {
		if (isalpha(ch)) {
			char base = islower(ch) ? 'a' : 'A';
			cipherText += (ch - base + shift) % 26 + base;
		}
		else {
			cipherText += ch; // 非字母字符保持不变  
		}
	}
	return cipherText;
}

// 解密函数，使用凯撒密码算法，将每个字母偏移-shift位  
std::string decrypt(const std::string cipherText, int shift) {
	return encrypt(cipherText, 26 - shift); // 解密其实就是加密shift的补数（26-shift）  
}

void GetPassWord()
{
	ifstream f;
	f.open("PassWord.txt");//打开菜单
	if (!f.is_open()) {
		//如果打开失败  直接命名密码
		PassWord = "ILOVEYOU";
	}
	else{
		f.clear();
		getline(f, PassWord);
		//cout << PassWord << endl;
		PassWord=decrypt(PassWord, shift);//解密函数
		//cout << "密码是：" << PassWord <<"（密码经过加密，一般不易看懂，在这里直接给出以供测试，实际使用时不会显示）" << endl;
		//这一行可以注释掉
	}
}
//将密码从文件中读取  便于核对

void cleanPassWordFile(string filePath) {
	std::ofstream outFile(filePath, ios::trunc);  // 打开文件并截断（清空）内容  

	if (!outFile) {
		std::cerr << "无法打开文件: " << filePath << std::endl;
	}
	else {
		// 文件已成功打开并清空，不需要写入任何内容  
		outFile.close();  // 关闭文件（ofstream析构函数也会自动关闭）  
	}
}

void ChangePassWord(string str="changeyourpassword")
{
	cleanPassWordFile("PassWord.txt");//清空原有文件内容

	ofstream outfile("PassWord.txt");
	str=encrypt(str, shift);//加密函数
	outfile << str << endl;
	outfile.close();
	//设置新密码

}

#endif // !MANAGE_H

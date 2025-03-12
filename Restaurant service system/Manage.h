//����ϵͳͷ�ļ�
#ifndef MANAGE_H
#define MANAGE_H

#include <iostream> 
#include <fstream>
#include <string>  
#include <iomanip>  
#include"Service.h"

using namespace std;

string PassWord;
int shift = 5;//������ƫ�ƶ�λ5

// ���ܺ�����ʹ�ÿ��������㷨����ÿ����ĸƫ��shiftλ  
std::string encrypt(const std::string plainText, int shift) {
	std::string cipherText = "";
	for (char ch : plainText) {
		if (isalpha(ch)) {
			char base = islower(ch) ? 'a' : 'A';
			cipherText += (ch - base + shift) % 26 + base;
		}
		else {
			cipherText += ch; // ����ĸ�ַ����ֲ���  
		}
	}
	return cipherText;
}

// ���ܺ�����ʹ�ÿ��������㷨����ÿ����ĸƫ��-shiftλ  
std::string decrypt(const std::string cipherText, int shift) {
	return encrypt(cipherText, 26 - shift); // ������ʵ���Ǽ���shift�Ĳ�����26-shift��  
}

void GetPassWord()
{
	ifstream f;
	f.open("PassWord.txt");//�򿪲˵�
	if (!f.is_open()) {
		//�����ʧ��  ֱ����������
		PassWord = "ILOVEYOU";
	}
	else{
		f.clear();
		getline(f, PassWord);
		//cout << PassWord << endl;
		PassWord=decrypt(PassWord, shift);//���ܺ���
		//cout << "�����ǣ�" << PassWord <<"�����뾭�����ܣ�һ�㲻�׿�����������ֱ�Ӹ����Թ����ԣ�ʵ��ʹ��ʱ������ʾ��" << endl;
		//��һ�п���ע�͵�
	}
}
//��������ļ��ж�ȡ  ���ں˶�

void cleanPassWordFile(string filePath) {
	std::ofstream outFile(filePath, ios::trunc);  // ���ļ����ضϣ���գ�����  

	if (!outFile) {
		std::cerr << "�޷����ļ�: " << filePath << std::endl;
	}
	else {
		// �ļ��ѳɹ��򿪲���գ�����Ҫд���κ�����  
		outFile.close();  // �ر��ļ���ofstream��������Ҳ���Զ��رգ�  
	}
}

void ChangePassWord(string str="changeyourpassword")
{
	cleanPassWordFile("PassWord.txt");//���ԭ���ļ�����

	ofstream outfile("PassWord.txt");
	str=encrypt(str, shift);//���ܺ���
	outfile << str << endl;
	outfile.close();
	//����������

}

#endif // !MANAGE_H

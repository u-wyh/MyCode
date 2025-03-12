#ifndef SERVICE_H  
#define SERVICE_H  

#include <iostream>  
#include <string>  
#include <iomanip>  

using namespace std;

struct Dish {
    string id;       // ��Ʒ���  
    string name;     // ��Ʒ����  
    int price;       // ��Ʒ�۸�  
    int evaluate;    // ��Ʒ���۵÷�  
    bool need;       // ��Ʒ�Ƿ���Ҫ  
    Dish(string ID = "0000", string NAME = "noname", int PRICE = 0, int EVALATE = 0, bool NEED = false)
        :id(ID), name(NAME), price(PRICE), evaluate(EVALATE), need(NEED){}
};

class FOODKIND {
public:
    FOODKIND(string name = "δ֪��ϵ", string style = "δ֪��ζ", int score = 0, int cnt = 0)
        : kindname(name), kindstyle(style), kindevaluate(score), kindcnt(cnt) {}

    void Set(string name, string style, int score, int cnt = 0); // ���ò�ϵ��Ϣ��ע��cntͨ����addDish����  
    void KindShow(ostream& out) const; // ��ϵ������ʾ����  
    void KindMenuShow(ostream& out) const; // ��ϵѡ�������ʾ����  

    Dish dish[10]; // ��ϵ�еĲ�Ʒ��Ϣ������������10��  

    static void Initdish(); // ��ʼ����Ʒ������Ϊ��̬��Ա����  
    static void addDish(FOODKIND& kind, const std::string& id, const std::string& name, int price, int evaluate, bool need); // ��Ӳ�Ʒ����  
    int cntprint() 
    {
        return kindcnt;//����ж��ٸ���Ʒ
    }

    string nameprint() {
        return kindname;
    }

    string styleprint() {
        return kindstyle;
    }

    int evalateprint() {
        return kindevaluate;
    }

    void cntsub(){
        kindcnt--;
    }

private:
    string kindname; // ��ϵ����  
    string kindstyle; // ��ϵ���  
    int kindevaluate; // ��ϵ���۵÷�  
    int kindcnt; // ��ϵ�еĲ�Ʒ����  
};

extern FOODKIND foodkind[10]; // ����ȫ�����飬���ڴ洢��ͬ��ϵ����Ϣ  

#endif // SERVICE_H
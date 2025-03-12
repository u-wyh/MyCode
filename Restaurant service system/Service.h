#ifndef SERVICE_H  
#define SERVICE_H  

#include <iostream>  
#include <string>  
#include <iomanip>  

using namespace std;

struct Dish {
    string id;       // 菜品编号  
    string name;     // 菜品名称  
    int price;       // 菜品价格  
    int evaluate;    // 菜品评价得分  
    bool need;       // 菜品是否需要  
    Dish(string ID = "0000", string NAME = "noname", int PRICE = 0, int EVALATE = 0, bool NEED = false)
        :id(ID), name(NAME), price(PRICE), evaluate(EVALATE), need(NEED){}
};

class FOODKIND {
public:
    FOODKIND(string name = "未知菜系", string style = "未知风味", int score = 0, int cnt = 0)
        : kindname(name), kindstyle(style), kindevaluate(score), kindcnt(cnt) {}

    void Set(string name, string style, int score, int cnt = 0); // 重置菜系信息，注意cnt通常由addDish更新  
    void KindShow(ostream& out) const; // 菜系界面显示函数  
    void KindMenuShow(ostream& out) const; // 菜系选择界面显示函数  

    Dish dish[10]; // 菜系中的菜品信息，这里假设最多10道  

    static void Initdish(); // 初始化菜品，声明为静态成员函数  
    static void addDish(FOODKIND& kind, const std::string& id, const std::string& name, int price, int evaluate, bool need); // 添加菜品函数  
    int cntprint() 
    {
        return kindcnt;//输出有多少个菜品
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
    string kindname; // 菜系名称  
    string kindstyle; // 菜系简介  
    int kindevaluate; // 菜系评价得分  
    int kindcnt; // 菜系中的菜品数量  
};

extern FOODKIND foodkind[10]; // 声明全局数组，用于存储不同菜系的信息  

#endif // SERVICE_H
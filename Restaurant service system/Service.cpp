#include "Service.h"  

FOODKIND foodkind[10]; // 定义全局数组  

// 添加菜品函数实现  
void FOODKIND::addDish(FOODKIND& kind, const std::string& id, const std::string& name, int price, int evaluate, bool need) {
    if (kind.kindcnt < 10) { // 确保不会超出数组界限  
        kind.dish[kind.kindcnt].id = id;
        kind.dish[kind.kindcnt].name = name;
        kind.dish[kind.kindcnt].price = price;
        kind.dish[kind.kindcnt].evaluate = evaluate;
        kind.dish[kind.kindcnt].need = need;
        kind.kindcnt++; // 更新菜系中的菜品数量  
    }
    else {
        cerr << "Error: Exceeded maximum dish count for this cuisine." << endl;
    }
}
//为菜系添加菜品  但是不能超过10道菜 
//如果想要增加到10道以上   就要更改这里的限制

// KIND类的其他成员函数实现  
void FOODKIND::Set(string name, string style, int score, int cnt) {
    kindname = name;
    kindstyle = style;
    kindevaluate = score;
    // 注意：kindcnt通常由addDish函数更新，这里不设置  
}

void FOODKIND::KindShow(ostream& out) const {
    cout << "主界面>>查看菜单>>" << kindname << endl << endl;
    out << setw(20) << "菜系名称" << setw(20) << "菜系简介"
        << setw(20) << "菜品数量" << endl
        << setw(20) << kindname << setw(20)
        << kindstyle << setw(20)
        << kindcnt << endl;
    out << setw(20) << "菜品编号" << setw(20) << "菜名"
        << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
    for (int i = 0; i < kindcnt; i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
        out << setw(20) << dish[i].id << setw(20) << dish[i].name
            << setw(20) << dish[i].price << setw(20) << dish[i].evaluate << setw(20) << (dish[i].need ? "是" : "否") << endl;
    }
}
//已点菜单展示

void  FOODKIND::KindMenuShow(ostream& out) const {
    cout << "*********************************菜品选择*******************************\n";
    cout << "0.返回主界面  \n";
    cout << "1.返回点单界面 \n";
    for (int i = 0; i < kindcnt; i++) {
        cout << i + 2 << "." << dish[i].name << endl;
    }
}
//菜单功能选择展示功能

// 初始化函数，使用addDish添加菜品  
void FOODKIND::Initdish() {
    foodkind[1] = FOODKIND("鲁菜", "山东风味");
    foodkind[2] = FOODKIND("川菜", "四川风味");
    foodkind[3] = FOODKIND("闵菜", "福建风味");
    foodkind[4] = FOODKIND("粤菜", "广东风味");
    foodkind[5] = FOODKIND("苏菜", "江苏风味");
    foodkind[6] = FOODKIND("浙菜", "浙江风味");
    foodkind[7] = FOODKIND("徽菜", "安徽风味");
    foodkind[8] = FOODKIND("湘菜", "湖南风味");
    foodkind[9] = FOODKIND("其他", "暂无介绍");
    foodkind[0] = FOODKIND("000", "0000");

    addDish(foodkind[0], "0000", "占位符", 0, 0, false); // 可选：为数组初始化一个占位符或跳过直接设置kindcnt  

    addDish(foodkind[1], "0001", "油焖大虾", 85, 9, false);
    addDish(foodkind[1], "0002", "一品豆腐", 35, 7, false);
    addDish(foodkind[1], "0003", "九转大肠", 55, 8, false);

    addDish(foodkind[2], "1001", "麻婆豆腐", 30, 6, false);
    addDish(foodkind[2], "1002", "宫保鸡丁", 55, 9, false);
    addDish(foodkind[2], "1003", "水煮鱼片", 45, 5, false);

    addDish(foodkind[3], "2001", "佛跳墙", 45, 8, false);
    addDish(foodkind[3], "2002", "闽醉排骨", 65, 5, false);
    addDish(foodkind[3], "2003", "刷九品", 75, 8, false);

    addDish(foodkind[4], "3001", "白切鸡", 35, 7, false);
    addDish(foodkind[4], "3002", "蜜汁叉烧", 25, 5, false);
    addDish(foodkind[4], "3003", "清蒸石斑鱼", 65, 9, false);

    addDish(foodkind[5], "4001", "松鼠桂鱼", 50, 6, false);
    addDish(foodkind[5], "4002", "蟹粉狮子头", 45, 7, false);
    addDish(foodkind[5], "4003", "金陵盐水鸭", 35, 5, false);

    addDish(foodkind[6], "5001", "西湖醋鱼", 45, 5, false);
    addDish(foodkind[6], "5002", "龙井虾仁", 55, 8, false);
    addDish(foodkind[6], "5003", "东坡肉", 65, 8, false);

    addDish(foodkind[7], "6001", "黄山炖鸽", 35, 7, false);
    addDish(foodkind[7], "6002", "腌鲜鳜鱼", 45, 7, false);
    addDish(foodkind[7], "6003", "徽州毛豆腐", 25, 8, false);

    addDish(foodkind[8], "7001", "辣椒炒肉", 35, 8, false);
    addDish(foodkind[8], "7002", "腊味合蒸", 40, 7, false);
    addDish(foodkind[8], "7003", "剁椒鱼头", 45, 9, false);

    addDish(foodkind[9], "8001", "纸巾", 5, 3, false);
    addDish(foodkind[9], "8002", "饮料畅饮", 10, 4, false);
    addDish(foodkind[9], "8003", "米饭", 2, 5, false);

    // 注意：由于addDish已经更新了kindcnt，这里不需要再手动设置  
}


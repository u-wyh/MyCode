#include "Service.h"  

FOODKIND foodkind[10]; // ����ȫ������  

// ��Ӳ�Ʒ����ʵ��  
void FOODKIND::addDish(FOODKIND& kind, const std::string& id, const std::string& name, int price, int evaluate, bool need) {
    if (kind.kindcnt < 10) { // ȷ�����ᳬ���������  
        kind.dish[kind.kindcnt].id = id;
        kind.dish[kind.kindcnt].name = name;
        kind.dish[kind.kindcnt].price = price;
        kind.dish[kind.kindcnt].evaluate = evaluate;
        kind.dish[kind.kindcnt].need = need;
        kind.kindcnt++; // ���²�ϵ�еĲ�Ʒ����  
    }
    else {
        cerr << "Error: Exceeded maximum dish count for this cuisine." << endl;
    }
}
//Ϊ��ϵ��Ӳ�Ʒ  ���ǲ��ܳ���10���� 
//�����Ҫ���ӵ�10������   ��Ҫ�������������

// KIND���������Ա����ʵ��  
void FOODKIND::Set(string name, string style, int score, int cnt) {
    kindname = name;
    kindstyle = style;
    kindevaluate = score;
    // ע�⣺kindcntͨ����addDish�������£����ﲻ����  
}

void FOODKIND::KindShow(ostream& out) const {
    cout << "������>>�鿴�˵�>>" << kindname << endl << endl;
    out << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
        << setw(20) << "��Ʒ����" << endl
        << setw(20) << kindname << setw(20)
        << kindstyle << setw(20)
        << kindcnt << endl;
    out << setw(20) << "��Ʒ���" << setw(20) << "����"
        << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
    for (int i = 0; i < kindcnt; i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
        out << setw(20) << dish[i].id << setw(20) << dish[i].name
            << setw(20) << dish[i].price << setw(20) << dish[i].evaluate << setw(20) << (dish[i].need ? "��" : "��") << endl;
    }
}
//�ѵ�˵�չʾ

void  FOODKIND::KindMenuShow(ostream& out) const {
    cout << "*********************************��Ʒѡ��*******************************\n";
    cout << "0.����������  \n";
    cout << "1.���ص㵥���� \n";
    for (int i = 0; i < kindcnt; i++) {
        cout << i + 2 << "." << dish[i].name << endl;
    }
}
//�˵�����ѡ��չʾ����

// ��ʼ��������ʹ��addDish��Ӳ�Ʒ  
void FOODKIND::Initdish() {
    foodkind[1] = FOODKIND("³��", "ɽ����ζ");
    foodkind[2] = FOODKIND("����", "�Ĵ���ζ");
    foodkind[3] = FOODKIND("�ɲ�", "������ζ");
    foodkind[4] = FOODKIND("����", "�㶫��ζ");
    foodkind[5] = FOODKIND("�ղ�", "���շ�ζ");
    foodkind[6] = FOODKIND("���", "�㽭��ζ");
    foodkind[7] = FOODKIND("�ղ�", "���շ�ζ");
    foodkind[8] = FOODKIND("���", "���Ϸ�ζ");
    foodkind[9] = FOODKIND("����", "���޽���");
    foodkind[0] = FOODKIND("000", "0000");

    addDish(foodkind[0], "0000", "ռλ��", 0, 0, false); // ��ѡ��Ϊ�����ʼ��һ��ռλ��������ֱ������kindcnt  

    addDish(foodkind[1], "0001", "���˴�Ϻ", 85, 9, false);
    addDish(foodkind[1], "0002", "һƷ����", 35, 7, false);
    addDish(foodkind[1], "0003", "��ת��", 55, 8, false);

    addDish(foodkind[2], "1001", "���Ŷ���", 30, 6, false);
    addDish(foodkind[2], "1002", "��������", 55, 9, false);
    addDish(foodkind[2], "1003", "ˮ����Ƭ", 45, 5, false);

    addDish(foodkind[3], "2001", "����ǽ", 45, 8, false);
    addDish(foodkind[3], "2002", "�����Ź�", 65, 5, false);
    addDish(foodkind[3], "2003", "ˢ��Ʒ", 75, 8, false);

    addDish(foodkind[4], "3001", "���м�", 35, 7, false);
    addDish(foodkind[4], "3002", "��֭����", 25, 5, false);
    addDish(foodkind[4], "3003", "����ʯ����", 65, 9, false);

    addDish(foodkind[5], "4001", "�������", 50, 6, false);
    addDish(foodkind[5], "4002", "з��ʨ��ͷ", 45, 7, false);
    addDish(foodkind[5], "4003", "������ˮѼ", 35, 5, false);

    addDish(foodkind[6], "5001", "��������", 45, 5, false);
    addDish(foodkind[6], "5002", "����Ϻ��", 55, 8, false);
    addDish(foodkind[6], "5003", "������", 65, 8, false);

    addDish(foodkind[7], "6001", "��ɽ����", 35, 7, false);
    addDish(foodkind[7], "6002", "��������", 45, 7, false);
    addDish(foodkind[7], "6003", "����ë����", 25, 8, false);

    addDish(foodkind[8], "7001", "��������", 35, 8, false);
    addDish(foodkind[8], "7002", "��ζ����", 40, 7, false);
    addDish(foodkind[8], "7003", "�罷��ͷ", 45, 9, false);

    addDish(foodkind[9], "8001", "ֽ��", 5, 3, false);
    addDish(foodkind[9], "8002", "���ϳ���", 10, 4, false);
    addDish(foodkind[9], "8003", "�׷�", 2, 5, false);

    // ע�⣺����addDish�Ѿ�������kindcnt�����ﲻ��Ҫ���ֶ�����  
}


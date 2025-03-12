#define _CRT_SECURE_NO_WARNINGS

#include <stdexcept>  
#include <sstream>  
#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>
#include <climits>
#include "Service.h"  
#include "Manage.h"
#include "Text.h"

using namespace std;

int people; // �˿͵�����  
int cost;//Ŀǰ�ѵ�˹��ƶ���Ԫ
int dishCnt = 0;//Ŀǰ�ѵ�˹��ƶ��ٸ�

Dish orderdish[90];//����������ڴ����ѵ��Ʒ

void MyOrderShow()//��������Ĺ�������ʾ�����Ѿ�����Ĳ�Ʒ
{
    std::cout << "������>>�ҵĲ˵�\n\n";

    std::cout << "**********************************************************************************************************\n";
    std::cout << "**********************************************�ѵ�˵�****************************************************\n\n";
    if (dishCnt == 0) {
        std::cout << "�����ڻ�û��ѡ���κβ�Ʒ!\n";
    }
    else {
        std::cout <<setw(5)<<"���" << setw(20) << "��Ʒ���" << setw(20) << "����"
            << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
        for (int i = 1; i <= dishCnt ; i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
            //int k = 1;

            std::cout <<setw(5)<<i <<setw(20) << orderdish[i].id << setw(20) << orderdish[i].name
                << setw(20) << orderdish[i].price << setw(20) << orderdish[i].evaluate << setw(20) << (orderdish[i].need ? "��" : "��") << endl;
        }

        std::cout << "Ŀǰ�Ѿ�ѡ���� " << dishCnt << " ���ˣ����ƻ��� " << cost << " Ԫ\n" << endl;
    }

}

int readIntFromInput(int limit) throw(char, int)
//limit�����ж��������������
{
    std::string input;
    std::getline(std::cin, input); // ʹ��getline����ȡֱ���ո�  

    // ���Խ�����ת��Ϊ����  
    std::istringstream iss(input);
    int num;
    if (!(iss >> num) || !iss.eof()) {
        // ���ת��ʧ�ܻ����������л���ʣ���ַ���˵�����벻�Ǵ�������  
        throw (char)1;
    }
    if (num > limit||num<0) {
        throw (int)1;
    }

    return num;
} //���������쳣���

bool cmp(Dish a, Dish b) {
    return a.id < b.id;
}
//���Ѿ�ѡ��Ĳ˵����ձ�����

int main() {
    // ��ʼ����Ʒ��Ϣ  
    MenuLoad();

    cout << "***********************************************\n";
    cout << "*******************��ӭ����!*******************\n������Ͳ������� ";
    bool peopleright = false;//�ж������Ƿ�Ϸ�
    while (!peopleright) {
        try {
            people = readIntFromInput(INT_MAX);
            peopleright = true;
        }
        catch (char) {
            // ���񲢴����쳣  
            cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
        }
        catch (int) {
            cout << "û���������ѡ�������ѡ��:";
        }
    }
    //���people��0���� ��ô�ͽ������ϵͳ  ����������ϵͳ
    if (people != 0) {
        //����ϵͳ
        cout << "��������������е㵥��������κ�������Ѱ�ҷ���Ա������ף���ò���죡\n";
        cout << "��������㵥ϵͳ\n";
        system("pause");
        system("cls");
        //getchar();//����������Ļ��з�
        while (true) {
            cout << "***********************        ��ӭ����!     **************************\n";
            cout << "***********************1.�鿴�˵�            **************************\n";
            cout << "***********************2.�ҵĲ˵�            **************************\n";
            cout << "***********************0.�òͽ���            **************************\n";
            cout << "����������ѡ�� ";
            int op;
            bool opright = false;//�ж������Ƿ�Ϸ�
            while (!opright) {
                try{
                    op = readIntFromInput(2);
                    opright = true;
                }
                catch (char) {
                    // ���񲢴����쳣  
                    cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                }
                catch (int) {
                    cout << "û���������ѡ�������ѡ��:";
                }
            }
            if (op == 0) {
                //�˳�����ϵͳ
                system("cls");
                if (dishCnt != 0) {
                    //����Ѿ����˲�Ʒ  ��ô�ڽ�����ʱ���˵����
                    sort(orderdish + 1, orderdish + dishCnt + 1, cmp);
                    cout << "**********************************************************************************************************\n";
                    cout << "**********************************************�ҵ��˵�****************************************************\n\n";

                    cout << setw(5) << "���" << setw(20) << "��Ʒ���" << setw(20) << "����"
                        << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
                    for (int i = 1; i <= dishCnt; i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                        //int k = 1;

                        cout << setw(5) << i << setw(20) << orderdish[i].id << setw(20) << orderdish[i].name
                            << setw(20) << orderdish[i].price << setw(20) << orderdish[i].evaluate << setw(20) << (orderdish[i].need ? "��" : "��") << endl;
                    }
                    std::cout << "\n\n���� " << dishCnt << " ���ˣ��ܻ��� " << cost << " Ԫ\n" << endl;
                    cout << "��ӭ�´ι��٣�\n";
                        // ��ȡ��ǰʱ���
                    auto now = std::chrono::system_clock::now();

                    // ��ʱ���ת��Ϊtime_t���ͣ��Ա�ʹ��ctime����
                     std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

                    // ��time_t����ת��Ϊ����ʱ��
                    std::tm* localTime = std::localtime(&currentTime);

                    // ���������ʽ��ȷ��ʱ������λ����ʾ
                    cout << "��ǰʱ��Ϊ�� ";
                    std::cout << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

                }
                break;
            }
            system("cls");  

            if (op == 1) {
            //�㵥����
            a://������һ��goto������ڷ��ز˵�����
                cout << "������>>�鿴�˵�\n\n";
                cout << "********1.³��\t2.����\t3.����\t********\n";
                cout << "********4.����\t5.�ղ�\t6.���\t********\n";
                cout << "********7.�ղ�\t8.���\t9.��ˮ��ֽ��****\n";
                cout << "********0.����������            ********\n";
                cout << "�����ѡ�� [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright=false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindop == 0) {
                    //����������
                    system("cls");
                    continue;
                }
                system("cls");
                if (kindop > 0 && kindop <= 9) {
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    foodkind[kindop].KindShow(cout); // ��ʾ��ѡ��ϵ�Ĳ˵� 
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << endl << endl;
                    foodkind[kindop].KindMenuShow(cout);
                    cout << "�����ѡ��: ";
                b://����һ��goto���  ���ڷ��ؼ����㵥
                    int kindmenuop;
                    bool kindmenuopright = false;
                    while (!kindmenuopright) {
                        try{
                            kindmenuop = readIntFromInput(foodkind[kindop].cntprint() + 1);
                            kindmenuopright = true;
                        }
                        catch (char) {
                            // ���񲢴����쳣  
                            cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                        }
                        catch (int) {
                            cout << "û���������ѡ�������ѡ��:";
                        }
                    }
                    if (kindmenuop == 0) {
                        system("cls");
                        continue;
                    }
                    else if (kindmenuop == 1) {
                        system("cls");
                        goto a;
                    }
                    else if (kindmenuop <= foodkind[kindop].cntprint() + 1) {
                        if (foodkind[kindop].dish[kindmenuop - 2].need == true){
                            //���ﲻ֧��һ���˱�ѡ����   �����Ҫ�޸ĵĻ�  ��Ҫ��need��Ϊquality  �����������ʱ��֧��
                            cout << "������Ѿ���ѡ����������Ʒʵ�ݣ������ٴ�ѡ��\n";
                            cout << "�����ѡ��: ";
                            goto b;
                        }
                        foodkind[kindop].dish[kindmenuop - 2].need = true;//�����������Ϊ�ѱ�ѡ���
                        cost += foodkind[kindop].dish[kindmenuop - 2].price;//�ܵĻ���Ҫ��������˵ļ۸�
                        orderdish[++dishCnt] = foodkind[kindop].dish[kindmenuop - 2];//��ѡ��Ĳ�Ʒ���뵽�ҵĲ˵�
                        cout << "�����ѡ��: ";
                        goto b;
                    }
                }
            }
            else if (op == 2){
            e:
                cout << "������>>�ҵĲ˵�\n\n";
                cout << "********1.��ʾ�ҵĲ˵�\t********\n";
                cout << "********2.�����㵥   \t********\n";
                cout << "********3.ɾ��ĳ����    ********\n";
                cout << "********0.����������    ********\n";
                cout << "�����ѡ�� [1 2 3 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(3);
                        kindopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                system("cls");
                if (kindop == 0) {
                    continue;
                    //���ﲻ��Ҫʲô����  ֱ�Ӿͻ᷵��
                }
                else if (kindop == 1) {
                    sort(orderdish + 1, orderdish + dishCnt + 1, cmp);
                    MyOrderShow();
                    cout << "********1.���ص㵥����     ********\n";
                    cout << "********2.�����ҵĲ˵�     ********\n";
                    cout << "********0.����������       ********\n";
                    cout << "�����ѡ�� [1 2 0]: ";
                    int choice;
                    bool choiceright = false;
                    while (!choiceright) {
                        try {
                            choice = readIntFromInput(3);
                            choiceright = true;
                        }
                        catch (char) {
                            // ���񲢴����쳣  
                            cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                        }
                        catch (int) {
                            cout << "û���������ѡ�������ѡ��:";
                        }
                    }
                    system("cls");
                    if (choice == 0) {
                        continue;
                    }
                    else if (choice == 1)
                    {
                        goto a;
                    }
                    else if (choice == 2)
                    {
                        goto e;
                    }
                    //��������Ҫ�������������ת
                }
                else if (kindop == 2){
                    system("cls");
                    goto a;
                }
                else if (kindop == 3){
                    MyOrderShow();
                    int choice=-1;
                    while (choice != 0&&dishCnt!=0) {
                        cout << "����������ɾ���ڼ����ˣ�ѡ0����ɾ������ ";
                        bool choiceright = false;
                        while (!choiceright) {
                            try {
                                choice = readIntFromInput(dishCnt);
                                choiceright = true;
                            }
                            catch (char) {
                                // ���񲢴����쳣  
                                cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                            }
                            catch (int) {
                                cout << "�������û����һ���ˣ�\n���������룺 ";
                            }
                        }
                        if (choice == 0)
                            break;
                        for (int i = 1; i <= 9; i++) {
                            for (int j = 0; j < foodkind[i].cntprint(); j++){
                                if (foodkind[i].dish[j].id == orderdish[choice].id) {
                                    foodkind[i].dish[j].need = false;
                                    i = 10;
                                    break;
                                }
                            }
                        }
                        cost -= orderdish[choice].price;
                        orderdish[choice].need = false;
                        //������ɾ������˵�Ӱ��
                        for (int i = choice + 1; i <= dishCnt; i++) {
                            orderdish[i - 1] = orderdish[i];
                        }
                        dishCnt--;
                        cout << "ɾ���ɹ����˵�չʾ��\n";
                        MyOrderShow();
                        cout << "�����������" << endl;
                    }
                    system("pause");
                    system("cls");
                    cout << "********1.���ص㵥����     ********\n";
                    cout << "********2.�����ҵĲ˵�     ********\n";
                    cout << "********0.����������       ********\n";
                    cout << "�����ѡ�� [1 2 0]: ";
                    int lastchoice;
                    bool lastchoiceright = false;
                    while (!lastchoiceright) {
                        try {
                            lastchoice = readIntFromInput(2);
                            lastchoiceright = true;
                        }
                        catch (char) {
                            // ���񲢴����쳣  
                            cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                        }
                        catch (int) {
                            cout << "û���������ѡ�������ѡ��:";
                        }
                    }
                    system("cls");
                    if (lastchoice == 0) {
                        continue;
                    }
                    else if (lastchoice == 1){
                        goto a;
                    }
                    else if (lastchoice == 2){
                        goto e;
                    }
                    //���ϲ��ָ�����Ҫ������ת
                }
            }
        }
    }
    else
    {
        cout << "�����������ϵͳ\n";
        system("pause");
        system("cls");
        GetPassWord();//���ļ��ж�ȡ����
        cout << "�����ǣ�" << PassWord << "�����뾭�����ܣ�һ�㲻�׿�����������ֱ�Ӹ����Թ����ԣ�ʵ��ʹ��ʱ������ʾ��" << endl;
        cout << "�����������ϵͳ���룬��֤���: ";
        int passcnt = 0;//�Դ����ͳ��
        //h://���h������Ļ����ᵼ�����������𰸣�2��getchar()��
        string password;
        //getchar();//�������з�Ӱ��
        h:
        getline(cin,password);//�������ո�
        if (password == PassWord) 
        {
            cout << "������ȷ����ӭ�������ϵͳ��\n";
            system("pause");
            system("cls");
            g:
            cout << "*******************        ��ӭ�������ϵͳ!     **********************\n";
            cout << "***********************0.�˳�ϵͳ            **************************\n";
            cout << "***********************1.�޸�����            **************************\n";
            cout << "***********************2.�޸Ĳ�Ʒ            **************************\n";
            cout << "***********************3.���Ӳ�Ʒ            **************************\n";
            cout << "***********************4.���ٲ�Ʒ            **************************\n";
            cout << "����������ѡ�� ";
            int choice;//ѡ��ѡ��
            bool choiceright = false;
            while (!choiceright) {
                try{
                    choice = readIntFromInput(4);
                    choiceright = true;
                }
                catch (char) {
                    // ���񲢴����쳣  
                    cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                }
                catch (int) {
                    cout << "û���������ѡ�������ѡ��:";
                }
            }
            system("cls");

            if (choice == 0) {
                cout << "3����Զ��˳�����ϵͳ" << endl;
                int seconds = 3;
                while (seconds > 0) {
                    //std::cout << "Remaining time: " << seconds << " seconds" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // ��ͣһ��
                    --seconds; // ����ʣ������
                }
                //system("pause");
                system("cls");
            }
            else if (choice == 1){
                cout << "����ϵͳ>>�޸�����\n\n";
                cout << "����������ԭ����: " ;
                string word;
                GetPassWord();//���ļ��ж�ȡ����  ����Ҫ���µ���  ��Ϊ���θ��������ʱ��  ���ԭʼ����û�б仯
                getline(cin, word);
                cout << endl;

                if (word == PassWord) {
                    string Changeword;
                    cout << "�������޸ĺ������: ";
                    //getchar();//����������Ӱ��(������Ҫ���� ����ڶ�����������  ���������һ�����뵼�´���  ��������Ϊ����Ҳ����һ��)
                    getline(cin, Changeword);//����������ڿո�
                    ChangePassWord(Changeword);
                    cout << "�����޸ĳɹ���\n";
                    cout << endl << endl;
                }
                else {
                    cout << "��������޷����ģ�" << endl;
                    system("pause");
                    system("cls");
                }
                cout << "*******1.���ع������  *******\n";
                cout << "*******0.�˳�����ϵͳ  *******\n";
                cout << "����������ѡ�� ";
                int op;
                bool opright=false;
                while (!opright) {
                    try{
                        op = readIntFromInput(1);
                        opright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (op == 1) {
                    system("cls");
                    goto g;
                }
                system("cls");
            }
            else if (choice == 2){
                bool change = false;
                y:
                cout << "����ϵͳ>>�޸Ĳ�Ʒ\n\n";
                cout << "********1.³��\t2.����\t3.����\t********\n";
                cout << "********4.����\t5.�ղ�\t6.���\t********\n";
                cout << "********7.�ղ�\t8.���\t9.��ˮ��ֽ��****\n";
                cout << "********0.����������            ********\n";
                cout << "�����ѡ����Ҫ�޸ĵĲ�Ʒ������ϵ [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindop == 0) {
                    system("cls");
                    goto g;
                }
                system("cls");
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << "����ϵͳ>>�޸Ĳ�Ʒ>>" << foodkind[kindop].nameprint() << endl << endl;
                cout << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
                    << setw(20) << "��Ʒ����" << endl
                    << setw(20) << foodkind[kindop].nameprint() << setw(20)
                    << foodkind[kindop].styleprint() << setw(20)
                    << foodkind[kindop].cntprint() << endl;
                cout << setw(20) << "��Ʒ���" << setw(20) << "����"
                    << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ��޸�" << endl;
                for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                    cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                        << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate << 
                        setw(20) << (foodkind[kindop].dish[i].need ? "��" : "��") << endl;
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << endl << endl;
                foodkind[kindop].KindMenuShow(cout);
                int kindmenuop;
                cout << "�����ѡ��: ";
            x://����һ��goto���  ���ڷ��ؼ����㵥
                bool kindmenuopright = false;
                while (!kindmenuopright) {
                    try{
                        kindmenuop = readIntFromInput(foodkind[kindop].cntprint() + 1);
                        kindmenuopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindmenuop == 0) {
                    if(change)
                        MenuSave();
                    system("cls");
                    goto g;
                }
                else if (kindmenuop == 1) {
                    if(change)
                        MenuSave();
                    system("cls");
                    goto y;
                }
                else if (kindmenuop <= foodkind[kindop].cntprint() + 1) {
                    change = true;
                    if (foodkind[kindop].dish[kindmenuop - 2].need == true)
                    {
                        cout << "������Ѿ����޸ģ�����ϸѡ��!\n";
                        bool Secondop;
                        cout << "�Ƿ�����Ҫ��������ˣ�����������ѡ��1-��/0-�� ��";
                        cin >> Secondop;
                        getchar();
                        if (!Secondop) {
                            cout << "�����ѡ��: ";
                            goto x;
                        }
                    }
                    cout << "�������޸ĺ����Ϣ[��� ���� �۸� ���۵÷�]�� ";
                    string Changeid, Changename;
                    int Changeprice, Changeevalate;
                    cin >> Changeid >> Changename >> Changeprice >> Changeevalate;
                    foodkind[kindop].dish[kindmenuop - 2].id = Changeid;
                    foodkind[kindop].dish[kindmenuop - 2].name= Changename;
                    foodkind[kindop].dish[kindmenuop - 2].price = Changeprice;
                    foodkind[kindop].dish[kindmenuop - 2].evaluate = Changeevalate;
                    foodkind[kindop].dish[kindmenuop - 2].need = true;
                    cout << "�޸ĳɹ���\n";
                    bool show;
                    cout << "�Ƿ���ʾ�޸ĺ�Ĳ˵���������ѡ��[0-��/1-��]: ";
                    cin >> show;
                    getchar();
                    if (show) {
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                        //cout << "����ϵͳ>>�޸Ĳ�Ʒ>>" << foodkind[kindop].nameprint() << endl << endl;
                        cout << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
                            << setw(20) << "��Ʒ����" << endl
                            << setw(20) << foodkind[kindop].nameprint() << setw(20)
                            << foodkind[kindop].styleprint() << setw(20)
                            << foodkind[kindop].cntprint() << endl;
                        cout << setw(20) << "��Ʒ���" << setw(20) << "����"
                            << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ��޸�" << endl;
                        for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                            cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                                << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                                setw(20) << (foodkind[kindop].dish[i].need ? "��" : "��") << endl;
                        }
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";

                    }
                    cout << "�����ѡ��: ";
                   
                    goto x;
                }
            }
            else if (choice == 3)
            {
                bool add = false;
            z:
                cout << "����ϵͳ>>���Ӳ�Ʒ\n\n";
                cout << "********1.³��\t2.����\t3.����\t********\n";
                cout << "********4.����\t5.�ղ�\t6.���\t********\n";
                cout << "********7.�ղ�\t8.���\t9.��ˮ��ֽ��****\n";
                cout << "********0.����������            ********\n";
                cout << "�����ѡ����Ҫ���ӵĲ�Ʒ������ϵ [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindop == 0) {
                    system("cls");
                    goto g;
                }
                system("cls");
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << "����ϵͳ>>���Ӳ�Ʒ>>" << foodkind[kindop].nameprint() << endl << endl;
                cout << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
                    << setw(20) << "��Ʒ����" << endl
                    << setw(20) << foodkind[kindop].nameprint() << setw(20)
                    << foodkind[kindop].styleprint() << setw(20)
                    << foodkind[kindop].cntprint() << endl;
                cout << setw(20) << "��Ʒ���" << setw(20) << "����"
                    << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
                for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                    cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                        << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                        setw(20) <<  "��" << endl;
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << endl << endl;
                cout << "*********************************����ѡ��*******************************\n";
                cout << "0.����������  \n";
                cout << "1.���ز˵����� \n";
                cout << "2.���Ӳ�Ʒ \n";
                int kindmenuop;
                cout << "�����ѡ��: ";
            w://����һ��goto���  ���ڷ��ؼ����㵥
                bool kindmenuopright = false;
                while (!kindmenuopright) {
                    try{
                        kindmenuop = readIntFromInput(2);
                        kindmenuopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindmenuop == 0) {
                    if (add)
                        MenuSave();
                    system("cls");
                    goto g;
                }
                else if (kindmenuop == 1) {
                    if (add)
                        MenuSave();
                    system("cls");
                    goto z;
                }
                else if (kindmenuop ==2) {
                    add = true;
                    cout << "�������µĲ�Ʒ��� ���� �۸� ���۵÷�: ";
                    string Changeid, Changename;
                    int Changeprice, Changeevalate;
                    cin >> Changeid >> Changename >> Changeprice >> Changeevalate;
                    //getchar();
                    FOODKIND::addDish(foodkind[kindop], Changeid, Changename,Changeprice,Changeevalate,false);
                    cout << "���ӳɹ���\n";
                    bool show;
                    cout << "�Ƿ���ʾ���Ӻ�Ĳ˵���������ѡ��[0-��/1-��]: ";
                    cin >> show;//������û�������ж� �����������  ����ֱ�ӳ���
                    getchar();
                    if (show) {
                        //foodkind[kindop].KindShow(cout);
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
                            << setw(20) << "��Ʒ����" << endl
                            << setw(20) << foodkind[kindop].nameprint() << setw(20)
                            << foodkind[kindop].styleprint() << setw(20)
                            << foodkind[kindop].cntprint() << endl;
                        cout << setw(20) << "��Ʒ���" << setw(20) << "����"
                            << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
                        for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                            cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                                << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                                setw(20) <<  "��" << endl;//����ط�ֻ�����  ��  ��Ϊ���ܻᱻǰ����޸Ĳ�����Ϊ ��  
                        }
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";

                    }
                    cout << "�����ѡ��: ";
                    goto w;
                }
            }
            else if (choice == 4)
            {
                bool sub=false;
                m:
                cout << "����ϵͳ>>���ٲ�Ʒ\n\n";
                cout << "********1.³��\t2.����\t3.����\t********\n";
                cout << "********4.����\t5.�ղ�\t6.���\t********\n";
                cout << "********7.�ղ�\t8.���\t9.��ˮ��ֽ��****\n";
                cout << "********0.����������            ********\n";
                cout << "�����ѡ����Ҫ���ٵĲ�Ʒ������ϵ�� [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindop == 0) {
                    system("cls");
                    goto g;
                }
                system("cls");
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << "����ϵͳ>>ɾ����Ʒ>>" << foodkind[kindop].nameprint() << endl << endl;
                cout << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
                    << setw(20) << "��Ʒ����" << endl
                    << setw(20) << foodkind[kindop].nameprint() << setw(20)
                    << foodkind[kindop].styleprint() << setw(20)
                    << foodkind[kindop].cntprint() << endl;
                cout << setw(20) << "��Ʒ���" << setw(20) << "����"
                    << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
                for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                    cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                        << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                        setw(20) << "��" << endl;
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << endl << endl;
                foodkind[kindop].KindMenuShow(cout);//���ﲻ��  Ҫ�޸�
                int kindmenuop;
                cout << "�����ѡ��: ";
                n://����һ��goto���  ���ڷ��ؼ����㵥
                bool kindmenuopright = false;
                while (!kindmenuopright) {
                    try{
                        kindmenuop = readIntFromInput(foodkind[kindop].cntprint() + 1);
                        kindmenuopright = true;
                    }
                    catch (char) {
                        // ���񲢴����쳣  
                        cout << "����ѡ�񲻺Ϸ���������ѡ��: ";
                    }
                    catch (int) {
                        cout << "û���������ѡ�������ѡ��:";
                    }
                }
                if (kindmenuop == 0) {
                    if (sub)
                        MenuSave();
                    system("cls");
                    goto g;
                }
                else if (kindmenuop == 1) {
                    if (sub)
                        MenuSave();
                    system("cls");
                    goto m;
                }
                else if (kindmenuop <= foodkind[kindop].cntprint() + 1) {
                    sub = true;
                    for (int i = kindmenuop - 1; i <= foodkind[kindop].cntprint(); i++) {
                        foodkind[kindop].dish[i - 1] = foodkind[kindop].dish[i];
                    }
                    foodkind[kindop].cntsub();
                    cout << "ɾ���ɹ���" << endl;
                    bool show;
                    cout << "�Ƿ���ʾɾ����Ĳ˵���������ѡ��[0-��/1-��]: ";
                    cin >> show;//������û�������ж� �����������  ����ֱ�ӳ���
                    getchar();
                    if (show) {
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                        //cout << "����ϵͳ>>�޸Ĳ�Ʒ>>" << foodkind[kindop].nameprint() << endl << endl;
                        cout << setw(20) << "��ϵ����" << setw(20) << "��ϵ���"
                            << setw(20) << "��Ʒ����" << endl
                            << setw(20) << foodkind[kindop].nameprint() << setw(20)
                            << foodkind[kindop].styleprint() << setw(20)
                            << foodkind[kindop].cntprint() << endl;
                        cout << setw(20) << "��Ʒ���" << setw(20) << "����"
                            << setw(20) << "�۸�" << setw(20) << "����" << setw(20) << "�Ƿ���Ҫ" << endl;
                        for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // ע������ʹ��i < kindcnt������i <= kindcnt  
                            cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                                << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                                setw(20) <<  "��" << endl;
                        }
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";

                    }
                    cout << "�����ѡ��: ";
                    goto n;
                }
                else {
                    cout << "�����������˲����ڣ����Ѿ���ɾ���������������룡\n";
                    cout << "�����ѡ��: ";
                    goto n;
                }
            }
        }
        else
        {
            passcnt++;
            if (passcnt == 3){
                cout << "ʧ�ܻ���ﵽ���ޣ��޷����룬3����Զ��˳���\n";
                //system("pause");
                int seconds = 3;
                while (seconds > 0) {
                    //std::cout << "Remaining time: " << seconds << " seconds" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // ��ͣһ��
                    --seconds; // ����ʣ������
                }
                system("cls");
                return 0;
            }
            cout << "��������㻹��" << 3 - passcnt << "�λ��ᣬ��3����������룡 "<<endl;
            int seconds = 3;
            while (seconds > 0) {
                std::cout << "Remaining time: " << seconds << " seconds" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1)); // ��ͣһ��
                --seconds; // ����ʣ������
            }
            cout << "���������룺";
            goto h;
        }
    }


    return 0;
}

//�����ݶ����ļ�����
//FOODKIND::Initdish();
//ofstream outfile(MENUTXT, ios::app);
//for (int i = 1; i <= 9; i++) {
//    outfile << foodkind[i].nameprint() << endl;
//    outfile << foodkind[i].styleprint() << endl;
//    outfile << foodkind[i].evalateprint()<< endl;
//    outfile << foodkind[i].cntprint() << endl;
//    for (int j = 1; j <= foodkind[i].cntprint(); j++) {
//        //cout << foodkind[i].dish[j - 1].id << endl;
//        outfile << foodkind[i].dish[j - 1].id << endl;
//        outfile << foodkind[i].dish[j - 1].name << endl;
//        outfile << foodkind[i].dish[j - 1].price << endl;
//        outfile << foodkind[i].dish[j - 1].evaluate << endl;
//        outfile << foodkind[i].dish[j - 1].need << endl;
//    }
//}
//outfile.close();
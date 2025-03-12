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

int people; // 顾客的人数  
int cost;//目前已点菜共计多少元
int dishCnt = 0;//目前已点菜共计多少个

Dish orderdish[90];//这个数组用于储存已点菜品

void MyOrderShow()//这个函数的功能是显示出现已经点过的菜品
{
    std::cout << "主界面>>我的菜单\n\n";

    std::cout << "**********************************************************************************************************\n";
    std::cout << "**********************************************已点菜单****************************************************\n\n";
    if (dishCnt == 0) {
        std::cout << "您现在还没有选择任何菜品!\n";
    }
    else {
        std::cout <<setw(5)<<"编号" << setw(20) << "菜品编号" << setw(20) << "菜名"
            << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
        for (int i = 1; i <= dishCnt ; i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
            //int k = 1;

            std::cout <<setw(5)<<i <<setw(20) << orderdish[i].id << setw(20) << orderdish[i].name
                << setw(20) << orderdish[i].price << setw(20) << orderdish[i].evaluate << setw(20) << (orderdish[i].need ? "是" : "否") << endl;
        }

        std::cout << "目前已经选择了 " << dishCnt << " 道菜，共计花费 " << cost << " 元\n" << endl;
    }

}

int readIntFromInput(int limit) throw(char, int)
//limit用于判断最大可以输出多少
{
    std::string input;
    std::getline(std::cin, input); // 使用getline来读取直到空格  

    // 尝试将输入转换为整数  
    std::istringstream iss(input);
    int num;
    if (!(iss >> num) || !iss.eof()) {
        // 如果转换失败或者输入流中还有剩余字符（说明输入不是纯整数）  
        throw (char)1;
    }
    if (num > limit||num<0) {
        throw (int)1;
    }

    return num;
} //读入数字异常检测

bool cmp(Dish a, Dish b) {
    return a.id < b.id;
}
//将已经选择的菜单按照编号输出

int main() {
    // 初始化菜品信息  
    MenuLoad();

    cout << "***********************************************\n";
    cout << "*******************欢迎光临!*******************\n请输入就餐人数： ";
    bool peopleright = false;//判断输入是否合法
    while (!peopleright) {
        try {
            people = readIntFromInput(INT_MAX);
            peopleright = true;
        }
        catch (char) {
            // 捕获并处理异常  
            cout << "输入选择不合法，请重新选择: ";
        }
        catch (int) {
            cout << "没有您输入的选项，请重新选择:";
        }
    }
    //如果people是0个人 那么就进入管理系统  否则进入服务系统
    if (people != 0) {
        //服务系统
        cout << "请您根据需求进行点单，如果有任何问题请寻找服务员帮助，祝您用餐愉快！\n";
        cout << "即将进入点单系统\n";
        system("pause");
        system("cls");
        //getchar();//清空留下来的换行符
        while (true) {
            cout << "***********************        欢迎光临!     **************************\n";
            cout << "***********************1.查看菜单            **************************\n";
            cout << "***********************2.我的菜单            **************************\n";
            cout << "***********************0.用餐结束            **************************\n";
            cout << "请输入您的选择： ";
            int op;
            bool opright = false;//判断输入是否合法
            while (!opright) {
                try{
                    op = readIntFromInput(2);
                    opright = true;
                }
                catch (char) {
                    // 捕获并处理异常  
                    cout << "输入选择不合法，请重新选择: ";
                }
                catch (int) {
                    cout << "没有您输入的选项，请重新选择:";
                }
            }
            if (op == 0) {
                //退出服务系统
                system("cls");
                if (dishCnt != 0) {
                    //如果已经点了菜品  那么在结束的时候将账单输出
                    sort(orderdish + 1, orderdish + dishCnt + 1, cmp);
                    cout << "**********************************************************************************************************\n";
                    cout << "**********************************************我的账单****************************************************\n\n";

                    cout << setw(5) << "编号" << setw(20) << "菜品编号" << setw(20) << "菜名"
                        << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
                    for (int i = 1; i <= dishCnt; i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                        //int k = 1;

                        cout << setw(5) << i << setw(20) << orderdish[i].id << setw(20) << orderdish[i].name
                            << setw(20) << orderdish[i].price << setw(20) << orderdish[i].evaluate << setw(20) << (orderdish[i].need ? "是" : "否") << endl;
                    }
                    std::cout << "\n\n共计 " << dishCnt << " 道菜，总花费 " << cost << " 元\n" << endl;
                    cout << "欢迎下次光临！\n";
                        // 获取当前时间点
                    auto now = std::chrono::system_clock::now();

                    // 将时间点转换为time_t类型，以便使用ctime函数
                     std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

                    // 将time_t类型转换为本地时间
                    std::tm* localTime = std::localtime(&currentTime);

                    // 设置输出格式，确保时间以两位数显示
                    cout << "当前时间为： ";
                    std::cout << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;

                }
                break;
            }
            system("cls");  

            if (op == 1) {
            //点单操作
            a://这里是一个goto语句用于返回菜单界面
                cout << "主界面>>查看菜单\n\n";
                cout << "********1.鲁菜\t2.川菜\t3.闽菜\t********\n";
                cout << "********4.粤菜\t5.苏菜\t6.浙菜\t********\n";
                cout << "********7.徽菜\t8.湘菜\t9.茶水、纸巾****\n";
                cout << "********0.返回主界面            ********\n";
                cout << "请进行选择： [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright=false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
                    }
                }
                if (kindop == 0) {
                    //返回主界面
                    system("cls");
                    continue;
                }
                system("cls");
                if (kindop > 0 && kindop <= 9) {
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    foodkind[kindop].KindShow(cout); // 显示所选菜系的菜单 
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << endl << endl;
                    foodkind[kindop].KindMenuShow(cout);
                    cout << "请进行选择: ";
                b://这是一个goto语句  用于返回继续点单
                    int kindmenuop;
                    bool kindmenuopright = false;
                    while (!kindmenuopright) {
                        try{
                            kindmenuop = readIntFromInput(foodkind[kindop].cntprint() + 1);
                            kindmenuopright = true;
                        }
                        catch (char) {
                            // 捕获并处理异常  
                            cout << "输入选择不合法，请重新选择: ";
                        }
                        catch (int) {
                            cout << "没有您输入的选项，请重新选择:";
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
                            //这里不支持一道菜被选两次   如果想要修改的话  需要将need改为quality  这个函数中暂时不支持
                            cout << "这道菜已经被选过，本店商品实惠，无需再次选择！\n";
                            cout << "请继续选择: ";
                            goto b;
                        }
                        foodkind[kindop].dish[kindmenuop - 2].need = true;//将这道菜设置为已被选择过
                        cost += foodkind[kindop].dish[kindmenuop - 2].price;//总的花费要加上这道菜的价格
                        orderdish[++dishCnt] = foodkind[kindop].dish[kindmenuop - 2];//将选择的菜品加入到我的菜单
                        cout << "请继续选择: ";
                        goto b;
                    }
                }
            }
            else if (op == 2){
            e:
                cout << "主界面>>我的菜单\n\n";
                cout << "********1.显示我的菜单\t********\n";
                cout << "********2.继续点单   \t********\n";
                cout << "********3.删除某道菜    ********\n";
                cout << "********0.返回主界面    ********\n";
                cout << "请进行选择： [1 2 3 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(3);
                        kindopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
                    }
                }
                system("cls");
                if (kindop == 0) {
                    continue;
                    //这里不需要什么操作  直接就会返回
                }
                else if (kindop == 1) {
                    sort(orderdish + 1, orderdish + dishCnt + 1, cmp);
                    MyOrderShow();
                    cout << "********1.返回点单界面     ********\n";
                    cout << "********2.返回我的菜单     ********\n";
                    cout << "********0.返回主界面       ********\n";
                    cout << "请进行选择： [1 2 0]: ";
                    int choice;
                    bool choiceright = false;
                    while (!choiceright) {
                        try {
                            choice = readIntFromInput(3);
                            choiceright = true;
                        }
                        catch (char) {
                            // 捕获并处理异常  
                            cout << "输入选择不合法，请重新选择: ";
                        }
                        catch (int) {
                            cout << "没有您输入的选项，请重新选择:";
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
                    //以上是需要根据情况进行跳转
                }
                else if (kindop == 2){
                    system("cls");
                    goto a;
                }
                else if (kindop == 3){
                    MyOrderShow();
                    int choice=-1;
                    while (choice != 0&&dishCnt!=0) {
                        cout << "请输入您想删除第几道菜（选0不再删除）： ";
                        bool choiceright = false;
                        while (!choiceright) {
                            try {
                                choice = readIntFromInput(dishCnt);
                                choiceright = true;
                            }
                            catch (char) {
                                // 捕获并处理异常  
                                cout << "输入选择不合法，请重新选择: ";
                            }
                            catch (int) {
                                cout << "输入错误，没有这一道菜！\n请重新输入： ";
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
                        //消除被删的这道菜的影响
                        for (int i = choice + 1; i <= dishCnt; i++) {
                            orderdish[i - 1] = orderdish[i];
                        }
                        dishCnt--;
                        cout << "删除成功，菜单展示！\n";
                        MyOrderShow();
                        cout << "请继续操作！" << endl;
                    }
                    system("pause");
                    system("cls");
                    cout << "********1.返回点单界面     ********\n";
                    cout << "********2.返回我的菜单     ********\n";
                    cout << "********0.返回主界面       ********\n";
                    cout << "请进行选择 [1 2 0]: ";
                    int lastchoice;
                    bool lastchoiceright = false;
                    while (!lastchoiceright) {
                        try {
                            lastchoice = readIntFromInput(2);
                            lastchoiceright = true;
                        }
                        catch (char) {
                            // 捕获并处理异常  
                            cout << "输入选择不合法，请重新选择: ";
                        }
                        catch (int) {
                            cout << "没有您输入的选项，请重新选择:";
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
                    //以上部分根据需要进行跳转
                }
            }
        }
    }
    else
    {
        cout << "即将进入管理系统\n";
        system("pause");
        system("cls");
        GetPassWord();//从文件中读取密码
        cout << "密码是：" << PassWord << "（密码经过加密，一般不易看懂，在这里直接给出以供测试，实际使用时不会显示）" << endl;
        cout << "请先输入管理系统密码，验证身份: ";
        int passcnt = 0;//试错次数统计
        //h://如果h在这里的话，会导致消耗两个答案（2个getchar()）
        string password;
        //getchar();//消除换行符影响
        h:
        getline(cin,password);//允许读入空格
        if (password == PassWord) 
        {
            cout << "密码正确，欢迎进入管理系统！\n";
            system("pause");
            system("cls");
            g:
            cout << "*******************        欢迎进入管理系统!     **********************\n";
            cout << "***********************0.退出系统            **************************\n";
            cout << "***********************1.修改密码            **************************\n";
            cout << "***********************2.修改菜品            **************************\n";
            cout << "***********************3.增加菜品            **************************\n";
            cout << "***********************4.减少菜品            **************************\n";
            cout << "请输入您的选择： ";
            int choice;//选择选项
            bool choiceright = false;
            while (!choiceright) {
                try{
                    choice = readIntFromInput(4);
                    choiceright = true;
                }
                catch (char) {
                    // 捕获并处理异常  
                    cout << "输入选择不合法，请重新选择: ";
                }
                catch (int) {
                    cout << "没有您输入的选项，请重新选择:";
                }
            }
            system("cls");

            if (choice == 0) {
                cout << "3秒后自动退出管理系统" << endl;
                int seconds = 3;
                while (seconds > 0) {
                    //std::cout << "Remaining time: " << seconds << " seconds" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // 暂停一秒
                    --seconds; // 减少剩余秒数
                }
                //system("pause");
                system("cls");
            }
            else if (choice == 1){
                cout << "管理系统>>修改密码\n\n";
                cout << "请首先输入原密码: " ;
                string word;
                GetPassWord();//从文件中读取密码  这里要重新调用  因为二次更改密码的时候  这的原始密码没有变化
                getline(cin, word);
                cout << endl;

                if (word == PassWord) {
                    string Changeword;
                    cout << "请输入修改后的密码: ";
                    //getchar();//消除缓存区影响(这里需要更改 如果第二次输入密码  这里会消耗一个密码导致错误  可能是因为上面也消耗一个)
                    getline(cin, Changeword);//允许密码存在空格
                    ChangePassWord(Changeword);
                    cout << "密码修改成功！\n";
                    cout << endl << endl;
                }
                else {
                    cout << "密码错误，无法更改！" << endl;
                    system("pause");
                    system("cls");
                }
                cout << "*******1.返回管理界面  *******\n";
                cout << "*******0.退出管理系统  *******\n";
                cout << "请输入您的选择： ";
                int op;
                bool opright=false;
                while (!opright) {
                    try{
                        op = readIntFromInput(1);
                        opright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
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
                cout << "管理系统>>修改菜品\n\n";
                cout << "********1.鲁菜\t2.川菜\t3.闽菜\t********\n";
                cout << "********4.粤菜\t5.苏菜\t6.浙菜\t********\n";
                cout << "********7.徽菜\t8.湘菜\t9.茶水、纸巾****\n";
                cout << "********0.返回主界面            ********\n";
                cout << "请进行选择想要修改的菜品所属菜系 [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
                    }
                }
                if (kindop == 0) {
                    system("cls");
                    goto g;
                }
                system("cls");
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << "管理系统>>修改菜品>>" << foodkind[kindop].nameprint() << endl << endl;
                cout << setw(20) << "菜系名称" << setw(20) << "菜系简介"
                    << setw(20) << "菜品数量" << endl
                    << setw(20) << foodkind[kindop].nameprint() << setw(20)
                    << foodkind[kindop].styleprint() << setw(20)
                    << foodkind[kindop].cntprint() << endl;
                cout << setw(20) << "菜品编号" << setw(20) << "菜名"
                    << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否被修改" << endl;
                for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                    cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                        << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate << 
                        setw(20) << (foodkind[kindop].dish[i].need ? "是" : "否") << endl;
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << endl << endl;
                foodkind[kindop].KindMenuShow(cout);
                int kindmenuop;
                cout << "请进行选择: ";
            x://这是一个goto语句  用于返回继续点单
                bool kindmenuopright = false;
                while (!kindmenuopright) {
                    try{
                        kindmenuop = readIntFromInput(foodkind[kindop].cntprint() + 1);
                        kindmenuopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
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
                        cout << "这道菜已经被修改，请仔细选择!\n";
                        bool Secondop;
                        cout << "是否依旧要更改这道菜？请输入您的选择（1-是/0-否） ：";
                        cin >> Secondop;
                        getchar();
                        if (!Secondop) {
                            cout << "请继续选择: ";
                            goto x;
                        }
                    }
                    cout << "请输入修改后的信息[编号 名称 价格 评价得分]： ";
                    string Changeid, Changename;
                    int Changeprice, Changeevalate;
                    cin >> Changeid >> Changename >> Changeprice >> Changeevalate;
                    foodkind[kindop].dish[kindmenuop - 2].id = Changeid;
                    foodkind[kindop].dish[kindmenuop - 2].name= Changename;
                    foodkind[kindop].dish[kindmenuop - 2].price = Changeprice;
                    foodkind[kindop].dish[kindmenuop - 2].evaluate = Changeevalate;
                    foodkind[kindop].dish[kindmenuop - 2].need = true;
                    cout << "修改成功！\n";
                    bool show;
                    cout << "是否显示修改后的菜单？请输入选择[0-否/1-是]: ";
                    cin >> show;
                    getchar();
                    if (show) {
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                        //cout << "管理系统>>修改菜品>>" << foodkind[kindop].nameprint() << endl << endl;
                        cout << setw(20) << "菜系名称" << setw(20) << "菜系简介"
                            << setw(20) << "菜品数量" << endl
                            << setw(20) << foodkind[kindop].nameprint() << setw(20)
                            << foodkind[kindop].styleprint() << setw(20)
                            << foodkind[kindop].cntprint() << endl;
                        cout << setw(20) << "菜品编号" << setw(20) << "菜名"
                            << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否被修改" << endl;
                        for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                            cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                                << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                                setw(20) << (foodkind[kindop].dish[i].need ? "是" : "否") << endl;
                        }
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";

                    }
                    cout << "请继续选择: ";
                   
                    goto x;
                }
            }
            else if (choice == 3)
            {
                bool add = false;
            z:
                cout << "管理系统>>增加菜品\n\n";
                cout << "********1.鲁菜\t2.川菜\t3.闽菜\t********\n";
                cout << "********4.粤菜\t5.苏菜\t6.浙菜\t********\n";
                cout << "********7.徽菜\t8.湘菜\t9.茶水、纸巾****\n";
                cout << "********0.返回主界面            ********\n";
                cout << "请进行选择想要增加的菜品所属菜系 [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
                    }
                }
                if (kindop == 0) {
                    system("cls");
                    goto g;
                }
                system("cls");
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << "管理系统>>增加菜品>>" << foodkind[kindop].nameprint() << endl << endl;
                cout << setw(20) << "菜系名称" << setw(20) << "菜系简介"
                    << setw(20) << "菜品数量" << endl
                    << setw(20) << foodkind[kindop].nameprint() << setw(20)
                    << foodkind[kindop].styleprint() << setw(20)
                    << foodkind[kindop].cntprint() << endl;
                cout << setw(20) << "菜品编号" << setw(20) << "菜名"
                    << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
                for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                    cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                        << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                        setw(20) <<  "否" << endl;
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << endl << endl;
                cout << "*********************************增加选择*******************************\n";
                cout << "0.返回主界面  \n";
                cout << "1.返回菜单界面 \n";
                cout << "2.增加菜品 \n";
                int kindmenuop;
                cout << "请进行选择: ";
            w://这是一个goto语句  用于返回继续点单
                bool kindmenuopright = false;
                while (!kindmenuopright) {
                    try{
                        kindmenuop = readIntFromInput(2);
                        kindmenuopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
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
                    cout << "请输入新的菜品编号 名称 价格 评价得分: ";
                    string Changeid, Changename;
                    int Changeprice, Changeevalate;
                    cin >> Changeid >> Changename >> Changeprice >> Changeevalate;
                    //getchar();
                    FOODKIND::addDish(foodkind[kindop], Changeid, Changename,Changeprice,Changeevalate,false);
                    cout << "增加成功！\n";
                    bool show;
                    cout << "是否显示增加后的菜单？请输入选择[0-否/1-是]: ";
                    cin >> show;//这里我没有设置判断 即不允许输错  否则直接出错
                    getchar();
                    if (show) {
                        //foodkind[kindop].KindShow(cout);
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << setw(20) << "菜系名称" << setw(20) << "菜系简介"
                            << setw(20) << "菜品数量" << endl
                            << setw(20) << foodkind[kindop].nameprint() << setw(20)
                            << foodkind[kindop].styleprint() << setw(20)
                            << foodkind[kindop].cntprint() << endl;
                        cout << setw(20) << "菜品编号" << setw(20) << "菜名"
                            << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
                        for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                            cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                                << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                                setw(20) <<  "否" << endl;//这个地方只能输出  否  因为可能会被前面的修改操作变为 是  
                        }
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";

                    }
                    cout << "请继续选择: ";
                    goto w;
                }
            }
            else if (choice == 4)
            {
                bool sub=false;
                m:
                cout << "管理系统>>减少菜品\n\n";
                cout << "********1.鲁菜\t2.川菜\t3.闽菜\t********\n";
                cout << "********4.粤菜\t5.苏菜\t6.浙菜\t********\n";
                cout << "********7.徽菜\t8.湘菜\t9.茶水、纸巾****\n";
                cout << "********0.返回主界面            ********\n";
                cout << "请进行选择想要减少的菜品所属菜系： [1 2 3 4 5 6 7 8 9 0]: ";
                int kindop;
                bool kindopright = false;
                while (!kindopright) {
                    try{
                        kindop = readIntFromInput(9);
                        kindopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
                    }
                }
                if (kindop == 0) {
                    system("cls");
                    goto g;
                }
                system("cls");
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << "管理系统>>删除菜品>>" << foodkind[kindop].nameprint() << endl << endl;
                cout << setw(20) << "菜系名称" << setw(20) << "菜系简介"
                    << setw(20) << "菜品数量" << endl
                    << setw(20) << foodkind[kindop].nameprint() << setw(20)
                    << foodkind[kindop].styleprint() << setw(20)
                    << foodkind[kindop].cntprint() << endl;
                cout << setw(20) << "菜品编号" << setw(20) << "菜名"
                    << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
                for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                    cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                        << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                        setw(20) << "否" << endl;
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                cout << endl << endl;
                foodkind[kindop].KindMenuShow(cout);//词语不当  要修改
                int kindmenuop;
                cout << "请进行选择: ";
                n://这是一个goto语句  用于返回继续点单
                bool kindmenuopright = false;
                while (!kindmenuopright) {
                    try{
                        kindmenuop = readIntFromInput(foodkind[kindop].cntprint() + 1);
                        kindmenuopright = true;
                    }
                    catch (char) {
                        // 捕获并处理异常  
                        cout << "输入选择不合法，请重新选择: ";
                    }
                    catch (int) {
                        cout << "没有您输入的选项，请重新选择:";
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
                    cout << "删除成功！" << endl;
                    bool show;
                    cout << "是否显示删除后的菜单？请输入选择[0-否/1-是]: ";
                    cin >> show;//这里我没有设置判断 即不允许输错  否则直接出错
                    getchar();
                    if (show) {
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                        //cout << "管理系统>>修改菜品>>" << foodkind[kindop].nameprint() << endl << endl;
                        cout << setw(20) << "菜系名称" << setw(20) << "菜系简介"
                            << setw(20) << "菜品数量" << endl
                            << setw(20) << foodkind[kindop].nameprint() << setw(20)
                            << foodkind[kindop].styleprint() << setw(20)
                            << foodkind[kindop].cntprint() << endl;
                        cout << setw(20) << "菜品编号" << setw(20) << "菜名"
                            << setw(20) << "价格" << setw(20) << "评分" << setw(20) << "是否需要" << endl;
                        for (int i = 0; i < foodkind[kindop].cntprint(); i++) { // 注意这里使用i < kindcnt而不是i <= kindcnt  
                            cout << setw(20) << foodkind[kindop].dish[i].id << setw(20) << foodkind[kindop].dish[i].name
                                << setw(20) << foodkind[kindop].dish[i].price << setw(20) << foodkind[kindop].dish[i].evaluate <<
                                setw(20) <<  "否" << endl;
                        }
                        cout << "-----------------------------------------------------------------------------------------------------------------------\n";

                    }
                    cout << "请继续选择: ";
                    goto n;
                }
                else {
                    cout << "输入错误，这道菜不存在（或已经被删除），请重新输入！\n";
                    cout << "请继续选择: ";
                    goto n;
                }
            }
        }
        else
        {
            passcnt++;
            if (passcnt == 3){
                cout << "失败机会达到上限，无法输入，3秒后自动退出！\n";
                //system("pause");
                int seconds = 3;
                while (seconds > 0) {
                    //std::cout << "Remaining time: " << seconds << " seconds" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // 暂停一秒
                    --seconds; // 减少剩余秒数
                }
                system("cls");
                return 0;
            }
            cout << "密码错误，你还有" << 3 - passcnt << "次机会，请3秒后重新输入！ "<<endl;
            int seconds = 3;
            while (seconds > 0) {
                std::cout << "Remaining time: " << seconds << " seconds" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1)); // 暂停一秒
                --seconds; // 减少剩余秒数
            }
            cout << "请输入密码：";
            goto h;
        }
    }


    return 0;
}

//将数据读入文件操作
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
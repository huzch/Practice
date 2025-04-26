#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm>
#include<cmath>
using namespace std;

#include"Calculator.h"

// 菜单显示函数，显示主菜单选项
void Menu()
{
    // 打印菜单的标题和选项
    cout << "******************************************************" << endl;
    cout << "************** 1.一元稀疏多项式简单计算 **************" << endl;
    cout << "************** 2.算法表达式求值计算     **************" << endl;
    cout << "************** 0.退出计算器             **************" << endl;
    cout << "******************************************************" << endl;
}

// 多项式计算菜单显示函数，显示可进行的多项式操作
void PolynomialMenu()
{
    // 打印多项式菜单的标题和选项
    cout << "******************************************************" << endl;
    cout << "***************   1.求值   2.求导  *******************" << endl;
    cout << "***************   3.相加   4.相减  *******************" << endl;
    cout << "***************   5.相乘   0.退出  *******************" << endl;
    cout << "******************************************************" << endl;
}

// 多项式计算器函数，提供多项式的输入和操作选择
void PolynomialCalculator()
{
    Polynomial p1, p2;  // 创建两个Polynomial类型的多项式对象
    cout << "请输入第一个多项式:" << endl;
    p1.Input();  // 读取第一个多项式的输入
    cout << "请输入第二个多项式(如果只需求值或求导，请输入0跳过):" << endl;
    p2.Input();  // 读取第二个多项式的输入

    int input;  // 用于保存用户的选择
    do
    {
        PolynomialMenu();  // 显示多项式操作菜单
        cout << "请选择:";
        cin >> input;  // 读取用户选择的操作
        switch (input)
        {
        case 1:
            double x;  // 用于保存x的值
            cout << "请输入x的值:";
            cin >> x;
            cout << "结果:" << p1.Eval(x) << endl;  // 计算多项式在x处的值并输出结果
            break;
        case 2:
            p1.Deriv().Output();  // 计算多项式的导数并输出
            break;
        case 3:
            p1.Add(p2).Output();  // 计算两个多项式的和并输出
            break;
        case 4:
            p1.Sub(p2).Output();  // 计算两个多项式的差并输出
            break;
        case 5:
            p1.Mul(p2).Output();  // 计算两个多项式的积并输出
            break;
        case 0:
            cout << "已退出" << endl;  // 用户选择退出
            break;
        default:
            cout << "输入非法，请重新选择" << endl;  // 用户输入非法选项
            break;
        }
    } while (input);  // 当用户选择0退出时，结束循环
}

// 表达式计算器函数，进行表达式求值
void ExpressionCalculator()
{
    string s;  // 用于保存用户输入的表达式
    cout << "请输入表达式:";
    cin.ignore();  // 忽略前一次输入残留的换行符
    getline(cin, s);  // 读取整个表达式

    try
    {
        // 尝试计算表达式的值，并输出结果
        cout << "该表达式值为:" << Expression().Calculator(s) << endl << endl;
    }
    catch (const string& s)
    {
        // 如果捕获到string类型的异常，输出错误信息
        cout << s << endl << endl;
    }
    catch (...)
    {
        // 捕获其他未知异常，输出错误提示
        cout << "未知异常" << endl << endl;
    }
}

// 主函数，显示菜单并处理用户的选择
int main()
{
    int input;  // 用于保存用户的选择
    do
    {
        Menu();  // 显示主菜单
        cout << "请选择:";
        cin >> input;  // 读取用户的选择
        switch (input)
        {
        case 1:
            PolynomialCalculator();  // 选择1，进入多项式计算器
            break;
        case 2:
            ExpressionCalculator();  // 选择2，进入表达式计算器
            break;
        case 0:
            cout << "已退出计算器" << endl;  // 用户选择退出
            break;
        default:
            cout << "输入非法，请重新选择" << endl;  // 用户输入非法选项
            break;
        }
    } while (input);  // 当用户选择0退出时，结束循环
    return 0;  // 程序结束
}
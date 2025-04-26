#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm>
#include<cmath>
using namespace std;

#include"Calculator.h"

// �˵���ʾ��������ʾ���˵�ѡ��
void Menu()
{
    // ��ӡ�˵��ı����ѡ��
    cout << "******************************************************" << endl;
    cout << "************** 1.һԪϡ�����ʽ�򵥼��� **************" << endl;
    cout << "************** 2.�㷨���ʽ��ֵ����     **************" << endl;
    cout << "************** 0.�˳�������             **************" << endl;
    cout << "******************************************************" << endl;
}

// ����ʽ����˵���ʾ��������ʾ�ɽ��еĶ���ʽ����
void PolynomialMenu()
{
    // ��ӡ����ʽ�˵��ı����ѡ��
    cout << "******************************************************" << endl;
    cout << "***************   1.��ֵ   2.��  *******************" << endl;
    cout << "***************   3.���   4.���  *******************" << endl;
    cout << "***************   5.���   0.�˳�  *******************" << endl;
    cout << "******************************************************" << endl;
}

// ����ʽ�������������ṩ����ʽ������Ͳ���ѡ��
void PolynomialCalculator()
{
    Polynomial p1, p2;  // ��������Polynomial���͵Ķ���ʽ����
    cout << "�������һ������ʽ:" << endl;
    p1.Input();  // ��ȡ��һ������ʽ������
    cout << "������ڶ�������ʽ(���ֻ����ֵ���󵼣�������0����):" << endl;
    p2.Input();  // ��ȡ�ڶ�������ʽ������

    int input;  // ���ڱ����û���ѡ��
    do
    {
        PolynomialMenu();  // ��ʾ����ʽ�����˵�
        cout << "��ѡ��:";
        cin >> input;  // ��ȡ�û�ѡ��Ĳ���
        switch (input)
        {
        case 1:
            double x;  // ���ڱ���x��ֵ
            cout << "������x��ֵ:";
            cin >> x;
            cout << "���:" << p1.Eval(x) << endl;  // �������ʽ��x����ֵ��������
            break;
        case 2:
            p1.Deriv().Output();  // �������ʽ�ĵ��������
            break;
        case 3:
            p1.Add(p2).Output();  // ������������ʽ�ĺͲ����
            break;
        case 4:
            p1.Sub(p2).Output();  // ������������ʽ�Ĳ���
            break;
        case 5:
            p1.Mul(p2).Output();  // ������������ʽ�Ļ������
            break;
        case 0:
            cout << "���˳�" << endl;  // �û�ѡ���˳�
            break;
        default:
            cout << "����Ƿ���������ѡ��" << endl;  // �û�����Ƿ�ѡ��
            break;
        }
    } while (input);  // ���û�ѡ��0�˳�ʱ������ѭ��
}

// ���ʽ���������������б��ʽ��ֵ
void ExpressionCalculator()
{
    string s;  // ���ڱ����û�����ı��ʽ
    cout << "��������ʽ:";
    cin.ignore();  // ����ǰһ����������Ļ��з�
    getline(cin, s);  // ��ȡ�������ʽ

    try
    {
        // ���Լ�����ʽ��ֵ����������
        cout << "�ñ��ʽֵΪ:" << Expression().Calculator(s) << endl << endl;
    }
    catch (const string& s)
    {
        // �������string���͵��쳣�����������Ϣ
        cout << s << endl << endl;
    }
    catch (...)
    {
        // ��������δ֪�쳣�����������ʾ
        cout << "δ֪�쳣" << endl << endl;
    }
}

// ����������ʾ�˵��������û���ѡ��
int main()
{
    int input;  // ���ڱ����û���ѡ��
    do
    {
        Menu();  // ��ʾ���˵�
        cout << "��ѡ��:";
        cin >> input;  // ��ȡ�û���ѡ��
        switch (input)
        {
        case 1:
            PolynomialCalculator();  // ѡ��1���������ʽ������
            break;
        case 2:
            ExpressionCalculator();  // ѡ��2��������ʽ������
            break;
        case 0:
            cout << "���˳�������" << endl;  // �û�ѡ���˳�
            break;
        default:
            cout << "����Ƿ���������ѡ��" << endl;  // �û�����Ƿ�ѡ��
            break;
        }
    } while (input);  // ���û�ѡ��0�˳�ʱ������ѭ��
    return 0;  // �������
}
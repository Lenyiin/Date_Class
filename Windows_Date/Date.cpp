#include "Date.hpp"
using namespace Lenyiin;

// ���Թ�����������
void TestDate_1()
{
    // Ĭ���޲ι���
    Date d1;
    // Ĭ���вι���
    Date d2(2024, 9, 1);
    // ��������
    Date d3(d2);

    // �����������
    std::cout << "d1 Ϊ " << d1 << std::endl;
    std::cout << "d2 Ϊ " << d2 << std::endl;
    std::cout << "d3 Ϊ " << d3 << std::endl;

    // ��ֵ����
    d1 = d3;
    std::cout << "d1 Ϊ" << d1 << std::endl;

    // ������������
    Date d4(2008, 2, 29);
    std::cout << "d4 Ϊ" << d4 << std::endl;

    // ����������Ч��
    Date d5(2007, 2, 29);
    std::cout << "d5 Ϊ" << d5 << std::endl;
}

// �������ڱȽ�
void TestDate_2()
{
    Date d1(2018, 3, 5);
    Date d2(2019, 6, 20);
    Date d3(d1);

    // ���� < 
    if (d1 < d2)
    {
        std::cout << d1 << " < " << d2 << std::endl;
    }
    if (d2 < d1)
    {
        std::cout << d2 << " < " << d1 << std::endl;
    }

    // ���� ==    !=
    if (d1 == d3)
    {
        std::cout << d1 << " == " << d3 << std::endl;
    }
    else
    {
        std::cout << d1 << " != " << d3 << std::endl;
    }
    if (d1 == d2)
    {
        std::cout << d1 << " == " << d2 << std::endl;
    }
    else
    {
        std::cout << d1 << " != " << d2 << std::endl;
    }

    // ���� <= 
    if (d1 <= d2)
    {
        std::cout << d1 << " <= " << d2 << std::endl;
    }
    if (d2 <= d1)
    {
        std::cout << d2 << " <= " << d1 << std::endl;
    }

    // ���� >
    if (d1 > d2)
    {
        std::cout << d1 << " > " << d2 << std::endl;
    }
    if (d2 > d1)
    {
        std::cout << d2 << " > " << d1 << std::endl;
    }

    //���� >=
    if (d1 >= d2)
    {
        std::cout << d1 << " >= " << d2 << std::endl;
    }
    if (d2 >= d1)
    {
        std::cout << d2 << " >= " << d1 << std::endl;
    }
}

// ������������
void TestDate_3()
{
    Date d1(2024, 9, 2);

    // ���Դ�ӡ����
    d1.Print();

    // +
    Date d2 = d1 + 100;
    // +=
    d1 += 100;
    d1.Print();
    d2.Print();

    // -
    d2 = d1 - 100;
    // -=
    d1 -= 100;
    d1.Print();
    d2.Print();

    // += ����
    d2 = d1 + (-100);
    d1 += -100;
    d1.Print();
    d2.Print();

    // -= ����
    d2 = d1 - (-100);
    d1 -= -100;
    d1.Print();
    d2.Print();
}

// �������ڲ�
void TestDate_4()
{
    Date d1(2024, 9, 2);

    // ǰ�� ++    ���� ++
    Date d2 = ++d1;
    Date d3 = d1++;
    d1.Print();
    d2.Print();
    d3.Print();

    // ǰ�� --    ���� --
    d2 = --d1;
    d3 = d1--;
    d1.Print();
    d2.Print();
    d3.Print();

    // ���ڲ�ֵ
    Date d4 = d1 + 100;
    std::cout << d4 << " - " << d1 << " = " << d4 - d1 << std::endl;

    // �����޸�
    Date d5(2024, 9, 2);
    std::cout << "�޸�ǰ�� d5 Ϊ" << d5 << std::endl;
    d5[0] = 2066, d5[1] = 6, d5[2] = 6;
    std::cout << "�޸ĺ�� d5 Ϊ" << d5 << std::endl;

    // ��������
    Date d6;
    std::cin >> d6;
    std::cout << "d6 Ϊ" << d6 << std::endl;
}

int main()
{
    //TestDate_1();

    //TestDate_2();

    //TestDate_3();

    TestDate_4();

    return 0;
}
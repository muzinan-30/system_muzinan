#include"pch.h"


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<sstream>



namespace  RSA
{
    //��ȡ������p��q
    int* primeget()
    {
        srand((unsigned)time(NULL));//�������������
        int p = rand() % 2001 + 1000;//��ȡ1000-3000��Χ�ڵ������
        int q = rand() % 2001 + 1000;
        int a[2];
        for (int i = p; i > 0; i--)//��ȡС�ڵ���p��q���������
        {
            for (int j = 2; j < i; j++)
            {
                if (i % j == 0)
                    break;
                else if (j == i - 1) {
                    p = i;
                    break;
                }
            }
            if (p == i + 1) break;
        }
        for (int i = q; i > 0; i--)
        {
            for (int j = 2; j < i; j++)
            {
                if (i % j == 0)
                    break;
                else if (j == i - 1) {
                    q = i;
                    break;
                }
            }
            if (q == i + 1) break;
        }
        a[0] = p;
        a[1] = q;
        return a;
    }

    int* get()
    {
        int* a = primeget();
        int b[4];
        int p = a[0], q = a[1];
        int n = p * q;
        int n1 = (p - 1) * (q - 1);//n1Ϊ��(n��
        int e;//eΪ����Կ
        int d;//dΪ����Կ
        int temp = (p > q) ? p : q;//tempΪp��q�нϴ��һ�������ڶ�e��ֵ
        srand((unsigned)time(NULL));//�������������
        e = rand() % (3000 - temp + 1) + temp;
        for (int i = e; i > 0; i--)//��ȡС�ڵ���e���������
        {
            for (int j = 2; j < i; j++)
            {
                if (i % j == 0)
                    break;
                else if (j == i - 1) {
                    e = i;
                    break;
                }
            }
            if (e == i + 1) break;
        }
        int k = rand() % 16 + 5;
        d = (k * n1 + 1) / e;
        b[0] = n;
        b[1] = n1;
        b[2] = e;
        b[3] = d;
        return b;
    }

    int encryption(int M)//���ܺ���
    {
        int e = get()[2];
        int n = get()[0];
        int sum = e / 5;
        int sup = e % 5;
        unsigned long long a = pow(M, 5);//����ģ�������ʶԴ������Ĵη�����������
        unsigned long long b = a % n;
        for (int i = 0; i < sum - 1; i++)
        {
            b = b * a % n;
        }
        unsigned long long C0 = pow(M, sup);
        int C = b * C0 % n;

        return C;
    }
    int decryption(int C)//���ܺ���
    {
        int d = get()[3];
        int n = get()[0];
        int sum = d / 5;
        int sup = d % 5;
        unsigned long long a = pow(C, 5);
        unsigned long long b = a % n;
        for (int i = 0; i < sum - 1; i++)
        {
            b = b * a % n;
        }
        unsigned long long M0 = pow(C, sup);
        int M = b * M0 % n;

        return M;
    }
    int binary2(char str[])//����������ת��Ϊʮ������
    {
        int sum = 0;
        int j = 1;
        int len = strlen(str) - 1;
        for (; len >= 0; len--)
        {
            sum += (int)str[len] * j;
            j *= 2;
        }

        return sum;
    }

}
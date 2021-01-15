#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char s[1000];
    int len;

} sstring;

void init(sstring *a, char *data)
{ //���ַ�����ֵ�����
    int i, j;
    j = strlen(data);
    for (i = 0; i < j; i++)
    {
        a->s[i] = 0;
        a->s[i] = data[i];
    }
    a->s[i] = '\0';
    a->len = j;
}
int com(sstring *a1, sstring *b1)
{ //�Ƚ������Ĵ�С��
    if (a1->len > b1->len)
    {
        return 1;
    }
    else if (a1->len == b1->len)
    {
        int i = 0;
        while (a1->s[i] == b1->s[i] && i < a1->len)
        {
            i++;
        }
        if (i == a1->len)
            return 0;
        else if (a1->s[i] > b1->s[i])
            return 1;
        else
            return -1;
    }
    else
        return -1;
}
void add(sstring *a1, sstring *b1, sstring *c1)
{
    char pp[100];
    int a[100];       //����
    int b[100];       //������
    int c[100] = {0}; //��
    int i, j = 0, k;  //i����ѭ����j��ʾ��λ ���������н�С�����ĳ��ȷŵ�k��
    int l1, l2, d;
    l1 = a1->len;
    l2 = b1->len;
    k = l1 > l2 ? l2 : l1;
    for (i = 0; i < a1->len; i++)
    { //�ַ���������������
        a[i] = a1->s[l1 - 1 - i] - '0';
    }
    for (i = 0; i < b1->len; i++)
    {
        b[i] = b1->s[l2 - 1 - i] - '0';
    }
    for (i = 0; i < k; i++)
    {
        d = a[i] + b[i] + j;
        j = d / 10;
        c[i] = d % 10;
    }
    while (i < l1)
    {
        d = a[i] + j;
        j = d / 10;
        c[i] = d % 10;
        i++;
    }
    while (i < l2)
    {
        d = b[i] + j;
        j = d / 10;
        c[i] = d % 10;
        i++;
    }
    if (j > 0)
    {
        c[i] = j;
        i++;
    }
    for (j = 0, k = i - 1; k > -1; k--, j++)
        pp[j] = c[k] + '0';
    pp[j] = '\0';
    init(c1, pp);
}
void subtract(sstring *a1, sstring *b1, sstring *c1)
{
    int a[100];       //�ѽϴ�������ڼ���
    int b[100];       //�ѽ�С�������ڱ�����
    int c[100] = {0}; //��
    int i, j, k;      //i����ѭ�� ,�������нϴ�����ĳ��ȷŵ�j��������н�С�����ĳ��ȷŵ�k��
    int flag;         //��־���Ϊ�����Ǹ���
    int l1, l2;
    char pp[100];
    l1 = a1->len;
    l2 = b1->len;
    k = l1 > l2 ? l2 : l1;
    j = l1 < l2 ? l2 : l1;
    if (strcmp(a1->s, b1->s) == 0)
    {
        init(c1, "0");
    }
    else
    {
        if (com(a1, b1) >= 0)
        { //����������ڱ�������������㡣���С�ڣ��͵���λ�á�
            flag = 0;
            for (i = 0; i < l1; i++)
            { //�ַ���������������
                a[i] = a1->s[l1 - 1 - i] - '0';
            }
            for (i = 0; i < l2; i++)
            {
                b[i] = b1->s[l2 - 1 - i] - '0';
            }
        }
        else
        {
            flag = 1;
            for (i = 0; i < l2; i++)
            {
                a[i] = b1->s[l2 - 1 - i] - '0';
            }
            for (i = 0; i < l1; i++)
            {
                b[i] = a1->s[l1 - 1 - i] - '0';
            }
        }
        for (i = 0; i < k; i++)
        {
            if (a[i] >= b[i])
                c[i] = a[i] - b[i];
            else
            {
                c[i] = a[i] + 10 - b[i];
                --a[i + 1];
            }
        }

        while (i < j)
        {
            if (a[i] >= 0)
                c[i] = a[i];
            else
            {
                c[i] = a[i] + 10;
                --a[i + 1];
            }
            i++;
        }
        while (c[i - 1] == 0)
            i--;
        j = 0;
        if (flag == 1)
            pp[j++] = '-';
        for (k = i - 1; k > -1; k--, j++)
            pp[j] = c[k] + '0';
        pp[j] = '\0';
        init(c1, pp);
    }
}
void multiply(sstring *a1, sstring *b1, sstring *c1)
{

    int a[100];
    int b[100];
    int c[100] = {0};
    int d, i, j, k; //i,j����ѭ��
    int flag = 0;   //��λ
    int l1, l2;
    l1 = a1->len;
    l2 = b1->len;
    init(c1, "0");
    for (i = 0; i < a1->len; i++)
    {
        a[i] = a1->s[l1 - 1 - i] - '0';
    }
    for (i = 0; i < b1->len; i++)
    {
        b[i] = b1->s[l2 - 1 - i] - '0';
    }
    for (i = 0; i < l2; i++)
    {
        flag = 0;
        for (j = 0; j < l1; j++)
        {
            d = a[j] * b[i] + flag;
            c[j] = d % 10;
            flag = d / 10;
        }
        if (flag > 0)
        {
            c[j] = flag;
            j++;
        }
        while (c[j - 1] == 0)
            j--;

        char str[100];
        for (k = 0; k < j; k++)
            str[k] = c[j - 1 - k] + '0';
        for (j = 0; j < i; j++)
            str[k++] = '0';
        str[k] = '\0';
        sstring *ff;
        ff = (sstring *)malloc(sizeof(sstring));
        init(ff, str);
        add(c1, ff, c1);
    }
}
void one(char *a)
{
    int i, l = strlen(a);
    int carry = 1;
    char t;
    for (i = 0; i < l; i++)
    {
        t = a[i] + carry;
        if (t > 9 + '0')
        {
            t = '0';
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        a[i] = t;
    }
    if (carry == 1)
        a[i++] = '1';
    a[i] = '\0';
}
void divide(sstring *a1, sstring *b1, sstring *c1, sstring *d1)
{   //CΪ�̣�DΪ����
    // int i,j,k,
    char t[100] = {0};
    char b[2] = "0";
    if (com(a1, b1) == 0)
    {
        init(d1, "0");
        init(c1, "1");
    }
    else if (com(a1, b1) < 0)
    {
        init(d1, a1->s);
        init(c1, "0");
    }
    else
    {
        sstring *aa;
        aa = (sstring *)malloc(sizeof(sstring));
        init(aa, a1->s);
        while (com(aa, b1) >= 0)
        {
            subtract(aa, b1, c1);
            init(aa, c1->s);
            one(t);
        }
        init(c1, t);
        init(d1, aa->s);
    }
}
int main()
{
    int flag = 1;
    while (flag)
    {
        printf("\n--------------------------------������������----------------------------------\n");
        printf("\n *************** 0���˳�             1,��������������             2��������� ************* \n");
        printf("\n *************** 3���������     4���������                       5���������*************\n");
        printf("\n ��ʾ������Ӧ���ֽ�����Ӧ��������������������ٽ������� \n");
        printf("\n----------------------------------------------------------------------------\n");
        scanf("%d", &flag);
        sstring *a, *b, *c;
        a = (sstring *)malloc(sizeof(sstring));
        b = (sstring *)malloc(sizeof(sstring));
        c = (sstring *)malloc(sizeof(sstring));
        if (flag == 1)
        {
            printf("\n ������������� \n");
            char a1[100], b1[100];
            scanf("%s", &a1);
            scanf("%s", &b1);
            init(a, a1);
            init(b, b1);
            int co;
            printf("\n ��������������� \n");
            scanf("%d", &co);
            while (co)
            {
                if (co == 1)
                {
                    printf("\n ��������������� ����\n");
                    break;
                }
                else if (co == 2)
                {
                    add(a, b, c);
                    printf("����֮��Ϊ��%s\n", c->s);
                }
                else if (co == 3)
                {
                    subtract(a, b, c);
                    printf("����֮��Ϊ��%s\n", c->s);
                }
                else if (co == 4)
                {
                    multiply(a, b, c);
                    printf("����֮��Ϊ��%s\n", c->s);
                }
                else if (co == 5)
                {
                    sstring *d;
                    d = (sstring *)malloc(sizeof(sstring));
                    if (strcmp(b->s, "0") == 0)
                    {
                        printf("��������Ϊ0");
                        break;
                    }
                    else
                    {
                        divide(a, b, c, d);
                        printf("��Ϊ:   ");
                        int i = strlen(c->s) - 1;
                        for (; i >= 0; i--)
                        {
                            printf("%c", c->s[i]);
                        }
                        printf(" ����Ϊ:%s ", d->s);
                    }
                }
                else
                {
                    printf("\n �����������������!!!\n");
                }
                printf("\n ��������������� \n");
                scanf("%d", &co);
            }
        }
        else if (flag == 0)
        {
            printf("\n �˳��ü������� \n");
        }
        else
        {

            printf("\n �����������������!!!\n");
        }
    }
    return 0;
}


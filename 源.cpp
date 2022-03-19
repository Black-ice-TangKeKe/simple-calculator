#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//本程序用于计算数学表达式，请在表达式的结尾加一个‘=’，例如：8/4+2-(5-1)=
//本程序支持且仅支持十位数以下运算，不然就寄
//本程序不能省略符号,如：2(5+3);要写为：2*(5+3)
// 
// 
// 
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG


struct Stack
{
    float n[40];
    char s[20];
    int top;
}sym, num;
Stack* pn = &num;
Stack* ps = &sym;


void chushihua(struct Stack* stack)  //初始化栈
{
    stack->top = -1;
}


int empty(struct Stack* stack)  //检查栈是否为空
{
    if (stack->top == -1)
        return 1;
    else
        return 0;
}


void nruzhan(struct Stack* stack, float value)  //数字入栈
{
    stack->n[++stack->top] = value;
}


void sruzhan(struct Stack* stack, char value)  //符号入栈
{
    stack->s[++stack->top] = value;
}


float nchuzhan(struct Stack* stack)  //数字出栈
{
    return stack->n[stack->top--];
}


char schuzhan(struct Stack* stack)  //符号出栈
{
    if (empty(stack))
        printf("栈空");
    return stack->s[stack->top--];
}

void compute(struct Stack* pn, struct Stack* ps) //弹出计算
{
    float a, b;
    char s;
    b = nchuzhan(pn);
    a = nchuzhan(pn);
    s = schuzhan(ps);
    switch (s)
    {
    case '+':
        nruzhan(pn, a + b); break;
    case '-':
        nruzhan(pn, a - b); break;
    case '*':
        nruzhan(pn, a * b); break;
    case '/':
        nruzhan(pn, a * 1.0 / b); break;
    default:
        printf("error"); break;
    }

}


int cmpe(char a)//比较a与栈顶符号优先级
{
    int k=0, k2=0;
    char  b;
    if (empty(ps))
        return 1;
    b = schuzhan(ps);
    sruzhan(ps, b);
    if (a == '(')
        return 1;
    switch (a)
    {
    case '+': k = 1; break;
    case '-': k = 1; break;
    case '*': k = 2; break;
    case '/': k = 2; break;
    default:break;
    }
    switch (b)
    {
    case '+': k2 = 1; break;
    case '-': k2 = 1; break;
    case '*': k2 = 2; break;
    case '/': k2 = 2; break;
    default:break;
    }
    if (k > k2)
        return 1;
    else
        return 0;
}

void scan(struct Stack* pn, struct Stack* ps)//扫描该表达式，直到‘=’
{
    char temp1=0;
    
    while (temp1 != '=')
    {
        scanf("%c", &temp1);
        if (temp1 >= '0' && temp1 <= '9')//判断是不是数字

            nruzhan(pn, (float)temp1-48);  //数字直接入栈
        else
        {
            if (ps->top == -1)  //判断符号栈是否为空
            {
                if(temp1!='\n')
                sruzhan(ps, temp1);
                continue;
            }

            else if (temp1 != '=')
            {
                if (temp1 == ')')
                {
                    while (ps->s[ps->top] != '(') //不断弹出计算直到左括号
                    {

                        compute(pn, ps);
                    }
                    ps->top--;
                }
                else
                {
                    if (cmpe(temp1))  //判断是否能入栈
                    {
                        if (temp1 != '\n')
                            sruzhan(ps, temp1);
                    }
                    else
                    {
                        while (!cmpe(temp1))//无法入栈，弹出计算
                        {
                            compute(pn, ps);
                        }
                        if (temp1 != '\n')
                            sruzhan(ps, temp1);
                    }
                }

            }

        }
    }

}


int main()
{
    printf("本程序用于计算中缀表达式\n");
    printf("请在表达式的结尾加一个‘=’，例如：8/4+2-(5-1)=\n");
    printf("本程序支持且仅支持十位数以下运算，不然就寄\n");
    printf("本程序不能省略符号,如：2(5+3);要写为：2*(5+3)\n");
    system("pause");
    while (1)
    {

        chushihua(ps);
        chushihua(pn);
        system("cls");
        printf("请输入表达式：\n");
        scan(pn, ps);
        while (ps->top != -1)//处理栈内残留
        {
            compute(pn, ps);
        }
        printf("%.6f\n", pn->n[0]);
        printf("\n");
        system("pause");
    }
    return 0;
}
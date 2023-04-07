#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

int err = 0;//����üũ ����
typedef char element;
element peak(s);
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s)
{
    s->top = -1;
}

int is_empty(StackType* s) {
    return (s->top == -1);
}

int is_full(StackType* s) {
    return(s->top == (MAX_STACK_SIZE - 1));

}

void push(StackType* s, element item) {
    if (is_full(s)) {

        fprintf(stderr, "---stack full error--- \n");
        return;

    }
    else s->data[++(s->top)]=item ;

}

element pop(StackType* s) {
    //element d = peak(s);//������     
    //printf("%d", d);

    if (is_empty(s)){
        fprintf(stderr, "---pop stack empty error--- \n");

        return;

    }

    else return s->data[(s->top)--];//top�� �ش��ϴ� data�� ��ȯ�� top���� 1�� ����.


}

element peak(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "peak stack empty error \n");
        return -1;

    }

    else return s->data[(s->top)];//top�� �ش��ϴ� data�� ��ȯ

}

int eval(char exp[]) {

    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;
    init_stack(&s);

    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            value = ch - '0';//���ڿ��� ���ڷ� �ٲ� , �ƽ�Ű �ڵ尪���� 0(�ƽ�Ű�ڵ� 48)�� ���� ���ڰ��� �� �ٷ�����Ʈ�ϸ� ���ٸ��Գ���
            push(&s, value);

        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+':push(&s, op1 + op2); break;
            case '-':push(&s, op1 - op2); break;
            case '*':push(&s, op1 * op2); break;
            case '/':push(&s, op1 / op2); break;

            }
        }
       
    }
    return pop(&s);
}


void check_error(element exp[]) {
    err = -1;
    int len = strlen(exp);


    for (int i = 0; i < len; i++) {
        if (i + 1 < len && exp[i] == '/' && exp[i + 1] == '0') {
            printf("<<error �߻�>>\n");
            printf("error0: divide by 0\n\n");
            err = 0;
            break;
        }
    }



    for (int i = 0; i < len; i++) {
        if (exp[i] == '('|| exp[i] == ')') {
            err = 1;
            printf("<<error �߻�>>\n");
            printf("��ȣ�� �ȵ�\n\n");
        }
       
    }
  

    for (int i = 0; i < len; i++) {
        if (exp[i] == '(' || exp[i] == ')') {
            continue;
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            continue;
        }
        else if ('0' <= exp[i] && exp[i] <= '9') {
            continue;
        }
        else {
            printf("<<error �߻�>>\n");
            printf("error2: ���� ���� ����\n\n");
            err = 2;
        }
    }


    int count_len = 0;
    int max_len = 0;
    for (int i = 0; i < len; i++) {
        if ('0' <= exp[i] && exp[i] <= '9') {
            count_len++;
            if (count_len >= max_len) {
                max_len = count_len;
            }
        }
        else {
            count_len = 0;
        }
    }

    if (max_len >= 2) {
        printf("<<error �߻�>>\n");
        printf("error3: �� �ڸ��� �̻��� �Է� ����\n\n");
        err = 3;
    }
   
}


int main(void)
{
    element expression[MAX_STACK_SIZE];

    // ���� �ݺ���
    while (1) {
        // ���� ǥ��� �Է�
        printf("enter an postfix Exp :");
        scanf_s("%s", expression, (int)sizeof(expression));//scanf_s�̷��Ծ��ϸ� ������
        check_error(expression);

       
       
        if (err == -1) {
            printf("result: : %d\n\n", eval(expression));
        }


    }

    return 0;
}
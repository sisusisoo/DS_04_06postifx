#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

int err = 0;//에러체크 변수
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
    //element d = peak(s);//디버깅용     
    //printf("%d", d);

    if (is_empty(s)){
        fprintf(stderr, "---pop stack empty error--- \n");

        return;

    }

    else return s->data[(s->top)--];//top에 해당하는 data를 반환후 top에서 1을 뺀다.


}

element peak(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "peak stack empty error \n");
        return -1;

    }

    else return s->data[(s->top)];//top에 해당하는 data를 반환

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
            value = ch - '0';//문자열을 숫자로 바꿈 , 아스키 코드값에서 0(아스키코드 48)을 빼면 숫자값이 됨 바로프린트하면 값다르게나옴
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
            printf("<<error 발생>>\n");
            printf("error0: divide by 0\n\n");
            err = 0;
            break;
        }
    }



    for (int i = 0; i < len; i++) {
        if (exp[i] == '('|| exp[i] == ')') {
            err = 1;
            printf("<<error 발생>>\n");
            printf("괄호는 안됨\n\n");
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
            printf("<<error 발생>>\n");
            printf("error2: 예외 문자 포함\n\n");
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
        printf("<<error 발생>>\n");
        printf("error3: 한 자리수 이상의 입력 포함\n\n");
        err = 3;
    }
   
}


int main(void)
{
    element expression[MAX_STACK_SIZE];

    // 무한 반복문
    while (1) {
        // 중위 표기식 입력
        printf("enter an postfix Exp :");
        scanf_s("%s", expression, (int)sizeof(expression));//scanf_s이렇게안하면 오류남
        check_error(expression);

       
       
        if (err == -1) {
            printf("result: : %d\n\n", eval(expression));
        }


    }

    return 0;
}
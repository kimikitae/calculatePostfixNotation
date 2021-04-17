// If the operand is 0, there is a bug that cannot be calculated, but I want to fix it.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// 피크함수
element peek(StackType *s){
    if (is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}

//후위 표기 수식 계산 함수
int eval(char exp[]){
    int op1, op2, a = 0, i = 0, value = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for(i = 0; i < len; i++){
        ch = exp[i];
        //ch가 수라면
        if (isdigit(ch)){
            if (is_empty(&s)) push(&s,(ch - '0'));
            else {
                value = pop(&s) * 10 + (ch - '0');
                push(&s, value);
            }
        }
        //ch가 공백이라면
        else if (isspace(ch)) push(&s, 0) ;
        //ch가 연산자라면
        else {
            while (peek(&s) == 0) {
                pop(&s);
            }op2 = pop(&s);
            
            while (peek(&s) == 0) {
                pop(&s);
            }op1 = pop(&s);

            switch (ch) {
                case '+': 
                    push(&s, op1 + op2);
                    break;
                case '-': 
                    push(&s, op1 - op2);
                    break;
                case '*': 
                    push(&s, op1 * op2);
                    break;
                case '/': 
                    push(&s, op1 / op2);
                    break;
            }push(&s, 0);
        }
    }
    while (peek(&s) == 0) {
                pop(&s);
    }
    return pop(&s);
}

int main(void)
{
	int result;
    
    //모든 피연산자 사이에 ' ' 이 존재하도록 설계됨
    printf("후위표기식은 135 1865 25 *7 /+1025 -\n"); 
    result = eval("135 1865 25 *7 /+1025 -");
    printf("결과값은 %d\n", result);
    return 0;
}

/* 
 * Priority Calculator 
 * using Stack
 * create by Eskeptor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define SUM(X,Y) (X)+(Y)
#define MULTI(X,Y) (X)*(Y)
#define DIV(X,Y) (X)/(Y)

typedef struct _Stack {
	char Operator[MAX];
	int Operand[MAX];
	int Opt_top;
	int Opd_top;
}Stack;
Stack stack;

void init() {
	stack.Opd_top = stack.Opt_top = 0;
}

void optPush(char opt) {
	stack.Operator[stack.Opt_top++] = opt;
}

void opdPush(int opd) {
	stack.Operand[stack.Opd_top++] = opd;
}

char optPop() {
	return stack.Operator[--stack.Opt_top];
}

int opdPop() {
	return stack.Operand[--stack.Opd_top];
}

void resetExpression(char Exp[], int len) {
	for (int i = 0; i < len; i++)
		Exp[i] = '\0';
}

int optCheck(char opt1, char opt2) {
	if (opt1 == '*' || opt1 == '/') {
		if (opt2 == '+' || opt2 == '-')
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int calFunc(int opd1, int opd2, char opt) {
	int result;
	switch (opt) {
	case '+':
		result = SUM(opd1, opd2);
		break;
	case '*':
		result = MULTI(opd1, opd2);
		break;
	case '/':
		result = DIV(opd1, opd2);
		break;
	}
	return result;
}

void calEngine(char Exp[], int len) {
	char tmpExp[MAX] = { 0, };// 2자리 이상의 수 입력을 받기위해 배열을 선언
	char ch, opt;
	int tmpCnt = 0, opd1, opd2, res, flag = 0;
	// flag는 빼기 연산을 판단할겁니다.
	for (int i = 0; i < len; i++) {
		ch = Exp[i];
		if (ch == ' ') // 공백의 경우에는 그냥 넘김
			continue;
		else if (ch >= '0' && ch <= '9') { // 숫자일 때
			tmpExp[tmpCnt++] = ch; // 숫자를 tmpExp에 저장
								   // 지금 숫자바로 다음에 오는 문자가 숫자가 아닐 경우에
			if (Exp[i + 1] == '(' || Exp[i + 1] == ')' || Exp[i + 1] == '+' || Exp[i + 1] == '-' || Exp[i + 1] == '*' || Exp[i + 1] == '/' || Exp[i + 1] == '=') {
				if (flag) {
					// 만약에 빼기 연산이 일어날 경우에
					flag = 0;
					// 빼기연산 판단 변수를 다시 0으로 만들어줍니다.
					opdPush(-atoi(tmpExp));
					// atoi는 문자열을 숫자로 바꿔주는 함수입니다.
					// 빼기 연산을 하지 않고 입력된 수를 음수로 바꿔줍니다.
					// 나머지 설명은 아래에서..
				}
				else
					opdPush(atoi(tmpExp));
				// 빼기연산이 아니면 그냥 숫자로 넣어줍니다.
				resetExpression(tmpExp, tmpCnt);
				// tmpExp의 내용을 초기화시켜줍니다.
				tmpCnt = 0;
			}
			// tmpExp를 따로 한 이유는 2자리 이상의 수를 입력받았을 때 다음에 올 문자를 토대로
			// 판단하여 다음에 올 문자가 숫자일 경우에 연달아서 배열에 넣어 atoi를 사용하여 숫자로 변환 후에
			// 자료구조에 넣어줍니다.
			// 이 방법을 사용하지 않을 경우에 25가 입력되면 2와 5 즉, 25가 아닌 2와 5로 인식해버리기 때문입니다.
		}
		//만약에 연산기호가 입력되면
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			if (ch == '-') {
				// 빼기연산이 감지되면 빼기연산 변수를 1로 활성화시키고
				flag = 1;
				// 연산을 더하기로 바꿔준다.
				ch = '+';
				// flag가 1이되면 위에서 음수로 바꿔주기에 더하기로 바뀌어도 무관하다.
				// 이 방법을 이용하는 이유는 일반적인 빼기연산으로 하면 음수가 나와도 양수로 인식해버리고 계산해버리기 때문이다.
			}
			if (stack.Opt_top == 0)
				optPush(ch);
			// 연산자배열에 연산자가 없는경우에는 그냥 넣어주기만 한다.
			else { // 연산자 배열에 연산자가 있는 경우에는
				opt = optPop();
				// 연산자 하나를 빼온다.
				if (optCheck(opt, ch)) { // 그리고 연산자 우선순위를 이전 연산자(opt)와 현재 연산자(ch)를 비교하여 계산한다.
					opd2 = opdPop();
					opd1 = opdPop();
					res = calFunc(opd1, opd2, opt);
					opdPush(res);
					optPush(ch);
				}
				else { // 우선순위 변동이 없을시에(혹은 괄호일 시에) 빼온 연산자와 지금 연산자를 다시 스택에 넣어준다.
					optPush(opt);
					optPush(ch);
				}
			}
		}
		else if (ch == '(') // 괄호가 열리면 열린 괄호를 넣어준다.
			optPush(ch);
		else if (ch == ')') { // 괄호가 닫히면
			while (opt != '(') { // 열린 괄호가 나올때까지 아래의 연산을 시행한다.(괄호 우선 계산)
				opt = optPop(); // 연산자를 뽑아온다.
				if (opt != '(') { // 열린 괄호가 나올때 까지 아래의 연산을 시행한다.(괄호 우선 계산, 괄호가 하나 더 있을지도 모르니)
					opd2 = opdPop(); // 스택은 나중에 입력한 것부터 나오기 때문에 2번에 저장, 그리고 나서 1번에 저장
					opd1 = opdPop();
					res = calFunc(opd1, opd2, opt);
					opdPush(res); // 계산된 값을 다시 숫자배열에 넣기
				}
			}
		}
		else if (ch == '=') // =이 나오면 바로 종료
			break;
	}
	while (stack.Opt_top != 0) { //위에서 있었던 우선계산이후의 배열을 최종적으로 계산
		opd1 = opdPop();
		opd2 = opdPop();
		opt = optPop();
		res = calFunc(opd1, opd2, opt);
		opdPush(res);
	}
}

int main(void) {
	char Expression[MAX] = { 0, };
	printf("Input : ");
	gets(Expression);
	calEngine(Expression, strlen(Expression));
	printf("Result = %d\n", opdPop());
	return 0;
}
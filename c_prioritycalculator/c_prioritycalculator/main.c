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
	char tmpExp[MAX] = { 0, };// 2�ڸ� �̻��� �� �Է��� �ޱ����� �迭�� ����
	char ch, opt;
	int tmpCnt = 0, opd1, opd2, res, flag = 0;
	// flag�� ���� ������ �Ǵ��Ұ̴ϴ�.
	for (int i = 0; i < len; i++) {
		ch = Exp[i];
		if (ch == ' ') // ������ ��쿡�� �׳� �ѱ�
			continue;
		else if (ch >= '0' && ch <= '9') { // ������ ��
			tmpExp[tmpCnt++] = ch; // ���ڸ� tmpExp�� ����
								   // ���� ���ڹٷ� ������ ���� ���ڰ� ���ڰ� �ƴ� ��쿡
			if (Exp[i + 1] == '(' || Exp[i + 1] == ')' || Exp[i + 1] == '+' || Exp[i + 1] == '-' || Exp[i + 1] == '*' || Exp[i + 1] == '/' || Exp[i + 1] == '=') {
				if (flag) {
					// ���࿡ ���� ������ �Ͼ ��쿡
					flag = 0;
					// ���⿬�� �Ǵ� ������ �ٽ� 0���� ������ݴϴ�.
					opdPush(-atoi(tmpExp));
					// atoi�� ���ڿ��� ���ڷ� �ٲ��ִ� �Լ��Դϴ�.
					// ���� ������ ���� �ʰ� �Էµ� ���� ������ �ٲ��ݴϴ�.
					// ������ ������ �Ʒ�����..
				}
				else
					opdPush(atoi(tmpExp));
				// ���⿬���� �ƴϸ� �׳� ���ڷ� �־��ݴϴ�.
				resetExpression(tmpExp, tmpCnt);
				// tmpExp�� ������ �ʱ�ȭ�����ݴϴ�.
				tmpCnt = 0;
			}
			// tmpExp�� ���� �� ������ 2�ڸ� �̻��� ���� �Է¹޾��� �� ������ �� ���ڸ� ����
			// �Ǵ��Ͽ� ������ �� ���ڰ� ������ ��쿡 ���޾Ƽ� �迭�� �־� atoi�� ����Ͽ� ���ڷ� ��ȯ �Ŀ�
			// �ڷᱸ���� �־��ݴϴ�.
			// �� ����� ������� ���� ��쿡 25�� �ԷµǸ� 2�� 5 ��, 25�� �ƴ� 2�� 5�� �ν��ع����� �����Դϴ�.
		}
		//���࿡ �����ȣ�� �ԷµǸ�
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			if (ch == '-') {
				// ���⿬���� �����Ǹ� ���⿬�� ������ 1�� Ȱ��ȭ��Ű��
				flag = 1;
				// ������ ���ϱ�� �ٲ��ش�.
				ch = '+';
				// flag�� 1�̵Ǹ� ������ ������ �ٲ��ֱ⿡ ���ϱ�� �ٲ� �����ϴ�.
				// �� ����� �̿��ϴ� ������ �Ϲ����� ���⿬������ �ϸ� ������ ���͵� ����� �ν��ع����� ����ع����� �����̴�.
			}
			if (stack.Opt_top == 0)
				optPush(ch);
			// �����ڹ迭�� �����ڰ� ���°�쿡�� �׳� �־��ֱ⸸ �Ѵ�.
			else { // ������ �迭�� �����ڰ� �ִ� ��쿡��
				opt = optPop();
				// ������ �ϳ��� ���´�.
				if (optCheck(opt, ch)) { // �׸��� ������ �켱������ ���� ������(opt)�� ���� ������(ch)�� ���Ͽ� ����Ѵ�.
					opd2 = opdPop();
					opd1 = opdPop();
					res = calFunc(opd1, opd2, opt);
					opdPush(res);
					optPush(ch);
				}
				else { // �켱���� ������ �����ÿ�(Ȥ�� ��ȣ�� �ÿ�) ���� �����ڿ� ���� �����ڸ� �ٽ� ���ÿ� �־��ش�.
					optPush(opt);
					optPush(ch);
				}
			}
		}
		else if (ch == '(') // ��ȣ�� ������ ���� ��ȣ�� �־��ش�.
			optPush(ch);
		else if (ch == ')') { // ��ȣ�� ������
			while (opt != '(') { // ���� ��ȣ�� ���ö����� �Ʒ��� ������ �����Ѵ�.(��ȣ �켱 ���)
				opt = optPop(); // �����ڸ� �̾ƿ´�.
				if (opt != '(') { // ���� ��ȣ�� ���ö� ���� �Ʒ��� ������ �����Ѵ�.(��ȣ �켱 ���, ��ȣ�� �ϳ� �� �������� �𸣴�)
					opd2 = opdPop(); // ������ ���߿� �Է��� �ͺ��� ������ ������ 2���� ����, �׸��� ���� 1���� ����
					opd1 = opdPop();
					res = calFunc(opd1, opd2, opt);
					opdPush(res); // ���� ���� �ٽ� ���ڹ迭�� �ֱ�
				}
			}
		}
		else if (ch == '=') // =�� ������ �ٷ� ����
			break;
	}
	while (stack.Opt_top != 0) { //������ �־��� �켱��������� �迭�� ���������� ���
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
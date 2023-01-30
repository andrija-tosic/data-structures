#include "Stack.h"
#include <iostream>
using namespace std;

bool areParenthesesMatching(char* expression)
{
	int i;
	for (i = 0; expression[i] != '\0'; i++) {}

	Stack stek(i);
	for (i = 0; expression[i] != '\0'; i++) {
		switch (expression[i]) {
		case '(':
		case '[':
		case '{':
			stek.push(expression[i]);
			break;
		case ')':
			if (!stek.isEmpty() && stek.getTop() == '(') {
				stek.pop();
			}
			else return false;
			break;
		case ']':
			if (!stek.isEmpty() && stek.getTop() == '[') {
				stek.pop();
			}
			else return false;
			break;
		case '}':
			if (!stek.isEmpty() && !stek.getTop() == '{') {
				stek.pop();
			}
			else return false;
			break;
		}
	}
	return stek.isEmpty();
}

void main()
{
	char expression1[] = "5 + [2-(5+3/5)/(5+2)]";
	char expression2[] = "{4 + 2 / 10 +[(3*3)}";
	char expression3[] = "(8 + 10 / 20 ))";
	cout << areParenthesesMatching(expression1);
	cout << areParenthesesMatching(expression2);
	cout << areParenthesesMatching(expression3);
}
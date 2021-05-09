/* jun 2018
Napisati funkciju char* Infix2Postfix(char* expr), koja aritmeticki izraz
expr prevodi iz infiks u postfiks notaciju. Smatrati da postoji implementirana
pomocna struktura potrebna za resavanje ovog problema, kao i da su operandi
jednoslovni, a operatori: +, -, * i /. Primer konverzije:
[((a+b)*c/d+e*f)/g] -> [ab+c*d/ef*+g/]
*/
int precedence(char op)
{
	if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return 0;
}

char* Infix2Postfix(char* expr) // j duzina jbg
{
	Stack s(strlen(expr));
	char* postf = new char[strlen(expr) + 1];
	int j = 0;
	char c;

	for (int i = 1; i < strlen(expr) - 1; i++)
	{
		c = expr[i];
		if (c >= 'a' && c <= 'z')
		{
			postf[j++] = c;
		}
		else if (c == '(')
		{
			s.push(c);
		}
		else if (c == ')')
		{
			while (!s.isEmpty() && s.getTop() != '(')
			{
				postf[j++] = s.pop();
			}

			if (!s.isEmpty())
			{
				s.pop();
			}
			else
			{
				throw "Izraz nije validan. Zagrade se ne poklapaju.";
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			while (!s.isEmpty() && precedence(s.getTop()) >= precedence(c))
			{
				postf[j++] = s.pop();
			}
			s.push(c);
		}
		else
		{
			throw "Izraz nije validan. Nedozvoljen karakter.";
		}
	}

	while (!s.isEmpty())
	{
		if (s.getTop() == '(')
			throw "Izraz nije validan. Zagrade se ne poklapaju.";
		postf[j++] = s.pop();
	}

	for (int i = 0; i < strlen(expr); i++)
		std::cout << expr[i];

	std::cout << std::endl;
	for (int i = 0; i < j; i++)
		std::cout << postf[i];

	return postf;
}

/*
2017 kol 1
Napisati funkciju bool isCorrect(char* inStr), koja utvrduje da li je aritmeticki izraz,
zadat kao ulazni niz karaktera, ispravan sa stanovista zatvaranja zagrada. U izrazu se mogu pojaviti
male, srednje i velike zagrade. Npr. izraz {(a+b)*[(c-d)]} je ispravan, dok izraz {[a+b]*(c-d}) nije.
Smatrati da postoji implemetirana struktura sa svim odgovarajucim operacijama, koju je potrebno
instancirati za odgovarajuci tip podataka.
*/
bool isCorrect(char* inStr)
{
	Stack s(strlen(inStr));

	for (int i = 0; inStr[i] != '\0'; i++)
	{
		switch (inStr[i])
		{
		case '(':
		case '{':
		case '[':
			s.push(inStr[i]);
			break;
		case ')':
			if (!s.isEmpty() && s.getTop() == '(')
				s.pop();
			else
				return false;
			break;
		case '}':
			if (!s.isEmpty() && s.getTop() == '{')
				s.pop();
			else
				return false;
			break;
		case ']':
			if (!s.isEmpty() && s.getTop() == '[')
				s.pop();
			else
				return false;
			break;
		}
	}
	
	return s.isEmpty();
}
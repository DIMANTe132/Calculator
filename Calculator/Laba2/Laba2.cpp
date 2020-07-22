/*!
\file
\brief Файл реализующий вторую лабораторную работу.

Задача:
Написать программу, анализирующую математическое выражение и вычисляющую его значение.
*/
#include <iostream>
#include <string>

using namespace std;

/**
\brief Структура знака
\param value − сам знак
\param weight - приоритет знака

Код структуры выглядит следующим образом:
\code
	struct Sign
	{
		string value;
		int weight;

		Sign() {}

		Sign(string value, int weight)
		{
			this->value = value;
			this->weight = weight;
		}
	};
	\endcode
\authors Tereshin D.D
 */
struct Sign
{
	string value;
	int weight;

	Sign() {}

	Sign(string value, int weight)
	{
		this->value = value;
		this->weight = weight;
	}
};

/**
\brief Функция подсчитывающая количество элементов
\param stack − указатель на элемент типа Sign
\return int - количество элементов

Код функции выглядит следующим образом:
\code
	int Count(Sign* stack)
	{
		int i = 0;
		while (true)
		{
			if (stack[i].value == "")
				return i;
			i++;
		}
	}
	\endcode
\authors Tereshin D.D
 */
int Count(Sign* stack)
{
	int i = 0;
	while (true)
	{
		if (stack[i].value == "")
			return i;
		i++;
	}
}

/**
\brief Функция выполняющая математические действия
\param FirstNumber − строка с первым числом
\param SecondNumber − строка со вторым числом
\param sign − знак операции
\return string - результат операции

Код функции выглядит следующим образом:
\code
	string Calculation(string FirstNumber, string SecondNumber, string sign)
	{
		double first = stod(FirstNumber);
		double second = stod(SecondNumber);
		double result;
		if (sign == "+")
		{
			result = first + second;
		}
		else if (sign == "-")
		{
			result = first - second;
		}

		else if (sign == "/")
		{
			result = first / second;
		}

		else if (sign == "*")
		{
			result = first * second;
		}

		return to_string(result);
	}
	\endcode
\authors Tereshin D.D
 */
string Calculation(string FirstNumber, string SecondNumber, string sign)
{
	double first = stod(FirstNumber);
	double second = stod(SecondNumber);
	double result;
	if (sign == "+")
	{
		result = first + second;
	}
	else if (sign == "-")
	{
		result = first - second;
	}

	else if (sign == "/")
	{
		result = first / second;
	}

	else if (sign == "*")
	{
		result = first * second;
	}

	return to_string(result);
}

/**
\brief Функция кладущая строку в конец массива
\param arr − массив, в который нужно положить элемент
\param number − строка для операции
\param i − индекс места, в которое нужно положить элемент

Код функции выглядит следующим образом:
\code
	void PushBack(string* arr, const string& number, int& i)
	{
		if (number.length() != 0)
		{
			arr[i] = number;
			i++;
		}
	}
	\endcode
\authors Tereshin D.D
 */
void PushBack(string* arr, const string& number, int& i)
{
	if (number.length() != 0)
	{
		arr[i] = number;
		i++;
	}
}

/**
\brief Функция кладущая знак в конец массива
\param arr − массив, в который нужно положить элемент
\param number − знак для операции
\param i − индекс места, в которое нужно положить элемент

Код функции выглядит следующим образом:
\code
	void PushBack(Sign* arr, Sign& sign, int& i)
	{
		arr[i] = sign;
		i++;
	}
	\endcode
\authors Tereshin D.D
 */
void PushBack(Sign* arr, Sign& sign, int& i)
{
	arr[i] = sign;
	i++;
}

/**
\brief Функция выдающая знак из конца массива и удаляет его
\param arr − массив, из которого нужно взять элемент
\param i − индекс места, из которого нужно взять элемент
\return Sign - последний элемент в массиве

Код функции выглядит следующим образом:
\code
	Sign PopBack(Sign* arr, int& i)
	{
		Sign sign = arr[i - 1];
		arr[i - 1].value = "";
		arr[i - 1].weight = 0;
		i--;
		return sign;
	}
	\endcode
\authors Tereshin D.D
 */
Sign PopBack(Sign* arr, int& i)
{
	Sign sign = arr[i - 1];
	arr[i - 1].value = "";
	arr[i - 1].weight = 0;
	i--;
	return sign;
}

/**
\brief Функция выдающая строку из конца массива и удаляет ее
\param arr − массив, из которого нужно взять элемент
\param i − индекс места, из которого нужно взять элемент
\return string - последний элемент в массиве

Код функции выглядит следующим образом:
\code
	string PopBack(string* arr, int& i)
	{
		string str = arr[i - 1];
		arr[i - 1] = "";
		i--;
		return str;
	}
	\endcode
\authors Tereshin D.D
 */
string PopBack(string* arr, int& i)
{
	string str = arr[i - 1];
	arr[i - 1] = "";
	i--;
	return str;
}

/**
\brief Функция выдающая строку из конца массива и удаляет ее
\param tokens − массив токенов
\param countOfTokens − количество токенов
\param variables − массив строк переменных
\param countOfVariables − количество строк переменных
\return string - результат всего выражения

Код функции выглядит следующим образом:
\code
	string RPN(string* tokens, int countOfTokens, string* variables, int countOfVariables)
	{
		for (int i = 0; i < countOfVariables; i++)
		{
			int equal = variables[i].find("=");
			string name = variables[i].substr(0, equal);
			string value = variables[i].substr(equal + 1);

			for (int i = 0; i < countOfTokens; i++)
			{
				if (tokens[i] == name)
					tokens[i] = value;
			}
		}

		string* queue = new string[countOfTokens];
		Sign* stackOfSigns = new Sign[countOfTokens];
		int queueCounter = 0, stackCounter = 0;
		bool UnaryMinus = false;
		bool OpenBracket = false;
		for (int i = 0; i < countOfTokens; i++)
		{
			if (tokens[i] == "+")
			{
				Sign plus("+", 2);
				if (Count(stackOfSigns) != 0)
				{
					while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > plus.weight)
					{
						Sign sign = PopBack(stackOfSigns, stackCounter);
						PushBack(queue, sign.value, queueCounter);
					}
				}
				PushBack(stackOfSigns, plus, stackCounter);
			}
			else if (tokens[i] == "-")
			{
				Sign minus("-", 2);
				if (Count(stackOfSigns) != 0)
				{
					while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > minus.weight)
					{
						Sign sign = PopBack(stackOfSigns, stackCounter);
						PushBack(queue, sign.value, queueCounter);
					}
				}
				PushBack(stackOfSigns, minus, stackCounter);
				if (OpenBracket == true)
					UnaryMinus = true;
			}

			else if (tokens[i] == "/")
			{
				Sign slash("/", 3);
				if (Count(stackOfSigns) != 0)
				{
					while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > slash.weight)
					{
						Sign sign = PopBack(stackOfSigns, stackCounter);
						PushBack(queue, sign.value, queueCounter);
					}
				}
				PushBack(stackOfSigns, slash, stackCounter);
			}

			else if (tokens[i] == "*")
			{
				Sign star("*", 3);
				if (Count(stackOfSigns) != 0)
				{
					while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > star.weight)
					{
						Sign sign = PopBack(stackOfSigns, stackCounter);
						PushBack(queue, sign.value, queueCounter);
					}
				}
				PushBack(stackOfSigns, star, stackCounter);
			}

			else if (tokens[i] == "(")
			{
				Sign bracket("(", 1);
				PushBack(stackOfSigns, bracket, stackCounter);
				OpenBracket = true;
			}

			else if (tokens[i] == ")")
			{
				while (stackOfSigns[Count(stackOfSigns) - 1].value != "(")
				{
					if (Count(stackOfSigns) == 0)
						return "Input Error";
					Sign sign = PopBack(stackOfSigns, stackCounter);
					PushBack(queue, sign.value, queueCounter);
				}
				PopBack(stackOfSigns, stackCounter);
			}

			else
			{
				OpenBracket = false;
				if (UnaryMinus == true)
				{
					tokens[i] = "-" + tokens[i];
					PopBack(stackOfSigns, stackCounter);
				}
				PushBack(queue, tokens[i], queueCounter);
				UnaryMinus = false;
			}
		}
		while (Count(stackOfSigns) != 0)
		{
			Sign sign = PopBack(stackOfSigns, stackCounter);
			if (sign.value == "(")
				return "Input Error";
			PushBack(queue, sign.value, queueCounter);
		}

		string* stackOfnumbers = new string[queueCounter];
		int finalCounter = 0;
		for (int i = 0; i < queueCounter; i++)
		{
			try
			{
				if (queue[i] == "+")
				{
					string SecondNumber = PopBack(stackOfnumbers, finalCounter);
					string FirstNumber = PopBack(stackOfnumbers, finalCounter);
					PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "+"), finalCounter);
				}
				else if (queue[i] == "-")
				{
					string SecondNumber = PopBack(stackOfnumbers, finalCounter);
					string FirstNumber = PopBack(stackOfnumbers, finalCounter);
					PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "-"), finalCounter);
				}

				else if (queue[i] == "/")
				{
					string SecondNumber = PopBack(stackOfnumbers, finalCounter);
					string FirstNumber = PopBack(stackOfnumbers, finalCounter);
					PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "/"), finalCounter);
				}

				else if (queue[i] == "*")
				{
					string SecondNumber = PopBack(stackOfnumbers, finalCounter);
					string FirstNumber = PopBack(stackOfnumbers, finalCounter);
					PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "*"), finalCounter);
				}

				else
				{
					PushBack(stackOfnumbers, queue[i], finalCounter);
				}
			}
			catch (const std::exception&)
			{
				return "Input Error";
			}
		}

		return *stackOfnumbers;
	}
	\endcode
\authors Tereshin D.D
 */
string RPN(string* tokens, int countOfTokens, string* variables, int countOfVariables)
{
	for (int i = 0; i < countOfVariables; i++)
	{
		int equal = variables[i].find("=");
		string name = variables[i].substr(0, equal);
		string value = variables[i].substr(equal + 1);

		for (int i = 0; i < countOfTokens; i++)
		{
			if (tokens[i] == name)
				tokens[i] = value;
		}
	}

	string* queue = new string[countOfTokens];
	Sign* stackOfSigns = new Sign[countOfTokens];
	int queueCounter = 0, stackCounter = 0;
	bool UnaryMinus = false;
	bool OpenBracket = false;
	for (int i = 0; i < countOfTokens; i++)
	{
		if (tokens[i] == "+")
		{
			Sign plus("+", 2);
			if (Count(stackOfSigns) != 0)
			{
				while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > plus.weight)
				{
					Sign sign = PopBack(stackOfSigns, stackCounter);
					PushBack(queue, sign.value, queueCounter);
				}
			}
			PushBack(stackOfSigns, plus, stackCounter);
		}
		else if (tokens[i] == "-")
		{
			Sign minus("-", 2);
			if (Count(stackOfSigns) != 0)
			{
				while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > minus.weight)
				{
					Sign sign = PopBack(stackOfSigns, stackCounter);
					PushBack(queue, sign.value, queueCounter);
				}
			}
			PushBack(stackOfSigns, minus, stackCounter);
			if (OpenBracket == true)
				UnaryMinus = true;
		}

		else if (tokens[i] == "/")
		{
			Sign slash("/", 3);
			if (Count(stackOfSigns) != 0)
			{
				while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > slash.weight)
				{
					Sign sign = PopBack(stackOfSigns, stackCounter);
					PushBack(queue, sign.value, queueCounter);
				}
			}
			PushBack(stackOfSigns, slash, stackCounter);
		}

		else if (tokens[i] == "*")
		{
			Sign star("*", 3);
			if (Count(stackOfSigns) != 0)
			{
				while (Count(stackOfSigns) != 0 && stackOfSigns[Count(stackOfSigns) - 1].weight > star.weight)
				{
					Sign sign = PopBack(stackOfSigns, stackCounter);
					PushBack(queue, sign.value, queueCounter);
				}
			}
			PushBack(stackOfSigns, star, stackCounter);
		}

		else if (tokens[i] == "(")
		{
			Sign bracket("(", 1);
			PushBack(stackOfSigns, bracket, stackCounter);
			OpenBracket = true;
		}

		else if (tokens[i] == ")")
		{
			while (stackOfSigns[Count(stackOfSigns) - 1].value != "(")
			{
				if (Count(stackOfSigns) == 0)
					return "Input Error";
				Sign sign = PopBack(stackOfSigns, stackCounter);
				PushBack(queue, sign.value, queueCounter);
			}
			PopBack(stackOfSigns, stackCounter);
		}

		else
		{
			OpenBracket = false;
			if (UnaryMinus == true)
			{
				tokens[i] = "-" + tokens[i];
				PopBack(stackOfSigns, stackCounter);
			}
			PushBack(queue, tokens[i], queueCounter);
			UnaryMinus = false;
		}
	}
	while (Count(stackOfSigns) != 0)
	{
		Sign sign = PopBack(stackOfSigns, stackCounter);
		if (sign.value == "(")
			return "Input Error";
		PushBack(queue, sign.value, queueCounter);
	}

	string* stackOfnumbers = new string[queueCounter];
	int finalCounter = 0;
	for (int i = 0; i < queueCounter; i++)
	{
		try
		{
			if (queue[i] == "+")
			{
				string SecondNumber = PopBack(stackOfnumbers, finalCounter);
				string FirstNumber = PopBack(stackOfnumbers, finalCounter);
				PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "+"), finalCounter);
			}
			else if (queue[i] == "-")
			{
				string SecondNumber = PopBack(stackOfnumbers, finalCounter);
				string FirstNumber = PopBack(stackOfnumbers, finalCounter);
				PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "-"), finalCounter);
			}

			else if (queue[i] == "/")
			{
				string SecondNumber = PopBack(stackOfnumbers, finalCounter);
				string FirstNumber = PopBack(stackOfnumbers, finalCounter);
				PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "/"), finalCounter);
			}

			else if (queue[i] == "*")
			{
				string SecondNumber = PopBack(stackOfnumbers, finalCounter);
				string FirstNumber = PopBack(stackOfnumbers, finalCounter);
				PushBack(stackOfnumbers, Calculation(FirstNumber, SecondNumber, "*"), finalCounter);
			}

			else
			{
				PushBack(stackOfnumbers, queue[i], finalCounter);
			}
		}
		catch (const std::exception&)
		{
			return "Input Error";
		}
	}

	return *stackOfnumbers;
}

/**
\brief Функция разбивающая строку на токены
\param expression − строка выражения
\param variables − массив строк переменных
\param countOfVariables − количество строк переменных
\return string - возращаемое значение функции RPN

Код функции выглядит следующим образом:
\code
	string Fragmentation(string expression, string* variables, int countOfVariables)
	{
		string *tokens = new string[expression.length()];
		string number;
		int j = 0;
		for (int i = 0; i < expression.length(); i++)
		{
			switch (expression[i])
			{
			case '+':
				PushBack(tokens, number, j);
				PushBack(tokens, "+", j);
				number.clear();
				break;
			case '-':
				PushBack(tokens, number, j);
				PushBack(tokens, "-", j);
				number.clear();
				break;
			case '/':
				PushBack(tokens, number, j);
				PushBack(tokens, "/", j);
				number.clear();
				break;
			case '*':
				PushBack(tokens,number, j);
				PushBack(tokens, "*", j);
				number.clear();
				break;
			case '(':
				PushBack(tokens, number, j);
				PushBack(tokens, "(", j);
				number.clear();
				break;
			case ')':
				PushBack(tokens, number, j);
				PushBack(tokens, ")", j);
				number.clear();
				break;
			default:
				number += expression[i];
				break;
			}
		}
		PushBack(tokens, number, j);
		return RPN(tokens, j, variables, countOfVariables);
	}
	\endcode
\authors Tereshin D.D
 */
string Fragmentation(string expression, string* variables, int countOfVariables)
{
	string *tokens = new string[expression.length()];
	string number;
	int j = 0;
	for (int i = 0; i < expression.length(); i++)
	{
		switch (expression[i])
		{
		case '+':
			PushBack(tokens, number, j);
			PushBack(tokens, "+", j);
			number.clear();
			break;
		case '-':
			PushBack(tokens, number, j);
			PushBack(tokens, "-", j);
			number.clear();
			break;
		case '/':
			PushBack(tokens, number, j);
			PushBack(tokens, "/", j);
			number.clear();
			break;
		case '*':
			PushBack(tokens,number, j);
			PushBack(tokens, "*", j);
			number.clear();
			break;
		case '(':
			PushBack(tokens, number, j);
			PushBack(tokens, "(", j);
			number.clear();
			break;
		case ')':
			PushBack(tokens, number, j);
			PushBack(tokens, ")", j);
			number.clear();
			break;
		default:
			number += expression[i];
			break;
		}
	}
	PushBack(tokens, number, j);
	return RPN(tokens, j, variables, countOfVariables);
}

/**
\brief Функция парсящая входные строки
\param argc − количество передающихся параметров
\param argv[] − входные строки
\return string - возращаемое значение функции Fragmentation

Код функции выглядит следующим образом:
\code
	string Parsing(int argc, char* argv[])
	{
		string expression = "";
		string *variables = new string[argc];
		int countOfVariables = 0;

		for (int i = 0; i < argc; i++)
		{
			string str = argv[i];
			if (str.find("--expression") != string::npos)
			{
				if (i + 1 < argc)
				{
					string str = argv[i + 1];
					if (str != "--variable")
						expression = argv[i + 1];

				}
			}

			if (str.find("--variable") != string::npos)
			{
				if (i + 1 < argc)
				{
					for (int j = i + 1; j < argc; j++)
					{
						string variable = argv[j];
						if (variable == "--expression")
							break;
						variables[countOfVariables] = variable;
						countOfVariables++;
					}

				}
			}
		}
		if (expression.length() == 0)
			return "Error expression";

		return Fragmentation(expression, variables, countOfVariables);
	}
	\endcode
\authors Tereshin D.D
 */
string Parsing(int argc, char* argv[])
{
	string expression = "";
	string *variables = new string[argc];
	int countOfVariables = 0;

	for (int i = 0; i < argc; i++)
	{
		string str = argv[i];
		if (str.find("--expression") != string::npos)
		{
			if (i + 1 < argc)
			{
				string str = argv[i + 1];
				if (str != "--variable")
					expression = argv[i + 1];

			}
		}

		if (str.find("--variable") != string::npos)
		{
			if (i + 1 < argc)
			{
				for (int j = i + 1; j < argc; j++)
				{
					string variable = argv[j];
					if (variable == "--expression")
						break;
					variables[countOfVariables] = variable;
					countOfVariables++;
				}

			}
		}
	}
	if (expression.length() == 0)
		return "Error expression";

	return Fragmentation(expression, variables, countOfVariables);
}

/**
\brief Основная функция программы
\param argc − количество передающихся параметров
\param argv[] − входные строки
\return int

\code
	int main(int argc, char* argv[])
	{
		cout << "result: " << Parsing(argc, argv) << endl;

		return 0;
	}
	\endcode
\authors Tereshin D.D
 */
int main(int argc, char* argv[])
{
	cout << "result: " << Parsing(argc, argv) << endl;

	return 0;
}
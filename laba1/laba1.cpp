#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional> 

// Вспомогательные функции
bool isFileWithContent(std::ifstream& file);
void ending(int n);
template <typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message);
int getRandomInInterval(int a, int b);
void print(int* arr, int size, const char* message);
void preambDynamic(short choice, std::ifstream& file, int& Rows, int& Colums);
void fill_row(int* arr, int a, int b, int Colums = Colums1);
void fill_row(int* arr, std::istream& stream, int Colums = Colums1);
void fill_matrix(int matrix[Rows1][Colums1], int a, int b);
void fill_matrix(int matrix[Rows1][Colums1], std::istream& stream = std::cin);
void fill_matrix(int** matrix, int Rows, int Colums, std::istream& stream = std::cin);
void fill_matrix(int** matrix, int a, int b, int Rows, int Colums);

// Функции связанные с памятью, выделяемой для массивов
int** memory_allocation(int newRows, int newColums);
void free_memory(int**& matrix, int Rows);


//Менюшки
int mainMenu();
int optionMenu();

const int Rows1 = 5;
const int Colums1 = 5;

int main()
{
	SetConsoleOutputCP(1251);

	short mainChoice;
	do
	{
		mainChoice = mainMenu();
		if (mainChoice != 3)
		{
			std::cout << "\nВыбран пункт меню: '" << mainChoice << "'\n";
			short choice;
			do
			{
				choice = optionMenu();
				if (choice != 4)
				{
					std::cout << "\nВыбран пункт меню: '" << choice << "'\n";


					switch (mainChoice)
					{
					case 1:
					{
						int size;
						std::ifstream file("data.txt");
						int matrix[Rows1][Colums1];

						switch (choice)
						{
						case 1:
						{
							std::cout << "Количество столбцов = " << Colums1 << ' ' << "Количество строк = " << Rows1 << '\n';

							break;
						}
						case 2:
						{

							break;
						}
						default:
						{
							std::cout << "Количество столбцов = " << Colums1 << ' ' << "Количество строк = " << Rows1 << '\n';

						}
						}
						break;
					}
					default:
					{
						int size;
						std::ifstream file("data.txt");
						int Rows = 0, Colums = 0;

						preambDynamic(choice, file, Rows, Colums);

						switch (choice)
						{
						case 1:
						{

							break;
						}
						case 2:
						{

							break;
						}
						default:
						{

						}
						}
					}
					}
				}
			} while (choice != 3);
			std::cout << "\nВыбран пункт меню: '" << choice << "'\n";

		}
	} while (mainChoice != 3);

}

int mainMenu()
{
	std::cout << "\n--------------\n";
	std::cout << "\nМеню";
	std::cout << "\n1. Найти номер первого из столбцов, не содержащих ни одного отрицательного элемента\n";
	std::cout << "2. Упорядочить строки матрицы по возрастанию количества двузначных элементов в каждой строке. \n";
	std::cout << "3. Завершить работу" << '\n';
	std::cout << "\n--------------\n";

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 3;
		};
	int choice = 0;
	Read_and_check(choice, std::cin, Lambda, "\n-> ");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int optionMenu()
{
	std::cout << "\n--------------\n";
	std::cout << "\n1. Ввод чисел с клавиатуры" << '\n';
	std::cout << "2. Ввод чисел из файла" << '\n';
	std::cout << "3. Случайный набор чисел" << '\n';
	std::cout << "4. Выйти в главное меню" << '\n';
	std::cout << "\n--------------\n";

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 4;
		};
	int choice = 0;
	Read_and_check(choice, std::cin, Lambda, "\n-> ");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

bool isFileWithContent(std::ifstream& file)
{
	int result = 1;
	if (!file)
	{
		result = -1;
		std::cout << "\nФайл не найден!\n";
	}
	else
		if (file.peek() == EOF) //==-1
		{
			result = 0;
			std::cout << "\nФайл пустой!\n";
		}

	return result == 1;
}

void ending(int n)
{
	std::cout << "\nВведите " << n << " элемент";
	if (n < 21 && n>10)
		std::cout << "ов: ";
	else
	{
		switch (n % 10)
		{
		case 1:
			std::cout << ": ";
			break;
		case 2:
		case 3:
		case 4:
			std::cout << "а: ";
			break;
		default:
			std::cout << "ов: ";
			break;

		}
	}
}

int getRandomInInterval(int a, int b)
{
	return a + rand() % (b - a + 1);
}


int** memory_allocation(int newRows, int newColums) {
	int** matrix = new int* [newRows];
	for (int i{ 0 }; i < newRows; ++i)
		matrix[i] = new int[newColums];
	return matrix;
}

void free_memory(int**& matrix, int Rows)
{
	for (int i{ 0 }; i < Rows; ++i)
		delete[]matrix[i];
	delete[]matrix;
}

void print(int* arr, int size, const char* message)
{
	std::cout << message;
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}


void preambDynamic(short choice, std::ifstream& file, int& Rows, int& Colums)
{
	switch (choice)
	{
	case 1:
	{
		Read_and_check(Rows, std::cin, [](int x) {return x > 0; }, "Введите количество строк квадратной матрицы\n->");
		Read_and_check(Colums, std::cin, [Rows](int x) {return x > 0 && Rows == x; }, "Введите количество столбцов квадратной матрицы\n->");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		break;
	}
	case 2:
	{
		if (isFileWithContent(file))
			file >> Rows >> Colums;
		break;
	}
	default:
	{
		std::cout << "\nВведите количество случайных слагаемых: ";
		Read_and_check(Rows, std::cin, [](int x) {return x > 0; }, "Введите количество случайных строк\n->");
		Read_and_check(Colums, std::cin, [Rows](int x) {return x > 0 && Rows == x; }, "Введите количество случайных столбцов\n->");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	}
}
void fill_row(int* arr, std::istream& stream, int Colums)
{
	for (int i{ 0 }; i < Colums; ++i)
		stream >> arr[i];
}

void fill_matrix(int matrix[Rows1][Colums1], int a, int b)
{
	for (int i{ 0 }; i < Rows1; ++i)
		fill_row(matrix[i], a, b);
}

void fill_matrix(int matrix[Rows1][Colums1], std::istream& stream)
{
	for (int i{ 0 }; i < Rows1; ++i)
		fill_row(matrix[i], stream);
}

void fill_matrix(int** matrix, int Rows, int Colums, std::istream& stream) {
	for (int i{ 0 }; i < Rows; ++i)
		fill_row(matrix[i], stream, Colums);
}

void fill_matrix(int** matrix, int a, int b, int Rows, int Colums) {
	for (int i{ 0 }; i < Rows; ++i)
		fill_row(matrix[i], a, b, Colums);
}


template<typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message)
{
	std::cout << message;
	while (!(stream >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!\n";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message;
	}
}
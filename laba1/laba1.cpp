#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional>
#include<iomanip>

// Константы
const int Rows1 = 5;
const int Colums1 = 5;

// Вспомогательные функции
bool isFileWithContent(std::ifstream& file);
template <typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message);
int getRandomInInterval(int a, int b);
void preambDynamic(short choice, std::ifstream& file, int& Rows, int& Colums);

// Заполнение матрицы
void fill_row(int* arr, int a, int b, int Colums);
void fill_row(int* arr, std::istream& stream, int Colums);
void fill_matrix(int matrix[Rows1][Colums1], int a, int b);
void fill_matrix(int matrix[Rows1][Colums1], std::istream& stream);
void fill_matrix(int** matrix, int Rows, int Colums, std::istream& stream);
void fill_matrix(int** matrix, int a, int b, int Rows, int Colums);

// Вывод матрицы
void print_row(int* arr, int Colums);
void print_matrix(int** matrix, int Rows, int Colums);
void print_matrix(int arr[Rows1][Colums1]);

// Функции связанные с памятью, выделяемой для массивов
int** memory_allocation(int newRows, int newColums);
void free_memory(int**& matrix, int Rows);

// Функции к task1
void transposition(int matrix[Rows1][Colums1]);
void task1(int matrix[Rows1][Colums1]);
bool isAllPositive(int* beginrow);

// Функции к task2
int countDoubleDigits(int* arr, int Colums);
void swap_rows(int* a, int* b, int Colums);
void sort_matrix(int** matrix, int Rows, int Colums);


// Менюшки
int mainMenu();
int optionMenu();


int main()
{
	SetConsoleOutputCP(1251);
	srand(GetTickCount());

	short mainChoice;
	do
	{
		mainChoice = mainMenu();
		if (mainChoice != 3)
		{
			std::cout << "\nВыбран пункт меню: '" << mainChoice << "'\n\n";
			short choice;
			do
			{
				choice = optionMenu();
				if (choice != 4)
				{
					std::cout << "\nВыбран пункт меню: '" << choice << "'\n\n";


					switch (mainChoice)
					{
					case 1:
					{
						int matrix[Rows1][Colums1];

						switch (choice)
						{
						case 1:
						{
							std::cout << "Количество столбцов = " << Colums1 << ' ' << "Количество строк = " << Rows1 << '\n';
							std::cout << "\nВведите квадратную матрицу:\n";
							fill_matrix(matrix, std::cin);
							break;
						}
						case 2:
						{
							std::ifstream file("matrix_static.txt");
							if (isFileWithContent(file))
							{
								fill_matrix(matrix, file);
								std::cout << "\nКвадратная матрица:\n";
								print_matrix(matrix);
							}
							break;

						}
						default:
						{
							std::cout << "Количество столбцов = " << Colums1 << ' ' << "Количество строк = " << Rows1 << '\n';
							int a, b;
							std::cout << "\nВведите диапазон рандома(от A до B): ";
							Read_and_check(a, std::cin, [](int x) {return true; }, "\n-> ");
							Read_and_check(b, std::cin, [a](int x) {return x > a; }, "");
							fill_matrix(matrix, a, b);
							std::cout << "\nКвадратная матрица:\n";
							print_matrix(matrix);
						}
						}
						task1(matrix);
						break;
					}
					default:
					{
						std::ifstream file("matrix_dynamic.txt");
						int Rows = 0, Colums = 0;

						preambDynamic(choice, file, Rows, Colums);
						int** matrix = memory_allocation(Rows, Colums);

						switch (choice)
						{
						case 1:
						{
							std::cout << "\nВведите квадратную матрицу:\n";
							fill_matrix(matrix, Rows, Colums, std::cin);
							break;
						}
						case 2:
						{
							fill_matrix(matrix, Rows, Colums, file);
							std::cout << "\nКвадратная матрица:\n";
							print_matrix(matrix, Rows, Colums);
							break;
						}
						default:
						{
							int a, b;
							std::cout << "\nВведите диапазон рандома(от A до B): ";
							Read_and_check(a, std::cin, [](int x) {return true; }, "\n-> ");
							Read_and_check(b, std::cin, [a](int x) {return x > a; }, "");
							fill_matrix(matrix, a, b, Rows, Colums);
							std::cout << "\nКвадратная матрица:\n";
							print_matrix(matrix, Rows, Colums);
						}
						}
						sort_matrix(matrix, Rows,Colums);
						std::cout << "\nПреобразованная матрица: " << '\n';
						print_matrix(matrix, Rows, Colums);
						free_memory(matrix, Rows);
					}
					}
				}
			} while (choice != 4);
			std::cout << "\nВыбран пункт меню: '" << choice << "'\n\n";

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
	std::cout << "\nВыберите вариант ввода\n";
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

void preambDynamic(short choice, std::ifstream& file, int& Rows, int& Colums)
{
	switch (choice)
	{
	case 1:
	{
		Read_and_check(Rows, std::cin, [](int x) {return x > 0; }, "Введите количество строк квадратной матрицы:\n->");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		Read_and_check(Colums, std::cin, [Rows](int x) {return x > 0 && Rows == x; }, "Введите количество столбцов квадратной матрицы:\n->");
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
		Read_and_check(Rows, std::cin, [](int x) {return x > 0; }, "Введите количество случайных строк:\n->");
		Read_and_check(Colums, std::cin, [Rows](int x) {return x > 0 && Rows == x; }, "Введите количество случайных столбцов:\n->");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	}
}

void fill_row(int* arr, int a, int b, int Colums)
{
	for (int i{ 0 }; i < Colums; ++i)
		arr[i] = getRandomInInterval(a,b);
}

void fill_row(int* arr, std::istream& stream, int Colums)
{
	for (int i{ 0 }; i < Colums; ++i)
		stream >> arr[i];
}

void fill_matrix(int matrix[Rows1][Colums1], int a, int b)
{
	for (int i{ 0 }; i < Rows1; ++i)
		fill_row(matrix[i], a, b, Colums1);
}

void fill_matrix(int matrix[Rows1][Colums1], std::istream& stream)
{
	for (int i{ 0 }; i < Rows1; ++i)
		fill_row(matrix[i], stream, Colums1);
}

void fill_matrix(int** matrix, int Rows, int Colums, std::istream& stream) {
	for (int i{ 0 }; i < Rows; ++i)
		fill_row(matrix[i], stream, Colums);
}

void fill_matrix(int** matrix, int a, int b, int Rows, int Colums) {
	for (int i{ 0 }; i < Rows; ++i)
		fill_row(matrix[i], a, b, Colums);
}

void print_row(int* arr, int Colums) {
	for (int i{ 0 }; i < Colums; ++i)
		std::cout << std::setw(4) << arr[i];
	std::cout << '\n';
}

void print_matrix(int** matrix, int Rows, int Colums) {
	std::cout << '\n';
	for (int i{ 0 }; i < Rows; ++i)
		print_row(matrix[i], Colums);
}

void print_matrix(int arr[Rows1][Colums1]) {
	std::cout << '\n';
	for (int i{ 0 }; i < Rows1; ++i)
		print_row(arr[i], Colums1);
}

bool isAllPositive(int* beginrow)
{
	bool result = true;
	int* ptr = beginrow;

	while (result && ptr < beginrow + Colums1)
	{
		if (*ptr < 0)
			result = false;
		else
			++ptr;
	}
	return result;
}

void transposition(int matrix[Rows1][Colums1])
{
	for (int i = 0; i < Rows1 - 1; ++i)
		for (int j = i + 1; j < Colums1; ++j)
			std::swap(matrix[i][j], matrix[j][i]);
}

void task1(int matrix[Rows1][Colums1])
{
	transposition(matrix);
	int* ptrrows = matrix[0];
	bool isFind = true;
	while (ptrrows < matrix[0] + Colums1 * Rows1 && isFind)
	{
		if (isAllPositive(ptrrows))
		{
			isFind = false;
			std::cout << "\nНомер столбца, не содержащий отрицательных элементов: "<< (ptrrows - matrix[0]) / Colums1 + 1 << '\n';
		}
		ptrrows += Colums1;
	}
	if (isFind)
	{
		std::cout << "В матрице нет столбцов без отрицательных элементов!\n";
	}
	transposition(matrix);
}

int countDoubleDigits(int* arr,int Colums)
{
	int result = 0;
	for (int i = 0; i < Colums; ++i)
	{
		if (abs(arr[i]) >= 10 && abs(arr[i]) <= 99)
			++result;
	}
	return result;
}

void swap_rows(int* a, int* b,int Colums)
{
	for (int i = 0; i < Colums; ++i)
		std::swap(a[i], b[i]);
}

void sort_matrix(int** matrix,int Rows,int Colums)
{
	int* tmp = new int [Rows];
	
	for (int i = 0; i < Rows; ++i)
		tmp[i] = countDoubleDigits(matrix[i],Colums);
	for (int j = Rows; j >= 2; j--)
		for (int i = 0; i < j - 1; ++i)
			if (tmp[i] > tmp[i + 1])
			{
				swap_rows(matrix[i], matrix[i + 1],Colums);
				std::swap(tmp[i], tmp[i + 1]);
			}
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
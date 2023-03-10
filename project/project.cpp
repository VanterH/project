#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <iomanip>
using namespace std;

template<typename T>
class List {
public:
	List();
	~List();
	void push_back(T data);
	int GetSize() { return Size; }
	T& operator[](const int index);
	void delete_elems(int index);

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T>* head;
};

template<typename T>
List<T>::List() {
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List() {
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}

		current->pNext = new Node<T>(data);
	}
	Size++;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::delete_elems(int index)
{
	Node<T>* temp = this->head;
	Node<T>* prev = NULL;
	int i = 0;
	if (index == Size - 3)
	{
		while (i < index)
		{
			temp = temp->pNext;
			prev = temp->pNext;
			i++;
		}
		prev->pNext = temp->pNext;
	}
	else if (index == 0)
	{
		while (i < 5)
		{
			head = head->pNext;
			i++;
		}
	}
	else
	{
		while (i < index + 4)
		{
			temp = temp->pNext;
			if (i + 3 == index)
			{
				prev = temp->pNext;
			}
			i++;
		}
		prev->pNext = temp->pNext;
	}
	Size -= 5;
	free(temp);
}

class Matrix
{
public:
	Matrix();
	~Matrix();
	void fillMat(int data, int i, int j);
	void printMat();
	int getSizeOfMat() { return size; }
	int getSizeOfCols() { return n; }
	int getSizeOfRow() { return m; }
	void minmax();

private:
	int n;
	int m;
	int** arr;
	int size;
};

Matrix::Matrix()
{

	while (n < 3 || m < 3)
	{
		cout << "Количество строк и столбцов должно быть не меньше трёх\n";
		cout << "Введите количество строк: ";
		cin >> n;
		cout << "Введите количество столбцов: ";
		cin >> m;
	}

	arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}

	size = n * m;
}

Matrix::~Matrix()
{
	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void Matrix::fillMat(int data, int i, int j)
{
	arr[i][j] = data;
}

void Matrix::printMat()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(4) << arr[i][j];
		}
		cout << endl;
	}

	//system("pause");
}

void Matrix::minmax()
{
	int min = INT_MAX;
	int max = INT_MIN;
	int min_index_rows, min_index_cols, max_index_rows, max_index_cols;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (arr[i][j] > max)
			{
				max = arr[i][j];
				max_index_rows = i;
				max_index_cols = j;
			}
			if (arr[i][j] < min)
			{
				min = arr[i][j];
				min_index_rows = i;
				min_index_cols = j;
			}
		}
	}
	arr[min_index_rows][min_index_cols] = max;
	arr[max_index_rows][max_index_cols] = min;
}


void students() {
	setlocale(LC_ALL, "ru");

	List<string> lst;

	int ans;

	cout << "Выберите формат ввода:\n1.Через файл.\n2.Через консоль.\n";
	ans = 0;
	while (ans != 1 || ans != 2)
	{
		cin >> ans;

		if (ans == 1)
		{
			string s1 = "0", s2 = "0", s3 = "0", s4 = "0", s5 = "0";
			fstream in;
			in.open("in.txt", ios_base::in);
			while (in >> s1 >> s2 >> s3 >> s4 >> s5)
			{
				lst.push_back(s1);
				lst.push_back(s2);
				lst.push_back(s3);
				lst.push_back(s4);
				lst.push_back(s5);
				if (s5 != "2" && s5 != "3" && s5 != "4" && s5 != "5")
				{
					cout << "Error";
					return;
				}
			}
			break;
		}
		else if (ans == 2)
		{
			cout << "Для выхода введите 0\n";
			while (true)
			{
				string s;
				cin >> s;
				if (s == "0")
				{
					break;
				}
				else
				{
					lst.push_back(s);
				}
			}
			if (lst.GetSize() % 5 != 0)
			{
				cout << "Неправильно введённые данные.";
				return;
			}
		}
	}

	cout << "\nВведённый вами список:\n";
	for (int i = 0; i < lst.GetSize(); i++)
	{
		if (i % 5 == 0) { cout << endl; }
		cout << lst[i] << " ";
	}

	vector<int> index;

	for (int i = 0; i < lst.GetSize() - 2; i++)
	{
		if (lst[i] == "2" && lst[i + 1] == "2" && lst[i + 2] == "2")
		{
			index.push_back(i - 2);
			i += 2;
		}
	}

	cout << endl;
	int cnt = 0;
	int lenght = 0;
	while (cnt < index.size())
	{

		lst.delete_elems(index[cnt] - lenght);
		lenght += 5;
		cnt++;
	}
	cout << "Список студентов без трёх задолжностей:\n";
	for (int i = 0; i < lst.GetSize(); i++)
	{
		if (i % 5 == 0) { cout << endl; }
		cout << lst[i] << " ";
	}
}

void mat() {
	Matrix mat;
	string ans;

	cout << "Выберите формат ввода:\n1.Через файл.\n2.Через консоль.\n";
	while (ans != "1" || ans != "2")
	{
		cin >> ans;
		if (ans == "1")
		{
			int data, i = 0, j = 0;
			ifstream in("in_mat.txt");
			int dat;
			while (in >> dat)
			{
				if (j == mat.getSizeOfRow())
				{
					i++;
					j = 0;
				}
				//data = stoi(dat);
				cout <<  "M" << i << " " << j << " " << dat << endl;
				mat.fillMat(dat, i, j);
				j++;			
			}
			break;
		}
		if (ans == "2")
		{
			int data;
			for (int i = 0; i < mat.getSizeOfCols(); i++)
			{
				for (int j = 0; j < mat.getSizeOfRow(); j++)
				{
					cout << "M[" << i << "][" << j << "] = ";
					cin >> data;
					mat.fillMat(data, i, j);
				}
			}
			break;
		}
	}

	cout << "Исходная матрица: \n";
	mat.printMat();
	mat.minmax();
	cout << "Матрица с заменой: \n";
	mat.printMat();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int in = 0;

	cout << "1.Удалить студентов с тремя задолжностями.\n2.Поменять местами минимальный и максимальный элементы матрицы.";
	cin >> in;
	switch (in)
	{
	case (1):
		students();
		break;
	case (2):
		mat();
		break;
	}
}

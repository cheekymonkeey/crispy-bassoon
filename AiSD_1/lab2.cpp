#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;
template <typename T>
class DynamicArray {
private:
	T* array; // указатель на массив
	int capacity; // текущая ёмкость массива
	int current_size; // текущий размер массива

public:
	// Конструктор
	DynamicArray() {
		capacity = 10; // начальная ёмкость массива
		array = new T[capacity];
		current_size = 0;
	}

	// Деструктор
	~DynamicArray() {
		delete[] array;
	}

	// Метод для получения текущего размера массива
	int size() const {
		return current_size;
	}

	// Метод для установки значения по индексу
	void set(int index, const T& value) {
		if (index >= 0 && index < current_size) {
			array[index] = value;
		}
	}

	// Метод для получения значения по индексу
	T get(int index) const {
		if (index >= 0 && index < current_size) {
			return array[index];
		}
		// Можно также вернуть значение по умолчанию или сгенерировать исключение в случае некорректного индекса
	}

	// Метод для удаления элемента по индексу
	void remove(int index) {
		if (index >= 0 && index < current_size) {
			for (int i = index; i < current_size - 1; i++) {
				array[i] = array[i + 1];
			}
			current_size--;
		}
	}

	// Метод для добавления элемента в конец массива
	void add(const T& value) {
		if (current_size >= capacity) {
			// Увеличиваем ёмкость массива в два раза при необходимости
			capacity *= 2;
			T* new_array = new T[capacity];
			for (int i = 0; i < current_size; i++) {
				new_array[i] = array[i];
			}
			delete[] array;
			array = new_array;
		}
		array[current_size] = value;
		current_size++;
	}
};

// Шаблонный класс узел списка
template<typename T>
class Node {
public:
	T data; // Данные узла
	Node* prev; // Указатель на предыдущий узел
	Node* next; // Указатель на следующий узел

	// Конструктор
	Node(T value) {
		data = value;
		prev = nullptr;
		next = nullptr;
	}
};

// Шаблонный класс двусвязного списка
template<typename T>
class DoublyLinkedList {
private:
	Node<T>* head; // Указатель на голову списка
	int size; // Размер списка

public:
	// Конструктор
	DoublyLinkedList() {
		head = nullptr;
		size = 0;
	}

	// Добавление элемента в конец списка
	void add(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<T>* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
			newNode->prev = current;
		}
		size++;
	}

	// Удаление элемента из списка
	void remove(T value) {
		if (head == nullptr)
			return;

		Node<T>* current = head;
		// Проверка, является ли элемент головным
		if (current->data == value) {
			// Переназначаем голову списка
			head = current->next;
			if (head != nullptr)
				head->prev = nullptr;
			delete current;
			size--;
			return;
		}

		// Поиск элемента для удаления
		while (current->next != nullptr) {
			current = current->next;
			if (current->data == value) {
				// Если элемент найден, то связываем соседние узлы
				current->prev->next = current->next;
				if (current->next != nullptr)
					current->next->prev = current->prev;
				delete current;
				size--;
				return;
			}
		}
	}

	// Замена значения элемента на новое значение
	void replace(T oldValue, T newValue) {
		Node<T>* current = head;
		while (current != nullptr) {
			if (current->data == oldValue) {
				current->data = newValue;
				return;
			}
			current = current->next;
		}
	}

	// Вывод элемента списка по индексу
	void print(int index) {
		if (index < 0 || index >= size) {
			cout << "Некорректный индекс" << endl;
			return;
		}

		Node<T>* current = head;
		int i = 0;
		while (i < index) {
			current = current->next;
			i++;
		}
		cout << current->data << endl;
	}

	// Получение размера списка
	int getSize() {
		return size;
	}

	// Деструктор
	~DoublyLinkedList() {
		Node<T>* current = head;
		Node<T>* nextNode;
		while (current != nullptr) {
			nextNode = current->next;
			delete current;
			current = nextNode;
		}
	}
};

void DynArr(int a) {
	if (a == 1) {
		DynamicArray<int> arr;
		while (true) {
			cout << "Выберите метод, который хотите задействовать(add - 1, get - 2, size - 3, remove - 4, set - 5): ";
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Введите элемент: ";
				int a;
				cin >> a;
				arr.add(a);
				cout << endl << "Вы успешно добавили элемент в конец списка.";
				break;
			}
			case 2: {
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				cout << "Элемент под индексом " << a << ": " << arr.get(a) << endl;
				break;
			}
			case 3: {
				cout << "Текущий размер массива: " << arr.size() << endl;
				break;
			}
			case 4: {
				int a;
				cout << "Выберите индекс элемента, который бы вы хотели удалить: ";
				cin >> a;
				arr.remove(a);
				cout << endl << "Вы успешно удалили элемент: " << arr.get(a) << " под индексом: " << a << endl;
				break;
			}
			case 5: {
				int a;
				int b;
				cout << "Введите индекс элемента, которое вы хотите заменить: ";
				cin >> a;
				cout << endl << "Введите новый элемент: ";
				cin >> b;
				arr.set(a, b);
				cout << "Вы успешно заменили элемент под индексом " << a << " на элемент " << b << endl;
				break;
			}
			}
			if (choice == 0) {
				break;
			}
		}
	}
	if (a == 2) {
		DynamicArray<char> arr;
		while (true) {
			cout << "Выберите метод, который хотите задействовать(add - 1, get - 2, size - 3, remove - 4, set - 5): ";
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Введите элемент: ";
				int a;
				cin >> a;
				arr.add(a);
				cout << endl << "Вы успешно добавили элемент в конец списка.";
				break;
			}
			case 2: {
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				cout << "Элемент под индексом " << a << ": " << arr.get(a) << endl;
				break;
			}
			case 3: {
				cout << "Текущий размер массива: " << arr.size() << endl;
				break;
			}
			case 4: {
				int a;
				cout << "Выберите индекс элемента, который бы вы хотели удалить: ";
				cin >> a;
				arr.remove(a);
				cout << endl << "Вы успешно удалили элемент: " << arr.get(a) << " под индексом: " << a << endl;
				break;
			}
			case 5: {
				int a;
				int b;
				cout << "Введите индекс элемента, которое вы хотите заменить: ";
				cin >> a;
				cout << endl << "Введите новый элемент: ";
				cin >> b;
				arr.set(a, b);
				cout << "Вы успешно заменили элемент под индексом " << a << " на элемент " << b << endl;
				break;
			}
			}
			if (choice == 0) {
				break;
			}
		}
	}
	else {
		DynamicArray<double> arr;
		while (true) {
			cout << "Выберите метод, который хотите задействовать(add - 1, get - 2, size - 3, remove - 4, set - 5): ";
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Введите элемент: ";
				int a;
				cin >> a;
				arr.add(a);
				cout << endl << "Вы успешно добавили элемент в конец списка.";
				break;
			}
			case 2: {
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				cout << "Элемент под индексом " << a << ": " << arr.get(a) << endl;
				break;
			}
			case 3: {
				cout << "Текущий размер массива: " << arr.size() << endl;
				break;
			}
			case 4: {
				int a;
				cout << "Выберите индекс элемента, который бы вы хотели удалить: ";
				cin >> a;
				arr.remove(a);
				cout << endl << "Вы успешно удалили элемент: " << arr.get(a) << " под индексом: " << a << endl;
				break;
			}
			case 5: {
				int a;
				int b;
				cout << "Введите индекс элемента, которое вы хотите заменить: ";
				cin >> a;
				cout << endl << "Введите новый элемент: ";
				cin >> b;
				arr.set(a, b);
				cout << "Вы успешно заменили элемент под индексом " << a << " на элемент " << b << endl;
				break;
			}
			}
			if (choice == 0) {
				break;
			}
		}
	}
	return;

}
void DouLinked(int a) {
	if (a == 1) {
		DoublyLinkedList<int> list;
		while (true) {
			cout << "Выберите, что будем делать (add - 1 remove - 2 replace - 3 print - 4 size - 5): ";
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Введите элемент: ";
				int a;
				cin >> a;
				list.add(a);
				cout << "Вы успешно добавили элемент." << endl;
				break;
			}
			case 2: {
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				list.remove(a);
				cout << "Вы успешно удалили элемент под индексом " << a << endl;
				break;
			}
			case 3: {
				cout << "Введите индекс элемента, который вы хотите заменить: ";
				int a;
				int b;
				cin >> a;
				cout << endl << "Введите элемент, который вы хотите добавить на место выбранного: ";
				cin >> b;
				list.replace(a, b);
				cout << endl << "Вы успешно заменили элемент под индексом: " << a << "На элемент " << b;
				break;
			}
			case 4: {
				cout << "Введите индекс элемента, который вы хотите получить: ";
				int a;
				cin >> a;
				cout << endl << "Элемент под индексом " << a << " : ";
				list.print(a);
				cout << endl;
				break;
			}
			case 5: {
				cout << "Текущий размер: ";
				list.getSize();
				cout << endl;
				break;
			}
			}
			if (choice == 0) {
				break;
			}
		}
	}
	if (a == 2) {
		DoublyLinkedList<char> list;
		while (true) {
			cout << "Выберите, что будем делать (add - 1 remove - 2 replace - 3 print - 4 size - 5): ";
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Введите элемент: ";
				int a;
				cin >> a;
				list.add(a);
				cout << "Вы успешно добавили элемент." << endl;
				break;
			}
			case 2: {
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				list.remove(a);
				cout << "Вы успешно удалили элемент под индексом " << a << endl;
				break;
			}
			case 3: {
				cout << "Введите индекс элемента, который вы хотите заменить: ";
				int a;
				int b;
				cin >> a;
				cout << endl << "Введите элемент, который вы хотите добавить на место выбранного: ";
				cin >> b;
				list.replace(a, b);
				cout << endl << "Вы успешно заменили элемент под индексом: " << a << "На элемент " << b;
				break;
			}
			case 4: {
				cout << "Введите индекс элемента, который вы хотите получить: ";
				int a;
				cin >> a;
				cout << endl << "Элемент под индексом " << a << " : ";
				list.print(a);
				cout << endl;
				break;
			}
			case 5: {
				cout << "Текущий размер: ";
				list.getSize();
				cout << endl;
				break;
			}
			}
			if (choice == 0) {
				break;
			}
		}
	}
	if (a == 3) {
		DoublyLinkedList<double> list;
		while (true) {
			cout << "Выберите, что будем делать (add - 1 remove - 2 replace - 3 print - 4 size - 5): ";
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				cout << "Введите элемент: ";
				int a;
				cin >> a;
				list.add(a);
				cout << "Вы успешно добавили элемент." << endl;
				break;
			}
			case 2: {
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				list.remove(a);
				cout << "Вы успешно удалили элемент под индексом " << a << endl;
				break;
			}
			case 3: {
				cout << "Введите индекс элемента, который вы хотите заменить: ";
				int a;
				int b;
				cin >> a;
				cout << endl << "Введите элемент, который вы хотите добавить на место выбранного: ";
				cin >> b;
				list.replace(a, b);
				cout << endl << "Вы успешно заменили элемент под индексом: " << a << "На элемент " << b;
				break;
			}
			case 4: {
				cout << "Введите индекс элемента, который вы хотите получить: ";
				int a;
				cin >> a;
				cout << endl << "Элемент под индексом " << a << " : ";
				list.print(a);
				cout << endl;
				break;
			}
			case 5: {
				cout << "Текущий размер: ";
				list.getSize();
				cout << endl;
				break;
			}
			}
			if (choice == 0) {
				break;
			}
		}
	}
}
// Стек
class MyStack {
private:
	double* data;
	int capacity;
	int top;

public:
	MyStack(int size) {
		capacity = size;
		data = new double[capacity];
		top = -1;
	}

	~MyStack() {
		delete[] data;
	}

	void push(double item) {
		if (isFull()) {
			std::cout << "Стек переполнен" << std::endl;
			return;
		}
		data[++top] = item;
	}

	double pop() {
		if (isEmpty()) {
			std::cout << "Стек пуст" << std::endl;
			return 0;
		}
		return data[top--];
	}

	double peek() {
		if (isEmpty()) {
			std::cout << "Стек пуст" << std::endl;
			return 0;
		}
		return data[top];
	}

	bool isEmpty() {
		return top == -1;
	}

	bool isFull() {
		return top == capacity - 1;
	}
};

int precedence(char op) {
	if (op == '^') return 3;
	if (op == '*' || op == '/') return 2;
	if (op == '+' || op == '-') return 1;
	return 0;
}

double applyOperator(char op, double b, double a) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	case '^': return std::pow(a, b);
	default: return 0;
	}
}
int evaluateExpression() {
	std::string expression;
	std::cout << "Введите выражение: ";
	std::getline(std::cin, expression);

	MyStack operators(expression.length());
	MyStack values(expression.length());

	for (std::size_t i = 0; i < expression.length(); ++i) {
		char token = expression[i];
		if (isdigit(token) || token == '.') {
			double value = 0;
			while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
				value = value * 10 + (expression[i] - '0');
				++i;
			}
			if (expression[i] == '.') {
				double fraction = 0.1;
				++i;
				while (i < expression.length() && isdigit(expression[i])) {
					value += (expression[i] - '0') * fraction;
					fraction *= 0.1;
					++i;
				}
			}
			--i;
			values.push(value);
		}
		else if (isalpha(token)) {
			std::string function;
			while (isalpha(expression[i])) {
				function += expression[i];
				++i;
			}
			if (function == "sin" || function == "cos") {
				if (expression[i] != '(') {
					std::cerr << "Ошибка: ожидалась открывающая скобка после функции " << function << std::endl;
					return 1;
				}
				double arg = 0;
				i++;
				int sign = 1;
				if (expression[i] == '-') {
					sign = -1;
					i++;
				}
				while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
					arg = arg * 10 + (expression[i] - '0');
					i++;
				}
				arg *= sign;
				if (expression[i] != ')') {
					std::cerr << "Ошибка: ожидалась закрывающая скобка после аргумента функции " << function << std::endl;
					return 1;
				}
				values.push((function == "sin") ? sin(arg) : cos(arg));
			}
			else {
				std::cout << "Неизвестная функция: " << function << std::endl;
				return 1;
			}
		}
		else if (token == ' ') {
			continue;
		}
		else if (token == '(') {
			operators.push(token);
		}
		else if (token == ')') {
			while (!operators.isEmpty() && operators.peek() != '(') {
				char op = operators.pop();
				double b = values.pop();
				double a = values.pop();
				values.push(applyOperator(op, b, a));
			}
			operators.pop();
		}
		else {
			while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(token)) {
				char op = operators.pop();
				double b = values.pop();
				double a = values.pop();
				values.push(applyOperator(op, b, a));
			}
			operators.push(token);
		}
	}

	while (!operators.isEmpty()) {
		char op = operators.pop();
		double b = values.pop();
		double a = values.pop();
		values.push(applyOperator(op, b, a));
	}

	double result = values.pop();
	std::cout << "Результат: " << result << std::endl;

	return 0;
}

int main() {
	setlocale(LC_ALL, "rus");
	while (true) {
		int user_choice;
		cout << endl << "Динамический массив - 1" << endl << "Двусвязный список - 2" << endl << "Стек - 3" << endl << "Выберите, с чем хотите работать: ";
		cout << "(для завершения работы программы введите 0): ";
		cin >> user_choice;
		cin.ignore();
		switch (user_choice) {
		case 1: {
			int data_type = 0;
			cout << "Введите тип данных( 1 - int 2 - char 3 - double): ";
			cin >> data_type;
			DynArr(data_type);
		}
		case 2: {
			cout << "Введите тип данных (int - 1 char - 2 double - 3): ";
			int a;
			cin >> a;
			DouLinked(a);
		}
		case 3: {
			evaluateExpression();
			break;
		}
		}
		if (user_choice == 0) { break; }
	}
}
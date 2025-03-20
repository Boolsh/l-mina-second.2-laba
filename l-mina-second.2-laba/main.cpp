//Задан текстовый файл. Сформировать набор словосочетаний из двух слов, встречающихся в тексте не менее двух раз.
//Из файла заполнить хэштаблицу, причем в информационной части ячейки хранится кол - во вхождений
//Потом прозодиммся, выбираем Каунт больше иди равен двум и распечатываем попарно
//В меню заполнить из файла, добавить, удалить, найти, распечатать все, очистить, задача

#include "Hash_table.h"
template <typename T>
T read_and_check() {
	T data;

	while (true) {
		std::cin >> data;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "Ошибка ввода!\n";
		}
		else {
			return data;
		}
	}
}

int menu()
{
	printf("Выберите действие:\n1.Заполнить из файла\n2.Добавить элемент\n3.Удалиь элемент\n4.Найти элемент\n5.Очистить таблицу\n6.Распечатать\n7.Решить задачу.\n--0.Завершить работу\n->");
	int res = read_and_check<int>();

	while (!(res <= 7 && res >= 0))
	{
		printf("Введите корректное число!\n");
		res = read_and_check<int>();
	}
	return res;
}

std::map<std::string, int> task(Hash_table & table)
{
	std::map<std::string, int> arr;
	if (table.get_size() > 0)
	{

		Hash_item* current;
		int count = 0;
		for (int i{}; i < table.get_MAX(); ++i)
		{
			current = table.get_elem(i);
			if (current && current->get_used() && current->get_count() >= 2)
			{
				//current->print();
				arr[current->get_key()] = current->get_count();
				//if (i % 3 == 0) std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
	return arr;
}

void print_task(std::map<std::string, int>& arr)
{
	
	auto it = arr.begin();
	while (std::next(it) != arr.end()) {
		if (it->second == 1) continue;

		auto nextIt = std::next(it); 

		while (nextIt != arr.end())
		{
			if (nextIt->second >= 2)
				std::cout << it->first << " " << nextIt->first << "\n";
			nextIt++;
			
		}
		++it;
	}
}


int main()
{
    SetConsoleOutputCP(1251);
 
    

	int choice = menu();
	Hash_table table;

	while (choice != 0)
	{

		if (choice == 1)
		{
			std::ifstream file("text.txt");
			table.fill(file);
		}
		
		if (choice == 2)
		{
			printf("Введите элемент для добавления-> ");
			std::string words = read_and_check<std::string>();
			if (!table.insert(words)) printf("\nЭлемент не добавлен\n\n");
			else printf("Элемент добавлен\n\n");
		}
		if (choice == 3)
		{
			printf("Введите элемент для удаления-> ");
			std::string words = read_and_check<std::string>();
			table.del(words);
		}
		if (choice == 4)
		{
			printf("Введите элемент для поиска-> ");
			std::string words = read_and_check<std::string>();
			if (table.search(words) == -1) printf("\nЭлемент не найден\n\n");
			else printf("\nЭлемент найден\n\n");
		}
		if (choice == 5) table.clear();
		if (choice == 6) table.print();
		if (choice == 7)
		{
			std::map<std::string, int> arr = task(table);
			print_task(arr);
		}
		choice = menu();
	}
	printf("\n\n\n\n\nРабота завершена.\n\n\n\n\n");


}


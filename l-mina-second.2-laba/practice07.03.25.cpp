#include <iostream>
#include <string>

class HashTable {
	struct HashItem {
	public:
		std::string info;
		bool used;
		HashItem(std::string info) {
			this->info = info;
			this->used = true;
		}
	};
	const int max_size = 127;
	const int step = 3;
	const int max_step_count = 10;
	int size = 0;
	HashItem** items;

	int hash_key(std::string value) {
		int res = 0;
		for (int i = 0; i < value.size(); i++)
		{
			res += value[i];
		}
		return res % max_size;
	}

	int make_step(int index) {
		return (index + step) % max_size;
	}

public:
	int get_size() { return size; }
	HashTable() {
		items = new HashItem * [max_size];
		for (int i = 0; i < max_size; i++) {
			items[i] = nullptr;
		}
	}
	~HashTable() {
		for (int i = 0; i < max_size; i++)
		{
			if (items[i] != nullptr)
				delete items[i];
		}
		delete items;
	}

	bool search(std::string value) {
		int i = hash_key(value);
		int step_num = 1;
		while (items[i] != nullptr && items[i]->info != value && step_num < max_step_count)
		{
			i = make_step(i);
			step_num++;
		}
		if (items[i] != nullptr && items[i]->info == value)
			return items[i]->used;
		return false;
	}
	bool insert(std::string value) {
		if (size == max_size - 1 || search(value))
			return false;
		int i = hash_key(value);
		int step_num = 1;
		while (items[i] != nullptr && items[i]->used && step_num < max_step_count)
		{
			i = make_step(i);
			step_num++;
		}

		if (items[i] == nullptr) {
			items[i] = new HashItem(value);
			size++;
			return true;
		}
		if (!items[i]->used) {
			items[i]->info = value;
			items[i]->used = true;
			return true;
		}
		return false;
	}

	bool del(std::string value)
	{
		if (size == 0 || !search(value))
			return false;
		int i = hash_key(value);
		int step_num = 1;
		while (items[i] != nullptr && items[i]->info != value && step_num < max_step_count)
		{
			i = make_step(i);
			step_num++;
		}
		if (items[i] != nullptr && items[i]->info == value && items[i]->used)
		{
			items[i]->used = false;
			size--;
			return true;
		}
		return false;
	}

	void print() {
		for (int i = 0; i < max_size; i++)
		{
			if (items[i] != nullptr && items[i]->used)
				std::cout << i << " " << items[i]->info << std::endl;
		}
	}

};

void print_menu() {
	std::cout << "1 - ADD\n";
	std::cout << "2 - DEL\n";
	std::cout << "3 - FIND\n";
	std::cout << "4 - PRINT\n";
	std::cout << "5 - EXIT\n";
}

	int main()
	{
		int choice = 0;
		HashTable ht;
		do {
			print_menu();
			std::cin >> choice;
			std::string value;
			switch (choice)
			{
			case 1:
				std::cout << "Enter value: ";
				std::cin >> value;
				if (!ht.insert(value))
					std::cout << "Error\n";
				else
					std::cout << "Added\n";
				break;
			case 2:
				std::cout << "Enter value: ";
				std::cin >> value;
				if (!ht.del(value))
					std::cout << "Error\n";
				else
					std::cout << "Deleted\n";
				break;
			case 3:
				std::cout << "Enter value: ";
				std::cin >> value;
				if (ht.search(value))
					std::cout << "Found\n";
				else
					std::cout << "Not found\n";
				break;
			case 4:
				ht.print();
				break;
			}
		} while (choice != 5);

	}
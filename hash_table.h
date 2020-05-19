#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <list>
#include <fstream>
#include <Windows.h>
#include <iomanip>

template <typename OurKey, typename OurField>
struct listik
{
	std::list<std::pair<OurKey, OurField>> arr;
};


template <typename OurKey, typename OurField>
class hash_table
{
public:

	inline void clear() {
		for (int i = 0; i < 256; i++)
			list_arr[i].arr.clear();
	}
	std::pair<OurKey, OurField>& operator[](const OurKey key) {
		for (auto it = list_arr[get_index(key)].arr.begin(); it != list_arr[get_index(key)].arr.end(); it++) {
			if (it->first == key) {
				return *it;
			}
		}
	}

	void print() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "Russian");
		for (int i = 0; i < 256; i++) {
			for (auto it : list_arr[i].arr) {
				std::cout << it.first << std::setw(65 - it.first.size())<< it.second << std::endl;
			}
		}
	}

	inline void put(OurKey key, OurField field) {
		if (!isInTable(key))
			list_arr[get_index(key)].arr.push_back(std::make_pair(key, field));
		else
			std::cerr << "That key are inclded into hash-table\n";
	}

	inline void remove(OurKey key) {
		for (auto it = list_arr[get_index(key)].arr.begin(); it != list_arr[get_index(key)].arr.end(); it++) {
			if (it->first == key) {
				list_arr[get_index(key)].arr.erase(it);
				return;
			}
		}
		std::cout << "Ёлементы не найдены\n";
	}

	inline void find(OurKey key) {
		for (auto it = list_arr[get_index(key)].arr.begin(); it != list_arr[get_index(key)].arr.end(); it++) {
			if (it->first == key) {
				std::cout << "Key: " << key << " Value: " << it->second << std::endl;
				return;
			}
		}
		std::cout << "Ёлементы не найдены\n";
	}

	bool isEmpty() {
		for (int i = 0; i < 256; i++) {
			if (list_arr[i].arr.size() != 0)
				return false;
		}
		return true;
	}

	void changeField(OurKey key, OurField newValue) {
		for (auto it = list_arr[get_index(key)].arr.begin(); it != list_arr[get_index(key)].arr.end(); it++) {
			if (it->first == key) {
				it->second = newValue;
				return;
			}
		}
	}

	void outputFile(std::string _FILENAME) {
		std::ofstream fout(_FILENAME, std::ios::out);
		for (int i = 0; i < 256; i++) {
			for (auto it : list_arr[i].arr) {
				fout << it.first << " " << it.second << std::endl;
			}
		}
	}

private:

	listik<OurKey, OurField> list_arr[256];

	inline int get_index(OurKey key) {
		std::string hash = md5(key);
		int index = hash[15];
		return index >= 0 ? index : 256 + index;
	}

	inline OurField& get_element(OurKey key) {
		for (auto it : list_arr[get_index(key)].arr) {
			if (it.first == key)
				return it.second;
		}
	}

	bool isInTable(OurKey key) {
		for (auto it = list_arr[get_index(key)].arr.begin(); it != list_arr[get_index(key)].arr.end(); it++) {
			if (it->first == key) {
				return true;
			}
		}
		return false;
	}
};
#endif 


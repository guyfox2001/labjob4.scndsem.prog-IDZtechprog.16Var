#include <iostream>
#include "md5.h"
#include <string>
#include <random>
#include "hash_table.h"
#include <Windows.h>
using namespace std;

void SW_OP(hash_table<string, int>* hs, string _FILENAME) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int oper, flag_def = 0;
	string key = "";
	pair<string, int> elem;
	while (flag_def != 2)
	{
		flag_def = 0;
		while (flag_def != 1)
		{
			cout << "Введите номер операции: \n";
			cout << "1. Добавить\n";
			cout << "2. Удалить\n";
			cout << "3. Поиск\n";
			cout << "4. Изменить\n";
			cout << "5. Пустой ли список?\n";

			cin >> oper;
			switch (oper)
			{
			case 1:
				cout << "Введите страну и ее население \n";
				cin >> elem.first;
				cin >> elem.second;
				hs->put(elem.first, elem.second);
				hs->print();
				flag_def = 1;
				break;
			case 2:
				cout << "Введите имя элемента: \n";
				cin.ignore();
				cin >> key;
				hs->remove(key);
				hs->print();
				flag_def = 1;
				break;
			case 3:
				cout << "Введите имя элемента: \n";
				cin.ignore();
				cin >> key;
				hs->find(key);
				hs->print();
				flag_def = 1;
				break;
			case 4:
				cout << "Введите имя элемента: \n";
				cin.ignore();
				cin >> key;
				hs->print();
				flag_def = 1;
				break;
			case 5:
				if (hs->isEmpty())
					cout << "Хэш-таблица пуста \n";
				else
					cout << "Хэш-таблица не пуста \n";
				flag_def = 1;
				break;
			default:
				cout << "Введено не верное значение \n";
				break;
			}
		}
		flag_def = 0;
		while (flag_def != 1 && flag_def != 2) {
			if (flag_def != 1 && flag_def != 2) {
				cout << "1. Продолжить работу с хэш-таблицей. 2.Закончить и записать в файл \n";
				cin >> flag_def;
			}
			else {
				cout << "Введено не верное значеие \n";
				cin >> flag_def;
			}
		}
	}
	cout << "Запись в файл \n";
	hs->outputFile(_FILENAME);
	hs->clear();
}

bool check_file(string _FILENAME) {
	ifstream read_file(_FILENAME, ios::in || ios::binary);
	if (read_file) {
		return true;
	}
	else {
		cerr << "Файл не был найден \n";
		return false;
	}
}
string check_mask(string _FILENAME) {
	if (_FILENAME.find(".pbs") != -1) {
		return _FILENAME;
	}
	else
	{
		return _FILENAME += ".pbs";
	}
}
bool check_empty(string _FILENAME) {
	int cnt = 0;
	string buff;
	ifstream check;
	check.open(_FILENAME, ios::in || ios::binary);
	while (!check.eof()) {
		check >> buff;
		if (!buff.empty())
			return false;
	}
	return true;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	ofstream out_file;
	ifstream read_file;
	fstream file;
	hash_table<string, int> map;
	pair<string, int> buffer;
	string _FILENAME;
	int exit = 0, oper, exit_2 = 0, n;
	do {
		cout << "Ведите имя файла \n";
		while (_FILENAME.empty()) {
			getline(cin, _FILENAME);
		}
		_FILENAME = check_mask(_FILENAME);
		if (check_file(_FILENAME)) {
			cout << "Вы хотите продолжать работу с файлом или перезаписать его? 1.Продолжить 2.Перезаписать\n";
			cin >> oper;
			switch (oper)
			{
			case 1:
				read_file.open(_FILENAME, ios::in || ios::binary);
				if (check_empty(_FILENAME)) {
					cerr << "Файл оказался пустым \n";
					cout << "Сейчас будет заново создаваться база данных\n";
					cin >> n;
					for (int i = 0; i < n; ++i) {
						cin >> buffer.first;
						cin >> buffer.second;
						map.put(buffer.first, buffer.second);
					}
					cout << "База записана \n";
					map.print();

				}
				else {
					int cnt = 0;
					while (!read_file.eof())
					{
						if (cnt == 10) break;
						read_file >> buffer.first;
						read_file >> buffer.second;
						if (buffer.first == "") {
							cnt++; continue;
						}
						else {
							cnt = 0;
							map.put(buffer.first, buffer.second);
							buffer.first = "";
							buffer.second = 0;
						}
					}
				}
				cout << "Файл считан \n";
				read_file.close();
				map.print();
				break;
			case 2:
				out_file.open(_FILENAME, ios::out);
				out_file.close();
				cout << "Файл очищен\n";
				cout << "Сейчас будет заново создаваться база данных\n";
				cin >> n;
				for (int i = 0; i < n; ++i) {
					cin >> buffer.first;
					cin >> buffer.second;
					map.put(buffer.first, buffer.second);
				}
				cout << "База записана \n";
				map.print();
				break;
			default:
				cerr << "Не верный параметр\n";
				break;

			}
		}
		else {
			out_file.open(_FILENAME, ios::out);
			out_file.close();
			cout << "Сейчас будет заново создаваться база данных\n";
			cin >> n;
			for (int i = 0; i < n; ++i) {
				cin >> buffer.first;
				cin >> buffer.second;
				map.put(buffer.first, buffer.second);
			}
			cout << "База записана \n";
			map.print();
		}
		SW_OP(&map, _FILENAME);
		_FILENAME.clear();
		fflush(stdin);
		// Параметры выхода
		cout << "Вы хотите продолжать работу с программой? 1.Да 2.Нет \n";
		cin >> exit;
		while (exit != 1 && exit != 2) {
			cout << "Не верное значение \n";
			cin >> exit;
		}
	} while (exit != 2);
}

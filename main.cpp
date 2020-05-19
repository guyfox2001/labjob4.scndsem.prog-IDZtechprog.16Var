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
			cout << "������� ����� ��������: \n";
			cout << "1. ��������\n";
			cout << "2. �������\n";
			cout << "3. �����\n";
			cout << "4. ��������\n";
			cout << "5. ������ �� ������?\n";

			cin >> oper;
			switch (oper)
			{
			case 1:
				cout << "������� ������ � �� ��������� \n";
				cin >> elem.first;
				cin >> elem.second;
				hs->put(elem.first, elem.second);
				hs->print();
				flag_def = 1;
				break;
			case 2:
				cout << "������� ��� ��������: \n";
				cin.ignore();
				cin >> key;
				hs->remove(key);
				hs->print();
				flag_def = 1;
				break;
			case 3:
				cout << "������� ��� ��������: \n";
				cin.ignore();
				cin >> key;
				hs->find(key);
				hs->print();
				flag_def = 1;
				break;
			case 4:
				cout << "������� ��� ��������: \n";
				cin.ignore();
				cin >> key;
				hs->print();
				flag_def = 1;
				break;
			case 5:
				if (hs->isEmpty())
					cout << "���-������� ����� \n";
				else
					cout << "���-������� �� ����� \n";
				flag_def = 1;
				break;
			default:
				cout << "������� �� ������ �������� \n";
				break;
			}
		}
		flag_def = 0;
		while (flag_def != 1 && flag_def != 2) {
			if (flag_def != 1 && flag_def != 2) {
				cout << "1. ���������� ������ � ���-��������. 2.��������� � �������� � ���� \n";
				cin >> flag_def;
			}
			else {
				cout << "������� �� ������ ������� \n";
				cin >> flag_def;
			}
		}
	}
	cout << "������ � ���� \n";
	hs->outputFile(_FILENAME);
	hs->clear();
}

bool check_file(string _FILENAME) {
	ifstream read_file(_FILENAME, ios::in || ios::binary);
	if (read_file) {
		return true;
	}
	else {
		cerr << "���� �� ��� ������ \n";
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
		cout << "������ ��� ����� \n";
		while (_FILENAME.empty()) {
			getline(cin, _FILENAME);
		}
		_FILENAME = check_mask(_FILENAME);
		if (check_file(_FILENAME)) {
			cout << "�� ������ ���������� ������ � ������ ��� ������������ ���? 1.���������� 2.������������\n";
			cin >> oper;
			switch (oper)
			{
			case 1:
				read_file.open(_FILENAME, ios::in || ios::binary);
				if (check_empty(_FILENAME)) {
					cerr << "���� �������� ������ \n";
					cout << "������ ����� ������ ����������� ���� ������\n";
					cin >> n;
					for (int i = 0; i < n; ++i) {
						cin >> buffer.first;
						cin >> buffer.second;
						map.put(buffer.first, buffer.second);
					}
					cout << "���� �������� \n";
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
				cout << "���� ������ \n";
				read_file.close();
				map.print();
				break;
			case 2:
				out_file.open(_FILENAME, ios::out);
				out_file.close();
				cout << "���� ������\n";
				cout << "������ ����� ������ ����������� ���� ������\n";
				cin >> n;
				for (int i = 0; i < n; ++i) {
					cin >> buffer.first;
					cin >> buffer.second;
					map.put(buffer.first, buffer.second);
				}
				cout << "���� �������� \n";
				map.print();
				break;
			default:
				cerr << "�� ������ ��������\n";
				break;

			}
		}
		else {
			out_file.open(_FILENAME, ios::out);
			out_file.close();
			cout << "������ ����� ������ ����������� ���� ������\n";
			cin >> n;
			for (int i = 0; i < n; ++i) {
				cin >> buffer.first;
				cin >> buffer.second;
				map.put(buffer.first, buffer.second);
			}
			cout << "���� �������� \n";
			map.print();
		}
		SW_OP(&map, _FILENAME);
		_FILENAME.clear();
		fflush(stdin);
		// ��������� ������
		cout << "�� ������ ���������� ������ � ����������? 1.�� 2.��� \n";
		cin >> exit;
		while (exit != 1 && exit != 2) {
			cout << "�� ������ �������� \n";
			cin >> exit;
		}
	} while (exit != 2);
}

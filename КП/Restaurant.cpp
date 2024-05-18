#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <iterator>
#include <cmath>
#include "UI.h"
using namespace std;

void pause();
string tab = "\t\t\t\t"; //������

//����������� ������������� �������� ������ ������ � ������ � 0
Restaurant::Restaurant() noexcept : _order_index(0)
{}

//����� ���� �� ����� menu.txt
void Restaurant::ShowMenu()
{
	system("cls");

	int i = 0;
	cout << endl << tab << "______________________ [ ���� ] _____________________" << endl << endl;

	for (const auto& dish : menu_list)
	{
		i++;
		cout << setw(34) << i << ". " << setw(35) << dish.first << setw(10) << dish.second << " BYN" << endl;
	}
	cout << tab << "_____________________________________________________\n\n";
}

//�������� ������� �� ����� orders.txt
void Restaurant::LoadOrders()
{
	ifstream in("source\\orders.txt");

	if (!in) return;

	order buff; //��������� ���������� ��� ������ ������ �� ������

	while (!in.eof() and in.peek() != EOF) //�������� �� ������ ����
	{
		in >> buff.order_num;
		in >> buff.name_waiter;
		in >> buff.price;
		in >> buff.order_time;
		in.get();
		getline(in, buff.filling);
		in >> buff.done;
		in.get();

		list.push_back(buff); //���������� ������ � ������

		_order_index++;		  //���������� ������� �� 1
	}

	in.close();
}

//���������� �������� ���� � ��� � ������� (����:��������, ��������:����)
void Restaurant::LoadMenuData()
{
	ifstream in("source\\menu_data.txt", ios::in);

	if (!in) throw " ";

	while (!in.eof())
	{
		string _title;
		float _price;

		in.get();
		getline(in, _title);
		in >> _price;

		menu_list.insert({ _title, _price }); //���������� ���� � �������
	}
}

//�������� �� ������� ������ � ������ �� ��� ������ (order.numorder)
bool Restaurant::checkOrder(vector<int> _orderIndexes, int _numOrder)
{
	//������������ ������� ��������: ���� ����� ���� � ������ - true, � ��������� ������ - false
	return (find(begin(_orderIndexes), end(_orderIndexes), _numOrder) != end(_orderIndexes));
}

//������� �������� ������
void Restaurant::DelOrder()
{
	cout << endl << tab << "__________________ [ �������� ������ ] ___________________\n" << endl;

	//����� ��������� (��������� � ������) ������� �� ��������

	//���� ������ ����, ������ ��� ������ ���� (return)
	if (list.empty())
	{
		cout << "���� ��� ������� ���" << endl;
		pause();
		return;
	}

	//������������� ��������
	char _change;
	cout << tab << "��������� ����� �����." << endl;
	cout << tab << "��������� ���������? (��� �������� ������ ����� ��������)" << endl;
	cout << tab << "      y. ��" << endl;
	cout << tab << "      n. ���" << endl;
	cout << endl << tab << "____________________________________________________\n";
	_change = _getch();

	if (_change == 'n') return;

	//�������� ��������

	list.erase(list.end() - 1);

	_order_index--;  //���������� �������
	_changed = true; //����� � ��������� ������
}

//����� ���� (��������� ������� AddOrder())
vector<string> Restaurant::ChooseDishes()
{
	//��������� �����
	vector<string> dishes{};

	int dish = -1;

	bool _continue = true;
	do
	{
		cin.clear();
		fflush(stdin);

		system("cls");
		cout << endl << tab << "_________________ [ ����� ����� ] __________________\n" << endl;

		//����� ����
		ShowMenu();

		//����� ���������� � ������� �� ���� � ������
		cout << endl << tab << "������� ��� �����:\n";
		cout << tab;

		cin >> dish;

		if (!cin)
		{
			cout << tab << "�������� ��������." << endl;
			cout << tab << "������� ����� ������� ��� �����������" << endl;

			pause();
			break;
		}
		//�� ������, ��� � ������ ����
		if (dish <= 0 or dish > menu_list.size())
		{
			cout << tab << "��� ������ �����." << endl;
			cout << tab << "������� ����� ������� ��� �����������" << endl;

			pause();
			continue;
		}

		//����� ����� �� ������ � ������
		string keyDish;
		int counter = 0;
		for (auto& d : menu_list)
			if (counter != dish - 1)
			{
				counter++;
				continue;
			}
			else
			{
				keyDish = d.first;
				break;
			}

		dishes.push_back(keyDish);
		cout << tab << "��� ��? (y/n)" << endl;

		do
		{
			const char __continue = _getch();
			if (__continue == 'y')
			{
				_continue = false;
				break;
			}
			else if (__continue == 'n')
				break;

		} while (true);

	} while (_continue);

	//������������ ������ � �������
	return dishes;
}

//������� ���� ������ �� ��������� ������
float Restaurant::CalculatePrice(vector<string> keyDishes)
{
	float _price = 0;
	for (int i = 0; i < keyDishes.size(); i++)
	{
		_price += menu_list[keyDishes.at(i)];
	}
	return _price;
}

//����� ���� ������� �� �����
void Restaurant::ShowOrders()
{
	cout << endl << tab << "_____________________ [ ������ ] ____________________\n" << endl;

	//�������� �� ��������� ��������� � ������
	if (list.empty())
	{
		cout << tab << "���� ��� ������� ���" << endl;
		cout << tab << "������� ����� ������� ��� �����������..." << endl;
		pause();
		return;
	}

	for (int i = 0; i < _order_index; i++)
	{
		system("cls");
		cout << endl << "\n\n\n\n\n" << tab << "_____________________ [ ������ ] ____________________\n" << endl;

		cout << tab << "\t����� �" << list.at(i).order_num + 1 << endl;
		cout << tab << "\t��� ���������: " << list.at(i).name_waiter << endl;
		cout << tab << "\t����� �������� ������: " << list.at(i).order_time << endl;

		//����� ����������� ������
		cout << tab << "\t���������� ������:\n";

		cout << endl << tab << '\t';
		string filling = list.at(i).filling;
		for (int i = 0; i < filling.size(); i++)
			if (filling[i] == ',') cout << endl << tab << '\t';
			else cout << filling[i];

		cout << endl;
		cout << tab << "\t���������: " << list.at(i).price << "BYN" << endl;
		cout << tab << "\t����������: " << (list.at(i).done ? "�����" : "�� �����") << endl;
		cout << tab << "____________________________________________________\n\n";
		cout << tab << "������� ����� �������, ����� ������� ��������� �����\n\n";
		pause();
	}
	cout << tab << "������� ����� ������� ��� ������..." << endl;
	pause();
}

//���������� ������ ������
void Restaurant::AddOrder()
{
	system("cls");
	system("mode con cols=115 lines=40");
	_changed = true;

	order buff;

	cout << endl << tab << "__________________ [ ����� ����� ] _________________" << endl;

	buff.order_num = _order_index; //��������� ������ ������

	_time.SetTime();
	buff.order_time = _time.ToString(); // ��������� ������� ���������� ������

	buff.done = false;

	cout << endl << tab << "������� ��� ���������: ";
	cin >> buff.name_waiter;

	//���������� ������
	vector<string> _dishes = ChooseDishes();

	if (!_dishes.size()) 
	{
		system("mode con cols=115 lines=30");
		return;
	}

	for (const auto& dish : _dishes)
		buff.filling += dish + ",";

	//��������� ������
	buff.price = CalculatePrice(_dishes);

	cout << endl << tab << "____________________________________________________\n";
	cout << endl << tab << "����� ����� ��������.";
	cout << endl << tab << "������� ����� ������� ��� �����������..." << endl;
	pause();
	list.push_back(buff);

	_order_index++;
	SaveOrders();
	system("mode con cols=115 lines=30");
}

//���������� ������ � ������ � ����
void Restaurant::SaveOrders()
{
	if (!_changed) return;

	const int mode = ios::out;

	ofstream out("source\\orders.txt", mode);

	if (!out) return;

	for (int i = 0; i < _order_index; i++)
	{
		out << list.at(i).order_num << ' ';
		out << list.at(i).name_waiter << ' ';
		out << list.at(i).price << ' ';
		out << list.at(i).order_time << '\n';
		out << list.at(i).filling << '\n';
		out << list.at(i).done << '\n';
	}

	out.close();
}

//���������� ������ � ����
void Restaurant::SaveMenuData()
{
	if (!_changed_menu) return;

	const int mode = ios::out;

	ofstream out("source\\menu_data.txt", mode);

	if (!out) return;

	for (auto& item : menu_list)
	{
		out << endl << item.first;
		out << endl << item.second;
	}

	out.close();
}

//��������� ���������� ������
void Restaurant::CheckMark()
{
	if (list.empty())
	{
		cout << tab << "���� ��� ������� ���" << endl;
		pause();
		return;
	}

	_changed = true;
	int _numorder = 0;
	cout << endl << tab << "__________________ [ �������� ������� ] ___________________\n";

	cout << endl << tab << "	�������� ���������� �������" << endl;
	cout << endl << tab << "___________________________________________________________\n";


	vector<int> availableOrders{};
	cout << endl << tab << "��������� ������:" << endl << tab;
	if (list.empty())
	{
		cout << "���� ��� ������� ���" << endl;
		pause();
		return;
	}
	else
		for (int i = 0; i < list.size(); i++)
		{
			availableOrders.push_back(list.at(i).order_num);
			cout << list.at(i).order_num + 1 << " ";
		}

	cout << endl << tab << "������� ����� ������: ";
	cin >> _numorder;

	if (!(checkOrder(availableOrders, _numorder - 1)))
	{
		cout << tab << "������ ������ �� ����������. ���������� � ������ ���.";
		pause();
		system("cls");
		return;
	}

	char change;
	cout << tab << "��������� ������ �" << _numorder << " �������� �� '�����'." << endl;
	cout << tab << "��������� ���������? (��� �������� ������ ����� ��������)" << endl;
	cout << tab << "      y. ��" << endl;
	cout << tab << "      n. ���" << endl;
	cout << endl << tab << "____________________________________________________\n";
	change = _getch();

	if (change == 'n') return;
	list.at(_numorder - 1).done = true;
}

//�������� ����� ����� ����
void Restaurant::AddNewMenuItem()
{
	system("cls");

	_changed_menu = true;

	cout << endl << tab << "____________________ [ ���� ] ___________________" << endl;

	//�������� �����
	string dish_title = "";
	cout << endl << tab << "�������� �����: \n";
	cout << tab;

	cin.get();
	getline(cin, dish_title);

	//����
	float price = 0.0;

	cout << endl << tab << "���� ����� (�������� 14.88): \n" << tab;
	cin >> price;

	if (price <= 0)
	{
		cout << tab << "____________________________________________________\n\n";
		cout << tab << "�������� ��������" << endl;
		cout << tab << "������� ����� �������, ����� �����" << endl;
		pause();
		system("cls");
		return;
	}

	//���������� �� 2 ������ ����� �������
	price = round((price * 100)) / 100.0;

	cout << tab << "____________________________________________________\n\n";

	cout << tab << "����� ����� ���� ��������";

	menu_list.insert({ dish_title, price });
}

//������� ����� ���� �� �������� �����
void Restaurant::DelMenuItem()
{
	system("mode con cols=115 lines=50");

	cout << endl << tab << "______________________ [ ���� ] _____________________" << endl;

	if (menu_list.empty())
	{
		cout << "���� ��� ������� ���" << endl;
		pause();
		return;
	}

	ShowMenu();

	cout << endl << tab << "��� �������� ����� �� ������ ���������� ������\n" << tab << "��� ��������";
	cout << endl << tab << "____________________________________________________\n";

	//�������� �����
	string dish_title = "";
	cout << endl << tab << "�������� �����: \n";
	cout << tab;

	cin.get();
	getline(cin, dish_title);

	if (!menu_list.count(dish_title))
	{
		cout << endl << tab << "____________________________________________________\n";
		cout << tab << "������ ����� �� ����������" << endl;
		pause();
		return;
	}

	//������������� ��������
	char _change;
	cout << tab << dish_title << " �����" << endl;
	cout << tab << "��������� ���������? (��� �������� ������ ����� ��������)" << endl;
	cout << tab << "      y. ��" << endl;
	cout << tab << "      n. ���" << endl;
	cout << endl << tab << "____________________________________________________\n";
	_change = _getch();

	system("mode con cols=115 lines=30");

	if (_change == 'n') return;

	menu_list.erase(dish_title);

}

//��������� ������� ���������� ������
void Restaurant::ltime::SetTime() noexcept
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	seconds = time.wSecond;
	minutes = time.wMinute;
	hours = time.wHour;
}

//������� ������� � ������
string Restaurant::ltime::ToString()
{
	return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}
#pragma once

#include "includes_file.h"

using namespace std;

class Restaurant;

class User
{

	friend class Restaurant;
private:

	//��������� � ������������
	string _login;    //����� ������������
	string _password; //������ ������������
	string _name;     //��� ������������
	//����� 

	bool _is_admin;   //�������� �� ������������� ���������������
	bool user_alive;  //���� �������� �����������

	void PrintVertucalLine(int x, int y);
public: 
	User();															//����������� ��� ����������
	User(bool is_admin, string login, string pass, string name, bool u = false); //����������� �� ����� ����������� ��� ���������� �����

	bool is_admin() const noexcept; //��������� �������� ���� is_admin
	void set_admin(bool w);			//��������� ���� is_admin
	bool alive();					//��������� �������� ���� user_alive

	void PrintInfo() const;    //���������� � ������������
	void ShowMyOrders(Restaurant* restaurant); //���������� � ������
};
//Programm A
#include<iostream>
#include<locale>
#include<string>
#include"../Additional/sockets.h"
#include"../Additional/functions.h"

int main() {

	setlocale(LC_ALL, "rus");
	PushPullSocket A;					//������������ ��� �������������� � ���������� C
	PushPullSocket State;				//������������ ��� �������������� � ���������� B

	A.GetPullSocket().Bind(4040);		//������� ���� 4040, ����� ����� ���-�� ����� �� ����
	A.GetPushSocket().Bind(4041);		//������� ���� 4041, ����� ����� ���-�� �������� � ����
	State.GetPushSocket().Bind(4042);
	State.SetBlock(ZMQ_DONTWAIT);		//�������� ������, ����� B �� ����� ��������, ����� ��� �������� ��������� � ���� �� ����� ����������� �����

	HANDLE C = CreateProcessC();		//��������� �
	HANDLE B = CreateProcessB();		//��������� B


	Sleep(1000);						//���� ���� �� ����

	std::string line;
	int count = 0;
	while (std::getline(std::cin, line)) {		//������ ������ �� �������
		count = A.SendMsg(line);				//���������� � � ������, ����� ��������� �����
		State.SendInt(count);					//���������� B ������� �������� ���������� � �
		A.GetMsg(line);							//�������� ����� �� �, ����� ����� ��������� �����, ��-�� ���� ������ ���-�� ������, ���� �� ����� ������� ����� �� � - ������
		std::cout << line << std::endl;			//������� ����� �� �
	}

	TerminateProcess(C, 0);			//��������� �
	TerminateProcess(B, 0);			//��������� B

	return 0;
}
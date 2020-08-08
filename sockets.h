#pragma once
#include <string>
#include <mutex>
#include <zmq.h>
//������ �� ������� ����� ������������� ��� ������
const std::string PREFIX_ADRESS_LOCALHOST = "tcp://localhost:";		//������������ � ������� connect
const std::string PREFIX_ADRESS = "tcp://*:";						//������������ � ������� bind

const int UNKNOWN = -1;			//� ������� ������ �� ������
const int BINDED = 0;			//����� ��� �������
const int CONNECTED = 1;		//����� ��� ���������
const int RECONNECTED = 2;		//����� ��� ������������

struct Socket {			//��������� zmq ������ ������������ ��� ������� ������, �������� ������ ������
	void* context;				//�������� ������
	void* socket;				//��� zmq �����
	int port = -1;				//���� �� �������� ��������� ����� ��� �� ��������� 
	int config = UNKNOWN;		//��� ����������� � �������
	bool Bind(int port);		//��������� ���� �� ����� 
	bool Connect(int port);		//������������ ���� �� �����
	bool Disconnect();			//�������������� �� ����
	bool Reconnect(int port);
};
const int NOT_BLOCKING = ZMQ_DONTWAIT;
const int BLOCKING = 0;
struct PushPullSocket {			//��������� ������� ���������� push � pull ����� � ����, ��������� ���� ����� ��� ���������� ���������, ��� � ���������
private:
	Socket push;
	Socket pull;
	std::mutex door;
	int flags = BLOCKING;
public:
	PushPullSocket();
	int SendMsg(const std::string& msg);				//��������� ��������� � �����
	int GetMsg(std::string& msg);						//�������� ��������� � ������
	int SendInt(int);									//��������� �����
	int GetInt(int&);									//�������� ����� � �������� ��� � ���������� �� ������ ��������
	void SetBlock(int flags);							//���������� ����� �� �����
	Socket& GetPushSocket();							//�������� ������ �� �����
	Socket& GetPullSocket();
};
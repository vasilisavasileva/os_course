#include<zmq.h>
#include"sockets.h"

PushPullSocket::PushPullSocket() {			//������������ push � pull ������
	push.context = zmq_ctx_new();
	pull.context = zmq_ctx_new();
	push.socket = zmq_socket(push.context, ZMQ_PUSH);
	pull.socket = zmq_socket(pull.context, ZMQ_PULL);
}

bool Socket::Bind(int port_) {						//��� ��������� �����
	std::string adress;
	port = port_;
	adress += PREFIX_ADRESS;
	adress += std::to_string(port);
	if (zmq_bind(socket, adress.c_str()) == 0) {
		//std::cout << "Binded: " << adress << "\n";
		config = BINDED;
		return true;
	}
	else {
		//std::cout << "Not binded : " << adress << "\n";
		return false;
	}
}

bool Socket::Disconnect() {								//��� ��������� �����
	if (config == CONNECTED) {
		std::string adress;
		adress += PREFIX_ADRESS_LOCALHOST;
		adress += std::to_string(port);
		if (zmq_disconnect(socket, adress.c_str()) == 0) {
			port = -1;
			config = UNKNOWN;
			return true;
		}
	}
	return false;
}

bool Socket::Reconnect(int port_) {						//��� �������������� �����
	if (Disconnect()) {
		if (Connect(port_)) {
			//std::cout << "Reconnected!\n";
			config = RECONNECTED;
			return true;
		}
	}
	//std::cout << "Does not Reconnected!\n";
	return false;
}

int PushPullSocket::SendMsg(const std::string& msg) {		//��� ���������� ���������
	door.lock();													//��� ������������� ���������� �������
	zmq_msg_t message;
	zmq_msg_init_size(&message, msg.length() + 1);
	memcpy(zmq_msg_data(&message), msg.c_str(), msg.length() + 1);
	int res = zmq_msg_send(&message, push.socket, flags);		//������ ���������� � push �����
	zmq_msg_close(&message);
	door.unlock();
	return res;
}
int PushPullSocket::GetMsg(std::string& msg) {				//��� ��������� ���������
	door.lock();
	zmq_msg_t reply;
	zmq_msg_init(&reply);
	int res;
	if ((res = zmq_msg_recv(&reply, pull.socket, flags)) != -1) {		//��������� �� pull ������
		char* str = new char[zmq_msg_size(&reply)];
		memcpy(str, zmq_msg_data(&reply), zmq_msg_size(&reply));
		zmq_msg_close(&reply);
		msg = std::string(str);
		delete[] str;
	}
	door.unlock();
	return res;
}
bool Socket::Connect(int port_) {					//��� ���������� �����
	std::string adress;
	port = port_;
	adress += PREFIX_ADRESS_LOCALHOST;
	adress += std::to_string(port);
	if (zmq_connect(socket, adress.c_str()) == 0) {
		//std::cout << "Connected: " << adress << "\n";
		config = CONNECTED;
		return true;
	}
	else {
		//std::cout << "Not Connected: " << adress << "\n";
		return false;
	}
}

Socket& PushPullSocket::GetPushSocket() {
	return push;
}
Socket& PushPullSocket::GetPullSocket() {
	return pull;
}


int PushPullSocket::SendInt(int num) {
	door.lock();													//��� ������������� ���������� �������
	zmq_msg_t message;
	zmq_msg_init_size(&message, sizeof(int));
	memcpy(zmq_msg_data(&message), &num, sizeof(int));
	int res = zmq_msg_send(&message, push.socket, flags);		//������ ���������� � push �����
	zmq_msg_close(&message);
	door.unlock();
	return res;
}
int PushPullSocket::GetInt(int& num) {
	door.lock();													//��������� �������
	zmq_msg_t reply;												//������� zmq-���������
	zmq_msg_init_size(&reply, sizeof(int));							//������������� ��� � ����������� ��������
	int res;
	if ((res = zmq_msg_recv(&reply, pull.socket, flags)) != -1) {		//��������� �� pull ������
		memcpy(&num, zmq_msg_data(&reply), zmq_msg_size(&reply));		//�������� � num �����, ������� �������
		zmq_msg_close(&reply);										//��������� zmq-���������
	}
	door.unlock();													//��������� �������
	return res;														//���������� ���-�� ��������� ����
}


void PushPullSocket::SetBlock(int flag) {
	flags = flag;
}
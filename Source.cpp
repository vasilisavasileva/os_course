//Programm A
#include<iostream>
#include<locale>
#include<string>
#include"../Additional/sockets.h"
#include"../Additional/functions.h"

int main() {

	setlocale(LC_ALL, "rus");
	PushPullSocket A;					//используется для взаимодействия с программой C
	PushPullSocket State;				//используется для взаимодействия с программой B

	A.GetPullSocket().Bind(4040);		//Слушаем порт 4040, чтобы потом что-то взять из него
	A.GetPushSocket().Bind(4041);		//Слушаем порт 4041, чтобы потом что-то положить в него
	State.GetPushSocket().Bind(4042);
	State.SetBlock(ZMQ_DONTWAIT);		//Возможен случай, когда B не будет работать, тогда при отправке сообщения в него не будет блокировать поток

	HANDLE C = CreateProcessC();		//Запускаем С
	HANDLE B = CreateProcessB();		//Запускаем B


	Sleep(1000);						//Чуть чуть по спим

	std::string line;
	int count = 0;
	while (std::getline(std::cin, line)) {		//читаем строки по строчно
		count = A.SendMsg(line);				//отправляем в С строку, сокет блокирует поток
		State.SendInt(count);					//отправляем B сколько символов отправлили в С
		A.GetMsg(line);							//получаем ответ от С, сокет также блокирует поток, из-за чего ввести что-то дальше, пока не будет получен ответ от С - нельзя
		std::cout << line << std::endl;			//выводим ответ от С
	}

	TerminateProcess(C, 0);			//закрываем С
	TerminateProcess(B, 0);			//закрываем B

	return 0;
}
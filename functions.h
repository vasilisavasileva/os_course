#pragma once
#include<Windows.h>
#include<string>

const std::string PROCCESS_B = "B";			//�������� ��������� B
const std::string PROCCESS_C = "C";			//�������� ��������� C
HANDLE CreateProcessB();
HANDLE CreateProcessC();
HANDLE CreateNamedProcess(const std::string& name);
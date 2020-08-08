#pragma once
#include<Windows.h>
#include<string>

const std::string PROCCESS_B = "B";			//название программы B
const std::string PROCCESS_C = "C";			//название программы C
HANDLE CreateProcessB();
HANDLE CreateProcessC();
HANDLE CreateNamedProcess(const std::string& name);
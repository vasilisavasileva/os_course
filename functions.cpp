#include"functions.h"

HANDLE CreateNamedProcess(const std::string& name) {	//������� ������� �� ��� ��������
	SECURITY_ATTRIBUTES sa;								//��� ����������� ����������� ����� �� ����� ���
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	char* SecondProcess = (char*)name.c_str();

	PROCESS_INFORMATION ProcessInfo;
	ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	StartupInfo.cb = sizeof(STARTUPINFO);


	BOOL process = CreateProcess(NULL,
		SecondProcess,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&StartupInfo,
		&ProcessInfo);
	if (!process) {
		return 0;
	}
	return ProcessInfo.hProcess;
}


HANDLE CreateProcessB() {
	return CreateNamedProcess(PROCCESS_B);		//������� ����� ������� - ��������� B
}
HANDLE CreateProcessC() {
	return CreateNamedProcess(PROCCESS_C);		//������� ����� ������� - ��������� �
}
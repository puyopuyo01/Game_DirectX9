#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include<map>
#include <stdio.h>
#include <iostream>
#include<string>

using namespace std;

/*
画像はそのままのデータを使用するのではなく、アーカイブファイルて1つのファイルにする。
FileMappingクラスでアーカイブファイルのデータから画像を抽出。
*/

struct MyFileInfo {
	int m_MemoryNum;
	int m_FileSize;
	std::string m_FileName;
	MyFileInfo(int t_MemoryNum, int t_FileSize, std::string t_FileName);
};
/*アーカイブファイルを処理するクラス*/
class FileMapping {
public:
	static FileMapping* GetInstance();
	void Release();
	FileMapping();

	void Mapping();

	const char* GetPointer(string FileName);
	MyFileInfo* GetFile(string FileName);

private:
	HANDLE FileHandle;
	HANDLE MappedFileHandle;
	WIN32_FIND_DATA t_FindData;


	int m_HeaderSize;
	std::map<string, MyFileInfo*> FileNameMap;
	vector<MyFileInfo*> FileDataVec;

	char *Mappingptr;


	static FileMapping* SingleTon;

};
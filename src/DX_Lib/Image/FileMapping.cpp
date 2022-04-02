#include"./FileMapping.h"



MyFileInfo::MyFileInfo(int t_MemoryNum, int t_FileSize, std::string t_FileName) {
	m_MemoryNum = t_MemoryNum;
	m_FileSize = t_FileSize;
	m_FileName = t_FileName;
}

FileMapping* FileMapping::SingleTon;


FileMapping* FileMapping::GetInstance() {
	if (FileMapping::SingleTon == nullptr) { FileMapping::SingleTon = new FileMapping(); }
	return FileMapping::SingleTon;
}

FileMapping::FileMapping(){}

void FileMapping::Release() {
	vector<MyFileInfo*>::iterator itr;
	itr = FileDataVec.begin();
	while(itr != FileDataVec.end()){
		delete *itr; 
		itr++;
	}
	CloseHandle(MappedFileHandle);   // �t�@�C���}�b�s���O�I�u�W�F�N�g�n���h�������;
	CloseHandle(FileHandle);   // �t�@�C���n���h�������

}


void FileMapping::Mapping() {
	FileHandle = CreateFile("MyArchive.pak", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (FileHandle == INVALID_HANDLE_VALUE) {
		MessageBox(NULL,
			"P", "���s_FileHandle", MB_OK);
		return;
	}
	//�t�@�C���̃n���h������A�}�b�v�h�t�@�C���̃n���h���𓾂�
	MappedFileHandle = CreateFileMapping(FileHandle,0, PAGE_READONLY, 0, 0,"MyArchive.pak");
	if (MappedFileHandle <= 0) {
		MessageBox(NULL,
			"P", "���s_MappingFileHandle", MB_OK);
		CloseHandle(FileHandle);
	}


	char FileName[1024] = { '\0' };
	Mappingptr= (char*)MapViewOfFile(MappedFileHandle, FILE_MAP_READ, 0, 0, 0);

	int t_Num = 0, t_MemoryNum = 0, t_FileNum = 1;
	for (; Mappingptr[t_Num] != '#'; t_Num++){

		int FileSize = 0;
		for (; Mappingptr[t_Num] >= '0' && Mappingptr[t_Num] <= '9'; t_Num++)
		{
			FileSize = FileSize * 10 + (Mappingptr[t_Num] - '0');
		}

		char t_FileName[1024] = { '\0' };
		t_Num += 1;
		for (int i = 0; Mappingptr[t_Num] != '"'; t_Num++, i++)
		{
			t_FileName[i] = Mappingptr[t_Num];
		}

		//�t�@�C���ƃ|�C���^�̈ʒu��Ή�������ׂ�map�o�^
		MyFileInfo* t_Info = new MyFileInfo(t_MemoryNum, FileSize, t_FileName);
		std::pair<std::string, MyFileInfo*> p(t_FileName, t_Info);
		FileNameMap.insert(p);

		//�t�@�C���ԍ��Ō�������ׂ�Vector�o�^
		FileDataVec.push_back(t_Info);

		t_MemoryNum += FileSize;
		t_FileNum += 1;
	}
	//�w�b�_�[�̃T�C�Y��ۑ�
	m_HeaderSize = t_Num + 1;

}




const char* FileMapping::GetPointer(string FileName) {
	//map<string, MyFileInfo*>::iterator it;
	auto it = FileNameMap.find(FileName);
	//it = FileNameMap.find(FileName);

	if (it != FileNameMap.end()) {
		//�t�@�C���J�n�ʒu + �w�b�_�[�T�C�Y���A���ۂ̃t�@�C���J�n�ʒu�I
		return(&Mappingptr[ it->second->m_MemoryNum + m_HeaderSize]);
	}
	else {
		MessageBox(NULL,
			FileName.c_str(), "���s_GetPointer", MB_OK);
		return(NULL);
	}
}


MyFileInfo* FileMapping::GetFile(string FileName) {
	auto it = FileNameMap.find(FileName);
	if (it != FileNameMap.end()) {
		return(it->second);
	}
	else {
		MessageBox(NULL,
			FileName.c_str(), "���s_GetFile", MB_OK);
		return(NULL);
	}

}
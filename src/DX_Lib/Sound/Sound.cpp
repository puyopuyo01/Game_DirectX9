#include"./Sound.h"

Sound::Sound(const char* file) {
	Secondary = NULL;

	/*�A�[�J�C�u�t�@�C�����特����ǂݍ���*/
	MyFileInfo* texture = FileMapping::GetInstance()->GetFile(file);
	MMIOINFO mmioInfo;
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	mmioInfo.pchBuffer = (HPSTR)FileMapping::GetInstance()->GetPointer(file);
	mmioInfo.fccIOProc = FOURCC_MEM;
	mmioInfo.cchBuffer = (LONG)texture->m_FileSize;

	if (FileMapping::GetInstance()->GetPointer(file) == NULL) {
		MessageBox(NULL,
			"�Ɏ��s(SetCooprativelevel)", "���s", MB_OK);
	}

	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf = NULL;

	HMMIO hSrc = mmioOpenA(NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc) {
		MessageBox(NULL,
			"�Z�J���_���o�b�t�@�̍쐬�Ɏ��s(SetCooprativelevel)", "���s", MB_OK);
	}


	// 'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		MessageBox(NULL,
			"Wave�`�����N�G���[", "���s", MB_OK);
		mmioClose(hSrc, 0);
	}

	// 'fmt '�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	mSrcWaveFmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		MessageBox(NULL,
			"fmt�`�����N�G���[", "���s", MB_OK);
		mmioClose(hSrc, 0);
	}

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// �w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf) {
		MessageBox(NULL,
			"�w�b�_�������[", "���s", MB_OK);
		mmioClose(hSrc, 0);
	}
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	if (FAILED(mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize))) {
		MessageBox(NULL,
			"WAVE�t�H�[�}�b�g���[�h�G���[", "���s", MB_OK);
		free(wf);
		mmioClose(hSrc, 0);
	}

	// fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// data�`�����N��T��
	while (1) {
		// ����
		if (FAILED(mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0))) {
			MessageBox(NULL,
				"data�`�����N��������Ȃ�", "���s", MB_OK);
			free(wf);
			mmioClose(hSrc, 0);
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// ���̃`�����N��
		mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	// �T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	if (FAILED(pSound->CreateSoundBuffer(&dsdesc, &Secondary, NULL))) {
		MessageBox(NULL,
			"�T�E���h�o�b�t�@�̍쐬�G���[", "���s", MB_OK);
		free(wf);
		mmioClose(hSrc, 0);
	}

	// ���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	if (FAILED((Secondary)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0))) {
		MessageBox(NULL,
			"���b�N���s", "���s", MB_OK);
		free(wf);
		mmioClose(hSrc, 0);
	}

	// �f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ���b�N����
	(Secondary)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// �w�b�_�p���������J��
	free(wf);

	// WAV�����
	mmioClose(hSrc, 0);

	LONG volume = (long)(1000.0 * log10((100.0 - 99.0) / 100.0));
	Secondary->SetVolume(volume);
}

Sound::~Sound() {
	if (Secondary) {
		Secondary->Stop();
		Secondary->Release();
		printf("SoundRelease!\n");
	}
}


void Sound::Reset() {
	Secondary->SetCurrentPosition(0);
}

void Sound::Play(bool loop) {
	if (loop) { Secondary->SetCurrentPosition(0); Secondary->Play(0, 0, DSBPLAY_LOOPING); }
	else{ Secondary->SetCurrentPosition(0); Secondary->Play(0, 0, 0); }
}

void Sound::Stop() {
	Secondary->Stop();
}
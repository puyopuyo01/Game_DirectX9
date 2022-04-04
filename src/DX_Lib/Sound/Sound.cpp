#include"./Sound.h"

Sound::Sound(const char* file) {
	Secondary = NULL;

	/*アーカイブファイルから音声を読み込む*/
	MyFileInfo* texture = FileMapping::GetInstance()->GetFile(file);
	MMIOINFO mmioInfo;
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	mmioInfo.pchBuffer = (HPSTR)FileMapping::GetInstance()->GetPointer(file);
	mmioInfo.fccIOProc = FOURCC_MEM;
	mmioInfo.cchBuffer = (LONG)texture->m_FileSize;

	if (FileMapping::GetInstance()->GetPointer(file) == NULL) {
		MessageBox(NULL,
			"に失敗(SetCooprativelevel)", "失敗", MB_OK);
	}

	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf = NULL;

	HMMIO hSrc = mmioOpenA(NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc) {
		MessageBox(NULL,
			"セカンダリバッファの作成に失敗(SetCooprativelevel)", "失敗", MB_OK);
	}


	// 'WAVE'チャンクチェック
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		MessageBox(NULL,
			"Waveチャンクエラー", "失敗", MB_OK);
		mmioClose(hSrc, 0);
	}

	// 'fmt 'チャンクチェック
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	mSrcWaveFmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		MessageBox(NULL,
			"fmtチャンクエラー", "失敗", MB_OK);
		mmioClose(hSrc, 0);
	}

	// ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// ヘッダメモリ確保
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf) {
		MessageBox(NULL,
			"ヘッダメモリー", "失敗", MB_OK);
		mmioClose(hSrc, 0);
	}
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVEフォーマットのロード
	if (FAILED(mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize))) {
		MessageBox(NULL,
			"WAVEフォーマットロードエラー", "失敗", MB_OK);
		free(wf);
		mmioClose(hSrc, 0);
	}

	// fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// dataチャンクを探す
	while (1) {
		// 検索
		if (FAILED(mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0))) {
			MessageBox(NULL,
				"dataチャンクが見つからない", "失敗", MB_OK);
			free(wf);
			mmioClose(hSrc, 0);
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// 次のチャンクへ
		mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	// サウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	if (FAILED(pSound->CreateSoundBuffer(&dsdesc, &Secondary, NULL))) {
		MessageBox(NULL,
			"サウンドバッファの作成エラー", "失敗", MB_OK);
		free(wf);
		mmioClose(hSrc, 0);
	}

	// ロック開始
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	if (FAILED((Secondary)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0))) {
		MessageBox(NULL,
			"ロック失敗", "失敗", MB_OK);
		free(wf);
		mmioClose(hSrc, 0);
	}

	// データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ロック解除
	(Secondary)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// ヘッダ用メモリを開放
	free(wf);

	// WAVを閉じる
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
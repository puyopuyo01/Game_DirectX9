#pragma once
#include"State/CharacterPanel/CharacterPanelMove.h"
#include"State/CharacterPanel/CharacterPanel.h"


/*キャラクターのパネルカットインを管理するクラス*/
class CutInCharacter {
public:
	CutInCharacter(float x, float y, int in, int stay, int out,int portrate,int InDir,int StayDir,int OutDir);
	unique_ptr<PanelMove> In;
	unique_ptr<PanelMove> Stay;
	unique_ptr<PanelMove> Out;
	PanelMove* NowState;

	unique_ptr<CharacterPanel> Panel;

	bool Update();
};
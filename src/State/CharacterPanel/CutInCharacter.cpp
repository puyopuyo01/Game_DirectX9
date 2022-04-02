#include"./CutInCharacter.h"


CutInCharacter::CutInCharacter(float x,float y,int in, int stay, int out,int portrate,int InDir, int StayDir, int OutDir) {
	Panel = make_unique<CharacterPanel>(x, y, portrate);
	In = make_unique<PanelMove>(InDir,in,Panel->Width);
	Stay = make_unique<PanelMove>(StayDir, stay, Panel->Width);
	Out = make_unique<PanelMove>(OutDir, out, Panel->Width);

	In->Set(Stay.get());
	Stay->Set(Out.get());
	Out->Set(Out.get());
	NowState = In.get();
}

bool CutInCharacter::Update() {

	/*パネル状態の更新*/
	NowState = NowState->Update(Panel.get());
	if (NowState == Out.get() && NowState->Finish()) {
		return true;
	}
	return false;
}
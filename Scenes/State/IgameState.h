#pragma once
//StatePatternの基底クラス(インターフェイス型)
class GameState
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	int GetSceneNum() { return StateNo; }

	virtual  ~GameState() {};
protected:
	static int StateNo;
};

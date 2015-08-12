#pragma once
#include "Location.h"

struct NumberData
{
	bool Lines[7];
};

struct LetterData
{
	bool Lines[16];
};

struct HiScoreData
{
	int Name[3];
	unsigned int Score;
};

class HUD : public Location
{
public:
	HUD(void);

	void Setup(Scene *scene);
	void Update();
	void Add(int score);
	void LostLife(void);
	int Lives(void);
	void NewGame(void);

private:
	bool m_GameOver;
	unsigned int m_Score;
	unsigned int m_PlayerHighScore;
	unsigned int m_NextNewShipScore;
	int m_Lives;
	Scene *m_Scene;
	SceneMesh *m_Letters;
	SceneMesh *m_Numbers;

	std::string m_GameText[8];
	std::string m_SaveFileName;
	int m_GameOverLetters[9];
	Vector3 m_HitsLocation;
	Vector3 m_GameOverLocation;
	Vector3 m_GameTextLocation;
	Vector3 m_PlayerScoreLocation;
	Vector3 m_PlayerHighScoreLocation;
	Vector3 m_HighScoreListLocaiton;
	HiScoreData m_HiScores[10];
	HiScoreData m_NewHiScore;

	NumberData Numbers[10];
	Vector3 m_NumberLineStart[7];
	Vector3 m_NumberLineEnd[7];

	LetterData Letters[26];
	Vector3 m_LetterLineStart[16];
	Vector3 m_LetterLineEnd[16];

	void ProcessNumber(SceneMesh *numbers, int number, Vector3 locationStart, float size);
	void DrawNumber(SceneMesh *numbers, float location, int number, float size);
	void DrawLetter(Vector3 location, int letter, float size);
	void InitializeNumberLine(void);
	void InitializeLetterLine(void);
};


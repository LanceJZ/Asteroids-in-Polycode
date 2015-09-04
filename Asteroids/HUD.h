#pragma once
#include "Location.h"
#include <fstream>

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
	void DisplayHighScores(int list);
	void Add(int score);
	void LostLife(void);
	void NewGame(void);
	void GameOver(bool gameIsOver);
	int Lives(void);

private:
	bool m_GameOver;
	bool m_HiScoreUpdated;
	bool m_NewScore;
	int m_HighScoreRank; //The place where the new high score ranks at.
	float m_HighScoreTimer;
	float m_HighScoreTimerAmount;
	unsigned int m_Score;
	unsigned int m_PlayerHighScore;
	unsigned int m_NextNewShipScore;
	int m_Lives;
	Scene *m_Scene;
	SceneMesh *m_Letters;
	SceneMesh *m_ScoreNumbers;
	SceneMesh *m_HiScoreNumbers;
	SceneMesh *m_GameOverLetters;
	SceneMesh *m_InstructionLetters[4];

	std::string m_GameText[8];
	std::string m_SaveFileName;
	Vector3 m_HitsLocation;
	Vector3 m_GameOverLocation;
	Vector3 m_GameTextLocation[4];
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

	void SaveHighScores(void);
	void SetupTextMeshs(void);
	void ProcessNumber(SceneMesh *numbers, int number, Vector3 locationStart, float size);
	void MakeNumbersMesh(SceneMesh *numbers, float locationX, int number, float size);
	void ProcessTextLine(SceneMesh *letters, String textLine, Vector3 locationStart, float size);
	void MakeLettersMesh(SceneMesh *letters, float locationX, int letter, float size);
	void InitializeNumberLine(void);
	void InitializeLetterLine(void);
};


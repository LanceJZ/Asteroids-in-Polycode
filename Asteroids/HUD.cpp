#include "HUD.h"

HUD::HUD(void)
{
	NewGame();

	m_Letters = new SceneMesh(Mesh::LINE_MESH);
	m_Letters->setColor(1.0, 1.0, 1.0, 1.0);

	m_GameText[0] = "GAME OVER";
	m_GameText[1] = "N KEY TO START OR RESTART GAME";
	m_GameText[2] = "ARROW KEYS TO CONTROL SHIP UP FOR THRUST";
	m_GameText[3] = "LEFT CTRL KEY OR SPACE TO FIRE";
	m_GameText[4] = "RIGHT CTRL KEY FOR HYPERSPACE";
	m_GameText[5] = "HIGH SCORE HEROES";
	m_GameText[6] = "NEW HIGH SCORE";
	m_GameText[7] = "ROTATE TO SELECT LETTER FIRE KEY WHEN DONE";

	m_PlayerHighScore = 0;

	m_GameOver = true;
	m_GameOverLocation = Vector3(0, 0, 0);
	m_PlayerScoreLocation = Vector3(m_WindowWidth / 1.5, m_WindowHeight - 0.25f, 0);
	m_PlayerHighScoreLocation = Vector3(0, m_WindowHeight - 0.25f, 0);
	m_HighScoreListLocaiton = Vector3(15, 30, 0);

	InitializeNumberLine();
	InitializeLetterLine();
}

void HUD::Setup(Scene * scene)
{
	m_Scene = scene;
}

void HUD::Update()
{

}

void HUD::Add(int score)
{
	m_Score += score;

	if (m_Score > m_NextNewShipScore)
	{
		m_Lives++;
		m_NextNewShipScore += 10000;
	}

	if (m_Score > m_PlayerHighScore)
		m_PlayerHighScore = m_Score;

	m_Scene->removeEntity(m_ScoreNumbers);
	m_Scene->removeEntity(m_HiScoreNumbers);
	m_ScoreNumbers = NULL;
	m_HiScoreNumbers = NULL;
	m_ScoreNumbers = new SceneMesh(Mesh::LINE_MESH);
	m_HiScoreNumbers = new SceneMesh(Mesh::LINE_MESH);
	m_GameOverLetters = new SceneMesh(Mesh::LINE_MESH);
	m_ScoreNumbers->setColor(1.0, 1.0, 1.0, 0.95);
	m_HiScoreNumbers->setColor(1.0, 1.0, 1.0, 0.95);
	m_GameOverLetters->setColor(1.0, 1.0, 1.0, 0.95);
	ProcessNumber(m_ScoreNumbers, m_Score, m_PlayerScoreLocation, 1);
	ProcessNumber(m_HiScoreNumbers, m_PlayerHighScore, m_PlayerHighScoreLocation, 1);
}

void HUD::LostLife(void)
{
	m_Lives--;

	if (m_Lives < 1)
		m_Lives = 0;
}

int HUD::Lives(void)
{
	return m_Lives;
}

void HUD::NewGame(void)
{
	m_Lives = 4;
	m_Score = 0;
	m_NextNewShipScore = 10000;
}

void HUD::GameOver(bool gameIsOver)
{
	if (gameIsOver)
	{
		ProcessTextLine(m_GameOverLetters, m_GameText[0], m_GameOverLocation, 1);
		m_GameOverLetters->enabled = true;
		m_Scene->addChild(m_GameOverLetters);
	}
	else
	{
		m_GameOverLetters->enabled = false;
		m_Scene->removeEntity(m_GameOverLetters);
		m_GameOverLetters = NULL;
	}
}

void HUD::ProcessNumber(SceneMesh *numbers, int number, Vector3 locationStart, float size)
{
	int numberIn = number;
	float space = 0;

	do
	{
		//Make digit the modulus of 10 from number.
		int digit = numberIn % 10;
		//This sends a digit to the draw function with the location and size.
		MakeNumbersMesh(numbers, space, digit, size);
		// Dividing the int by 10, we discard the digit that was derived from the modulus operation.
		numberIn /= 10;
		// Move the location for the next digit location to the left. We start on the right hand side with the lowest digit.
		space += size * 2;
	} while (numberIn > 0);

	numbers->setPosition(locationStart);
	m_Scene->addChild(numbers);
}

void HUD::MakeNumbersMesh(SceneMesh *numbers, float location, int number, float size)
{
	if (number > -1 && number < 10)
	{
		for (int line = 0; line < 7; line++)
		{
			if (Numbers[number].Lines[line])
			{
				Number Xstart = m_NumberLineStart[line].x * size + location;
				Number Ystart = m_NumberLineStart[line].y * size;

				Number Xend = m_NumberLineEnd[line].x * size + location;
				Number Yend = m_NumberLineEnd[line].y * size;

				numbers->getMesh()->addVertex(Xstart, Ystart, 0);
				numbers->getMesh()->addVertex(Xend, Yend, 0);
			}
		}
	}	
}

void HUD::ProcessTextLine(SceneMesh * letters, String textLine, Vector3 locationStart, float size)
{
	int textSize = textLine.size();
	int space = float((-size * 3) * (textSize - 1) / 2);

	for (int letter = 0; letter < textSize; letter++)
	{
		if ((int)textLine[letter] > 64 && (int)textLine[letter] < 91)
			MakeLettersMesh(letters, space, (int)textLine[letter] - 65, size);

		space += float(size * 3);
	}

	letters->setPosition(locationStart);
	m_Scene->addChild(letters);
}

void HUD::MakeLettersMesh(SceneMesh *letters, float location, int letter, float size)
{
	//Line LetterLine;

	if (letter > -1 && letter < 26)
	{
		for (int line = 0; line < 16; line++)
		{
			if (Letters[letter].Lines[line])
			{
				Number Xstart = m_LetterLineStart[line].x * size - location;
				Number Ystart = m_LetterLineStart[line].y * size;

				Number Xend = m_LetterLineEnd[line].x * size - location;
				Number Yend = m_LetterLineEnd[line].y * size;

				letters->getMesh()->addVertex(Xstart, Ystart, 0);
				letters->getMesh()->addVertex(Xend, Yend, 0);
			}
		}
	}
}

void HUD::InitializeNumberLine(void)
{
	// LED Grid location of line start and end points. 0, 0 is the top left corner.
	//The left of screen, positive X is the direction for rotation zero.
	//The top of the screen, positive Y is the direction for rotation zero.
	m_NumberLineStart[0] = Vector3(0, 0, 0);
	m_NumberLineStart[1] = Vector3(-1, 0, 0);
	m_NumberLineStart[2] = Vector3(-1, -1, 0);
	m_NumberLineStart[3] = Vector3(0, -2, 0);
	m_NumberLineStart[4] = Vector3(0, -1, 0);
	m_NumberLineStart[5] = Vector3(0, 0, 0);
	m_NumberLineStart[6] = Vector3(0, -1, 0);

	m_NumberLineEnd[0] = Vector3(-1, 0, 0);
	m_NumberLineEnd[1] = Vector3(-1, -1, 0);
	m_NumberLineEnd[2] = Vector3(-1, -2, 0);
	m_NumberLineEnd[3] = Vector3(-1, -2, 0);
	m_NumberLineEnd[4] = Vector3(0, -2, 0);
	m_NumberLineEnd[5] = Vector3(0, -1, 0);
	m_NumberLineEnd[6] = Vector3(-1, -1, 0);

	// LED Grid, what lines are on for each number.
	// Line 0 is the top line.
	// Line 1 is upper right side line.
	// Line 2 is lower right side line.
	// Line 3 is bottom line.
	// Line 4 is lower left side line.
	// Line 5 is upper left side line.
	// Line 6 is the middle line.

	Numbers[0].Lines[0] = true;
	Numbers[0].Lines[1] = true;
	Numbers[0].Lines[2] = true;
	Numbers[0].Lines[3] = true;
	Numbers[0].Lines[4] = true;
	Numbers[0].Lines[5] = true;
	Numbers[0].Lines[6] = false;

	Numbers[1].Lines[0] = false;
	Numbers[1].Lines[1] = true;
	Numbers[1].Lines[2] = true;
	Numbers[1].Lines[3] = false;
	Numbers[1].Lines[4] = false;
	Numbers[1].Lines[5] = false;
	Numbers[1].Lines[6] = false;

	Numbers[2].Lines[0] = true;
	Numbers[2].Lines[1] = true;
	Numbers[2].Lines[2] = false;
	Numbers[2].Lines[3] = true;
	Numbers[2].Lines[4] = true;
	Numbers[2].Lines[5] = false;
	Numbers[2].Lines[6] = true;

	Numbers[3].Lines[0] = true;
	Numbers[3].Lines[1] = true;
	Numbers[3].Lines[2] = true;
	Numbers[3].Lines[3] = true;
	Numbers[3].Lines[4] = false;
	Numbers[3].Lines[5] = false;
	Numbers[3].Lines[6] = true;

	Numbers[4].Lines[0] = false;
	Numbers[4].Lines[1] = true;
	Numbers[4].Lines[2] = true;
	Numbers[4].Lines[3] = false;
	Numbers[4].Lines[4] = false;
	Numbers[4].Lines[5] = true;
	Numbers[4].Lines[6] = true;

	Numbers[5].Lines[0] = true;
	Numbers[5].Lines[1] = false;
	Numbers[5].Lines[2] = true;
	Numbers[5].Lines[3] = true;
	Numbers[5].Lines[4] = false;
	Numbers[5].Lines[5] = true;
	Numbers[5].Lines[6] = true;

	Numbers[6].Lines[0] = true;
	Numbers[6].Lines[1] = false;
	Numbers[6].Lines[2] = true;
	Numbers[6].Lines[3] = true;
	Numbers[6].Lines[4] = true;
	Numbers[6].Lines[5] = true;
	Numbers[6].Lines[6] = true;

	Numbers[7].Lines[0] = true;
	Numbers[7].Lines[1] = true;
	Numbers[7].Lines[2] = true;
	Numbers[7].Lines[3] = false;
	Numbers[7].Lines[4] = false;
	Numbers[7].Lines[5] = false;
	Numbers[7].Lines[6] = false;

	Numbers[8].Lines[0] = true;
	Numbers[8].Lines[1] = true;
	Numbers[8].Lines[2] = true;
	Numbers[8].Lines[3] = true;
	Numbers[8].Lines[4] = true;
	Numbers[8].Lines[5] = true;
	Numbers[8].Lines[6] = true;

	Numbers[9].Lines[0] = true;
	Numbers[9].Lines[1] = true;
	Numbers[9].Lines[2] = true;
	Numbers[9].Lines[3] = false;
	Numbers[9].Lines[4] = false;
	Numbers[9].Lines[5] = true;
	Numbers[9].Lines[6] = true;
}

void HUD::InitializeLetterLine(void)
{
	m_LetterLineStart[0] = Vector3(0, 0, 0); //1
	m_LetterLineStart[1] = Vector3(-1, 0, 0); //2
	m_LetterLineStart[2] = Vector3(-2, 0, 0); //3
	m_LetterLineStart[3] = Vector3(-2, -2, 0); //4
	m_LetterLineStart[4] = Vector3(-1, -4, 0); //5
	m_LetterLineStart[5] = Vector3(0, -4, 0); //6
	m_LetterLineStart[6] = Vector3(0, -2, 0); //7
	m_LetterLineStart[7] = Vector3(0, 0, 0); //8
	m_LetterLineStart[8] = Vector3(0, 0, 0); //9
	m_LetterLineStart[9] = Vector3(-2, 0, 0); //10
	m_LetterLineStart[10] = Vector3(-1, -2, 0); //11
	m_LetterLineStart[11] = Vector3(-1, -2, 0); //12
	m_LetterLineStart[12] = Vector3(-1, -2, 0); //13
	m_LetterLineStart[13] = Vector3(0, -2, 0); //14
	m_LetterLineStart[14] = Vector3(-1, 0, 0); //15
	m_LetterLineStart[15] = Vector3(-1, -2, 0); //16

	m_LetterLineEnd[0] = Vector3(-1, 0, 0); //1
	m_LetterLineEnd[1] = Vector3(-2, 0, 0); //2
	m_LetterLineEnd[2] = Vector3(-2, -2, 0); //3
	m_LetterLineEnd[3] = Vector3(-2, -4, 0); //4
	m_LetterLineEnd[4] = Vector3(-2, -4, 0); //5
	m_LetterLineEnd[5] = Vector3(-1, -4, 0); //6
	m_LetterLineEnd[6] = Vector3(0, -4, 0); //7
	m_LetterLineEnd[7] = Vector3(0, -2, 0); //8
	m_LetterLineEnd[8] = Vector3(-1, -2, 0); //9
	m_LetterLineEnd[9] = Vector3(-1, -2, 0); //10
	m_LetterLineEnd[10] = Vector3(-2, -2, 0); //11
	m_LetterLineEnd[11] = Vector3(-2, -4, 0); //12
	m_LetterLineEnd[12] = Vector3(0, -4, 0); //13
	m_LetterLineEnd[13] = Vector3(-1, -2, 0); //14
	m_LetterLineEnd[14] = Vector3(-1, -2, 0); //15
	m_LetterLineEnd[15] = Vector3(-1, -4, 0); //16

	// A
	Letters[0].Lines[0] = true;
	Letters[0].Lines[1] = true;
	Letters[0].Lines[2] = true;
	Letters[0].Lines[3] = true;
	Letters[0].Lines[4] = false;
	Letters[0].Lines[5] = false;
	Letters[0].Lines[6] = true;
	Letters[0].Lines[7] = true;
	Letters[0].Lines[8] = false;
	Letters[0].Lines[9] = false;
	Letters[0].Lines[10] = true;
	Letters[0].Lines[11] = false;
	Letters[0].Lines[12] = false;
	Letters[0].Lines[13] = true;
	Letters[0].Lines[14] = false;
	Letters[0].Lines[15] = false;
	// B
	Letters[1].Lines[0] = true;
	Letters[1].Lines[1] = true;
	Letters[1].Lines[2] = true;
	Letters[1].Lines[3] = true;
	Letters[1].Lines[4] = true;
	Letters[1].Lines[5] = true;
	Letters[1].Lines[6] = false;
	Letters[1].Lines[7] = false;
	Letters[1].Lines[8] = false;
	Letters[1].Lines[9] = false;
	Letters[1].Lines[10] = true;
	Letters[1].Lines[11] = false;
	Letters[1].Lines[12] = false;
	Letters[1].Lines[13] = false;
	Letters[1].Lines[14] = true;
	Letters[1].Lines[15] = true;
	// C
	Letters[2].Lines[0] = true;
	Letters[2].Lines[1] = true;
	Letters[2].Lines[2] = false;
	Letters[2].Lines[3] = false;
	Letters[2].Lines[4] = true;
	Letters[2].Lines[5] = true;
	Letters[2].Lines[6] = true;
	Letters[2].Lines[7] = true;
	Letters[2].Lines[8] = false;
	Letters[2].Lines[9] = false;
	Letters[2].Lines[10] = false;
	Letters[2].Lines[11] = false;
	Letters[2].Lines[12] = false;
	Letters[2].Lines[13] = false;
	Letters[2].Lines[14] = false;
	Letters[2].Lines[15] = false;
	// D
	Letters[3].Lines[0] = true;
	Letters[3].Lines[1] = true;
	Letters[3].Lines[2] = true;
	Letters[3].Lines[3] = true;
	Letters[3].Lines[4] = true;
	Letters[3].Lines[5] = true;
	Letters[3].Lines[6] = false;
	Letters[3].Lines[7] = false;
	Letters[3].Lines[8] = false;
	Letters[3].Lines[9] = false;
	Letters[3].Lines[10] = false;
	Letters[3].Lines[11] = false;
	Letters[3].Lines[12] = false;
	Letters[3].Lines[13] = false;
	Letters[3].Lines[14] = true;
	Letters[3].Lines[15] = true;
	// E
	Letters[4].Lines[0] = true;
	Letters[4].Lines[1] = true;
	Letters[4].Lines[2] = false;
	Letters[4].Lines[3] = false;
	Letters[4].Lines[4] = true;
	Letters[4].Lines[5] = true;
	Letters[4].Lines[6] = true;
	Letters[4].Lines[7] = true;
	Letters[4].Lines[8] = false;
	Letters[4].Lines[9] = false;
	Letters[4].Lines[10] = false;
	Letters[4].Lines[11] = false;
	Letters[4].Lines[12] = false;
	Letters[4].Lines[13] = true;
	Letters[4].Lines[14] = false;
	Letters[4].Lines[15] = false;
	// F
	Letters[5].Lines[0] = true;
	Letters[5].Lines[1] = true;
	Letters[5].Lines[2] = false;
	Letters[5].Lines[3] = false;
	Letters[5].Lines[4] = false;
	Letters[5].Lines[5] = false;
	Letters[5].Lines[6] = true;
	Letters[5].Lines[7] = true;
	Letters[5].Lines[8] = false;
	Letters[5].Lines[9] = false;
	Letters[5].Lines[10] = false;
	Letters[5].Lines[11] = false;
	Letters[5].Lines[12] = false;
	Letters[5].Lines[13] = true;
	Letters[5].Lines[14] = false;
	Letters[5].Lines[15] = false;
	// G
	Letters[6].Lines[0] = true;
	Letters[6].Lines[1] = true;
	Letters[6].Lines[2] = false;
	Letters[6].Lines[3] = true;
	Letters[6].Lines[4] = true;
	Letters[6].Lines[5] = true;
	Letters[6].Lines[6] = true;
	Letters[6].Lines[7] = true;
	Letters[6].Lines[8] = false;
	Letters[6].Lines[9] = false;
	Letters[6].Lines[10] = true;
	Letters[6].Lines[11] = false;
	Letters[6].Lines[12] = false;
	Letters[6].Lines[13] = false;
	Letters[6].Lines[14] = false;
	Letters[6].Lines[15] = false;
	// H
	Letters[7].Lines[0] = false;
	Letters[7].Lines[1] = false;
	Letters[7].Lines[2] = true;
	Letters[7].Lines[3] = true;
	Letters[7].Lines[4] = false;
	Letters[7].Lines[5] = false;
	Letters[7].Lines[6] = true;
	Letters[7].Lines[7] = true;
	Letters[7].Lines[8] = false;
	Letters[7].Lines[9] = false;
	Letters[7].Lines[10] = true;
	Letters[7].Lines[11] = false;
	Letters[7].Lines[12] = false;
	Letters[7].Lines[13] = true;
	Letters[7].Lines[14] = false;
	Letters[7].Lines[15] = false;
	// I
	Letters[8].Lines[0] = true;
	Letters[8].Lines[1] = true;
	Letters[8].Lines[2] = false;
	Letters[8].Lines[3] = false;
	Letters[8].Lines[4] = true;
	Letters[8].Lines[5] = true;
	Letters[8].Lines[6] = false;
	Letters[8].Lines[7] = false;
	Letters[8].Lines[8] = false;
	Letters[8].Lines[9] = false;
	Letters[8].Lines[10] = false;
	Letters[8].Lines[11] = false;
	Letters[8].Lines[12] = false;
	Letters[8].Lines[13] = false;
	Letters[8].Lines[14] = true;
	Letters[8].Lines[15] = true;
	// J
	Letters[9].Lines[0] = false;
	Letters[9].Lines[1] = true;
	Letters[9].Lines[2] = true;
	Letters[9].Lines[3] = true;
	Letters[9].Lines[4] = true;
	Letters[9].Lines[5] = true;
	Letters[9].Lines[6] = true;
	Letters[9].Lines[7] = false;
	Letters[9].Lines[8] = false;
	Letters[9].Lines[9] = false;
	Letters[9].Lines[10] = false;
	Letters[9].Lines[11] = false;
	Letters[9].Lines[12] = false;
	Letters[9].Lines[13] = false;
	Letters[9].Lines[14] = false;
	Letters[9].Lines[15] = false;
	// K
	Letters[10].Lines[0] = false;
	Letters[10].Lines[1] = false;
	Letters[10].Lines[2] = false;
	Letters[10].Lines[3] = false;
	Letters[10].Lines[4] = false;
	Letters[10].Lines[5] = false;
	Letters[10].Lines[6] = true;
	Letters[10].Lines[7] = true;
	Letters[10].Lines[8] = false;
	Letters[10].Lines[9] = true;
	Letters[10].Lines[10] = false;
	Letters[10].Lines[11] = true;
	Letters[10].Lines[12] = false;
	Letters[10].Lines[13] = true;
	Letters[10].Lines[14] = false;
	Letters[10].Lines[15] = false;
	// L
	Letters[11].Lines[0] = false;
	Letters[11].Lines[1] = false;
	Letters[11].Lines[2] = false;
	Letters[11].Lines[3] = false;
	Letters[11].Lines[4] = true;
	Letters[11].Lines[5] = true;
	Letters[11].Lines[6] = true;
	Letters[11].Lines[7] = true;
	Letters[11].Lines[8] = false;
	Letters[11].Lines[9] = false;
	Letters[11].Lines[10] = false;
	Letters[11].Lines[11] = false;
	Letters[11].Lines[12] = false;
	Letters[11].Lines[13] = false;
	Letters[11].Lines[14] = false;
	Letters[11].Lines[15] = false;
	// M
	Letters[12].Lines[0] = false;
	Letters[12].Lines[1] = false;
	Letters[12].Lines[2] = true;
	Letters[12].Lines[3] = true;
	Letters[12].Lines[4] = false;
	Letters[12].Lines[5] = false;
	Letters[12].Lines[6] = true;
	Letters[12].Lines[7] = true;
	Letters[12].Lines[8] = true;
	Letters[12].Lines[9] = true;
	Letters[12].Lines[10] = false;
	Letters[12].Lines[11] = false;
	Letters[12].Lines[12] = false;
	Letters[12].Lines[13] = false;
	Letters[12].Lines[14] = false;
	Letters[12].Lines[15] = false;
	// N
	Letters[13].Lines[0] = false;
	Letters[13].Lines[1] = false;
	Letters[13].Lines[2] = true;
	Letters[13].Lines[3] = true;
	Letters[13].Lines[4] = false;
	Letters[13].Lines[5] = false;
	Letters[13].Lines[6] = true;
	Letters[13].Lines[7] = true;
	Letters[13].Lines[8] = true;
	Letters[13].Lines[9] = false;
	Letters[13].Lines[10] = false;
	Letters[13].Lines[11] = true;
	Letters[13].Lines[12] = false;
	Letters[13].Lines[13] = false;
	Letters[13].Lines[14] = false;
	Letters[13].Lines[15] = false;
	// O
	Letters[14].Lines[0] = true;
	Letters[14].Lines[1] = true;
	Letters[14].Lines[2] = true;
	Letters[14].Lines[3] = true;
	Letters[14].Lines[4] = true;
	Letters[14].Lines[5] = true;
	Letters[14].Lines[6] = true;
	Letters[14].Lines[7] = true;
	Letters[14].Lines[8] = false;
	Letters[14].Lines[9] = false;
	Letters[14].Lines[10] = false;
	Letters[14].Lines[11] = false;
	Letters[14].Lines[12] = false;
	Letters[14].Lines[13] = false;
	Letters[14].Lines[14] = false;
	Letters[14].Lines[15] = false;
	// P
	Letters[15].Lines[0] = true;
	Letters[15].Lines[1] = true;
	Letters[15].Lines[2] = true;
	Letters[15].Lines[3] = false;
	Letters[15].Lines[4] = false;
	Letters[15].Lines[5] = false;
	Letters[15].Lines[6] = true;
	Letters[15].Lines[7] = true;
	Letters[15].Lines[8] = false;
	Letters[15].Lines[9] = false;
	Letters[15].Lines[10] = true;
	Letters[15].Lines[11] = false;
	Letters[15].Lines[12] = false;
	Letters[15].Lines[13] = true;
	Letters[15].Lines[14] = false;
	Letters[15].Lines[15] = false;
	// Q
	Letters[16].Lines[0] = true;
	Letters[16].Lines[1] = true;
	Letters[16].Lines[2] = true;
	Letters[16].Lines[3] = true;
	Letters[16].Lines[4] = true;
	Letters[16].Lines[5] = true;
	Letters[16].Lines[6] = true;
	Letters[16].Lines[7] = true;
	Letters[16].Lines[8] = false;
	Letters[16].Lines[9] = false;
	Letters[16].Lines[10] = false;
	Letters[16].Lines[11] = true;
	Letters[16].Lines[12] = false;
	Letters[16].Lines[13] = false;
	Letters[16].Lines[14] = false;
	Letters[16].Lines[15] = false;
	// R
	Letters[17].Lines[0] = true;
	Letters[17].Lines[1] = true;
	Letters[17].Lines[2] = true;
	Letters[17].Lines[3] = false;
	Letters[17].Lines[4] = false;
	Letters[17].Lines[5] = false;
	Letters[17].Lines[6] = true;
	Letters[17].Lines[7] = true;
	Letters[17].Lines[8] = false;
	Letters[17].Lines[9] = false;
	Letters[17].Lines[10] = true;
	Letters[17].Lines[11] = true;
	Letters[17].Lines[12] = false;
	Letters[17].Lines[13] = true;
	Letters[17].Lines[14] = false;
	Letters[17].Lines[15] = false;
	// S
	Letters[18].Lines[0] = true;
	Letters[18].Lines[1] = true;
	Letters[18].Lines[2] = false;
	Letters[18].Lines[3] = true;
	Letters[18].Lines[4] = true;
	Letters[18].Lines[5] = true;
	Letters[18].Lines[6] = false;
	Letters[18].Lines[7] = true;
	Letters[18].Lines[8] = false;
	Letters[18].Lines[9] = false;
	Letters[18].Lines[10] = true;
	Letters[18].Lines[11] = false;
	Letters[18].Lines[12] = false;
	Letters[18].Lines[13] = true;
	Letters[18].Lines[14] = false;
	Letters[18].Lines[15] = false;
	// T
	Letters[19].Lines[0] = true;
	Letters[19].Lines[1] = true;
	Letters[19].Lines[2] = false;
	Letters[19].Lines[3] = false;
	Letters[19].Lines[4] = false;
	Letters[19].Lines[5] = false;
	Letters[19].Lines[6] = false;
	Letters[19].Lines[7] = false;
	Letters[19].Lines[8] = false;
	Letters[19].Lines[9] = false;
	Letters[19].Lines[10] = false;
	Letters[19].Lines[11] = false;
	Letters[19].Lines[12] = false;
	Letters[19].Lines[13] = false;
	Letters[19].Lines[14] = true;
	Letters[19].Lines[15] = true;
	// U
	Letters[20].Lines[0] = false;
	Letters[20].Lines[1] = false;
	Letters[20].Lines[2] = true;
	Letters[20].Lines[3] = true;
	Letters[20].Lines[4] = true;
	Letters[20].Lines[5] = true;
	Letters[20].Lines[6] = true;
	Letters[20].Lines[7] = true;
	Letters[20].Lines[8] = false;
	Letters[20].Lines[9] = false;
	Letters[20].Lines[10] = false;
	Letters[20].Lines[11] = false;
	Letters[20].Lines[12] = false;
	Letters[20].Lines[13] = false;
	Letters[20].Lines[14] = false;
	Letters[20].Lines[15] = false;
	// V
	Letters[21].Lines[0] = false;
	Letters[21].Lines[1] = false;
	Letters[21].Lines[2] = false;
	Letters[21].Lines[3] = false;
	Letters[21].Lines[4] = false;
	Letters[21].Lines[5] = false;
	Letters[21].Lines[6] = true;
	Letters[21].Lines[7] = true;
	Letters[21].Lines[8] = false;
	Letters[21].Lines[9] = true;
	Letters[21].Lines[10] = false;
	Letters[21].Lines[11] = false;
	Letters[21].Lines[12] = true;
	Letters[21].Lines[13] = false;
	Letters[21].Lines[14] = false;
	Letters[21].Lines[15] = false;
	// W
	Letters[22].Lines[0] = false;
	Letters[22].Lines[1] = false;
	Letters[22].Lines[2] = true;
	Letters[22].Lines[3] = true;
	Letters[22].Lines[4] = false;
	Letters[22].Lines[5] = false;
	Letters[22].Lines[6] = true;
	Letters[22].Lines[7] = true;
	Letters[22].Lines[8] = false;
	Letters[22].Lines[9] = false;
	Letters[22].Lines[10] = false;
	Letters[22].Lines[11] = true;
	Letters[22].Lines[12] = true;
	Letters[22].Lines[13] = false;
	Letters[22].Lines[14] = false;
	Letters[22].Lines[15] = false;
	// X
	Letters[23].Lines[0] = false;
	Letters[23].Lines[1] = false;
	Letters[23].Lines[2] = false;
	Letters[23].Lines[3] = false;
	Letters[23].Lines[4] = false;
	Letters[23].Lines[5] = false;
	Letters[23].Lines[6] = false;
	Letters[23].Lines[7] = false;
	Letters[23].Lines[8] = true;
	Letters[23].Lines[9] = true;
	Letters[23].Lines[10] = false;
	Letters[23].Lines[11] = true;
	Letters[23].Lines[12] = true;
	Letters[23].Lines[13] = false;
	Letters[23].Lines[14] = false;
	Letters[23].Lines[15] = false;
	// Y
	Letters[24].Lines[0] = false;
	Letters[24].Lines[1] = false;
	Letters[24].Lines[2] = false;
	Letters[24].Lines[3] = false;
	Letters[24].Lines[4] = false;
	Letters[24].Lines[5] = false;
	Letters[24].Lines[6] = false;
	Letters[24].Lines[7] = false;
	Letters[24].Lines[8] = true;
	Letters[24].Lines[9] = true;
	Letters[24].Lines[10] = false;
	Letters[24].Lines[11] = false;
	Letters[24].Lines[12] = false;
	Letters[24].Lines[13] = false;
	Letters[24].Lines[14] = false;
	Letters[24].Lines[15] = true;
	// Z
	Letters[25].Lines[0] = true;
	Letters[25].Lines[1] = true;
	Letters[25].Lines[2] = false;
	Letters[25].Lines[3] = false;
	Letters[25].Lines[4] = true;
	Letters[25].Lines[5] = true;
	Letters[25].Lines[6] = false;
	Letters[25].Lines[7] = false;
	Letters[25].Lines[8] = false;
	Letters[25].Lines[9] = true;
	Letters[25].Lines[10] = false;
	Letters[25].Lines[11] = false;
	Letters[25].Lines[12] = true;
	Letters[25].Lines[13] = false;
	Letters[25].Lines[14] = false;
	Letters[25].Lines[15] = false;
}

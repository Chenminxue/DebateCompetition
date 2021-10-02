#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include "Player.h"
using namespace std;

class ManagementSystem 
{
public:
	ManagementSystem();

	void ShowMenu();

	void ExitSystem();

	void InitSystem();

	void CreatePlayer();

	void Start();

	void Draw();

	void Contest();

	void showScore();

	void record();

	void loadRecord();

	void showRecord();

	void clearRecord();

	~ManagementSystem();

public:

	vector<int> round_1;

	vector<int> round_2;

	vector<int> victory;

	map<int, Player> m_Player;

	int m_Index;

	map<int, vector<string>> m_Record;

	bool fileIsEmpty;
};


#include "ManagementSystem.h"

ManagementSystem::ManagementSystem() 
{
	InitSystem();

	CreatePlayer();

	loadRecord();
}

ManagementSystem::~ManagementSystem()
{

}

void ManagementSystem::ShowMenu()
{
	cout << "******************************" << endl;
	cout << "********   Welcome!   ********" << endl;
	cout << "********   1. Start   ********" << endl;
	cout << "********   2. History ********" << endl;
	cout << "********   3. Clear   ********" << endl;
	cout << "********   0. Exit    ********" << endl;
	cout << "******************************" << endl;

}

void ManagementSystem::ExitSystem() 
{
	cout << "Goodbye!" << endl;
	system("pause");
	exit(0);
}

void ManagementSystem::InitSystem() 
{
	round_1.clear();
	round_2.clear();
	victory.clear();
	m_Player.clear();

	m_Index = 1;
	m_Record.clear();
}

void ManagementSystem::CreatePlayer()
{
	string nameSeed = "ABCDEFGHIJKL";
	for(int i = 0; i < nameSeed.size(); i++)
	{
		string name = "Player ";
		name += nameSeed[i];

		Player p;
		p.m_Name = name;

		for (int i = 0; i < 2; i++)
		{
			p.m_Score[i] = 0;
		}

		round_1.push_back(i + 10001);

		m_Player.insert(make_pair(i + 10001, p));
	}
}

void ManagementSystem::Start()
{
	Draw();

	Contest();

	showScore();

	m_Index++;

	Draw();
	
	Contest();

	showScore();

	record();

	InitSystem();

	CreatePlayer();

	loadRecord();

	cout << "Competition is over!" << endl;
	system("pause");
	system("cls");
}

void ManagementSystem::Draw()
{
	cout << "Round " << m_Index << " Drawing..." << endl;
	cout << "------------------------" << endl;
	cout << "New order: " << endl;

	if (m_Index == 1)
	{
		random_shuffle(round_1.begin(), round_1.end());
		for (vector<int>::iterator it = round_1.begin(); it != round_1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(round_2.begin(), round_2.end());
		for (vector<int>::iterator it = round_2.begin(); it != round_2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
	system("pause");
	cout << endl;
}

void ManagementSystem::Contest()
{
	cout << "----------Round " << m_Index << " starts.----------" << endl;

	multimap<double, int, greater<double>> groupScore;

	int num = 0;

	vector<int> v_Temp;
	if (m_Index == 1)
	{
		v_Temp = round_1;
	}
	else
	{
		v_Temp = round_2;
	}

	for (vector<int>::iterator it = v_Temp.begin(); it != v_Temp.end(); it++)
	{
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << " "; uncomment it to see the specific score
			d.push_back(score);
		}
		cout << endl;

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double) d.size();

		// cout << "ID: " << *it << "Name: " << m_Player[*it].m_Name << " Average Score: " << avg << endl;

		m_Player[*it].m_Score[m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "Group " << num / 6 << " final result." << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "ID: " << it->second << " Name: " << m_Player[it->second].m_Name << " Score: " << m_Player[it->second].m_Score[m_Index - 1] << endl;

			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (m_Index == 1)
				{
					round_2.push_back((*it).second);
				}
				else
				{
					victory.push_back((*it).second);
				}
			}

			groupScore.clear();
			cout << endl;
		}

	}
	cout << "----------Round" << m_Index << " Finished.----------" << endl;
	system("pause");
}

void ManagementSystem::showScore()
{
	cout << "----------Round " << m_Index << " Info: ----------" << endl;

	vector<int> v;
	if (m_Index == 1)
	{
		v = round_2;
	}
	else
	{
		v = victory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ID: " << *it << " Name: " << m_Player[*it].m_Name << " Score: " << m_Player[*it].m_Score[m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	ShowMenu();
}

void ManagementSystem::record()
{
	ofstream ofs;
	ofs.open("DebateCompetition.csv", ios::out | ios::app);

	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << m_Player[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "Recorded." << endl;

	fileIsEmpty = false;
}

void ManagementSystem::loadRecord()
{
	ifstream ifs("DebateCompetition.csv", ios::in);
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		// cout << "File doesn't exist." << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		// cout << "File is empty." << endl;
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	fileIsEmpty = false;
	ifs.putback(ch);
	
	string data;

	int index = 0;

	while(ifs >> data)
	{ 
		vector<string> v;

			

		// cout << data << endl;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			// cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}
		m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		//cout << it->first << "Champion is: " << it->second[0] << " Score: " << it->second[1] << endl;
	}
}

void ManagementSystem::showRecord()
{
	if(fileIsEmpty)
	{
		cout << "File doesn't exist or empty." << endl;
	}
	else
	{
		for (int i = 0; i < m_Record.size(); i++)
		{
			cout << "Competition " << i + 1
				<< " Gold winner is " << m_Record[i][0] << " and score is " << m_Record[i][1] << " "
				<< " Silver winner is " << m_Record[i][2] << " and score is " << m_Record[i][3] << " "
				<< " Bronze winner is " << m_Record[i][4] << " and score is " << m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void ManagementSystem::clearRecord()
{
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		ofstream ofs("DebateCompetition.csv", ios::trunc);
		ofs.close();
		InitSystem();
		CreatePlayer();
		loadRecord();
		cout << "Done!" << endl;
	}
	system("pause");
	system("cls");
}
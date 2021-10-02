#include "ManagementSystem.h"
#include <ctime>
int main()
{

	srand((unsigned int)time(NULL));

	ManagementSystem ms;

	//for (map<int, Player>::iterator it = ms.m_Player.begin(); it != ms.m_Player.end(); it++)
	//{
	//	cout << it->first << " " << it->second.m_Name << " " << it->second.m_Score[0] << endl;
	//}


	int choice = 0;

	while(true)
	{
		ms.ShowMenu();

		cout << "Please enter your choice." << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			ms.ExitSystem();
			break;
		case 1:
			ms.Start();
			break;
		case 2:
			ms.showRecord();
			break;
		case 3:
			ms.clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
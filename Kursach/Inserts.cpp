#include <iostream>


//������ ����� ����
/*
heading;
cout << "\n\t\t\t\t\t       ���� ������ �����\n" << endl;
cout << "|!| ���� � ����� - '" << path << "';" << endl;
cout << "|!| �������� ���� - '�����';\n" << endl;
cout << "|x| �������� ����� �������� �����:" << endl;
cout << "\n   | 0 - �����;\n   | 1 - �������� ����\n   | 2 - �������� ����������� �����;\n   | 3 - ���������� �����;\n\n$->: ";
*/


// ��������� ������� ���������� � �������������� � ����������
/*
void sysInfo()
{
	heading();
	cout << "\n\t\t\t\t\t   ���������� � ���������:\n" << endl;
	cout << " - ����: ����������� �������������������" << endl;
	cout << " - ���� �������������� - ���������� ��������� �� �� ����������� ����������� ������ � ��������� ����� �� ����� ������" << endl;
	cout << "\n\t\t\t\t\t   ����������� ����������:\n" << endl;
	cout << " 1. ��� ���������� ��������� ������������ �������������� �������� ����������� IA-32." << endl;
	cout << " 2. ������� ������, ��������������� ��� ����������, �������� � ��������� ��������� �����." << endl;
	cout << " 3. �������� ������, ���������� � ���������� ������ ���������, ��������� � ��������� ��������� ����." << endl;
	cout << " 4. ��� ����� � ������ ���������� � ��������� ������������ ��������� ����� �������� ������." << endl;
	cout << " 5. �������� �������� ��������� ��������� ������ ���� ����������� �� ����������" << endl;
	cout << "\n\t\t\t\t\t ���������� - ���������� �.�." << endl;

	delay();
}
*/


// ����������� �������
/*
// ����� ����������� ������
int PathSelection(List <string>& filePath)
{
	int flagChose;
	do
	{
		//heading("�� �������");
		cout << "\n\t\t\t\t\t   ������ ����������� ������:\n" << endl;
		cout << "|x| �������� ������ ����:\n" << endl;
		for (int i = 0; i < filePath.getSize(); i++)
		{
			cout << "\n | " << i + 1 << " - " << filePath[i] << ";" << endl;
		}
		cout << "\n\n$->: ";

		// �������� �� ���� �����
		if (!(cin >> flagChose))
		{
			// �������� ����� ������
			cin.clear();
			// ������� ������� ������
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}
		if (flagChose > filePath.getSize())
		{
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}
		return flagChose;
	} while (flagChose != 0);
	return flagChose;
}


// ����� ���� � �����
string pathChange(List <string>& filePath)
{
	string path = "�������� ����";
	int flagChose, pathChose;
	do
	{
		//heading("������ � ������");
		cout << "\n\t\t\t\t\t       ���� ������ �����\n" << endl;
		//cout << "|x| �������� ����� �������� �����:" << endl;
		cout << "\n   | 0 - �����;\n   | 1 - �������� ���������� ������;\n   | 2 - ���������� ������ �����;\n\n$->: ";
		// �������� �� ���� �����
		if (!(cin >> flagChose))
		{
			// �������� ����� ������
			cin.clear();
			// ������� ������� ������
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}
		switch (flagChose)
		{
			// �������� ���������� ������
		case 1:
			// �������� �� ������� ����������� ������
			if (filePath.getSize() == 0)
			{
				system("cls");
				cout << "\n|!| ����������� ������ �� ����������!\n" << endl;
				break;
			}
			system("cls");
			pathChose = PathSelection(filePath) - 1;
			if (pathChose != 0)
			{
				path = filePath[pathChose];
			}
			system("cls");
			break;
			// ���������� ������ �����
		case 2:
			system("cls");
			//heading("");
			cout << "\n\t\t\t\t\t   ���������� ����� �����\n" << endl;
			cout << "|x| ������� ����:\n\n$->: ";
			cin >> path;
			filePath.append(path);
			system("cls");
			break;
		}
	} while (flagChose != 0);
	return path;
}


// ��������� ����� � ������� ������������ ����
void autoMode()
{
	string path = "D:\\example.txt";
	int flagChose;
	do {
		//heading("�����");
		cout << "\n\t\t\t\t\t       ���� ��������� �����\n" << endl;
		cout << "|!| ���� � ����� - 'D:\\example.txt';" << endl;
		cout << "|!| �������� ���� - '�����';\n" << endl;
		cout << "|x| �������� ����� �������� �����:" << endl;
		cout << "\n   | 0 - �����;\n   | 1 - �������� ����������� �����;\n   | 2 - ���������� �����;\n\n$->: ";
		// �������� �� ���� �����
		if (!(cin >> flagChose))
		{
			// �������� ����� ������
			cin.clear();
			// ������� ������� ������
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}

		switch (flagChose)
		{
		case 1:
			system("cls");
			readFile(path);

			system("cls");
			break;
		case 2:
			break;
		}
	} while (flagChose != 0);
}


// ��������� ����� � ������� ������� ����� ���� 
void manualMode(List <string>& filePath)
{
	string path = "�������� ����";
	int flagChose, flagActive = 0;
	do
	{
		//heading(path);
		cout << "\n\t\t\t\t\t       ���� ������ �����\n" << endl;
		cout << "|!| ���� � ����� - '" << path << "';" << endl;
		cout << "|!| �������� ���� - '�����';\n" << endl;
		cout << "|x| �������� ����� �������� �����:" << endl;
		cout << "\n   | 0 - �����;\n   | 1 - �������� ����\n   | 2 - �������� ����������� �����;\n   | 3 - ���������� �����;\n\n$->: ";
		if (!(cin >> flagChose))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flagChose = -1;
			system("cls");
			cout << "\n|!| �� ����� ������������ ��������!\n" << endl;
			continue;
		}

		switch (flagChose)
		{
		case 1:
			system("cls");
			path = pathChange(filePath);
			system("cls");
			break;
		case 2:
			system("cls");
			readFile(path);
			system("cls");
			break;
		case 3:
			break;
		}
	} while (flagChose != 0);
}
*/


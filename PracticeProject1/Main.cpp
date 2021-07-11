#include "Database.h"



int main() {
	setlocale(LC_ALL, "Russian");
	Database database;
	string command;
	while (true) {
		cout << "������� ��������(0 - �����, 1 - ���������� ������, 2 - ������� �����, 3 - ������� ������): ";
		getline(cin, command);

		if (command == "0")
			exit(0);
		else if (command == "1")
			database.load();
		else if (command == "2")
			database.create();
		else if (command == "3")
			database.remove();
	}
	database.load();
	database.create();


	system("Pause");
	return 0;
}
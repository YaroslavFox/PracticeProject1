#include "Main.h"

int main() {
	setlocale(LC_ALL, "Russian");
	string command;


	char menu[] = "\n  ����: "
		"\n �������� �����           1"
		"\n ������ �����             2"
		"\n ���������� �����         3"
		"\n �������� ������ �� ����� 4"
		"\n �����                    0"
		"\n ������� �������: ";
	//char command;
	while (true) {
		database.load();
		cout <<menu ;
		
		getline(cin, command);

		if (command == "0")
			break;
		else if (command == "1")
			continue;
		else if (command == "2") {
			database.create();
		}
		else if (command == "3") {
			database.remove();

		}
		else if (command[0] == '4') {
			database.sort(command.substr(1));
			system("pause");
		}
		
		else {  }

		system("cls");

	}
	database.close();


	system("Pause");
	return 0;
}
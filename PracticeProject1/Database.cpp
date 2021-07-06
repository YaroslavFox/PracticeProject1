#include "Database.h"

void Database::create()
{
	string command;
	fstream file(database_file_name, ios::app);

	while (true) {
		cout << "Введите комманду( 0 - назад \t 1 - создать новую запись): ";
		getline(cin, command);

		if (command == "0")
			break;
		else if (command == "1") {
			TvSet set = TvSet::create();
			file << set;
			getline(cin, command);
		}
	}
	file.close();
}

void Database::load()
{
	fstream file(database_file_name, ios::in);
	int amount = 0;

	if (not file.is_open()) {
		file.open(database_file_name, ios::out | ios::binary);
		cout << "\nФайл базыданных создан\n";
		file.close();
		return;
	}
	while (not file.eof()) {
		TvSet set;
		file >> set;
		if (set.name.size() < 1)
			continue;
		cout << set << endl;
		amount++;

	}
	if (amount == 0)
		cout << "\n Записей не обнаружено\n";
	file.close();

}

void Database::seek_mark(string& name)//имя - это параметр поиска объектов для удаления
{
	{
		fstream db_file(database_file_name, ios::out | ios::in);
		print(db_file.is_open());

		db_file.seekp(0, ios::beg);
		char mark = '*';
		TvSet set;
		int set_begining = 0;
		int set_ending = 0;
		print(name);

		while ( not db_file.eof()) {
			set_begining = db_file.tellp();
			db_file >> set;
			
			if (set.name == name) {
				set_ending = db_file.tellp();
				db_file.seekp(set_begining, ios::beg);
				db_file.write(&mark, sizeof(char));
				db_file.seekp(set_ending, ios::beg);

			}
			
		}
		
		db_file.close();
	}
}

void Database::remove()
{


	string rem_name;
	fstream rem_file(delete_file_name, ios::in);
	while (rem_file.is_open() && not rem_file.eof()) {
		rem_file >> rem_name;
		seek_mark(rem_name);
	}
	rem_file.close();
	fstream db_file(database_file_name, ios::in);
	queue<TvSet> TvQueque;
	while (not db_file.eof()) {
		TvSet set;
		db_file >> set;
		print(set);
		if (set.name[0] != '*')
			TvQueque.push(set);
	}

	db_file.close();
	db_file.open(database_file_name, ios::out);

	while (not TvQueque.empty()) {
		db_file << TvQueque.front();
		TvQueque.pop();
	}
	db_file.close();


}

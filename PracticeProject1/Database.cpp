#include "Database.h"

fstream Database::file = fstream();

void Database::create()
{
	string command;
	fstream file(database_file_name, ios::app);
	file.seekp(ios::end);
	while (true) {
		cout << "Введите комманду( 0 - назад \t 1 - создать новую запись): ";
		getline(cin, command);

		if (command == "0")
			break;
		else if (command == "1") {
			TvSet set = TvSet::create();
			file << set;
		}
	}

}

void Database::load(fstream& file)
{
	file.clear();
	file.seekg(0);

	int amount = 0;
	print(header);
	if (not file.is_open()) {
		cout << "\nОшибка открытия\n";
		return;
	}
	while (not file.eof()) {
		TvSet set;
		file >> set;
		if (set.name.size() < 1)
			break;
		cout << set << line_separator;
		amount++;

	}
	if (amount == 0)
		cout << "\n Записей не обнаружено\n";


}

void Database::seek_mark(fstream& db_file, string& name)//имя - это параметр поиска объектов для удаления
{
	{
		
		//fstream db_file(temp_database, ios::out | ios::in);
		db_file.clear();
		db_file.seekp(0, ios::beg);
		char mark = '*';
		TvSet set;
		streamoff set_begining = 0;
		streamoff set_ending = 0;

		while ( not db_file.eof()) {
			set_begining = db_file.tellp();
			db_file >> set;
			
			if (set.manufacturer == name) {
				set_ending = db_file.tellp();
				db_file.seekp(set_begining, ios::beg);
				db_file.write(&mark, sizeof(char));
				db_file.seekp(set_ending, ios::beg);
			}	
		}
		
	}
}

void Database::remove()
{
	string rem_name;
	fstream rem_file(delete_file_name, ios::in);
	DeleteFile(L"temp.bin");
	CopyFile(L"data.bin", L"temp.bin", true);

	fstream temp_file(temp_database, ios::binary | ios::in | ios::out);
	while (rem_file.is_open() && not rem_file.eof()) {
		getline(rem_file, rem_name);
		everyone_loves_cpp::trim(rem_name);

		seek_mark(temp_file, rem_name);
		temp_file.clear();
		temp_file.seekg(0);
	}
	rem_file.close();
	//load(temp_file);
	temp_file.clear();
	temp_file.seekg(0);
	queue<TvSet> ShipsQueque;
	while (not temp_file.eof()) {
		TvSet set;
		temp_file >> set;
		if (set.name[0] != '*') 
			ShipsQueque.push(set);
	}
	
	temp_file.close();
	temp_file.open(temp_database, ios::binary | ios::out);

	while (not ShipsQueque.empty()) {
		temp_file << ShipsQueque.front();
		ShipsQueque.pop();
	}
	temp_file.close();
	load(temp_database);
	string command;
	while (true) {
		cout << "Сохранить изменения 0 - нет 1 - да: ";
		getline(cin, command);
		if (command == "0") {
			break;
		}
		else if (command == "1") {
			file.close();
			DeleteFile(L"data.bin");
			if(not CopyFile(L"temp.bin", L"data.bin", true))
				print("Ошибка записи. \n Изменения не внесены");
			open();
			break;
		}

	}
	temp_file.close();


}

void Database::sort(string file_name )
{
	bool new_created = false;
	fstream *file;
	if (not file_name.size())
		file = &this->file;
	else {
		new_created = true;
		print("Файл до сортировки: ");
		file = new fstream(file_name, ios::in);
		load(*file);
		
	}
	string command;
	int amount = 0;
	vector<TvSet> sets;
	if (not file->is_open()) {
		file->open(file_name, ios::out | ios::binary);
		cout << "\nФайл базыданных создан\n";
		file->close();
		return;
	}

	file->clear();
	file->seekg(0);
	while (not file->eof()) {
		TvSet set;
		*file >> set;
		if (set.name.size() < 1)
			continue;
		sets.push_back(set);
		amount++;

	}
	if (amount == 0) {
		cout << "\n Записей не обнаружено\n";
		return;
	}

	bool (*f)(TvSet&, TvSet&);

	while (true) {
		cout << "Введите комманду(Выберети параметр сортировки 1 -  по имени, 2 - по количеству на складе \n 0 - отмена ): ";
		getline(cin, command);
		if (command == "0")
			break;
		else if (command == "1")
			f = [](TvSet& ship1, TvSet& ship2)->bool {return ship1.name > ship2.name; };
		else if (command == "2")
			f = [](TvSet& ship1, TvSet& ship2)->bool {return ship1.amount < ship2.amount; };
		else continue;

		quickSort(sets, 0, sets.size() - 1, f);
		break;
	}
	file->clear();
	file->seekg(0);
	for (TvSet ship : sets) 
		*file << ship;
	print("Файл после сортировки: ");
	if (new_created) {
		file->close();
		load(*file);

	}
}

void Database::quickSort(vector<TvSet>& ships, int first_index, int last_index, bool (*f)(TvSet&, TvSet&))
{
	
	if (first_index < last_index)
	{
		int pivot = partition(ships, first_index, last_index, f);
		quickSort(ships, first_index, pivot - 1, f);
		quickSort(ships, pivot + 1, last_index, f);
	}
}


int Database::partition(vector<TvSet>& ships, int first_index, int last_index, bool (*f)(TvSet&, TvSet&))
{
	TvSet pivot = ships[last_index];
	int i = (first_index - 1);

	for (int j = first_index; j <= last_index - 1; j++)
	{
		
		if (f(ships[j], pivot))
		{
			i++; 

			swap(ships[i], ships[j]);
		}
	}
	swap(ships[i + 1], ships[last_index]);
	return (i + 1);
}

void everyone_loves_cpp::trim(string& str)
{
	str.insert(0, " ");
	str.append("   ");
	short beg_s = 0;
	short end_s = 0;
	for (unsigned int i = 0; i < str.size(); i++)
		if (str[i] != ' '  && not beg_s)
			beg_s = i;
		else if (str[str.size() - 1 - i] != ' ' && not end_s)
			end_s = i;
	str = str.substr(beg_s, str.size() - end_s - beg_s);

}

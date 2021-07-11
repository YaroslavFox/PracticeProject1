#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
#include <vector>
#include <iomanip>
#include <Windows.h>


using namespace std;
const char separator = '|';
const int size_of_separator = sizeof(separator);
const string header = 
" ------------------------------------------------------------------------------------- \n"
"| Наименование | Фирма изготовител | Стоимость | Размер экрана | Количество на складе |\n"
" ------------------------------------------------------------------------------------- ";
const string input_header = "Наименование  Фирма изготовител  Стоимость  Размер экрана  Количество на складе";
const string line_separator = "\n ------------------------------------------------------------------------------------- \n";
const fstream log_file;
namespace everyone_loves_cpp {
	void trim(string& str);
}


template<typename Type>
void print(Type arg = NULL) {
	cout << arg << "\n";
}


struct TvSet {
	string name;
	string manufacturer;
	float cost;
	int screen_size;
	int amount;


	friend fstream& operator<<(fstream& file, TvSet& tv) {

		file.write(tv.name.c_str(), tv.name.size());
		file.write(&separator, size_of_separator);

		file.write(tv.manufacturer.c_str(), tv.manufacturer.size());
		file.write(&separator, size_of_separator);

		file.write((char*)&tv.cost, sizeof(tv.cost));
		file.write((char*)&tv.screen_size, sizeof(tv.screen_size));
		file.write((char*)&tv.amount, sizeof(tv.amount));
		return file;
	}

	friend fstream& operator>>(fstream& file, TvSet& tv) {
		getline(file, tv.name, '|');
		getline(file, tv.manufacturer, '|');

		file.read((char*)&tv.cost, sizeof(tv.cost));
		file.read((char*)&tv.screen_size, sizeof(tv.screen_size));
		file.read((char*)&tv.amount, sizeof(tv.amount));
		return file;
	}

	friend ostream& operator<<(ostream& stream, TvSet set) {
		stream<< separator << left
			<< setw(14) << set.name << separator
			<< setw(19) << set.manufacturer.substr(0, set.manufacturer.size()) << separator
			<< setw(11) << set.cost << separator 
			<< setw(15) << set.screen_size << separator 
			<< setw(22) << set.amount << separator;
		return stream;

	}

	static TvSet& create() {
		
		TvSet *set = new TvSet();
		char input[20]{};
		while (true) {
			print(input_header);
			cin.get(input, 15);
			set->name = input;
			everyone_loves_cpp::trim(set->name);
			cin.get(input, 19);
			set->manufacturer = input;
			everyone_loves_cpp::trim(set->manufacturer);

			cin >> set->cost >> set->screen_size >> set->amount;

			cin.clear();    
			cin.ignore(100, '\n');

			if (set->name.size() * set->manufacturer.size() * set->cost * set->screen_size * set->amount) break;
			print("Ошибка ввода");
			

		}
		return *set;
	}
};

class Database
{
private:
	string delete_file_name = "del.txt";
	string database_file_name = "data.bin" ;
	string temp_database = "temp.bin";
	static fstream file;

	void seek_mark(fstream& file ,string& name);
	void quickSort(vector<TvSet>& ships, int first_index, int last_index, bool (*f)(TvSet&, TvSet&));
	int partition(vector<TvSet>& ships, int first_index, int last_index, bool (*f)(TvSet&, TvSet&));
	void toBegining() {
		file.clear();
		file.seekg(0);
	}

	void open() { file.open(database_file_name, ios::binary | ios::in | ios::out); }
public:
	Database() { open(); }
	~Database() { file.close(); }
	void create();
	void load(fstream& file = file);
	void load(string& name) { fstream temp_file(temp_database, ios::binary | ios::in); load(temp_file); temp_file.close(); };
	void remove();
	void sort(string file_name = "");
	void close() { file.close(); }

};



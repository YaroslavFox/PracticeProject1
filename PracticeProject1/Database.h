#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

const char separator = '|';
const int size_of_separator = sizeof(separator);


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

		file.write(tv.manufacturer.c_str(), tv.name.size());
		file.write(&separator, size_of_separator);

		file.write((char*) &tv.cost, sizeof(tv.cost));
		file.write((char*) &tv.screen_size, sizeof(tv.screen_size));
		file.write((char*) &tv.amount, sizeof(tv.amount));
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

	friend ostream& operator<<(ostream& stream, TvSet tv) {
		stream << "name: " << tv.name 
			<< " manufactorer: " << tv.manufacturer 
			<< " cost: " << tv.cost 
			<< " screen size: " << tv.screen_size 
			<< " amount: " << tv.amount << "\n";
		return stream;

	}

	static TvSet& create() {
		TvSet *set = new TvSet();
		cout << endl << "¬ведите наименование: ";
		getline(cin, set->name);


		cout << endl << "¬ведите изготовител€: ";
		getline(cin, set->manufacturer);

		cout << endl << "¬ведите цену: ";
		cin >> set->cost;

		cout << endl << "¬ведите разрешение экрана: ";
		cin >> set->screen_size;

		cout << endl << "¬ведите колличество на складе : ";
		cin >> set->amount;

		return *set;
	}
};

class Database
{
private:
	string delete_file_name = "del.txt";
	string database_file_name = "data.bin";
	void seek_mark(string& name);
public:
	void create();
	void load();
	void remove();€
};
#include "Database.h"

Database database;

namespace Funcs {
	void create() {  }//database.create();
	void remove() { }// database.remove();
	void sort() {  };//database.sort();
}
void(*funcs[3]) = {Funcs::create, Funcs::sort, Funcs::remove};

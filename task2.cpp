#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

// number_to_string :)
template <typename T>
	string number_to_string(T value) {
		ostringstream stream;
		stream.precision(2);
		stream << fixed << value;
		return stream.str();
	}

string fixed_output(string, int = 15);
string fixed_output(int, int = 15);
string fixed_output(double, int = 15);

struct worker {
	int id;
	int workplace_id;
	string surname;
	double salary;
	worker(int _id = 1, int _workplace_id = 1, string _surname = "test", double _salary = 5) {
		id = _id; 
		workplace_id = _workplace_id;
		surname = _surname;
		salary = _salary;
	}
};


// add element to dynamic array;

void add_element(worker* &database, int& database_len, worker temp) {
	worker* buffer = new worker[database_len];
	for (int i = 0; i < database_len; i++) {
		buffer[i] = database[i];
	}

	database = new worker[database_len+1];
	for (int i = 0; i < database_len; i++) {
		database[i] = buffer[i];
	}

	database[database_len] = temp;
	database_len++;
}


// command line interface (CLI)

void hello();
void menu();
void input_error();
void goodbye();
void enter_surname();
void enter_worker_id();
void enter_workplace_id();
void enter_salary();
void enter_worker(worker &temp);
void table_line();
void table_head();
void table_line_group();
void table_head_group();
void database_row(worker person);
void database_row_group(worker person);


signed main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

	char key;
	int database_len = 5;
	worker* database = new worker[5] { 
		worker(1, 1, string("Administrator"), 9999),
		worker(2, 2, string("Draevich"), 999),
		worker(3, 2, string("Volkov"), 100),
		worker(4, 3, string("Ivanov"), 50),
		worker(5, 3, string("Kuraev"), 60)
	};

	hello();
	while (true) {
		menu();

		cin.clear();
		cin >> key;

		switch (key) {
			case '0': {  // add a worker
				worker temp;
				enter_worker(temp);
				add_element(database, database_len, temp);
			
				break;
			}
			case '1': {  // just print
				table_line();
				table_head();
				table_line();
				for (int i = 0; i < database_len; i++) {
					database_row(database[i]);
				}
				table_line();
				break;
			}
			case '2': {  // group by production
				worker* temp_database = new worker[database_len];
				copy(database, database+database_len, temp_database);

				bool flag = true;
				for (int i = 0; i < database_len && flag; i++) {
					flag = false;
					for (int j = 0; j < database_len-1-i; j++) {
						if (temp_database[j].workplace_id < temp_database[j+1].workplace_id) {
							swap(temp_database[j], temp_database[j+1]);
							flag = true;
						}
					}
				}

				int key = 0;
				if (database_len > 0) {
					temp_database[key].surname = "[...]";
					temp_database[key].id = 1;
					for (int i = 1; i < database_len; i++) {
						if (temp_database[i].workplace_id == temp_database[key].workplace_id) {
							temp_database[key].salary += temp_database[i].salary;  // add salary
							temp_database[key].id++;  // add count of workers
							temp_database[i].workplace_id = -1;
						} else {
							temp_database[key].salary /= temp_database[key].id;
							key = i;
							
							temp_database[key].surname = "[...]";
							temp_database[key].id = 1;
						}
					}	temp_database[key].salary /= temp_database[key].id;
				}

				table_line_group();
				table_head_group();
				table_line_group();
				for (int i = 0; i < database_len; i++) {
					if (temp_database[i].workplace_id != -1) {
						database_row_group(temp_database[i]);
					}
				}
				table_line_group();
				break;
			}
			case '3': {  // print specific production 
				int production;
				
				enter_workplace_id();
				cin >> production; 

				table_line();
				table_head();
				table_line();
				for (int i = 0; i < database_len; i++) {
					if (database[i].workplace_id == production) {
						database_row(database[i]);
					}
				}
				table_line();
				break;
			}
			case '4':  // just goodbye
				goodbye(); 
				return 0;
				break;
			default: 
				input_error(); 
				break;
		}
	}

	return 0;
}


// output functions

string fixed_output(string value, int size) {
	string temp = value;
	while (temp.length() < size) {
		temp.append(" ");
		temp.insert(0, " ");
	}
	return temp.substr(0, size);
}
string fixed_output(int value, int size) {
	return fixed_output(number_to_string<int>(value), size);
}
string fixed_output(double value, int size) {
	return fixed_output(number_to_string<double>(value), size);
}


void hello() {
	cout << "Добро пожаловать, администратор!\n";
}
void menu() {
	cout << "\n0: Добавить работника в базу;\n1: Вывести всю базу;\n2: Вывести всю базу с группировкой по цехам;\n3: Вывести всю базу указанного цеха;\n\n4: Выход.\n\nВыберите опцию: ";
}
void input_error() {
	cout << "Проверьте ввод команды!\n";
}
void goodbye() {
	cout << "Всего хорошего!\n";
}
void enter_surname() {
	cout << "(Фамилия): ";
}
void enter_worker_id() {
	cout << "(Идентификатор работника): ";
}
void enter_workplace_id() {
	cout << "(Идентификатор цеха): ";
}
void enter_salary() {
	cout << "(Зарплата): ";
}


void table_line() {
	cout << "----------------------------------------------------------------------" << endl;
}
void table_head() {
	cout << "|" << fixed_output("Workplace") << "|" << fixed_output("Worker ID") << "|" << fixed_output("Surname", 20) << "|" << fixed_output("Salary ($)") << "|\n";
}


void table_line_group() {
	cout << "--------------------------------------------------------------------------------------" << endl;
}
void table_head_group() {
	cout << "|" << fixed_output("Workplace") << "|" << fixed_output("Amount of workers", 23) << "|" << fixed_output("Surnames", 20) << "|" << fixed_output("Average salary ($)", 23) << "|\n";
}


void database_row(worker person) {
	cout << "|" << fixed_output(person.workplace_id) << "|" << fixed_output(person.id) << "|" << fixed_output(person.surname, 20) << "|" << fixed_output(person.salary) << "|\n";
}
void database_row_group(worker person) {
	cout << "|" << fixed_output(person.workplace_id) << "|" << fixed_output(person.id, 23) << "|" << fixed_output(person.surname, 20) << "|" << fixed_output(person.salary, 23) << "|\n";
}


void enter_worker(worker &temp) {
	enter_surname();
	cin >> temp.surname;
	
	enter_worker_id();
	cin >> temp.id;
	
	enter_workplace_id();
	cin >> temp.workplace_id;

	enter_salary();
	cin >> temp.salary;
}
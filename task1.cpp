#include <iostream>
#include <string.h>

using namespace std;

int process(char* init_line) {
	int count = 0;

	char* line = new char[ strlen(init_line) + 10 ];  // allocate memory for copy of init_line
	strcpy(line, init_line);  // copying init_line

	char* result = new char[ 2 * strlen(init_line) + 10];  // allocate memory for result 
	char* piece = strtok(line, " ");
	char* buffer;

	while (piece != nullptr) {
		
		buffer = new char[ strlen(piece) + 10 ];
		strcpy(buffer, piece);
		
		if (strlen(piece) % 2 == 0) {
			count++;
			strcat(buffer, "**");
		}
		
		strcat(buffer, " ");
		strcat(result, buffer);
	
		piece = strtok(NULL, " ");
	}
	strcpy(init_line, result);

	return count;
}

signed main() {

	int n;

	cout << "Enter n: ";
	cin >> n;
	cin.ignore();

	char** array = new char* [n];
	char* white_space = new char[10];
	int* counter = new int[n];

	for (int i = 0; i < n; i++) {
		array[i] = new char[50];
		cin.getline(array[i], 50);
		strcat(array[i], " ");
		counter[i] = process(array[i]);
	}	cout << endl;

	bool flag = true;
	for (int i = 0; i < n && flag; i++) {
		flag = false;
		for (int j = i+1; j < n; j++) {
			if (counter[i] < counter[j]) {
				swap(counter[i], counter[j]);
				swap(array[i], array[j]);
				flag = true;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		cout << "[" << counter[i] << "] " << array[i] << endl;
	}

	return 0;
}

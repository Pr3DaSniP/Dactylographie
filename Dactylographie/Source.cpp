#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

struct Erreur {
	char c;
	char err;
};

void afficheErreurs(const vector<Erreur>& errors) {
	cout << "Vous avez fait : " << errors.size() << " erreurs" << endl;
	if (errors.size() != 0) {
		cout << "Les erreurs que vous avez faites : \n";
		for (Erreur e : errors) {
			cout << e.err << " au lieu de " << e.c << endl;
		}
	}
}

void saveErrors(const vector<Erreur>& errors) {
	ofstream errorFile("Errors.txt");
	errorFile << "Vous avez fait : " << errors.size() << " erreurs" << endl;
	if (errors.size() != 0) {
		for (Erreur e : errors) {
			errorFile << e.err << " au lieu de " << e.c << endl;
		}
	}
	errorFile.close();
}

string loadText(const string& filename) {
	ifstream fIN(filename);
	string text = "", line;
	while (getline(fIN, line)) {
		text += line + " ";
	}
	
	fIN.close();
	return text;
}

void main() {

	clock_t start, end;
	
	string lorem = loadText("lorem.txt");
	lorem.erase(remove(lorem.begin(), lorem.end(), ' '), lorem.end());

	vector<Erreur> errors;

	start = clock();
	for (char c : lorem) {
		system("cls");
		cout << c << endl;
		char input;
		cin >> input;
		
		if (input != c) {
			cout << "Bip!!!" << endl;
			//Beep(523, 500);
			Erreur e{ c, input };
			errors.push_back(e);
		}		
	}
	end = clock();
	
	afficheErreurs(errors);
	saveErrors(errors);

	cout << "Vous avez mis : " << (end - start) / CLOCKS_PER_SEC << "s" << endl;
	
}
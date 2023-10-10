#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Person {
    string kNum;
    string lastName;
    string firstName;
    string zipCode;
};

int getNumericPart(const string& kNum) {
    return stoi(kNum.substr(1));
}

bool compareByID(const Person& a, const Person& b) {
    return getNumericPart(a.kNum) < getNumericPart(b.kNum);
}

void selectionSort(vector<Person>& array, int size) {
    int n = min(static_cast<int>(array.size()), size);

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (compareByID(array[j], array[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(array[i], array[minIndex]);
        }
    }
}

int main() {
    int size;
    cout << "Enter the number of records to sort: ";
    cin >> size;

    vector<Person> people;

    ifstream inputFile("people.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        Person person;
        istringstream iss(line);
        iss >> person.kNum >> person.lastName >> person.firstName >> person.zipCode;
        people.push_back(person);
    }

    selectionSort(people, size);

    for (int i = 0; i < size && i < people.size(); ++i) {
        cout << people[i].kNum << " "
             << people[i].lastName << " "
             << people[i].firstName << " "
             << people[i].zipCode << endl;
    }

    return 0;
}

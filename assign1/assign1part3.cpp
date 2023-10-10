#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

struct Person {
    string kNum;
    string lastName;
    string firstName;
    string zipCode;
};

bool compareName(const Person& a, const Person& b) {
    if (a.lastName == b.lastName) {
        return a.firstName < b.firstName;
    }
    return a.lastName < b.lastName;
}

int splitName(vector<Person>& array, int low, int high) {
    Person pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareName(array[j], pivot)) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}

void quickSort(vector<Person>& array, int low, int high) {
    if (low < high) {
        int pi = splitName(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

void nameSort(vector<Person>& array) {
    quickSort(array, 0, array.size() - 1);
}

int main() {
    int size;
    cout << "Enter the number of records to print: ";
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
        getline(iss, person.kNum, ',');
        getline(iss, person.lastName, ',');
        getline(iss, person.firstName, ',');
        getline(iss, person.zipCode, ',');
        people.push_back(person);
    }

    vector<Person> copiedPeople = people;

    clock_t start = clock();

    nameSort(copiedPeople);

    clock_t end = clock();
    double elapsed_time = static_cast<double>(end - start)
            / CLOCKS_PER_SEC;

    for (int i = 0; i < size && i < copiedPeople.size(); ++i) {
        cout << copiedPeople[i].kNum << ","
             << copiedPeople[i].lastName << ","
             << copiedPeople[i].firstName << ","
             << copiedPeople[i].zipCode << endl;
    }
     cout << "Time taken: " << elapsed_time << " seconds." << endl;

    return 0;
}

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

void zipSort(vector<Person>& people) {
    vector<vector<Person>> buckets(1000);

    for (const Person& person : people) {
        int bucketIndex = stoi(person.zipCode) - 97000;
        buckets[bucketIndex].push_back(person);
    }

    int index = 0;
    for (const vector<Person>& bucket : buckets) {
        for (const Person& person : bucket) {
            people[index++] = person;
        }
    }
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
        istringstream iss(line);
        Person person;
        getline(iss, person.kNum, ',');
        getline(iss, person.lastName, ',');
        getline(iss, person.firstName, ',');
        getline(iss, person.zipCode, ',');

        people.push_back(person);
    }

    vector<Person> copiedPeople = people;

    clock_t start = clock();
    zipSort(copiedPeople);
    clock_t end = clock();
    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;



    for (int i = 0; i < size && i < copiedPeople.size(); ++i) {
        cout << copiedPeople[i].kNum << " "
             << copiedPeople[i].lastName << " "
             << copiedPeople[i].firstName << " "
             << copiedPeople[i].zipCode << endl;
    }

    cout << "Time taken: " << duration << " seconds" << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;
const int NUM_SIMULATIONS = 15;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string[], string[]);
void display_trip(list<Goat> trip);

int main_menu();

int main() {
    srand(static_cast<unsigned int>time(0));
    bool again;

    double times[NUM_SIMULATIONS][4][3] = {0};

    for (int sim = 0; sim < NUM_SIMULATIONS; sim++){
        list < Goat> trip;
        int tripSize = rand() % 8 + 8;

//read
        auto start = chrono::high_resolution_clock:: now();
        for (int i = 0; i <tripSize; i++){
            int age = rand() % MAX_AGE;
            string name = names[rand() % SZ_NAMES];
            string color = colors[rand() % SZ_COLORS];
            trip.push_back();
        }
        auto end = chrono::high_resolution_clock::now();
        total_times[0][0] += chrono::duration_cast<chrono::microseconds>().count();

//sort
        start = chrono :: high_resolution_clock::now();
        trip.sort([]const Goat &a, const Goat &b){
            return a.get_name() < b.get_name();
        };
        end=chrono::high_resolution_clock::now();
        total_times[1][0] += chrono::duration_cast<chrono::microseconds>().count();

//insert 
        start = chrono:: high_resolution_clock
        add_goat(trip, names, colors);
        end = chrono::high_resolution_clock::now();
        total_times[][0] += chrono::duration_cast<chrono::microseconds>().count();

//delete
        start = chrono:: high_resolution_clock
        delete_goat(trip);
        end = chrono::high_resolution_clock::now();
        total_times[][0] += chrono:: duration_cast<chrono::microseconds>().count();

    }

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();
    
    cout << "Simulations: " << NUM_SIMULATIONS << endl;
    cout << "Operation      Vector      List        Set\n";
    for(int op= 0 && op< 4){
        cout << "   " << (op == 0 ? "Read" : op == 1 ? "Sort" : op == 2? "Insert" : "Delete") << "  ";
        for (){
            double avg_time = total_times[op][ds] / NUM_SIMULATIONS;
            cout << fixed << setprecision(2) << avg_time << "   ";
        }
        cout << endl;
    }


    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}
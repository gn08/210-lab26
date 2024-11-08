#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <chrono>
#include <cstdlib>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;
const int NUM_SIMULATIONS = 15;
//select goat
//arguements: const list<Goat> trip- list of goats
//return: int- selected goat position
int select_goat(const list<Goat> trip);
//delete goat
//agruement- list<Goat> &trip- list of goats
//return: nothing
void delete_goat(list<Goat> &trip);
// add goat
//agruement- list<Goat> &trip- list of goats, names- names, colors- colors
//return: nothing
void add_goat(list<Goat> &trip, string names[], string colors[]);
//display list goats
//arguements- const list<Goat> trip-list of goats
//returns: nothing
void display_trip(const list<Goat> trip);

int main() {
    srand(static_cast<unsigned int>(time(0)));

    long long total_times[4][3][NUM_SIMULATIONS]= {{{0}}};
    string names[SZ_NAMES];
    string colors[SZ_COLORS];

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    int i = 0;
    while (fin >> names[i] && i < SZ_NAMES){
        i++;
    }
    fin.close();

    ifstream fin1("colors.txt");
    i = 0;
    while (fin1 >> colors[i] && i < SZ_COLORS){
        i++;
    }
    fin1.close();

    for (int sim = 0; sim < NUM_SIMULATIONS; sim++){
        list < Goat> trip;
        int tripSize = rand() % 8 + 8;

//read
        auto start = chrono::high_resolution_clock:: now();
        for (int i = 0; i <tripSize; i++){
            int age = rand() % MAX_AGE;
            string name = names[rand() % SZ_NAMES];
            string color = colors[rand() % SZ_COLORS];
            trip.push_back(Goat(name, age, color));
        }
        auto end = chrono::high_resolution_clock::now();
        total_times[0][0][sim] = chrono::duration_cast<chrono::microseconds>(end- start).count();

//sort
        start = chrono :: high_resolution_clock::now();
        trip.sort([](const Goat &a, const Goat &b){
            return a.get_name() < b.get_name();
        });
        end=chrono::high_resolution_clock::now();
        total_times[1][0][sim] = chrono::duration_cast<chrono::microseconds>(end- start).count();

//insert 
        start = chrono::high_resolution_clock::now();
        add_goat(trip, names, colors);
        end = chrono::high_resolution_clock::now();
        total_times[2][0][sim] = chrono::duration_cast<chrono::microseconds>(end - start).count();

//delete
        start = chrono:: high_resolution_clock::now();
        delete_goat(trip);
        end = chrono::high_resolution_clock::now();
        total_times[3][0][sim] = chrono:: duration_cast<chrono::microseconds>(end- start).count();

    }
    
    cout << "Simulations: " << NUM_SIMULATIONS << endl;
    cout << "Operation      Vector      List        Set\n";
    for(int op= 0; op< 4; op++){
        cout << "   " << (op == 0 ? "Read" : op == 1 ? "Sort" : op == 2? "Insert" : "Delete") << "  ";
        for (int ds =0; ds<3; ds++){
            double avg_time = 0.0;
            for(int sim=0; sim< NUM_SIMULATIONS; sim++){
                avg_time += total_times[op][ds][sim];
            }

            avg_time /= NUM_SIMULATIONS;
            cout << setw(12) << avg_time;
        }
        cout << endl;
    }


    return 0;
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
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}
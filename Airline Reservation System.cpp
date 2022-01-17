#include "Functions.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
//"Seats History.txt" contains the record that how many seats are reserved till that time, 1 indicates economy seat while
//2 indicates first class seat
//"Receipt.txt" contains the boarding pass issued for customer
//"Reserved Seat.txt" contains the seat number of each seat reserved till that time seats(1-5) are in first class and
//seats(6-10) are in economy class

using namespace std;
int plane_seats[AIR] = {0};
int count1s = 0, count2s = 0;

void airSeat() {
    int type;
    readSeats();
    cout << "Welcome to IJT Airlines" << endl;
    if (count1s == 5 && count2s == 5) {
        cout << "Ticket Reservation has been closed." << endl;
        cout << "Flight#042 is ready to takeoff." << endl;
        cout << "Fasten your seatbelts." << endl;
        cout << "Next flight leaves in 3 hours." << endl;
    } else {
        cout << "You are going to book your seat in FLight#042 (Lahore to Istanbul) of IJT Airlines" << endl;
        cout << "Press 1 for First class" << endl;
        cout << "Press 2 for Economy class" << endl;
        cout << "In which class you want to book your seat:" << endl;
        cin >> type;
        switch (type) {
            case 1:
                //cout<<"You have selected First class."<<endl
                firstClass(plane_seats);
                break;
            case 2:
                economyClass(plane_seats);
                break;
        }
        return;
    }
}

void readSeats() {
    int seat, i = 0;
    ifstream read;
    read.open("Seats History.txt");
    while (read >> seat && i < AIR) {
        plane_seats[i] = seat;
        i++;
    }
    count(plane_seats);
}

void count(int temp[AIR]) {
    count1s = 0;
    count2s = 0;
    for (int i = 0; i < AIR; ++i) {
        if (temp[i] == 1) {
            count1s++;
        }
        if (temp[i] == 2) {
            count2s++;
        }
    }
    //cout << count1s << ":" << count2s << endl;
}

void firstClass(int seats[AIR]) {
    int check = 0;
    string again;
    ofstream write;
    write.open("Seats History.txt", ios::app);
    for (int i = 0; i < AIR && check == 0 && count1s != 5; ++i) {
        if (seats[i] == 0) {
            seats[i] = 1;
            check++;
            write << seats[i] << endl;
            cout << "Your seat has booked in First Class." << endl;
            passGen(seats[i]); //generates boarding pass
        }
    }
    if (check == 0) {
        cout << "First class is fully reserved, do you want to try in economy class? (Yes/No)" << endl;
        cin >> again;
        if (again == "Y" || again == "y" || again == "yes" || again == "Yes" || again == "YES") {
            economyClass(seats);
        } else cout << "Next flight leaves in 3 hours." << endl;
    }
    check = 0;
    return;
}

void economyClass(int seats[AIR]) {
    int check = 0;
    string again;
    ofstream write;
    write.open("Seats History.txt", ios::app);
    for (int i = 0; i < AIR && check == 0 && count2s != 5; ++i) {
        if (seats[i] == 0) {
            seats[i] = 2;
            check++;
            write << seats[i] << endl;
            cout << "Your seat has booked in Economy Class." << endl;
            passGen(seats[i]);
        }
    }
    if (check == 0) {
        cout << "Economy class is fully reserved, do you want to book in First class? (Yes/No)" << endl;
        cin >> again;
        if (again == "Y" || again == "y" || again == "yes" || again == "Yes" || again == "YES") {
            firstClass(seats);
        } else cout << "Next flight leaves in 3 hours." << endl;
    }
    check = 0;
    return;
}

void passGen(int type) {
    int ticket = rand() % 5000 + 1000;
    fstream seat;
    seat.open("Reserved Seats.txt", ios::app);
    fstream pass;
    pass.open("Receipt.txt", ios::out);
    cout << "Your complete boarding pass has been dispatched. You can view it in 'Receipt.txt'." << endl;
    pass << "Ticket Number: " << ticket << endl;
    pass << "Flight#042" << endl;
    if (type == 1) {
        pass << "Category: " << "First Class" << endl;
        cout << "Seat Number: " << count1s + 1 << endl;
        pass << "Seat Number: " << count1s + 1 << endl;
        seat << count1s + 1 << endl;
    } else {
        pass << "Category: " << "Economy Class" << endl;
        cout << "Seat Number: " << count2s + 6 << endl;
        pass << "Seat Number: " << count2s + 6 << endl;
        seat << count2s + 6 << endl;
    }
}
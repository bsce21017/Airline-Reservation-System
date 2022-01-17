#include <iostream>
#include "Functions.h"
using namespace std;

int main(){
    again:
    int user;
    cout<<"Enter 1 for Salesman Salary, 2 for airline ticket system, 3 for Joyland Info: ";
    cin>>user;
    switch (user) {
        case 1:
            salesmanSalary();
            break;
        case 2:
            airSeat();
            break;
        case 3:
            joyLandInfo();
            break;
    }
    cout<<"Enter 1 to reuse programs: ";
    cin>>user;
    if (user == 1){
        goto again;
    }
}

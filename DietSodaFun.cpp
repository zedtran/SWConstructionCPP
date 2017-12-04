//
// Name:            Donald Tran
// Date:            01/26/17
// AU User ID:      DZT0021
// File Name:       hw1.cpp
//  
// Instructions to compile:
// g++ -std=c++11 hw1.cpp
//

#include <iostream>
using namespace std;

int main() {
    
    const double SWEETENER = 0.001;
    double kill_amt;
    double div_1;
    double mult_1;
    double mouse_wgt;
    double dieter_wgt;
    double max_amt;
    
    cout << "What is the amount of artificial sweetener needed to kill a mouse?:" << endl;
    cin >> kill_amt;
    
    // Calculates the % of sweetener in a dose per input amount needed to kill a mouse 
    div_1 = (kill_amt/SWEETENER);
    
    cout << "\nWhat is the weight of the mouse?: ";
    cin >> mouse_wgt;
    
    // Calculates the input mouse weight per the divisor used we calculated earlier
    mult_1 = (div_1/mouse_wgt);
    
    cout << "\nWhat is the weight of the dieter?: ";
    cin >> dieter_wgt;
    
    // Calculates the maximum allowable amount the dieter can consume 
    max_amt = (dieter_wgt * mult_1);
    
    cout << "\nYou can drink " << max_amt << " diet sodas without dying as a result. " << endl;
    
    return 0;
    
}

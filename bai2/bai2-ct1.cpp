#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>

using namespace std;

string st = "";                
volatile bool isRunning = true; 
volatile bool hasNewData = false; 

void Task1_Input() {
    while (isRunning) {
        string raw_input;
        getline(cin, raw_input);

        size_t start = raw_input.find_first_not_of(" \t\n\r");
        size_t end = raw_input.find_last_not_of(" \t\n\r");

        if (start == string::npos) {
            st = ""; 
        } else {
            st = raw_input.substr(start, end - start + 1);
        }

        if (st == "bye") {
            isRunning = false; 
            break;
        } else {
            hasNewData = true; 
        }

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void Task2_Display() {
    string lastPrinted = "";

    while (isRunning) {
        if (hasNewData && !st.empty() && st != lastPrinted) {
            cout << "[Task2] Gia tri bien st: \"" << st << "\"" << endl;
            lastPrinted = st;
            hasNewData = false;
        }
        if (st == "bye") {
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
int main() {
    cout << "=== CHUONG TRINH TASK 1 VA TASK 2 KHONG DONG BO ===" << endl;
    cout << "Nhap xau ki tu (nhap 'bye' de ket thuc):" << endl;

    thread t1(Task1_Input);
    thread t2(Task2_Display);
    t1.join();
    t2.join();

    cout << "=== CHUONG TRINH KET THUC ===" << endl;
    return 0;
}
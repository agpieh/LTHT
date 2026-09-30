#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

volatile char c = '\0';
volatile bool isRunning = true;

void Timer1_Task() {
    while (isRunning) {
        char inputChar;
        cin >> inputChar;
        c = inputChar;

        cout << "Hex: 0x" << hex << uppercase << (int)(unsigned char)c << dec << endl;

        if (c == '*') {
            isRunning = false;
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void Timer2_Task() {
    while (isRunning) {
        cout << "\a" << flush;

        if (c == '*') {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(7));
    }
}

int main() {
    thread Timer1(Timer1_Task);
    thread Timer2(Timer2_Task);

    Timer1.join();
    Timer2.join();

    return 0;
}

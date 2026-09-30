#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

volatile bool isRunning = true;
volatile int sharedNum = 0;
volatile bool hasNewData = false;

void Task1_GenerateNumber() {
    while (isRunning) {
        // Sinh so nguyen ngau nhien (ghep bit de vuot RAND_MAX 32767)
        int num = ((rand() << 15) | rand()) % 50000 + 1;
        
        sharedNum = num;
        hasNewData = true;

        if (num > 10000 && num % 2021 == 0) {
        	cout << "\n==========================================" << endl;
            cout << "[Task1] DA PHAT HIEN SO THOA MAN DIEU KIEN DUNG: " << num << endl;
            cout << "        (" << num << " > 10000 va " << num << " % 2021 == 0)" << endl;
            cout << "==========================================\n" << endl;
            isRunning = false;
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

void Task2_TrackMax() {
    int max1 = INT_MIN;
    int max2 = INT_MIN;

    while (isRunning || hasNewData) {
        if (hasNewData) {
            int x = sharedNum;
            hasNewData = false;

            bool isUpdated = false;

            if (x > max1) {
                max2 = max1;
                max1 = x;
                isUpdated = true;
            } else if (x < max1 && x > max2) {
                max2 = x;
                isUpdated = true;
            }

            cout << "\a" << flush; 
            cout << "[Task2] Max 1: " << max1 << " | Max 2: ";
            if (max2 == INT_MIN) cout << "N/A";
            else cout << max2;
            cout << " (So vua nhan: " << x << ")" << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    cout << "=== KHOI CHAY TASK 1 VA TASK 2 (BAI 04) ===" << endl;
    thread t1(Task1_GenerateNumber);
    thread t2(Task2_TrackMax);
    t1.join();
    t2.join();
    cout << "=== CHUONG TRINH KET THUC ===" << endl;
    return 0;
}

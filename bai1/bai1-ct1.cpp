#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
void Ham_TaoVaGhiFile() {
    while (true) {
        int num = (rand() << 15) | rand();
        if (num < 0) {
            num = -num;
        }
        if (num % 2021 == 0) {
            ofstream outFile("dulieu.dat", ios::binary | ios::trunc);
            if (outFile.is_open()) {
                outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
                outFile.close(); // Dong file ngay sau khi ghi
            }
            cout << "[CT1] Da sinh so chia het cho 2021: " << num << " -> Thoat vong lap!" << endl;
            break; // Thoat khoi vong lap
        } 
        else {
            ofstream outFile("dulieu.dat", ios::binary | ios::trunc);
            if (outFile.is_open()) {
                outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
                outFile.close(); // Khi ghi duoc thi dong file
            }
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    cout << "=== CHUONG TRINH 1 (CT1) DANG CHAY ===" << endl;
    thread luong1(Ham_TaoVaGhiFile);
    luong1.join();
    cout << "=== CHUONG TRINH 1 KET THUC ===" << endl;
    cout << "Nhan Enter de thoat..." << endl;
    cin.get();
    return 0;
}

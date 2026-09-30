#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;
void Ham_DocFileVaHienThi() {
    int lastRead = -1; 
    while (true) {
        ifstream inFile("dulieu.dat", ios::binary);

        if (inFile.is_open()) {
            int num;
            if (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
                inFile.close(); 
                if (num != lastRead) {
                    cout << "[CT2] Gia tri doc duoc: " << num << endl; 
                    lastRead = num;
                    if (num % 2021 == 0) {
                        cout << "[CT2] So nguyen chia het cho 2021 (" << num << ") -> Thoat vong lap!" << endl;
                        break;
                    }
                }
            } else {
                inFile.close(); // Dong file neu khong doc duoc
            }
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
int main() {
    cout << "=== CHUONG TRINH 2 (CT2) DANG CHAY ===" << endl;
    thread luong2(Ham_DocFileVaHienThi);

    luong2.join();

    cout << "=== CHUONG TRINH 2 KET THUC ===" << endl;
    return 0;
}

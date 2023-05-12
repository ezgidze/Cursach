#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Crypt()
{
    srand(time(NULL));
    char* pass = new char[65];
    for (int i = 0; i < 64; ++i) {
        switch (rand() % 3) {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
        }
    }
    pass[64] = '\0';

    string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in students.txt -out students.txt.enc -pass pass:\"";
    command += pass;
    command += "\" -pbkdf2";
    int commandResult = system(command.c_str());
    

    if (remove("students.txt") != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }

    ofstream file;
    file.open("key.txt", ios::binary);
    file.write(pass, 65);
    file.close();

    command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    commandResult = system(command.c_str());
    

    if (remove("key.txt") != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }

    delete[] pass;
}

void Decrypt()
{
    string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    int commandResult = system(command.c_str());
    

    if (remove("key.txt.enc") != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }

    char* pass = new char[65];
    ifstream file;
    file.open("key.txt", ios::binary);
    file.read(pass, 65);
    file.close();
    pass[64] = '\0';

    if (remove("key.txt") != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }

    command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in students.txt.enc -out students.txt -pass pass:\"";
    command += pass;
    command += "\" -pbkdf2";
    commandResult = system(command.c_str());
    

    if (remove("students.txt.enc") != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }


    delete[] pass;
}

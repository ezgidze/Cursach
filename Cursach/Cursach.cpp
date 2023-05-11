#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

#include "Menu_and_Functions.h"
#include "ClassStudentList.h"

int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    StudentList studentList;
    studentList.loadFromFile("students.txt", studentList); // загружаем данные из файла
    int choice;
    do {
        choice = getMenuChoice();
        system("cls");
        switch (choice) {
        case 0:
            cout << "Выход из программы" << endl;
            break;
        case 1:
            displayStudents(studentList);
            break;
        case 2:
            editStudent(studentList);
            break;
        case 3:
            addStudent(studentList);
            break;
        case 4:
            removeStudent(studentList);
            break;
        case 5:
            performTask(studentList);
            break;
        default:
            system("pause");
            system("cls");
            break;
        }
    } while (choice != 0);
    studentList.saveToFile("students.txt", studentList); // сохраняем данные в файл
    return 0;
}
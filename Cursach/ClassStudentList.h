#pragma once
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "Student.h"
#include "DopFunctions.h"

// Класс для хранения списка студентов
class StudentList {
public:
    // Конструктор по умолчанию
    StudentList() {
        head = nullptr;
    }

    // Деструктор
    ~StudentList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Загрузка из файла
    void loadFromFile(string filename, StudentList& studentList) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << "Не удалось открыть файл " << filename << endl;
            return;
        }


        string line;
        while (getline(fin, line)) {
            Student student;

            student.setSurname(line);

            getline(fin, line);
            student.setName(line);

            getline(fin, line);
            student.setPatronymic(line);

            getline(fin, line);
            student.setGender(line[0]);

            getline(fin, line);
            student.setFaculty(line);

            getline(fin, line);
            student.setDepartment(line);

            getline(fin, line);
            student.setGroup(line);

            getline(fin, line);
            student.setStudentID(line);

            int day, month, year;
            fin >> day >> month >> year;
            student.setBirthDay(day);
            student.setBirthMonth(month);
            student.setBirthYear(year);

            int admissionYear;
            fin >> admissionYear;
            student.setAdmissionYear(admissionYear);

            int sessionsCount;
            fin >> sessionsCount;
            student.setSessionsCount(sessionsCount);

            getline(fin, line); // считываем конец строки после считывания количества сессий

            for (int i = 0; i < sessionsCount; i++) {
                int numberSessions;
                fin >> numberSessions;
                getline(fin, line);
                int examsCount;
                fin >> examsCount;
                getline(fin, line); // считываем конец строки после считывания количества экзаменов
                for (int j = 0; j < examsCount; j++) {
                    getline(fin, line);
                    int pos = line.find(":");
                    string examName = line.substr(0, pos);
                    string examResult = line.substr(pos + 2);
                    student.setSessionName(i, j, examName);
                    student.setSessionResult(i, j, examResult);
                }
            }

            studentList.addStudent(student);
            getline(fin, line);
        }

        fin.close();
    }

    // Загрузка в файл
    void saveToFile(string filename, StudentList& studentList) {
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            cout << "Error opening file\n";
            return;
        }
        int size = studentList.getSize();
        for (int i = 0; i < size; i++) {
            Student student = studentList.getStudent(i);
            outfile << student.getSurname() << endl;
            outfile << student.getName() << endl;
            outfile << student.getPatronymic() << endl;
            outfile << student.getGender() << endl;
            outfile << student.getFaculty() << endl;
            outfile << student.getDepartment() << endl;
            outfile << student.getGroup() << endl;
            outfile << student.getStudentID() << endl;
            outfile << student.getBirthDay() << endl;
            outfile << student.getBirthMonth() << endl;
            outfile << student.getBirthYear() << endl;
            outfile << student.getAdmissionYear() << endl;
            int sessionsCount = student.getSessionsCount();
            outfile << sessionsCount << endl;
            for (int j = 0; j < sessionsCount; j++) {
                outfile << j + 1 << endl;
                int examsCount = student.getExamsInCount(j);
                outfile << examsCount << endl;
                for (int k = 0; k < examsCount; k++) {
                    outfile << student.getExamName(j, k) << ": ";
                    outfile << student.getExamResult(j, k) << endl;
                }
            }
            outfile << endl;
        }
        outfile.close();
    }

    // Добавить студента в список
    void addStudent(Student student) {
        Node* newNode = new Node;
        newNode->student = student;
        newNode->next = head;
        head = newNode;
    }

    // Удалить студента из списка
    void removeStudent(int index) {
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    // Получить количество студентов в списке
    int getSize() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Получить студента по индексу
    Student getStudent(int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->student;
    }

    // Изменить данные о студенте
    void editStudent(int index, Student student) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->student = student;
    }

private:
    // Структура для хранения узла списка
    struct Node {
        Student student;
        Node* next;
    };

    Node* head; // Указатель на голову списка
};

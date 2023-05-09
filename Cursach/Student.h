#pragma once
#include <iostream>
using namespace std;

// Структура для хранения информации о студенте
class Student {
private:
    string surname;
    string name;
    string patronymic;
    char gender;
    string faculty;
    string department;
    string group;
    string studentID;
    int birthDay;
    int birthMonth;
    int birthYear;
    int admission_year;
    string examsNames[9][10];
    string results[9][10];
    int sessionsCount;
public:

    void setName(string name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setSurname(string surname) {
        this->surname = surname;
    }

    string getSurname() const {
        return surname;
    }

    void setPatronymic(string patronymic) {
        this->patronymic = patronymic;
    }

    string getPatronymic() const {
        return patronymic;
    }

    void setGender(char gender) {
        this->gender = gender;
    }

    char getGender() const {
        return gender;
    }

    void setFaculty(string faculty) {
        this->faculty = faculty;
    }

    string getFaculty() const {
        return faculty;
    }

    void setDepartment(string department) {
        this->department = department;
    }

    string getDepartment() const {
        return department;
    }

    void setGroup(string group) {
        this->group = group;
    }

    string getGroup() const {
        return group;
    }

    void setStudentID(string studentID) {
        this->studentID = studentID;
    }

    string getStudentID() const {
        return studentID;
    }

    void setBirthDay(int birthDay) {
        this->birthDay = birthDay;
    }

    int getBirthDay() const {
        return birthDay;
    }

    void setBirthMonth(int birthMonth) {
        this->birthMonth = birthMonth;
    }

    int getBirthMonth() const {
        return birthMonth;
    }

    void setBirthYear(int birthYear) {
        this->birthYear = birthYear;
    }

    int getBirthYear() const {
        return birthYear;
    }

    void setAdmissionYear(int admission_year) {
        this->admission_year = admission_year;
    }

    int getAdmissionYear() const {
        return admission_year;
    }

    void setSessionName(int sessionIndex, int examIndex, string name) {
        examsNames[sessionIndex][examIndex] = name;
    }

    string getSessionName(int sessionIndex, int examIndex) const {
        return examsNames[sessionIndex][examIndex];
    }

    void setSessionResult(int sessionIndex, int examIndex, string result) {
        results[sessionIndex][examIndex] = result;
    }

    string getSessionResult(int sessionIndex, int examIndex) const {
        return results[sessionIndex][examIndex];
    }

    int getSessionsCount() const {
        return sessionsCount;
    }

    void setSessionsCount(int count) {
        sessionsCount = count;
    }

    int getExamsCount() const {
        int examsCount = 0;
        int sessionsCount = getSessionsCount();
        for (int i = 0; i < sessionsCount; i++) {
            int examsInSessionCount = 0;
            for (int j = 0; j < 10; j++) {
                if (getSessionResult(i, j) != "") {
                    examsInSessionCount++;
                }
            }
            examsCount += examsInSessionCount;
        }
        return examsCount;
    }

    int getExamsInCount(int i) const {
        int examsCount = 0;
        int examsInSessionCount = 0;
        for (int j = 0; j < 10; j++) {
            if (getSessionResult(i, j) != "") {
                examsInSessionCount++;
            }
        }
        examsCount += examsInSessionCount;

        return examsCount;
    }

    string getExamResult(int j, int k) const {
        if (j >= sessionsCount || k >= 10) {
            return ""; //некорректный номер сессии или экзамена
        }
        return results[j][k];
    }

    string getExamName(int j, int k) const {
        if (j >= sessionsCount || k >= 10) {
            return ""; //некорректный номер сессии или экзамена
        }
        return examsNames[j][k];
    }
};
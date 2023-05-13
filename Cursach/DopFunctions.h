#pragma once
#include <iostream>
#include <conio.h>
using namespace std;

// Функция вывода даты
void printDate(int day, int month, int year) {
    if (day < 10) {
        cout << "0" << day << ".";
    }
    else {
        cout << day << ".";
    }
    if (month < 10) {
        cout << "0" << month << ".";
    }
    else {
        cout << month << ".";
    }
    cout << year;
}

// Проверка даты рождения
bool isValidBirthDate(int day, int month, int year) {
    if (year < 1980 || month < 1 || month > 12 || day < 1 || day > 31 || year > 2004) {
        // год должен быть положительным
        // месяц должен быть от 1 до 12
        // день должен быть от 1 до 31
        return false;
    }
    if (month == 2) {
        // февраль
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            // високосный год
            return day <= 29;
        }
        else {
            // не високосный год
            return day <= 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        // месяцы с 30 днями
        return day <= 30;
    }
    else {
        // месяцы с 31 днем
        return true;
    }
}

// Проверка на год поступления
bool isValidAdmissionYear(int year) {
    if (year > 2023 || year < 2018) {
        return false;
    }
}

// Проверка на пол 
bool GenderTest(char gender) {
    if (gender == 'М' || gender == 'Ж') {
        return true;
    }
    return false;
}

// Проверка на ввод только букв
bool Alpha(string str) {
    bool contains_only_letters = true;
    for (char c : str) {
        if (!((65 <= static_cast<int>(c) && static_cast<int>(c) <= 90) || (97 <= static_cast<int>(c) && static_cast<int>(c) <= 122) || (-200 <= static_cast<int>(c) && static_cast<int>(c) <= -1))) {
            contains_only_letters = false;
            break;
        }
    }

    if (contains_only_letters) {
        return true;
    }
    else {
        return false;
    }
}

// Проверка на ввод только цифр
bool Digital(string str) {
    bool contains_only_letters = true;
    if (str.length() > 1 && str[0] == '0') {
        contains_only_letters = false;
    }
    for (char c : str) {
        if (!(static_cast<int>(c) >= '0' && static_cast<int>(c) <= '9') && contains_only_letters == true) {
            contains_only_letters = false;
            break;
        }
    }

    if (contains_only_letters) {
        return true;
    }
    else {
        return false;
    }
}

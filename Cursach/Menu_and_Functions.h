#pragma once
using namespace std;

#include "ClassStudentList.h"
#include "DopFunctions.h"

// Функция для отображения меню и получения выбора пользователя
int getMenuChoice() {
    int choice;
    cout << "Выберите действие:" << endl;
    cout << "0) Выход из программы" << endl;
    cout << "1) Отобразить данные о студентах" << endl;
    cout << "2) Изменить данные о студентах" << endl;
    cout << "3) Добавить данные о студенте" << endl;
    cout << "4) Удалить студента" << endl;
    cout << "5) Выполнить задание" << endl;
    cin >> choice;
    return choice;
}

// Функция для отображения списка студентов
void displayStudents(StudentList& studentList) {
    int size = studentList.getSize();
    for (int i = 0; i < size; i++) {
        Student student = studentList.getStudent(i);
        cout << "Студент #" << i + 1 << ":" << endl;
        cout << "ФИО: " << student.getSurname() << " " << student.getName() << " " << student.getPatronymic() << endl;
        cout << "Пол: " << (student.getGender() == 'М' ? "Мужской" : "Женский") << endl;
        cout << "Факультет: " << student.getFaculty() << endl;
        cout << "Кафедра: " << student.getDepartment() << endl;
        cout << "Группа: " << student.getGroup() << endl;
        cout << "Зачетная книжка: " << student.getStudentID() << endl;
        cout << "Дата рождения: ";
        printDate(student.getBirthDay(), student.getBirthMonth(), student.getBirthYear());
        cout << endl;
        cout << "Год проступления: " << student.getAdmissionYear() << endl;
        int sessionsCount = student.getSessionsCount();
        for (int j = 0; j < sessionsCount; j++) {
            cout << "Сессия #" << j + 1 << ":" << endl;
            int examsCount = student.getExamsInCount(j);
            for (int k = 0; k < examsCount; k++) {
                cout << student.getExamName(j, k) << ": ";
                cout << student.getExamResult(j, k) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    system("pause");
    system("cls");
}

// Функция добавления экзаменов
void addExams(Student& student) {
    int sessionIndex;
    int sessionCount = student.getSessionsCount();
    cout << "Выберите сессию для добавления экзамена (1-" << student.getSessionsCount() + 1 << "): ";
    cin >> sessionIndex;
    if (sessionIndex < 1 || sessionIndex > student.getSessionsCount() + 1) {
        cout << "Некорректный номер сессии." << endl;
        return;
    }

    int examsCount = student.getExamsInCount(sessionIndex - 1);
    if (examsCount >= 10) {
        cout << "Достигнуто максимальное число экзаменов для этой сессии." << endl;
        return;
    }

    if (sessionIndex > sessionCount) {
        sessionCount++;
        student.setSessionsCount(sessionCount);
    }

    string examName;
    do {
        cout << "Введите название экзамена: ";
        cin >> examName;
        if (!Alpha(examName)) {
            cout << "Некорректное название экзамена. Попробуйте еще раз." << endl;
        }
    } while (!Alpha(examName));

    string examResult;
    do {
        cout << "Введите новый результат экзамена (2, 3, 4, 5, Зачет, Незачет): ";
        cin >> examResult;
        if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
            examResult != "Зачет" && examResult != "Незачет") {
            cout << "Некорректный результат экзамена. Попробуйте еще раз." << endl;
        }
    } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
        examResult != "Зачет" && examResult != "Незачет");

    student.setSessionName(sessionIndex - 1, examsCount, examName);
    student.setSessionResult(sessionIndex - 1, examsCount, examResult);

    cout << "Экзамен успешно добавлен." << endl;
}

// Функция изменения экзаменов
void editExams(Student& student) {
    int sessionIndex, examIndex;
    string strSessionIndex, strExamIndex;
    do {
        do {
            cout << "Введите номер сессии (1-" << student.getSessionsCount() << "): ";
            cin >> strSessionIndex;
            if (!Digital(strSessionIndex)) {
                cout << "Введен недоступный номер сессии. Попробуйте ещё раз. " << endl;
            }
        } while ((!Digital(strSessionIndex)));
        sessionIndex = stoi(strSessionIndex);
        if (sessionIndex > student.getSessionsCount()) {
            cout << "Введен недоступный номер сессии. Попробуйте ещё раз. " << endl;
        }
    } while (sessionIndex > student.getSessionsCount());
    sessionIndex--;
    do {
        do {
            cout << "Введите номер экзамена (1-" << student.getExamsInCount(sessionIndex) << "): ";
            cin >> strExamIndex;
            if (!Digital(strExamIndex)) {
                cout << "Введен недоступный номер экзамена. Попробуйте ещё раз. " << endl;
            }
        } while ((!Digital(strExamIndex)));
        examIndex = stoi(strExamIndex);
        if (examIndex > student.getExamsInCount(sessionIndex)) {
            cout << "Введен недоступный номер экзамена. Попробуйте ещё раз. " << endl;
        }
    } while (examIndex > student.getExamsInCount(sessionIndex));
    examIndex--;
    string examName, examResult;
    do {
        cout << "Введите новое название экзамена: ";
        cin >> examName;
        if (!(Alpha(examName))) {
            cout << "Неверено введено название экзамена. Ппоробуйте ещё раз. " << endl;
        }
    } while (!(Alpha(examName)));
    do {
        cout << "Введите новый результат экзамена (2, 3, 4, 5, Зачет, Незачет): ";
        cin >> examResult;
        if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
            examResult != "Зачет" && examResult != "Незачет") {
            cout << "Некорректный результат экзамена. Попробуйте еще раз." << endl;
        }
    } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
        examResult != "Зачет" && examResult != "Незачет");
    student.setSessionName(sessionIndex, examIndex, examName);
    student.setSessionResult(sessionIndex, examIndex, examResult);
}

// Функция для изменения данных о студенте
void editStudent(StudentList& studentList) {
    int index;
    cout << "Введите номер студента для редактирования: ";
    cin >> index;
    system("cls");
    Student student = studentList.getStudent(index - 1);
    cout << "Выбран студент #" << index << ":" << endl;
    cout << "1) Фамилия: " << student.getSurname() << endl;
    cout << "2) Имя: " << student.getName() << endl;
    cout << "3) Отчество: " << student.getPatronymic() << endl;
    cout << "4) Пол: " << (student.getGender() == 'М' ? "Мужской" : "Женский") << endl;
    cout << "5) Факультет: " << student.getFaculty() << endl;
    cout << "6) Кафедра: " << student.getDepartment() << endl;
    cout << "7) Группа: " << student.getGroup() << endl;
    cout << "8) Зачетная книжка: " << student.getStudentID() << endl;
    cout << "9) Дата рождения: ";
    printDate(student.getBirthDay(), student.getBirthMonth(), student.getBirthYear());
    cout << endl;
    cout << "10) Год поступления: " << student.getAdmissionYear() << endl;
    cout << "11) Результаты и названия экзаменов: " << endl;
    int sessionsCount = student.getSessionsCount();
    for (int j = 0; j < sessionsCount; j++) {
        cout << "Сессия #" << j + 1 << ":" << endl;
        int examsCount = student.getExamsInCount(j);
        for (int k = 0; k < examsCount; k++) {
            cout << student.getExamName(j, k) << ": ";
            cout << student.getExamResult(j, k) << " ";
        }
        cout << endl;
    }
    cout << endl;
    int choice;
    do {
        cout << "Введите номер значения, которое вы хотите изменить, или нажмите 0, чтобы ничего не изменять:  ";
        cin >> choice;
        system("cls");
        switch (choice) {
        case 0:
            break;
        case 1: {
            string newSurname;
            do {
                cout << "Введите новую фамилию: ";
                cin >> newSurname;
                if (!Alpha(newSurname)) {
                    cout << "Некорректно введена фамилия. Попробуйте еще раз." << endl;
                }
            } while (!Alpha(newSurname));
            student.setSurname(newSurname);
            choice = 0;
            break;
        }
        case 2: {
            string newName;
            do {
                cout << "Введите новое имя: ";
                cin >> newName;
                if (!Alpha(newName)) {
                    cout << "Некорректно введено имя. Попробуйте еще раз." << endl;
                }
            } while (!Alpha(newName));
            student.setName(newName);
            choice = 0;
            break;
        }
        case 3: {
            string newPatronymic;
            do {
                cout << "Введите новое отчество: ";
                cin >> newPatronymic;
                if (!Alpha(newPatronymic)) {
                    cout << "Некорректно введено отчество. Попробуйте еще раз." << endl;
                }
            } while (!Alpha(newPatronymic));
            student.setPatronymic(newPatronymic);
            choice = 0;
            break;
        }
        case 4: {
            char newGender;
            do {
                cout << "Введите пол (М/Ж): ";
                cin >> newGender;
                if (!GenderTest(newGender)) {
                    cout << "Некорректно введен пол. Попробуйте еще раз." << endl;
                }
            } while (!GenderTest(newGender));
            student.setGender(newGender);
            choice = 0;
            break;
        }
        case 5: {
            string newFaculty;
            do {
                cout << "Введите новый факультет: ";
                cin >> newFaculty;
                if (!Alpha(newFaculty)) {
                    cout << "Некорректно введен факультет. Попробуйте еще раз." << endl;
                }
            } while (!Alpha(newFaculty));
            student.setFaculty(newFaculty);
            choice = 0;
            break;
        }
        case 6: {
            string newDepartment;
            cout << "Введите новую кафедру: ";
            cin >> newDepartment;
            student.setDepartment(newDepartment);
            choice = 0;
            break;
        }
        case 7: {
            string newGroup;
            cout << "Введите новую группу: ";
            cin >> newGroup;
            student.setGroup(newGroup);
            choice = 0;
            break;
        }
        case 8: {
            string newStudentID;
            cout << "Введите новый номер зачетной книжки: ";
            cin >> newStudentID;
            student.setStudentID(newStudentID);
            choice = 0;
            break;
        }
        case 9: {
            string strNewBirthDay, strNewBirthMonth, strNewBirthYear;
            int newBirthDay, newBirthMonth, newBirthYear;
            do {
                do {
                    cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
                    cin >> strNewBirthDay >> strNewBirthMonth >> strNewBirthYear;
                    if (!Digital(strNewBirthDay) || !Digital(strNewBirthMonth) || !Digital(strNewBirthYear)) {
                        cout << "Некорректная дата. Попробуйте еще раз." << endl;
                    }
                } while (!Digital(strNewBirthDay) || !Digital(strNewBirthMonth) || !Digital(strNewBirthYear));
                newBirthDay = stoi(strNewBirthDay);
                newBirthMonth = stoi(strNewBirthMonth);
                newBirthYear = stoi(strNewBirthYear);
                if (!isValidBirthDate(newBirthDay, newBirthMonth, newBirthYear)) {
                    cout << "Некорректная дата. Попробуйте еще раз." << endl;
                }
            } while (!isValidBirthDate(newBirthDay, newBirthMonth, newBirthYear));
            student.setBirthDay(newBirthDay);
            student.setBirthMonth(newBirthMonth);
            student.setBirthYear(newBirthYear);
            choice = 0;
            break;
        }
        case 10: {
            string strNewAdmissinYear;
            int newAdmissionYear;
            do {
                do {
                    cout << "Введите год поступления: ";
                    cin >> strNewAdmissinYear;
                    if (!Digital(strNewAdmissinYear)) {
                        cout << "Некорректный год поступления. Попробуйте еще раз." << endl;
                    }
                } while (!Digital(strNewAdmissinYear));
                newAdmissionYear = stoi(strNewAdmissinYear);
                if (!isValidAdmissionYear(newAdmissionYear)) {
                    cout << "Некорректный год поступления. Попробуйте еще раз." << endl;
                }
            } while (!isValidAdmissionYear(newAdmissionYear));
            student.setAdmissionYear(newAdmissionYear);
            choice = 0;
            break;
        }
        case 11: {
            cout << "Выберите действие:" << endl;
            cout << "0) Ничего не изменять" << endl;
            cout << "1) Добавить новые экзамены" << endl;
            cout << "2) Изменить результаты и названия уже добавленных экзаменов" << endl;
            int choice1;
            do {
                cin >> choice1;
                switch (choice1) {
                case 0:
                    break;
                case 1:
                    system("cls");
                    addExams(student);
                    choice1 = 0;
                    break;
                case 2:
                    system("cls");
                    editExams(student);
                    choice1 = 0;
                    break;
                default:
                    cout << "Ошибка: неверный выбор" << endl;
                    break;
                }
            } while (choice1 != 0);
            choice = 0;
            break;
        }
        default:
            cout << "Ошибка: неверный выбор" << endl;
            break;
        }
    } while (choice != 0);
    system("cls");
    studentList.editStudent(index - 1, student);
    cout << "Данные о студенте #" << index << " изменены" << endl;
    system("pause");
    system("cls");
}

// Функция для добавления нового студента
void addStudent(StudentList& studentList) {
    Student student;

    string surname;
    do {
        cout << "Введите Фамилию: ";
        cin >> surname;
        if (!Alpha(surname)) {
            cout << "Некорректно введена фамилия. Попробуйте еще раз." << endl;
        }
    } while (!Alpha(surname));
    student.setSurname(surname);

    string name;
    do {
        cout << "Введите имя: ";
        cin >> name;
        if (!Alpha(name)) {
            cout << "Некорректно введено имя. Попробуйте еще раз." << endl;
        }
    } while (!Alpha(name));
    student.setName(name);

    string patronymic;
    do {
        cout << "Введите Отчество: ";
        cin >> patronymic;
        if (!Alpha(patronymic)) {
            cout << "Некорректно введено отчество. Попробуйте еще раз." << endl;
        }
    } while (!Alpha(patronymic));
    student.setPatronymic(patronymic);

    char gender;
    do {
        cout << "Введите пол (М/Ж): ";
        cin >> gender;
        if (!GenderTest(gender)) {
            cout << "Некорректно введен пол. Попробуйте еще раз." << endl;
        }
    } while (!GenderTest(gender));
    student.setGender(gender);

    string faculty;
    do {
        cout << "Введите факультет: ";
        cin >> faculty;
        if (!Alpha(faculty)) {
            cout << "Некорректно введен факультет. Попробуйте еще раз." << endl;
        }
    } while (!Alpha(faculty));
    student.setFaculty(faculty);

    cout << "Введите кафедру: ";
    string department;
    cin >> department;
    student.setDepartment(department);

    cout << "Введите группу: ";
    string group;
    cin >> group;
    student.setGroup(group);

    cout << "Введите номер зачетной книжки: ";
    string studentID;
    cin >> studentID;
    student.setStudentID(studentID);

    string strBirthDay, strBirthMonth, strBirthYear;
    int birthDay, birthMonth, birthYear;
    do {
        do {
            cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
            cin >> strBirthDay >> strBirthMonth >> strBirthYear;
            if (!Digital(strBirthDay) || !Digital(strBirthMonth) || !Digital(strBirthYear)) {
                cout << "Некорректная дата. Попробуйте еще раз." << endl;
            }
        } while (!Digital(strBirthDay) || !Digital(strBirthMonth) || !Digital(strBirthYear));
        birthDay = stoi(strBirthDay);
        birthMonth = stoi(strBirthMonth);
        birthYear = stoi(strBirthYear);
        if (!isValidBirthDate(birthDay, birthMonth, birthYear)) {
            cout << "Некорректная дата. Попробуйте еще раз." << endl;
        }
    } while (!isValidBirthDate(birthDay, birthMonth, birthYear));
    student.setBirthDay(birthDay);
    student.setBirthMonth(birthMonth);
    student.setBirthYear(birthYear);

    string strAdmissinYear;
    int admissionYear;
    do {
        do {
            cout << "Введите год поступления: ";
            cin >> strAdmissinYear;
            if (!Digital(strAdmissinYear)) {
                cout << "Некорректный год поступления. Попробуйте еще раз." << endl;
            }
        } while (!Digital(strAdmissinYear));
        admissionYear = stoi(strAdmissinYear);
        if (!isValidAdmissionYear(admissionYear)) {
            cout << "Некорректный год поступления. Попробуйте еще раз." << endl;
        }
    } while (!isValidAdmissionYear(admissionYear));
    student.setAdmissionYear(admissionYear);

    // Ввод результатов сессий
    int sessionsCount = 0;
    do {
        cout << "Введите количество экзаменов в сессии " << sessionsCount + 1 << " (от 1 до 10): ";
        int examsCount;
        string strExamsCount;
        cin >> strExamsCount;
        if (!Digital(strExamsCount)) {
            cout << "Нерорректное число экзаменов. Попробуйте ещё раз. " << endl;
            continue;
        }
        examsCount = stoi(strExamsCount);

        // Проверка корректности ввода количества экзаменов
        if (examsCount < 1 || examsCount > 10) {
            cout << "Некорректное количество экзаменов. Попробуйте еще раз." << endl;
            continue;
        }

        for (int i = 0; i < examsCount; i++) {
            string examName;
            do {
                cout << "Введите название экзамена " << i + 1 << ": ";
                cin >> examName;
                if (!Alpha(examName)) {
                    cout << "Некорректное название экзамена. Попробуйте еще раз." << endl;
                }
            } while (!Alpha(examName));

            string examResult;
            do {
                cout << "Введите результат экзамена " << i + 1 << " (2, 3, 4, 5, Зачет, Незачет): ";
                cin >> examResult;
                if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
                    examResult != "Зачет" && examResult != "Незачет") {
                    cout << "Некорректный результат экзамена. Попробуйте еще раз." << endl;
                }
            } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
                examResult != "Зачет" && examResult != "Незачет");
            // Установка результатов экзаменов для текущей сессии
            student.setSessionName(sessionsCount, i, examName);
            student.setSessionResult(sessionsCount, i, examResult);
        }

        sessionsCount++;
        if (sessionsCount >= 9) {
            cout << "Достигнуто максимальное количество сессий." << endl;
            break;
        }

        char choice;
        do {
            cout << "Хотите добавить еще одну сессию? (Если да - введите Д, иначе - Н): ";
            cin >> choice;
        } while (choice != 'Д' && choice != 'Н');

        if (choice == 'Н') {
            break;
        }

    } while (true);

    // Установка количества проведенных сессий
    student.setSessionsCount(sessionsCount);

    studentList.addStudent(student);
    system("cls");
    cout << "Студент добавлен" << endl;
    system("pause");
    system("cls");

}

// Функция для удаления студента
void removeStudent(StudentList& studentList) {
    int index;
    cout << "Введите номер студента для удаления: ";
    cin >> index;
    system("cls");
    studentList.removeStudent(index - 1);
    cout << "Студент #" << index << " удален" << endl;
    system("pause");
    system("cls");
}

// Функция для выполнения задания
void performTask(StudentList& studentList) {
    cout << "Выполняется задание..." << endl;
    // здесь можно написать свой код для выполнения задания
}

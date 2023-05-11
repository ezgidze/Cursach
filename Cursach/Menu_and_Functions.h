#pragma once
using namespace std;

#include "ClassStudentList.h"
#include "DopFunctions.h"

// Функция для отображения меню и получения выбора пользователя
int getMenuChoice() {
    int choice;
    string strChoice;
    cout << "Выберите действие:" << endl;
    cout << "0) Выход из программы" << endl;
    cout << "1) Отобразить данные о студентах" << endl;
    cout << "2) Изменить данные о студентах" << endl;
    cout << "3) Добавить данные о студенте" << endl;
    cout << "4) Удалить студента" << endl;
    cout << "5) Выполнить задание" << endl << endl;
    do {
        do {
            cout << "Введите значение: ";
            cin >> strChoice;
            if (!Digital(strChoice)) {
                cout << "Ошибка! Введено недопустимое значение. Попробуйте снова." << endl;
            }
        } while (!(Digital(strChoice)));
        choice = stoi(strChoice);
        if (choice > 5 || choice < 0) {
            cout << "Ошибка! Значение не входит в диапозон. Ппробуйте снова." << endl;
        }
    } while (choice > 5 || choice < 0);
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
                cout << student.getExamResult(j, k) << "; ";
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
    int sessionIndex; string strSessionIndex;
    int sessionCount = student.getSessionsCount();
    do {
        do {
            cout << "Выберите сессию для добавления экзамена (1-" << student.getSessionsCount() + 1 << "): ";
            cin >> strSessionIndex;
            if (!Digital(strSessionIndex)) {
                cout << "Ошибка! Введено недопустимое значение. Попробуйте снова. " << endl;
            }
        } while (!Digital(strSessionIndex));
        sessionIndex = stoi(strSessionIndex);

        if (sessionIndex < 1 || sessionIndex > student.getSessionsCount() + 1) {
            cout << "Ошибка! Некорректный номер сессии. Попробуйте снова. " << endl;
        }
    } while (sessionIndex < 1 || sessionIndex > student.getSessionsCount() + 1);

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
        cout << "Введите новый результат экзамена (2, 3, 4, 5, Зачет, Незачет, Не явился): ";
        cin >> examResult;
        if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
            examResult != "Зачет" && examResult != "Незачет" && examResult != "Не явился") {
            cout << "Некорректный результат экзамена. Попробуйте еще раз." << endl;
        }
    } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
        examResult != "Зачет" && examResult != "Незачет" && examResult != "Не явился");

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
        if (sessionIndex > student.getSessionsCount() || sessionIndex < 1) {
            cout << "Ошибка! Значение не входит в диапозон. Попробуйте ещё раз. " << endl;
        }
    } while (sessionIndex > student.getSessionsCount() || sessionIndex < 1);
    sessionIndex--;

    cout << "Список экзаменов в выбранной сессии:" << endl;
    for (int i = 0; i < student.getExamsInCount(sessionIndex); i++) {
        cout << i + 1 << ") " << student.getExamName(sessionIndex, i) << ": "
            << student.getExamResult(sessionIndex, i) << endl;
    }

    do {
        do {
            cout << "Введите номер экзамена (1-" << student.getExamsInCount(sessionIndex) << "): ";
            cin >> strExamIndex;
            if (!Digital(strExamIndex)) {
                cout << "Введен недоступный номер экзамена. Попробуйте ещё раз. " << endl;
            }
        } while ((!Digital(strExamIndex)));
        examIndex = stoi(strExamIndex);
        if (examIndex > student.getExamsInCount(sessionIndex) || examIndex < 1) {
            cout << "Введен недоступный номер экзамена. Попробуйте ещё раз. " << endl;
        }
    } while (examIndex > student.getExamsInCount(sessionIndex) || examIndex < 1);
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
        cout << "Введите новый результат экзамена (2, 3, 4, 5, Зачет, Незачет, Не явился): ";
        cin >> examResult;
        if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
            examResult != "Зачет" && examResult != "Незачет" && examResult != "Не явился") {
            cout << "Некорректный результат экзамена. Попробуйте еще раз." << endl;
        }
    } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
        examResult != "Зачет" && examResult != "Незачет" && examResult != "Не явился");
    student.setSessionName(sessionIndex, examIndex, examName);
    student.setSessionResult(sessionIndex, examIndex, examResult);
}

// Функция удаления экзамена
void deleteExams(Student& student) {
    int sessionsCount = student.getSessionsCount();
    if (sessionsCount == 0) {
        cout << "Нет доступных сессий для удаления экзаменов." << endl;
        return;
    }

    int sessionIndex; string strSessionIndex;
    do {
        do {
            cout << "Выберите номер сессии, из которой хотите удалить экзамен(1-" << student.getSessionsCount() << "): ";
            cin >> strSessionIndex;
            if (!Digital(strSessionIndex)) {
                cout << "Ошибка! Введено недопустимое значение. Попробуйте снова. " << endl;
            }
        } while (!Digital(strSessionIndex));
        sessionIndex = stoi(strSessionIndex);
        if (sessionIndex < 1 || sessionIndex > sessionsCount) {
            cout << "Некорректный номер сессии." << endl;
        }
    } while (sessionIndex < 1 || sessionIndex > sessionsCount);

    int examsCount = student.getExamsInCount(sessionIndex - 1);
    if (examsCount == 0) {
        cout << "В выбранной сессии нет экзаменов для удаления." << endl;
    }

    // Проверка, если сессия находится перед или между другими сессиями
    bool check = true;
    if (sessionIndex < student.getSessionsCount() && student.getExamsInCount(sessionIndex - 1) == 1) {
        cout << "В выбранной сессии находится только один экзамен и она находится перед или между другими сессиями. "
            "Удаление экзамена невозможно." << endl;
        system("pause");
        check = false;
    }

    if (check == true) {
        cout << "Список экзаменов в выбранной сессии:" << endl;
        for (int i = 0; i < examsCount; i++) {
            cout << i + 1 << ") " << student.getExamName(sessionIndex - 1, i) << ": "
                << student.getExamResult(sessionIndex - 1, i) << endl;
        }



        int examIndex; string strExamIndex;
        do {
            do {
                cout << "Выберите номер экзамена, который хотите удалить: ";
                cin >> strExamIndex;
                if (!Digital(strExamIndex)) {
                    cout << "Ошибка! Введено недопустимое значение. Попробуйте снова. " << endl;
                }
            } while (!Digital(strExamIndex));
            examIndex = stoi(strExamIndex);
            if (examIndex < 1 || examIndex > examsCount) {
                cout << "Некорректный номер экзамена." << endl;
            }
        } while (examIndex < 1 || examIndex > examsCount);

        // Сдвиг экзаменов влево
        for (int i = examIndex - 1; i < examsCount - 1; i++) {
            student.setSessionName(sessionIndex - 1, i, student.getExamName(sessionIndex - 1, i + 1));
            student.setSessionResult(sessionIndex - 1, i, student.getExamResult(sessionIndex - 1, i + 1));
        }

        // Очистка последнего экзамена
        student.setSessionName(sessionIndex - 1, examsCount - 1, "");
        student.setSessionResult(sessionIndex - 1, examsCount - 1, "");

        if (student.getExamsInCount(sessionIndex - 1) == 0) {
            // Удаление всей сессии
            student.setSessionsCount(student.getSessionsCount() - 1);
        }

    }
}

// Функция для изменения данных о студенте
void editStudent(StudentList& studentList) {
    int index; string strIndex;
    do {
        do {
            cout << "Введите номер студента для редактирования (1 - " << studentList.getSize() << "): ";
            cin >> strIndex;
            if (!Digital(strIndex)) {
                cout << "Ошибка! Введено недопустимый символ. Попробуйте снова. " << endl;
            }
        } while (!Digital(strIndex));
        index = stoi(strIndex);
        if (index < 1 || index > studentList.getSize()) {
            cout << "Ошибка! Введенное значение не попадает в диапозон. Попробуйте снова." << endl;
        }
    } while (index < 1 || index > studentList.getSize());
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
    int choice; string strChoice;
    do {
        do {
            cout << "Введите номер значения, которое вы хотите изменить, или нажмите 0, чтобы ничего не изменять:  ";
            cin >> strChoice;
            if (!Digital(strChoice))  {
                cout << "Ошибка! Введено неверное значение. Попробуйте снова. " << endl;
            }
        } while (!Digital(strChoice));
        choice = stoi(strChoice);
        switch (choice) {
        case 0:
            system("cls");
            break;
        case 1: {
            system("cls");
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
            system("cls");
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
            system("cls");
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
            system("cls");
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
            system("cls");
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
            system("cls");
            string newDepartment;
            cout << "Введите новую кафедру: ";
            cin >> newDepartment;
            student.setDepartment(newDepartment);
            choice = 0;
            break;
        }
        case 7: {
            system("cls");
            string newGroup;
            cout << "Введите новую группу: ";
            cin >> newGroup;
            student.setGroup(newGroup);
            choice = 0;
            break;
        }
        case 8: {
            system("cls");
            string newStudentID;
            cout << "Введите новый номер зачетной книжки: ";
            cin >> newStudentID;
            student.setStudentID(newStudentID);
            choice = 0;
            break;
        }
        case 9: {
            system("cls");
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
            system("cls");
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
            system("cls");
            cout << "0) Ничего не изменять" << endl;
            cout << "1) Добавить новые экзамены" << endl;
            cout << "2) Изменить результаты и названия уже добавленных экзаменов" << endl;
            cout << "3) Удалить экзамен" << endl;
            int choice1; string strChoice1;
            do {
                do {
                    cout << "Выберите действие (1-3): ";
                    cin >> strChoice1;
                    if (!Digital(strChoice1)) {
                        cout << "Ошибка! Введено недопустимое значение. Попробуйте снова. " << endl;
                    }
                } while (!Digital(strChoice1));
                choice1 = stoi(strChoice1);
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
                case 3:
                    system("cls");
                    deleteExams(student);
                    choice1 = 0;
                    break;
                default:
                    cout << "Ошибка! Значение не входит в диапозон. Попробуйте снова. " << endl;
                    break;
                } 
                } while (choice1 != 0);
            choice = 0;
            break;
        }
        default:
            cout << "Ошибка! Значение не входит в диапозон. Попробуйте снова. " << endl;
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
                cout << "Введите результат экзамена " << i + 1 << " (2, 3, 4, 5, Зачет, Незачет, Неявка): ";
                cin >> examResult;
                if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
                    examResult != "Зачет" && examResult != "Незачет" && examResult != "Неявка") {
                    cout << "Некорректный результат экзамена. Попробуйте еще раз." << endl;
                }
            } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
                examResult != "Зачет" && examResult != "Незачет" && examResult != "Неявка");
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
    int index; string strIndex;
    do {
        do {
            cout << "Введите номер студента для удаления (1 - " << studentList.getSize() << "): ";
            cin >> strIndex;
            if (!(Digital(strIndex))) {
                cout << "Ошибка! Введен недопустимый символ. Попробуйте снова." << endl;
            }
        } while (!(Digital(strIndex)));
        index = stoi(strIndex);
        if (index < 1 || index > studentList.getSize()) {
            cout << "Ошибка! Число не входит в диапозон. Попробуйте снова." << endl;
        }
    } while (index < 1 || index > studentList.getSize());
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

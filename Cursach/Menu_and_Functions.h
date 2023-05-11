#pragma once
using namespace std;

#include "ClassStudentList.h"
#include "DopFunctions.h"

// ������� ��� ����������� ���� � ��������� ������ ������������
int getMenuChoice() {
    int choice;
    cout << "�������� ��������:" << endl;
    cout << "0) ����� �� ���������" << endl;
    cout << "1) ���������� ������ � ���������" << endl;
    cout << "2) �������� ������ � ���������" << endl;
    cout << "3) �������� ������ � ��������" << endl;
    cout << "4) ������� ��������" << endl;
    cout << "5) ��������� �������" << endl;
    cin >> choice;
    return choice;
}

// ������� ��� ����������� ������ ���������
void displayStudents(StudentList& studentList) {
    int size = studentList.getSize();
    for (int i = 0; i < size; i++) {
        Student student = studentList.getStudent(i);
        cout << "������� #" << i + 1 << ":" << endl;
        cout << "���: " << student.getSurname() << " " << student.getName() << " " << student.getPatronymic() << endl;
        cout << "���: " << (student.getGender() == '�' ? "�������" : "�������") << endl;
        cout << "���������: " << student.getFaculty() << endl;
        cout << "�������: " << student.getDepartment() << endl;
        cout << "������: " << student.getGroup() << endl;
        cout << "�������� ������: " << student.getStudentID() << endl;
        cout << "���� ��������: ";
        printDate(student.getBirthDay(), student.getBirthMonth(), student.getBirthYear());
        cout << endl;
        cout << "��� ������������: " << student.getAdmissionYear() << endl;
        int sessionsCount = student.getSessionsCount();
        for (int j = 0; j < sessionsCount; j++) {
            cout << "������ #" << j + 1 << ":" << endl;
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

// ������� ���������� ���������
void addExams(Student& student) {
    int sessionIndex;
    int sessionCount = student.getSessionsCount();
    cout << "�������� ������ ��� ���������� �������� (1-" << student.getSessionsCount() + 1 << "): ";
    cin >> sessionIndex;
    if (sessionIndex < 1 || sessionIndex > student.getSessionsCount() + 1) {
        cout << "������������ ����� ������." << endl;
        return;
    }

    int examsCount = student.getExamsInCount(sessionIndex - 1);
    if (examsCount >= 10) {
        cout << "���������� ������������ ����� ��������� ��� ���� ������." << endl;
        return;
    }

    if (sessionIndex > sessionCount) {
        sessionCount++;
        student.setSessionsCount(sessionCount);
    }

    string examName;
    do {
        cout << "������� �������� ��������: ";
        cin >> examName;
        if (!Alpha(examName)) {
            cout << "������������ �������� ��������. ���������� ��� ���." << endl;
        }
    } while (!Alpha(examName));

    string examResult;
    do {
        cout << "������� ����� ��������� �������� (2, 3, 4, 5, �����, �������): ";
        cin >> examResult;
        if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
            examResult != "�����" && examResult != "�������") {
            cout << "������������ ��������� ��������. ���������� ��� ���." << endl;
        }
    } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
        examResult != "�����" && examResult != "�������");

    student.setSessionName(sessionIndex - 1, examsCount, examName);
    student.setSessionResult(sessionIndex - 1, examsCount, examResult);

    cout << "������� ������� ��������." << endl;
}

// ������� ��������� ���������
void editExams(Student& student) {
    int sessionIndex, examIndex;
    string strSessionIndex, strExamIndex;
    do {
        do {
            cout << "������� ����� ������ (1-" << student.getSessionsCount() << "): ";
            cin >> strSessionIndex;
            if (!Digital(strSessionIndex)) {
                cout << "������ ����������� ����� ������. ���������� ��� ���. " << endl;
            }
        } while ((!Digital(strSessionIndex)));
        sessionIndex = stoi(strSessionIndex);
        if (sessionIndex > student.getSessionsCount()) {
            cout << "������ ����������� ����� ������. ���������� ��� ���. " << endl;
        }
    } while (sessionIndex > student.getSessionsCount());
    sessionIndex--;
    do {
        do {
            cout << "������� ����� �������� (1-" << student.getExamsInCount(sessionIndex) << "): ";
            cin >> strExamIndex;
            if (!Digital(strExamIndex)) {
                cout << "������ ����������� ����� ��������. ���������� ��� ���. " << endl;
            }
        } while ((!Digital(strExamIndex)));
        examIndex = stoi(strExamIndex);
        if (examIndex > student.getExamsInCount(sessionIndex)) {
            cout << "������ ����������� ����� ��������. ���������� ��� ���. " << endl;
        }
    } while (examIndex > student.getExamsInCount(sessionIndex));
    examIndex--;
    string examName, examResult;
    do {
        cout << "������� ����� �������� ��������: ";
        cin >> examName;
        if (!(Alpha(examName))) {
            cout << "�������� ������� �������� ��������. ���������� ��� ���. " << endl;
        }
    } while (!(Alpha(examName)));
    do {
        cout << "������� ����� ��������� �������� (2, 3, 4, 5, �����, �������): ";
        cin >> examResult;
        if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
            examResult != "�����" && examResult != "�������") {
            cout << "������������ ��������� ��������. ���������� ��� ���." << endl;
        }
    } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
        examResult != "�����" && examResult != "�������");
    student.setSessionName(sessionIndex, examIndex, examName);
    student.setSessionResult(sessionIndex, examIndex, examResult);
}

// ������� ��� ��������� ������ � ��������
void editStudent(StudentList& studentList) {
    int index;
    cout << "������� ����� �������� ��� ��������������: ";
    cin >> index;
    system("cls");
    Student student = studentList.getStudent(index - 1);
    cout << "������ ������� #" << index << ":" << endl;
    cout << "1) �������: " << student.getSurname() << endl;
    cout << "2) ���: " << student.getName() << endl;
    cout << "3) ��������: " << student.getPatronymic() << endl;
    cout << "4) ���: " << (student.getGender() == '�' ? "�������" : "�������") << endl;
    cout << "5) ���������: " << student.getFaculty() << endl;
    cout << "6) �������: " << student.getDepartment() << endl;
    cout << "7) ������: " << student.getGroup() << endl;
    cout << "8) �������� ������: " << student.getStudentID() << endl;
    cout << "9) ���� ��������: ";
    printDate(student.getBirthDay(), student.getBirthMonth(), student.getBirthYear());
    cout << endl;
    cout << "10) ��� �����������: " << student.getAdmissionYear() << endl;
    cout << "11) ���������� � �������� ���������: " << endl;
    int sessionsCount = student.getSessionsCount();
    for (int j = 0; j < sessionsCount; j++) {
        cout << "������ #" << j + 1 << ":" << endl;
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
        cout << "������� ����� ��������, ������� �� ������ ��������, ��� ������� 0, ����� ������ �� ��������:  ";
        cin >> choice;
        system("cls");
        switch (choice) {
        case 0:
            break;
        case 1: {
            string newSurname;
            do {
                cout << "������� ����� �������: ";
                cin >> newSurname;
                if (!Alpha(newSurname)) {
                    cout << "����������� ������� �������. ���������� ��� ���." << endl;
                }
            } while (!Alpha(newSurname));
            student.setSurname(newSurname);
            choice = 0;
            break;
        }
        case 2: {
            string newName;
            do {
                cout << "������� ����� ���: ";
                cin >> newName;
                if (!Alpha(newName)) {
                    cout << "����������� ������� ���. ���������� ��� ���." << endl;
                }
            } while (!Alpha(newName));
            student.setName(newName);
            choice = 0;
            break;
        }
        case 3: {
            string newPatronymic;
            do {
                cout << "������� ����� ��������: ";
                cin >> newPatronymic;
                if (!Alpha(newPatronymic)) {
                    cout << "����������� ������� ��������. ���������� ��� ���." << endl;
                }
            } while (!Alpha(newPatronymic));
            student.setPatronymic(newPatronymic);
            choice = 0;
            break;
        }
        case 4: {
            char newGender;
            do {
                cout << "������� ��� (�/�): ";
                cin >> newGender;
                if (!GenderTest(newGender)) {
                    cout << "����������� ������ ���. ���������� ��� ���." << endl;
                }
            } while (!GenderTest(newGender));
            student.setGender(newGender);
            choice = 0;
            break;
        }
        case 5: {
            string newFaculty;
            do {
                cout << "������� ����� ���������: ";
                cin >> newFaculty;
                if (!Alpha(newFaculty)) {
                    cout << "����������� ������ ���������. ���������� ��� ���." << endl;
                }
            } while (!Alpha(newFaculty));
            student.setFaculty(newFaculty);
            choice = 0;
            break;
        }
        case 6: {
            string newDepartment;
            cout << "������� ����� �������: ";
            cin >> newDepartment;
            student.setDepartment(newDepartment);
            choice = 0;
            break;
        }
        case 7: {
            string newGroup;
            cout << "������� ����� ������: ";
            cin >> newGroup;
            student.setGroup(newGroup);
            choice = 0;
            break;
        }
        case 8: {
            string newStudentID;
            cout << "������� ����� ����� �������� ������: ";
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
                    cout << "������� ���� �������� (��.��.����): ";
                    cin >> strNewBirthDay >> strNewBirthMonth >> strNewBirthYear;
                    if (!Digital(strNewBirthDay) || !Digital(strNewBirthMonth) || !Digital(strNewBirthYear)) {
                        cout << "������������ ����. ���������� ��� ���." << endl;
                    }
                } while (!Digital(strNewBirthDay) || !Digital(strNewBirthMonth) || !Digital(strNewBirthYear));
                newBirthDay = stoi(strNewBirthDay);
                newBirthMonth = stoi(strNewBirthMonth);
                newBirthYear = stoi(strNewBirthYear);
                if (!isValidBirthDate(newBirthDay, newBirthMonth, newBirthYear)) {
                    cout << "������������ ����. ���������� ��� ���." << endl;
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
                    cout << "������� ��� �����������: ";
                    cin >> strNewAdmissinYear;
                    if (!Digital(strNewAdmissinYear)) {
                        cout << "������������ ��� �����������. ���������� ��� ���." << endl;
                    }
                } while (!Digital(strNewAdmissinYear));
                newAdmissionYear = stoi(strNewAdmissinYear);
                if (!isValidAdmissionYear(newAdmissionYear)) {
                    cout << "������������ ��� �����������. ���������� ��� ���." << endl;
                }
            } while (!isValidAdmissionYear(newAdmissionYear));
            student.setAdmissionYear(newAdmissionYear);
            choice = 0;
            break;
        }
        case 11: {
            cout << "�������� ��������:" << endl;
            cout << "0) ������ �� ��������" << endl;
            cout << "1) �������� ����� ��������" << endl;
            cout << "2) �������� ���������� � �������� ��� ����������� ���������" << endl;
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
                    cout << "������: �������� �����" << endl;
                    break;
                }
            } while (choice1 != 0);
            choice = 0;
            break;
        }
        default:
            cout << "������: �������� �����" << endl;
            break;
        }
    } while (choice != 0);
    system("cls");
    studentList.editStudent(index - 1, student);
    cout << "������ � �������� #" << index << " ��������" << endl;
    system("pause");
    system("cls");
}

// ������� ��� ���������� ������ ��������
void addStudent(StudentList& studentList) {
    Student student;

    string surname;
    do {
        cout << "������� �������: ";
        cin >> surname;
        if (!Alpha(surname)) {
            cout << "����������� ������� �������. ���������� ��� ���." << endl;
        }
    } while (!Alpha(surname));
    student.setSurname(surname);

    string name;
    do {
        cout << "������� ���: ";
        cin >> name;
        if (!Alpha(name)) {
            cout << "����������� ������� ���. ���������� ��� ���." << endl;
        }
    } while (!Alpha(name));
    student.setName(name);

    string patronymic;
    do {
        cout << "������� ��������: ";
        cin >> patronymic;
        if (!Alpha(patronymic)) {
            cout << "����������� ������� ��������. ���������� ��� ���." << endl;
        }
    } while (!Alpha(patronymic));
    student.setPatronymic(patronymic);

    char gender;
    do {
        cout << "������� ��� (�/�): ";
        cin >> gender;
        if (!GenderTest(gender)) {
            cout << "����������� ������ ���. ���������� ��� ���." << endl;
        }
    } while (!GenderTest(gender));
    student.setGender(gender);

    string faculty;
    do {
        cout << "������� ���������: ";
        cin >> faculty;
        if (!Alpha(faculty)) {
            cout << "����������� ������ ���������. ���������� ��� ���." << endl;
        }
    } while (!Alpha(faculty));
    student.setFaculty(faculty);

    cout << "������� �������: ";
    string department;
    cin >> department;
    student.setDepartment(department);

    cout << "������� ������: ";
    string group;
    cin >> group;
    student.setGroup(group);

    cout << "������� ����� �������� ������: ";
    string studentID;
    cin >> studentID;
    student.setStudentID(studentID);

    string strBirthDay, strBirthMonth, strBirthYear;
    int birthDay, birthMonth, birthYear;
    do {
        do {
            cout << "������� ���� �������� (��.��.����): ";
            cin >> strBirthDay >> strBirthMonth >> strBirthYear;
            if (!Digital(strBirthDay) || !Digital(strBirthMonth) || !Digital(strBirthYear)) {
                cout << "������������ ����. ���������� ��� ���." << endl;
            }
        } while (!Digital(strBirthDay) || !Digital(strBirthMonth) || !Digital(strBirthYear));
        birthDay = stoi(strBirthDay);
        birthMonth = stoi(strBirthMonth);
        birthYear = stoi(strBirthYear);
        if (!isValidBirthDate(birthDay, birthMonth, birthYear)) {
            cout << "������������ ����. ���������� ��� ���." << endl;
        }
    } while (!isValidBirthDate(birthDay, birthMonth, birthYear));
    student.setBirthDay(birthDay);
    student.setBirthMonth(birthMonth);
    student.setBirthYear(birthYear);

    string strAdmissinYear;
    int admissionYear;
    do {
        do {
            cout << "������� ��� �����������: ";
            cin >> strAdmissinYear;
            if (!Digital(strAdmissinYear)) {
                cout << "������������ ��� �����������. ���������� ��� ���." << endl;
            }
        } while (!Digital(strAdmissinYear));
        admissionYear = stoi(strAdmissinYear);
        if (!isValidAdmissionYear(admissionYear)) {
            cout << "������������ ��� �����������. ���������� ��� ���." << endl;
        }
    } while (!isValidAdmissionYear(admissionYear));
    student.setAdmissionYear(admissionYear);

    // ���� ����������� ������
    int sessionsCount = 0;
    do {
        cout << "������� ���������� ��������� � ������ " << sessionsCount + 1 << " (�� 1 �� 10): ";
        int examsCount;
        string strExamsCount;
        cin >> strExamsCount;
        if (!Digital(strExamsCount)) {
            cout << "������������ ����� ���������. ���������� ��� ���. " << endl;
            continue;
        }
        examsCount = stoi(strExamsCount);

        // �������� ������������ ����� ���������� ���������
        if (examsCount < 1 || examsCount > 10) {
            cout << "������������ ���������� ���������. ���������� ��� ���." << endl;
            continue;
        }

        for (int i = 0; i < examsCount; i++) {
            string examName;
            do {
                cout << "������� �������� �������� " << i + 1 << ": ";
                cin >> examName;
                if (!Alpha(examName)) {
                    cout << "������������ �������� ��������. ���������� ��� ���." << endl;
                }
            } while (!Alpha(examName));

            string examResult;
            do {
                cout << "������� ��������� �������� " << i + 1 << " (2, 3, 4, 5, �����, �������): ";
                cin >> examResult;
                if (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
                    examResult != "�����" && examResult != "�������") {
                    cout << "������������ ��������� ��������. ���������� ��� ���." << endl;
                }
            } while (examResult != "2" && examResult != "3" && examResult != "4" && examResult != "5" &&
                examResult != "�����" && examResult != "�������");
            // ��������� ����������� ��������� ��� ������� ������
            student.setSessionName(sessionsCount, i, examName);
            student.setSessionResult(sessionsCount, i, examResult);
        }

        sessionsCount++;
        if (sessionsCount >= 9) {
            cout << "���������� ������������ ���������� ������." << endl;
            break;
        }

        char choice;
        do {
            cout << "������ �������� ��� ���� ������? (���� �� - ������� �, ����� - �): ";
            cin >> choice;
        } while (choice != '�' && choice != '�');

        if (choice == '�') {
            break;
        }

    } while (true);

    // ��������� ���������� ����������� ������
    student.setSessionsCount(sessionsCount);

    studentList.addStudent(student);
    system("cls");
    cout << "������� ��������" << endl;
    system("pause");
    system("cls");

}

// ������� ��� �������� ��������
void removeStudent(StudentList& studentList) {
    int index;
    cout << "������� ����� �������� ��� ��������: ";
    cin >> index;
    system("cls");
    studentList.removeStudent(index - 1);
    cout << "������� #" << index << " ������" << endl;
    system("pause");
    system("cls");
}

// ������� ��� ���������� �������
void performTask(StudentList& studentList) {
    cout << "����������� �������..." << endl;
    // ����� ����� �������� ���� ��� ��� ���������� �������
}

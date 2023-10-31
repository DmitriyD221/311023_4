#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>
using namespace std;
enum specialization { COMPUTER_SCIENCE, ELECTRICAL_ENGINEERING, MECHANICAL_ENGINEERING };

class student {
public:
    student(string name, int id, double averageScore)
        : name(name), id(id), averageScore(averageScore) {}
    string getname() const {
        return name;
    }
    int getId() const {
        return id;
    }
    double getAverageScore() const {
        return averageScore;
    }
private:
    string name;
    int id;
    double averageScore;
};

class Group {
public:
    Group() : groupName(""), specialization(COMPUTER_SCIENCE), course(1) {}
    Group(const Group& other) {
        groupName = other.groupName;
        specialization = other.specialization;
        course = other.course;
        students = other.students;
    }
    Group(string name, specialization spec, int crs)
        : groupName(name), specialization(spec), course(crs) {}
    int getStudentCount() const {
        return students.size();
    }
    string getGroupName() const {
        return groupName;
    }
    void setGroupName(const string& name) {
        groupName = name;
    }
    specialization getSpecialization() const {
        return specialization;
    }
    void setSpecialization(specialization spec) {
        specialization = spec;
    }
    int getCourse() const {
        return course;
    }
    void setCourse(int crs) {
        course = crs;
    }
    const student& getStudentByIndex(int index) const {
        if (index >= 0 && index < students.size()) {
            return students[index];
        }
        else {
            cout << "������� - i����� �������� �� ��� ��������." << endl;
        }
    }
    void addStudent(const student& student) {
        students.push_back(student);
    }
    void mergeGroups(const Group& otherGroup) {
        students.insert(students.end(), otherGroup.students.begin(), otherGroup.students.end());
    }
    void transferStudent(int studentId, Group& otherGroup) {
        auto it = find_if(students.begin(), students.end(),
            [studentId](const student& s) { return s.getId() == studentId; });
        if (it != students.end()) {
            otherGroup.addStudent(*it);
            students.erase(it);
        }
        else {
            cout << "�������: �������� �� ��������." << endl;
        }
    }
    void removeFailedStudents() {
        students.erase(remove_if(students.begin(), students.end(),
            [](const student& s) { return s.getAverageScore() < 60.0; }), students.end());
    }
    void removeStudentWithLowestAverageScore() {
        if (students.empty()) {
            cout << "������: � ���� ���� ��������." << endl;
            return;
        }
        auto lowestScoreStudent = min_element(students.begin(), students.end(),
            [](const student& a, const student& b) {
                return a.getAverageScore() < b.getAverageScore();
            });
        students.erase(lowestScoreStudent);
    }
    void printAllStudents() const {
        cout << "����� �����: " << groupName << ", ������������: " << specialization << ", ����: " << course
            << endl;
        cout << "������ ��������:" << endl;
        for (const student& student : students) {
            cout << "ID: " << student.getId() << ", ��'�: " << student.getName() << ", ������� ���: "
                << student.getAverageScore() << endl;
        }
    }
private:
    string groupName;
    specialization specialization;
    int course;
    vector<student> students;
};

int main() {
    setlocale(LC_ALL, "");

    Group group1;
    group1.setGroupName("����� �");
    group1.setSpecialization(COMPUTER_SCIENCE);
    group1.setCourse(2);
    student student1("���� ������", 1, 75.5);
    student student2("���� ��������", 2, 82.3);
    student student3("����� ������", 3, 55.0);
    group1.addStudent(student1);
    group1.addStudent(student2);
    group1.addStudent(student3);
    Group group2("����� �", ELECTRICAL_ENGINEERING, 1);
    cout << "����� �:" << endl;
    group1.printAllStudents();
    cout << "����� �:" << endl;
    group2.printAllStudents();
    group1.mergeGroups(group2);
    cout << "��'������ �����:" << endl;
    group1.printAllStudents();
    group1.removeFailedStudents();
    cout << "�������� ��������, �� �� ������ ������:" << endl;
    group1.printAllStudents();
     group1.removeStudentWithLowestAverageScore();
    cout << "��������� ������� � ��������� �������� �����:" << endl;
    group1.printAllStudents();
    return 0;
}

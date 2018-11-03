//John Lauer
//HW3
//Due: 11:59PM, February 25 (Sunday)

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
    string name;
    int section;
    int credits;
    course() {}
    course(string n, int s, int c) { name = n; section = s; credits = c; }
    bool operator<(const course &c) { return (name < c.name); }
    bool operator==(const course &c) { return (name == c.name); }
};
void add_student(map<int, map<int, list<course *> * > *> &DB, int id);
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id);
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course *> * >  *> &DB, int id);
void print_DB(map<int, map<int, list<course *> * >  *> &DB);

int main() {
    map<int, map<int, list<course  *> *> *> DB;
    add_student(DB, 11111);
    course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);
    
    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);
    
    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111);
    
    add_course(DB, 20172, 11111, C2);
    add_course(DB, 20172, 11111, C4);
    add_course(DB, 20172, 11111, C3);
    add_course(DB, 20172, 11111, C1);
    print_student_all_courses(DB, 11111);
    
    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C4);
    add_course(DB, 20171, 11112, C3);
    add_course(DB, 20171, 11112, C1);
    print_student_semester_courses(DB, 20171, 11112);
    
    add_course(DB, 20172, 11112, C2);
    add_course(DB, 20172, 11112, C4);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112);
    
    print_student_all_courses(DB, 11112);
    
    print_DB(DB);
    remove_student(DB, 11111);
    print_DB(DB);
    getchar();
    getchar();
    return 0;
}

void add_student(map<int, map<int, list<course *> * > *> &DB, int id) {
    
    if (DB.size() == 0)
        DB[id] = new map<int, list<course *> * >; return;
        
        auto it1 = DB.find(id); //Note the find syntax; different from find for list and vector
        if (it1 == DB.end()) {
            DB[id] = new map<int, list<course *> * >; return;
        }
    }
    
    void remove_student(map<int, map<int, list<course *> * > *> &DB, int id) {
        auto it = DB.find(id);
        delete it->second;
        DB.erase(it);
    }

    void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
        auto it1 = DB.find(id);
        if (it1 == DB.end()) {
            DB[id] = new map<int, list<course *> *>;
            return;
        }
        map<int, list<course *> *> *sem = it1->second;
        auto it2 = sem->find(id);
        if(it2 == sem->end()) {
            DB[id]->insert(make_pair(semester, new list<course *>));
        }
        it2 = sem->find(semester);
        list<course *> *courses = it2->second;
        course *cp = new course(c.name, c.section, c.credits);
        courses->push_back(cp);
    }
    void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
        auto it1 = DB.find(id);
        if (it1 == DB.end()) {
            DB[id] = new map<int, list<course *> *>; return;
        }
        map<int, list<course *> *> *sem = it1->second;
        auto it2 = sem->find(id);
        if(it2 == sem->end()) {
            DB[id]->insert(make_pair(semester, new list<course *>));
        }
        it2 = sem->find(semester);
        list<course *> *courses = it2->second;
        for (course * cp : *courses) {
            if(cp->name == c.name) {
                courses->remove(cp);
            }
        }
    }
    void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id) {
        cout << endl;
        cout << "student id = " << id << "\n" << "semester = " << semester << "\n";
        auto it1 = DB.find(id);
        if (it1 == DB.end()) {
            DB[id] = new map<int, list<course *> *>; return;
        }
        map<int, list<course *> *> *sem = it1->second;
        auto it2 = sem->find(semester);
        list<course *> courses = *it2->second;
        for (course* c : courses) {
            cout << c->name << " " << c->section << " " << c->credits << " ";
        }
        cout << "\n";
    }
    void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id) {
        auto it1 = DB.find(id);
        cout << "student id = " << it1->first << "\n";
        map<int, list<course *> *> *sem = it1->second;
        for (auto it2 = sem->begin(); it2 != sem->end(); ++it2) {
            cout << "semester = " << it2->first << "\n";
            list<course *> courses = *it2->second;
            for (course * c : courses) {
                cout << c->name << " " << c->section << " " << c->credits << " " << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    void print_DB(map<int, map<int, list<course *> * >  *> &DB) {
        cout << "print DB: ";
        for (auto it1 = DB.begin(); it1 != DB.end(); ++it1) {
            cout << "student id = " << it1->first << "\n";
            map<int, list<course *> *> *sem = it1->second;
            for (auto it2 = sem->begin(); it2 != sem->end(); ++it2) {
                cout << "semester = " << it2->first << "\n";
                list <course *> courses = *it2->second;
                for (course * c : courses) {
                    cout << c->name << " " << c->section << " " << c->credits << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
    }

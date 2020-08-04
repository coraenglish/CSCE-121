#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"

using namespace std;

void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    if (line.length() == 0) {
      break;
    }
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
      students.push_back(Student(uin, name));
    }
  }
}

void School::addCourses(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    if (line.length() == 0) {
      break;
    }
    istringstream ss(line);

    string id;
    getline(ss, id, ',');

    string startTimeHr; string startTimeMin;
    getline(ss, startTimeHr, ':');
    getline(ss, startTimeMin, ',');
    int sth = stoi(startTimeHr);
    int stm = stoi(startTimeMin);
    Date startTime(sth, stm, 0);

    string endTimeHr; string endTimeMin;
    getline(ss, endTimeHr, ':');
    getline(ss, endTimeMin, ',');
    int eth = stoi(endTimeHr);
    int etm = stoi(endTimeMin);
    Date endTime(eth, etm, 0);

    string title;
    getline(ss, title);

    if (!ss.fail()) {
      courses.push_back(Course(id, title, startTime, endTime));
    }
  }
}

void School::addAttendanceData(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    if (line.length() == 0) {
      break;
    }
    istringstream ss(line);

    string year; string month; string day;
    string hour; string min; string sec;
    getline(ss, year, '-');
    getline(ss, month, '-');
    getline(ss, day, ' ');
    getline(ss, hour, ':');
    getline(ss, min, ':');
    getline(ss, sec, ',');

    string course_id;
    getline(ss, course_id, ',');

    string student_id;
    getline(ss, student_id);
    int iyear = stoi(year);
    int imonth = stoi(month);
    int iday = stoi(day);
    int ihour = stoi(hour);
    int imin = stoi(min);
    int isec = stoi(sec);
    Date time(iyear, imonth, iday, ihour, imin, isec);

    if (!ss.fail()) {
      for (int i = 0; i < courses.size(); ++i) {
        if (courses.at(i).getID() == course_id) {
          courses.at(i).addAttendanceRecord(AttendanceRecord(course_id, student_id, time));
        }
      }

      for (int i = 0; i < students.size(); ++i) {
        if (students.at(i).get_id() == student_id) {
          students.at(i).addCourse(course_id);
        }
      }

    }
  }
}


void School::listCourses() {
  if (courses.size() == 0) {
    cout << "No Courses" << endl;
    return;
  }
  for (int i = 0; i < courses.size(); ++i) {
    cout << courses.at(i).getID() << ',' << courses.at(i).getStartTime().getTime() << ','
    << courses.at(i).getEndTime().getTime() << ',' << courses.at(i).getTitle() << endl;
  }
}

void School::listStudents() {
  if (students.size() == 0) {
    cout << "No Students" << endl;
    return;
  }
  for (int i = 0; i < students.size(); ++i) {
    cout << students.at(i).get_id() << ',' << students.at(i).get_name() << endl;
  }
}

void School::outputCourseAttendance(string course_id) {
  for (int i = 0; i < courses.size(); ++i) {
    if (courses.at(i).getID() == course_id) {
      courses.at(i).outputAttendance();
      return;
    }
  }
  cout << "No Records" << endl;

}



void School::outputStudentAttendance(string student_id, string course_id) {
  for (int i = 0; i < courses.size(); ++i) {
    if (courses.at(i).getID() == course_id) {
      courses.at(i).outputAttendance(student_id);
      return;
    }
  }
  cout << "No Records" << endl;

}

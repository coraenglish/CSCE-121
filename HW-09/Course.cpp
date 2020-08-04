#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using namespace std;

// DONE ?
Course::Course(string course_id, string course_title, Date course_startTime, Date course_endTime):startTime(course_startTime), endTime(course_endTime) {
  id = course_id;
  title = course_title;
}


// DONE
string Course::getID() {
  return id;
}

// DONE
string Course::getTitle() {
  return title;
}


Date Course::getStartTime() {
  return startTime;
}


Date Course::getEndTime() {
  return endTime;
}


void Course::addAttendanceRecord(AttendanceRecord ar) {
  attendanceRecords.push_back(ar);
}

void Course::outputAttendance() {
  if (attendanceRecords.size() == 0) {
    cout << "No Records" << endl;
  }
  for (int i = 0; i < attendanceRecords.size(); ++i) {
    cout << attendanceRecords.at(i).getDate().getDate() << ',' << attendanceRecords.at(i).getCourseID()
    << ',' << attendanceRecords.at(i).getStudentID() << endl;
  }
}

void Course::outputAttendance(string student_id) {
  if (attendanceRecords.size() == 0) {
    cout << "No Records" << endl;
  }
  int matches = 0;
  for (int i = 0; i < attendanceRecords.size(); ++i) {
    if (attendanceRecords.at(i).getStudentID() == student_id) {
      cout << attendanceRecords.at(i).getDate().getDate() << ',' << attendanceRecords.at(i).getCourseID()
      << ',' << attendanceRecords.at(i).getStudentID() << endl;
      matches += 1;
    }
  }
  if (matches == 0) {
    cout << "No Records" << endl;
  }
}

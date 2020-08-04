#include <string>
#include "AttendanceRecord.h"
#include "Date.h"

using namespace std;

// DONE ?
AttendanceRecord::AttendanceRecord(string course, string student, Date time):time(time) {
  course_id = course;
  student_id = student;
}

// DONE
string AttendanceRecord::getCourseID() {
  return course_id;
}

// DONE
string AttendanceRecord::getStudentID() {
  return student_id;
}

// DONE
Date AttendanceRecord::getDate() {
  return time;
}


/*
Example code for local unit-testing of HW 4
*/

#include <iostream>
#include <string>
#include "blas.h"
#include "tests.h"

using std::cout;

// amax ; , 0 ; -1
// amax ; -6 -5 , 2 ; 0
// amax ; 1.2 9.6 8.4 , 3 ; 1
// amax ; 8 6 7 5 3 0 9 , 7 ; 6
// amax ; -6 , 1 ; 0

bool test_amax() {

    bool pass = true;

    {
        string testcase = "amax ; 8 6 7 -5 3 0 9 , 7 ; 6";
        double x[] = {8, 6, 7, -5, 3, 0, 9};
        unsigned int len = 7;
        int expected = 6;
        int actual = amax(x, len);

        pass &= EXPECT_EQ(actual, expected, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "amax ; -5 -4 -3 -2 -1 0 1 2, 8 ; 0";
        double x[] = {-4, -5, -3, -2, -1, 0, 1, 2};
        unsigned int len = 8;
        int expected = 1;
        int actual = amax(x, len);

        pass &= EXPECT_EQ(actual, expected, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "amax ; , 0 ; -1";
        double x[] = {};
        unsigned int len = 0;
        int expected = -1;
        int actual = amax(x, len);

        pass &= EXPECT_EQ(actual, expected, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "amax ; -6 -5 , 2 ; 0";
        double x[] = {-6, -5};
        unsigned int len = 2;
        int expected = 0;
        int actual = amax(x, len);

        pass &= EXPECT_EQ(actual, expected, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "amax ; 1.2 9.6 8.4 , 3 ; 1";
        double x[] = {1.2, 9.6, 8.4};
        unsigned int len = 3;
        int expected = 1;
        int actual = amax(x, len);

        pass &= EXPECT_EQ(actual, expected, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "amax ; -6 , 1 ; 0";
        double x[] = {-6};
        unsigned int len = 1;
        int expected = 0;
        int actual = amax(x, len);

        pass &= EXPECT_EQ(actual, expected, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    return pass;
}

// asum ; x, len ; expected return value
// asum ; , 0 ; 0
// asum ; -6 -5 -3 , 3 ; 14
// asum ; 1.2 9.6 8.4 , 3 ; 19.2
// asum ; 1 9 5 4 6 2 3 8 7 , 9 ; 45
// asum ; 0 0 , 2 ; 0

bool test_asum() {

  bool pass = true;

  {
    string testcase = "asum ; , 0 ; 0";
    double x[] = {};
    unsigned int len = 0;
    double expected = 0;
    double actual = asum(x, len);

    pass &= EXPECT_EQ(actual, expected, testcase);
    if (pass) {
      cout << "PASS: " << testcase << endl;
    }

  }

  {
    string testcase = "asum ; -6 -5 -3 , 3 ; 14";
    double x[] = {-6, -5, -3};
    unsigned int len = 3;
    double expected = 14;
    double actual = asum(x, len);

    pass &= EXPECT_EQ(actual, expected, testcase);
    if (pass) {
      cout << "PASS: " << testcase << endl;
    }

  }

  {
    string testcase = "asum ; 1.2 9.6 8.4 , 3 ; 19.2";
    double x[] = {1.2, 9.6, 8.4};
    unsigned int len = 3;
    double expected = 19.2;
    double actual = asum(x, len);

    pass &= EXPECT_EQ(actual, expected, testcase);
    if (pass) {
      cout << "PASS: " << testcase << endl;
    }

  }

  {
    string testcase = "asum ; 1 9 5 4 6 2 3 8 7 , 9 ; 45";
    double x[] = {1, 9, 5, 4, 6, 2, 3, 8, 7};
    unsigned int len = 9;
    double expected = 5;
    double actual = asum(x, len);

    pass &= EXPECT_EQ(actual, expected, testcase);
    if (pass) {
      cout << "PASS: " << testcase << endl;
    }

  }

  {
    string testcase = "asum ; 0 0 , 2 ; 0";
    double x[] = {0, 0};
    unsigned int len = 2;
    double expected = 0;
    double actual = asum(x, len);

    pass &= EXPECT_EQ(actual, expected, testcase);
    if (pass) {
      cout << "PASS: " << testcase << endl;
    }

  }

  return pass;

}

// axpy ; a, x, y, len ; expected y
// axpy ; 1 , , , 0 ;
// axpy ; -2 , 1 2 3 , 4 5 6 , 3 ; 2 1 0
// axpy ; 0 , -1 -2 -3 , 7 8 9 , 3 ; 7 8 9
// axpy ; 2 , 1 1 1 , 1.2 9.6 8.4 , 3 ;  3.2 11.6 10.4

bool test_axpy() {

  bool pass = true;

    {
        string testcase = "axpy ; 1 , 1 2 3 , 4 5 6 , 3 ; 5 7 9";
        double a = 1;
        double x[] = {1, 2, 3};
        double y[] = {4, 5, 6};
        unsigned int len = 3;
        double expected[] = {5, 7, 9};
        axpy(a, x, y, len);
        double* actual = y;

        pass &= EXPECT_EQ(actual, expected, len, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "axpy ; 1 , , , 0 ;";
        double a = 1;
        double x[] = {};
        double y[] = {};
        unsigned int len = 0;
        double expected[] = {};
        axpy(a, x, y, len);
        double* actual = y;

        pass &= EXPECT_EQ(actual, expected, len, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "axpy ; -2 , 1 2 3 , 4 5 6 , 3 ; 2 1 0";
        double a = -2;
        double x[] = {1, 2, 3};
        double y[] = {4, 5, 6};
        unsigned int len = 3;
        double expected[] = {2, 1, 0};
        axpy(a, x, y, len);
        double* actual = y;

        pass &= EXPECT_EQ(actual, expected, len, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "axpy ; 0 , -1 -2 -3 , 7 8 9 , 3 ; 7 8 9";
        double a = 0;
        double x[] = {-1, -2, -3};
        double y[] = {7, 8, 9};
        unsigned int len = 3;
        double expected[] = {7, 8, 9};
        axpy(a, x, y, len);
        double* actual = y;

        pass &= EXPECT_EQ(actual, expected, len, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    {
        string testcase = "axpy ; 2 , 1 1 1 , 1.2 9.6 8.4 , 3 ;  3.2 11.6 10.4";
        double a = 2;
        double x[] = {1, 1, 1};
        double y[] = {1.2, 9.6, 8.4};
        unsigned int len = 3;
        double expected[] = {3.2, 11.6, 10.4};
        axpy(a, x, y, len);
        double* actual = y;

        pass &= EXPECT_EQ(actual, expected, len, testcase);
        if (pass) {
            cout << "PASS: " << testcase << endl;
        }
    }

    return pass;
}

// // copy ; x, y, len ; expected y
// copy ; , , 0 ;
// copy ; -1 -2 -3 , 6 5 4 , 3 ; -1 -2 -3
// copy ; 1.1 2.2 3.3 , 1 1 1 , 3 ; 1.1 2.2 3.3

bool test_copy() {

  bool pass = true;

  {
      string testcase = "copy ; , , 0 ;";
      double x[] = {};
      double y[] = {};
      unsigned int len = 0;
      double expected[] = {};
      copy(x, y, len);
      double* actual = y;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "copy ; -1 -2 -3 , 6 5 4 , 3 ; -1 -2 -3";
      double x[] = {-1, -2, -3};
      double y[] = {6, 5, 4};
      unsigned int len = 3;
      double expected[] = {-1, -2, -3};
      copy(x, y, len);
      double* actual = y;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "copy ; 1.1 2.2 3.3 , 1 1 1 , 3 ; 1.1 2.2 3.3";
      double x[] = {1.1, 2.2, 3.3};
      double y[] = {1, 1, 1};
      unsigned int len = 3;
      double expected[] = {1.1, 2.2, 3.3};
      copy(x, y, len);
      double* actual = y;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  return pass;
}

// dot ; x, y, len ; expected return value
// dot ; , , 0 ; 0
// dot ; -1 1 2 , 2 -4 3 , 3 ; 0
// dot ; -1 -2 -3 , 6 5 4 , 3 ; -28
// dot ; 1.1 2.2 3.3 , 1 1 1 , 3 ; 6.6

bool test_dot() {

  bool pass = true;

  {
      string testcase = "dot ; , , 0 ; 0";
      double x[] = {};
      double y[] = {};
      unsigned int len = 0;
      double expected = 0;
      double actual = dot(x, y, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "dot ; -1 1 2 , 2 -4 3 , 3 ; 0";
      double x[] = {-1, 1, 2};
      double y[] = {2, -4, 3};
      unsigned int len = 3;
      double expected = 0;
      double actual = dot(x, y, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "dot ; -1 -2 -3 , 6 5 4 , 3 ; -28";
      double x[] = {-1, -2, -3};
      double y[] = {6, 5, 4};
      unsigned int len = 3;
      double expected = -28;
      double actual = dot(x, y, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "dot ; 1.1 2.2 3.3 , 1 1 1 , 3 ; 6.6";
      double x[] = {1.1, 2.2, 3.3};
      double y[] = {1, 1, 1};
      unsigned int len = 3;
      double expected = 6.6;
      double actual = dot(x, y, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  return pass;

}

// norm2 ; x, len ; expected return value
// norm2 ; 1 2 3 , 3 ; 3.74165738677
// norm2 ; 0 0 0 , 3 ; 0
// norm2 ; -1 -2 -3 , 3 ; 3.74165738677
// norm2 ; , 0 ; 0

bool test_norm2() {

  bool pass = true;

  {
      string testcase = "norm2 ; , 0 ; 0";
      double x[] = {};
      unsigned int len = 0;
      double expected = 0;
      double actual = norm2(x, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "norm2 ; 0 0 0 , 3 ; 0";
      double x[] = {0, 0, 0};
      unsigned int len = 3;
      double expected = 0;
      double actual = norm2(x, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "norm2 ; 1 2 3 , 3 ; 3.74165738677";
      double x[] = {1, 2, 3};
      unsigned int len = 3;
      double expected = 3.74165738677;
      double actual = norm2(x, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "norm2 ; -1 -2 -3 , 3 ; 3.74165738677";
      double x[] = {-1, -2, -3};
      unsigned int len = 3;
      double expected = 3.74165738677;
      double actual = norm2(x, len);

      pass &= EXPECT_EQ(actual, expected, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  return pass;
}

// scale ; a, x, len ; expected x
// scale ; 1 , , 0 ;
// scale ; 2 , 2 0 1 9 , 4 ; 4 0 2 18
// scale ;  0 , 2.2 0 2.2 2.2 , 4 ; 0 0 0 0
// scale ; -5 , 5 -10 15 -20 , 4 ; -25 50 -75 100

bool test_scale() {

  bool pass = true;

  {
      string testcase = "scale ; 1 , , 0 ;";
      double a = 1;
      double x[] = {};
      unsigned int len = 0;
      double expected[] = {};
      scale(a, x, len);
      double* actual = x;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "scale ; 2 , 2 0 1 9 , 4 ; 4 0 2 18";
      double a = 2;
      double x[] = {2, 0, 1, 9};
      unsigned int len = 4;
      double expected[] = {4, 0, 2, 18};
      scale(a, x, len);
      double* actual = x;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "scale ;  0 , 2.2 0 2.2 2.2 , 4 ; 0 0 0 0";
      double a = 0;
      double x[] = {2.2, 0, 2.2, 2.2};
      unsigned int len = 4;
      double expected[] = {0, 0, 0, 0};
      scale(a, x, len);
      double* actual = x;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "scale ; -5 , 5 -10 15 -20 , 4 ; -25 50 -75 100";
      double a = -5;
      double x[] = {5, -10, 15, -20};
      unsigned int len = 4;
      double expected[] = {-25, 50, -75, 100};
      scale(a, x, len);
      double* actual = x;

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  return pass;
}

// swap ; x, y, len ; expected x, expected y
// swap ; , , 0 ; ,
// swap ; -1 -2 -3 , 6 5 4 , 3 ; 6 5 4 , -1 -2 -3
// swap ; 1.1 2.2 3.3 , 1 1 1 , 3 ; 1 1 1 , 1.1 2.2 3.3

bool test_swap() {

  bool pass = true;

  {
      string testcase = "swap ; , , 0 ; ,";
      double x[] = {};
      double y[] = {};
      unsigned int len = 0;
      double expected[] = {};
      double* actual = x;
      swap(x, y, len);

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "swap ; -1 -2 -3 , 6 5 4 , 3 ; 6 5 4 , -1 -2 -3";
      double x[] = {-1, -2, -3};
      double y[] = {6, 5, 4};
      unsigned int len = 3;
      double expected[] = {6, 5, 4};
      double* actual = x;
      swap(x, y, len);

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  {
      string testcase = "swap ; 1.1 2.2 3.3 , 1 1 1 , 3 ; 1 1 1 , 1.1 2.2 3.3";
      double x[] = {1.1, 2.2, 3.3};
      double y[] = {1, 1, 1};
      unsigned int len = 3;
      double expected[] = {1, 1, 1};
      double* actual = x;
      swap(x, y, len);

      pass &= EXPECT_EQ(actual, expected, len, testcase);
      if (pass) {
          cout << "PASS: " << testcase << endl;
      }
  }

  return pass;
}



int main() {
    int failing = 0;
    // add 1 to failing if function returns false
    failing += test_amax() ? 0 : 1;
    failing += test_asum() ? 0 : 1;
    failing += test_axpy() ? 0 : 1;
    failing += test_copy() ? 0 : 1;
    failing += test_dot() ? 0 : 1;
    failing += test_norm2() ? 0 : 1;
    failing += test_scale() ? 0 : 1;
    failing += test_swap() ? 0 : 1;


    if (!failing) {
        cout << "ALL TESTS PASSING" << endl;
    } else {
        cout << endl << "Failing: " << failing << endl;
    }

    return 0;
}
//tests.cpp
//Displaying tests.cpp.

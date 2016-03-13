// Confusion matrix test
//
// jeffsp@gmail.com
//
// Sat Mar 12 12:04:17 CST 2016

#include "confusion_matrix.h"
#include "verify.h"
#include <iostream>

using namespace std;

void test1 ()
{
    confusion_matrix cm;
    const size_t N = 1000;
    for (size_t i = 0; i < N; ++i)
        cm.update (rand () % 2, rand () % 2);
    clog << cm << endl;
}

void test2 ()
{
    confusion_matrix cm;
    cm.update (1, 1);
    cm.update (0, 1);
    cm.update (1, 0);
    cm.update (0, 0);
    clog << cm << endl;
    cm.update (1, 1);
    clog << cm << endl;
    cm.update (0, 1);
    clog << cm << endl;
    cm.update (1, 0);
    clog << cm << endl;
    cm.update (0, 0);
    clog << cm << endl;
}

void test3 ()
{
    stringstream ss;
    ss << "1 1" << endl;
    ss << "2 1" << endl;
    ss << "1 2" << endl;
    ss << "2 2" << endl;
    conditions conditions = read_conditions (ss);
    confusion_matrix cm = get_confusion_matrix (conditions, 1);
    clog << cm << endl;
}

void test4 ()
{
    stringstream ss;
    ss << "1 1" << endl;
    ss << "2 1" << endl;
    ss << "1 2" << endl;
    // oops, missing prediction
    ss << "2" << endl;
    bool caught = false;
    try { conditions conditions = read_conditions (ss); }
    catch (const exception &e) {
        clog << "caught exception... OK" << endl;
        caught = true;
    }
    verify (caught);
}

int main (int argc, char **argv)
{
    try
    {
        test1 ();
        test2 ();
        test3 ();
        test4 ();
        clog << "Success" << endl;

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "exception: " << e.what () << endl;
    }
    return -1;
}

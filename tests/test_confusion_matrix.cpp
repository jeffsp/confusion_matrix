// Confusion matrix test
//
// jeffsp@gmail.com
//
// Sat Mar 12 12:04:17 CST 2016

#include "../confusion_matrix.h"
#include "verify.h"
#include <iostream>

using namespace std;

void test1 ()
{
    confusion_matrix cm;
    const size_t N = 1000;
    for (size_t i = 0; i < N; ++i)
        cm.update (rand () % 2, rand () % 2);
    verify (cm.true_positives () > 200 && cm.true_positives () < 300);
    verify (cm.true_negatives () > 200 && cm.true_negatives () < 300);
    verify (cm.false_positives () > 200 && cm.false_positives () < 300);
    verify (cm.false_negatives () > 200 && cm.false_negatives () < 300);
}

void test2 ()
{
    confusion_matrix cm;
    cm.update (0, 0);
    cm.update (0, 1);
    cm.update (1, 0);
    cm.update (1, 1);
    verify (cm.recall () == 0.5);
    verify (cm.precision () == 0.5);
    verify (cm.fallout () == 0.5);
    verify (cm.accuracy () == 0.5);
    verify (cm.F1 () == 0.5);
    verify (cm.MCC () == 0.0);
    cm.update (1, 1);
    verify (cm.recall () != 0.5);
    verify (cm.precision () != 0.5);
    verify (cm.fallout () == 0.5);
    verify (cm.accuracy () != 0.5);
    verify (cm.F1 () != 0.5);
    verify (cm.MCC () != 0.0);
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
    verify (cm.recall () == 0.5);
    verify (cm.precision () == 0.5);
    verify (cm.fallout () == 0.5);
    verify (cm.accuracy () == 0.5);
    verify (cm.F1 () == 0.5);
    verify (cm.MCC () == 0.0);
}

void test4 ()
{
    stringstream ss;
    ss << "1 1" << endl;
    ss << "2 1" << endl;
    ss << "1 2" << endl;
    // oops, missing prediction
    ss << "2 " << endl;
    bool caught = false;
    try { conditions conditions = read_conditions (ss); }
    catch (const exception &e) {
        clog << "caught exception... OK" << endl;
        caught = true;
    }
    verify (caught);
}

void test5 ()
{
    conditions conditions;
    confusion_matrix cm = get_confusion_matrix (conditions, 3);
    verify (cm.true_positives () == 0);
    verify (cm.true_negatives () == 0);
    verify (cm.false_positives () == 0);
    verify (cm.false_negatives () == 0);
    {
    stringstream ss;
    ss << "3 3" << endl;
    conditions = read_conditions (ss);
    cm = get_confusion_matrix (conditions, 3);
    verify (cm.true_positives () == 1);
    verify (cm.true_negatives () == 0);
    verify (cm.false_positives () == 0);
    verify (cm.false_negatives () == 0);
    }
    {
    stringstream ss;
    ss << "1 0" << endl;
    ss << "2 5" << endl;
    conditions = read_conditions (ss);
    cm = get_confusion_matrix (conditions, 3);
    verify (cm.true_positives () == 0);
    verify (cm.true_negatives () == 2);
    verify (cm.false_positives () == 0);
    verify (cm.false_negatives () == 0);
    }
    {
    stringstream ss;
    ss << "1 3" << endl;
    ss << "2 3" << endl;
    ss << "4 3" << endl;
    conditions = read_conditions (ss);
    cm = get_confusion_matrix (conditions, 3);
    verify (cm.true_positives () == 0);
    verify (cm.true_negatives () == 0);
    verify (cm.false_positives () == 3);
    verify (cm.false_negatives () == 0);
    }
    {
    stringstream ss;
    ss << "3 0" << endl;
    ss << "3 2" << endl;
    conditions = read_conditions (ss);
    cm = get_confusion_matrix (conditions, 3);
    verify (cm.true_positives () == 0);
    verify (cm.true_negatives () == 0);
    verify (cm.false_positives () == 0);
    verify (cm.false_negatives () == 2);
    }
}

int main (int argc, char **argv)
{
    try
    {
        test1 ();
        test2 ();
        test3 ();
        test4 ();
        test5 ();
        clog << "Success" << endl;

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "exception: " << e.what () << endl;
    }
    return -1;
}

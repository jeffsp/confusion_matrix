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

int main (int argc, char **argv)
{
    try
    {
        test1 ();
        clog << "Success" << endl;

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "exception: " << e.what () << endl;
    }
    return -1;
}

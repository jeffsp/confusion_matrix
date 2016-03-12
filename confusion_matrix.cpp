// confusion_matrix.cpp
//
// Program for measuring the performance of a supervised learning task
//
// jeffsp@gmail.com
//
// Sat Mar 12 08:21:45 CST 2016

#include "confusion_matrix.h"
#include <getopt.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

const string usage = "confusion_matrix [options]";

struct cmd_line_args
{
    bool help;
    bool verbose;
    size_t class_number;
    string input_filename;
};

cmd_line_args get_args (int argc, char **argv)
{
    cmd_line_args args = { false, false, 0, string() };
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = {
            {"help", no_argument, 0,  'h' },
            {"verbose", no_argument, 0,  'v' },
            {"class-number", required_argument, 0,  'c' },
            {"input-filename", required_argument, 0,  'f' },
            {0,      0,           0,  0 }
        };

        int c = getopt_long(argc, argv, "hvc:f:", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            default:
            case 0:
            case 'h':
            {
                clog << "usage:" << endl << '\t' << usage << endl << endl;
                clog << "options:" << endl;
                for (size_t i = 0; i + 1 < sizeof (long_options) / sizeof (struct option); ++i)
                {
                    clog << "\t--" << long_options[i].name << "|-" << char (long_options[i].val);
                    if (long_options[i].has_arg)
                        clog << " <arg>" << endl;
                    else
                        clog << endl;
                }
                if (c != 'h')
                    throw runtime_error ("Invalid option");
                args.help = true;
                return args;
            }
            case 'v': args.verbose = true; break;
            case 'c': args.class_number = atol (optarg); break;
            case 'f': args.input_filename = optarg; break;
        }
    }
    return args;
}

int main (int argc, char **argv)
{
    try
    {
        cmd_line_args args = get_args (argc, argv);

        // If you are getting help, exit without an error
        if (args.help)
            return 0;

        if (args.verbose)
        {
            clog << "help\t" << args.help << endl;
            clog << "verbose\t" << args.verbose << endl;
            clog << "class_number\t" << args.class_number << endl;
            clog << "input_filename\t" << args.input_filename << endl;
        }

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "exception: " << e.what () << endl;
    }
    return -1;
}

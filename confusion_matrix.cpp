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
#include <vector>

using namespace std;

const string usage = "confusion_matrix [options]";

struct cmd_line_args
{
    bool help;
    bool verbose;
    size_t class_number;
    vector<string> input_filenames;
};

cmd_line_args get_args (int argc, char **argv)
{
    cmd_line_args args = { false, false, 0, vector<string> () };
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = {
            {"help", no_argument, 0,  'h' },
            {"verbose", no_argument, 0,  'v' },
            {"class-number", required_argument, 0,  'c' },
            {0,      0,           0,  0 }
        };

        int c = getopt_long(argc, argv, "hvc:", long_options, &option_index);
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
        }
    }
    // Save off filenames on command line
    while (optind < argc)
    {
        args.input_filenames.push_back (argv[optind]);
        ++optind;
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
            clog << "class_number\t" << args.class_number << endl;
            clog << "input_filenames";
            if (args.input_filenames.empty ())
                clog << "\tnone" << endl;
            else
            {
                clog << endl;
                for (size_t i = 0; i < args.input_filenames.size (); ++i)
                    clog << "\t'" << args.input_filenames[i]  << "'" << endl;
            }
        }

        conditions conditions;

        if (args.input_filenames.empty ())
        {
            if (args.verbose)
                clog << "reading stdin" << endl;
            conditions = read_conditions (cin);
        }
        else
        {
            for (auto fn : args.input_filenames)
            {
                if (args.verbose)
                    clog << "opening " << fn << endl;
                ifstream ifs (fn);
                if (!ifs)
                    throw runtime_error ("Could not open file for reading");
                // Read into tmp
                ::conditions tmp = read_conditions (ifs);
                // Append to conditions
                conditions.insert (conditions.end(), tmp.begin(), tmp.end());
            }
        }

        if (args.verbose)
            clog << conditions.size () << " conditions read" << endl;

        confusion_matrix cm = get_confusion_matrix (conditions, args.class_number);

        cout << "true_positives " << cm.true_positives () << std::endl;
        cout << "true_negatives " << cm.true_negatives () << std::endl;
        cout << "false_positives " << cm.false_positives () << std::endl;
        cout << "false_negatives " << cm.false_negatives () << std::endl;
        cout << "recall " << cm.recall () << std::endl;
        cout << "precision " << cm.precision () << std::endl;
        cout << "accuracy " << cm.accuracy () << std::endl;
        cout << "F1 " << cm.F1 () << std::endl;
        cout << "MCC " << cm.MCC () << std::endl;
        if (args.verbose)
        {
            cout << "sensitivity " << cm.sensitivity () << std::endl;
            cout << "true_positive_rate " << cm.true_positive_rate () << std::endl;
            cout << "specificity " << cm.specificity () << std::endl;
            cout << "true_negative_rate " << cm.true_negative_rate () << std::endl;
            cout << "positive_predictive_value " << cm.positive_predictive_value () << std::endl;
            cout << "negative_predictive_value " << cm.negative_predictive_value () << std::endl;
            cout << "fallout " << cm.fallout () << std::endl;
            cout << "false_positive_rate " << cm.false_positive_rate () << std::endl;
            cout << "false_discovery_rate " << cm.false_discovery_rate () << std::endl;
            cout << "miss_rate " << cm.miss_rate () << std::endl;
            cout << "false_negative_rate " << cm.false_negative_rate () << std::endl;
        }

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "exception: " << e.what () << endl;
    }
    return -1;
}

// confusion_matrix.h
//
// Support for measuring the performance of a supervised learning task
//
// jeffsp@gmail.com
//
// Sat Mar 12 08:22:08 CST 2016

#ifndef CONFUSION_MATRIX_H
#define CONFUSION_MATRIX_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

class confusion_matrix
{
    public:
    confusion_matrix ()
        : tp (0.0)
        , tn (0.0)
        , fp (0.0)
        , fn (0.0)
    {
    }
    /// @brief Update the matrix
    /// @param present Truth value. True if class is present.
    /// @param prediction Prediction value. True if we predicted that the class is present.
    void update (bool present, bool prediction)
    {
        tp += ( present) && ( prediction); // hit
        tn += (!present) && (!prediction); // correct rejection
        fp += (!present) && ( prediction); // type I: false positive
        fn += ( present) && (!prediction); // type II: false negative
    }

    double recall () const { return true_positive_rate (); }
    double sensitivity () const { return true_positive_rate (); }
    double true_positive_rate () const { return tp / (tp + fn); }

    double specificity () const { return true_negative_rate (); }
    double true_negative_rate () const { return tn / (fp + tn); }

    double precision () const { return positive_predictive_value (); }
    double positive_predictive_value () const { return tp / (tp + fp); }

    double negative_predictive_value () const { return tn / (tn + fn); }

    double fall_out () const { return false_positive_rate (); }
    double false_positive_rate () const { return fp / (fp + tn); }

    double false_discovery_rate () const { return fp / (fp + tp); }

    double miss_rate () const { return false_negative_rate (); }
    double false_negative_rate () const { return fn / (fn + tp); }

    double accuracy () const { return (tp + tn) / (tp + tn + fp + fn); }

    // The harmonic mean of precision and sensitivity
    double F1 () const { return (2.0 * tp) / (2.0 * tp + fp + fn); }

    double MCC () const { return (tp * tn - fp * fn) / sqrt ((tp + fp) * (tp + fn) * (tn + fp) * (tn + fn)); }

    friend std::ostream& operator<< (std::ostream &s, const confusion_matrix &cm)
    {
        s << "true_positives " << static_cast<size_t> (cm.tp) << std::endl;
        s << "true_negatives " << static_cast<size_t> (cm.tn) << std::endl;
        s << "false_positives " << static_cast<size_t> (cm.fp) << std::endl;
        s << "false_negatives " << static_cast<size_t> (cm.fn) << std::endl;
        s << "recall " << cm.recall () << std::endl;
        s << "sensitivity " << cm.sensitivity () << std::endl;
        s << "true_positive_rate " << cm.true_positive_rate () << std::endl;
        s << "specificity " << cm.specificity () << std::endl;
        s << "true_negative_rate " << cm.true_negative_rate () << std::endl;
        s << "precision " << cm.precision () << std::endl;
        s << "positive_predictive_value " << cm.positive_predictive_value () << std::endl;
        s << "negative_predictive_value " << cm.negative_predictive_value () << std::endl;
        s << "fall_out " << cm.fall_out () << std::endl;
        s << "false_positive_rate " << cm.false_positive_rate () << std::endl;
        s << "false_discovery_rate " << cm.false_discovery_rate () << std::endl;
        s << "miss_rate " << cm.miss_rate () << std::endl;
        s << "false_negative_rate " << cm.false_negative_rate () << std::endl;
        s << "accuracy " << cm.accuracy () << std::endl;
        s << "F1 " << cm.F1 () << std::endl;
        s << "MCC " << cm.MCC () << std::endl;
        return s;
    }

    private:
    double tp;
    double tn;
    double fp;
    double fn;
};

using conditions = std::vector<std::pair<unsigned,unsigned>>;

// Read a file with two columns:
//
//  Column 1: truth class
//  Column 2: predicted class
//
// Class are unsigned integers
std::vector<std::pair<unsigned,unsigned>> read_conditions (std::istream &ifs)
{
    conditions conditions;
    std::pair<unsigned,unsigned> p;
    while (ifs >> p.first)
    {
        ifs >> p.second;
        if (!ifs)
            throw std::runtime_error ("Could not read predicted class");
        conditions.push_back (p);
    }
    return conditions;
}

confusion_matrix get_confusion_matrix (const conditions &conditions, unsigned class_number)
{
    confusion_matrix cm;
    // The first column is the truth class.
    //
    // The second column is the class that was predicted.
    for (auto i : conditions)
    {
        cm.update (i.first == class_number, i.second == class_number);
    }
    return cm;
}


#endif // CONFUSION_MATRIX_H

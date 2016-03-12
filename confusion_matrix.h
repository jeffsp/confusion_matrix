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
    /// @param prediction Prediction value. True if we think the class is present.
    void update (bool present, bool prediction)
    {
        tp += ( present) && ( prediction); // hit
        tn += (!present) && (!prediction); // correct rejection
        fp += (!present) && ( prediction); // type I: false positive
        fn += ( present) && (!prediction); // type II: false negative
    }

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

    double matthews_correlation_coefficient () const { return MCC (); }
    double MCC () const { return (tp * tn - fp * fn) / sqrt ((tp + fp) * (tp + fn) * (tn + fp) * (tn + fn)); }

    friend std::ostream& operator<< (std::ostream &s, const confusion_matrix &cm)
    {
        s << "tp\t" << static_cast<size_t> (cm.tp) << std::endl;
        s << "tn\t" << static_cast<size_t> (cm.tn) << std::endl;
        s << "fp\t" << static_cast<size_t> (cm.fp) << std::endl;
        s << "fn\t" << static_cast<size_t> (cm.fn) << std::endl;
        s << "sensitivity\t" << cm.sensitivity () << std::endl;
        s << "true_positive_rate\t" << cm.true_positive_rate () << std::endl;
        s << "specificity\t" << cm.specificity () << std::endl;
        s << "true_negative_rate\t" << cm.true_negative_rate () << std::endl;
        s << "precision\t" << cm.precision () << std::endl;
        s << "positive_predictive_value\t" << cm.positive_predictive_value () << std::endl;
        s << "negative_predictive_value\t" << cm.negative_predictive_value () << std::endl;
        s << "fall_out\t" << cm.fall_out () << std::endl;
        s << "false_positive_rate\t" << cm.false_positive_rate () << std::endl;
        s << "false_discovery_rate\t" << cm.false_discovery_rate () << std::endl;
        s << "miss_rate\t" << cm.miss_rate () << std::endl;
        s << "false_negative_rate\t" << cm.false_negative_rate () << std::endl;
        s << "accuracy\t" << cm.accuracy () << std::endl;
        s << "F1\t" << cm.F1 () << std::endl;
        s << "matthews_correlation_coefficient\t" << cm.matthews_correlation_coefficient () << std::endl;
        s << "MCC\t" << cm.MCC () << std::endl;
        return s;
    }

    private:
    double tp;
    double tn;
    double fp;
    double fn;
};

#endif // CONFUSION_MATRIX_H

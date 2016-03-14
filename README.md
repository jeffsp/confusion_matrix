# Confusion Matrix

Program for reading two columns of text and printing confusion matrix and
derived measures.

# Examples

    $ confusion_matrix -h
    usage:
        confusion_matrix [options]

    options:
        --help|-h
        --verbose|-v
        --class-number|-c <arg>
        --input-filename|-f <arg>

    $ confusion_matrix
    0 0
    0 1
    0 0
    1 1
    0 0
    1 0
    0 1
    true_positives 3
    true_negatives 1
    false_positives 1
    false_negatives 2
    recall 0.6
    precision 0.75
    accuracy 0.571429
    F1 0.666667
    MCC 0.0912871

    $ cat data.txt
    3 3
    3 0
    3 1
    1 3
    1 2
    1 1
    3 3
    2 4
    3 3
    3 3

    $ cat data.txt | confusion_matrix -c 3
    true_positives 4
    true_negatives 3
    false_positives 1
    false_negatives 2
    recall 0.666667
    precision 0.8
    accuracy 0.7
    F1 0.727273
    MCC 0.408248

    $ confusion_matrix -c 1 data.txt
    true_positives 1
    true_negatives 6
    false_positives 1
    false_negatives 2
    recall 0.333333
    precision 0.5
    accuracy 0.7
    F1 0.4
    MCC 0.218218

    $ confusion_matrix -c 3 -v < data.txt
    class_number    3
    input_filename ''
    reading stdin
    10 conditions read
    true_positives 4
    true_negatives 3
    false_positives 1
    false_negatives 2
    recall 0.666667
    precision 0.8
    accuracy 0.7
    F1 0.727273
    MCC 0.408248
    sensitivity 0.666667
    true_positive_rate 0.666667
    specificity 0.75
    true_negative_rate 0.75
    positive_predictive_value 0.8
    negative_predictive_value 0.6
    fallout 0.25
    false_positive_rate 0.25
    false_discovery_rate 0.2
    miss_rate 0.333333
    false_negative_rate 0.333333

# Makefile for confusion matrix
#
# jeffsp@gmail.com
#
# Sat Mar 12 08:45:04 CST 2016

BUILD=debug
#BUILD=release

.PHONY : \
default
default: waf

.PHONY : \
waf
waf:
	waf configure
	waf
	$(MAKE) -C tests waf

.PHONY : \
check
check:
	$(MAKE) -C tests check

.PHONY : \
cmd_line_check
cmd_line_check:
	./build/$(BUILD)/confusion_matrix --help
	./build/$(BUILD)/confusion_matrix -h
	./build/$(BUILD)/confusion_matrix --verbose < /dev/null | grep true_positives
	./build/$(BUILD)/confusion_matrix -v -c 9 < /dev/null | grep true_positives
	./build/$(BUILD)/confusion_matrix -v --class-number 8 < /dev/null | grep true_positives

.PHONY : \
clean
clean:
	waf clean
	$(MAKE) -C tests clean

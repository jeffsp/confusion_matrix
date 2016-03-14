# Makefile for confusion matrix tests
#
# jeffsp@gmail.com
#
# Sun Mar 13 21:50:51 CDT 2016

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

.PHONY : \
check
check:
	./build/$(BUILD)/test_confusion_matrix

.PHONY : \
clean
clean:
	waf clean

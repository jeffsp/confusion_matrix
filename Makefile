# Makefile for C++ minimal waf wscript
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

.PHONY : \
check
check:
	./build/$(BUILD)/confusion_matrix -h
	./build/$(BUILD)/confusion_matrix --help
	./build/$(BUILD)/confusion_matrix --verbose
	./build/$(BUILD)/confusion_matrix -v -c 9
	./build/$(BUILD)/confusion_matrix -v --class-number 8
	./build/$(BUILD)/confusion_matrix -v -f data1.txt
	./build/$(BUILD)/confusion_matrix -v --input-filename data2.txt
	./build/$(BUILD)/confusion_matrix -v -c 100 --input-filename data3.txt
	-./build/$(BUILD)/confusion_matrix --blah
	#./build/$(BUILD)/confusion_matrix < data.txt
	./build/$(BUILD)/test_confusion_matrix

.PHONY : \
clean
clean:
	waf clean

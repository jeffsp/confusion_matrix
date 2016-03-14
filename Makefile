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
	./build/$(BUILD)/test_confusion_matrix

.PHONY : \
cmd_line_check
cmd_line_check:
	./build/$(BUILD)/confusion_matrix -h
	./build/$(BUILD)/confusion_matrix --help
	./build/$(BUILD)/confusion_matrix --verbose < /dev/null
	./build/$(BUILD)/confusion_matrix -v -c 9 < /dev/null
	./build/$(BUILD)/confusion_matrix -v --class-number 8 < /dev/null
	./build/$(BUILD)/confusion_matrix -v -f /dev/null
	./build/$(BUILD)/confusion_matrix -v --input-filename /dev/null
	./build/$(BUILD)/confusion_matrix -v -c 100 --input-filename /dev/null
	-./build/$(BUILD)/confusion_matrix --blah < /dev/null
	-./build/$(BUILD)/confusion_matrix filename.txt

.PHONY : \
clean
clean:
	waf clean

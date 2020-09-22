APPNAME = array_thrsafe_rwlock

$(APPNAME): main.c array.c
	cc -g -Wall -Wextra main.c array.c -o $(APPNAME) -pthread -lm


.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)

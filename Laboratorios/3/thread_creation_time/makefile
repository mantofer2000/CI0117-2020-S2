APPNAME = thread_creation_time

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -pthread -lm


.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


#thread_creation_time.out : thread_creation_time.c
#	gcc thread_creation_time.c -pthread -o thread_creation_time.out

#clean:
#	rm -rf *.out *.o *.exe
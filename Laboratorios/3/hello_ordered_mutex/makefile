
APPNAME = hello_ordered_mutex

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -pthread -lm

.PHONY: clean
clean:
	rm -f  $(APPNAME)


#hello_ordered_mutex.out : hello_ordered_mutex.c
#	gcc hello_ordered_mutex.c -pthread -o hello_ordered_mutex.out

#clean:
#	rm -rf *.out *.o *.exe



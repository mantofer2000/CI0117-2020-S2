APPNAME = barbershop

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -pthread -lm

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore



.PHONY: clean
clean:
	rm -f  $(APPNAME)


#hello_ordered_semaphore.out : hello_ordered_semaphore.c
#	gcc hello_ordered_semaphore.c -pthread -o hello_ordered_semaphore.out

#clean:
#	rm -rf *.out *.o *.exe
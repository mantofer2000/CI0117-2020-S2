APPNAME = count_primes_serial

$(APPNAME): $(APPNAME).cpp
	g++ -g -Wall -Wextra $(APPNAME).cpp -o $(APPNAME) 

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


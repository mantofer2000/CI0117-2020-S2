APPNAME = count_primes_cyclic

$(APPNAME): $(APPNAME).cpp
	g++ -g -Wall -Wextra $(APPNAME).cpp -o $(APPNAME) -fopenmp -lm 

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


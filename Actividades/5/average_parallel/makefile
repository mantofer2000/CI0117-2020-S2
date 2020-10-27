APPNAME = average_parallel

$(APPNAME): $(APPNAME).cpp
	g++ -g -Wall -Wextra $(APPNAME).cpp -o $(APPNAME) -fopenmp -lm -std=c99

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


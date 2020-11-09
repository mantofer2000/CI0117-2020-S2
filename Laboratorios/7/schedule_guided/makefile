APPNAME = schedule_guided

$(APPNAME): $(APPNAME).cpp
	g++ -g -Wall -Wextra $(APPNAME).cpp -o $(APPNAME) -fopenmp

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


APPNAME = riemann_openmp

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -fopenmp -lm -std=c99

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


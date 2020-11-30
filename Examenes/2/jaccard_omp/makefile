APPNAME = jaccard_omp

$(APPNAME): $(APPNAME).cpp
	g++ -Wall -Wextra $(APPNAME).cpp -o $(APPNAME) -fopenmp 

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore

.PHONY: clean
clean:
	rm -f  $(APPNAME)


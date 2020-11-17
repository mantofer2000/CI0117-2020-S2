APPNAME = random_number_allreduce

$(APPNAME): $(APPNAME).cpp
	mpic++ $(APPNAME).cpp -o $(APPNAME) 

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


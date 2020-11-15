APPNAME = ping_pong

$(APPNAME): $(APPNAME).cpp
	mpic++ $(APPNAME).cpp -o $(APPNAME) 

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


APPNAME = dna_sequences

$(APPNAME):  main.c acid_counter.c dna_sequence.c
	cc -g -Wall -Wextra main.c acid_counter.c dna_sequence.c -o $(APPNAME) -pthread 
	#cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -pthread -lm -std=c99

.PHONY: gitignore
gitignore:
	echo $(APPNAME) > .gitignore


.PHONY: clean
clean:
	rm -f  $(APPNAME)


#
# UTD CS3377.501
# Michael Teeple
# mxt151430@utdallas.edu
#

CXX = g++ -std=c++11 -g
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#Project name is program6

SRCS =cdkexample.cc
EXECFILE = program6
OBJS = cdkexample.o

all: $(EXECFILE)
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

#Backup
backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H.%M.%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@tar cfvz $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

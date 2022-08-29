NAME          := $(shell head -n 1 config.txt)


CC            := g++
HEADERS       := $(wildcard *.h)
SOURCES       := $(wildcard *.cpp)
PROG          := $(NAME)
RESOURCES_RES := resource.res
OBJ           := Server.o Client.o Game.o WinMain.o 
LIB_LINKS     := -lgdi32 -lgdiplus -lws2_32
SUBSYS        := -Wl,-subsystem,console


run: cls $(PROG)
	./exec.bat $(PROG)

r: cls $(PROG) 

a:  
ifneq ("$(wildcard ./$(PROG))","")
	./$(PROG)
else
	@ECHO ""
	@ECHO "$(PROG)"
	@ECHO ""
	@ECHO "compilation running ....."
	@ECHO ""
	make run
	@ECHO ""
	@ECHO "finished"
	@ECHO ""
endif

$(PROG): $(OBJ) $(RESOURCES_RES)
	$(CC) $^ -o $@ $(LIB_LINKS) $(SUBSYS) 

%.o: %.cpp
	$(CC) -c $< 

%.res: %.rc
	WINDRES $< -O coff -o $@

clean:
	@rm -f *.o *.res *.exe *.exe.stackdump *.bak

cls: clean



CC    = g++
FLAG  = -std=c++0x
SRC   = Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o LogMessage.o
good : Date User Meeting Storage AgendaService AgendaUI LogMessage main.cpp
	$(CC) $(FLAG) main.cpp $(SRC) -o good
LogMessage : LogMessage.cpp
	$(CC) $(FLAG) -c LogMessage.cpp
Date : Date.cpp
	$(CC) $(FLAG) -c Date.cpp
User : User.cpp Date
	$(CC) $(FLAG) -c User.cpp
Meeting : Meeting.cpp User Date
	$(CC) $(FLAG) -c Meeting.cpp
Storage : Storage.cpp User Meeting Date
	$(CC) $(FLAG) -c Storage.cpp
AgendaService : AgendaService.cpp User Meeting Date Storage
	$(CC) $(FLAG) -c AgendaService.cpp
AgendaUI : AgendaUI.cpp Date User Meeting Storage AgendaService
	$(CC) $(FLAG) -c AgendaUI.cpp
clean:
	rm *.o *.data good

#ifndef AGENDAUI_H
#define AGENDAUI_H

#ifdef WIN32
#include "SnakeGame.h"
#endif

#include "AgendaService.h"
#include "LogMessage.h"

#include <iostream>
#include <string>
#include <iomanip>

class AgendaUI {
 protected:
  LogMessage log;   //LOG IN UI
 public:
  AgendaUI();
  void OperationLoop(void);

 private:
  // task functions
  void startAgenda(void);
  void showMenu(void);
  std::string getOperation();
  bool executeOperation(std::string op);
  void userLogIn(void);
  void userRegister(void);
  void updateUser(void);
  void quitAgenda(void);
  void userLogOut(void);
  void deleteUser(void);
  void listAllUsers(void);
  void createMeeting(void);
  void listAllMeetings(void);
  void listAllSponsorMeetings(void);
  void listAllParticipateMeetings(void);
  void queryMeetingByTitle(void);
  void queryMeetingByTimeInterval(void);
  void deleteMeetingByTitle(void);
  void deleteAllMeetings(void);
  void printMeetings(std::list<Meeting> meetings);
  // dates
  std::string userName_;
  std::string userPassword_;
  bool sudo;
  AgendaService agendaService_;
#ifdef WIN32
  SnakeGame game;
#endif
};

#endif


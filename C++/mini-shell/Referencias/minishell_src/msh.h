#ifndef MSH_H
#define MSH_H
#define FOREGROUND 'F'
#define BACKGROUND 'B'
#define SUSPENDED 'S'
#define WAITING_INPUT 'W'

void populateCommand();
void destroyCommand();
insertJob();
delJob();
getJob();
void printJobs();
void welcomeScreen();
void shellPrompt();
void handleUserCommand();
int checkBuiltInCommands();
void executeCommand();
void launchJob();
void putJobForeground();
void putJobBackground();
void waitJob(t_job* job);
void killJob(int jobId);
void changeDirectory();
void init();
void signalHandler_child(int p);
#endif

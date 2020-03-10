//////////////////////////////////////////////////////////////////////////////////
// This program tries to catch every signal, enter 'q' in your terminal to quit //
//////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define NUMSIGNALS 31
#define EXIT 0

typedef unsigned char byte;

typedef struct {
    int num;
    char name[10];
} signal_tt;

// Most possible signals
signal_tt signals[] = {

    { SIGHUP, "SIGHUP" },
    { SIGINT, "SIGINT" },
    { SIGQUIT, "SIGQUIT" },
    { SIGILL, "SIGILL" },
    { SIGTRAP, "SIGTRAP" },
    { SIGABRT, "SIGABRT" },
    { SIGBUS, "SIGBUS" },
    { SIGFPE, "SIGFPE" },
    { SIGKILL, "SIGKILL" },
    { SIGUSR1, "SIGUSR1" },
    { SIGSEGV, "SIGSEGV" },
    { SIGUSR2, "SIGUSR2" },
    { SIGPIPE, "SIGPIPE" },
    { SIGALRM, "SIGALRM" },
    { SIGTERM, "SIGTERM" },
    { SIGSTKFLT, "SIGSTKFLT" },
    { SIGCHLD, "SIGCHLD" },
    { SIGCONT, "SIGCONT" },
    { SIGSTOP, "SIGSTOP" },
    { SIGTSTP, "SIGTSTP" },
    { SIGTTIN, "SIGTTIN" },
    { SIGTTOU, "SIGTTOU" },
    { SIGURG, "SIGURG" },
    { SIGXCPU, "SIGXCPU" },
    { SIGXFSZ, "SIGXFSZ" },
    { SIGVTALRM, "SIGVTALRM" },
    { SIGPROF, "SIGPROF" },
    { SIGWINCH, "SIGWINCH" },
    { SIGIO, "SIGIO" },
    { SIGPWR, "SIGPWR" },
    { SIGSYS, "SIGSYS" }

};

char* getname(int sig) {

    for (int i = 0; i < NUMSIGNALS; i++) {
        if (signals[i].num == sig) {
            return signals[i].name;
        }
    }

    return NULL;

}

void handler(int sig) {

    printf("Received signal num %d: %s\n", sig, getname(sig));

    if (EXIT)
        exit(1);

}

int main(int argc, char **argv) {

    struct sigaction sa = { 0 };

    sa.sa_handler = handler;

    for (int i = 0; i < NUMSIGNALS; i++) {
        sigaction(i, &sa, NULL);
    }

    for (;;) {
        char c = getchar();
        if (c == 'q') { // This, aside from SIGKILL is one of the only ways to exit the program
            break;
        }
    }

}
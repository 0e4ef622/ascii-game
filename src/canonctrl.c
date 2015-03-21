#include <termios.h>

struct termios old_term, new_term;

void termNonCanon() {
    tcgetattr(0, &old_term);
    new_term = old_term;
    new_term.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(0, TCSANOW, &new_term);
}

void termReset() {
    tcsetattr(0, TCSANOW, &old_term);
}

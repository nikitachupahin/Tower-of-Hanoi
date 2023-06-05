#include "move.h"

Move::Move(int f, int t):
    from(f),
    to(t)
    {
    };

Move::Move():
    from(0),
    to(0)
    {
    };

int Move::getFrom(){
    return from;
}

int Move::getTo(){
    return to;
}

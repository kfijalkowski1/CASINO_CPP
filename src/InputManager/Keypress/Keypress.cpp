#include "Keypress.h"

Keypress::Keypress(char input) : arrow(false), character(input) {}
Keypress::Keypress(Direction direction) : arrow(true), direction(direction) {}
#ifndef CELL_H
#define CELL_H

#include <iostream>

class Cell
{
int value;
bool checked;

public:
Cell(int v);
Cell(int v, bool c);
~Cell();

int getValue() const;
bool ischecked() const;
void check();
void uncheck();
void reverse_check();

void printcell(std::ostream &os) const;

};

#endif

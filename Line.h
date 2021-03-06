#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Cell.h"

class Line
{
std::vector<Cell*> line;
bool isfull;
size_t line_size;

public:
Line(std::vector<int> v);
~Line();
Line(const Line& old);

bool islinefull() const;
void setfull(bool b);
size_t getSize() const;
Cell* getCell(size_t i) const;
size_t getIndex(int v) const;
int containsValue(int v) const;
bool checkvalue(int v);
bool uncheckvalue(int v);
bool reverse_checkvalue(int v);
std::vector<int> getValues() const;

Line& operator=(const Line& old);

void printLine(std::ostream &os) const;
};

std::ostream& operator<<(std::ostream &os, Line const& L);

#endif

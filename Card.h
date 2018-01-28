#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Cell.h"
#include "Line.h"

class Card
{
std::vector<Line*> card;
bool isfull;
size_t card_size;
size_t nb_values_left;
size_t card_id;

public:
Card(std::vector<std::vector<int> > v);
Card(std::vector<std::vector<int> > v, bool b);
~Card();

bool iscardfull();
void set_linefull(size_t i, bool b);
void set_cardfull(bool b);
size_t getSize() const;
Line* getLine(size_t i) const;
Cell* getCell(size_t i, size_t j) const;
size_t getRValues() const;
size_t getID() const;
//size_t getIndex(int v) const;
int containsValue(int v) const;
size_t checkvalue(int v);
size_t uncheckvalue(int v);
size_t reverse_checkvalue(int v);
std::vector<std::vector<int> > getValues() const;

void printCard(std::ostream &os) const;
};

#endif

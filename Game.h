#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Cell.h"
#include "Line.h"
#include "Card.h"

class Game
{
std::vector<Card*> game;
size_t min_card;
std::vector<size_t> id_min;

public:
Game(std::vector<std::vector<std::vector<int> > > v);
Game(std::vector<std::vector<std::vector<int> > > v, bool b);
~Game();

size_t getSize() const;
Line* getLine(size_t ca, size_t l) const;
Cell* getCell(size_t ca, size_t l, size_t ce) const;
Card* getCard(size_t ca) const;
// size_t getRValues() const;
std::vector<size_t> containsValue(int v) const;
std::vector<size_t> checkvalue(int v);
std::vector<size_t> uncheckvalue(int v);
std::vector<size_t> reverse_checkvalue(int v);
std::vector<std::vector<int> > getValues() const;

void printGame(std::ostream &os) const;
};


std::ostream& operator<<(std::ostream &os, Game const& G);

#endif

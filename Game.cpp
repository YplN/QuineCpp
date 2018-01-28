#include "Line.h"
#include "Cell.h"
#include "Card.h"
#include "Game.h"
#include <assert.h>

Game::Game(std::vector<std::vector<std::vector<int> > > v)
{
        // bool isfull = true;
        size_t min_c, line, tmp;
        std::vector<size_t> id_min;

        // if(!v.empty())
        size_t ca;        // = 0;
        size_t l;
        // size_t ce = 0;

        while(ca<v.size())
        {
                line = 0;
                while(l<v.at(ca).size())
                {
                        line+=v.at(ca).at(l).size();
                        // std::cout<<v.at(ca).at(l)<<std::endl;
                        std::sort(v.at(ca).at(l).begin(), v.at(ca).at(l).end());
                        l++;
                }
                tmp = min_c;
                min_c = line<min_c ? line : min_c;
                if(tmp!=min_c)
                        id_min.erase(id_min.begin(), id_min.end());
                else
                        id_min.push_back(l);

                ca++;
        }

        this->min_card = min_c;
        this->game = std::vector<Card*>();
        this->id_min = id_min;
        for (size_t i = 0; i < v.size(); i++) {
                this->game.push_back(new Card(v.at(i)));
        }

        // this->card_size = v.size();
        // this->isfull = isfull;
}

Game::Game(std::vector<std::vector<std::vector<int> > > v, bool b)
{

        // bool isfull = true;
        size_t min_c, line, tmp;
        std::vector<size_t> id_min;

        // if(!v.empty())
        size_t ca;        // = 0;
        size_t l;
        // size_t ce = 0;

        while(ca<v.size())
        {
                line = 0;
                while(l<v.at(ca).size())
                {
                        line+=v.at(ca).at(l).size();
                        // std::cout<<v.at(ca).at(l)<<std::endl;
                        std::sort(v.at(ca).at(l).begin(), v.at(ca).at(l).end());
                        l++;
                }
                tmp = min_c;
                min_c = line<min_c ? line : min_c;
                if(tmp!=min_c)
                        id_min.erase(id_min.begin(), id_min.end());
                else
                        id_min.push_back(l);

                ca++;
        }

        this->min_card = min_c;
        this->game = std::vector<Card*>();
        this->id_min = id_min;
        for (size_t i = 0; i < v.size(); i++) {
                this->game.push_back(new Card(v.at(i), b));
        }

        // this->card_size = v.size();
        // this->isfull = isfull;
}

Game::~Game()
{
        while(!this->game.empty())
        {
                delete this->game.back();
                this->game.pop_back();
        }

}
//
// bool Card::iscardfull()
// {
//         return this->isfull;
// }

size_t Game::getSize() const
{
        return this->game.size();
}
//
// size_t Card::getRValues() const
// {
//         return this->nb_values_left;
// }
//
Card* Game::getCard(size_t ca) const
{
        assert(ca<this->getSize());
        return this->game.at(ca);
}

Line* Game::getLine(size_t ca, size_t li) const
{
        assert(ca<this->getSize() && li<this->getCard(ca)->getSize());
        return this->getCard(ca)->getLine(li);
}

Cell* Game::getCell(size_t ca, size_t li, size_t ce) const
{
        assert(ca<this->getSize() && li<this->getCard(ca)->getSize() && ce<this->getCard(ca)->getLine(li)->getSize());
        return this->getCard(ca)->getLine(li)->getCell(ce);
}

// // size_t Card::getIndex(int v) const
// // {
// //         assert(this->containsValue(v));
// //         return this->containsValue(v);
// // }
//
// void Card::set_linefull(size_t i, bool b)
// {
//         this->card.at(i)->setfull(b);
// }
//
// void Card::set_cardfull(bool b)
// {
//         this->isfull = b;
// }
//
// returns empty vector if v is not in any cards, the vector conataining all the cards where there is an occurence of v otherwise
std::vector<size_t> Game::containsValue(int v) const
{
        std::vector<size_t> cards_with_value;
        for (size_t i = 0; i < this->getSize(); i++) {
                if(this->getCard(i)->containsValue(v)!=-1)
                        cards_with_value.push_back(i);

        }
        return cards_with_value;
}
//
// std::vector<size_t> Game::checkvalue(int v) {
//         std::vector<size_t> remaining_cells;
//         for (size_t ca = 0; ca < this->getSize(); ca++) {
//
//         }
// }
//


// size_t Card::uncheckvalue(int v)
// {
//         int is_in_line = this->containsValue(v);
//         if(is_in_line >= 0)
//         {
//                 int is_in = this->getLine(is_in_line)->containsValue(v);
//                 if(this->getCell(is_in_line, is_in)->ischecked())
//                 {
//                         this->getLine(is_in_line)->uncheckvalue(v);
//                         this->nb_values_left++;
//                         this->isfull = false;
//                 }
//                 return this->nb_values_left;
//         }
//         else
//                 return this->nb_values_left;
// }
//
// size_t Card::reverse_checkvalue(int v)
// {
//         int is_in_line = this->containsValue(v);
//         if(is_in_line >= 0)
//         {
//
//                 int is_in = this->getLine(is_in_line)->containsValue(v);
//                 if(this->getCell(is_in_line, is_in)->ischecked())
//                 {
//                         this->getLine(is_in_line)->uncheckvalue(v);
//                         this->nb_values_left++;
//                 }
//                 else
//                 {
//                         this->getLine(is_in_line)->checkvalue(v);
//                         this->nb_values_left--;
//                 }
//
//
//                 // if(this->getLine(is_in_line)->islinefull() == false)
//                 // {
//                 //         this->nb_values_left++;
//                 //         return false;
//                 // }
//                 //
//                 // this->nb_values_left--;
//
//                 // size_t i = 0;
//                 // while (i<this->card->getSize() && this->card->getLine(i)->ischecked())
//                 //         i++;
//
//                 this->isfull = (this->nb_values_left == 0);
//                 return this->nb_values_left;
//
//         }
//         else
//                 return this->nb_values_left;
// }
//
//
// std::vector<std::vector<int> > Card::getValues() const
// {
//         std::vector<std::vector<int> > v;
//         for (size_t i = 0; i < this->getSize(); i++) {
//                 v.push_back(this->getLine(i)->getValues());
//         }
//
//         return v;
// }
//
void Game::printGame(std::ostream &os) const
{
        for (size_t i = 0; i < this->getSize(); i++) {
                os<<"["<<this->getCard(i)->getID()<<"] ";
                this->getCard(i)->printCard(os);
                os<<std::endl;
        }
}

std::ostream& operator<<(std::ostream &os, Game const& G)
{
        G.printGame(os);
        return os;
}

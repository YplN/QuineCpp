#include "Line.h"
#include "Cell.h"
#include "Card.h"
#include <assert.h>

Card::Card(std::vector<std::vector<int> > v)
{
        bool isfull = true;
        for (size_t i = 0; i < v.size(); i++) {
                isfull = isfull && v.at(i).empty();
                for (size_t j = 0; j < v.at(i).size(); j++) {
                        std::sort(v.at(i).begin(), v.at(i).end());
                }
        }

        this->nb_values_left = 0;
        this->card = std::vector<Line*>();
        for (size_t i = 0; i < v.size(); i++) {
                this->card.push_back(new Line(v.at(i)));
                this->nb_values_left+=v.at(i).size();
        }

        this->card_size = v.size();
        this->isfull = isfull;
        // std::sort(v.begin(), v.end());
        // this->line = std::vector<Cell*>();
        // for (size_t i = 0; i < v.size(); i++) {
        //         this->line.push_back(new Cell(v.at(i)));
        // }
        // this->line_size = v.size();
}


Card::Card(std::vector<std::vector<int> > v, bool b)
{
        // if the boolean is true, the first vector only contains the ID
        if(b && !v.empty() && !v.at(0).empty())
        {
                this->card_id = v.at(0).at(0);
                v.erase(v.begin());
        }

        bool isfull = true;
        for (size_t i = 0; i < v.size(); i++) {
                isfull = isfull && v.at(i).empty();
                for (size_t j = 0; j < v.at(i).size(); j++) {
                        std::sort(v.at(i).begin(), v.at(i).end());
                }
        }

        this->nb_values_left = 0;
        this->card = std::vector<Line*>();
        for (size_t i = 0; i < v.size(); i++) {
                this->card.push_back(new Line(v.at(i)));
                this->nb_values_left+=v.at(i).size();
        }

        this->card_size = v.size();
        this->isfull = isfull;
        // std::sort(v.begin(), v.end());
        // this->line = std::vector<Cell*>();
        // for (size_t i = 0; i < v.size(); i++) {
        //         this->line.push_back(new Cell(v.at(i)));
        // }
        // this->line_size = v.size();
}

Card::~Card()
{
        while(!this->card.empty())
        {
                delete this->card.back();
                this->card.pop_back();
        }
        // while(!this->line.empty())
        // {
        //         delete this->line.back();
        //         this->line.pop_back();
        // }

}

bool Card::iscardfull()
{
        return this->isfull;
}

size_t Card::getSize() const
{
        return this->card_size;
}

size_t Card::getRValues() const
{
        return this->nb_values_left;
}

size_t Card::getID() const
{
        return this->card_id;
}

Line* Card::getLine(size_t i) const
{
        assert(i<this->getSize());
        return this->card.at(i);
}

Cell* Card::getCell(size_t i, size_t j) const
{
        assert(i<this->getSize() && j<this->getLine(i)->getSize());
        return this->getLine(i)->getCell(j);
}

// size_t Card::getIndex(int v) const
// {
//         assert(this->containsValue(v));
//         return this->containsValue(v);
// }

void Card::set_linefull(size_t i, bool b)
{
        this->card.at(i)->setfull(b);
}

void Card::set_cardfull(bool b)
{
        this->isfull = b;
}


// returns -1 if v is not in any lines, the index of the 1st occurence otherwise
int Card::containsValue(int v) const
{
        // We assume the lines are all sorted
        size_t i = 0;
        while(i<this->getSize() && this->card.at(i)->containsValue(v) == -1)
                i++;
        if (i==this->getSize())
                return -1;
        else
                return i;
}

size_t Card::checkvalue(int v) {
        int is_in_line = this->containsValue(v);
        if(is_in_line >= 0)
        {
                int is_in = this->getLine(is_in_line)->containsValue(v);
                if(!this->getCell(is_in_line, is_in)->ischecked())
                {
                        this->getLine(is_in_line)->checkvalue(v);
                        this->nb_values_left--;
                        // size_t i = 0;
                        // while (i<this->getSize() && this->card.at(i)->islinefull())
                        //         i++;
                        //
                        this->isfull = (nb_values_left == 0);
                }
                return this->nb_values_left;

        }
        else
                return this->nb_values_left;
}



size_t Card::uncheckvalue(int v)
{
        int is_in_line = this->containsValue(v);
        if(is_in_line >= 0)
        {
                int is_in = this->getLine(is_in_line)->containsValue(v);
                if(this->getCell(is_in_line, is_in)->ischecked())
                {
                        this->getLine(is_in_line)->uncheckvalue(v);
                        this->nb_values_left++;
                        this->isfull = false;
                }
                return this->nb_values_left;
        }
        else
                return this->nb_values_left;
}

size_t Card::reverse_checkvalue(int v)
{
        int is_in_line = this->containsValue(v);
        if(is_in_line >= 0)
        {

                int is_in = this->getLine(is_in_line)->containsValue(v);
                if(this->getCell(is_in_line, is_in)->ischecked())
                {
                        this->getLine(is_in_line)->uncheckvalue(v);
                        this->nb_values_left++;
                }
                else
                {
                        this->getLine(is_in_line)->checkvalue(v);
                        this->nb_values_left--;
                }


                // if(this->getLine(is_in_line)->islinefull() == false)
                // {
                //         this->nb_values_left++;
                //         return false;
                // }
                //
                // this->nb_values_left--;

                // size_t i = 0;
                // while (i<this->card->getSize() && this->card->getLine(i)->ischecked())
                //         i++;

                this->isfull = (this->nb_values_left == 0);
                return this->nb_values_left;

        }
        else
                return this->nb_values_left;
}


std::vector<std::vector<int> > Card::getValues() const
{
        std::vector<std::vector<int> > v;
        for (size_t i = 0; i < this->getSize(); i++) {
                v.push_back(this->getLine(i)->getValues());
        }

        return v;
}

void Card::printCard(std::ostream &os) const
{
        if(this->nb_values_left != 0)
                os<<"("<<this->nb_values_left<<")"<<std::endl;
        else
                os<<"[CARTON PLEIN]"<<std::endl;
        for (size_t i = 0; i < this->getSize(); i++) {
                os<<"[";
                if(this->getLine(i)->islinefull())
                        os<<"OK] ";
                else
                        os<<"NO] ";
                this->getLine(i)->printLine(os);
                os<<std::endl;
        }
}


std::ostream& operator<<(std::ostream &os, Card const& C)
{
        C.printCard(os);
        return os;
}

#include "Line.h"
#include "Cell.h"
#include <assert.h>

Line::Line(std::vector<int> v)
{
        std::sort(v.begin(), v.end());
        this->line = std::vector<Cell*>();
        for (size_t i = 0; i < v.size(); i++) {
                this->line.push_back(new Cell(v.at(i)));
        }
        this->line_size = v.size();
        this->isfull = false;
}
Line::~Line()
{
        while(!this->line.empty())
        {
                delete this->line.back();
                this->line.pop_back();
        }

}

bool Line::islinefull() const
{
        return this->isfull;
}

size_t Line::getSize() const
{
        return this->line_size;
}

Cell* Line::getCell(size_t i) const
{
        assert(i<this->getSize());
        return this->line.at(i);
}

size_t Line::getIndex(int v) const
{
        assert(this->containsValue(v));
        return this->containsValue(v);
}

void Line::setfull(bool b)
{
        this->isfull = b;
}


// returns -1 if v is not in the vector, the index otherwise
int Line::containsValue(int v) const
{
        // We assume the vector is sorted
        size_t i = 0;
        while (i<this->line.size() && this->line.at(i)->getValue()<v)
                i++;
        if (i==this->line.size() || this->line.at(i)->getValue()>v)
                return -1;
        else
                return i;
}

bool Line::checkvalue(int v) {
        int is_in = this->containsValue(v);
        if(is_in >= 0)
        {
                this->line.at(is_in)->check();
                size_t i = 0;
                while (i<this->line.size() && this->line.at(i)->ischecked())
                        i++;

                // if(i==this->line.size())
                //         std::cout<<"Hey!"<<std::endl;
                // else
                //         std::cout<<"Ho!"<<std::endl;
                this->isfull = (i==this->line.size());
                return this->isfull;

        }
        else
                return this->isfull;
}



bool Line::uncheckvalue(int v)
{
        int is_in = this->containsValue(v);
        if(is_in >= 0)
        {
                this->line.at(is_in)->uncheck();
                this->isfull = false;
                return this->isfull;
        }
        else
                return this->isfull;
}

bool Line::reverse_checkvalue(int v)
{
        int is_in = this->containsValue(v);
        if(is_in >= 0)
        {
                this->line.at(is_in)->reverse_check();
                if(this->line.at(is_in) == false)
                        return false;

                size_t i = 0;
                while (i<this->line.size() && this->line.at(i)->ischecked())
                        i++;

                this->isfull = (i==this->line.size());
                return this->isfull;

        }
        else
                return this->isfull;
}


std::vector<int> Line::getValues() const
{
        std::vector<int> v;
        for (size_t i = 0; i < this->line.size(); i++) {
                v.push_back(this->line.at(i)->getValue());
        }

        return v;
}

Line& Line::operator=(const Line old)
{
        if(&old == this)
                return *this;

        std::cout<<"Coucou?"<<std::endl;

        std::vector<Cell*> c;
        std::vector<int> v = old.getValues();

        for (size_t i = 0; i < old.getSize(); i++) {
                Cell ce(old.getCell(i)->getValue(), old.getCell(i)->ischecked());
                // std::cout<<"Euuh..."<<std::endl;
                // c.push_back(new Cell(old.getCell(i)->getValue(), old.getCell(i)->ischecked()));
                ce.printcell(std::cout);
                c.push_back(&ce);
        }

        this->line = c;
        this->isfull = old.islinefull();
        this->line_size = old.getSize();

        return *this;
}


void Line::printLine(std::ostream &os) const
{
        for (size_t i = 0; i < this->line.size(); i++) {
                this->line.at(i)->printcell(os);
                os<<" ";
        }
        if(this->isfull)
                os<<" <";
}

#include "Cell.h"

Cell::Cell(int v) : value(v), checked(false){
}
Cell::Cell(int v, bool c) : value(v), checked(c){
}
Cell::~Cell(){
}

int Cell::getValue() const {
        return this->value;
}
bool Cell::ischecked() const {
        return this->checked;
}
void Cell::check() {
        this->checked = true;
}
void Cell::uncheck() {
        this->checked = false;
}
void Cell::reverse_check() {
        this->ischecked() ? this->uncheck() : this->check();
}

void Cell::printcell(std::ostream &os) const
{
        if(this->getValue()<10)
                os<<"0";
        os<<this->getValue()<<"(";
        if(this->ischecked())
                os<<"V)";
        else
                os<<"X)";
}



std::ostream& operator<<(std::ostream &os, Cell const& C)
{
        C.printcell(os);
        return os;

}

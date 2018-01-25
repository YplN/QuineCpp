#include "Cell.h"
#include "Line.h"

std::ostream& operator<<(std::ostream &os, Cell const& C)
{
        C.printcell(os);
        return os;
}

std::ostream& operator<<(std::ostream &os, Line const& L)
{
        L.printLine(os);
        return os;
}

Line operator+(Line & L, Cell const& C)
{
        std::vector<int> v = L.getValues();

        std::cout<<v<<std::endl;
        if(L.containsValue(C.getValue())==-1)
        {
                bool after = true;
                v.push_back(C.getValue());
                std::cout<<v<<std::endl;
                Line L1 = Line(v);
                for (size_t i = 0; i < L1.getSize(); i++) {
                        if(L1.getCell(i)->getValue()==C.getValue())
                        {
                                after = false;
                                if(C.ischecked())
                                        L1.getCell(i)->check();
                        }
                        else
                        {
                                if(after)
                                {
                                        if(L.getCell(i)->ischecked())
                                                L1.getCell(i)->check();
                                }
                                else
                                {
                                        if(L.getCell(i-1)->ischecked())
                                                L1.getCell(i)->check();
                                }
                        }
                        std::cout<<*L1.getCell(i)<<std::endl;

                }
                return L1;
        }

        if(C.ischecked())
        {
                size_t index = L.getIndex(C.getValue());
                if(C.ischecked())
                        L.getCell(index)->check();

        }
        return L;
}



int main()
{
        Cell C(3);
        std::vector<int> v;
        v.push_back(23);
        v.push_back(42);
        v.push_back(14);
        v.push_back(9);
        v.push_back(4);
        v.push_back(84);

        Line L(v);
        std::cout<<L<<std::endl;

        v.insert(v.begin()+4, 5);

        Line L2(v);

        std::cout<<L2<<std::endl;
        std::cout<<L2+C<<std::endl;

        return 0;
}

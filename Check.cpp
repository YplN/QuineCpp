#include "Cell.h"
#include "Line.h"
#include "Card.h"
#include "Game.h"

#include <fstream>
#include <sstream>
#include <string>


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

std::ostream& operator<<(std::ostream &os, Card const& C)
{
        C.printCard(os);
        return os;
}

std::ostream& operator<<(std::ostream &os, Game const& G)
{
        G.printGame(os);
        return os;
}




Line operator+(Line &L, Cell const& C)
{
        std::vector<int> v = L.getValues();

        // std::cout<<v<<std::endl;
        if(L.containsValue(C.getValue())==-1)
        {
                bool after = true;
                v.push_back(C.getValue());
                // std::cout<<v<<std::endl;
                Line L1 = Line(v);
                std::cout<<L1<<std::endl;

                // for (size_t i = 0; i < L1.getSize(); i++) {
                //         if(L1.getCell(i)->getValue()==C.getValue())
                //         {
                //                 after = false;
                //                 if(C.ischecked())
                //                         L1.getCell(i)->check();
                //         }
                //         else
                //         {
                //                 if(after)
                //                 {
                //                         if(L.getCell(i)->ischecked())
                //                                 L1.getCell(i)->check();
                //                 }
                //                 else
                //                 {
                //                         if(L.getCell(i-1)->ischecked())
                //                                 L1.getCell(i)->check();
                //                 }
                //         }
                //         std::cout<<*L1.getCell(i)<<std::endl;
                //
                // }
                //
                // std::cout<<"Hey ! "<<std::endl;
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

std::vector<std::vector<std::vector<int> > > Parser(std::string filename)
{
        std::ifstream in(filename, std::ifstream::in);
        size_t nb_cards, nb_lines, id_card;
        std::string val, line;
        std::vector<std::vector<std::vector<int> > > game;
        std::vector<std::vector<int> > card;
        std::vector<int> one_line;

//The first item is the number of cards in total
        in>>nb_cards;
        in.ignore(1,'\n');
        // std::cout<<"CARDS : "<<nb_cards<<std::endl;

        for (size_t ca = 0; ca < nb_cards; ca++) {
                std::getline(in, line);
                std::istringstream iss (line);

                iss>>nb_lines;
                // std::cout<<nb_lines<<std::endl;
                iss>>id_card;
                // std::cout<<"ID:"<<id_card<<std::endl;

                card.push_back(std::vector<int>(1, id_card));
                for (size_t li = 0; li < nb_lines; li++) {

                        std::getline(in, line);
                        std::istringstream iss(line);

                        // size_t i = 0;
                        while (std::getline(iss,val,' ')) {
                                one_line.push_back(stoi(val));
                                // std::cout<<i<<"("<<val<<")";
                                // i++;
                        }
                        // std::cout<<std::endl;

                        card.push_back(one_line);
                        one_line.clear();
                }

                in.ignore(1,'\n');
                game.push_back(card);
                card.clear();
        }
        return game;
}

int main()
{
        // std::vector<std::vector<std::vector<int> > > g = Parser("input2.txt");
        // Game G(g, true);
        // std::cout<<G<<std::endl;


        //
        // for (size_t i = 0; i < G.containsValue(99).size(); i++) {
        //         std::cout<<G.containsValue(99).at(i)<<std::endl;
        // }

        Cell C(3);
        std::vector<int> v;
        v.push_back(2);
        v.push_back(7);

        Line L(v);

        Line L2 = L;
        std::cout<<L<<std::endl;
        std::cout<<L2<<std::endl<<std::endl;

        std::cout<<L.getCell(0)<<std::endl;
        std::cout<<L2.getCell(0)<<std::endl<<std::endl;

        L2.checkvalue(2);
        std::cout<<L<<std::endl;
        std::cout<<L2<<std::endl<<std::endl;

        return 0;
}

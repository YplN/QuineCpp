#include "Cell.h"
#include "Line.h"
#include "Card.h"
#include "Game.h"

#include <fstream>
#include <sstream>
#include <string>


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
                // std::cout<<L1<<std::endl;

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
                        // std::cout<<*L1.getCell(i)<<std::endl;

                }

                // std::cout<<"Hey ! "<<std::endl;
                return L1;
        }


        Line L1 = L;
        if(C.ischecked())
        {
                size_t index = L.getIndex(C.getValue());
                if(C.ischecked())
                        L1.getCell(index)->check();

        }
        return L1;
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


void StartAGame(std::string filename)
{
        //We first load our cards from filename
        std::vector<std::vector<std::vector<int> > > g = Parser(filename);
        Game G(g, true);

        // the number we have to check
        int value = -1;
        size_t i;
        std::vector<int> saveValues;

        bool conti = true;

        do {
                do {
                        std::cout << "Enter the new number:" << '\n';
                        std::cin>>value;

                        if(value>0)
                        {
                                i = 0;
                                while (i<saveValues.size() && saveValues.at(i)<value)
                                        i++;
                                if((i<saveValues.size() && saveValues.at(i)!=value) || saveValues.empty() || ( i==saveValues.size() && value> saveValues.back()))
                                {
                                        saveValues.insert(saveValues.begin()+i,value);
                                        G.checkvalue(value);
                                        if(G.getMin()==0)
                                        {
                                                for (size_t i = 0; i < G.getAllMin().size(); i++) {
                                                        std::cout<<"WINNING CARD ID N°"<<G.getCard(G.getAllMin().at(i))->getID()<<std::endl;
                                                }
                                        }

                                }

                        }
                        if(value<0)
                        {
                                i = 0;
                                while (i<saveValues.size() && saveValues.at(i)<-value)
                                        i++;
                                if(i<saveValues.size() && saveValues.at(i) == -value)
                                {
                                        saveValues.erase(saveValues.begin()+i);
                                        G.uncheckvalue(-value);

                                }
                                else
                                        std::cout << "Error: the value "<<value<<" is not appeared yet... Ignoring." << '\n';
                        }

                        if(saveValues.size()>0)
                        {
                                std::cout << "NUMBERS APPEARED UNTIL NOW: ";
                                for (size_t i = 0; i < saveValues.size(); i++) {
                                        std::cout<<saveValues.at(i)<<" ";
                                }
                                std::cout<<std::endl;
                        }

                        if(G.getAllMin().size()>5)
                        {
                                std::cout << "SOME OF THE ";
                        }
                        std::cout << "CLOSEST CARD(S): " << '\n';
                        for (size_t i = 0; i < (5<G.getAllMin().size() ? 5 : G.getAllMin().size()); i++) {
                                std::cout<<*G.getCard(G.getAllMin().at(i))<<std::endl;
                        }

                        std::cout << "DEBUG : " <<G.getMin()<< '\n';

                } while(value!=0);

                std::cout << "EXIT GAME ? (y/n)" << '\n';
                char c;
                std::cin>>c;
                conti=(c=='y' || c=='Y');
        } while(conti);
        std::cout << "GOOD BYE !" << '\n';

}


int main()
{
        // std::vector<std::vector<std::vector<int> > > g = Parser("input2.txt");
        // Game G(g, true);
        StartAGame("input2.txt");



        // std::cout<<G<<std::endl;
        //
        // G.checkvalue(3);
        // G.checkvalue(21);
        // G.checkvalue(11);
        // G.checkvalue(23);
        // G.checkvalue(5);
        //
        // std::cout<<G<<std::endl;
        //
        // G.uncheckvalue(99);
        //
        // std::cout<<G<<std::endl;
        //
        //


        // Cell C(3, true);
        // std::vector<int> v;
        // v.push_back(2);
        // v.push_back(7);
        //
        // Line L(v);
        // L.checkvalue(2);
        //
        // Line L2=L+C;
        // std::cout<<L<<std::endl;
        // std::cout<<L2<<std::endl<<std::endl;
        //
        // L2.checkvalue(3);
        // std::cout<<L<<std::endl;
        // std::cout<<L2<<std::endl<<std::endl;

        return 0;
}

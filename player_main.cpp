//Abby Itty
//Program Demo thing

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "player.h"

int longestName(const std::vector<Player>& p)
{
    int unsigned max = 0;
    for(unsigned int i = 0; i < p.size(); i++)
        if((p[i].getFirstName().size() + p[i].getLastName().size()) > max)
            max = p[i].getFirstName().size() + p[i].getLastName().size();

    return max;
}

int main(int argc, char* argv[])
{

    //right # of inputs?
    if(argc != 4)
    {
        std::cerr << "Not four arguments" << std::endl;
        return 1;
    }

    //good fourth argument (custom or standard and not...geronimo or webkinz
    if(std::string(argv[3]) != "standard" && std::string(argv[3]) != "custom")
    {
        std::cerr << "Fourth argument must be either custom or standard!" << std::endl;
        return 1;
    }

    //reading in file works?
    std::ifstream infile(argv[1]);
    if(!infile.good())
    {
        std::cerr << "Can't open " << std::string(argv[1]) << " to read" << std::endl;
        return 1;
    }

    //read in everyone
    std::vector<Player> players;

    std::string fname;
    std::string lname;
    std::vector<int> scores;
    int tmp;
    while (infile >> fname >> lname)
    {
       while(infile >> tmp)
            scores.push_back(tmp);

        players.push_back(Player(fname, lname, scores));
        scores.clear();
        infile.clear();
    }
    infile.close();

    //sort vector by last name, first name -> function
    std::sort(players.begin(), players.end());

    //outfile check
    std::ofstream outfile(argv[2]);
    if(!outfile.good())
    {
        std::cerr << "Can't open " << std::string(argv[2]) << " to write to" << std::endl;
        return 1;
    }

    //table
    int lineLength = longestName(players) + 67;
    outfile << std::string(lineLength, '-') << std::endl; //dashed line
    for(unsigned int i = 0; i < players.size(); i++)
    {
        //name cell
        outfile << "| ";
        std::string name = players[i].getFirstName() + " " + players[i].getLastName();
        outfile << std::setw(lineLength-66) << std::left << name;
        outfile << " | ";

        int frame = 1;
        int indivScores[10];
        for(int j = 0; j < 10; j++) //initializing array of scores for each player
        {
            indivScores[j] = 0;
        }
        //score cells
        while(frame <= 10)
        {
            for(unsigned int j = 0; j < players[i].getScores().size(); j+=2) //going through scores
            {
                if(frame == 10) //final frame
                {
                    unsigned int elementsLeft = players[i].getScores().size() - j;
                    for(unsigned int k = 0; k < elementsLeft; k++)
                    {
                        bool inc = false;
                        if(k != 0 && (players[i].getScores()[j] + players[i].getScores()[j-1]) == 10) //spare (not first throw)
                        {
                            indivScores[frame-1] += players[i].getScores()[j];
                            if(k == elementsLeft - 1)
                            {
                                if(elementsLeft == 2)
                                    outfile << "/   |" << std::endl;
                                else
                                    outfile << "/ |" << std::endl;
                                frame = 11;
                            }
                            else
                            {
                                outfile << "/ ";
                                j++;
                                inc = true;
                            }
                        }

                        if(players[i].getScores()[j] == 10) //strike
                        {
                            if(k == elementsLeft - 1) //last throw
                            {
                                indivScores[frame-1] += 10;
                                if(elementsLeft == 2)
                                    outfile << "X   |" << std::endl;
                                else
                                    outfile << "X |" << std::endl;
                                frame = 11;
                            }
                            else //not last throw (first or second)
                            {
                                if(!inc)
                                {
                                    outfile << "X ";
                                    j++;
                                    inc = true;
                                    if(players[i].getScores().size()-k == j)
                                        indivScores[frame-1] = indivScores[frame-1] + indivScores[frame-2] + 10;
                                    else
                                        indivScores[frame-1] += 10;
                                }
                            }

                        }
                        else //spare or 0-9 (still 10th frame)
                        {
                            if(players[i].getScores()[j] == 0) //zero
                            {
                                players[i].incGutterBalls();
                                if(k == elementsLeft - 1) //last throw
                                {
                                    if(elementsLeft == 2)
                                        outfile << "-   |" << std::endl;
                                    else
                                        outfile << "- |" << std::endl;
                                    frame = 11;
                                }
                                else
                                {
                                    if(!inc)
                                        indivScores[frame-1] = indivScores[frame-2];
                                    outfile << "- ";
                                    j++;
                                    inc = true;
                                }
                            }
                            else //not zero (still in 10th frame)
                            {
                                if(k == elementsLeft - 1) //last throw
                                {
                                    indivScores[frame-1] += players[i].getScores()[j];
                                    if(elementsLeft == 2)
                                        outfile << players[i].getScores()[j] << "   |" << std::endl;
                                    else
                                        outfile << players[i].getScores()[j] << " |" << std::endl;
                                    frame = 11;
                                }
                                else
                                {
                                    if(!inc)
                                        indivScores[frame-1] = indivScores[frame-1] + indivScores[frame-2] + players[i].getScores()[j];
                                    outfile <<  players[i].getScores()[j] << " ";
                                    j++;
                                    inc = true;
                                }
                            }
                        }
                    }
                }
                else //not final frame (first nine frames)
                {
                    if(players[i].getScores()[j] == 10) //strike
                    {
                        outfile << "  X | ";
                        if(frame == 1)
                            indivScores[frame-1] = 10 + players[i].getScores()[j+1] + players[i].getScores()[j+2];
                        else
                            indivScores[frame-1] = indivScores[frame-2] + 10 + players[i].getScores()[j+1] + players[i].getScores()[j+2];
                        j--;
                        frame++;
                    }
                    else
                    {
                        //first throw
                        if(players[i].getScores()[j] == 0) //zero
                        {
                            players[i].incGutterBalls();
                            outfile << '-' << " ";
                            if(frame != 1)
                                indivScores[frame-1] = indivScores[frame -2];
                        }

                        else //1-9
                        {
                            outfile << players[i].getScores()[j] << " ";
                            if(frame == 1)
                                indivScores[frame-1] += players[i].getScores()[j];
                            else
                                indivScores[frame-1] += indivScores[frame-2] + players[i].getScores()[j];
                        }

                        //second throw
                        if(players[i].getScores()[j] + players[i].getScores()[j+1] == 10) //spare
                        {
                            outfile << "/ | ";
                            indivScores[frame-1] += players[i].getScores()[j+1] + players[i].getScores()[j+2];
                        }
                        else
                        {
                            if(players[i].getScores()[j+1] == 0) //zero
                            {
                                players[i].incGutterBalls();
                                outfile << "- | ";
                            }
                            else //1-9
                            {
                                outfile << players[i].getScores()[j+1] << " | ";
                                indivScores[frame-1] += players[i].getScores()[j+1];
                            }
                        }
                        frame++;
                    }
                }
            }
            outfile << "|" << std::string(lineLength-64, ' ') << "|";
            for(int j = 0; j < 9; j++)
                outfile << std::setw(4) << std::right << indivScores[j] << " |";
            outfile << std::setw(6) << std::right << indivScores[9] << " |" << std::endl;
            outfile << std::string(lineLength, '-') << std::endl;

            players[i].setFinalScore(indivScores[9]);
        }
        frame = 0;

    }

    //output names
    std::sort(players.begin(), players.end(), finalSort);
    outfile << std::endl;
    if(std::string(argv[3]) == "standard")
    {
        for(int i = 0; i < players.size(); i++)
            outfile << std::setw(longestName(players) + 1) << std::left << players[i].getFirstName() + " " +  players[i].getLastName()
                         << std::setw(5) << std::right << players[i].getFinalScore() << std::endl;
    }
    else
    {
        outfile << std::setw(longestName(players) + 1) << std::left << "Name" << std::setw(18) << std::right << "Gutter Balls" << std::endl;
        for(int i = 0; i < players.size(); i++)
            outfile << std::setw(longestName(players) + 1) << std::left << players[i].getFirstName() + " " +  players[i].getLastName()
                    << std::setw(18) << std::right << players[i].getGutterBalls() << std::endl;
    }
    outfile.close();

    return 0;
}
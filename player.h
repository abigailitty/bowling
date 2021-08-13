//Abby Itty
//Player header file

#ifndef HW2_PLAYER_H
#define HW2_PLAYER_H

#include <vector>

class Player
{
    private:
        std::vector<int> scores;
        std::string firstName;
        std::string lastName;
        int finalScore;
        int gutterBalls;

    public:
        Player(std::string& fn, std::string& ln, std::vector<int>& scores);

        //getters
        std::string getFirstName() const; //const std::string& getName() const; ?
        std::string getLastName() const;
        std::vector<int> getScores() const; //const std::vector<int>& getScores() const;?
        int getFinalScore() const;
        int getGutterBalls() const;

        //setters
        void setFirstName(const std::string& fn);
        void setLastName(const std::string& ln);
        void setScores(const std::vector<int>& s);
        void setFinalScore(int x);
        void incGutterBalls();
};

    bool operator< (const Player& first, const Player& second);
    bool finalSort (const Player& first, const Player& second);

#endif //HW2_PLAYER_H
#include "controller.h"
#include "chess.h"
#include "player.h"
#include "human.h"
#include "viewer.h"
#include "textviewer.h"
#include "graphicviewer.h"
#include "easy.h"
#include "medium.h"
#include "hard.h"
#include "ultra.h"

#include <string>
#include <iostream>

// Contructor/Destructor
Controller::Controller() {}

Controller::~Controller() {}

bool Controller::getMove(std::string colour){
    for (auto p: active_players){
        if (p->getColour() == colour){
            return p->move();
        }
    }
    std::cout << "Colour does not match player" << std::endl;
    return false;
}

void Controller::__init__(){
    chess = std::make_shared<Chess>();
    viewers.emplace_back(std::make_shared<TextViewer>(8, 8, chess));
    viewers.emplace_back(std::make_shared<GraphicViewer>(chess));
    viewers.at(1)->display();
}

// Initiates new chess game
void Controller::NewGame(){
    chess = std::make_shared<Chess>();
    for (auto v: viewers){
        v->updateChess(chess);
        chess->addViewers(v);
    }
    for (auto p: players){
        p->updateGame(chess);
    }
}

// Adds player to controller
void Controller::addPlayer(){
    std::string type, name;
    std::cin >> type >> name;
    for (auto p: players){
        if (p->getName() == name){
            std::cout << "Player Already Exists!" << std::endl;
            return;
        }
    }
    if (type == "human"){
        players.emplace_back(std::make_shared<Human>(chess, "none", name));
    }
    else if (type == "computer1"){
        players.emplace_back(std::make_shared<Easy>(chess, "none", name));
    }
    else if (type == "computer2"){
        players.emplace_back(std::make_shared<Medium>(chess, "none", name));
    }
    else if (type == "computer3"){
        players.emplace_back(std::make_shared<Hard>(chess, "none", name));
    }
    else if (type == "computer4"){
        players.emplace_back(std::make_shared<Ultra>(chess, "none", name));
    }
    else{
        std::cout << "Invalid player type" << std::endl;
    }
}

// gets Command
bool Controller::getCommand(){
    std::string command;
    std::cout << "Enter Command: " << std::endl;
    std::cin >> command;
    if (command == "exit") return false;
    else if ((command == "add") && !playing){
        addPlayer();
    }
    else if ((command == "game") && !playing){
        if (setup){
            if (configurePlayers()){
                playing = true;
                viewers.at(1)->displayMessage("Game Start!");
                chess->updateViewers();
            }
        }
        else {
            NewGame();
            chess->defaultSetup();
            if (configurePlayers()){
                playing = true;
                viewers.at(1)->displayMessage("Game Start!");
                chess->updateViewers();
            }
        }   
    }
    else if ((command == "score")){
        scoreboard();
    }
    else if ((command == "move") && playing){
        if(getMove(chess->getTurn())){
            chess->updateViewers();
        }
        else{
            std::cout << "Invalid Move" << std::endl;
        }
    }
    else if ((command == "printmoves") && playing) {
        std::string s;
        std::cin >> s;
        int x = s[0] - 97;
        int y = s[1] - 49;
        chess->getPrint(s, x, y);
    }
    else if ((command == "setup") && !playing){
        NewGame();
        chess->userSetup();
        setup = true;
    }
    else if (command == "resign" && playing){
        for (auto p: active_players){
            if (p->getColour() != chess->getTurn()){
                std::cout << p->getColour() << " Wins!" << std::endl;
                p->addWin();
            }
        }
        setup = false;
        playing = false;
        NewGame();
    }
    else if ((command == "undo") && playing){
        chess->undoMove();
        chess->updateViewers();
    }
    else std::cout << "Invalid Command" << std::endl;
    return true;
}
 
void Controller::play(){
    while (getCommand()){
        if (playing){
            if (chess->checkmate()){
                std::cout << "CheckMate! ";
                for (auto p: active_players){
                    if (p->getColour() != chess->getTurn()){
                        std::cout << p->getColour() << " Wins!" << std::endl;
                        p->addWin();
                    }
                }
                playing = false;
                setup = false;
            }
            else if (chess->stalemate()){
                std::cout << "StaleMate!" << std::endl;
                for (auto p: active_players){
                    p->addDraw();
                }
                setup = false;
                playing = false;
            }
        }
    }
    End();
}

// Configures players, returns true if successful, false otherwise
// This should be changed for final product
bool Controller::configurePlayers(){
    std::string player_1, player_2;
    std::cin >> player_1;
    std::cin >> player_2;
    active_players.clear();
    for (auto p: players){
        if (p->getName() == player_1){
            p->changeColour("white");
            active_players.emplace_back(p);
        }
        else if (p->getName() == player_2){
            p->changeColour("black");
            active_players.emplace_back(p);
        }
    }
    if (active_players.size() < 2){
        std::cout << "Player(s) not found" << std::endl;
        return false;
    }
    else return true;
}

// Runs when Program ends
void Controller::End(){
    scoreboard();
    chess->removeAllViewers();
    std::cout << "Thanks For Playing!" << std::endl;
}

// Print Scoreboard
void Controller::scoreboard(){
    std::cout << "Score" << std::endl;
    for (auto p: players){
        std::cout << p->getName() << ": " << p->getScore() << std::endl;
    }
}



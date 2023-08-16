#include <vector>
#include <string>
#include <memory>
#include "viewer.h"

class Chess;
class Player;

class Controller{
    // List of all players
    std::vector<std::shared_ptr<Player>> players;
    // Chess
    std::shared_ptr<Chess> chess;
    // List of Active players
    std::vector<std::shared_ptr<Player>> active_players;
    // List of Viewers
    std::vector<std::shared_ptr<Viewer>> viewers;

    // True if game is active
    bool playing = false;
    // True if game is setup
    bool setup = false;

    // Adds New Player
    void addPlayer();
    // Initiates New Chess Game
    void NewGame();
    // Tries to make a move
    bool getMove(std::string colour);
    // Gets command from user
    bool getCommand();
    // Configures Players
    bool configurePlayers();
    // Ends Game
    void End();
    // Prints scoreboard
    void scoreboard();
public:
    // Contructor/Destructor
    Controller();
    ~Controller();
    void play();
    void __init__();
           
};

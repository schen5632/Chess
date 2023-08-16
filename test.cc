#include "viewer.h"
#include "textviewer.h"
#include "chess.h"
#include "graphicviewer.h"
#include "controller.h"
#include "player.h"
#include "human.h"
#include <iostream>

using namespace std;

int main(){
    Controller c;
    c.__init__();
    c.play();
}

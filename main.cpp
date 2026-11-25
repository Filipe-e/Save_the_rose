#include "./screens/screensWeapons.hpp"
#include "./player/classes_player.hpp"
#include "./player/itens.hpp"

int main(){
    vector<Player*> players; 

    Archer archer("legolas", 100, 10, 5, 2, 100, new Bow("Bow", 15, 5, 10, 2, 50, 20), new Crossbow("Crossbow", 20, 10, 15, 3, 60, 15), new Armor("Leather Armor", 20, 5));
    players.push_back(&archer);
}
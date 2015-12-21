#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct equip {
    int cost;
    int damage;
    int armor;
};

static const int boss_HP = 104;
static const int boss_damage = 8;
static const int boss_armor = 1;

int main() {
    std::vector<equip> weapons{ 
         {8, 4, 0}, // dagger
        {10, 5, 0}, // shortsword
        {25, 6, 0}, // warhammer
        {40, 7, 0}, // longsword
        {74, 8, 0}, // greataxe
    };
    std::vector<equip> armors{
        { 0, 0, 0}, // no armor
        {13, 0, 1}, // leather
        {31, 0, 2}, // chainmail
        {53, 0, 3}, // splintmail
        {75, 0, 4}, // bandedmail
       {102, 0, 5}, // platemail
    };
    std::vector<equip> rings{
        {0, 0, 0}, // no ring one
        {0, 0, 0}, // no ring two
       {25, 1, 0}, // dam + 1
       {50, 2, 0}, // dam + 2
      {100, 3, 0}, // dam + 3
       {20, 0, 1}, // def + 1
       {40, 0, 2}, // def + 2
       {80, 0, 3}, // def + 3
    };

    int min_cost = std::numeric_limits<int>::max();
    int max_cost = std::numeric_limits<int>::min();
    for (auto& w : weapons) {
        for (auto& a : armors) {
            for (int i = 0; i < rings.size(); ++i) {
                for (int j = 0; j < rings.size(); ++j) {
                    if (i == j) continue;
                    int dmg = w.damage + rings[i].damage + rings[j].damage;
                    int def = a.armor + rings[i].armor + rings[j].armor;
                    int HP = 100;
                    // how long does boss need to kill us
                    int boss_adjusted_damage = std::max(1, boss_damage - def);
                    int boss_turns = (HP + boss_adjusted_damage - 1) / boss_adjusted_damage;
                    // how long does it take us to kill him
                    int adjusted_damage = std::max(1, dmg - boss_armor);
                    int turns = (boss_HP + adjusted_damage - 1) / adjusted_damage;
                    if (turns <= boss_turns) {
                        // we will in fact win
                        min_cost = std::min(min_cost, w.cost + a.cost + rings[i].cost + rings[j].cost);
                    }
                    if (turns > boss_turns) {
                        max_cost = std::max(max_cost, w.cost + a.cost + rings[i].cost + rings[j].cost);
                    }
                }
            }
        }
    }
    std::cout << "Easy: " << min_cost << std::endl;
    std::cout << "Hard: " << max_cost << std::endl;
}

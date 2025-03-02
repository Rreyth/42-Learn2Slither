#include <Agent/Agent.hpp>


// AGENT
// # Q = {}
// # init q table +- -> dict {state : [up, down, left, right]}
// # Q[state][action]
//
// # closer to bonus + 1
// # take bonus + 30
// # take malus -30
// # dead -100
//
// # chose move + update q table (or create entry for the first encounter)
//
// # chose move without learn
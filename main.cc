#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "deck.h"
#include "game.h"

using namespace std;

int main( int argc, char * argv[] )
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if
	std::default_random_engine rng{seed};
	
	char player_types[4];
	for (int i = 1; i <= 4; ++i) {
	    cout << "Is Player" << i << " a human (h) or a computer (c)?" << endl;
	    cin >> player_types[i - 1];
	}
	int num_of_players = 4;
	game* straights = new game{rng, player_types, num_of_players};
	straights->playGame();
	delete straights;
}

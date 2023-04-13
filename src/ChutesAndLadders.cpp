#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;


const int BOARD_SIZE = 40;

const int MAX_PLAYERS = 4;

const char STATIC_BOARD[BOARD_SIZE] = { '_', '_', '_', '#', '1', '_', '2', '_',
	                                    '_', '_', '_', '1', '$', '_', '_', '_',
	                                    '_', '#', '_', '3', '_', '_', '_', '_',
	                                    '_', '_', '%', '2', '_', '_', '$', '_',
	                                    '_', '_', '_', '%', '3', '_', '_', '_'
                                      };

const int CHUTES_MAP[2][3] = {   3, 12, 26,
	                            17, 30, 35   };


const int LADDERS_MAP[2][3] = {  11, 27, 36,
	                              4, 6, 19   };


void activate_chute( );
void activate_ladder( );
char get_mode( );
void has_chute_or_ladder( int, int &, char & );
bool has_player( int, int, const int [] );
void move( bool &, char, int, int [] );
void print_board( int [] );
char print_menu( int );
int roll_dice( char );
void run_game( char , int, int [] );
char square_symbol( int, const int [] );


int main( )
{
	int i = 0;
	char mode = 'Z';
	int num_players = 0;

	// A player's symbol is represented by the array index, a player's position
	// is the value at that index.
	int player_list[MAX_PLAYERS];

	// Initializing players
	for (i = 0; i < MAX_PLAYERS; ++i)
	{
		player_list[i] = -1;
	}

	// Welcome Menu
	cout << setfill( '-' ) << setw( 23 ) << "Chutes and ladders";
	cout << setfill( '-' ) << setw( 6 ) << "\n";
	cout << "1, 2, 3 go up, and #, $, and ^ go down\n";

	// Getting the number of players
	cout << "\nPlease, enter how many players: ";
	cin >> num_players;

	// Verifying 2 - 4 players
	while ( num_players < 2 || num_players > MAX_PLAYERS )
	{
		cout << "Please enter 2 to " << MAX_PLAYERS << " players: ";
		cin >> num_players;
	}

	mode = get_mode( );

	run_game( mode, num_players, player_list );


	return 0;
}


void activate_chute( )
{
	int rand_phrase = 0;

	rand_phrase = rand( ) % 3;

	if ( rand_phrase == 0 )
	{
		cout << "Chute: Going Down!\n";
	}
	else if ( rand_phrase == 1 )
	{
		cout << "Chute: Fasten your seatbelt!\n";
	}
	else
	{
		cout << "Chute: The Eagle has landed.\n";
	}


	return;
}


void activate_ladder( )
{
	int rand_phrase = 0;

	rand_phrase = rand( ) % 3;

	if ( rand_phrase == 0 )
	{
		cout << "Ladder: Going Up!\n";
	}
	else if ( rand_phrase == 1 )
	{
		cout << "Ladder: Up, Up and Away!\n";
	}
	else
	{
		cout << "Ladder: Houston, we have lift off.\n";
	}
	

	return;
}


char get_mode( )
{
	char mode = 'Z';

	cout << "\nChoose which mode to play in" <<
		"\n(D)ebug mode\n(P)ower mode" <<
		"\nAnything else will be regular mode" <<
		"\nEnter Mode: ";

	cin >> mode;
	mode = toupper( mode );

	if ( mode != 'D' && mode != 'P' )
	{
		mode = 'R';
		srand( int( time( NULL ) ) );
	}
	else
	{
		srand( 10 );
	}


	return mode;
}


void has_chute_or_ladder( int check_val, int & move_to, char & landed_on )
{	
	int i = 0;

	for ( i = 0; i < 3; ++i )
	{
		// Checking for start of chute
		if ( check_val == CHUTES_MAP[0][i] )
		{
			move_to = CHUTES_MAP[1][i];
			landed_on = 'C';
			

			return;
		}
		
		// Checking for start of ladder
		else if ( check_val == LADDERS_MAP[0][i] )
		{
			move_to = LADDERS_MAP[1][i];
			landed_on = 'L';
			

			return;
		}
	}
	
	// Normal square
	move_to = check_val;
	landed_on = 'N';
	

	return;
}


bool has_player( int move_to, int current_player, const int player_list[] )
{
	int i = 0;
	char hit_player = 'Z';

	for ( i = 0; i < MAX_PLAYERS; ++i )
	{
		// Checking for player - Players can't hit themselves
		if ( move_to == player_list[i] && current_player != i )
		{
				hit_player = 97 + i; // ASCII value
				cout << "Hit player " << hit_player << endl;
				
				
				return true;
		}
	}
	
	
	return false;
}


void move( bool & game_over, char mode, int current_player, int player_list[] )
{
	int check_val = 0;
	int move_to = 0;
	char landed_on = 'Z';
	bool hit_player = false;
	char winner = 'Z';
	
	// Determining which square needs to be checked
	check_val = roll_dice( mode ) + player_list[current_player];
	// Checking for a chute or ladder
	has_chute_or_ladder( check_val, move_to, landed_on );

	// Prints messages indicating if the player landed on a chute or ladder
	if ( landed_on == 'C' )
	{
		activate_chute( );
	}
	else if ( landed_on == 'L' )
	{
		activate_ladder( );
	}

	// Checking for another player occupying the square
	hit_player = has_player( move_to, current_player, player_list );

	if ( hit_player == false )
	{
		// Checking that player didn't roll past the last square
		if ( move_to > BOARD_SIZE - 1 )
		{
			cout <<
				"Rolled past the end of the board. You need an exact roll.\n";
		}
	    // Checking for a winner
		else if ( move_to == BOARD_SIZE - 1 )
		{
			winner = 97 + current_player;
			cout << "Player " << winner << " won.\n";
			game_over = true;
		}
		// Updating current player's location
		else if ( move_to < BOARD_SIZE - 1 )
		{
			( player_list[current_player] = move_to );
		}
	}
	return;
}


void print_board( int player_list[] )
{
	bool end_row = false;
	int i = 0;
	char symbol = 'Z';

	// Print Game Board
	for ( i = 0; i < BOARD_SIZE; ++i )
	{
		// Getting the board symbol
		symbol = square_symbol( i, player_list );

		// Checking for end of a row
		if ( ( i + 1 ) % 8 == 0 )
		{
			end_row = true;
		}
		else
		{
			end_row = false;
		}

		// Printing the formatted table
		if ( end_row )
		{
			cout << "| " << symbol << " |\n";
		}

		else if ( i == BOARD_SIZE - 1 )
		{
			cout << "| " << symbol << " |";
		}

		else
		{
			cout << "| " << symbol << " ";
		}
	}


	return;
}


char print_menu( int current_player )
{
	char choice = 'Z';
	char player_symbol = 'Z';

	player_symbol = current_player + 97; // ASCII value

	// Menu
	cout << endl;
	cout << setfill( '-' ) << setw( 22 ) << "Current player is "
		 << player_symbol;
	cout << setfill( '-' ) << setw( 5 ) << "\n";

	cout << "(R)oll\n(Q)uit\n";

	cin >> choice;
	choice = toupper( choice );

	// Checking for valid input
	while ( choice != 'R' && choice != 'Q' )
	{
		cout << "Invalid option" <<
			"\n(R)oll\n(Q)uit \n";

		cin >> choice;
		choice = toupper( choice );
	}


	return choice;
}


int roll_dice( char mode )
{
	int roll_val = 0;

	// Debug or Regular Mode
	if ( mode != 'P' )
	{
		roll_val = rand( ) % 6 + 1;
		cout << "Rolled a " << roll_val;
		cout << endl;
	}

	// Power Mode
	else
	{
		cout << "Roll: ";
		cin >> roll_val;
	}


	return roll_val;
}


void run_game( char mode, int num_players, int player_list[] )
{
	bool game_over = false;
	int current_player = 0;
	int i = 0;
	char roll_or_quit = 'Z';

	while ( game_over == false )
	{
		for ( i = 0; i < num_players; ++i )
		{
			current_player = i;

			print_board( player_list );

			roll_or_quit = print_menu( current_player );

			if ( roll_or_quit == 'Q' )
			{
				game_over = true;


				return;
			}
			else
			{
				move( game_over, mode, current_player, player_list );

				if ( game_over == true )
				{
					
					return;

				}
			}
		}
	}


	return;
}


char square_symbol( int check_square, const int player_list[] )
{
	char symbol = ' ';
	int i = 0;

	// Checks each players location
	for ( i = 0; i < MAX_PLAYERS; ++i )
	{
		if ( player_list[i] == check_square )
		{
			symbol = 97 + i; // ASCII value
			
			
			return symbol;
		}
	}

	// Checks for game-board symbol
	if ( STATIC_BOARD[check_square] != '_' )
	{
		symbol = STATIC_BOARD[check_square];
		
		
		return symbol;
	}


	return symbol;
}

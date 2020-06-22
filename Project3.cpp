
#include <iostream>
#include "Game.h"

int main() {
	// Automagically read and parse data into game object via constructor:
	Game game;

	// Present menu options:
	cout << "==== Welcome to PRAHJEKT-TREE: The Text-Based Adventure Game! ====" << endl;
	cout << "====       Written by Terence Creighton & Cameron Hazlip      ====" << endl;
	cout << endl;
	cout << "1) New Game" << endl;
	cout << "2) Continue Game" << endl;
	cout << "3) Leaderboard" << endl;
	cout << "4) Save All" << endl;
	cout << "5) Delete All Saves" << endl;
	cout << "6) Quit" << endl;
	cout << endl;
	cout << "Choice: ";

	int choice = 0;

	cin >> choice;

	// Verify the input is valid:
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024 * 10, '\n');

		cout << "Invalid option!\n" << endl;
		main();
		return -1;
	}
	else {
		// Handle user choice:
		switch (choice) {
		case 1: {
			cout << "Welcome to PRAHJEKT-TREE! Please enter a username: ";
			string username;

			cin >> username;

			if (game.addUser(username)) {
				cout << "Welcome " << Utilities::toLower(username) << " lets begin!" << endl;

				game.advanceStage(username);
				main();
			}
			else {
				cout << "'" << Utilities::toLower(username) << "' already exists!" << endl << endl;
				main();
			}

			break;
		}
		case 2: {
			cout << "Welcome to PRAHJEKT-TREE! Please enter your username: ";
			string username;

			cin >> username;

			if (game.doesUserExist(username)) {
				game.advanceStage(username);

				main();
			}
			else {
				cout << "'" << Utilities::toLower(username) << "'" << " does not exist!" << endl;
				main();
			}

			break;
		}
		case 3: {
			auto users = game.getSortedUsers();

			if (users.size() == 0) {
				printf("There are no highscores saved yet!\n\n");
			}
			else {
				int count = 0;

				// Show top n users:
				printf("How many users would you like to see? ");
				cin >> count;
				cout << endl;

				// Verify the input is valid:
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024 * 10, '\n');

					count = users.size();
				}

				// Prevent out of bound exceptions:
				count = count > users.size() ? users.size() : count;

				printf("Top %i Leaderboard:\n", count);

				for (int i = 0; i < count; i++) {
					auto leaderboardData = users[i].getLeaderboardData();
					printf("[%i] %s - %i\n", i + 1, leaderboardData.username.data(), leaderboardData.highScore);
				}

				printf("\n");
			}

			main();
			break;
		}
		case 4: {
			printf("Saving all game data...\n");

			game.saveUserData();

			printf("Game data has been saved!\n\n");

			main();
			break;
		}
		case 5: {
			printf("Are you sure you want to delete every save? (Y/N) ");

			string response;

			cin >> response;

			if (Utilities::toLower(response) == "y") {
				game.deleteAllUsers();

				printf("All saves have been successfully deleted!\n\n");
			}

			main();
			break;
		}
		case 6:
			cout << "Thanks for playing!" << endl;
			return -1;
		default: {
			// Return to main by default:
			printf("Invalid choice!\n");
			cout << endl;
			main();
		}

		}
	}

	return -1;
}

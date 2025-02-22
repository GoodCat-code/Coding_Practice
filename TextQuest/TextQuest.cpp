#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

float Dice_Roll = -1.0;
void (*Current_Position)();

struct M_Char{
	void (*current_position)();
	bool bHas_Backpuck = false;
	bool bGG_Find_Door_Dark_Corridor = false;

	M_Char() {
		current_position = Current_Position;
	}
};

struct Scene
{
	void (*action)();
};

void FirstRoom();
void Hallway();
void Trap();
void StorageRoom();
void DarkCorridor();

M_Char GG;
Scene First_Room = {FirstRoom};	// review
Scene Hall_Room = {Hallway};		// review
Scene Trap_Room;						// review
//______________________________________________________________________________________________________________
void Choice(map<string, void(*)()> arr, void (*foo)()) {

	int choice, arr_size = arr.size();
	vector<void(*)()> arr_foo{};

	for (auto& pair : arr) {
		cout << pair.first << endl;
		arr_foo.push_back(pair.second);
	}

	cin >> choice;
	cout << endl;
	if (choice == 1)
		arr_foo[0]();
	else if (arr_size >= choice) {
		if (choice == 2)
			arr_foo[1]();
		else if (choice == 3)
			arr_foo[2]();
	}
	else {
		Choice(arr, foo);
	}

}; 

//______________________________________________________________________________________________________________
int Death() {
	int choice;

	cout << "You died" << "\n" << "Try again?" << endl;
	cout << "1. Yes" << "\n" << "2. No" << endl;

	cin >> choice;
	cout << endl;
	if (choice == 1)
		FirstRoom();
	else if (choice == 2)
		return 0;
};

//______________________________________________________________________________________________________________
void Trap() {
	cout << "There is a trap" << endl;
	Death();
};

//______________________________________________________________________________________________________________
void Safety_Search_In() {
	Dice_Roll = -1.0;
	srand(time(nullptr));
	Dice_Roll = rand() % 11 / 10.0;
	//Dice_Roll = 0; // play test
	cout << Dice_Roll << endl;
	GG.current_position();
};

//______________________________________________________________________________________________________________
// review
void Not_Safety_Search_In() { 
	srand(time(nullptr));
	float roll = rand() % 11 / 10.0;
	if (roll > 0.4)
		cout << roll << "\t" << "Luck!" << endl;
	else cout << roll << "\t" << "Unluck!" << endl;
};

//______________________________________________________________________________________________________________
void FirstRoom() {
	cout << "You're in the dark room. There are two doors." << endl;

	map<string, void(*)()> choice_arr = { {"1. Enter the left door", Hallway}, {"2. Enter the right door", DarkCorridor} };
	Choice(choice_arr, FirstRoom);
};

//______________________________________________________________________________________________________________
void Hallway() {
	cout << "You're in the hall. There is one door ahead" << endl;

	map<string, void(*)()> choice_arr = { {"1. Enter the door", StorageRoom}, {"2. Return", FirstRoom} };
	Choice(choice_arr, Hallway);
};

//______________________________________________________________________________________________________________
void StorageRoom() {
	if (Dice_Roll > 0.4) {
		GG.bHas_Backpuck = true;
		Dice_Roll = -1.0;
		cout << "Luck! You find backpack" << endl;
	}
	else if (Dice_Roll >= 0.0)
		cout << "Unluck! But you may try again" << endl;


	if (GG.bHas_Backpuck) {
		cout << "You're in the Storage Room. There is no more intresting" << endl;
		map<string, void(*)()> choice_arr = { {"1. Return", Hallway} };
		Choice(choice_arr, StorageRoom);
	}

	cout << "You're in the Storage Room" << endl;
	GG.current_position = StorageRoom;
	map<string, void(*)()> choice_arr = { {"1. Search the room", Safety_Search_In}, {"2. Return", Hallway} };
	Choice(choice_arr, StorageRoom);
};

//______________________________________________________________________________________________________________
void DarkCorridor() {
	if (Dice_Roll > 0.4) {
		GG.bGG_Find_Door_Dark_Corridor = true;
		Dice_Roll = -1.0;
		cout << "Luck! You find the door" << endl;
		map<string, void(*)()> choice_arr = { {"1. Open the door", StorageRoom}, {"2. Return", FirstRoom} };
		Choice(choice_arr, DarkCorridor);
	}
	else if (Dice_Roll > 0.1)
		cout << "Unluck! But you may try again" << endl;
	else if (Dice_Roll >= 0.0) Trap();

	if (GG.bGG_Find_Door_Dark_Corridor) {
		cout << "You're in the Dark Corridor" << endl;
		map<string, void(*)()> choice_arr = { {"1. Open the door", StorageRoom}, {"2. Return", FirstRoom} };
		Choice(choice_arr, DarkCorridor);
	}

	cout << "You're in the Dark Corridor" << endl;
	GG.current_position = DarkCorridor;
	map<string, void(*)()> choice_arr = { {"1. Search the room", Safety_Search_In}, {"2. Return", FirstRoom} };
	Choice(choice_arr, DarkCorridor);
};


int main()
{
	cout << "You wake up and ";
	FirstRoom();
}

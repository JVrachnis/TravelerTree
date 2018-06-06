#include <iostream>
using namespace std;
#include <string>
#include <string.h>
#include <assert.h>
#include <algorithm>
#include "Tree.h"
#include "TreeFlight.h"

Tree tree;
TreeFlight rootFlight;
void InsertFlightRoot(string id, double departureTime, double arrivalTime) {//βαζει την πτιση-ριζα στο δεντρο με τα στιχια που δινοντε
	rootFlight.id = id;
	rootFlight.departureTime = departureTime;
	rootFlight.arrivalTime = arrivalTime;
	rootFlight.maxTime = arrivalTime;
	tree.insert(rootFlight);
}

void InsertFlight(string id, double departureTime, double arrivalTime) {//βαζει την πτιση με τα στιχια που δινοντε στο δεντρο
	if (tree.isEmpty())//αν ειναι αδιο το δεντρο φταχνει την ριζα με τα στιχια που δινοντε
		InsertFlightRoot(id, departureTime, arrivalTime);
	else {
		TreeFlight flight;
		flight.id = id;
		flight.departureTime = departureTime;
		flight.arrivalTime = arrivalTime;
		flight.maxTime = arrivalTime;
		tree.insert(flight);
	}

}

void InsertFlight(){//ζηταει τα στιχια για μια πτιση και επιτα την βαζει στο δεντρο
	string id;
	double departureTime;
	double arrivalTime;
	TreeFlight flight;
	cout << "give flight id";
	cin >> id;
	cout << "give departure time of flight";
	cin >> departureTime;
	cout << "give arrival time of flight";
	cin >> arrivalTime;
		InsertFlight(id, departureTime, arrivalTime);
	
}

void removeFlight() {//ζητα το κοδικο πτισης και την ωρα αναορισης και διαγραφη την τπιση με τα αντιστιχα στιχια
	string id;
	double time;
	cout << "give flight id";
	cin >> id;
	cout << "give departure time of flight";
	cin >> time;
	tree.removeByIddepartureTime(id, time);
}
void printFlightByTime() {//εκτυπωνη την προτι πτιση που θα βρει να ειναι στο χρονικο πλεσιο που δινετε
 	double time1;
	double time2;
	cout << "give time1";
	cin >> time1;
	cout << "give time2 'time2>=time1'";
	cin >> time2;
	tree.printFlightByTime(time1, time2);
}
void printFlightsByTime() {//επτυπωνη ολες της πτισης που ειναι στο χρονικο πλεσιο που δινετε
	double time1;
	double time2;
	cout << "give time1";
	cin >> time1;
	cout << "give time2 'time2>=time1'";
	cin >> time2;
	tree.printFlightsByTime(time1, time2);
}
void maxTimeBeforhTime() {// εκτηπωνη την μεγιστη αφιξη που εχει
	double time;
	cout << "give time";
	cin >> time;
	tree.maxTimeBeforhTime(time);
}
void minTimeAfterhTime() {// εκτηπωνη την ελαχιστη αναχοριση που εκτελιτε μετα την ωρα που δινετε
	double time;
	cout << "give time";
	cin >> time;
	tree.minTimeAfterhTime(time);
}
void commandList() {// εκτηπωνη ολες της εντολες
	cout
		<< "1 for insert \n"
		<< "2 for delete \n"
		<< "3 for flight in the time period x,y \n"
		<< "4 for all flights in the time period x,y \n"
		<< "5 maximum arrival time befor time h \n"
		<< "6 minimum departure time after time h \n"
		<< "7 print all flights \n"
		<< "8 PreLoad example tree \n"
		<< "9 empty the tree\n";
}
void loadExampleTree() {//φορτονει το δεντρο του παραδιγματος
	InsertFlight("OA345", 12, 13);
	InsertFlight("BA123", 9, 11);
	InsertFlight("BA834", 16, 17);
	InsertFlight("SW489", 7, 14);
	InsertFlight("AG879", 10, 12);
	InsertFlight("UA987", 14, 18);
	InsertFlight("OA745", 19, 21);
	InsertFlight("BA854", 6, 12);
	InsertFlight("OA109", 8, 16.30);
	InsertFlight("CA863", 11, 13.30);
	InsertFlight("BA111", 18, 20);
	tree.printAll();
}
int main()
{
	
	
	int command;
	commandList();
	cout << "give command :";
	cin >> command;
	
	while (command!=0)//η κεντρικη λουπα
	{
		switch (command)
		{
		case 1:
			InsertFlight();
			break;
		case 2:
			removeFlight();
			break;
		case 3:
			printFlightByTime();
			break;
		case 4:
			printFlightsByTime();
			break;
		case 5:
			maxTimeBeforhTime();
			break;
		case 6:
			minTimeAfterhTime();
			break;
		case 7:
			tree.printAll();
			break;
		case 8:
			loadExampleTree();
			break;
		case 9:
			tree.makeEmpty();
			break;
		default:
			commandList();
		}
		cout << "give command :";
		cin >> command;
	}
	return 0;
}
#ifndef TREE_H_
#define TREE_H_
#include <iostream>
using namespace std;
#include <string>
#include "TreeFlight.h"
#include "TreeNode.h"
class Tree
{
public:
	Tree(); // constructor
	~Tree(); // destructor


	void printAll(TreeNode*, char, int);//καλει τον εαυτο της δεξια και αριστα απο καθε κομβο και εκτηπονει της τιμες αυτου του κομβου
	void printAll();//εκτυπωνει ολο το δεντρο με αυξουσα σειρα κατα την ωρα αναχορισης καλοντας τον εαυτο της δεξια και αριστα απο την ριζα και εκτηπονει της τιμες της
	double fixMaxTime(TreeNode*);//φτιαχνει τις τιμες μαγ_αφ , καλει τον εαυτο της δεξια και αριστα απο καθε κομβο και επηστρεφει την μεγιστη τιμη αναχορισης απο αριστερα δεξια και τον ιδιο τον κομβο 
	TreeNode* findReplacement(TreeNode*);//ψαχνει για την σοστη αντηκατασταση του κομβου που διαγραφτηκε
	void removeByIddepartureTime(string, double);//ψαχνει και διαγραφη τον κομβο με της τιμες id και departure time, καλει την findReplacement
	void printFlightByTime(double, double);//εκτηπονει τον προτο κομβο που βρισκει να ειναι στο χρονικο πλαισιο που δινετε,καλει τον εαυτο της ως προς την ριζα
	void printFlightByTime(TreeNode*, double, double);//εκτηπονει τον προτο κομβο που βρισκει να ειναι στο χρονικο πλεσιο που δινετε,καλει τον εαυτο της δεξια και αριστερα απο τον κομβο που ειναι μεχρει να το βρει
	void printFlightsByTime(double, double);//εκτηπονει ολλους τους κομβους που ειναι στο χρονικο πλεσιο που δινετε,καλει τον εαυτο της ως προς την ριζα
	void printFlightsByTime(TreeNode*, double, double);//εκτηπονει ολλους τους κομβους που ειναι στο χρονικο πλεσιο που δινετε, καλει τον εαυτο της δεξια και αριστερα απο τον κομβο που ειναι μεχρει να τους βρει
	void maxTimeBeforhTime(double);//ψαχνει ολους τους κομβους που ειναι πριν την ωρα που δινετε και βρισκει την μεγιστη τιμη αναχορισεις,καλει τον εαυτο της ως προς την ριζα
	double maxTimeBeforhTime(TreeNode*, double);//ψαχνει ολους τους κομβους που ειναι πριν την ωρα που δινετε και βρισκει την μεγιστη τιμη αναχορισεις, καλει τον εαυτο της δεξια και αριστερα απο τον κομβο που ειναι μεχρει να τους βρει
	void minTimeAfterhTime(double);//ψαχνει ολους τους κομβους που ειναι μετα την ωρα που δινετε και βρισκει την ωρα αναχορισεις που ειναι πιο κοντα σε αυτην την ωρα
	void insert(const TreeFlight);//προσθετη ενα κενουργιο κομβο στο δεντρο με της τιμες που δινονται
	void makeEmpty();//συναρτιση για αδιασμα του δεντρου,καλει τον εαυτο της, ξεκινα να διαγραφη απο τα φυλλα
	void makeEmpty(TreeNode*);//συναρτιση για αδιασμα του δεντρου,καλει τον εαυτο της, ξεκινα να διαγραφη απο τα φυλλα
	bool isEmpty() const;//ελενχει αν υπαρχει ριζα "αν ειναι αδιο το δεντρο"
private:
	TreeNode *rootPtr; // δείκτης στο πρωτο node
	TreeNode *getNewNode(const TreeFlight &);// Λειτουργία δημιουργία καινούργιου Node
};

// constructor
Tree::Tree()
	: rootPtr(0)

{
}

// destructor
Tree::~Tree()
{
	makeEmpty();
}
void Tree::makeEmpty() {
	if (!isEmpty()) // Αν δεν είναι αδειο το δεντρο
	{
		makeEmpty(rootPtr);
		rootPtr = 0;
	}
}
void Tree::makeEmpty(TreeNode* tempPtr) {
	if (tempPtr->leftPtr != 0) {//αν υπαρχει αριστερο παιδι καλει τον εαυτο της για αριστερα
		makeEmpty(tempPtr->leftPtr);
		tempPtr->leftPtr = 0;
	}
	if (tempPtr->rightPtr != 0) {//αν υπαρχει δεξιο παιδι καλει τον εαυτο της φια δεξια
		makeEmpty(tempPtr->rightPtr);
		tempPtr->rightPtr = 0;
	}
	delete tempPtr;//διαγραφει τον κομβο
}
void Tree::insert(const TreeFlight value) {
	TreeNode* newPtr = getNewNode(value);
	if (rootPtr == 0)//αν δεν υπαρχει ριζα, ο νεος κομβος θα γινει ριζα
	{

		rootPtr = newPtr;
		return;
	}
	TreeNode *tempPtr = rootPtr;
	while (true)
	{
		if (newPtr->data.maxTime > tempPtr->data.maxTime)//φτιαχνει την μεγ_αφ καθος ο κενουργος κομβος περνα απο τους υπαρχνοντες
			tempPtr->data.maxTime = newPtr->data.maxTime;

		if (newPtr->data.departureTime >= tempPtr->data.departureTime)//αν η ωρα αναχορισεις του νεου κομβου ειναι μεγαλιτερη απο τον παρον κομβο θα προχοριση στον δεξια κομβο αλλιος στον αριστερα
		{
			if (tempPtr->rightPtr == 0)//αν ο δεξια κομβος ειναι αδιος βαλε στην αδια θεση το νεω κομβο αλλιος μετακηνησε τον δεκτι στον δεξια κομβο
			{
				tempPtr->rightPtr = newPtr;
				return;
			}
			else
				tempPtr = tempPtr->rightPtr;
		}
		else
		{
			if (tempPtr->leftPtr == 0)//αν ο αριστερος κομβος ειναι αδειος βαλε στην αδεια θεση το νεο κομβο αλλιος μετακινησε τον δεκτι στον αριστερο κομβο
			{
				tempPtr->leftPtr = newPtr;
				return;
			}
			else
				tempPtr = tempPtr->leftPtr;
		}
	}
}
void Tree::printAll() {
	int hight = 0;
	if (isEmpty()) {
		cout << "it is empty \n";
		return;
	}
	if (rootPtr->leftPtr != 0)// αν υπαρχει ο αριστερος κομβος καλεσε τον εαυτο σου ως προς τον αριστερο κομβο
		printAll(rootPtr->leftPtr, 'L', hight);

	cout << rootPtr->data.id << " : " << rootPtr->data.departureTime << " : " << rootPtr->data.arrivalTime << " : " << rootPtr->data.maxTime << " root \n";//εκτηπωσε την τιμη της ριζας

	if (rootPtr->rightPtr != 0)// αν υπαρχει ο δεξιος κομβος καλεσε τον εαυτο σου ως προς τον δεξιο κομβο
		printAll(rootPtr->rightPtr, 'R', hight);
}
void Tree::printAll(TreeNode* tempPtr, char lof, int hight) {
	hight += 1;

	if (tempPtr->leftPtr != 0)// αν υπαρχει ο αριστερος κομβος καλεσε τον εαυτο σου ως προς τον αριστερο κομβο
		printAll(tempPtr->leftPtr, 'L', hight);

	cout << tempPtr->data.id << " : " << tempPtr->data.departureTime << " : " << tempPtr->data.arrivalTime << " : " << tempPtr->data.maxTime << " : " << hight << " : " << lof << endl;//εκτηπωσε την τιμη του κομβου

	if (tempPtr->rightPtr != 0)// αν υπαρχει ο δεξιος κομβος καλεσε τον εαυτο σου ως προς τον δεξιο κομβο
		printAll(tempPtr->rightPtr, 'R', hight);

	return;
}
double Tree::fixMaxTime(TreeNode* tempPtr) {
	double maxTime1 = 0;
	double maxTime2 = 0;
	if (tempPtr->leftPtr != 0)//βρισκη το μεγιστο απο αριστερα αν υπαρχει ο κομβος
		maxTime1 = fixMaxTime(tempPtr->leftPtr);

	if (tempPtr->rightPtr != 0)//βρισκη το μεγιστο απο δεξια αν υπαρχει ο κομβος
		maxTime2 = fixMaxTime(tempPtr->rightPtr);

	tempPtr->data.maxTime = max(max(maxTime1, maxTime2), tempPtr->data.arrivalTime);//βρισκη το μεγ_αφ
	return tempPtr->data.maxTime;
}
TreeNode* Tree::findReplacement(TreeNode* tempPtr) {
	int x = 0;//μεταβλιτη αριστερις ή δεξιας κινισης
	TreeNode* firstPtr = tempPtr;
	if (tempPtr->leftPtr != 0)//αν υπαρχει ο αριστερα κομβος
	{
		TreeNode* replPtr = tempPtr->leftPtr;//πιγενει αριστερα
		x = 1;

		if (replPtr->rightPtr == 0 && replPtr->leftPtr == 0)//αν δεν υπαρχει παιδι περνει το δεξι παιδι του κομβου που θα διαγραφει και επηστρεφει τον αντικαταστατι
		{
			replPtr->leftPtr = 0;
			replPtr->rightPtr = firstPtr->rightPtr;
			return replPtr;
		}
		else if (replPtr->rightPtr != 0)//αν υπαρχει ο δεξις κομβος, φτανει σε φυλλο και του δινει τα παιδια του κομβου που θα διαγραφει,μηδενιζει το δεκτι απο τον οπιο προηλθε και επηστρεφει το φυλλο ως αντικαταστατι
		{
			x = 2;
			tempPtr = replPtr;
			replPtr = replPtr->rightPtr;
			while (true)
			{
				if (replPtr->rightPtr == 0 && replPtr->leftPtr == 0)
				{
					if (x == 1)
						tempPtr->leftPtr = 0;
					else if (x == 2)
						tempPtr->rightPtr = 0;
					replPtr->leftPtr = firstPtr->leftPtr;
					replPtr->rightPtr = firstPtr->rightPtr;
					return replPtr;
				}
				else if (replPtr->rightPtr != 0)
				{
					x = 2;
					tempPtr = replPtr;
					replPtr = replPtr->rightPtr;

				}
				else if (replPtr->leftPtr != 0) {
					x = 1;
					tempPtr = replPtr;
					replPtr = replPtr->leftPtr;
				}
			}
		}
		else if (replPtr->rightPtr == 0) {//αν το αριστερο παιδι του κομβου που θα διαγραφι εχει παιδι μονο αριστερα , θετει το δεξει παιδι ως το δεξει παιδι του κομβου που θα διαγραφι
			replPtr->rightPtr = firstPtr->rightPtr;
			return replPtr;
		}
	}
	else if (tempPtr->rightPtr != 0)//αν υπαρχει το δεξει παιδι πιγενε στον δεξια κομβο
	{
		TreeNode* replPtr = tempPtr->rightPtr;
		x = 2;

		if (replPtr->rightPtr == 0 && replPtr->leftPtr == 0)//αν αυτος ο κομβος ειναι φυλλο,κανει το δεξι παιδι του το δεξι παιδι του κομβου που θα διαγραφι
		{
			replPtr->rightPtr = 0;
			replPtr->rightPtr = firstPtr->rightPtr;
			return replPtr;
		}
		else if (replPtr->leftPtr != 0)//αν υπαρχει ο αριστερος κομβος, φτανει σε φυλλο και του δινει τα παιδια του κομβου που θα διαγραφει,μηδενιζει το δεκτι απο τον οποιο προηλθε και επηστρεφει το φυλλο ως αντικαταστατι
		{
			tempPtr = replPtr;
			replPtr = replPtr->leftPtr;
			x = 1;
			while (true)
			{

				if (replPtr->rightPtr == 0 && replPtr->leftPtr == 0)
				{
					if (x == 1)
						tempPtr->leftPtr = 0;
					else if (x == 2)
						tempPtr->rightPtr = 0;
					replPtr->leftPtr = firstPtr->leftPtr;
					replPtr->rightPtr = firstPtr->rightPtr;
					return replPtr;
				}
				else if (replPtr->leftPtr == 0) {
					if (x == 1)
						tempPtr->leftPtr = 0;
					else if (x == 2)
						tempPtr->rightPtr = 0;
					replPtr->leftPtr = firstPtr->leftPtr;
					return replPtr;
				}
				else if (replPtr->rightPtr != 0)
				{
					tempPtr = replPtr;
					replPtr = replPtr->rightPtr;
					x = 2;
				}
			}
		}
		else if (replPtr->leftPtr == 0) {//αν το δεξι παιδι του κομβου που θα διαγραφι εχει παιδι μονο δεξι , θετει το αριστερο παιδι ως το αριστερο παιδι του κομβου που θα διαγραφι
			tempPtr->rightPtr = 0;
			replPtr->leftPtr = firstPtr->leftPtr;
			return replPtr;
		}

	}
	else//αλλιος ο κομβος που θα διαγραφει ειναι φυλλο και επιστρεφει ως αντικαταστατι το 0
	{
		return 0;
	}
}
void Tree::removeByIddepartureTime(string id, double time) {
	if (rootPtr == 0)//αν δεν υπαρχει η ριζα σταματα
	{
		return;
	}
	TreeNode *tempPtr = rootPtr;
	TreeNode *prevPtr = rootPtr;
	TreeNode *replPtr = rootPtr;
	bool isRoot = true;
	bool fromLeft = true;
	while (tempPtr != 0)//
	{
		if (tempPtr->data.id == id)//αν το βρει καλει την συναρτιση findReplacement ,διαγραφει το κομβο, αντικατιστα το κομβο που διαγραφικε με τον αντικαταστατι του
		{

			replPtr = findReplacement(tempPtr);
			if (isRoot)
			{
				delete rootPtr;
				rootPtr = replPtr;
				cout << "here root is " << rootPtr->data.id << " repl is " << replPtr->data.id << endl;
			}
			else if (fromLeft)
			{
				delete tempPtr;
				prevPtr->leftPtr = replPtr;
			}
			else {
				delete tempPtr;
				prevPtr->rightPtr = replPtr;
			}
			fixMaxTime(rootPtr);
			return;
		}
		else if (time >= tempPtr->data.departureTime)//μετακινιση αριστερα ή δεξια αναλογα με το χρονο αναχορισης
		{
			fromLeft = false;
			isRoot = false;
			prevPtr = tempPtr;
			tempPtr = tempPtr->rightPtr;
		}
		else if (time < tempPtr->data.departureTime)
		{
			fromLeft = true;
			isRoot = false;
			prevPtr = tempPtr;
			tempPtr = tempPtr->leftPtr;
		}
	}
}
void Tree::printFlightByTime(double time1, double time2) {
	printFlightByTime(rootPtr, time1, time2);
}
void Tree::printFlightByTime(TreeNode* tempPtr, double time1, double time2) {
	if ((time1 <= tempPtr->data.departureTime && tempPtr->data.departureTime <= time2) || (time1 <= tempPtr->data.arrivalTime && tempPtr->data.arrivalTime <= time2)) {//αν ειναι μεσα στο χρονικο πλεσιο που δοθηκε, εκτηπωνει την πτηση και σταματα να ψαχνει
		cout << tempPtr->data.id << endl;
		return;
	}
	if (tempPtr->leftPtr != 0)
		printFlightByTime(tempPtr->leftPtr, time1, time2);// αν υπαρχει το αριστερο παιδι καλει τον εαυτο της αριστερα

	if (tempPtr->rightPtr != 0)//αν υπαρχει το δεξι παιδι καλει τον εαυτο της δεξι
		printFlightByTime(tempPtr->rightPtr, time1, time2);
}
void Tree::printFlightsByTime(double time1, double time2) {
	printFlightsByTime(rootPtr, time1, time2);
}
void Tree::printFlightsByTime(TreeNode* tempPtr, double time1, double time2) {
	if (tempPtr->leftPtr != 0)//αν υπαρχει το αριστερο παιδι καλει τον εαυτο της αριστερα
		printFlightsByTime(tempPtr->leftPtr, time1, time2);

	if ((time1 <= tempPtr->data.departureTime && tempPtr->data.departureTime <= time2) || (time1 <= tempPtr->data.arrivalTime && tempPtr->data.arrivalTime <= time2))//αν ειναι μεσα στο χρονικο πλεσιο που δοθηκε, εκτηπωνει την πτηση
		cout << tempPtr->data.id << endl;

	if (tempPtr->rightPtr != 0)//αν υπαρχει το δεξι παιδι καλει τον εαυτο της δεξι
		printFlightsByTime(tempPtr->rightPtr, time1, time2);
}

void Tree::maxTimeBeforhTime(double h) {
	if (rootPtr == 0)
		return;
	cout << maxTimeBeforhTime(rootPtr->rightPtr, h) << endl;
}
double Tree::maxTimeBeforhTime(TreeNode* tempPtr, double h) {
	double time1 = 0;
	double time2 = 0;
	double time3 = 0;
	if (tempPtr->data.departureTime <= h) //αν η ωρα αναχορισης ειναι μηκροτερη απο την ωρα h τοτε θα υπολογιση και αυτην την ωρα για να βρει το μεγιστο
		time3 = tempPtr->data.arrivalTime;
	if (tempPtr->leftPtr != 0)// αν υπαρχει ο αριστερος κομβος καλει τον εαυτο της ως προς αριστερα και περνει το μεγιστο του "δεν ελενχο τον αριστερο χρονο επηδει μπορει σε καποιο αριστεροτερο κομβο η ωρα αναχορισης ειναι μηκροτερη απο την h"
		time1 = maxTimeBeforhTime(tempPtr->leftPtr, h);
	if (tempPtr->rightPtr != 0 && tempPtr->data.departureTime <= h)// αν υπαρχει ο δεξιος κομβος και η ωρα αναχορισης ειναι μικροτερη απο το h καλει τον εαυτο της ως προς δεξια 
		time2 = maxTimeBeforhTime(tempPtr->rightPtr, h);
	return max(max(time1, time2), time3);//επηστεφει την μεγιστη ωρα αφιξεις
}
void Tree::minTimeAfterhTime(double h) {
	double min = -1;
	if (rootPtr == 0)
		return;
	TreeNode *tempPtr = rootPtr;
	if (rootPtr->data.departureTime >= h)//ελενχει αν η τιμη αναχορισης της ριζας ειναι μετα την ωρα h αν ναι τοτε την θετει ως ελιχιστη
		min = rootPtr->data.departureTime;
	while (tempPtr->leftPtr != 0 || tempPtr->rightPtr != 0)
	{
		if (tempPtr->leftPtr != 0 && tempPtr->leftPtr->data.departureTime >= h)
		{
			tempPtr = tempPtr->leftPtr;
		}
		else if (tempPtr->rightPtr != 0)
		{
			tempPtr = tempPtr->rightPtr;
		}
		if (tempPtr->data.departureTime >= h && (tempPtr->data.departureTime < min || min == -1))
		{
			min = tempPtr->data.departureTime;
		}
	}
	if (min == -1)
		cout << "NaN Found" << endl;
	else
		cout << min << endl;
	return;
}

bool Tree::isEmpty() const
{
	return rootPtr == 0;
}


TreeNode *Tree::getNewNode(const TreeFlight &value)
{
	return new TreeNode(value);
}
#endif
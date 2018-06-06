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


	void printAll(TreeNode*, char, int);//����� ��� ����� ��� ����� ��� ������ ��� ���� ����� ��� ��������� ��� ����� ����� ��� ������
	void printAll();//��������� ��� �� ������ �� ������� ����� ���� ��� ��� ���������� �������� ��� ����� ��� ����� ��� ������ ��� ��� ���� ��� ��������� ��� ����� ���
	double fixMaxTime(TreeNode*);//�������� ��� ����� ���_�� , ����� ��� ����� ��� ����� ��� ������ ��� ���� ����� ��� ���������� ��� ������� ���� ���������� ��� �������� ����� ��� ��� ���� ��� ����� 
	TreeNode* findReplacement(TreeNode*);//������ ��� ��� ����� ������������� ��� ������ ��� �����������
	void removeByIddepartureTime(string, double);//������ ��� �������� ��� ����� �� ��� ����� id ��� departure time, ����� ��� findReplacement
	void printFlightByTime(double, double);//��������� ��� ����� ����� ��� ������� �� ����� ��� ������� ������� ��� ������,����� ��� ����� ��� �� ���� ��� ����
	void printFlightByTime(TreeNode*, double, double);//��������� ��� ����� ����� ��� ������� �� ����� ��� ������� ������ ��� ������,����� ��� ����� ��� ����� ��� �������� ��� ��� ����� ��� ����� ������ �� �� ����
	void printFlightsByTime(double, double);//��������� ������ ���� ������� ��� ����� ��� ������� ������ ��� ������,����� ��� ����� ��� �� ���� ��� ����
	void printFlightsByTime(TreeNode*, double, double);//��������� ������ ���� ������� ��� ����� ��� ������� ������ ��� ������, ����� ��� ����� ��� ����� ��� �������� ��� ��� ����� ��� ����� ������ �� ���� ����
	void maxTimeBeforhTime(double);//������ ����� ���� ������� ��� ����� ���� ��� ��� ��� ������ ��� ������� ��� ������� ���� �����������,����� ��� ����� ��� �� ���� ��� ����
	double maxTimeBeforhTime(TreeNode*, double);//������ ����� ���� ������� ��� ����� ���� ��� ��� ��� ������ ��� ������� ��� ������� ���� �����������, ����� ��� ����� ��� ����� ��� �������� ��� ��� ����� ��� ����� ������ �� ���� ����
	void minTimeAfterhTime(double);//������ ����� ���� ������� ��� ����� ���� ��� ��� ��� ������ ��� ������� ��� ��� ����������� ��� ����� ��� ����� �� ����� ��� ���
	void insert(const TreeFlight);//�������� ��� ��������� ����� ��� ������ �� ��� ����� ��� ��������
	void makeEmpty();//��������� ��� ������� ��� �������,����� ��� ����� ���, ������ �� �������� ��� �� �����
	void makeEmpty(TreeNode*);//��������� ��� ������� ��� �������,����� ��� ����� ���, ������ �� �������� ��� �� �����
	bool isEmpty() const;//������� �� ������� ���� "�� ����� ���� �� ������"
private:
	TreeNode *rootPtr; // ������� ��� ����� node
	TreeNode *getNewNode(const TreeFlight &);// ���������� ���������� ����������� Node
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
	if (!isEmpty()) // �� ��� ����� ����� �� ������
	{
		makeEmpty(rootPtr);
		rootPtr = 0;
	}
}
void Tree::makeEmpty(TreeNode* tempPtr) {
	if (tempPtr->leftPtr != 0) {//�� ������� �������� ����� ����� ��� ����� ��� ��� ��������
		makeEmpty(tempPtr->leftPtr);
		tempPtr->leftPtr = 0;
	}
	if (tempPtr->rightPtr != 0) {//�� ������� ����� ����� ����� ��� ����� ��� ��� �����
		makeEmpty(tempPtr->rightPtr);
		tempPtr->rightPtr = 0;
	}
	delete tempPtr;//��������� ��� �����
}
void Tree::insert(const TreeFlight value) {
	TreeNode* newPtr = getNewNode(value);
	if (rootPtr == 0)//�� ��� ������� ����, � ���� ������ �� ����� ����
	{

		rootPtr = newPtr;
		return;
	}
	TreeNode *tempPtr = rootPtr;
	while (true)
	{
		if (newPtr->data.maxTime > tempPtr->data.maxTime)//�������� ��� ���_�� ����� � ��������� ������ ����� ��� ���� �����������
			tempPtr->data.maxTime = newPtr->data.maxTime;

		if (newPtr->data.departureTime >= tempPtr->data.departureTime)//�� � ��� ����������� ��� ���� ������ ����� ���������� ��� ��� ����� ����� �� ��������� ���� ����� ����� ������ ���� ��������
		{
			if (tempPtr->rightPtr == 0)//�� � ����� ������ ����� ����� ���� ���� ���� ���� �� ��� ����� ������ ���������� ��� ����� ���� ����� �����
			{
				tempPtr->rightPtr = newPtr;
				return;
			}
			else
				tempPtr = tempPtr->rightPtr;
		}
		else
		{
			if (tempPtr->leftPtr == 0)//�� � ��������� ������ ����� ������ ���� ���� ����� ���� �� ��� ����� ������ ���������� ��� ����� ���� �������� �����
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
	if (rootPtr->leftPtr != 0)// �� ������� � ��������� ������ ������ ��� ����� ��� �� ���� ��� �������� �����
		printAll(rootPtr->leftPtr, 'L', hight);

	cout << rootPtr->data.id << " : " << rootPtr->data.departureTime << " : " << rootPtr->data.arrivalTime << " : " << rootPtr->data.maxTime << " root \n";//�������� ��� ���� ��� �����

	if (rootPtr->rightPtr != 0)// �� ������� � ������ ������ ������ ��� ����� ��� �� ���� ��� ����� �����
		printAll(rootPtr->rightPtr, 'R', hight);
}
void Tree::printAll(TreeNode* tempPtr, char lof, int hight) {
	hight += 1;

	if (tempPtr->leftPtr != 0)// �� ������� � ��������� ������ ������ ��� ����� ��� �� ���� ��� �������� �����
		printAll(tempPtr->leftPtr, 'L', hight);

	cout << tempPtr->data.id << " : " << tempPtr->data.departureTime << " : " << tempPtr->data.arrivalTime << " : " << tempPtr->data.maxTime << " : " << hight << " : " << lof << endl;//�������� ��� ���� ��� ������

	if (tempPtr->rightPtr != 0)// �� ������� � ������ ������ ������ ��� ����� ��� �� ���� ��� ����� �����
		printAll(tempPtr->rightPtr, 'R', hight);

	return;
}
double Tree::fixMaxTime(TreeNode* tempPtr) {
	double maxTime1 = 0;
	double maxTime2 = 0;
	if (tempPtr->leftPtr != 0)//������ �� ������� ��� �������� �� ������� � ������
		maxTime1 = fixMaxTime(tempPtr->leftPtr);

	if (tempPtr->rightPtr != 0)//������ �� ������� ��� ����� �� ������� � ������
		maxTime2 = fixMaxTime(tempPtr->rightPtr);

	tempPtr->data.maxTime = max(max(maxTime1, maxTime2), tempPtr->data.arrivalTime);//������ �� ���_��
	return tempPtr->data.maxTime;
}
TreeNode* Tree::findReplacement(TreeNode* tempPtr) {
	int x = 0;//��������� ��������� � ������ �������
	TreeNode* firstPtr = tempPtr;
	if (tempPtr->leftPtr != 0)//�� ������� � �������� ������
	{
		TreeNode* replPtr = tempPtr->leftPtr;//������� ��������
		x = 1;

		if (replPtr->rightPtr == 0 && replPtr->leftPtr == 0)//�� ��� ������� ����� ������ �� ���� ����� ��� ������ ��� �� ��������� ��� ���������� ��� �������������
		{
			replPtr->leftPtr = 0;
			replPtr->rightPtr = firstPtr->rightPtr;
			return replPtr;
		}
		else if (replPtr->rightPtr != 0)//�� ������� � ����� ������, ������ �� ����� ��� ��� ����� �� ������ ��� ������ ��� �� ���������,��������� �� ����� ��� ��� ���� ������� ��� ���������� �� ����� �� �������������
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
		else if (replPtr->rightPtr == 0) {//�� �� �������� ����� ��� ������ ��� �� �������� ���� ����� ���� �������� , ����� �� ����� ����� �� �� ����� ����� ��� ������ ��� �� ��������
			replPtr->rightPtr = firstPtr->rightPtr;
			return replPtr;
		}
	}
	else if (tempPtr->rightPtr != 0)//�� ������� �� ����� ����� ������ ���� ����� �����
	{
		TreeNode* replPtr = tempPtr->rightPtr;
		x = 2;

		if (replPtr->rightPtr == 0 && replPtr->leftPtr == 0)//�� ����� � ������ ����� �����,����� �� ���� ����� ��� �� ���� ����� ��� ������ ��� �� ��������
		{
			replPtr->rightPtr = 0;
			replPtr->rightPtr = firstPtr->rightPtr;
			return replPtr;
		}
		else if (replPtr->leftPtr != 0)//�� ������� � ��������� ������, ������ �� ����� ��� ��� ����� �� ������ ��� ������ ��� �� ���������,��������� �� ����� ��� ��� ����� ������� ��� ���������� �� ����� �� �������������
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
		else if (replPtr->leftPtr == 0) {//�� �� ���� ����� ��� ������ ��� �� �������� ���� ����� ���� ���� , ����� �� �������� ����� �� �� �������� ����� ��� ������ ��� �� ��������
			tempPtr->rightPtr = 0;
			replPtr->leftPtr = firstPtr->leftPtr;
			return replPtr;
		}

	}
	else//������ � ������ ��� �� ��������� ����� ����� ��� ���������� �� ������������� �� 0
	{
		return 0;
	}
}
void Tree::removeByIddepartureTime(string id, double time) {
	if (rootPtr == 0)//�� ��� ������� � ���� �������
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
		if (tempPtr->data.id == id)//�� �� ���� ����� ��� ��������� findReplacement ,��������� �� �����, ����������� �� ����� ��� ���������� �� ��� ������������� ���
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
		else if (time >= tempPtr->data.departureTime)//���������� �������� � ����� ������� �� �� ����� ����������
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
	if ((time1 <= tempPtr->data.departureTime && tempPtr->data.departureTime <= time2) || (time1 <= tempPtr->data.arrivalTime && tempPtr->data.arrivalTime <= time2)) {//�� ����� ���� ��� ������� ������ ��� ������, ��������� ��� ����� ��� ������� �� ������
		cout << tempPtr->data.id << endl;
		return;
	}
	if (tempPtr->leftPtr != 0)
		printFlightByTime(tempPtr->leftPtr, time1, time2);// �� ������� �� �������� ����� ����� ��� ����� ��� ��������

	if (tempPtr->rightPtr != 0)//�� ������� �� ���� ����� ����� ��� ����� ��� ����
		printFlightByTime(tempPtr->rightPtr, time1, time2);
}
void Tree::printFlightsByTime(double time1, double time2) {
	printFlightsByTime(rootPtr, time1, time2);
}
void Tree::printFlightsByTime(TreeNode* tempPtr, double time1, double time2) {
	if (tempPtr->leftPtr != 0)//�� ������� �� �������� ����� ����� ��� ����� ��� ��������
		printFlightsByTime(tempPtr->leftPtr, time1, time2);

	if ((time1 <= tempPtr->data.departureTime && tempPtr->data.departureTime <= time2) || (time1 <= tempPtr->data.arrivalTime && tempPtr->data.arrivalTime <= time2))//�� ����� ���� ��� ������� ������ ��� ������, ��������� ��� �����
		cout << tempPtr->data.id << endl;

	if (tempPtr->rightPtr != 0)//�� ������� �� ���� ����� ����� ��� ����� ��� ����
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
	if (tempPtr->data.departureTime <= h) //�� � ��� ���������� ����� ��������� ��� ��� ��� h ���� �� ��������� ��� ����� ��� ��� ��� �� ���� �� �������
		time3 = tempPtr->data.arrivalTime;
	if (tempPtr->leftPtr != 0)// �� ������� � ��������� ������ ����� ��� ����� ��� �� ���� �������� ��� ������ �� ������� ��� "��� ������ ��� �������� ����� ������ ������ �� ������ ������������ ����� � ��� ���������� ����� ��������� ��� ��� h"
		time1 = maxTimeBeforhTime(tempPtr->leftPtr, h);
	if (tempPtr->rightPtr != 0 && tempPtr->data.departureTime <= h)// �� ������� � ������ ������ ��� � ��� ���������� ����� ��������� ��� �� h ����� ��� ����� ��� �� ���� ����� 
		time2 = maxTimeBeforhTime(tempPtr->rightPtr, h);
	return max(max(time1, time2), time3);//��������� ��� ������� ��� �������
}
void Tree::minTimeAfterhTime(double h) {
	double min = -1;
	if (rootPtr == 0)
		return;
	TreeNode *tempPtr = rootPtr;
	if (rootPtr->data.departureTime >= h)//������� �� � ���� ���������� ��� ����� ����� ���� ��� ��� h �� ��� ���� ��� ����� �� ��������
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
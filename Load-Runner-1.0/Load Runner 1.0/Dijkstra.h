//Header guards avoids double inclusion of the header file

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include<vector>
#include<iostream>
#include<algorithm>
#include"GLOBALS.h"


const int MAXROW = ROWS;
const int MAXCOL = COLUMNS;

/*
-UML DIAGRAM-
Class Node												|
________________________________________________________|
-costSoFar:int											|
-row:int												|
-col:int												|
-from:Node*												|
________________________________________________________|
+Node():Node											|
+Node(int,int,int,Node*):Node*							|
+getRow():int											|
+getCol():int											|
+setCostSoFar(int):void									|
+getCostSoFar():int										|
+setFromNode(Node*):void								|
+getFromNode():Node*									|
+operator == (const Node*):bool							|
+operator != (const Node*):bool							|
+blockNumber(int,int):static int						|
+getAdjNodes(Node*,Node*[]):static std::vector<Node*>	|
________________________________________________________|
*/
class Node
{
	int costSoFar;
	int row, col;
	Node *from;
public:

	Node() {}

	Node(int aCostSoFar, int aRow, int aCol, Node *aFrom) : costSoFar(aCostSoFar), row(aRow), col(aCol), from(aFrom)
	{}

	//returns row of this node in map
	inline int getRow() { return row; }

	//returns col of this node in map
	inline int getCol() { return col; }

	//sets the cost so far of this node
	void setCostSoFar(int costSoFar) { this->costSoFar = costSoFar; }

	//returns the current cost so of this node
	int getCostSoFar() { return costSoFar; }

	//sets the from node
	void setFromNode(Node*);

	//returns the from node
	Node* getFromNode() { return from; }

	//compares the "this" to other Node...returns true if both are equal otherwise false
	bool operator == (const Node*);

	//compares the "this" to other Node...returns true if both are unequal otherwise false
	bool operator != (const Node*);

	//returns the index represented by row and col in the map
	inline static int Node::blockNumber(int row, int col)
	{
		return MAXCOL * row + col;
	}

	//returns Nodes which are adjacent to Node*
	static std::vector<Node*> getAdjNodes(Node*, Node*[]);

};

//definitions of class Node member functions
void Node::setFromNode(Node * current)
{
	this->from = current;
}


bool Node::operator==(const Node* other)
{
	return (other->col == this->col) && (other->row == this->row);
}


bool Node::operator!=(const Node*other)
{
	return (other->col != this->col) || (other->row != this->row);
}


std::vector<Node*> Node::getAdjNodes(Node* current, Node *nMap[])
{
	std::vector<Node*> nodes;

	if (current->getRow() < MAXROW - 1)
		nodes.push_back(nMap[Node::blockNumber(current->getRow() + 1, current->getCol())]);

	if (current->getCol() < MAXCOL - 1)
		nodes.push_back(nMap[Node::blockNumber(current->getRow(), current->getCol() + 1)]);

	if (current->getCol() > 0)
		nodes.push_back(nMap[Node::blockNumber(current->getRow(), current->getCol() - 1)]);

	if (current->getRow() > 0)
		nodes.push_back(nMap[Node::blockNumber(current->getRow() - 1, current->getCol())]);

	/*if (current->getRow()<MAXROW - 1 && current->getCol()>0)
	nodes.push_back(nMap[Node::blockNumber(current->getRow() + 1, current->getCol() - 1)]);

	if (current->getRow()>0 && current->getCol()<MAXCOL - 1)
	nodes.push_back(nMap[Node::blockNumber(current->getRow() - 1, current->getCol() + 1)]);

	if (current->getRow()>0 && current->getCol()>0)
	nodes.push_back(nMap[Node::blockNumber(current->getRow() - 1, current->getCol() - 1)]);

	if (current->getRow()<MAXROW - 1 && current->getCol()<MAXCOL - 1)
	nodes.push_back(nMap[Node::blockNumber(current->getRow() + 1, current->getCol() + 1)]);*/

	return nodes;
}

/* *** End of class Node*** */



/*
-UML DIAGRAM-
Class MyList
____________________________|
+operator +=(Node*):void	|
+operator !=(Node*):void	|
+contains(Node*):bool		|
____________________________|
public std::vector<Node*> <------- MyList
*/
class MyList : public std::vector<Node*>
{
public:
	//adds the node to the list
	void operator +=(Node*);
	//removes the particular node from the list
	void operator -=(Node*);
	//checks whether the current list contains particular node....if it contains then it will return true else will return false.
	bool contains(Node*);
	//returns the node which is at the begining of the list
	Node* getFirstNode();

};

//Definitions of MyList member functions
void MyList::operator+=(Node* obj)
{

	this->push_back(obj);
}


void MyList::operator-=(Node* obj)
{
	auto  iter = std::remove(this->begin(), this->end(), obj);
	this->erase(iter, this->end());
}


bool MyList::contains(Node* obj)
{
	for (vector<Node*>::iterator iter = this->begin(); iter != this->end(); iter++) {
		if ((*iter)->operator==(obj)) return true;
	}
	return false;
}


Node* MyList::getFirstNode()
{
	auto iter = begin();
	return *iter;
}

//Reverse the contents of the given std::vector
void reverse(std::vector<int> &v)
{
	auto iter1 = v.begin();
	auto iter2 = v.end();
	iter2--;
	for (unsigned int i = 0; i < v.size() / 2; i++)
	{

		*iter1 = *iter1 + *iter2;
		*iter2 = *iter1 - *iter2;
		*iter1 = *iter1 - *iter2;

		iter1++;
		iter2--;
	}
}

//This function helps std::sort algorithm to sort the contents of openList
bool sortHelper(Node* i, Node* j)
{
	return (i->getCostSoFar()<j->getCostSoFar());
}


std::vector<int> dijsktra(const int *map, Node *startNode, Node* goalNode)
{
	Node* nMap[MAXROW*MAXCOL];

	/*
	Creating Nodes for map (Allocating memory).
	The Memory will allocated only for those nodes which are not the goalNode and the startNode
	*/
	for (int row = 0; row < MAXROW; row++)
	{
		for (int col = 0; col < MAXCOL; col++)
		{
			if (row == startNode->getRow() && col == startNode->getCol())
				nMap[Node::blockNumber(row, col)] = startNode;
			if (row == goalNode->getRow() && col == goalNode->getCol())
				nMap[Node::blockNumber(row, col)] = goalNode;
			nMap[Node::blockNumber(row, col)] = new Node(map[Node::blockNumber(row, col)], row, col, 0);
		}
	}


	Node *current = 0;

	//openList containts the nodes whose subnodes are not traversed
	MyList openList;
	//closeList contains the nodes whose subnodes are traversed
	MyList closedList;

	openList += startNode;

	while (openList.size() > 0)
	{
		//sorting openList in ascending order of cost so far
		sort(openList.begin(), openList.end(), sortHelper);

		//Getting first node from the list
		current = openList.getFirstNode();

		//Comparing whether this node is goal node
		if (*current == (goalNode))
			break;

		//Getting adjacent nodes of this node
		std::vector<Node*> adjNodes = Node::getAdjNodes(current, nMap);

		//foreach loop : A C++ 11 feature
		for (Node* node : adjNodes)
		{
			//calculating cost so far for subnode
			int totalCostSoFar = current->getCostSoFar() + map[Node::blockNumber(node->getRow(), node->getCol())];

			//if the node is already in the closedList then check next subnode
			if (closedList.contains(node))
				continue;

			/*
			if the node is already in openList then it should already have a cost so far value
			and if the previous cost so far is less than the current one then we dont need to 
			update its value . if the previous cost so fat is greater than current cost so far then 
			we will update its cost so far value and Its connection i.e fromNode value
			*/
			if (openList.contains(node))
			{
				if (node->getCostSoFar() <= totalCostSoFar)
					continue;
				else
				{

					node->setCostSoFar(totalCostSoFar);
					node->setFromNode(current);
				}
			}
			else
			{
				node->setCostSoFar(totalCostSoFar);
				node->setFromNode(current);
				openList += node;
			}
		}

		/*
		Now at this point all the subnodes of this node are traversed 
		so deleting currentNode from the openList and adding it to the closedList
		*/
		openList -= current;
		closedList += current;


	}

	//Creating an array so we can store our path
	std::vector<int> path;

	/*If the goal node is not found in the given map then inform it*/
	assert(*current==goalNode);

	/*
	Going back from the currentNode in the reverse direction and pushing the index in path
	*/
	while (current->operator!=(startNode))
	{
		path.push_back(Node::blockNumber(current->getRow(), current->getCol()));
		current = current->getFromNode();
	}

	path.push_back(Node::blockNumber(startNode->getRow(), startNode->getCol()));

	for (int row = 0; row < MAXROW; row++)
	{
		for (int col = 0; col < MAXCOL; col++)
			delete nMap[Node::blockNumber(row, col)];
	}
	/*
	Since the calculated path is opposite to the path we need. we will reverse it and get the right path
	*/
	reverse(path);
	return path;
}

#endif
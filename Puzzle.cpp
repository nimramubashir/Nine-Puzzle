# include <iostream>
# include <string>
using namespace std;

int ** goal ; 
int ** input ;

void initialize_goal ()
{
		goal = new int* [3];
		input = new int* [3];
		
		for (int i = 0,k = 1 ; i < 3 ; i ++)
		{
			goal[i] = new int [3];
			input[i] = new int [3];
			for (int j = 0 ; j < 3 ; j ++,k++)
			{
				goal[i][j] = k;
				input[i][j] = 0;
			}
		}
		
		goal[2][2] = -1 ; 
}

void print(int ** temp)
{
		for (int i = 0; i < 3 ; i ++)
		{
			for (int j = 0 ; j < 3 ; j ++)
			{
				cout << temp[i][j] << " " ;
			}
			cout << " " ;
		}
}

bool match ( int ** ptr , int ** res)
{
	int counter = 0 ; 
	for (int i = 0 ; i < 3 ; i ++)
	{
		for (int j = 0 ; j < 3 ; j ++)
		{
				if (ptr[i][j]==res[i][j])
					counter ++;
		}
	}
	
	if (counter  == 9)
		return true ;
	else
		return false ; 
}

void enter_values ()
{
		
		for (int i = 0 ; i < 3 ; i ++)
		{
				for (int j = 0 ; j < 3 ; j ++)
				{
					cin >> input[i][j] ; 
				}
		}
}

struct Node
{
	int** data;
	Node *next;
};

class LinkedList
{
	Node*head;
	Node*tail;
public:
	void init()
	{
		head = NULL;
		tail = NULL;
	}

	void create_node (int ** & temp , int ** parent)
	{
		temp = new int *[3];
		for (int i = 0 ; i < 3 ; i ++)
		{
			temp[i] = new int [3];
			for (int j = 0 ; j < 3 ; j ++)
			{
				temp[i][j] = parent[i][j];
			}
		}
	}
	void addNode(int** & val)
	{
		if (head == NULL && tail == NULL)
		{
			Node *newNode;
			newNode = new Node;
			create_node(newNode->data ,val );
			newNode->next = NULL;
			head = newNode;
			tail = newNode;
		}

		else
		{
			Node *newNode;
			newNode = new Node;
			create_node(newNode->data ,val );
			newNode->next = NULL;
			tail->next = newNode;
			tail = newNode;
		}
	}

	void display()
	{
		Node *temp = head;
		if (head == NULL)
		{
			cout << "Linked list is empty" << endl;
		}

		else
		{
			int count  = 0 ; 
			while (1)
			{
				for (int i = 0 ; i < 3 ; i ++)
				{
					for (int j = 0 ; j < 3 ; j ++)
					{
						cout << temp->data[i][j] << endl;
					}
				}
				
				temp = temp->next;
				if (temp == NULL)
					break;
			}
		}
	}

	int count()
	{
		int count = 0;
		Node *temp = head;
		if (head == NULL)
		{
			return 0;
		}

		else
		{
			while (1)
			{
				count++;
				temp = temp->next;
				if (temp == NULL)
					break;
			}
		}
		return count;
	}
	
	int ** &find_and_return (int count)
	{
		Node * temp = head ; 
		for (int i = 1 ; i < count ; i ++)
		{
			temp = temp -> next ; 
		}
		
		return  temp -> data ; 
	}

	int **  deleteFromHead()
	{
		if (head == NULL)
		{
			cout << "Linked List is Empty" << endl;
		}

		else if (head == tail)
		{
			Node *temp = head;
			head = NULL;
			tail = NULL;
			return  temp-> data;
		}
		else
		{
			cout << " in delete from head" << endl ; 
			Node *temp = head;
			head = temp->next;
			return  temp-> data;
		}
	
	}

};

bool find_if_explored (LinkedList & explored , int ** & temp)
{
	
	int count = explored.count () ; 
	int ** child ;
	cout << "in explored and count.Count is:" << count <<  endl; 
	for (int i = 1 ; i <= count ; i ++)
	{
			child = explored.find_and_return (count);
			if (match (child,temp) == true)
				return true ; 
	}
	return false ; 
}

void create_node_copy (int ** & temp , int ** & parent)
{
	temp = new int *[3];
	for (int i = 0 ; i < 3 ; i ++)
	{
		temp[i] = new int [3];
		for (int j = 0 ; j < 3 ; j ++)
		{
			temp[i][j] = parent[i][j];
		}
	}
}
void generate_child (LinkedList & frontier , LinkedList & explored , int ** & temp)
{
	int i , j = 0 ; 
		for (int a = 0 ; a < 3 ; a ++)
		{
			for (int b = 0 ; b < 3 ; b ++)
			{
					if (temp[a][b] == -1)
					{
						i = a , j = b ; 
					}
			}
		}
		
		cout << " i & j are:" << i << " " << j << endl ; 
		for (int a = 0 ; a  < 4 ; a++)
		{
			int swap = 0 ; 
			// iteration to produce a child by moving blank upwards
			if (a == 0)
			{
				if (i != 0)
				{
					int ** upward ; 
					cout << "upward" << endl ; 
					create_node_copy (upward,temp);
					swap = upward[i][j]; 
					upward[i][j] = upward[i-1][j];
					upward[i-1][j] = swap;
					cout << upward [1][1] << " yayy" << endl ; 
					bool result = find_if_explored (explored,upward);
					if (result == false)
						frontier.addNode(upward);
				}
			}
			
			// iteration to produce a child by moving blank downwards
			if (a == 1)
			{
				if (i != 2)
				{
					int ** down ; 
						cout << "down" << endl ; 
					create_node_copy (down,temp);
					swap = down[i][j]; 
					down[i][j] = down[i+1][j];
					down[i+1][j] = swap;
				
				bool result = find_if_explored (explored,down);
				if (result == false)
					frontier.addNode(down);
				}
			}
			
			// iteration to produce a child by moving blank left
			if (a == 2)
			{
				cout << " Second" << endl ; 
				if (j != 0)
				{
					int ** left ; 
						cout << "left" << endl ; 
					create_node_copy (left,temp);
					swap = left[i][j-1]; 
					left[i][j-1] = left[i][j];
					left[i][j] = swap;
				
					bool result = find_if_explored (explored,left);
					if (result == false)
						frontier.addNode(left);
				}
			}
			
			// iteration to produce a child by moving blank right
			if (a == 3)
			{
				if (j != 2)
				{
					int ** right ; 
						cout << "right" << endl ; 
					create_node_copy (right,temp);
					swap = right[i][j+1]; 
					right[i][j+1] = right[i][j];
					right[i][j] = swap;
					bool result = find_if_explored (explored,right);
					if (result == false)
						frontier.addNode(right);
				}
			}
		}
}
int main ()
{
	initialize_goal ();
	cout << " Enter the values of the puzzle.For blank tile please use -1: " ; 
	enter_values ();
	bool result = match(input , goal) ; 
	if (result == true)
		cout << "it is a goal state \n" ; 
	else
	{
		cout << " it isn't a goal state \n" ; 
		cout << " Finding the solution. "<< endl ; 
		cout << " Please Wait... " << endl ; 
		LinkedList frontier ; 
		LinkedList explored ; 
		frontier.init();
		explored.init() ; 
		frontier.addNode(input);
		int ** temp ; 
		int ** address ; 
		while (1)
		{
			if (frontier.count() == 0 )
			{
				cout << " We are unable to find the solution sorry" ; 
				return 0 ; 
			}
			else
			{
				cout << " in else" << endl ; 
			//	cout << " count is:" << frontier.count() << endl ; 
				address = frontier.deleteFromHead ();
				create_node_copy(temp,address);
				result = match(temp,goal) ; 
				if (result == true)
				{
					cout << "Goal state Found \n" ; 
					print(temp);
					return 0 ; 
				}
				else
				{
					cout << " Going to generate the childs" << endl ; 
					explored.addNode(temp);
					generate_child(frontier , explored , temp);
				}
			}
		}
	}
	return 0 ; 
}



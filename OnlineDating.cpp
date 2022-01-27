#include <iostream>
#include "OnlineDating.h"
using namespace std;

OnlineDating::Node::Node() //default constructor
{}

OnlineDating::Node::Node(string firstName, string lastName, OnlineType value): first_name(firstName), last_name(lastName), m_value(value) //constructor
{}

OnlineDating::OnlineDating()
{
    head = new Node;
    head->next = head;
    head -> prev = head;
    m_size = 0;
}//Here we created an empty list

OnlineDating::~OnlineDating(){//destructor
    Node* n = head;
    for (int i =0; i != m_size; i++)
    {
        Node* temp = n;
        n = n->next;
        delete temp;
        //We delete everything but the last node
    }
    delete n; //and here we delete the last node
    
}

OnlineDating::OnlineDating(const OnlineDating& other) //Copy Constructor
{
    head = new Node;
    head->next = head;
    head -> prev = head;
    m_size = 0;
    Node* n = head;
    Node* prevnode = head;
    Node* copy = other.head -> next;
    for (int i = 0; i < other.howManyMatches(); i++)
    {
        Node* newNode = new Node(copy -> first_name, copy -> last_name, copy->m_value);
        n->next = newNode;
        n->prev = prevnode;
        newNode -> next = head;
        newNode -> prev = n;
        copy = copy -> next;
        prevnode = n;
        n = n->next;
        m_size++;
    }
}

OnlineDating& OnlineDating:: operator=(const OnlineDating &other)//assignment operator
{
    if (this == &other)
        return *this;
    
    OnlineDating copylist(other);
    tradeMatches(copylist);
    return *this;
    
}

bool OnlineDating::noMatches() const{// We check if the size of the list is zero if so we return true
    if (m_size == 0)
        return true;
        return false;
}

int OnlineDating::howManyMatches() const//We just return m_size to see the size of the list
{
    return m_size;
}

bool OnlineDating::makeMatch(const string &firstName, const string &lastName, const OnlineType &value)//Here we are adding to the list, we first check if the name exist if it does we return false. If the name is not on the list we create a new Node and add the name
{
    Node* n = head -> next;
        for (; n!=head; n = n-> next)
        {
            if (firstName == n-> first_name && lastName == n -> last_name) //we check if the name exists
                return false;
            else if (lastName == n->last_name)
            {
                if (firstName < n->first_name)
                break;
            }
            else if (lastName < n->last_name)
                break;
            //We sort it based on last name but if the last name is the same as one in the list we sort by first name
        }
        
        Node* newNode = new Node(firstName, lastName, value);
        newNode -> next = n;
        newNode -> prev = n-> prev;
        n -> prev -> next = newNode;
        n -> prev = newNode;
        m_size++;
        
        return true;
}

bool OnlineDating::transformMatch(const string& firstName, const string& lastName, const OnlineType& value)
//Here we want to change a name on the list,
//to change a name we have to make sure the name exists if it exist then we change the value
{
    Node* n = head -> next;
    for (; n!=head; n = n-> next)
        {
            if (firstName == n-> first_name && lastName == n -> last_name)
            {
                n->m_value = value;
                return true;
            }
        }
        return false;
}

bool OnlineDating::makeOrTransform(const string& firstName, const string& lastName, const OnlineType& value)//To check if we need to add a name or just change the name we first must check if it exists. If that is the case then we change the name and value
{
    if(transformMatch(firstName, lastName, value))
        transformMatch(firstName, lastName, value);
       else
           makeMatch(firstName, lastName, value);

        return true;
}

bool OnlineDating::blockPreviousMatch(const string& firstName, const string& lastName)//remove
{//We use this function to remove a name from the list, like the other function before we can alter a value from the list we must check that is exists
    for (Node* n = head -> next; n!=head; n = n-> next)
         if (firstName == n-> first_name && lastName == n -> last_name)
         {
             Node* temp = n;
             n -> prev -> next = n-> next;
             n->next->prev = n->prev;
             delete temp;
             m_size--; //After delete the node and make the list smaller
             return true;
         }
     return false;
}
bool OnlineDating::someoneAmongMatches(const string& firstName, const string& lastName) const
{//Here we search up the name by checking if the name is in the list. if so return true
    for (Node* n = head -> next; n!=head; n = n-> next)
         if (firstName == n-> first_name && lastName == n -> last_name)
         {
             return true;
         }
     return false;
}

bool OnlineDating::lookAtMatches(const string& firstName, const string& lastName, OnlineType& value) const
{
    for (Node* n = head -> next; n!=head; n = n-> next)
        if (firstName == n-> first_name && lastName == n -> last_name)
        {
            value = n-> m_value;
            return true;
        }
    return false;
}

bool OnlineDating::confirmMatch(int i, string& firstName, string& lastName, OnlineType& value) const//get
{
    if (i >= howManyMatches() || i<0)
        return false;//We check if the user is trying to access something outside of the list if so return false
   
    int count = 0;
    for (Node* n = head -> next; n!=head; n = n-> next)
    {//If it is in the list we go through the list and store the value at that position
        if (i == count)
        {
            firstName = n->first_name;
            lastName = n-> last_name;
            value = n->m_value;
        }
        count++;
    }
    return true;
}

void OnlineDating::tradeMatches(OnlineDating& other)//tradeMatches is just a basic swap function
{
    swap(head, other.head);
    swap(m_size, other.m_size);
}

bool mergeMatches(const OnlineDating& odOne, const OnlineDating& odTwo, OnlineDating& odResult){
    OnlineDating mergedList;
    string odOnefirst;
    string odOnelast;
    string odTwofirst;
    string odTwolast;
    OnlineType odOnevalue;
    OnlineType odTwovalue;
    bool returnbool = true;
        //What I did was loop through both lists first through odTwo and see if any in that list didnt match odOne. Any that didnt match would be added to a new list
        //Next I loop through odOne and  see if any in that list didnt match odTwo. Any that didnt match would be added to a new list.
        for (int n = 0; n < odTwo.howManyMatches(); n++)
        {
            odTwo.confirmMatch(n, odTwofirst, odTwolast, odTwovalue);
            if (!odOne.someoneAmongMatches(odTwofirst, odTwolast))
                mergedList.makeMatch(odTwofirst, odTwolast, odTwovalue);
        }
        
        for (int n = 0; n < odOne.howManyMatches(); n++)
        {
            odOne.confirmMatch(n, odOnefirst, odOnelast, odOnevalue);
            if (!odTwo.someoneAmongMatches(odOnefirst, odOnelast))
                mergedList.makeMatch(odOnefirst, odOnelast, odOnevalue);
            else if (odTwo.someoneAmongMatches(odOnefirst, odOnelast))
            {
                odTwo.lookAtMatches(odOnefirst, odOnelast, odTwovalue);
                if(odTwovalue != odOnevalue)
                {
                    returnbool = false;
                }
                else if (odTwovalue == odOnevalue)
                {
                    mergedList.makeMatch(odOnefirst, odOnelast, odOnevalue);
                }
            }
        }
        
        odResult.tradeMatches(mergedList);
        return returnbool;
    
}
void authenticateMatches(const string& fsearch, const string& lsearch, const OnlineDating& odOne, OnlineDating& odResult)
{//What I did was check if fsearch and lsearch = *
    //if so we copy all the values
    //then I made two else if function, one if only fsearch = * and one if only lsearch = *, if the first name corresponds to either we add to the new mergedList
    OnlineDating mergedList;
    string odOnefirst;
    string odOnelast;
    OnlineType odOnevalue;
    if (fsearch == "*" && lsearch == "*")
        mergedList = odOne;
        else if (fsearch == "*")
        {
            for (int n = 0; n < odOne.howManyMatches(); n++)
            {
                odOne.confirmMatch(n, odOnefirst, odOnelast, odOnevalue);
                if (lsearch == odOnelast)
                    mergedList.makeMatch(odOnefirst, odOnelast, odOnevalue);
            }
        }
        
        else if (lsearch == "*")
        {
            for (int n = 0; n < odOne.howManyMatches(); n++)
            {
                odOne.confirmMatch(n, odOnefirst, odOnelast, odOnevalue);
                if (fsearch == odOnefirst)
                    mergedList.makeMatch(odOnefirst, odOnelast, odOnevalue);
            }
        }
        
        else //if neither searches are "*" then we check if the
        {
            for (int n = 0; n < odOne.howManyMatches(); n++) //loop through list first and last names correspond, if they do we add them to the mergedList
            {
                odOne.confirmMatch(n, odOnefirst, odOnelast, odOnevalue); //for each entry in p1
                if (lsearch == odOnelast && fsearch == odOnefirst) //check if both first and last names correspond
                    mergedList.makeMatch(odOnefirst, odOnelast, odOnevalue); //then add to result
            }
        }
        odResult.tradeMatches(mergedList);
}

void OnlineDating::dump() const
{
    for (Node* p = head -> next; p != head; p = p-> next)
            cerr<< p->last_name << p->first_name << p->m_value << endl;
}

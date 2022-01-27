#ifndef OnlineDating_h
#define OnlineDating_h
#include <iostream>
#include <string>

typedef std::string OnlineType;

class OnlineDating
{
private://I have implemented a doubly linked list
    struct Node {
        std::string first_name;
        std::string last_name;
        OnlineType m_value;
        Node *next;
        Node *prev;
        Node(std::string firstName, std::string lastName, OnlineType val);
        Node();
    };
    Node *head;
    int m_size;

public:
    OnlineDating();// Create an empty OnlineDatinglist

    ~OnlineDating();//Destructor
    
    OnlineDating(const OnlineDating& other);//Copy Contructor
    
    OnlineDating& operator=(const OnlineDating& other); //Assingment operator
    
    bool noMatches() const;  // Return true if the OnlineDatinglist
    // is empty, otherwise false.
    
    int howManyMatches() const;  // Return the number of matches
    // on the OnlineDatinglist.
    
    bool makeMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value);
        // If the full name (both the first and last name) is not equal
    // to any full name currently in the list then add it and return
    // true. Elements should be added according to their last name.
    // Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and
    // return false (indicating that the name is already in the // list).
    bool transformMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value);
    // If the full name is equal to a full name currently in the
    // list, then make that full name no longer map to the value it
    // currently maps to, but instead map to the value of the third
    // parameter; return true in this case. Otherwise, make no
    // change to the list and return false.
    bool makeOrTransform(const std::string& firstName, const std::string& lastName, const OnlineType& value);
    // If full name is equal to a name currently in the list, then
    // make that full name no longer map to the value it currently
    // maps to, but instead map to the value of the third parameter;
    // return true in this case. If the full name is not equal to
    // any full name currently in the list then add it and return
    // true. In fact,this function always returns true.
    bool blockPreviousMatch(const std::string& firstName, const std::string& lastName);
    // If the full name is equal to a full name currently in the
    // list, remove the full name and value from the list and return
    // true.  Otherwise, make no change to the list and return
    // false.
    bool someoneAmongMatches(const std::string& firstName, const std::string& lastName) const;
    // Return true if the full name is equal to a full name
    // currently in the list, otherwise false.
    bool lookAtMatches(const std::string& firstName, const std::string& lastName, OnlineType& value) const;
    // If the full name is equal to a full name currently in the
    // list, set value to the value in the list that that full name
    // maps to, and return true.  Otherwise, make no change to the
    // value parameter of this function and return false.
    bool confirmMatch(int i, std::string& firstName, std::string& lastName, OnlineType& value) const;
    // If 0 <= i < howManyMatches(), copy into firstName, lastName
    // and value parameters the corresponding information of the
    // element at position iin the list and return true.
    // Otherwise, leave the parameters unchanged and return false.
    // (See below for details about this function.)
    void tradeMatches(OnlineDating& other);// Exchange the contents of this list with the other one.};

    void dump() const;
  
};
bool mergeMatches(const OnlineDating& odOne, const OnlineDating& odTwo, OnlineDating& odResult);
void authenticateMatches(const std::string& fsearch, const std::string& lsearch, const OnlineDating& odOne, OnlineDating& odResult);

#endif /* OnlineDating_h */

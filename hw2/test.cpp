#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
    if (list->empty() == expEmpty) {
        cout << "SUCCESS: List is ";
        if (!expEmpty) cout << "not ";
        cout << "empty" << endl;
    }
    else {
        cout << "FAIL: List is ";
        if (expEmpty) cout << "not ";
        cout << "empty" << endl;
    }
}

void checkSize(LListStr *list, int expSize) {
    int size = list->size();
    if (size == expSize) {
        cout << "SUCCESS: List has size " << size << endl;
    }
    else {
        cout << "FAIL: List has size " << size;
        cout << " but expected " << expSize << endl;
    }
}

void checkGet(LListStr *list, int pos, const string &expStr) {
    string str = list->get(pos);
    if (str == expStr) {
        cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
    } 
    else {
        cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
        cout << " but expected \'" << expStr << "\'" << endl;
    }
}

int main()
{
    LListStr* list = new LListStr();

    // Check if the list is initially empty.
    checkEmpty(list, true);
    checkSize(list, 0);

    // Insert an item at the head.
    list->insert(0, "CSCI104");

    // Verify the list is not empty
    checkEmpty(list, false);
    checkSize(list, 1);

    // Check if the value is correct.
    checkGet(list, 0, "CSCI104");

    // TODO: Continue adding tests for your program, or start your own file with your
    // own tests. Remember to submit a file that is named correctly!
    
    //When the list is empty
    list->remove(0);
    checkEmpty(list,true);

    list->insert(74, "Hello World");
    checkEmpty(list, true);
    checkGet(list, 0, "");

    list->remove(74);
    checkEmpty(list,true);

    //Inserting all cases
    list->insert(0, "Tommy Trojan");
    list->insert(1, "Sam Darnold");
    list->insert(2, "Lio Messi");
    list->insert(3, "Lebron James");
    checkSize(list, 4);

    list->insert(0, "Christiano Ronaldo");
    checkSize(list, 5);

    list->insert(2, "David De Gea");
    checkSize(list, 6);

    checkGet(list,1, "Tommy Trojan");

    //Set Function
    list->set(1, "Gareth Bale");
    checkGet(list,1,"Gareth Bale");

    //Removing all cases
    list->remove(3);
    list->remove(0);
    list->remove(2);

    checkSize(list,3);

    // Clean up memory.
    delete list;
}
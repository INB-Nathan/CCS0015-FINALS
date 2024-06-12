#include <iostream>
#include <list>
#include <string>
#include <stack>
using namespace std;

struct Characters { // Similar to a Node struct. In charge of creating places in the list where the data can be placed
    string braces; // Data that it passed and placed in a location in the heap memory, basically the value for address in the list
};


int main () {
    stack<Characters, list<Characters>> curly; // Creating the list template using STL
    int closeCount= 0, openCount=0, req=0, strLength; // Counters, setting the three to 0 so by default their value will always be zero
    string bracesHolder; /* Holder for the string Braces inputted by the user and can be manipulated before passing
                         to the actual braces variable in struct*/
    Characters character; // Object of struct to call the struct and things declared in struct

    while (true) { // loop just to test continuously
        
        cout << "\nEnter a string of braces: ";
        getline(cin, bracesHolder);

        strLength = bracesHolder.length(); // Getting length of the inputted string by the user

        for (int i=0; i < strLength; i++) { 
            char ch = bracesHolder[i]; // Loops through each character in the string inputted by the user
            character.braces = ch; // Sets the character that got looped through to the string braces variable in Character struct
                                   // Used type conversion to make the character data type converted to string and accepted by braces variable

            curly.push(character); // Pushes or adds the character into the list before going to the next iteration
            /*  The characters extracted from the actual string inputted by the user is treated as brace = "}" / braces = "{"
                as it gets pushed in the list */
        }

        while (!curly.empty()) { // becomes true if the list is empty
        character = curly.top(); // similar to current = current->head; when traversing linked list needs to be declared to have a starting point 
        if (character.braces == "{") { // checks if the current position's value is open curly
            openCount++; // adds to the open count if it's the case
            curly.pop(); // pops after counting to delete from the list
        }
        else if (character.braces == "}"){ // checks if the current position's value is close curly
            closeCount++; // adds to the close count if it's the case
            curly.pop(); // pops after counting to delete from the list
        }
    }

    // To avoid a negative number as result, made conditions to make sure it will always be the larger number first
    if (openCount < closeCount) {
        req = closeCount - openCount;
    }
    else {
    req = openCount - closeCount;
    }
    cout << "Minimum number of replacements: " << req;
    // after printing out the number of replacements declare back the counters to 0 to reset for the next input
    req = 0;
    openCount = 0;
    closeCount = 0;
    }
}
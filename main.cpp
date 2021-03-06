#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

#include "ShipGirl.h"
#include "Dock.h"

// double avg(const vector<ShipGirl>& values) {
//     double count = 0, sum = 0;
//     for (int i = 0; i < values.size(); i++) {
//         sum += values.at(i);
//         count++;
//     }
//     return (sum / count); 
// }

// double standardDeviation(const vector<ShipGirl>& values) {
//     double numer = 0;
//     double average = avg(values);
//     double denom = values.size() - 1;
    
//     for (int i = 0; i < values.size(); i++) {
//         numer += pow(average - values.at(i), 2);
//     }
    
//     return (numer / denom);
// }

// void recommendBuckets(vector<ShipGirl> & v) {
//     double avg()
// }

void printList(const vector<ShipGirl>& dock) {
    if (dock.empty()) {
        cout << "Nothing" << endl;
        return;
    }
    for (int i = 0; i < dock.size(); i++) {
        dock.at(i).display();
    }
    
    return;
}

int calculateSeconds(int hours, int minutes, int seconds) {
    int total = 0;
    
    total += hours * 3600;
    total += minutes * 60;
    total += seconds;
    
    return total;
}

int main() {
    ifstream filestream;
    stringstream currentLine;
    stringstream relevant;
    string firstLine, secondLine, ship;
    vector<ShipGirl> shipList;
    char lastChar = '~';
    int repair = 0, hours = 0, minutes = 0, seconds = 0, dockSize = 0;
	string fileName;
	int pause;

    cout << "Welcome to the kantai repair calculator, please type the name of your txt file: ";
	cin >> fileName;
	cout << endl;
	
	if (fileName.find(".") == string::npos) {
	    fileName += ".txt";
	} else if (fileName.substr(fileName.find_last_of(".") + 1) != "txt") {
	    cout << "Invalid file type!";
	    return 0;
	}
    
    filestream.open(fileName.c_str());
    if (!filestream.is_open()) {
        cout << "There was an error loading your file or it does not exist." << endl;
		cin >> pause;
        return -1;
    }
	char firstChar = filestream.peek();
	while (firstChar < 48 || firstChar > 57) {
		filestream.ignore(50, '\n');
		firstChar = filestream.peek();
	}
    
    while (getline(filestream, firstLine)) {
        //cout << firstLine << endl;
        currentLine << firstLine;
        
        while (1==1) {
            char temp = currentLine.get();
            /*
            order of checking:
            ship class - if ship class, then break
            if last character does not follow into next character, add old one
            if number, skip
            if none, continue
            */
            
            if (lastChar == 'C' && temp == 'V') {
                break;
            } else if (lastChar == 'C' && temp == 'A') {
                break;
            } else if (lastChar == 'C' && temp == 'L') {
                break;
            } else if (lastChar == 'C' && temp == 'T') {
                break;
            } else if (lastChar == 'D' && temp == 'D') {
                break;
            } else if (lastChar == 'H' && temp == 'A') {
                break;
            } else if (lastChar == 'B' && temp == 'B') {
                break;
            } else if (lastChar == 'S' && temp == 'S') {
                break;
            } else if (lastChar == 'A' && temp == 'V') {
                break;
            } else if (lastChar == 'A' && temp == 'S') {
                break;
            } else if (lastChar == 'A' && temp == 'O') {
                break;
            } else if (lastChar == 'A' && temp == 'R') {
                break;
            } else if (lastChar == 'A') {
                relevant << 'A';
            } else if (lastChar == 'S') {
                relevant << 'S';
            } else if (lastChar == 'B') {
                relevant << 'B';
            } else if (lastChar == 'H') {
                relevant << 'H';
            } else if (lastChar == 'D') {
                relevant << 'D';
            } else if (lastChar == 'C') {
                relevant << 'C';
            }
            
            lastChar = '~';
            
            if (temp == 'C') {
                lastChar = temp;
            } else if (temp == 'D') {
                lastChar = temp;
            } else if (temp == 'H') {
                lastChar = temp;
            } else if (temp == 'B') {
                lastChar = temp;
            } else if (temp == 'S') {
                lastChar = temp;
            } else if (temp == 'A') {
                lastChar = temp;
            } else if (temp > 47 && temp < 58) {
                lastChar = temp;
            } else {
                relevant << temp;
            }
            
        }
        lastChar = '~';
        
        ship = relevant.str();
        
        relevant.str("");
        currentLine.str("");
        
        getline(filestream, secondLine);
        
        int colonIndex = secondLine.find(":");
        
        hours = atoi((secondLine.substr(0, colonIndex)).c_str());
        minutes = atoi((secondLine.substr(colonIndex + 1, 2)).c_str());
        seconds = atoi((secondLine.substr(colonIndex + 4, 2)).c_str());
        
        repair = calculateSeconds(hours, minutes, seconds);
        
        shipList.push_back(ShipGirl(repair, ship));
    }
    
    if (shipList.empty()) {
        cout << "File loaded, but empty file." << endl;
        cin.get();
        return 0;
    }
    
    cout << "File loaded." << endl;
    
    cout << "Dock size: ";
    while (cin >> dockSize) {
        if (dockSize == 2 || dockSize == 3 || dockSize == 4) {
            break;
        }
        cout << endl << "Invalid number of docks, please type '2', '3', or '4'" << endl;
    }
// 	if (dockSize == 4) {
// 		cout << "4 docks are a work in progress." << endl;
// 		cin.get();
// 		return 0;
// 	}

    cout << endl;
    
    printList(shipList);
    
    //recommend buckets
    
    Dock repairDocks(shipList);
    Dock bucketedDocks(shipList);
    
    if (dockSize == 2) {
        repairDocks.checkTwoDocks();
        repairDocks.printDocks(2);
        vector<ShipGirl> bucketList = bucketedDocks.recommendBuckets();
        cout << endl << "Recommended buckets: " << endl;
        printList(bucketList);
        bucketedDocks.checkTwoDocks();
        bucketedDocks.printDocks(2);
    } else if (dockSize == 3) {
        repairDocks.checkThreeDocks();
        repairDocks.printDocks(3);
        vector<ShipGirl> bucketList = bucketedDocks.recommendBuckets();
        cout << endl << "Recommended buckets: " << endl;
        printList(bucketList);
        bucketedDocks.checkTwoDocks();
        bucketedDocks.printDocks(3);
    } else {
        repairDocks.checkFourDocks();
        repairDocks.printDocks(4);
        vector<ShipGirl> bucketList = bucketedDocks.recommendBuckets();
        cout << endl << "Recommended buckets: " << endl;
        printList(bucketList);
        bucketedDocks.checkTwoDocks();
        bucketedDocks.printDocks(4);
    }

	cin >> pause;
    
    return 0;
}
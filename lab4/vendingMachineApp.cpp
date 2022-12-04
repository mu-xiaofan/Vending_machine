/*
*Xiaofan Mu
*Description: Lab4 CS113
*This program can be used for vending machines in order to help users make selections using the truth table and warning the users while their input is not proper or the product they selected is out of stock. The technician can also use a special input in order to going to the setting of this vending machine. This can help the technician add new beverage, remove a beverage, and update beverage price.
*Instructor: Professor Pham
*Date:March 16
*Name of the file: vendingMachinApp.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

bool usedLocationOfTruthTable[8] = {1,0,0,0,1,0,0,1};//the set of boolean variables that indicate whether there is product matches the location of this index of the truth table
bool C1, C2, C3; //the boolean variables used for truth table
bool O = 0;//initialize the O to false
bool truetable[8][3] =  //the truth table
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};
double p1 = 1.5; //set prices of the drinks
double p2 = 0;
double p3 = 0;
double p4 = 0;
double p5 = 1.75;
double p6 = 0;
double p7 = 0;
double p8 = 1;

string b1 = "Coke";//set the name of the drinks
string b2 = "";
string b3 = "";
string b4 = "";
string b5 = "Pepsi";
string b6 = "";
string b7 = "";
string b8 = "Water";

int s1 = 2;  //set the amount of drinks in stock
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 3;
int s6 = 0;
int s7 = 0;
int s8 = 4;

string c1 = "A1";   //set the choices in order to match user's input
string c2 = "A2";   // those are reserved for changing the selection pairs later
string c3 = "A3";
string c4 = "B1";
string c5 = "B2";
string c6 = "C1";
string c7 = "C2";
string c8 = "C3";

int numberOfProduct = 3;//we only have coke, pepsi, and water by now

double priceList[8] = {p1,p2,p3,p4,p5,p6,p7,p8};//the list of price
string beverageList[8] = {b1,b2,b3,b4,b5,b6,b7,b8};//the list of the name of the beverages
int stockList[8] = {s1,s2,s3,s4,s5,s6,s7,s8};//the list of the stock of the beverages
string choiceList[8] = {c1,c2,c3,c4,c5,c6,c7,c8};//the list of valid input

void menu();//the function for presenting the list of valid beverages
void technicianMenu();//the function for presenting the menu for settings
void truthTable(string choice);//the function uses truth table to determine whether user's input is valid and match the correct name of beverage and its price and stock.
void makeMoney();//the function find out the price of the beverage that user chose and then lets users insert money and then calculate the change
string askSlection();//the function asks user for input

void decimalToBinary(int dec, int *binary, int counter);//the function that convert a decimal to binary
//the function that
bool convertInputTo8DigitalInput(string keypad, int *binary1, int *binary2, int *binary3, int *binary4, int *binary5);
void convertPriceInformationToBinary(string information);

using namespace std;

int main()//driver
{
    do{          //Loop to run the vendingmachine continuesly
        string selection = "";//initialize it to empty string
        int charInput[8] = {0,0,0,0,0,0,0,0};
        int numInput[8] = {0,0,0,0,0,0,0,0};
        int backUp1[8] = {0,0,0,0,0,0,0,0};
        int backUp2[8] = {0,0,0,0,0,0,0,0};
        int backUp3[8] = {0,0,0,0,0,0,0,0};
        O = 0;//reset the value of O
        menu();//open the main menu
        selection = askSlection();//take user's selection of beverages
        bool technicianMenue = convertInputTo8DigitalInput(selection, charInput, numInput, backUp1, backUp2, backUp3);
        cout << "According to the user's selection, the corresponding binary numbers are: " << endl;
        if (technicianMenue)//if the input is 0000#
        {
            //print out every elment (the corresponding binary numbers) inside those arrays
            for(int i = 0; i < 8; i++)
            {
                cout << charInput[i];
            }
            cout << endl;
            
            for(int i = 0; i < 8; i++)
            {
                cout << numInput[i];
            }
            cout << endl;
            
            for(int i = 0; i < 8; i++)
            {
                cout << backUp1[i];
            }
            cout << endl;
            
            for(int i = 0; i < 8; i++)
            {
                cout << backUp2[i];
            }
            cout << endl;
            
            for(int i = 0; i < 8; i++)
            {
                cout << backUp3[i];
            }
            cout << endl;
            
        }
        else//if the input pair is not 0000#
        {
            //print out every elment (the corresponding binary numbers) inside those arrays
            for(int i = 0; i < 8; i++)
            {
                cout << charInput[i];
            }
            cout << endl;
            
            for(int i = 0; i < 8; i++)
            {
                cout << numInput[i];
            }
            cout << endl;
        }
        truthTable(selection);//use truth table to handle user's selection. Use the truth table to check whether the user's selection is valid first and then match the proper beverage.

        makeMoney();//call the change function to let users insert money and then calculate the change

        cout << endl;//formatting
        
    }while(true);//reserved condition, can be changed later in order to have more options

    return 0;
}


/*
The function that prints the list of the valid beverages by using the for loop and if statement.
*/
void menu()
{
    cout << endl;//formatting
    cout << "Please enter a letter and a number to select a drink:" << endl << endl;
    for(int i = 0; i < 8; i++)//use the for loop to print the list of valid beverages
    {
        if(usedLocationOfTruthTable[i])//if that location stores a kind of beverage
        {//then print it out
            cout << "Enter " << choiceList[i] << " for:  " << beverageList[i] << "   " << fixed << setprecision(2) << priceList[i] << " Stock: " << stockList[i] << endl;
            //cout << "Enter " << choiceList[i] << " for:  " << beverageList[i] << "   " << priceList[i] << " Stock: " << stockList[i] << endl;
        }
    }
}

/*
The askSlection function asks user for input and then check whether the input is proper(the pair of a valid character and an integer) by comparing the input with the set of the valid input
*/
string askSlection(){
    string s;
    cout << "Please enter your selection now:  ";
    cin >> s;
    while (cin.fail()|| (s != choiceList[0] & s != choiceList[1] & s != choiceList[2] & s != choiceList[3] & s != choiceList[4] & s != choiceList[5] & s != choiceList[6] & s != choiceList[7] & s != "0000#"))//check whether the data type doesn't match or whether the user's input doesn't match any element in the set of valid input
    {//let the user enter the selection again while it is invalid
        cin.clear();
        cin.ignore(1024,'\n');
        cout << "Invalid input, Please try again: ";
        cin >> s;
    }

    return s;
}


/*
The function truthTable check whether the user's input is valid and then find out the value of O. It also shows user the name and the price of the beverage that user chose. Finally, it will also subtract the stock of the corresponding beverages.
*/
void truthTable(string choice)
{
    string remover = "";
    if(choice == choiceList[0] && usedLocationOfTruthTable[0])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[0] > 0){ //check whether the beverage is in stock
            cout << "The price： "<< beverageList[0] <<" $" << fixed << setprecision(2) << priceList[0] << endl;
            remover = to_string(priceList[0]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[0] + " $" + remover;
            int check = priceList[0];
            if (check == priceList[0])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 0;
            C2 = 0;
            C3 = 0;
            O = 1;
            stockList[0]--;//reduce the stock
        }
        else{
        cout << "Sorry, we are running out of stock." << endl;
        O = 0;
        }
    }
    else if(choice == choiceList[1] && usedLocationOfTruthTable[1])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[1] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[1] <<" is $" << fixed << setprecision(2) << priceList[1] << endl;
            
            remover = to_string(priceList[1]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[1] + " $" + remover;
            int check = priceList[1];
            if (check == priceList[1])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 0;
            C2 = 0;
            C3 = 1;
            O = 1;
            stockList[1]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == choiceList[2] && usedLocationOfTruthTable[2])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[2] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[2] <<" is $" << fixed << setprecision(2) << priceList[2] << endl;
            
            remover = to_string(priceList[2]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[2] + " $" + remover;
            int check = priceList[2];
            if (check == priceList[2])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 0;
            C2 = 1;
            C3 = 0;
            O = 1;
            stockList[2]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == choiceList[3] && usedLocationOfTruthTable[3])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[3] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[3] <<" is $" << fixed << setprecision(2) << priceList[3] << endl;
            
            remover = to_string(priceList[3]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[3] + " $" + remover;
            int check = priceList[3];
            if (check == priceList[3])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 0;
            C2 = 1;
            C3 = 1;
            O = 1;
            stockList[3]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == choiceList[4] && usedLocationOfTruthTable[4])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[4] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[4] <<" is $" << fixed << setprecision(2) << priceList[4] << endl;
            
            remover = to_string(priceList[4]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[4] + " $" + remover;
            int check = priceList[4];
            if (check == priceList[4])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 1;
            C2 = 0;
            C3 = 0;
            O = 1;
            stockList[4]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == choiceList[5] && usedLocationOfTruthTable[5])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[5] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[5] <<" is $" << fixed << setprecision(2) << priceList[5] << endl;
            
            
            remover = to_string(priceList[5]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[5] + " $" + remover;
            int check = priceList[5];
            if (check == priceList[5])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 1;
            C2 = 0;
            C3 = 1;
            O = 1;
            stockList[5]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == choiceList[6] && usedLocationOfTruthTable[6])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[6] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[6] <<" is $" << fixed << setprecision(2) << priceList[6] << endl;
            
            remover = to_string(priceList[6]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[6] + " $" + remover;
            int check = priceList[6];
            if (check == priceList[6])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 1;
            C2 = 1;
            C3 = 0;
            O = 1;
            stockList[6]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == choiceList[7] && usedLocationOfTruthTable[7])//check whether there is a valid beverage, which matchs the user's selection, is stored there
    {
        if(stockList[7] > 0){//check whether the beverage is in stock
            cout << "The price of a "<< beverageList[7] <<" is $" << fixed << setprecision(2) << priceList[7] << endl;
            
            remover = to_string(priceList[7]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[7] + " $" + remover;
            int check = priceList[7];
            if (check == priceList[7])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            //Set the boolean variables for this selection
            C1 = 1;
            C2 = 1;
            C3 = 1;
            O = 1;
            stockList[7]--;//reduce the stock
        }
        else{
            cout << "Sorry, we are running out of stock." << endl;
            O = 0;
        }
    }
    else if(choice == "0000#")//if the technician wants to open the settings
    {
        technicianMenu();//call the function technicianMenu to open the menue for settings
    }
    else{//The selection doesn't match any element in the set of valid input
        cout << "Not Available.";       //If choice is not available, this output is shown
        O = 0;
    }
}

void technicianMenu()
{
    int option;//the option that the technician chose
    int index;//the index of the beverage stored in the corresponding location that will be influenced
    double price;//the price of the beverage will be influenced
    int stock;//the stock of the beverage will be influenced
    string name;//the name of the beverage will be influenced
    do{//the menu for technician to adjust settings
        cout << "Hi technician! What do you want to do today: \n";
        //several options
        cout << "Enter 1 to add new beverage\n";
        cout << "Enter 2 to remove a beverage\n";
        cout << "Enter 3 to update beverage price\n";
        cout << "Enter 4 to increase the stock of a beverage\n";
        cout << "Enter 5 to reprogram the valid pair of user's input\n";
        cout << "Enter 6 to exit\n";
        cin >>option;
        while (cin.fail() || (option > 6 || option < 1))//check whether the input is a valid option
        {//while it is not, then let the technician correct it
            cin.clear();
            cin.ignore(1024,'\n');
            cout << "Invalid input, Please try again: ";
            cin >> option;
        }
        string selec = to_string(option);
        cout << "For option " << option <<", ";
        convertPriceInformationToBinary(selec);
        if(option == 1)//if the technician wants to add a new beverage
        {
            if(numberOfProduct == 8)//if the list of beverages has already full
            {
                cout << "Sorry, We are currently selling 8 different products. You have to remove one of them before adding a new product!" << endl;
                break;//exit the technician's menu
            }
            for(int i = 0; i < 8; i++)//prin out the current list of beverages with their index of location
            {
                if(usedLocationOfTruthTable[i])//if there is a kind of beverage stored there
                {//then print out the location, pair of selction, name, price, ans stock of the beverage
                    cout << "Location " << i+1<< ": " << choiceList[i] << ":  " << beverageList[i] << "   " << priceList[i] << " Stock: " << stockList[i] << endl;
                }
            }
            cout << "Please enter the index of the location you want to add a new beverage, valid integer from 1 to 8: ";
            cin >> index;//let user choose the index
            while(cin.fail() || (index > 8 || index < 1) || usedLocationOfTruthTable[index-1])//check whether the index of the location is valid
            {
                cin.clear();
                cin.ignore(1024,'\n');
                if(usedLocationOfTruthTable[index-1])//check whether the location has already been used
                {
                    cout << "This location has already been used! ";//warning
                }
                cout << "Invalid input, Please try again: ";
                cin >> index;//let the technician enter the index again
            }
            string convert = to_string(index);
            cout << "For index " << index <<", ";
            convertPriceInformationToBinary(convert);
            usedLocationOfTruthTable[index-1] = 1;//indicate that this location stores a kind of beverage right now
            numberOfProduct++;//increase the total amount of product that the vending machine is selling
            cout << "Please enter the name of the beverage: " << endl;
            cin.ignore();
            getline(cin, name, '\n');//use getline in order to handle the spaces technician may enter
            beverageList[index-1] = name;//set the name of the beverage in the list
            cout << "Please enter the price of the beverage: ";
            cin >> price;
            priceList[index-1] = price;//set the price of the beverage in the list
            string remover;
            remover = to_string(priceList[index-1]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            string simulate = beverageList[index-1] + " $" + remover;
            int check = priceList[index-1];
            if (check == priceList[index-1])
            {
                simulate = simulate + "0";
            }
            cout << "For " << simulate <<", ";
            convertPriceInformationToBinary(simulate);
            cout << "Please enter the number of this beverage in stock: ";
            cin >> stock;
            stockList[index-1] = stock;//set the stock of the beverage in the list
            simulate = to_string(stockList[index-1]);
            cout << "For stock " << stockList[index-1] <<", ";
            convertPriceInformationToBinary(simulate);
        }
        else if(option == 2)//if the technician wants to remove a beverage
        {
            if(numberOfProduct == 0)//check whether the list of product is empty now
            {
                cout << "Sorry, We are currently selling nothing. You have to add some products before removing anything!" << endl;//waring
                break;//exit the technician's menu
            }
            for(int i = 0; i < 8; i++)//use for loop to print the list of the beverages that are selling
            {
                if(usedLocationOfTruthTable[i])//if there is a beverage stored in this location
                {
                    cout << "Location " << i+1<< ": " << choiceList[i] << ":  " << beverageList[i] << "   " << priceList[i] << " Stock: " << stockList[i] << endl;
                }
            }
            cout << "Please enter the index of the location of the beverage you want to remove, valid integer from 1 to 8: ";
            cin >> index;
            while(cin.fail() || (index > 8 || index < 1) || !usedLocationOfTruthTable[index-1])//check whether the index is valid or not
            {
                cin.clear();
                cin.ignore(1024,'\n');
                if(!usedLocationOfTruthTable[index-1])//check whether the location has already been used
                {
                    cout << "This location has not been used yet! ";//warning
                }
                cout << "Invalid input, Please try again: ";
                cin >> index;
            }
            string convert = to_string(index);
            cout << "For index " << index <<", ";
            convertPriceInformationToBinary(convert);
            beverageList[index-1] = "";//clear the list
            priceList[index-1] = 0.00;//clear the list
            stockList[index-1] = 0;//clear the list
            usedLocationOfTruthTable[index-1] = 0;//indecate that there is no beverage stored in this location
            numberOfProduct--;//reduce the total amount of the product that are selling
        }
        else if(option == 3)//if the technician wants to adjust the price of a beverage
        {
            if(numberOfProduct == 0)//check whether the list of products is empty
            {
                cout << "Sorry, We are currently selling nothing. You have to add some products before adjust the price!" << endl;
                break;//exit the technician's menu
            }
            for(int i = 0; i < 8; i++)//use for loop to print the list of beverages that are selling
            {
                if(usedLocationOfTruthTable[i])//check whether there is a kind of beverage stored in that location
                {//if there is, then peint its information out
                    cout << "Location " << i+1<< ": " << choiceList[i] << ":  " << beverageList[i] << "   " << priceList[i] << " Stock: " << stockList[i] << endl;
                }
            }
            cout << "Please enter the index of the location of the beverage you want to adjust the price(valid integer from 1 to 8): ";
            cin >> index;
            while(cin.fail() || (index > 8 || index < 1) || !usedLocationOfTruthTable[index-1])//check whether the index is valid
            {
                cin.clear();
                cin.ignore(1024,'\n');
                if(!usedLocationOfTruthTable[index-1])//check whether the location has already been used
                {
                    cout << "This location has not been used yet! ";//warning
                }
                cout << "Invalid input, Please try again: ";
                cin >> index;//let the technician enter the index again
            }
            string convert = to_string(index);
            cout << "For index " << index <<", ";
            convertPriceInformationToBinary(convert);
            cout << "Please enter the new price of " << beverageList[index-1] << ": ";
            cin >> price;
            while(cin.fail() || price < 0)
            {
                cout << "Invalid price! Please try again: ";
                cin >> price;
            }
            priceList[index-1] = price;//update the corresponding price
            string remover;
            remover = to_string(priceList[index - 1]);
            remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
            int check = priceList[index - 1];
            if (check == priceList[index - 1])//check whether it is an integer
            {
                remover = remover + "0";//if it is an integer then add an additional 0 after the dot
            }
            cout << "For price: " << remover <<", ";
            convertPriceInformationToBinary(remover);
        }
        else if(option == 4)
        {
            if(numberOfProduct == 0)//check whether the list of products is empty
            {
                cout << "Sorry, We are currently selling nothing. You have to add some products before adjust the stock!" << endl;
                break;//exit the technician's menu
            }
            for(int i = 0; i < 8; i++)//use for loop to print the list of beverages that are selling
            {
                if(usedLocationOfTruthTable[i])//check whether there is a kind of beverage stored in that location
                {//if there is, then peint its information out
                    cout << "Location " << i+1<< ": " << choiceList[i] << ":  " << beverageList[i] << "   " << priceList[i] << " Stock: " << stockList[i] << endl;
                }
            }
            cout << "Please enter the index of the location of the beverage you want to adjust the stock(valid integer from 1 to 8): ";
            cin >> index;
            while(cin.fail() || (index > 8 || index < 1) || !usedLocationOfTruthTable[index-1])//check whether the index is valid
            {
                cin.clear();
                cin.ignore(1024,'\n');
                if(!usedLocationOfTruthTable[index-1])//check whether the location has already been used
                {
                    cout << "This location has not been used yet! ";//warning
                }
                cout << "Invalid input, Please try again: ";
                cin >> index;//let the technician enter the index again
            }
            string convert = to_string(index);
            cout << "For index " << index <<", ";
            convertPriceInformationToBinary(convert);
            cout << "Please enter the number of the " << beverageList[index-1] << " you want to add: ";
            cin >> stock;
            while(cin.fail() || stock < 0)
            {
                cout << "Invalid price! Please try again: ";
                cin >> stock;
            }
            string simulate = to_string(stock);//convert to string
            cout << "For stock " << simulate <<", ";
            convertPriceInformationToBinary(simulate);//convert to binary and print out
            stockList[index-1] = stockList[index-1] + stock;//update the corresponding price
        }
        else if(option == 5)
        {
            for(int i = 0; i < 8; i++)//use for loop to print the list of beverages that are selling
            {
                if(usedLocationOfTruthTable[i])//check whether there is a kind of beverage stored in that location
                {//if there is, then peint its information out
                    cout << "Location " << i+1<< ": " << choiceList[i] << ":  " << beverageList[i] << "   " << priceList[i] << " Stock: " << stockList[i] << endl;
                }
                else
                {
                    cout << "Location " << i+1<< ": " << choiceList[i] << ":  " << "N/A" << "   " << "N/A" << " Stock: " << "N/A" << endl;
                }
            }
            cout << "Please enter the index of the location you want to adjust the matched user's input(valid integer from 1 to 8): ";
            cin >> index;
            while(cin.fail() || (index > 8 || index < 1))//check whether the index is valid
            {
                cin.clear();
                cin.ignore(1024,'\n');
                cout << "Invalid input, Please try again: ";
                cin >> index;//let the technician enter the index again
            }
            string convert = to_string(index);
            cout << "For index " << index <<", ";
            convertPriceInformationToBinary(convert);
            cout << "Please update the pair: ";//let the technician update the valid pairs
            char c;//create character c to hold the character
            int i;//create integer i to hold the integer
            string number;//convert the integer into string and then use the string called number to hold it
            string newPair;//use the string called newPair to hold the new pair
            cout << endl;//formatting
            cout << "Character (from A to D): ";
            cin >> c;
            while(cin.fail() || (c != 'A' && c != 'B' && c != 'C' && c != 'D'))//check whether the inpu is correct and proper
            {
                cout << "Invalid input, please try again: ";
                cin >> c;
            }
            
            cout << "Integer (from 1 to 10): ";
            cin >> i;
            while(cin.fail() || i > 10 || i < 1)
            {
                cout << "Invalid input, please try again: ";
                cin >> i;
            }
            number = to_string(i);
            newPair = c + number;
            choiceList[index-1] = newPair;
            cout << "For the new valid pair " << newPair << ":" << endl;
            convertPriceInformationToBinary(newPair);
        }
    }while(option != 6);//if the technician wants to exit the menu, then exit
}

/*
The function makeMoney that uses the result given by the truth table and match the corresponding price of the beverage in order to calculate the change. It also helps users insert money to purchase the beverages.
*/
void makeMoney()
{
    double money = 0.0;//the total amount of money that the user has inserted
    double insert = 0.0;//the amount of money that the user is inserting right now
    double change = 0.0;//the change that is calculated

    if(O == 1)//if the truth table gives the result that the user's input is valid
    {
        if(C1 == 0 && C2 == 0 && C3 == 0){       //match the corresponding information of the beverage according to the truth table
            while (money < priceList[0])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[0];//calculate the change according to the price of the beverage
        }
        else if(C1 == 0 && C2 == 0 && C3 == 1){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[1])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[1];//calculate the change according to the price of the beverage
        }
        else if(C1 == 0 && C2 == 1 && C3 == 0){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[2])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[2];//calculate the change according to the price of the beverage
        }
        else if(C1 == 0 && C2 == 1 && C3 == 1){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[3])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[3];//calculate the change according to the price of the beverage
        }
        else if(C1 == 1 && C2 == 0 && C3 == 0){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[4])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[4];//calculate the change according to the price of the beverage
        }
        else if(C1 == 1 && C2 == 0 && C3 == 1){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[5])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[5];//calculate the change according to the price of the beverage
        }
        else if(C1 == 1 && C2 == 1 && C3 == 0){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[6])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[6];//calculate the change according to the price of the beverage
        }
        else if(C1 == 1 && C2 == 1 && C3 == 1){//match the corresponding information of the beverage according to the truth table
            while (money < priceList[7])//while the money is not enough
            {
                cout << "Please enter cash: $";//keep asking user to insert more money
                cin >> insert;//let the user inert money
                while(cin.fail() || insert < 0)//check whether the money that the user is inserting is valid
                {
                    cout << "Invalid money! Please try again: ";
                    cin.clear();
                    cin.ignore(1024,'\n');
                    cin >> insert;//let the user correct it
                }
                string remover;
                remover = to_string(insert);//convert insert to string
                remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
                int check = insert;
                if (check == insert)//check whether it is an integer
                {
                    remover = remover + "0";//if it is an integer then add an additional 0 after the dot
                }
                cout << "For the number of money you are inserting: " << remover <<", ";
                convertPriceInformationToBinary(remover);
                money = money + insert;//add the money that the user is inserting to the total amount of money he or she inserted
            }
            change = money - priceList[7];//calculate the change according to the price of the beverage
        }
        string remover;
        remover = to_string(change);//convert change to string
        remover.erase (remover.find_last_not_of('0') + 1, std::string::npos);//the to_string function gives non-control result with 0s in the end, this method can remove 0s in the trail
        int check = change;
        if (check == change)//check whether it is an integer
        {
            remover = remover + "0";//if it is an integer then add an additional 0 after the dot
        }
        cout << "For the number of change: " << remover <<", ";
        convertPriceInformationToBinary(remover);
        cout << "Here is your change: $" << fixed << setprecision(2) << change << endl;   //Returns the amount of change to user.
    }
}


/*
 The function that takes the user's input pair and 5 integer array as arguments. It will then determine whether it needs 5 array to store the corresponding binary numbers and return true if it does, return false if it doesn't. It also call the decimalToBinary function to convert an integer to a binary number.
 */
bool convertInputTo8DigitalInput(string keypad, int *binary1, int *binary2, int *binary3, int *binary4, int *binary5)
{
    if(keypad != "0000#")
    {
        int hex1 = keypad.at(0);//convert character to a corresponding integer
        decimalToBinary(hex1, binary1,0);//call converting function to concert the integer to a binary number and store it in binary1
        int hex2 = keypad.at(1);//convert character to a corresponding integer
        decimalToBinary(hex2, binary2,0);//call converting function to concert the integer to a binary number and store it in binary2
        return false;
    }
    else
    {
        int hex1 = keypad.at(0);//convert character to a corresponding integer
        decimalToBinary(hex1, binary1,0);//call converting function to concert the integer to a binary number and store it in binary1
        int hex2 = keypad.at(1);//convert character to a corresponding integer
        decimalToBinary(hex2, binary2,0);//call converting function to concert the integer to a binary number and store it in binary2
        int hex3 = keypad.at(2);//convert character to a corresponding integer
        decimalToBinary(hex3, binary3,0);//call converting function to concert the integer to a binary number and store it in binary3
        int hex4 = keypad.at(3);//convert character to a corresponding integer
        decimalToBinary(hex4, binary4,0);//call converting function to concert the integer to a binary number and store it in binary4
        int hex5 = keypad.at(4);//convert character to a corresponding integer
        decimalToBinary(hex5, binary5,0);//call converting function to concert the integer to a binary number and store it in binary5
        return true;
    }
}

/*
 The recursive function decimalToBinary that takes an integer, an binary array,and a counter as its arguments. It call itself until there is no more value needs to be convert. It also stores the corresponding binary numbers into the binary array when it is in process.
 */
void decimalToBinary(int dec, int *binary, int counter)
{
    if(dec > 0)
    {
        counter = counter + 1;
        decimalToBinary(dec / 2, binary, counter);
        binary[8 - counter] = dec % 2;
    }
    
}

/*
 This function only takes a string as its argument. It then get the length of the string and call the converting function to get the corresponidng binary numbers of each character in the string according to the length of the string.
 */
void convertPriceInformationToBinary(string information)
{
    cout << "the binary signals is: " << endl;//print the input signals
    
    int length = information.length();//get the length of the string in order to know how many binary numbers we need to get
    for(int i = 0; i < length; i++)//call the linear search function to get the corresponding binary numbers according to length of the string
    {
        int input_signals[8] = {0,0,0,0,0,0,0,0};//create an array for storing the binary numbers,initialize to all 0s
        //store the binary numbers in the array
        int dec = information.at(i);
        decimalToBinary(dec, input_signals, 0);
        for(int j = 0; j < 8; j++)
        {
            cout << input_signals[j];
        }
        cout << endl;
    }
    
}

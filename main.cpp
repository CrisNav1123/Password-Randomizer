#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <random>
#include <cstdio>

/*
    Menu Functions
--------------------
1.Retrieve specific account [ Read_File() ]
    -Displays list of accounts stored in file and retrieves specific account
2.Create new Account [ create_pass() ] 
    -This gets user options to generate a new password
3.Change Account   [ Read_File(), req_getter(), Edit_File() ]
    -Gets a specific account from list and allows you to make changes to website, username, or password
4.

#. Quit

To-Do List:
1. Create the account maker
2. Create write to file
3.

*/

class Account
{
public:
//Primary:
    void create_account();
    void view_account();
    void edit_account();
    void delete_account();

//Secondary:
    void create_pass();
    void write_file();
    void read_file();
    bool ToF(char&); //Assigns True or False

private:
//If char array not initilized with empty space, then weird symbols will display 
    char website[20] = {};
    char username[20] = {};
    char password[20] = {};
};

const std::string fileName = "Accounts.record";

int main() 
{
    int choice;

    while(true)
    {
        Account account;
        std::cout << "   Menu   " << std::endl;
        std::cout << "----------" << std::endl;
        std::cout << "1. Create New Account\n";
        std::cout << "2. View Account\n";
        std::cout << "3. Edit Account\n" ;
        std::cout << "4. Delete Account\n";
        std::cout << "5. Exit\n\n"; 

        std::cout << "Choose an option: ";
        std::cin >> choice;

    switch(choice)
    {
        case 1: //Create New Account
            account.create_account();
            break;
        case 2: //View Account
            account.view_account();
            break;
        case 3: //Edit Account
            account.edit_account();
            break;
        case 4: //Delete Account
            //account.delete_account();
            break;
        
    }


    }
}


  /**********************************************************************
 *************************************************************************
**********                 Function Definitions                 ***********       
 *************************************************************************
  ***********************************************************************/

void Account::create_account()
{
    char loop;
    do
    {
    std::cout << "Name of website: ";
    std::cin >> website;
    
    std::cout << "Username: ";
    std::cin >> username;
    system("cls");

    std::cout << "Website : " << website << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "\nIs this correct? (Y/N) ";
    std::cin >> loop;
    }while (toupper(loop) == 'N');

    create_pass();
    write_file();
}
//Function reads account from file
void Account::view_account()
{
   //ERROR: File could not seekp() after Read loop. Could not choose specific data to //read; only read from beginning.

   //SOLUTION: File's eof flag was set to TRUE. This stopped me from being able to //change position of reader. file.clear() resolved the issue. Can choose specific //data to read

    //Checks for file existence
    //Returns if no file found
    std::ifstream ifile;
    ifile.open(fileName, std::ios::binary | std::ios::in);
    if (!ifile)
    {
        std::cout << "File not found. Create an account first.\n";
        return;
    }

    //Variable declaration
    int input;
    ifile.seekg(0, std::ios::end);
//DEBUG
//std::cout << "checkpoint 1: " << ifile.tellg() << std::endl;
    int count = ifile.tellg() / sizeof(*this);
    ifile.seekg(0);
//DEBUG
//std::cout << "checkpoint 2: " << ifile.tellg() << std::endl;
    std::cout << "There are " << count << " account(s) stored.\n\n";
    std::cout << "   Websites" << std::endl;
    std::cout << "--------------" << std::endl;

    while (!ifile.eof())
    {
            for (int i = 0; i < count; i++)
            {
                if(ifile.read(reinterpret_cast<char*>(this), sizeof(*this)))
                {
                    std::cout << i+1 << ". Website: " << std::setw(15) << std::left << website;
                    std::cout << std::setw(10) << "| Username: " << username << std::endl;
//DEBUG
//std::cout << "Read loop checkpoint: " << ifile.tellg() << std::endl;            
                }
            }
    }
//DEBUG - ERROR FOUND. EOF set to 0.
//std::cout << ifile.eof() << std::endl;
//ifile.clear();
//std::cout << ifile.eof() << std::endl;

    std::cout << "Choose an option to view account information: ";
    std::cin >> input;
//DEBUG
//std::cout << "checkpoint 3-1: " << ifile.tellg() << std::endl;
    ifile.seekg((input-1)*sizeof(*this));
//DEBUG
//std::cout << "checkpoint 3-2: " << ifile.tellg() << std::endl;

    ifile.read(reinterpret_cast<char*>(this), sizeof(*this));
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    system("pause");
}


// Should allow user to change website name, username, or re-randomize password
void Account::edit_account(){
    //ERROR: Same issue as view_account(); eof flag set to TRUE. Could not write over specific data, instead only appending.

    //SOLUTION: file.clear() fixes issue.

//Checks for file existence
//Returns if no file found
    std::fstream iofile;
    iofile.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
    if (!iofile)
    {
        std::cout << "File not found. Create an account first.\n";
        return;
    }

    unsigned int input;
    iofile.seekg(0, std::ios::end);
    int count = iofile.tellg() / sizeof(*this);
    iofile.seekg(0);
    std::cout << "There are " << count << " account(s) stored.\n\n";
    std::cout << "   Websites" << std::endl;
    std::cout << "--------------" << std::endl;

    while (!iofile.eof())
    {
            for (int i = 0; i < count; i++)
            {
                if(iofile.read(reinterpret_cast<char*>(this), sizeof(*this)))
                {
                    std::cout << i+1 << ". Website: " << std::setw(15) << std::left << website;
                    std::cout << std::setw(10) << "| Username: " << username << std::endl;
                }
            }
    }
    iofile.clear();
    //Menu selection
    int editChoice;
    std::cout << "Choose the account number to edit" << std::endl;
    std::cout << ">";
    std::cin >> input;
    iofile.seekg((input - 1) *sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "\nChoose the information you would like to edit\n\n" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "1. website\n"
              << "2. username\n"
              << "3. password\n" << std::endl;
    std::cout << ">";
    std::cin >> editChoice;
    switch(editChoice){
        case 1: //Edit website
            std::cout << "Name of website: ";
            std::cin >> website;
            break;
        case 2: //Edit username
            std::cout << "Name of username: ";
            std::cin >> username;
            break;
        case 3: //Edit password
            this->create_pass();
            break;
    }
    //Writes over previous information. Should keep unedited information the same
    iofile.seekp((input - 1) * sizeof(*this));
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

//Deletes an account
void Account::delete_account(){
    //tempfile is replacement. mainFile will write over tempfile BUT skip over selection //to "delete" selected account
    int choice;
    std::fstream tempfile;
    std::ifstream infile;

    infile.open(fileName, std::ios::binary);
    tempfile.open("temp", std::ios::binary | std::ios::out);

    if (!infile)
    {
        std::cout << "File not found. Create an account first.\n";
        return;
    }

    unsigned int input;
    infile.seekg(0, std::ios::end);
    int count = infile.tellg() / sizeof(*this);
    infile.seekg(0);
    std::cout << "There are " << count << " account(s) stored.\n\n";
    std::cout << "   Websites" << std::endl;
    std::cout << "--------------" << std::endl;

    while (!infile.eof())
    {
            for (int i = 0; i < count; i++)
            {
                if(infile.read(reinterpret_cast<char*>(this), sizeof(*this)))
                {
                    std::cout << i+1 << ". Website: " << std::setw(15) << std::left << website;
                    std::cout << std::setw(10) << "| Username: " << username << std::endl;
                }
            }
    }
    infile.clear();
    std::cout << "Choose the account you want to delete: ";
    std::cin >> choice;
    for(int i; i < count; i++){
        infile.read(reinterpret_cast<char*>(this), sizeof(*this));
        if (i == (choice - 1)){
            continue;
        }
        tempfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tempfile.close();
    remove(fileName);
    rename("temp", fileName);
}



/**************************************************
***************************************************
***                 Secondary                 *****
***************************************************     
***************************************************           
*/


//Assigns True or False
bool Account::ToF(char& choice)
{
    while (toupper(choice) != 'Y' && toupper(choice) != 'N')
    {     
            std::cout << "Please choose either 'Y' or 'N': ";
            std::cin >> choice;  
    }
     if (toupper(choice) == 'Y')
         return true;
     else
         return false;
}

//Generates a random password
//Secondary
void Account::create_pass()
{
    char choice;
    char reqLoop;
    char newPassLoop;
    int length;
    bool numReq;
    bool upperReq;
    bool specialReq;

    std::srand(time(nullptr));
    std::random_device gen;
    std::mt19937 e{gen()};
    std::uniform_int_distribution<int> lowerCase{97, 122};
    std::uniform_int_distribution<int> upperCase{65, 90};
    //Combined Case includes special characters 91-96. FIX
    //std::uniform_int_distribution<int> combinedCase{65, 122};
    std::uniform_int_distribution<int> numRan{48, 57};
    std::uniform_int_distribution<int> specialRan{0,31};
    std::uniform_int_distribution<int> chance(0,5);

    char specialChar[31] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'};

    do
    {
        std::cout << "Choose how long to make your password (Max = 20): ";
        std::cin >> length;
        length = length>20? 20:length; 
        std::cout << "Numbers? (Y/N): ";
        std::cin >> choice;
        numReq = ToF(choice);
        std::cout << "Capital character? (Y/N): ";
        std::cin >> choice;
        upperReq = ToF(choice);
        std::cout << "Special character? (Y/N): ";
        std::cin >> choice;
        specialReq = ToF(choice);
    
        std::cout << "\n\n\nAre these options correct?" << std::endl;
        std::cout << "Length: " << 
            length << std::endl;
        std::cout << "Numbers: ";
            numReq? std::cout << "Yes\n" : std::cout << "No\n";
        std::cout << "Upper Case: ";
            upperReq? std::cout << "Yes\n" : std::cout << "No\n";
        std::cout << "Special Character: ";
            specialReq? std::cout << "Yes\n" : std::cout << "No\n";

        std::cout << "Are these options correct? (Y/N) ";
        std::cin >> reqLoop;
    }while (toupper(reqLoop) == 'N');

    do
    {
        std::cout << "Generating new password... " << std::endl;;

        for(int i = 0; i < length; i++)
        {
            if (upperReq && chance(e) <= 1){
                this->password[i] = upperCase(e);
            }
            else{
                this->password[i] = lowerCase(e);
            }
        }
        for (int i = 0; i <length; i++)
        {
            if (numReq == true && chance(e) == 0){
                this->password[i] = numRan(e);
            }
            if(specialReq == true && chance(e) == 0){
                this->password[i] = specialChar[specialRan(e)];
            }
            
        }
        std::cout << "\nPassword: "<< password << std::endl;
        std::cout << "\nAccept? (Y/N) ";
        std::cin >> newPassLoop;
        std::cout << std::endl;

    }while (toupper(newPassLoop) == 'N');
}

//Secondary
//Writes to file
void Account::write_file()
{
    std::fstream file;
    file.open(fileName, std::ios::binary | std::ios::app );
    file.write(reinterpret_cast<char*>(this), sizeof(*this));
    file.close();
}


//function to manipulate date time objects
#include <ctime>
#include <iostream>
#include <stdlib.h>
//function to not need allocate memory
#include <vector>


using namespace std;

    //create a public information
struct EmployeeData{

    time_t timestamp;
    //EmployeeID
    int employeeID;

    //Name:
    string personName;

    //Employment Type (Full-Time,Contract,Part Time)
    string employmentType;

    //Department (Hospital Departments)
    string departmentName;

    //Branch Name and Location
    string branchLocation;

};

class Block{

    private:
        //INDEX
        int blockIndex;
        //current hashed block
        size_t currentBlockHash;
        //previous hashed block
        size_t previousBlockHash;
        //generate the hash
        size_t generateHash();


    public:
        //Constructor for block
        Block(int blockIndex,size_t previousBlockHash,EmployeeData d);
        //Get Original Hash
        size_t getHash();
        //Get Previous Hash
        size_t getPreviousHash();
        //Employee Data
        EmployeeData data;

        //Validate Hash
        bool isHashValid();
};

//Constructor of block
Block::Block(int idx,size_t previousBlockHash,EmployeeData d){

blockIndex=idx;
data=d;
previousBlockHash=previousBlockHash;
currentBlockHash=generateHash();
}

//To generate hashs
size_t Block::generateHash(){

    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;
    string toHash = to_string(data.employeeID)+ to_string(data.timestamp);

    return finalHash(hash1(toHash)+hash2(previousBlockHash));
}

size_t Block::getHash(){
    return currentBlockHash;
}

size_t Block::getPreviousHash(){
    return previousBlockHash;
}

bool Block::isHashValid(){
    return generateHash()==currentBlockHash;
}


//Blockchain Class
class Blockchain{

    private:
        Block createGenesisBlock();

    public:
        //chain
        vector<Block> chain;
        Blockchain();

        void addBlock(EmployeeData data);
        bool isChainValid();

        Block *getLatestBlock();

};

//Blockchain Constructor
Blockchain::Blockchain(){
    Block genesis=createGenesisBlock();
    chain.push_back(genesis);

}

//create first block (Genesis) of chain
Block Blockchain::createGenesisBlock(){

    time_t current;
    EmployeeData employee1;
    employee1.employeeID=2522;
    employee1.personName="Shannon Lee Chung Jin";
    employee1.employmentType="Contract";
    employee1.departmentName="Administration";
    employee1.branchLocation="Semenyih, Selangor";
    employee1.timestamp=time(&current);

    hash<int>hash1;
    Block genesis(1,hash1(1),employee1);
    return genesis;
}

//Get the latest added block
Block *Blockchain::getLatestBlock(){
    return &chain.back();
}


//Add a new block to blockchain
void Blockchain::addBlock(EmployeeData d){
    int index = (int)chain.size()-1;
    Block newBlock(index, getLatestBlock()->getHash(),d);
}

//Check if the chain is valid
bool Blockchain::isChainValid(){

    vector<Block>::iterator it;
    int chainLen=(int)chain.size();

    for (it=chain.begin(); it !=chain.end();++it){
        Block currentBlock=*it;

        if(!currentBlock.isHashValid()){
            return false;
        }

        if(chainLen>1){
            Block previousBlock=*(it-1);
            if(currentBlock.getPreviousHash()!=previousBlock.getHash()){
                return false;
            }
        }
    }
    return true;
}

void displayBlockChain(){



}

//display main menu of program
void displayMainMenu(int programStatus,EmployeeData){

    while(programStatus==1){
        cout<<""<<endl;
        cout<<"Welcome to Medical Record Block Chain"<<endl;
        cout<<"Please select your option"<<endl;

        cout<<""<<endl;
        cout<<"1.Display Block Chain"<<endl;
        cout<<"2.Modify Block Chain"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"____________________________"<<endl;
        cout<<""<<endl;

        //Allow user to select in menu
        cout<<"Option:";
        int menuOption;
        cin>>menuOption;
        cout<<"____________________________"<<endl;

        switch(menuOption){
            case 1:
                //display blockchain
                displayBlockChain();
                cout<<"____________________________"<<endl;
                break;
            case 2:
                //modify blockchain
                cout<<"____________________________"<<endl;
                break;
            case 3:
                programStatus=0;
                cout<<""<<endl;
                cout<<"Thank you for using our service!"<<endl;
                cout<<"____________________________"<<endl;
                break;
            default:
                cout<<"Error! Please Select Option Number"<<endl;
                cout<<"____________________________"<<endl;
        }
    }
}

int main (){


    //Start Blockchain
    Blockchain MedicalRecord;

    //Added 1st Block (genesis) data
    EmployeeData employee1;
    time_t employe1Time;
    employee1.employeeID=2522;
    employee1.personName="Shannon Lee Chung Jin";
    employee1.employmentType="Contract";
    employee1.departmentName="Administration";
    employee1.branchLocation="Semenyih, Selangor";
    employee1.timestamp=time(&employe1Time);

    MedicalRecord.addBlock(employee1);
    cout<<"Is chain valid?"<<endl;
    cout<<MedicalRecord.isChainValid()<<endl;


    //displayMainMenu(1,EmployeeData);
}

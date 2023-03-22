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

        //previous hashed block
        size_t previousBlockHash;
        //generate the hash
        size_t generateHash();


    public:
        //Constructor for block
        Block(int blockIndex,size_t previousBlockHash,EmployeeData d);
        //Get Original Hash
        size_t getHash();
        //current hashed block
        size_t currentBlockHash;
        //Get Previous Hash
        size_t getPreviousHash();
        //Employee Data
        EmployeeData data;

        //Get the data
         string getDataString(){
            string dataStr = "";
            dataStr += "Employee ID: " + to_string(data.employeeID) + "\n";
            dataStr += "Name: " + data.personName + "\n";
            dataStr += "Employment Type: " + data.employmentType + "\n";
            dataStr += "Department: " + data.departmentName + "\n";
            dataStr += "Branch Location: " + data.branchLocation + "\n";
            dataStr += "Timestamp: " + string(ctime(&data.timestamp));
            return dataStr;
        }

        //Validate Hash
        bool isHashValid();
};

//Constructor of block
Block::Block(int idx,size_t previousBlockHash,EmployeeData d){

    //Position of Block
    blockIndex=idx;
    //Data in the Block
    data=d;
    //Access the previous block hash
    this->previousBlockHash=previousBlockHash;
    //Generate Hash for current block
    currentBlockHash=generateHash();
}

//To generate hashes
size_t Block::generateHash(){

    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;
    string toHash = to_string(data.employeeID) + to_string(data.timestamp);
    size_t fullHash = finalHash(hash1(toHash) + hash2(previousBlockHash));
    return fullHash % 10000000000; // get only the first 10 digits
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
        vector<Block>chain;
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

    EmployeeData employee1;
    employee1.employeeID=0;
    employee1.personName="";
    employee1.employmentType="";
    employee1.departmentName="";
    employee1.branchLocation="";

    time_t current;
    time(&current);
    employee1.timestamp=current;

    hash<string>hash1;
    string hashStr = "genesis";
    // get only the first 10 digits of previous hash and current hash
    size_t previousBlockHash = hash1(hashStr)% 10000000000;
    size_t currentBlockHash = hash1(hashStr)% 10000000000;  // current hash is equal to previous hash
    Block genesis(1, previousBlockHash, employee1);
    genesis.currentBlockHash = currentBlockHash;  // set the current hash of genesis block to be equal to the previous hash of the same block
    return genesis;
}

//Get the latest added block (BUG)
Block *Blockchain::getLatestBlock(){
        return &chain.back();
}

//Add a new block to block chain
void Blockchain::addBlock(EmployeeData d){
    int index = (int)chain.size();
    Block newBlock(index, getLatestBlock()->getHash(), d);
    chain.push_back(newBlock);
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

int main (){

    //Start Blockchain
    Blockchain MedicalRecord;

    //Added 1st Block (genesis) data
    EmployeeData employee1;
    time_t employee1Time;
    employee1.employeeID=2522;
    employee1.personName="Shannon Lee Chung Jin";
    employee1.employmentType="Contract";
    employee1.departmentName="Administration";
    employee1.branchLocation="Semenyih, Selangor";
    employee1.timestamp=time(&employee1Time);
    MedicalRecord.addBlock(employee1);

    /*
    EmployeeData employee2;
    time_t employee2Time;
    employee2.employeeID=3255;
    employee2.personName="Adil Lahil";
    employee2.employmentType="Full-Time";
    employee2.departmentName="Administration";
    employee2.branchLocation="Semenyih, Selangor";
    employee2.timestamp=time(&employee2Time);
    MedicalRecord.addBlock(employee2);
    */

// Display the current and previous hash for each block in the chain
    for (int i = 0; i < MedicalRecord.chain.size(); i++) {
        cout << "Block " << i << ":" << endl;
        cout << "Current Hash: " << MedicalRecord.chain[i].getHash() << endl;
        cout << "Previous Hash: " << MedicalRecord.chain[i].getPreviousHash() << endl;
        cout << "__________Data__________" << endl;
        cout << MedicalRecord.chain[i].getDataString()<< endl;
        cout << "________________________" << endl;
        cout <<""<<endl;
    }


    cout<<"Is chain valid?"<<endl;
    cout<<MedicalRecord.isChainValid()<<endl;

    return 0;
}

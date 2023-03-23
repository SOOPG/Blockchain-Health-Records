//function to manipulate date time objects
#include <ctime>
#include <iostream>
#include <stdlib.h>
//function to not need allocate memory
#include <vector>


using namespace std;

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

    string pastShift;
    string currentShift;
    string upcomingShift;
    string extraDetails;

};

//Block class
class Block{

    private:
        //Index of Block
        int blockIndex;

        //previous hashed block
        size_t previousBlockHash;
        //generate the hash
        size_t generateHash();


    public:
        //Call the Constructor Function
        Block(int blockIndex,size_t previousBlockHash,EmployeeData d);
        //Get Original Hash
        size_t getHash();
        //current hashed block
        size_t currentBlockHash;
        //Get Previous Hash
        size_t getPreviousHash();
        //Employee Data
        EmployeeData data;

        //Get the employee data
         string getEmployeeData(){
            string employeeData = "";
            employeeData += "Employee ID: " + to_string(data.employeeID) + "\n";
            employeeData += "Name: " + data.personName + "\n";
            employeeData += "Employment Type: " + data.employmentType + "\n";
            employeeData += "Department: " + data.departmentName + "\n";
            employeeData += "Branch Location: " + data.branchLocation + "\n";
            employeeData += "Timestamp: " + string(ctime(&data.timestamp));
            return employeeData;
        }

        //Get Employee Work Shift
        string getEmployeeShift(){
            string employeeShift = "";
            employeeShift +="Previous Shift: " + data.pastShift + "\n";
            employeeShift +="Current Shift: " + data.currentShift + "\n";
            employeeShift +="Next Shift: " + data.upcomingShift + "\n";
            return employeeShift;
        }

        //Get Extra Employee Information
        string getEmployeeExtraInfo(){
        string employeeExtraInfo= "";
         employeeExtraInfo += "More Details: "+ data.extraDetails + "\n";
        return employeeExtraInfo;
        }

};

//Constructor of Block
Block::Block(int idx,size_t previousBlockHash,EmployeeData d){

    //Index of Block
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

//Blockchain Class
class Blockchain{

    private:
        Block createGenesisBlock();

    public:
        //chain
        vector<Block>chain;
        Blockchain();

        void addBlock(EmployeeData data);

        //Pointer to the latest block
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

//Get the latest added block
Block *Blockchain::getLatestBlock(){
        return &chain.back();
}

//Add a new block to block chain
void Blockchain::addBlock(EmployeeData d){
    int index = (int)chain.size();
    Block newBlock(index, getLatestBlock()->getHash(), d);
    chain.push_back(newBlock);
}

int main (){

    //Start Blockchain
    Blockchain MedicalRecord;

    EmployeeData employee1;
    time_t employee1Time;
    employee1.employeeID=2522;
    employee1.personName="Shannon Lee Chung Jin";
    employee1.employmentType="Contract";
    employee1.departmentName="Administration-Receptionist";
    employee1.branchLocation="Semenyih, Selangor";
    employee1.timestamp=time(&employee1Time);
    employee1.pastShift="9.00am-11.00am";
    employee1.currentShift="3.00pm-5.00pm";
    employee1.upcomingShift="8.00pm-10.00pm";
    employee1.extraDetails="Attend to customers/patients at the lobby of hospital";
    MedicalRecord.addBlock(employee1);


    EmployeeData employee2;
    time_t employee2Time;
    employee2.employeeID=3255;
    employee2.personName="Adil Lahil";
    employee2.employmentType="Full-Time";
    employee2.departmentName="ER-Nurse";
    employee2.branchLocation="Semenyih, Selangor";
    employee2.timestamp=time(&employee2Time);
    employee2.pastShift="12.00am-2.00am";
    employee2.currentShift="6.00am-8.00am";
    employee2.upcomingShift="10.00am-12.00pm";
    employee2.extraDetails="Responsible for Emergency Responses";
    MedicalRecord.addBlock(employee2);

    EmployeeData employee3;
    time_t employee3Time;
    employee3.employeeID=5591;
    employee3.personName="Amry Ganle";
    employee3.employmentType="Intern";
    employee3.departmentName="Administration-Assistant Secretary";
    employee3.branchLocation="Semenyih, Selangor";
    employee3.timestamp=time(&employee3Time);
    employee3.pastShift="8.00am-3pm";
    employee3.currentShift="8.00am-3pm";
    employee3.upcomingShift="8.00am-3pm";
    employee3.extraDetails="Assisting secretary on hospital paperwork.";
    MedicalRecord.addBlock(employee3);

    EmployeeData employee4;
    time_t employee4Time;
    employee4.employeeID=1274;
    employee4.personName="Danton Fowlee";
    employee4.employmentType="Full-Time";
    employee4.departmentName="General Practitioner";
    employee4.branchLocation="Semenyih, Selangor";
    employee4.timestamp=time(&employee4Time);
    employee4.pastShift="6.00pm-8.00pm";
    employee4.currentShift="8.00am-3pm";
    employee4.upcomingShift="6.00pm-8.00pm";
    employee4.extraDetails="General Practitioner for normal illnesses";
    MedicalRecord.addBlock(employee4);

    EmployeeData employee5;
    time_t employee5Time;
    employee5.employeeID=9188;
    employee5.personName="Frederich Heisel";
    employee5.employmentType="Full-Time";
    employee5.departmentName="Radiology-Head of Staff";
    employee5.branchLocation="Semenyih, Selangor";
    employee5.timestamp=time(&employee5Time);
    employee5.pastShift="6.00pm-8.00pm";
    employee5.currentShift="10.00am-2pm";
    employee5.upcomingShift="6.00pm-8.00pm";
    employee5.extraDetails="Radiology Staff responsible for XRAY procedures";
    MedicalRecord.addBlock(employee5);

    EmployeeData employee6;
    time_t employee6Time;
    employee6.employeeID=7781;
    employee6.personName="Hille Grant";
    employee6.employmentType="Full-Time";
    employee6.departmentName="Cardiologist-Specialist";
    employee6.branchLocation="Semenyih, Selangor";
    employee6.timestamp=time(&employee6Time);
    employee6.pastShift="Standby:11.00am-5.00am";
    employee6.currentShift="8.00am-6.00pm";
    employee6.upcomingShift="Standby:11.00am-5.00am";
    employee6.extraDetails="Cadiologist specialist on standby at night";
    MedicalRecord.addBlock(employee6);

// Display the current and previous hash for each block in the chain and also employee data
    for (int i = 0; i < MedicalRecord.chain.size(); i++) {
        cout << "Block " << i << ":" << endl;
        cout << "Current Hash: " << MedicalRecord.chain[i].getHash() << endl;
        cout << "Previous Hash: " << MedicalRecord.chain[i].getPreviousHash() << endl;
        cout << "__________Data__________" << endl;
        cout << MedicalRecord.chain[i].getEmployeeData()<< endl;
        cout << MedicalRecord.chain[i].getEmployeeShift()<< endl;
        cout << MedicalRecord.chain[i].getEmployeeExtraInfo()<< endl;
        cout << "________________________" << endl;
        cout <<""<<endl;
    }

    return 0;
}

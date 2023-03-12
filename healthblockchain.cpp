//function to manipulate date time objects
#include <ctime>
#include <iostream>
#include <stdlib.h>
//function to not need allocate memory
#include <vector>


using namespace std;

/*
void createBlockRecord(){

    //create a block
    struct Block{
    int blockNumber;
    int currentBlockHash;
    int previousBlockHash;

    //Timestamp


    };

}
*/


//display blockchain
void displayBlockChain(){

    cout<<"BlockChain Displayed"<<endl;

}

//display main menu of program
void displayMainMenu(int programStatus){

    while(programStatus==1){
        cout<<""<<endl;
        cout<<"Welcome to Health Blockchain"<<endl;
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

    displayMainMenu(1);


}


void createNodeReference(){

/*
     //One block
    struct node{
    int data;
    node* next;
    };

    node* n;
    node* temp;
    node* head;

    n=new node;
    n->data=1;

    temp=n;
    //head of linked list
    head=n;

    //adding new node
    n=new node;
    n->data=2;

    //linking to next node (extending)
    temp->next=n;
    //move temp to 2nd node
    temp=temp->next;

    //3rd node
    n=new node;
    n->data=3;
    temp->next=n;

    n=new node;
    n->data=4;
    temp->next=n;
    n->next=NULL;
    */
}

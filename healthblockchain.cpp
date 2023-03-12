#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

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

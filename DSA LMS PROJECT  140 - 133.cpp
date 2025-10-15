#include<iostream>
#include<windows.h>
#include <fstream>   // File handling
#include <sstream>   // For string stream //
#include<conio.h>
using namespace std;
class library
{
	private :
		struct Node{
			int id,quantity;
			string name,auther,publisher, category;  // catagory or quantity gpt
			Node* next_add;  //Node create kr lya vo next address ko point kry ga
		};
		public:
			Node *head = nullptr;  //filhal ll empty
			void menu();
			void insert();
			void search();
            void update();
            void del();
            void sort();  // Bubble sorting hoi ha 
            void show();
            void searchByNameOrAuthor();  // This is the function declaration
            void showCreatorDetails();
            
            void saveToFile();  // Save data to file
            void loadFromFile(); // Load data from file//
        
        
        
};



bool login() {  
    string user, pass;
    cout << "\n\n\t\t\tLIBRARY MANAGEMENT SYSTEM - LOGIN";
    cout << "\n\n Username: ";
    cin >> user;
    cout << "\n Password: ";
    cin >> pass;

    // Static username and password
    if (user == "admin" && pass == "12345") {
        cout << "\n\n Login successful!";
        Sleep(1000);
        return true;
    } else {
        cout << "\n\n Invalid credentials. Access denied.";
        return false;
    }
}


void library::saveToFile() {  
    ofstream outFile("library_data.txt", ios::out);
    if (!outFile) {
        cout << "File could not be opened!" << endl;
        return;
    }

    Node* ptr = head;
    while (ptr != nullptr) {
        // Saving data in the format: id,name,author,publisher,quantity,category
        outFile << ptr->id << "," 
                << ptr->name << "," 
                << ptr->auther << "," 
                << ptr->publisher << "," 
                << ptr->quantity << ","
                << ptr->category << endl;
        ptr = ptr->next_add;
    }
    outFile.close();
    cout << "Data has been saved successfully!" << endl;
}//gpt


void library::loadFromFile() {  
    ifstream inFile("library_data.txt", ios::in);
    if (!inFile) {
        cout << "File could not be opened!" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Node* newNode = new Node;

        // Reading data from file, splitting by comma
        getline(ss, line, ','); newNode->id = stoi(line);
        getline(ss, newNode->name, ',');
        getline(ss, newNode->auther, ',');
        getline(ss, newNode->publisher, ',');
        getline(ss, line, ','); newNode->quantity = stoi(line);
        getline(ss, newNode->category, ',');

        newNode->next_add = head;  // Adding to the start of linked list
        head = newNode;  // Make the new node the head of the list
    }
    inFile.close();
    cout << "Data has been loaded successfully!" << endl;
}


void library ::menu()

{
	loadFromFile(); 
	system("cls");
	int choice;
	cout<<"\n\n\t\t\t====================================================";
	cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	cout<<"\n\n\t\t\t====================================================";
	cout<<"\n\n 1. Insert New Record";
	cout<<"\n\n 2. Search Record";
	cout<<"\n\n 3. Update Record";
	cout<<"\n\n 4. Delete Record";
	cout<<"\n\n 5. Show all Record";
	cout<<"\n\n 6. Show Creator Details";
	cout<<"\n\n 7. Exit";
	cout<<"\n\n Enter Your Choice : ";
	cin>>choice;
	switch (choice){
		case 1:
			insert();
			break;
		case 2:
			search();
		    break;
		case 3:
			update();
		    break;
		case 4:
			 del();
		    break;
		case 5:
			 sort();
			 show();
			break;
			case 6:
			showCreatorDetails();
			break;
				
		case 7:
			exit(0);
			default:
				cout<<"\n\n Invalid Choice..Please try Again......";
		}
		getch();
	   
	}
	void library:: insert(){
		
		system("cls");
	    cout<<"\n\n\t\t\t====================================================";
        Node *new_node = new Node;
        cout<<"\n\n Book ID : ";
        cin>>new_node -> id;
        cout<<"\n\n Name : ";
        cin>>new_node -> name;
        cout<<"\n\n Auther : ";
        cin>>new_node -> auther;
        cout<<"\n\n publisher Name : ";
        cin>>new_node -> publisher;
        
        
        cout << "\n\t\t\tEnter Category: ";//gpt
        cin.ignore();
        getline(cin, new_node->category);

        cout << "\n\t\t\tEnter Quantity: ";
        cin >> new_node->quantity;//gpt

        
        new_node -> next_add =nullptr;
        if(head==nullptr){
        	head=new_node;
		}
		else{
			Node *ptr = head;
            while (ptr->next_add != nullptr) {
            ptr = ptr->next_add;
}
           ptr->next_add = new_node;  // ? Properly linking the new node


			
		}
		cout<<"\n\n\t\t\t New Book Inserted Successfully ";
		    saveToFile();
			Sleep(1000); // Wait for 1 seconds (1000 milliseconds)
	     	menu();      // Go back to menu
		    return; 

	}
	
	void library::searchByNameOrAuthor() {
    system("cls");

    string searchTerm;
    int choice;

    // Display header and options for search
    cout << "\n\n\t\t\t====================================================";
    cout << "\n\n\t\t\t=========LIBRARY MANAGEMENT SYSTEM===================";
    cout << "\n\n\t\t\t====================================================";

    cout << "\n\n\t\tSearch By:\n";
    cout << "1. Search by Book Name\n";
    cout << "2. Search by Author Name\n";
    cout << "\nEnter your choice (1 or 2): ";
    cin >> choice;

    // Depending on choice, ask for the search term
    if (choice == 1) {
        cout << "\nEnter Book Name: ";
        cin.ignore();  // To handle newline character
        getline(cin, searchTerm);
    } else if (choice == 2) {
        cout << "\nEnter Author Name: ";
        cin.ignore();
        getline(cin, searchTerm);
    } else {
        cout << "\nInvalid choice!";
        return;
    }

    // Search logic
    Node* ptr = head;
    bool found = false;

    while (ptr != nullptr) {
        if ((choice == 1 && ptr->name == searchTerm) || (choice == 2 && ptr->auther == searchTerm)) {
            found = true;
            cout << "\nBook Found!";
            cout << "\nBook ID: " << ptr->id;
            cout << "\nBook Name: " << ptr->name;
            cout << "\nAuthor: " << ptr->auther;
            cout << "\nPublisher: " << ptr->publisher;
            cout << "\nCategory: " << ptr->category;
            cout << "\nQuantity: " << ptr->quantity;
            break;
        }
        ptr = ptr->next_add;
    }

    if (!found) {
        cout << "\nNo Book Found!";
    }

    cout << "\n\nPress any key to continue...";
    _getch();
}

	void library::search(){
		int t_id,found=0;
		cout<<"\n\n\t\t\t====================================================";
	    cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	    cout<<"\n\n\t\t\t====================================================";
	    
	    if(head==nullptr){
	    cout<<"\n\n Linked List is Empty";
	    Sleep(1000); // Wait for 4 seconds (4000 milliseconds)
		menu();      // Go back to menu
		return;   
	    
	    	
		}
		
			cout<<"\n\n Book ID : ";
			cin>>t_id;
			Node *ptr=head;
			while(ptr != nullptr){
				if(t_id == ptr -> id){
					system("cls");
		    cout<<"\n\n\t\t\t====================================================";
	        cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	        cout<<"\n\n\t\t\t====================================================";
			cout<<"\n\n Book ID : "<<ptr -> id;
			cout<<"\n\n Book Name : "<<ptr -> name;
			cout<<"\n\n Auther Name: "<<ptr -> auther;
			cout<<"\n\n Publisher Name : "<<ptr -> publisher;
			found++;
		
				}
				ptr  = ptr -> next_add;
				
			}
			getch();
			menu();
			if(found== 0){
				cout<<"\n\n Book ID is invalid .......";
			}
		}
	
	void library::update(){
		int t_id,found=0;
	
		cout<<"\n\n\t\t\t====================================================";
	    cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	    cout<<"\n\n\t\t\t====================================================";
	    
	    if(head==nullptr){
	    	cout<<"\n\n Linked List is Empty";
	    	Sleep(1000); // Wait for 1 seconds (1000 milliseconds)
		    menu();      // Go back to menu
		    return; 
	    	
		}
		else{
			cout<<"\n\n Book ID : ";
			cin>>t_id;
			Node *ptr=head;
			while(ptr != nullptr){
				if(t_id == ptr -> id){
		    system("cls");
		    cout<<"\n\n\t\t\t====================================================";
	        cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	        cout<<"\n\n\t\t\t====================================================";
			cout<<"\n\n Book ID : ";
			cin>>ptr -> id;
		    cout<<"\n\n Book Name : ";
			cin>>ptr -> name;
			cout<<"\n\n Auther Name: ";
			cin>>ptr -> auther;
			cout<<"\n\n Publisher Name : ";
			cin>>ptr -> publisher;
			found++;
		    cout<<"\n\n\t\t\t update Book SuccessFully";
		    ptr  = ptr -> next_add;
				}
				getch();
				menu();
			
				
			}
			if(found== 0){
				cout<<"\n\n Book ID is invalid .......";
			}
		}
	}
	
		
		void library::del(){
	     saveToFile(); 
		
		system("cls");
			int t_id,found=0;
		cout<<"\n\n\t\t\t====================================================";
	    cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	    cout<<"\n\n\t\t\t====================================================";
	    
	    if(head == nullptr ){
	    	cout<<"\n\n Linked List is Empty";
	    	Sleep(1000); // Wait for 1 seconds (1000 milliseconds)
	     	menu();      // Go back to menu
		    return; 
	    	
		}
		else{
			cout<<"\n\n Book ID : ";
			cin>>t_id;
			if( t_id == head->id){
				Node *ptr =head;
				head=head ->next_add;
				delete ptr;
				cout<<"\n\n Delete Book SuccessFully";
				found++;
			}
		
			else{
				Node *pre=head;
				Node *ptr=head;
				
				while(ptr !=nullptr){
					if (t_id ==ptr ->id ){
						pre ->next_add=ptr ->next_add;
						delete ptr;
						cout<<"\n\n Delete Book SuccessFully";
						found++;
						break;
						
						
					}
					getch();
					menu();
					pre=ptr;
					ptr=ptr->next_add;
				}
			}
			if(found==0){
				cout<<"\n\n Book ID is Invalid";
			}
			
		}
		
	}		
		void library::sort(){
			if(head==nullptr){
				system("cls");
				cout<<"\n\n\t\t\t====================================================";
	            cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	            cout<<"\n\n\t\t\t====================================================";
				cout<<"\n\n Linked List is empty";
				getch();
				menu();
			}
			int count=0,t_id;
			
			string t_name,t_auther,t_publisher;
			Node *ptr=head;
			while(ptr !=nullptr){
				count++;
				ptr=ptr -> next_add;
				
			}
			
			for(int i=1;i<count;i++){  
			Node *ptr=head;
			
				for (int j=1;j<count;j++ ){  //start with next next 
					if(ptr ->id > ptr -> next_add ->id)   { //sort
			//save data into temporary variable
						
				     t_id=ptr ->id;  	//current variable ki value temporary safe 
				     t_name=ptr -> name;
				     t_auther= ptr ->auther;
				     t_publisher=ptr->publisher;
				     //save data into current node
				     ptr ->id =ptr -> next_add ->id;
				     ptr ->name=ptr -> next_add ->name;
				     ptr ->auther=ptr -> next_add ->auther;
				     ptr ->publisher=ptr -> next_add ->publisher;
				     //save data into next node 
				     ptr -> next_add ->id=t_id;
				     ptr -> next_add ->name=t_name;
				     ptr -> next_add ->auther=t_auther;
				     ptr -> next_add ->publisher=t_publisher;
				}
				ptr=ptr->next_add;
			}
		}
	}
	void library::show(){

	    system ("cls");
		cout<<"\n\n\t\t\t====================================================";
	    cout<<"\n\n\t\t\t=========LIBRARY MANAGMENT SYSTEM===================";
	    cout<<"\n\n\t\t\t====================================================";
	    
			Node *ptr=head;
			if (ptr == nullptr) {
        cout << "\n\n Linked List is Empty";
    }
			while(ptr != nullptr){
			cout<<"\n\n Book ID : "<<ptr -> id;
			cout<<"\n\n Book Name : "<<ptr -> name;
			cout<<"\n\n Auther Name: "<<ptr -> auther;
			cout<<"\n\n Publisher Name : "<<ptr -> publisher;
			cout <<"\n\nCategory: " << ptr->category;//gpt
            cout <<"\n\nQuantity: " << ptr->quantity;//gpt
			
			cout<<"\n\n\t\t\t====================================================";
			 	
			ptr  = ptr -> next_add;
				
			}
			getch();
			menu();
			
	}
	
void library::showCreatorDetails() {
    cout << "\n==================================================\n";
    cout << "            DSA Project: Library Management System\n";
    cout << "==================================================\n";
    cout << " Subject       : Data Structures & Algorithms (DSA)\n";
    cout << " Instructor    : Shaheen Kausar\n";
    cout << " Technology    : Singly Linked List (Data Structure)\n";
    cout << " Functionality : Book Insert, Search, Update, Delete, Sort, etc.\n";
    cout << "--------------------------------------------------\n";
    cout << " Project Created By:\n";
    cout << " 1. Ali Hasnian     | Roll Number: FA23-BSE-140\n";
    cout << " 2. Dawood Tahir    | Roll Number: FA23-BSE-133\n";
    cout << " Department         : Software Engineering\n";
    cout << " Session            : Fall 2023\n";
    cout << " Institution        : COMSATS University, Sahiwal\n";
    cout << "==================================================\n";
}

int main(){

    library obj;

    if (login()) {
        obj.menu();
    } else {
        cout << "\n\n Exiting program...";
        Sleep(1500);
        exit(0);
    }

	obj.menu();
	return 0;
		
}
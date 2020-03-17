#include<iostream>
#include<stdio.h>
#include<fstream>
#include<process.h>
void showevent(long int);
void requested_event();
void registeruser();
void registerevent(long int);
void admin_panel_fns();
void admin_panel();
void user_panel();
void thanks();
void user_panel_fns();
void writedata();
void addevent();
void delete_event();
void editevent(long int);
using namespace std;
//class template for events
class EVENT{
	char name[20];
	char desc[100];
	char date[10];
	long int id;
	int participants;
	int participant_limit;
	float popularity;
	
	public:
		EVENT(){
		participants=0;
		participant_limit=0;
		popularity=0.0;
	}
	   long int getid(){
	   	return id;
	   }
		void getdata(){
			cout<<"Enter Event id::";
			cin>>id;
			fflush(stdin);
			cout<<"\nEnter the name of the Event::";
			gets(name);
			cout<<"\nEnter the description of the Event::";
			gets(desc);
			cout<<"\nEnter the date of the event(DD.MM.YYYY)::";
			gets(date);
			cout<<"\nEnter the participation Limit::";
			cin>>participant_limit;
		}
		
		void getparticipant(){
			participants++;
		}
		
		void putdata(){
			
			cout<<"\nName of the Event::"<<name<<endl;
			cout<<"Discription::"<<desc<<endl;
			cout<<"Date of Event::"<<date<<endl;
			cout<<"Participation limits::"<<participant_limit<<endl;
			cout<<"Status of the event::"<<"active"<<endl;
			cout<<"Participants::"<<participants<<endl;
		}
};

//class template for admin
class admin{
	char username[20];
	char password[20];
	public:
	void getdata(){
	cout<<"Enter your username::";
	cin>>username;
	cout<<"Enter your password::";
	cin>>password;
	}
	char* getusername(){
		return username;
	}
	
	char* getpassword(){
		return password;
	}
};


//class template for users
class user{
	char user_name[20];
	char pass_word[20];
	public:
	char* getusername(){
		return user_name;
		
	}
	char* getpassword(){
		return pass_word;
	}
	
	void getdata(){
	cout<<"\nEnter username::";
	cin>>user_name;
	cout<<"\nEnter password::";
	cin>>pass_word;
	}
};
// main function
int main(){
	int ch;
	//writedata();
	//registeruser();
	while(ch!=3){
	
	cout<<"\t\t\tMAIN MENU"<<endl;
	cout<<"1.Sign in as admin"<<endl;
	cout<<"2.Sign in as user"<<endl;
	cout<<"3.Exit"<<endl;
	cout<<"Enter Your choice::";
	cin>>ch;
	switch(ch){
		case 1: admin_panel();
		        break;
		case 2: user_panel();
		        break;
		case 3: thanks();
		        exit(-1);
		default: cout<<"Enter correct choice!!!"<<endl;
		
	};}
	return 0;
}


// login function for admin
void admin_panel(){
	fstream adminfile;
	adminfile.open("Admin.dat",ios::in|ios::binary);
	if(!adminfile){
		cout<<"Can't find the admin file!!!"<<endl;
		exit(0);
	}
	admin A;
	string user,pass;
	cout<<"\nEnter Your username::";
	cin>>user;
	cout<<"\nEnter Yout password::";
	cin>>pass;
	
	
	while(adminfile.read((char*)&A,sizeof(A))){
		if(A.getusername()==user && A.getpassword()==pass){
			cout<<"Login Successfull!!"<<endl;
			admin_panel_fns();
		}else{
			cout<<"Wrong credientials!!!"<<endl;
			exit(0);
		}
	}
	
	
}
// admin panel for doing many stuffs

void admin_panel_fns(){
	int ch;
	int id;
	
	system("cls");
	cout<<"\n\t\tADMIN MENU"<<endl;
	cout<<"1.Add an event"<<endl;
	cout<<"2.Show an event"<<endl;
	cout<<"3.Delete an event"<<endl;
	cout<<"4.Edit an  event"<<endl;
	cout<<"5.Requested Events"<<endl;
	cout<<"6.Exit"<<endl;
	cout<<"Enter Your choice::";
	cin>>ch;
	switch(ch){
	case 1: addevent();
	        break;
	case 2: cout<<"Enter the id of the event::";
	        cin>>id;
	        showevent(id);
	       break;
	case 3: delete_event();
	        break;
	case 4: cout<<"Enter the id of the event::";
	        cin>>id;
	        editevent(id);
	        break;
	        
	case 5:requested_event();
	case 6: thanks();
	        exit(0);	
	};
}
void user_panel_fns(){
	fstream f;
	EVENT E;
	f.open("event.dat",ios::in|ios::binary);
	if(!f){
		cout<<"No events found!!!"<<endl;
		exit(0);
}
while(f.read((char*)&E,sizeof(E))){
	E.putdata();
}
long int id;
cout<<"Enter the Event id to register::";
cin>>id;
registerevent(id);

}

void registerevent(long int id){
	fstream f;
	EVENT E;
	bool found=false;
	f.open("Event.dat",ios::binary|ios::in|ios::app);
	if(!f){
		cout<<"Can't register now!!!"<<endl;
		exit(0);
	}
	int pos=sizeof(E);
	while(f.read((char*)&E,sizeof(E))){
		if(E.getid()==id){
			f.seekg(-pos,ios::cur);
			E.getparticipant();
			found=true;
		}
	}
	if(found==false){
	cout<<"No event found with this id!!"<<endl;
}
}

//users panel for showing the events
void registeruser(){
	fstream f;
	user u;
	f.open("users.dat",ios::app|ios::binary|ios::out);
	u.getdata();
	f.write((char*)&u,sizeof(u));
	cout<<"Registered successfully!!"<<endl;
}
void user_panel(){
	fstream f;
	user u;
	f.open("users.dat",ios::in|ios::binary);
	if(!f){
		cout<<"No user exits!!!"<<endl;
		exit(0);
	}
     string user,pass;
	cout<<"\t\t\tUser Login"<<endl;
	cout<<"Enter username::";
	cin>>user;
	cout<<"\nEnter password::";
	cin>>pass;
	while(f.read((char*)&u,sizeof(u))){
		if(u.getusername()==user && u.getpassword()==pass){
			cout<<"Login successfull!!"<<endl;
			user_panel_fns();
		}
		else{
			cout<<"Wrong Credentials!!!"<<endl;
			exit(0);
		}
	}
	
	
}

void thanks(){
	cout<<"\n\n\n\t\t\tTHANKS FOR USING THIS SOFTWARE"<<endl;
	cout<<"NAME:BHUPENDRA"<<endl;
}
// function to call in case admin login file is lost
void writedata(){
	fstream f;
	f.open("admin.dat",ios::out|ios::binary);
	admin A;
	A.getdata();
	f.write((char*)&A,sizeof(A));
	cout<<"Write Successfull!!";
}

void addevent(){
	EVENT E;
	fstream fout;
	fout.open("event.dat",ios::app|ios::out|ios::binary);
	if(!fout){
		cout<<"Can't create file!!"<<endl;
		exit(0);
	}
	
	/*if(fout.good()){
		cout<<"Good"<<endl;
		
	}
	if(fout.bad()){
		cout<<"Bad!!"<<endl;
	}*/
	E.getdata();
	E.putdata();
	fout.write((char*)&E,sizeof(EVENT));
	cout<<"Data saved Sucessfully!!!"<<endl;
	fout.close();
}

void delete_event(){
	cout<<"Delete Event module"<<endl;
}

void editevent(long int id){
	EVENT E;
	fstream f;
	bool found=false;
	f.open("event.dat",ios::in|ios::binary|ios::app);
	if(!f){
		cout<<"can't open file"<<endl;
		exit(0);
	}
	int pos = sizeof(EVENT);
	while(f.read((char*)&E,sizeof(E))){
		if(E.getid()==id){
			found=true;
			
			f.seekg(-pos,ios::cur);
			E.getdata();
			f.write((char*)&E,sizeof(E));
			
		}
	}
	if(found==false){
		cout<<"No Event found!!"<<endl;
	}
	f.close();
}
void showevent(long int id){
	fstream f;
	EVENT E;
	bool found = false;
	f.open("event.dat",ios::in|ios::binary);
	while(f.read((char*)&E,sizeof(E))){
		if(id==E.getid()){
			E.putdata();
			found =true;
		}
	}
	if(found==false){
		cout<<"No Event found!!!"<<endl;
	}
	
	
}

void requested_event(){
	EVENT E;
	cout<<"\t\t\trequested Events"<<endl;
	fstream f;
	f.open("request.dat",ios::in|ios::binary);
	if(!f){
		cout<<"No requested Events!!!"<<endl;
		exit(0);
	}
	
	while(f.read((char*)&E,sizeof(E))){
		E.putdata();
	}
	f.close();
}

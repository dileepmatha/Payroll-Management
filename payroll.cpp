//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;
class NoEmp{};
class FileNoOpened{};
class WrongPassword{};
class UserNotfound{};
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
void clrscr()
{
   system("cls");
}
class emp{
    char password[50],name[50];
    int empid;
    char gen;
    double sal;
    bool payroll;
public:
    void write(){

        cout<<"\n enter the employee  id:";
        cin>>empid;
        cout<<"\n enter the  employee name :";
        cin.ignore();
        cin.getline(name,49);
        cout<<"\n enter the employee gender :";
        cin>>gen;
        cout<<"\n enter the salary per month :";
        cin>>sal;
        strcpy(password,"password");
        payroll=false;
    }
    void setpassword(char* p){strcpy(password,p);}
    int retempid(){return empid;}
    char *retpassword(){return password;}
    char *retname(){return name;}
    double retsal(){return sal;}
    char retgen(){return gen;}
    void setpayroll(bool b){payroll=b;}
    bool retpayroll(){return payroll;}
    void display(){
    cout<<"\n employee  id:"<<empid;
    cout<<"\n employee name:"<<name;
    cout<<"\n employee gender:"<<gen;
    cout<<"\n employee salary package:"<<sal<<endl;
    }
    void list()
    {
        cout<<"\t"<<empid<<"\t\t"<<name<<"\t\t"<<gen<<"\t\t"<<sal<<"\t\t"<<payroll<<endl;
    }

};
void attributes(){
    cout<<"\tEMP.ID\t\tName\t\tGender\t\tSalary\t\tPayment";
}
bool verifi(int empid,char *p){
			fstream myfile;
			emp temp;
			myfile.open("emp.dat",ios::in);
			if(myfile.is_open()){
				while(myfile.read((char*)&temp, sizeof(temp))>0)
					if(empid==temp.retempid())
						if(strcmp(p,temp.retpassword())==0)
							return true;
				return false;
			}else throw FileNoOpened();
}
bool search(int empid){
			ifstream myfile;
			emp temp;
			myfile.open("emp.dat",ios::in);
			if (myfile.is_open())
			{
				while(myfile.read((char*)&temp, sizeof(temp))>0){
					if(empid==temp.retempid())
						return true;
				}
			}else throw FileNoOpened();
			return false;
		}
void modify_password(int empid){
			fstream myfile;
			if(search(empid)){
			    myfile.open("emp.dat",ios::in | ios::out);
			    emp obj;char temp[50];
			    while(myfile.read((char*)&obj, sizeof(obj)))
			        if(empid==obj.retempid())
			        {
			            cout << "\nEnter the new password ";
			            cin>>temp;
			      		obj.setpassword(temp);
			            int pos = -1 * sizeof(obj);
			            myfile.seekp(pos, ios::cur);
			            myfile.write((char*)&obj, sizeof(obj));
			        }
			    myfile.close();
			}else throw UserNotfound();
}
void withdrow(int empid){
    fstream myfile;
			if(search(empid)){
			    myfile.open("emp.dat",ios::in | ios::out);
			    emp obj;
			    while(myfile.read((char*)&obj, sizeof(obj)))
			        if(empid==obj.retempid())
			        {
			            if(obj.retpayroll()){
			            obj.setpayroll(false);
			            int pos = -1 * sizeof(obj);
                        myfile.seekp(pos, ios::cur);
                        myfile.write((char*)&obj, sizeof(obj));
                        cout<<"\ntransaction is successful..";
                        }
                        else{
                            cout<<"\nyou have no balance";
                        }
			        }
                myfile.close();
			}else throw UserNotfound();
}
void display_all(){
	double total;
	fstream fp;
  	emp e;
  	clrscr();
  	fp.open("emp.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }
     cout<<"\n\n\t\tEmployee's\n\n";
	  cout<<"====================================================\n";
	  attributes();
	  cout<<"====================================================\n";

      while(fp.read((char*)&e,sizeof(e)))
	 {
	   e.list();
	   total += e.retsal();
	}
	cout<<"\nTotal ="<<total;
     fp.close();
}
void display_sp(int empid){
    fstream fp;
    emp temp;
    int flag=0;
    fp.open("emp.dat", ios::in);
    while(fp.read((char*)&temp,sizeof(temp)))
    	{
    	    cout<<"try";
    	 if(temp.retempid()==empid)
    		{
    		 clrscr();
    		 temp.display();
    		 flag=1;
    		 break;
    		}
    	}
    fp.close();
    if(flag==0)
     cout<<"\n\nrecord not exist";
        getch();
}
void delete_user(int empid){
			ifstream myfile;
		    emp obj;
		    if(search(empid)){
			    myfile.open("emp.dat", ios::binary);
			    ofstream outFile;
			    outFile.open("temp.dat", ios::out | ios::binary);
			    while(myfile.read((char*)&obj, sizeof(obj)))
			        if(empid!=obj.retempid())
			            outFile.write((char*)&obj, sizeof(obj));
			    myfile.close();
			    outFile.close();
			    remove("emp.dat");
			    rename("temp.dat", "emp.dat");
			}else throw UserNotfound();
}
void modify_pay(int empid){
	fstream myfile;
			if(search(empid)){
			    myfile.open("emp.dat",ios::in | ios::out);
			    emp obj;
			    while(myfile.read((char*)&obj, sizeof(obj)))
			        if(empid==obj.retempid())
			        {
			      		obj.setpayroll(true);
			            int pos = -1 * sizeof(obj);
			            myfile.seekp(pos, ios::cur);
			            myfile.write((char*)&obj, sizeof(obj));
                        cout<<"\n\nthe salary is credited..";
			        }
			    myfile.close();
			}else throw UserNotfound();

}
void pay_all(){
        fstream myfile;
        double total=0;
			    myfile.open("emp.dat",ios::in | ios::out);
			    emp obj;
			    while(myfile.read((char*)&obj, sizeof(obj)))
			    {
			        if(!obj.retpayroll()){
			    	obj.setpayroll(true);
                    int pos = -1 * sizeof(obj);
                    myfile.seekp(pos, ios::cur);
                    myfile.write((char*)&obj, sizeof(obj));
			    	total +=obj.retsal();
			    	}
			    }
			    cout<<"the total amount payed :"<<total<<endl;
}

void write(emp temp){
			ofstream myfile;
			myfile.open("emp.dat",ios::binary | ios::app);
			if (myfile.is_open())
			{
				if(!search(temp.retempid()))
					myfile.write((char*)&temp, sizeof(temp));
				else cout<<"\n employee already exist : try";
			}else throw FileNoOpened();
			myfile.close();
}
int emp_menu(int empid){
    while(1)
    {
    clrscr();
    char ch2;
    cout<<"\n\n\n\tEmployee MENU";
    cout<<"\n\n\t1.Display";
    cout<<"\n\n\t2.Modify password";
    cout<<"\n\n\t3.Withdrew ";
    cout<<"\n\n\t4.Exit ";
    cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
    ch2=getche();
    switch(ch2)
    {
      case '1': clrscr();
  	      display_sp(empid);
  	      break;
      case '2':
          clrscr();
          modify_password(empid);
          break;
      case '3':
          clrscr();
          withdrow(empid);
          getch();
  	       break;
      case '4': return 0;
      default:
        cout<<"\a";
      emp_menu(empid);
    }
    }
}
int admin_menu()
{
  while(1)
  {
    clrscr();
    char ch2;
    int num;
    cout<<"\n\n\n\tADMIN MENU";
    cout<<"\n\n\t1.CREATE EMPLOYEE";
    cout<<"\n\n\t2.DISPLAY ALL EMPLOYEE'S";
    cout<<"\n\n\t3.SEARCH ";
    cout<<"\n\n\t4.DELETE EMPLOYEE";
    cout<<"\n\n\t5.PAY A EMPLOYEE";
    cout<<"\n\n\t6.PAY ALL EMPLOYEE";
    cout<<"\n\n\t7.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
    ch2=getche();
    switch(ch2)
    {
      case '1':
          clrscr();
          emp temp;
          temp.write();
          write(temp);
          getch();
  	      break;
      case '2':
        display_all();
        getch();
          break;
      case '3':

  	       clrscr();
  	       cout<<"\n\n\tPlease Enter The EmpID : ";
  	       cin>>num;
  	       display_sp(num);
  	       getch();
  	       break;
      case '4':

  	       clrscr();
  	       cout<<"\n\n\tPlease Enter The EmpID : ";
  	       cin>>num;
          delete_user(num);
          getch();
          break;
      case '5':

  	       clrscr();
  	       cout<<"\n\n\tPlease Enter The EmpID : ";
  	       cin>>num;
  	       modify_pay(num);
  	       getch();
            break;
      case '6':
          clrscr();
          pay_all();
          getch();
          break;
      case '7':
           return 0;
      default:
        cout<<"\a";
      admin_menu();
    }
  }
}
void emplogin()
{
    int empid;
    char  pw[50];
    cout<<"Enter EmpID: ";
    cin>>empid;
    if(search(empid)){
        cout<<"Enter password: ";
        cin>>pw;
        if(verifi(empid,pw))
        {
          emp_menu(empid);
        }
        else
        cout<<"\nwrong password :";
    }
    else{
        cout<<"\nEmpid does not exists :";
        getch();
    }
}
void adminlogin(){
    char name[10], pw[10];
    cout<<"Enter username: ";
    cin>>name;
    cout<<"Enter password: ";
    cin>>pw;
    if(strcmp(name,"admin")==0&&strcmp(pw,"password")==0){
        admin_menu();
    }else {
        cout<<"\nAuthentication failed: try again ";
    }
}


int main(){
 while(1){
    clrscr();
    char ch;
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. Employee";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': clrscr();
			   emplogin();
			   getch();
			   break;
		  case '2': clrscr();
		      adminlogin();
                getch();
			    break;
		  case '3':exit(0);
                break;
		  default :cout<<"\a";
        }
 }
}

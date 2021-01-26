#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include"bonus_project.h"
#include<time.h>//This header file contains definitions of functions to get and manipulate date and time information
#include<windows.h>
#include<conio.h>                 
#include<ctype.h>                   
#include<dos.h>                    
/* .dat files DAT file contains important information for software to handle. The information contained inside a DAT file 
is usually either plain text or binary, although in rare cases you might encounter them as the actual data of a video file for programs like VCDGear or CyberLink PowerDirector.    */


/*struct Courses
{
		
};*/

struct Date
{
	int mm,dd,yy;
};

struct GPA 
{
	char sgpa[10];
	//float sgpa;
	float cgpa;
	int semFinished;
};

struct CreditHours
{
	int maxRequired = 180;
	int finished;
	int current;
	int remaining;
};

struct PaymentDetails
{
 	float amountPaid;
 	int transNumber;
 	int transBank;
	char Bankname;
 	struct Date TDate;
};

 
struct Contacts
{
	char Email[40];
	int phoneNumber;
	int mobileNumber;
};

struct Payments
{
	char fundingType[15];
	int pamentDone;
	float totalAmountPaid;
};

/*struct Birth
{
	int birthDay;
	int birthMonth;
	int birthYear;
};*/

struct Address
{
	char Country[20];
	char GoverName[20];
	char City[20];
	char AreaName[20];
	char StreetName[20];
	int PostalCode;
	int flatNumber;
	int houseNumber;
};

struct ID
{
	char IDtype[20];
	int IDnumber;
};


typedef struct students
{
	char firstName[30], midName[30], lastName[30];
	char nationality[20];
	char gender[10];
	char department[20];
	char tutor[20];
	int regNumber;
	int birthDay;
	int birthMonth;
	int birthYear;
	int tutorcode;
	int enrolmentterm;
	int enrolmentyear;
	
	
	
 //	struct Birth TBirth;
	struct GPA TGPA;
	struct CreditHours TCredithour;
	struct PaymentDetails TPaymentdeteil;
	struct Contacts TContact;
	struct Payments TPayments;
	struct Address TAddress;
	struct ID TID;
	struct Date TDate;
};

struct students Tstudent;

//***************************************************************
//      global declaration for stream object, object
//****************************************************************

COORD coord = {0, 0};

FILE *fp,*ft;//file_pointer

int choice;

char ch;

//char another='y';

char no='n';


void gotoxy (int x, int y)
{
	coord.X = x; 
	coord.Y = y; 

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void main_menu(void)
{

	system("cls");
//	int i;

	gotoxy(20,3);
	printf(" Arab Academy For Science And Technology Student Managment system \n ");
	printf("\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");


	gotoxy(20,5);
	printf("<1> Add Student   ");
	gotoxy(20,7);
	printf("<2> Display Student Information");
	gotoxy(20,9);
	printf("<3> Enter New Payment");
	gotoxy(20,11);
	printf("<4> Calculate Student GPA");
	gotoxy(20,13);
	printf("<5> Edit Student Information");
	gotoxy(20,15);
	printf("<6> Close Application");
	gotoxy(20,22);

	time_date();

	gotoxy(20,18);
	printf("Enter your choice:");
	
	ch=getche(); /* getche() = Declaration: int getche(void); This function waits for any character input 
				from keyboard. And, it will also echo the input character on to the output screen.*/
	switch(ch) 
	{	
		case '1': add_student(); break;
		case '2': display_student(); break;
		case '3': add_payment(); break;
		case '4': student_gpa_calc(); break;
		case '5': edit_student_info(); break;
		case '6':
		{
			system("cls");
			gotoxy(16,3);
			printf("\tAASTMT Management System");
			exit(0);
		}
		default:
		{
			gotoxy(10,25);
			printf("\aWrong Entry!!Please re-entered correct option");
			if(ch)
			main_menu();
		}
	}	
}

//***************************************************************
//      function to print time and date
//****************************************************************

int time_date(void) 

{
	time_t t;
	time(&t);

	printf("Date and time:%s\n",ctime(&t));  /*header file declares a set of functions,
											   macros and types to work with date and time*/
	return 0 ;
}



//***************************************************************
//      function to return to main menu
//****************************************************************

void return_main(void)
{

	{	
		gotoxy(15,20);
		printf("Press ENTER to return to main menu");
	}

	a:
	if(getche()==13) 
	main_menu();

	else
	goto a;
}


int check_reg_number(int t)  
{
	rewind(fp);
	while(fread(&Tstudent,sizeof(Tstudent),1,fp)==1)
		if(Tstudent.regNumber==t)
		return 0;  
	return 1; 

}


//***************************************************************
//      function to ADD a new student
//****************************************************************

void add_student(void)
{
	system("cls");
	int i;

	fp=fopen("students.dat","ab+");

	if(get_data()==1)
	{
		fseek(fp,0,SEEK_END);
		fwrite(&Tstudent,sizeof(Tstudent),1,fp);
		fclose(fp);
		gotoxy(21,14);
		printf("The record is sucessfully saved");
		gotoxy(21,15);
		printf("Save any more?(Y / N):");
		fflush(stdin);

		if(getche()=='n')
			main_menu();
		else if(getche()=='y')
		{
			system("cls");
			add_student();
		}
		else
		{
			gotoxy(21,15);
			printf("\aWrong Entry!!Please re-entered correct option");
		}
	}
}


//***************************************************************
//      function to get student data 
//****************************************************************

int get_data()
{
	int t;

	gotoxy(20,3);
	printf("Enter the Information Below");
	gotoxy(21,6);
	printf("Student Registration Number:\t");
	gotoxy(50,6);
	scanf("%d",&t);

	if(check_reg_number(t) == 0)
	{
		gotoxy(21,13);
		printf("\aThe Registration Number already exists\a");
		getche();
		main_menu();
		return 0;
	}

	Tstudent.regNumber=t;
	gotoxy(21,7);
	printf("Student First Name:");
	gotoxy(40,7);
	scanf("%s",Tstudent.firstName);
	
	gotoxy(21,8);
	printf("Student Middle Name:");
	gotoxy(41,8);
	scanf("%s",Tstudent.midName);

	gotoxy(21,9);
	printf("Student Last Name:");
	gotoxy(40,9);
	scanf("%s",&Tstudent.lastName);

	gotoxy(21,10);
	printf("Student Gender:");
	gotoxy(37,10);
	scanf("%s",&Tstudent.gender);

	gotoxy(21,11);
	printf("Student Nationality:");
	gotoxy(42,11);
	scanf("%s",&Tstudent.nationality);
	
	gotoxy(21,12);
	printf("Student Department:");
	gotoxy(41,12);
	scanf("%s",&Tstudent.department);
	
	gotoxy(21,13);
	printf("Student Email");
	gotoxy(39,13);
	scanf("%s",&Tstudent.TContact.Email);

	gotoxy(21,14);
	printf("Student Mobile Number");
	gotoxy(39,14);
	scanf("%d",&Tstudent.TContact.mobileNumber);

	gotoxy(21,15);
	printf("Student Country");
	gotoxy(39,15);
	scanf("%s",&Tstudent.TAddress.Country);

	gotoxy(21,16);
	printf("Student Goverment - City");
	gotoxy(39,16);
	scanf("%s%s",&Tstudent.TAddress.GoverName,Tstudent.TAddress.City);

	gotoxy(21,17);
	printf("Student Area Name - Street Name - Flat Number - House Number:");
	gotoxy(39,17);
	scanf("%s%s%d%d",&Tstudent.TAddress.AreaName,Tstudent.TAddress.StreetName,Tstudent.TAddress.flatNumber,Tstudent.TAddress.houseNumber);

	gotoxy(21,18);
	printf("Student Postal Code:");
	gotoxy(39,18);
	scanf("%d",&Tstudent.TAddress.PostalCode);

	gotoxy(21,19);
	printf("Student ID Type");
	gotoxy(39,19);
	scanf("%s",&Tstudent.TID.IDtype);

	gotoxy(21,20);
	printf("Student ID Number");
	gotoxy(39,20);
	scanf("%s",&Tstudent.TID.IDnumber);
	return 1;
}

//***************************************************************
//      function to display a student
//****************************************************************

void display_student(void)
{
	int i=0;
	int f=1;
	int j;
	system("cls");
	gotoxy(1,1);
	printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdbStudents List\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
	gotoxy(2,2);
	printf("\n NAME ============== Reg Number ===== Nationality ======== Department ====== Gender ===== ID =========== GPA     ");
	j=4;

	fp=fopen("students.dat","rb");

	while(fread(&Tstudent,sizeof(Tstudent),1,fp)==1)
	{
		gotoxy(f,j);
		printf("%s%s%s",Tstudent.firstName,Tstudent.midName,Tstudent.lastName);
		gotoxy(f+21,j);
		printf("%d",Tstudent.regNumber);
		gotoxy(f+38,j);
		printf("%s",Tstudent.nationality);
		gotoxy(f+59,j);
		printf("%s",Tstudent.department);
		gotoxy(f+77,j);
		printf("%s",Tstudent.gender);
		gotoxy(f+91,j);
		printf("%s",Tstudent.TID.IDnumber);
		gotoxy(f+106,j);
		printf("%f",Tstudent.TGPA.cgpa);
		gotoxy(108,j);
		printf("\n\n");
		j++;
	}
	fclose(fp);
	gotoxy(35,25);
	return_main();
}


//***************************************************************
//      function to Edit a student information
//****************************************************************

void edit_student_info(void)
{
	system("cls");
	int c=0;
	int d,e;

	char another='y';

	gotoxy(20,4);
	printf("\xdb\xdb\xdb\xdb\xdb Edit Student \xdb\xdb\xdb\xdb\xdb");

	while(another=='y')
	{
		system("cls");
		gotoxy(15,6);
		printf("Enter Student Registration Number to be edited:");
		scanf("%d",&d);

		fp=fopen("students.dat","rb+");
		//gotoxy(15,7);
		//printf("iam here");
		while(fread(&Tstudent,sizeof(Tstudent),1,fp)==1)//fwrite&fread(data-element-to-be-written, size_of_elements, number_of_elements, pointer-to-file);
		{
			//printf("iam here");
			if(check_reg_number(d)==0)
			{
				gotoxy(20,10);
				printf("1. Edit Student Name and Department");
				gotoxy(20,14);
				printf("2. Edit Student Contacts");
				gotoxy(20,18);
				printf("3. Edit Student Address");
				gotoxy(15,24);
				printf("Enter Your Choice");
				switch(getche())
				{
					case '1':
					{
						system("cls");
						gotoxy(15,7);
						printf("This Student is available");
						gotoxy(15,8);
						printf("Registration Number is:%d",Tstudent.regNumber);
						gotoxy(15,9);
						printf("Enter New First name:");
						scanf("%s",Tstudent.firstName);
						gotoxy(15,10);
						printf("Enter New Middle Name:");
						scanf("%s",Tstudent.midName);
						gotoxy(15,11);
						printf("Enter New Last Name:");
						scanf("%s",&Tstudent.lastName);
						gotoxy(15,12);
						printf("Enter New Departemnt:");
						scanf("%s",&Tstudent.department);
						gotoxy(15,13);
						printf("The record is modified");
						fseek(fp,ftell(fp)-sizeof(Tstudent),0);
						fwrite(&Tstudent,sizeof(Tstudent),1,fp);
						fclose(fp);
						c=1;
						break;
					}
					case '2'://Contacts
					{
						system("cls");
						gotoxy(15,7);
						printf("This Student is available");
						gotoxy(15,8);
						printf("Registration Number is:%d",Tstudent.regNumber);
						gotoxy(15,9);
						printf("Enter New Email:");
						scanf("%s",Tstudent.TContact.Email);
						gotoxy(15,10);
						printf("Enter New Phone Number:");
						scanf("%d",Tstudent.TContact.phoneNumber);
						gotoxy(15,11);
						printf("Enter Mobile Number:");
						scanf("%d",&Tstudent.TContact.mobileNumber);
						gotoxy(15,13);
						printf("The record is modified");
						fseek(fp,ftell(fp)-sizeof(Tstudent),0);
						fwrite(&Tstudent,sizeof(Tstudent),1,fp);
						fclose(fp);
						c=1;
						break;
					}
					case '3'://Address 
					{
						system("cls");
						gotoxy(15,7);
						printf("This Student is available");
						gotoxy(15,8);
						printf("Registration Number is:%d",Tstudent.regNumber);
						gotoxy(15,9);
						printf("Enter New Goverment Name - City:");
						scanf("%s%s",Tstudent.TAddress.GoverName,Tstudent.TAddress.City);
						gotoxy(15,10);
						printf("Enter New Area Name - Street Nmae:");
						scanf("%s%s",Tstudent.TAddress.AreaName,Tstudent.TAddress.StreetName);
						gotoxy(15,11);
						printf("Enter New Flat Number - House Number:");
						scanf("%d%d",&Tstudent.TAddress.flatNumber,Tstudent.TAddress.houseNumber);
						gotoxy(15,12);
						printf("Enter New Postal Code:");
						scanf("%d",&Tstudent.TAddress.PostalCode);
						gotoxy(15,13);
						printf("The record is modified");
						fseek(fp,ftell(fp)-sizeof(Tstudent),0);
						fwrite(&Tstudent,sizeof(Tstudent),1,fp);
						fclose(fp);
						c=1;
						break;
					}
				}
			}
			else if(c==0)
			{
				gotoxy(15,9);
				printf("No record found");
			}
		}
		//gotoxy(15,15);
		//printf("iam here at end");
		gotoxy(15,16);
		printf("Modify another Record?(Y/N)");
		fflush(stdin);//is used to flush the output buffer of the stream. It returns zero, if successful otherwise, returns EOF and feof error indicator is set.
		another=getche();

		/*if(getche()=='n')
			main_menu();
		else if(getche()=='y')
		{
			system("cls");
			add_student();
		}
		else
		{
			gotoxy(21,15);
			printf("\aWrong Entry!!Please re-entered correct option");
		}*/
	}
	return_main();
}

//***************************************************************
//      function to enter a student age
//****************************************************************

void student_age(void)
{
	
}

//***************************************************************
//      function to enter a student credit_hours
//****************************************************************

void student_credit_hours(void)
{
	
}

//***************************************************************
//      function to calculat a student GPA
//****************************************************************

void student_gpa_calc(void)
{
	system("cls");
	int c=0;
	int d,i;
	//int x;
	char another='y';
	float cgpa;

	gotoxy(20,4);
	printf("\xdb\xdb\xdb\xdb\xdb Calculate Student GPA \xdb\xdb\xdb\xdb\xdb");

	while(another=='y')
	{
		system("cls");
		gotoxy(15,6);
		printf("Enter Student Registration Number to be edited:");
		scanf("%d",&d);

		fp=fopen("students.dat","rb+");

		while(fread(&Tstudent,sizeof(Tstudent),1,fp)==1)
		{
			if(check_reg_number(d)==0)
			{
				gotoxy(15,7);
				printf("This Student is available");
				gotoxy(15,8);
				printf("Registration Number is:%d",Tstudent.regNumber);
				gotoxy(15,9);
				printf("Enter Student Enrolment Term:");
				scanf("%d",Tstudent.enrolmentterm);
				gotoxy(15,10);
				printf("Enter Student Tutor:");
				scanf("%s",Tstudent.tutor);
				gotoxy(15,11);
				printf("Enter Student Tutor Code:");
				scanf("%d",&Tstudent.tutorcode);
				gotoxy(15,12);
				printf("Enter GPA for 10 Semestes :");
				/*for ( i = 0,Tstudent.TGPA.cgpa=0; i < 10; i++)
				{
					scanf("%f",&Tstudent.TGPA.sgpa[i]);
					Tstudent.TGPA.cgpa+=Tstudent.TGPA.sgpa[i];
				}
				Tstudent.TGPA.cgpa/=12.0;
				Tstudent.TGPA.sgpa=Tstudent.TGPA.cgpa;*/
				for ( i = 0,cgpa=0.0; i < 10; i++)
				{
					scanf("%f",&Tstudent.TGPA.sgpa[i]);
					cgpa+=Tstudent.TGPA.sgpa[i];
				}
				cgpa/=12.0;
				Tstudent.TGPA.sgpa[i]=cgpa;
				scanf("%d",&Tstudent.tutorcode);
				gotoxy(15,13);
				printf("You are Done");
				fseek(fp,ftell(fp)-sizeof(Tstudent),0);
				fwrite(&Tstudent,sizeof(Tstudent),1,fp);
				fclose(fp);
				c=1;
			}
			else if(c==0)
			{
				gotoxy(15,9);
				printf("No record found");
			}
		}
		gotoxy(15,16);
		printf("Calculat another Student GPA?(Y/N)");
		fflush(stdin);
		another=getche();
	}
	return_main();
}

//***************************************************************
//      function to ADD a new patment
//****************************************************************

void add_payment(void)
{
	system("cls");
	//int i;

	ft=fopen("students_Payments.dat","rb+");

	//while(fread(&Tstudent,sizeof(Tstudent),1,ft)==1)
	//{
	//(fread(&Tstudent,sizeof(Tstudent),1,ft));
	gotoxy(20,3);
	printf("Enter the Information Below");
	gotoxy(21,6);
	printf("Student Registration Number:");
	gotoxy(50,6);
	scanf("%d",Tstudent.regNumber);
	//gotoxy(50,7);
	//printf("Iam here");

	gotoxy(21,7);
	printf("Bank Name:");
	gotoxy(40,7);
	scanf("%s",Tstudent.TPaymentdeteil.Bankname);

	gotoxy(21,8);
	printf("Total Paid:");
	gotoxy(40,8);
	scanf("%d",Tstudent.TPaymentdeteil.amountPaid);

	gotoxy(21,9);
	printf("Transaction Number:");
	gotoxy(40,9);
	scanf("%d",Tstudent.TPaymentdeteil.transNumber);

	fseek(ft,0,SEEK_END);
	fwrite(&Tstudent,sizeof(Tstudent),1,ft);
	fclose(ft);
	gotoxy(21,14);
	printf("The Payment saved");
	//}

	gotoxy(21,15);
	printf("Save any more?(Y / N):");
	//gotoxy(50,22);
	//printf("Iam here");

	if(getche()=='n')
		main_menu();
	else if(getche()=='y')
	{
		system("cls");
		add_payment();
	}
	else
	{
		gotoxy(21,15);
		printf("\aWrong Entry!!Please re-entered correct option");
	}
}

#include<fstream.h> //Used for data file handling
#include<conio.h> //Used for console input-output
#include<stdio.h> //Used for standard input-output functions
int hl[8]={1, 8, 14, 15, 22, 28, 29, 30}; //List of Bank Holidays in Aug 2021
ofstream fout; //For output into file
ifstream fin; //For input from file
void main()
{
	clrscr();
    int d, h, m, n, dt; //Variables to store current date, current hour, current minutes, current token number, and user inputted date
    cout<<"Welcome to ABC Bank.\nBank Timings:\n9:00 to 12:00\n13:00 to 16:00\nPlease take a screenshot of your token, date and time.\nProvide the same when entering the Bank.\n";
    fin.open("date.dat",ios::in); //Initial date to be assigned from database at the start of every day (if prev day slots are not full)
	fin>>d; //Taking current date from binary file
	fin.close();
	for (int i=0; i<8; i++) //Checks for Bank Holidays
	    {
		if (d==hl[i])
		    d++;
	    }
	fin.open("hour.dat",ios::in); //First working hour (9) to be assigned from database at the start of every day (if prev day slots not full)
	fin>>h; //Taking hour from binary file
	fin.close();
	fin.open("min.dat",ios::in); //First instance (00) to be assigned from database at the start of every day (if prev day slots not full)
	fin>>m; //Taking minutes from binary file
	fin.close();
	fin.open("token.dat",ios::in); //First instance (1) to be assigned from database at the start of every day (if prev day slots not full)
	fin>>n; //Taking current token from binary file
	fin.close();
	cout<<"Enter Appointment date: ";
	cin>>dt; //User enters required appointment date
	for (int j=0; j<8; j++) //Checks if entered date is a holiday
    {
		{
			if(dt==hl[j])
			{
				cout<<"Bank Holiday. Please try again some other day.";
				goto end; //End label at the end of program
			}
		}
	}
	if (dt<d && dt<=31) //Entered date is before current date or slots are full 
	cout<<"Slots are full. Please try again some other day.";
	else if (dt>d && dt<=31) //Entered date is yet to come
	cout<<"Slot Booking will open on "<<dt<<"/8/21";
	else if (dt>31) //Only 31 days in August
	cout<<"Invalid Date!";
	else //If current date matches entered date and slots are left
	{
	    if (m==0)
	    cout<<"Token: "<<n<<"\nTime: "<<h<<":"<<m<<m<<"\nDate: "<<d<<"/8/21"; //Printing m twice to show "00"
	    else
	    cout<<"Token: "<<n<<"\nTime: "<<h<<":"<<m<<"\nDate: "<<d<<"/8/21";
	    n++; //Token incrementation
	    if (n%4==1) //4 tokens per 30 min, then time increments
		{
		    if (h==11 && m==30) //After 11:30, next batch at 13:00 (Lunch Break)
		    h+=2;
		    else if (h==15 && m==30) //15:30 is last slot
			{
			       d++; //Next day
			       h=9; //Hours intialised to 9
			       n=1; //No. of token initialised
			}
		    else if (m==30)
		    h++; //Next hour
		    if (m==0) //"00" + 30 min
		    m+=30;
		    else //"30" min + 30 min = Next Hour ("00")
		    m-=30;
	        }	
	}
	fout.open("date.dat",ios::out);
	fout<<d; //Input date back to binary file
	fout.close();
	fout.open("hour.dat",ios::out);
	fout<<h; //Input hour back to binary file
	fout.close();
	fout.open("min.dat",ios::out);
	fout<<m; //Input minutes back to binary file
	fout.close();
	fout.open("token.dat",ios::out);
	fout<<n; //Input token number back to binary file
	fout.close();
	end: //label
	getch();
}
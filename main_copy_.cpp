#include <iostream>  // * c++ code style use
#include <stdio.h>   // * for c style code use
#include <stdlib.h>  // * standard library like dynamic memory allocation and exit macros and other..
#include <conio.h>   // * console input output
#include <windows.h> // * windows console related functions handle
#include <unistd.h>  // * for sleep function
#include <iomanip>   // * for manipulator
#include <cwchar>    // * for console font purpose
#include <string.h>  // * C style string related functions access
#include <stdbool.h> // * boolean operation
#include <math.h>    // * math operations
#include <fstream>   // * file handling functions access
#include <string>    // * C++ STL( string library) function access
#include <regex>     // * for email validation
#include <algorithm> // * for transform function access
#include <ctime>     // * for getting current date and time
#include <sstream>   // * for conversion to string
#include <vector>    // * STL DYNAMIC ARRAY used
#include <tuple>     // * for using tuples 
#include <thread>    // * using multi threading


//--------FOR-DOCUMENT PATH GETTING------/

#include <shlobj.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

#pragma comment(lib, "shell32.lib") 

//--------FOR-DOCUMENT PATH GETTING-------------/

//*if _WIN32_WINNT macro doesn't exist then conditional compilation will be done and those files will be included

#ifndef _WIN32_WINNT  
  #define _WIN32_WINNT 0x0601
  #include<wincon.h>
  #include<string>

  #endif  // user 1  e.g.DRASHTI //! EOP() seek.edit(*required) :DRASHTI DHOLA
  
  typedef struct _CONSOLE_FONT_INFOEX
  {
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT FontFamily;
    UINT FontWeight;
    WCHAR FaceName[LF_FACESIZE];
  }CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

  #ifdef __cplusplus
  extern "C"
  {
  #endif
    BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX  lpConsoleCurrentFontEx);
  #ifdef __cplusplus
  }
  #endif

//#endif // user 2 e.g.HARSHIL //! EOP() seek.edit(*required) :HARSHIL RAMANI

using namespace std; // standard namespace for  resolving naming coflicts


//***************************** APP-CLASS ***********************************/

void Debug(string t) //! EOP() seek.edit(*required) :ALL AMS TEAM
{
  cout<<endl<<t<<getch();
}

//********* GLOBAL VARIABLE **************//

bool process_flag=false;
bool email_flag=false;

/****************************************/

class APP 
{

public:

static int MODULE_CHOICE; //module selector

public:

  APP()
  { 
    //*******************GET-CURRENT-DATE**************************//

    string temp;                      // temp variable for storage
    time_t tmNow;                     // structure variable
    tmNow = time(NULL);               // set to initial zero=NULL
    struct tm t = *localtime(&tmNow); // pre defined function

    stringstream ss; // string stream class object
    ss<<t.tm_mday; // pass day
    temp = ss.str(); // it returns as string

    if(stoi(temp) < 10) // if date-day is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      temp = "0" + temp;
    }

    CUR_DATE = temp; // save to input parameter

    ss.str(""); // flush string stream class so new input can be taken

    ss<<(t.tm_mon + 1);       // pass months
    temp = ss.str();            // returns month
    CUR_DATE = CUR_DATE + "/";  // add slash  for formet dd/mm/yy

    if(stoi(temp) < 10) // if date-month is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      temp = "0" + temp;
    }

    CUR_DATE = CUR_DATE + temp; // concate to input para

    ss.str("");
    ss<<(t.tm_year + 1900);   // pass year
    temp = ss.str();            // returns year
    CUR_DATE = CUR_DATE + "/";  // add slash
    CUR_DATE = CUR_DATE + temp; // concate to input para

    ss.str(""); // flush string stream class so new input can be taken

    /*******************CURRENT-DATE**********************************/

    //*******************GET-CURRENT-TIME******************************//

    int meridiem_Flag = 0; // 0=AM 1=PM
    if(t.tm_hour > 12)    // if hours is greter than 12 then convert into 12 hour formet
    {
      t.tm_hour = (t.tm_hour - 12);
      meridiem_Flag = 1; // Flag set to show AM-PM
    }
    
    if(t.tm_hour == 00)  //for night set 24- to 12 hour format e.g. 00:24 -> 12:24
    {
      t.tm_hour = 12;
    }

    ss<<t.tm_hour; // pass Hours
    temp = ss.str(); // it returns as string
    CUR_TIME = temp;

    if(stoi(CUR_TIME) < 10) // if hours is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      CUR_TIME = "0" + CUR_TIME;
    }

    ss.str("");
    ss<<(t.tm_min);
    temp = ss.str();
    if(stoi(temp) < 10) // if minutes is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      temp = "0" + temp;
    }
    CUR_TIME = CUR_TIME + ":";  // add : to look format appropriate
    CUR_TIME = CUR_TIME + temp;

    ss.str("");

    CUR_TIME += (meridiem_Flag == 0) ? " AM" : " PM"; // AM and PM

    /*******************CURRENT-TIME*********************************/

    //**************** AMS DATABASE PATH GETTING *********************//
        
      CHAR pathDocument[MAX_PATH];   // string to store path
      HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL,SHGFP_TYPE_CURRENT,pathDocument); // getting documents path
  
      if (result == S_OK) // check if documents path is successfully stored in pathdocuments
      {
        AMS_Path = pathDocument;       // take original documents path into string
        AMS_Path = AMS_Path + "\\{JSN-1008-JSK-22-10-2021}"; // making AMS folder path
      }
      else
      { 
        scrClr();
        setCursorPos(9,24);
        cout << "DATA BASE-ERROR : 424-500-503 ";
        scrClr(2);
        exit(1);
      }
     /**************** AMS DATABASE PATH GETTING *********************/
  }

  void setCursorPos(int x, int y = 0) //? cursor position set ->IMPORTANT: relative postion is set
  {

    // vertical lines space
    while(x > 0)
    {
      cout << endl;
      x--;
    }

    // horizontal cursor space by 1 charecter
    while(y != 0)
    {
      printf(" ");
      y--;
    }
  }

  void scrClr(float i = 0.0) //?for clearing screen afer particular time
  {
    // by default set to zero with default arguements
    sleep(i);      //  going in sleep mode for particular time
    system("cls"); //  clear  the screen
  }


  void startApp() //? start Application
  {
    if(MODULE_CHOICE == 0) //* only 1 time initiaization function need to be called after then just we need ro refresh home screen 
    {
      initApp();                    // init screen first time by opening console in full screen
      
      if(!dirExists(AMS_Path.c_str()))  //? check for availability of DataBase
      { 
        scrClr();
        setCursorPos(9,24);
        cout << "DATA BASE-ERROR : 404-500-503 ";
        scrClr(3);
        exit(1);
      }

      MODULE_CHOICE = HomeScreen(); // home screen will tell which module is selected
    }
    else
    {
      MODULE_CHOICE = HomeScreen();// home screen will tell which module is selected
    }
  }

  ~APP()
  {
    
  }

private:

  void initApp() //?setting up first time APP screen by making console in full screen
  {

    // get handle to the console window
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // retrieve screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    // current window size
    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

    // current screen buffer size
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    // to remove the scrollbar, make sure the window height matches the screen buffer height
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    // set the new screen buffer dimensions
    SetConsoleScreenBufferSize(hOut, newSize);

    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    setConsoleSize(); //set full screen console

    system("color F0"); // set white background and text color black
  }

  int HomeScreen() //?ask Module choice at Home screen of APP
  {
    int line;

    gotoHomeScreen:

    Date(1,15); // current date print
    Time(0,16); // current time print

    setCursorPos(2);
    cout << setw(55) << " || ATTENDANCE MANAGEMENT SYSTEM ||" << endl; // TITLE OF APP

    string operationChoice;
   
    //build UI-Box screen of HOME SCREEN
    setCursorPos(1,15);//set cursor position
    buildVerticalWall(43);

    line = 0;
 
    while (line < 11) 
    {
      setCursorPos(1, 15);
      if (line == 1)
        buildHorizontalWall(43, "1) NEW SETUP FOR SEMESTER");
      else if (line == 3)
        buildHorizontalWall(43, "2) TAKE ATTENDANCE ");
      else if (line == 5)
        buildHorizontalWall(43, "3) CUSTOMIZED ATTENDANCE REPORT ");
      else if (line == 7)
        buildHorizontalWall(43, "4) SEARCH & UPDATE DETAILS ");
      else if (line == 9)
        buildHorizontalWall(43, "5) EXIT ");
      else
        buildHorizontalWall(43, " ");
      line++;
    }

    setCursorPos(1,15);
    buildVerticalWall(43);

    askChoice(2,30,operationChoice);
    
    //! EOP() seek.edit(*required) :  NUPUR KUKADIYA
    if(!cin) // new line(enter key input ignoring) // not necessary bcz it is set as invalid input error
    {
      cin.clear();
      cin.ignore(80, '\n');
    }

    ConvertChoiceToINT = validateString(operationChoice, 5, 1); // validate and convert choice into integer

    if (!ConvertChoiceToINT) // if wrong input then repeat process until correct input
    {
      goto gotoHomeScreen;//re-ask choice
    }

    return (ConvertChoiceToINT);//return choice
  }

  int GetDesktopResolution() //? for getting particular device size screen
  {
    int size = 22;                            // specified intial size for small screen
    RECT desktop;                             // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow(); // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)

    int horizontal = desktop.right; // horizontal
    int vertical = desktop.bottom;  // vertical

    //*setting up console inside size according to device size and resolution
    if (horizontal <= 600)
    {
      size = 30;
    }
    else if (horizontal <= 800)
    {
      size = 33;
    }
    else if (horizontal <= 1000)
    {
      size = 35;
    }
    else if (horizontal <= 1400)
    {
      size = 38;
    }
    else if (horizontal <= 1900)
    {
      size = 42;
    }
    else if (horizontal <= 2500)
    {
      size = 45;
    }
    else if (horizontal <= 3200)
    {
      size = 50;
    }
    else if (horizontal <= 4000)
    {
      size = 55;
    }
    else if (horizontal <= 4800)
    {
      size = 58;
    }

    return (size);//return size
  }

  void setConsoleSize() //? for setting up console size
  {
    CONSOLE_FONT_INFOEX cfi;  // structure variable
    cfi.cbSize = sizeof(cfi); // total bytes of cfi
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                                                  // Width of each character in the font
    cfi.dwFontSize.Y = GetDesktopResolution();                             // Height getting
    cfi.FontFamily = FF_DONTCARE;                                          // font family doesn't matter
    cfi.FontWeight = FW_NORMAL;                                            // font normally bold
    std::wcscpy(cfi.FaceName, L"JetBrains Mono Bold");                     // Choose your font BY SETTING FONT FACE
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); // pass reference of that structure to OUTPUT HANDLE
  }

protected:

  string CUR_DATE, CUR_TIME; //*CURRENT DATE TIME FOR APPLICATION
  int ConvertChoiceToINT;    //* INTEGER CONVERT VARIABLE FOR INPUT FOR APPLICATION
  string AMS_Path;           //* DATABASE PATH
  string tempStorage;        //* TEMPORARY STORAGE FOR APPLICATION VARIABLE
  string command;            //* COMMAND VARIABLE FOR SYSTEM()

  void SetColor(int ForgC) //?for setting individual text color
  {
    WORD wColor;                                      // color specifier
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // create windows handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;                  // We use csbi for the wAttributes word.
    
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      // Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut,wColor); // set console text color
    }
    
  }
  
  void buildVerticalWall(int briks) //? for making vertical side
  {
    cout<<"*";
    while(briks > 0)
    {
      cout<< "-";
      briks--;
    }
    cout<<"*";
  }

  void buildHorizontalWall(int endBrick, string tempStorage) //? for making horizontal side
  {
    cout<<"|";
    int run = 1;
    while(run < endBrick)
    {

      if (run == (endBrick / 6))
      {
        cout<<tempStorage;
        run += (tempStorage.length() - 1);
        cout<<" ";
      }
      else
      {
        cout<<" ";
      }

      run++;
    }
    cout<<"|";
  }

  int dirExists(const char *path) //?checking if directory exists or not 1=EXIST 0=NOT EXIST
  {
    struct stat info;

    if (stat(path, &info) != 0)
      return (0);
    else if (info.st_mode & S_IFDIR)
      return (1);
    else
      return (0);
  }

  void ShowConsoleCursor(bool showFlag)//? hiding or showing cursor
  {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // set handle

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
  }

  void askChoice(int h, int v, string &input) //?general choice taking function  e.g. 1,2,3,4...N
  {
    setCursorPos(h, v);      // set cursor position
    ShowConsoleCursor(true); // show the cursor
    cout << "CHOICE : ";
    fflush(stdin);            // flushing standard input buffer
    getline(cin, input);      // taking white space string input
    ShowConsoleCursor(false); // hide the cursor
  }

  int YesNoInput(string inputAsk, string &in,string t="",int color=0,int color2=0)//?take input in yes or no 
  {
    int line;
    setCursorPos(2, 17);
    buildVerticalWall(43);//set vertical line on console
    line = 0;
    //build UI-Box screen
    while (line < 3)
    {
      setCursorPos(1,17);

      if (line == 1)
      {
       if(color==0&&color2==0&&t.empty())
       {
         buildHorizontalWall(43, inputAsk); // message BOX-UI
       }
       else
       {
       cout<<"|";
       setCursorPos(0,7);
       SetColor(color);//set color
       cout<<inputAsk;
       SetColor(color2);
       setCursorPos(0,1);
       cout<<t;
       setCursorPos(0,8);
       cout<<"|";
       }

      }
      else
      {
        buildHorizontalWall(43, " ");
      }

      line++;
    }
    setCursorPos(1, 17);
    buildVerticalWall(43);
    setCursorPos(2,31);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, in);//take input
    ShowConsoleCursor(false);
    line = validateString(in); // validate input // line re used as return value storage

    return (line);//return line
  }

  void InvalidInputErr() //? invalid input error function
  {
    scrClr(0.5);//clear screen
    ShowConsoleCursor(false);
    setCursorPos(8, 26);
    SetColor(4); // set color for text individual
    cout << "INVALID INPUT ENTERTED !" << endl;
    setCursorPos(1, 20);
    cout << "PLEASE RE-ENTER YOUR INPUT CORRECTLY !" << endl;
    ShowConsoleCursor(false);
    scrClr(1);
    SetColor(0); // back to normal color
  }

  void warnMsg(string err_msg, int color, int pos,string err_msg2=" ",int color2=0,int pos2=0) //? overloaded version //?medium level Warning
  {
    scrClr();

    if(err_msg2.length() >= 20)
    {
      setCursorPos(8,pos); 
      SetColor(color);      
      ShowConsoleCursor(false);
      cout << err_msg << endl; 
      setCursorPos(1,pos2); 
      SetColor(color2);      
      cout << err_msg2 << endl;  
      scrClr(2);              // screen stops so user can read message
      SetColor(0);
    }
    else
    {
      setCursorPos(9, pos); 
      SetColor(color);      
      ShowConsoleCursor(false);
      cout << err_msg << endl; 
      scrClr(2);               // screen stops so user can read message
      SetColor(0);
    }
  }

  void MSG(string msg, string msg2, int color, int color2, int pos) //? succeed message print
  {
    
    scrClr();

    if(msg.length()<=30)//msg length is less than and equal to 30 print this msg
    {
        setCursorPos(9, pos);
        SetColor(color);
        ShowConsoleCursor(false);
        cout << msg; // mess 1 st
        SetColor(color2);
        cout << msg2; // mess 2  nd
        scrClr(2);
        SetColor(0);
    }
    else//if length is greater than 30 than print this msg
    {
        setCursorPos(8,pos);
        SetColor(color);
        ShowConsoleCursor(false);
        cout << msg; // mess 1 st
        setCursorPos(2,pos+7);
        SetColor(color2);
        cout << msg2; // mess 2  nd
        scrClr(2);
        SetColor(0);

    }
  }

  int validateString(string input, int Bnd, int start) //? string input validate as integer
  {
    int flag = 0, tem = 1;
    
    if (start == 0)
        start++;

    for(tem = start; tem <= Bnd; tem++)
    {
      if(to_string(tem) == input) // convert tem int to string to check input valid condition
      {
        flag = 1;
        break;
      }
    }

    if(flag == 0) //IF flag=0 means input is invalid
    {
      InvalidInputErr(); //error msg
      return 0;
    }
    else
    {
      return tem; //returns converted string.to_int(INT)
    }
    
  }

  int validateString(string input) //?overloaded version of validating string input of yes/no
  {
    if(input == "YES" || input == "yes" || input == "Yes")//check yes input
    {
      return 1; // yes
    }
    else if (input == "NO" || input == "no" || input == "No")//check no input
    {
      return 0; // no
    }
    else 
    {
      return -1; // error
    }
  }

  bool checkAlphaSpInput(string &input,int both=0)  //?function to check occurence of special charaters and alphabets
  {

    string list = "#%&{}\\/*>< $!:\'\"@+`|=";
    string list2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";    

    int j=0,i=0;
    bool flag=false;

    if(!both) //SELECT IF ONLY ALPHABET validation of both
    {
      
      for(i=0; i<list.length(); i++) //checking special  symbols
      {
           for(j=0;j<input.length(); j++)
           { 
             if( input[j] == list[i] )
             {   
                  flag=true;
                  break;
             }
           } 
      }

      for(i=0; i<list2.length(); i++) //checking alphabets  
      {
           for(j=0; j<input.length(); j++)
           {
             if( list2[i] == input[j] )
             {   
                 flag=true;
                 break;
             }
           } 
      }

    }
    else
    {
      for(i=0; i<list2.length(); i++) //checking alphabets only
      {
           for(j=0; j<input.length(); j++)
           {
             if( list2[i] == input[j] )
             {   
                 flag=true;
                 break;
             }
           } 
      }
    }
    
    return(flag);
  }

  void Date(int v, int h) //? current Date print function
  {
    setCursorPos(v, h);//set cursor position as vertical and horizontal
    cout << "DATE : ";
    SetColor(2);//set color as green
    cout << CUR_DATE;
    SetColor(0);//set color black
  }

  void Time(int v, int h) //? current Time print function
  {
    setCursorPos(v, h);//set cursor position as vertical and horizontal
    cout << "TIME : ";
    SetColor(2);//set color as green
    cout << CUR_TIME;
    SetColor(0);//set color black
  }

  int checkEmptyFile(string path)//?check empty file
  {
    ifstream read(path.c_str(),ios::binary);     // file opened 
    if(!read.is_open())
    {
      scrClr();
      setCursorPos(9,28);
      cout << "DATA BASE-ERROR : 404 ";
      scrClr(2);
      exit(1);
    }
    read.seekg(0,ios::end);
    int sz = read.tellg();
    read.close();
    return sz;//return size of file
  }

  void getDataFromFile(string path, string &input, int lineNo) //?get Data of given path file line in string
  {
    ifstream get(path.c_str(),ios::in); //file opened in reading mode 

    if(!get.is_open())//if file is not opened
    {  
       scrClr();
       setCursorPos(9,28);
       cout << "DATA BASE-ERROR : 404 ";
       scrClr(2);
       exit(1);
    }
    else//if file is opened
    {
      int FileLine = 1; // start from first line
      while(FileLine<= lineNo)//whille fileline is <= lineno then
      {
        getline(get,input); //get data
        FileLine++;         //increment the fileline
      }
    }
   get.close(); //file closed
  }

  void writeDataToFile(string path, string write_data) //?write string data to given path file at latest line
  {
    ofstream write(path.c_str(), ios::app); //file opened in append mode 

    if (!write.is_open())//if file is not opened 
    { 
      scrClr();
      setCursorPos(9,26);
      cout << "DATA BASE-ERROR : 203-204 ";
      scrClr(2);
      exit(1);
    }
    else
    {
      write << write_data << endl; // write data
    }
    write.close();//file closed
  }

  void replaceWithHyphen(string &str) //? in given string special symbols should be replaced by hyphen and string will be convert into UPPERCASE
  {
    int i = 0, j = 0;
    string list = "#%&{}\\/*>< $!:\'\"@+`|="; // need to be checked as these are restricated symbols

    for (i = 0; i <= list.length(); i++)//check list condition
    {
      for (j = 0; j <= str.length(); j++)//check str condition
      {
        if (str[j] == list[i])//if string and list are same
        {
          str[j] = '-'; // replace with hyphen symbol
        }
      }
    }

    transform(str.begin(), str.end(), str.begin(), ::toupper); // convert to uppercase
  }

  bool EmptyInput(string &input) //?checking if input is empty (e.g. : enter key)
  {
    if(input.empty())
    {
      return true; // if emty then returns  true
    }
    else
    {
      return false; // if not then returns false
    }
  }

  bool LengthValidation(string &input,int l) //? input string length validation
  {
    if(input.length()<=l)
    {
        return(true);//if valid then true return
    }
    else
    {   
        warnMsg("INPUT LENGTH EXCEED !",4,28);  //if invalid then return false
        return(false);
    }
  }

  bool validateEmail(string email) //?checking for email validation
  {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); //email pattern
    return regex_match(email, pattern);
  }

  void LoadingProcess() //? LOADING WINDOWS WHILE TASK PROCESSING
  {
    tempStorage.clear();
    tempStorage = "WORKING ON IT";
    do
    {
    scrClr(0.5);
    setCursorPos(9,26);
    SetColor(2);
    ShowConsoleCursor(false);
    cout << tempStorage ;
    scrClr(1);
    tempStorage = tempStorage + ".";
 
    if(process_flag)
    {
      break;
    }

    }while(true);
    
    tempStorage.clear();
    SetColor(0);
  }

  void sendToEmail(string SenderAddress,string password,string RecepientAddress,string Subject,string Msg,string AttachmentPath,string fileName) //? sending email to user
  {   
      command.clear(); // clear for re-using
  
      command = AMS_Path + "\\OTHER\\mail.py"; // make database path for email.py
  
      fstream write(command.c_str(),ios::out); // file opened in writing mode
  
      if(!write.is_open()) // if file not opened
      {  
          scrClr();
          setCursorPos(9,26);
          cout << "DATA BASE-ERROR : 201-203 ";//error 
          scrClr(2);
          exit(1);
      }
      else //CREATE EMAIL PYTHON FILE
      {   
          command.clear();
  
          //* make python code for email
  
          command ="import smtplib\nfrom email.mime.multipart import MIMEMultipart\nfrom email.mime.text import MIMEText\nfrom email.mime.base import MIMEBase\nfrom email import encoders\n\nfromaddr = \"";
          command = command + SenderAddress + "\"\ntoaddr = \"" + RecepientAddress + "\"\n"; 
          command = command + "msg = MIMEMultipart()\nmsg['From'] = fromaddr\nmsg['To'] = toaddr\nmsg['Subject'] = \"";
          command = command + Subject +"\"\nbody = \"\"\"" + Msg + "\"\"\"\nmsg.attach(MIMEText(body, 'plain'))\n";
          command = command + "filename = r\"" + AttachmentPath + "\"\n";    
          command = command + "attachment = open(filename,\"rb\")" + "\n";
          command = command + "part = MIMEBase('application', 'octet-stream')\npart.set_payload((attachment).read())\nencoders.encode_base64(part)\npart.add_header('Content-Disposition', \"attachment; filename= \%s\" \% \" " + fileName + "\")\nmsg.attach(part)\nserver = smtplib.SMTP('smtp.gmail.com', 587)\nserver.starttls() \n";
          command = command +"server.login(fromaddr, \""+ password + "\")\n";
          command = command +"text = msg.as_string()\nserver.sendmail(fromaddr, toaddr, text)\nserver.quit()\n";              
  
          write<<command; // data write to file
          write.close();// file closed
          
          command.clear();
          command = "python "+AMS_Path + "\\OTHER\\mail.py " + "1> " + AMS_Path + "\\OTHER\\output.txt 2>&1"; 
  
          system(command.c_str()); //* FILE SENDING TO EMAIL USING PYTHON CODE
          
          command.clear(); 
          command = AMS_Path + + "\\OTHER\\output.txt";

          int err = checkEmptyFile(command);
          remove(command.c_str()); // delete output/error file

          command.clear(); 
          command = AMS_Path + "\\OTHER\\mail.py"; 
  
          remove(command.c_str()); //delete py file
          remove(AttachmentPath.c_str()); //delete attachment file

          process_flag=true;

          if(err)
          email_flag=false;
          else
          email_flag=true;
          
      }

  }
  
  int validateRollNo(string input, int Bnd, int start) //? string input validate as integer
  {
     int flag = 0, tem = 1;
     
     if (start == 0)//roll no is 0
         start++;
     for(tem = start; tem <= Bnd; tem++)//roll no start with 1 and go up to boundry
     {
       if(to_string(tem) == input) // convert tem int to string to check input valid condition
       {
         flag = 1;//if condition true than flag =1
         break;
       }
     }
   
     if(EmptyInput(input)||checkAlphaSpInput(input))//empty input check 
     {
       InvalidInputErr(); // input error
       return 0;        
     } 
     else if(flag == 0) //IF flag=0 means input is invalid
     {
       MSG(" ROLL NUMBER DOESN'T EXIST !"," ",4,0,23);
       return 0; 
     }
     else
     {
       return tem; //returns converted string.to_int(INT)
     }
  
  }

};

//*---------STATIC DEFINATIONS-OF-APP---------------//

int APP::MODULE_CHOICE = 0; //? MODULE CHOICE WILL

//-------------------------------------------------//

/****************************APP-CLASS-END****************************************/

//*****************************************  MODULE-START  ************************************************/
class MODULE_GENERAL : public APP
{

private:

public:

  MODULE_GENERAL() 
  {

  }
  ~MODULE_GENERAL()
  {
    
  }

  int checkDB() //? functions for checking at least(1) database semster Records exists or not
  {
      
      if(!checkEmptyFile(AMS_Path + "\\OTHER\\semesterRecord.txt")) //check file size IF=0 -> NO RECORD IF=1 ->RECORD EXITS
      {
        warnMsg("NO SETUP EXISTS! KINDLY ADD ATLEST 1 SETUP", 4, 19); // warn msg
        return(false);
      }
      else
      {
        getSemesterRecordFile();
        ExtractStringFromBuffer();
        return (true);
      }
  }

  void askCourseChoice() //? take input choice of course for attendance
  {
    DisplayList_Input(course_name); // display list for taking input
    for(auto i = DATA.begin(); i != DATA.end(); ++i) // process to make list of semester in particular course
    {
      if(course_name == get<0>((*i)))
      {
        if(checkDuplicateRecord(LIST, get<1>((*i)))) // cheking if any duplicate records
        {
          LIST.push_back(get<1>((*i))); // making distinguished list
        }
      }
    }
  }

  void askSemsterChoice() //? take input choice of semester for attendance
  {
    DisplayList_Input(sem, 1);// display list for taking input
    for(auto i = DATA.begin(); i != DATA.end(); ++i) // process to make list of subject in particular course & semester
    {
      if(course_name == get<0>((*i)) && sem == get<1>((*i)))
      {
        if(checkDuplicateRecord(LIST, get<2>((*i))))
        {
          LIST.push_back(get<2>((*i)));
        }
      }
    }
  }

  bool askSubjectChoice() //? take input choice of subject for attendance
  { 
    DisplayList_Input(subject_name);
    getFolderPath(); // get folder path into SemPath
    
    //* below is for checking database scrambling

    if(checkEmptyFile(SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt") && checkEmptyFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt") )
    {
      return true;
    }
    else
    {
      //error part
      warnMsg(course_name +" SEM-" + sem + " " +subject_name,1,28," ERROR CODE: 206-400-412 , PLEASE DELETE & RE-CREATE IT ",4,12);
      return false;
    }
    
  }
   
  virtual int proceedFurther() //? functions for confirming to proceed for attendance
  {
    int line = 0;

    reinputforattendance:

    scrClr(0.5); 
    line = 0;

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // making path to access faculty details
    
    //*BOX-UI FOR Details confirmation

    setCursorPos(1, 7);
    buildVerticalWall(65);
    
    while(line < 13)
    {
      setCursorPos(1,7);
      if(line == 1)
      {
          getDataFromFile(command,FacultyName,1);  //get faculty name from file
          buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
      }
      else if(line == 3)
      {
          buildHorizontalWall(65, "COURSE               :  " + course_name);
      }
      else if(line == 5)
      {
          buildHorizontalWall(65, "SEM                  :  " + sem);
      }
      else if(line == 7)
      {  
          buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
      }
      else if(line == 9)
      {
          getDataFromFile(command, numberOfstudents,6); //get the number of students
          buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
      }
      else if(line == 11)
      {
        cout << "|";
        Date(0, 9);
        Time(0, 7);
        cout << setw(18) << "|";
      }
      else
        buildHorizontalWall(65, " ");
      line++;
    }
    setCursorPos(1, 7);
    buildVerticalWall(65);

    tempStorage.clear();//clear variable for re-using
    SetColor(1);
    setCursorPos(2, 23);
    cout << "DO YOU WANT TO PROCEED FURTHER ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value
    if(ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); 
      goto reinputforattendance;
    }
    return (ConvertChoiceToINT); // return confirmation for taking attendace
  }


protected:

  virtual void SetNoObj() = 0; //*WE MAKE THIS CLASS AS PURE VIRTUAL SO  OBJECT OF THIS CLASS CAN'T NOT BE CREATED IN MAIN()

  //********** MODULE_GENERAL *************/
  
  string SemPath;

  /********************************************/

  //********** FACULTY *************/

  string FacultyName;
  string FacultyEmail;
  string course_name;
  string sem;
  string subject_name;

  /********************************/

  //********** STUDENT *************/

  string student_name;
  string student_email;
  string RoLLNo;
  string numberOfstudents;

  /*******************************/


  //********MODULE-2-3************/ 

  vector<string> buffer,LIST;                           // vector buffer for file handling data receiver  LIST FOR STORE LIST CONTENT
  vector< tuple < string,string,string,string > > DATA; // search-key-value-access vector-tuple 

  /*******************************/

  

  //*************************  MODULE 2-3 **********************************//


  int checkDuplicateRecord(vector<string> vec, string search) //?for cheking if duplicate records found in vector_storage
  {
    vector<string>::iterator it; // iterator

    it = find(vec.begin(), vec.end(), search); // finding elemnt in vector

    if (it != vec.end())
    {
      return 0; // if found then return 0
    }
    else
    {
      return 1; // if not found then return 1
    }
  }

  void DisplayList_Input(string &put, int select = 0) //? display the list and take appropriate input of corse/sem/subject
  {
    int listFlag = 1, chFlag = 0, countFlag = 0, temp_flag = 1;
    auto i = LIST.begin();

    (LIST.size() > 6) ? setCursorPos(0, 10) : setCursorPos(1, 20); // set box-view for list >5 and less than 5
    buildVerticalWall(35);
    setCursorPos(1, 20);
    buildHorizontalWall(35, " ");

    while (i != LIST.end()) // dynamic list loop for sem course subject input choice
    {

      displayAgain:
      chFlag = 0;
      setCursorPos(1, 20);
      if (select == 0)
        buildHorizontalWall(35, to_string(5 * countFlag + listFlag) + ") " + (*i));
      else
        buildHorizontalWall(35, to_string(5 * countFlag + listFlag) + ") " + "Sem-" + (*i));
        
      setCursorPos(1, 20);
      buildHorizontalWall(35, " ");
      listFlag++;
      i++;

      if (listFlag > 5 && i != LIST.end())
      {

        chFlag = 1;
        countFlag++;
        setCursorPos(1, 20);
        buildHorizontalWall(35, "TYPE '+' FOR EXTENDED LIST");
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");
        setCursorPos(1, 20);
        buildVerticalWall(35);
        askChoice(2, 34, tempStorage);//ask choice
        scrClr(0.5);
        if(tempStorage == "+")//if user press +
        {
           setCursorPos(2, 20);
           buildVerticalWall(35);
           listFlag = 1;//list flag =1 
           chFlag = 0;
           setCursorPos(1, 20);
           buildHorizontalWall(35, " ");
           goto displayAgain;//again display screen
        }
        else
        {
          ConvertChoiceToINT = validateString(tempStorage, countFlag * 5, (countFlag - 1) * 5);//validatestring 
          
          if(ConvertChoiceToINT == 0)
          {
            while (temp_flag != (listFlag))
            {
              i--;
              temp_flag++;
            }
            
            temp_flag = 1;
            countFlag--;
            listFlag = 1;
            
            setCursorPos(2, 20);
            buildVerticalWall(35);

            chFlag = 0;

            setCursorPos(1, 20);
            buildHorizontalWall(35, " ");
            
            goto displayAgain;
          }
          else
          {
            break;
          }
        }
      }
    }

    if(chFlag == 0)
    {
      setCursorPos(1, 20);
      buildVerticalWall(35);
      askChoice(2, 30, tempStorage);

      if(tempStorage == "+")
      {
        InvalidInputErr();
        while(temp_flag != (listFlag))
        {
          i--;
          temp_flag++;
        }
        temp_flag = 1;
        listFlag = 1;

        setCursorPos(2, 20);
        buildVerticalWall(35);
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");

        goto displayAgain;
      }
      ConvertChoiceToINT = validateString(tempStorage, (((countFlag)*5 + listFlag - 1)), ((countFlag)*5));
      
      if(ConvertChoiceToINT == 0)
      {
        while(temp_flag != (listFlag))
        {
          i--;
          temp_flag++;
        }

        temp_flag = 1;
        listFlag = 1;

        setCursorPos(2, 20);
        buildVerticalWall(35);
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");

        goto displayAgain;
      }
      scrClr(0.5);
    }
    for(i = LIST.begin(), countFlag = 1; i != LIST.end(); ++i, countFlag++) // set data to string for searching
    {
      if(countFlag == ConvertChoiceToINT)
      {
        put = (*i);
      }
    }

    LIST.clear();        // flush vector data for re-using
    tempStorage.clear(); // flush string for re-using
  }

  void getFolderPath() //? based on input choice of course->sem-subject we find correct folder and save path  to Sem_path
  {
    for(auto i = DATA.begin(); i != DATA.end(); ++i) // process to find folder path using vector tuple we have 3 input parameter coursename , sem , subject name
    {

      if(course_name == get<0>((*i)))
        if(sem == get<1>((*i)))
          if(subject_name == get<2>((*i)))
            SemPath = get<3>((*i));
    }

    SemPath = AMS_Path + "\\" + SemPath; //* assigning searched path to SemPath and concate AMS_Path

  }

  void getSemesterRecordFile() //? get data of course-semester-sub-path records
  {
    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; // making path to AMS->OTHER->semsterRecord.txt
    fstream fin(tempStorage.c_str(), ios::in);              // file opened 

    if(!fin.is_open()) // if not opened
    {
      scrClr();
      setCursorPos(9,28);
      cout << "DATA BASE-ERROR : 404 ";
      scrClr(2);
      exit(1);
    }
    else // if opened
    {
      tempStorage.clear();       // clear for re-using
      getline(fin, tempStorage); // tempStorage used as temporary storage

      while(!fin.eof()) // data receive until file ends
      {
        buffer.push_back(tempStorage); // save that string(data) in vector
        getline(fin, tempStorage);     // fetch again from file
      }
      fin.close(); // file close
    }

    sort(buffer.begin(), buffer.end()); // sort file data in vector in Dictionary order
    tempStorage.clear();
  }

  void ExtractStringFromBuffer() //? extracting main string into substring like course - sem - sub - path
  {
    for(auto i = buffer.begin(); i != buffer.end(); ++i) // insert in to vector-tuple from vector buffer with extracting string
    {
      tempStorage = (*i);      // temp variable for moving vector tempStorage to string
      int found_pos, temp_pos; // temp variable for position storing

      found_pos = tempStorage.find("|");                // find the first occurance of '|'
      course_name = tempStorage.substr(0, (found_pos)); // get proper course name from string and save it to course_name
      temp_pos = (found_pos + 1);                       // making next finding position

      if(checkDuplicateRecord(LIST, course_name)) // checking if any duplicate course exists
      {
        LIST.push_back(course_name); // making list for input of UI screen of course select
      }

      found_pos = tempStorage.find("|", temp_pos);                // finds string till 1st pipe i.e coursename
      sem = tempStorage.substr(temp_pos, (found_pos - temp_pos)); // stores the string in TEMP_STR
      temp_pos = (found_pos + 1);                                 // searching next position

      found_pos = tempStorage.find("|", temp_pos);                         // finds string till 2nd pipe i.e. semester
      subject_name = tempStorage.substr(temp_pos, (found_pos - temp_pos)); // stores the string in TEMP_STR
      temp_pos = (found_pos + 1);                                          // searching next position

      found_pos = tempStorage.find("|", temp_pos); // finds string till 3rd pipe i.e. subjectname
      SemPath = tempStorage.substr(temp_pos);      // stores the string in TEMP_STR

      DATA.push_back(make_tuple(course_name, sem, subject_name, SemPath)); // makes a final string to display
    }

    //*clearing for reusing

    tempStorage.clear();
    course_name.clear();
    sem.clear();
    subject_name.clear();
    SemPath.clear();
  }

  virtual int studConfirmation() //?basic confirmation message for user
  {
    int line;

    reConfirm:
    scrClr(0.5);

    // BOX-UI FOR STUDENT INFO CONFIRM
    setCursorPos(5, 15);
    cout << "STUDENT ROLL NUMBER " << right << setw(4) << ": " << RoLLNo;
    setCursorPos(1, 15);
    cout << "STUDENT NAME " << right << setw(11) << ": " << student_name;
    setCursorPos(1, 15);
    cout << "STUDENT E-MAIL " << right << setw(9) << ": " << student_email;

    ConvertChoiceToINT = YesNoInput("Confirm these details (yes/no) ", tempStorage); // taking input yes/no

    if (ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); // error message
      goto reConfirm;
    }

    return (ConvertChoiceToINT); // returns confirmation value yes=1 / no=0
  }

  /***********************************************************************************************/
  
};

class MODULE_1 : public MODULE_GENERAL //?module 1 class
{

  //*=============================DATA-MEMBERS================================//

private:

public:

protected:

  //*=============================DATA-MEMBERS-END================================//

  //*=============================MEMBERS-FUNCTIONS===================================//

private:

  int createSemester() //? return 1=semester created successfully & return 0=not created
  {

    tempStorage = course_name;
    replaceWithHyphen(tempStorage); //replace with hyphen an make capital letter string

    SemPath = AMS_Path + "\\" + tempStorage + "-SEM-" + sem; // making semesterpath with coursename

    tempStorage = subject_name;
    replaceWithHyphen(tempStorage);  // make subject hyphen and uppercase
  
    SemPath = SemPath + "-" + tempStorage; // proper subject folder create

    if (!dirExists(SemPath.c_str())) // if directory not exists then create it
    {
      command = "mkdir " + SemPath; // making commad which will pass in cmd

      system(command.c_str()); // creating  directory by CMD

      //*********************  FOLDERS ***********************************************/

      command = "mkdir " + SemPath + "\\DAILY-RECORD"; // making COMMAND FOR DAILY_RECORD folder

      system(command.c_str()); // creating DAILY_RECORD directory by CMD

      command = "mkdir " + SemPath + "\\FAC-STUD-DETAILS"; // making COMMAND FOR FAC&STUD_DETAILS folder

      system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD

      command = "mkdir " + SemPath + "\\MONTHLY-REPORTS"; // making COMMAND FOR MONTHLY_REPORTS folder

      system(command.c_str()); // creating MONTHLY_REPORTS directory by CMD

      /**********************************************************************************/

      //*******************  FILES ******************************************************/

      command = "cd. > " + SemPath + "\\DAILY-RECORD\\records.txt"; // RECORDS.TXT file
      system(command.c_str());

      command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; // faculty_details.TXT file
      system(command.c_str());

      command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; // student_details.TXT file
      system(command.c_str());

      tempStorage = course_name; // re used tempStorage
      replaceWithHyphen(tempStorage);

      command = course_name + "|" + sem + "|" + subject_name + "|" + tempStorage + "-SEM-" + sem + "-";

      transform(command.begin(), command.end(), command.begin(), ::toupper); // convert to uppercase

      tempStorage = subject_name; // re used tempStorage
       
      replaceWithHyphen(tempStorage); 

      command = command + tempStorage; // command for making path for writting data to file
      
      tempStorage.clear();

      tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; //* it will keep record of each semester that is created like all data of faculty | folderName

      writeDataToFile(tempStorage, command); //*writting data to file
      return 1;                              // all above code works then returns 1 = successfully
      
      /***************************************************************************************/
    }
    else //* if that semester already exist
    {
      warnMsg("SEMSTER WITH THAT SUBJECT ALREADY EXIST !", 2, 19); 
      return 0;  // returns 0=failed as User trying to create that same folder again
    }
  }
  
  //*----------------FACULTY DETAILS CONFIRMATION AND MODIFICATION---------------------/

  int confirmation() //?basic confirmation message for user
  {
    int line;

    reConfirm:

    // cofirmation BOX-UI
    scrClr(0.5);

    setCursorPos(4, 15);
    cout << "FACULTY NAME " << right << setw(9) << ": " << FacultyName;
    setCursorPos(1, 15);
    cout << "FACULTY E-MAIL " << right << setw(7) << ": " << FacultyEmail;
    setCursorPos(2, 15);
    cout << "COURSE NAME " << right << setw(10) << ": " << course_name;
    setCursorPos(1, 15);
    cout << "SEMESTER " << right << setw(13) << ": " << sem;
    setCursorPos(1, 15);
    cout << "SUBJECT " << right << setw(14) << ": " << subject_name;
    setCursorPos(1, 15);
    cout << "NUMBER OF STUDENTS " << right << setw(3) << ": " << numberOfstudents;

    // message BOX-UI

    ConvertChoiceToINT = YesNoInput("Confirm these details (yes/no) ", tempStorage); // taking input yes/no

    if (ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); // error message
      goto reConfirm;
    }

    return (ConvertChoiceToINT); // returns basic confirmation value yes=1 / no=0
  }

  int InfoModification() //? MODIFICATIONS OF FACULTY DETAILS
  {

    int line;
    reInputOfmodchoice:

    line = 0;
    setCursorPos(1);
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;
    
    // BOX-UI OF modification information
    setCursorPos(1, 25);
    buildVerticalWall(27);

    while (line < 13) 
    {
      setCursorPos(1, 25);
      if (line == 0)
        buildHorizontalWall(27, "1) FACULTY NAME ");
      else if (line == 2)
        buildHorizontalWall(27, "2) FACULTY E-MAIL ");
      else if (line == 4)
        buildHorizontalWall(27, "3) COURSE NAME ");
      else if (line == 6)
        buildHorizontalWall(27, "4) SEMESTER ");
      else if (line == 8)
        buildHorizontalWall(27, "5) SUBJECT ");
      else if (line == 10)
        buildHorizontalWall(27, "6) NUMBER OF STUDENTS ");
      else if (line == 12)
        buildHorizontalWall(27, "7) NO CHANGE ");
      else
        buildHorizontalWall(27, " ");
      line++;
    }

    setCursorPos(1, 25);
    buildVerticalWall(27);

    askChoice(2, 32, tempStorage); // ask choice

    //! EOP() seek.edit(*required) :NUPUR KUKADIYA
    if (!cin)// new line(enter key input ignoring) // not necessary bcz it is set as invalid input error
    {
      cin.clear();
      cin.ignore(80, '\n');
    }
    ConvertChoiceToINT = validateString(tempStorage, 7, 1); // validate input

    if (ConvertChoiceToINT == 0) // if wrong input
    {
      goto reInputOfmodchoice; // repeat the process until correct input
    }
    else
    {
      return (ConvertChoiceToINT); // return the number option of modification
    }
  }

  /***************************************************************************/

  //********** STUDENT DETAILS CONFIRMATION AND MODIFICATION ****************/

  int InfoStudModification() //? MODIFICATIONS OF STUDENTS DETAILS
  {

    int line;
    reInputOfmod:

    line = 0;
    setCursorPos(3);
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;
    
    // BOX-UI FOR MODIFICATION INFORMATION OF STUDENTS
    setCursorPos(2, 25);
    buildVerticalWall(23);

    
    while (line < 7)
    {
      setCursorPos(1, 25);
      if (line == 1)
        buildHorizontalWall(23, "1) STUDENT NAME ");
      else if (line == 3)
        buildHorizontalWall(23, "2) STUDENT E-MAIL ");
      else if (line == 5)
        buildHorizontalWall(23, "3) NO CHANGE");
      else
        buildHorizontalWall(23, " ");
      line++;
    }

    setCursorPos(1,25);
    buildVerticalWall(23);

    askChoice(3,32,tempStorage);//ask choice
   
    //! EOP() seek.edit(*required) :NUPUR KUKADIYA
    if (!cin)// new line(enter key input ignoring) // not necessary bcz it is set as invalid input error
    {
      cin.clear();
      cin.ignore(80, '\n');
    }
    ConvertChoiceToINT = validateString(tempStorage, 3, 1); // validate input

    if (ConvertChoiceToINT == 0) // if wrong input
    {
      goto reInputOfmod; // re take choice of modification
    }
    else
    {
      return (ConvertChoiceToINT); // returns number option of modification
    }
  }

  /***********************************************************************************/

  void UpdateName(string &input) //?Faculty & student name update input
  {
    reinput:

    scrClr(0.5);
    setCursorPos(9, 20);
    cout << "ENTER NAME : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, input);
    ShowConsoleCursor(false);
    
    if(!LengthValidation(input,27))
    {
      goto reinput;//re-ask student name as length exceed
    }
    if (EmptyInput(input))//if input is empty than error
    {
      InvalidInputErr(); // input error
      goto reinput;//re-ask student name
    }
  }

  void UpdateEmail(string &input) //?Faculty & student email address update & input
  {
    reinputOfEmail:

    scrClr(0.5);
    setCursorPos(9, 16);
    cout << "ENTER E-MAIL : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, input);
    ShowConsoleCursor(false);
    
    transform(input.begin(), input.end(), input.begin(), ::tolower); // convert to uppercase

    if(!LengthValidation(input,29))
    {
      goto reinputOfEmail;//re-ask student email as length exceed
    }

    if(EmptyInput(input)) // EmptyInput VALIDATION
    {
      InvalidInputErr(); // input error
      goto reinputOfEmail;
    }
    else if (!validateEmail(input)) // email validation
    {
      warnMsg("INVALID E-MAIL ADDRESS !", 4, 26); //warn msg 
      goto reinputOfEmail;//re-ask email
    }
    scrClr(0.5);  //! EOP() seek.review(*required) we can remove it : ALL AMS TEAM
  }

  void EnterCourseName() //?course name input
  {
    reinputOfcourseName:

    scrClr(0.5);
    setCursorPos(9, 26);
    cout << "ENTER COURSE NAME : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, course_name);
    ShowConsoleCursor(false);

    if(!LengthValidation(course_name,27))
    {
      goto reinputOfcourseName;//re-ask course_name as length exceed
    }
    
    if (EmptyInput(course_name))//check course_name is empty or not
    {
      InvalidInputErr();//invalid input error
      goto reinputOfcourseName;//re-ask course_name
    }

    scrClr(0.5); //! EOP() seek.review(*required) we can remove it :ALL AMS TEAM
  }

  void EnterSem() //?input of semester
  {
    reinputOfsem:

    scrClr(0.5);
    fflush(stdin);
    setCursorPos(9, 26);
    cout << "ENTER SEMESTER : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, sem);
    ShowConsoleCursor(false);

    if (!validateString(sem, 10, 1)) // validate sem input
    {
      goto reinputOfsem;//re-ask sem
    }

  }
  
  void EnterSubject() //?input subject
  {
    reinputOfsubjectName:

    scrClr(0.5);
    setCursorPos(9, 26);
    cout << "ENTER SUBJECT : ";
    ShowConsoleCursor(true);
    fflush(stdin);
    getline(cin, subject_name);
    ShowConsoleCursor(false);
    if(!LengthValidation(subject_name,27))
    {
      goto reinputOfsubjectName;//re-ask subject name as length exceed
    }
    if (EmptyInput(subject_name))//check subject name is empty or not
    {
      InvalidInputErr();//invalid input error
      goto reinputOfsubjectName;//re-ask subject name
    }

  }

  void rollNo(int RollNo) //?show Roll Number
  {
    scrClr(0.5);              
    ShowConsoleCursor(false); 
    setCursorPos(9, 27);
    cout << " ROLL NUMBER : " << RollNo;
    scrClr(1); // user can read no. FOR 1 SECOND
  }

  void askNumberOfStudents() //?asking number of students
  {
    reAskNumStud:
    
    scrClr(0.5);
    setCursorPos(7, 23);
    cout << " HOW MANY STUDENTS DO YOU HAVE ? ";
    setCursorPos(4, 27);
    cout << "NUMBER OF STUDENT : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, numberOfstudents);
    ShowConsoleCursor(false);
    
    ConvertChoiceToINT = validateString(numberOfstudents, 5000, 1); //validate number of students input
    if (ConvertChoiceToINT == 0)  
    {
      goto reAskNumStud;   //take reinput of number of students
    }
  }

  public:

  MODULE_1()
  {
   command.clear();//command clear for re-use 
   tempStorage.clear();//tempStorage clear for re-use
  }

  ~MODULE_1()
  {
    command.clear();
    tempStorage.clear();
  }

  void askFacDetails() //?asking faculty details
  {

    reAskFacDet:

    EnterCourseName(); // course name input
    EnterSem();        // sem input
    EnterSubject();    // subject input

    if(!createSemester()) // semester confirmation
    {
      goto reAskFacDet; // reasking faculty details as semester already exists
    }

    askNumberOfStudents(); // number of students INPUT

    command = AMS_Path + "\\USER-INFO\\userdetails.txt"; // making path for getting data from file

    getDataFromFile(command, FacultyName, 1);  // taking faculty name  from file
    getDataFromFile(command, FacultyEmail, 2); // taking  faculty email  from file

    confirmAgain: 

    if(confirmation()) // basic confirmation dialog if yes then semester folder create
    {
      command = SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; // path making for writting into file

      // writting faculty data to files

      writeDataToFile(command, FacultyName);
      writeDataToFile(command, FacultyEmail);
      writeDataToFile(command, course_name);
      writeDataToFile(command, sem);
      writeDataToFile(command, subject_name);
      writeDataToFile(command, numberOfstudents);
    }
    else
    {
      scrClr(0.5); // clear screen so flickring won't happen

      switch(InfoModification()) // which details do you want to update that function returns
      {       // each function is called according to requirement
              case 1:
              {
                UpdateName(FacultyName);//update faculty Name
                break;
              } 
              case 2:
              {
                UpdateEmail(FacultyEmail);//update faculty email
                break;
              }
              case 3:
              {
                EnterCourseName();//course Name
                break;
              }
              case 4:
              {
                EnterSem();//semester
                break;
              }
              case 5:
              {
                EnterSubject();//subject
                break;
              }
              case 6:
              {
                askNumberOfStudents();//total number of students
                break;
              }
              case 7:
              {
                scrClr(0.5);
                break;
              }

              }
             goto confirmAgain; // ask user to final confirmation
     }
  }

  void askStudDetails() //? asking students details
  {
    int ROLLNO = 0;
    while (ROLLNO < stoi(numberOfstudents)) // functions for taking student data input roll no wise
    {
      ROLLNO++;

      rollNo(ROLLNO);             // for take input of roll no
      UpdateName(student_name);   // for take input of student name
      UpdateEmail(student_email); // for taking input of email

      confirmAgain: // final confirmation
      RoLLNo = to_string(ROLLNO);//convert ROLLNO integer to string

      if (studConfirmation()) // basic confirmation dialog if yes then semester folder create
      {
        command = SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; // path making for writing into file
        RoLLNo = to_string(ROLLNO);                                                 // rollNo Int to string
        tempStorage = RoLLNo + "|" + student_name + "|" + student_email;            // folder name
        writeDataToFile(command, tempStorage);                                      // writing data to files
      }
      else
      {
        scrClr(0.5); // clear screen so flickring won't happen

        switch (InfoStudModification()) // which details do you want to update that function returns
        {
            case 1:
            {
              UpdateName(student_name);//student name modification
              break;
            }
            case 2:
            {
              UpdateEmail(student_email);//student email modification
              break;
            }
            case 3:
            {
              scrClr(0.5);
              break;
            }
        }
        goto confirmAgain; // ask user to final confirmation
      }
    }
  }

  void SetUpSucceed() // module 1 successfully worked
  {
    tempStorage = course_name + " SEM " + sem + " " + subject_name;
    MSG(tempStorage," SET UP SUCCESSFUL ", 2, 0, 20);// succeed msg
  }

  protected:

  void SetNoObj()
  {
    //* by empty defination of pure virtual function here we are restricating creation of parent class
  }

  //*==============================MEMBERS-FUNCTIONS===================================//
};

class MODULE_2 : public MODULE_GENERAL //?module 2 class
{

  //******************************** DATA-MEMBERS **********************************/

private:


public:

  static int AT_OPTION_CHOICE; // attendance taking option select

protected:

  //*********************************************************************************/

  //******************************** MEMBER-FUNCTIONS *********************************/

private:


  bool checkExistRollNo(string &Attendance,string rl,char AT,int select=0)//?checking if same roll no exist in the list
  {
    if(Attendance[(stoi(rl)-1)]==AT)//if user entered roll no is already exist in list
    {
      if(select==0)
        MSG("ROLL NUMBER ALREADY ","EXISTS IN THE LIST!",2,2,19);//print error msg
      else
        MSG("ROLL NUMBER DOESN'T ","EXIST IN THE LIST!",2,2,20);//else print doesn't exist
      return true;
    }
    else
    {
      return false;
    }
  } 
  
  /*//! EOP() seek.review(*required) there is no use of it : ALL AMS TEAM
  int ValidateAttendance(string &input) //?attendance validation to mark either P or A
  {
    for(int i = 0; i < input.length(); i++)
    {
      input[i] = toupper(input[i]);//input string covert into uppercase
    }
    if(input == "P" || input == "A")
    {
      return 1;//return true
    }
    else
    {
      return 0;//return false
    }
  }
  */
  void ListOfAttendance(string &Attendance, int choice) // ? Final List for absent / present student
  {
    int i,spacing_flag=0,space=1;
    
    if(choice == 3)
    {
      setCursorPos(2,24);
      cout << "|| LIST OF PRESENT ROLL NUMBER ||" << endl; // present list
      setCursorPos(1,1);
      SetColor(1); 

            for(i = 0;i < Attendance.length(); i++)//full list
            {
               if(Attendance[i] == 'P')
               { 
                 if(space>=49&&space<=53) //new line &space logic
                    spacing_flag=1;
       
                 if(spacing_flag==0)
                 {
                  cout << i + 1 << " ";
                  if(i<10)
                  space++;
                  else if(i<100)
                  space+=2;
                  else if(i<1000)
                  space+=3;
                  else if(i<10000)
                  space+=4;
                 }
                 else
                 {
                   setCursorPos(1,1);
                   spacing_flag=0;
                   space=-2;
                   cout << i + 1 << " ";
                   if(i<10)
                   space++;
                   else if(i<100)
                   space+=2;
                   else if(i<1000)
                   space+=3;
                   else if(i<10000)
                   space+=4;
                  }
               }
            }
       
    }

    else if(choice == 4)
    {
      setCursorPos(2,24);
      cout << "|| LIST OF ABSENT  ROLL NUMBER ||" << endl; // absent list
      setCursorPos(1,1);
      SetColor(4);
      
             for(i = 0; i < Attendance.length(); i++)
             {
               if(Attendance[i] == 'A')
               {
                    
                    if(space>=49&&space<=53)
                    {spacing_flag=1;}
       
                    if(spacing_flag==0)
                    {
                      cout << i + 1 << " ";
                      if(i<10)
                      space++;
                      else if(i<100)
                      space+=2;
                      else if(i<1000)
                      space+=3;
                      else if(i<10000)
                      space+=4;      
                    }
                    else
                    { 
                      setCursorPos(1,1);
                      spacing_flag=0;
                      space=-2;
                      cout << i + 1 << " ";
       
                      if(i<10)
                      space++;
                      else if(i<100)
                      space+=2;
                      else if(i<1000)
                      space+=3;
                      else if(i<10000)
                      space+=4;
                    }
               }
             }
            

      
    }

    SetColor(0);

  }

  bool ModificationOfAttDATA(string &Attendance,int choice) // ? modify the attendance data
  {    
      int Empty_flag=0,i;
      bool return_flag=false;
   
      command.clear(); 


      while(true)
      {    
           MDAgain:
           scrClr(0.5);
 
           setCursorPos(1,26);
           SetColor(2);
           cout << "PRESS '*' TO PROCEED FURTHER" ;
           SetColor(0);
         
           ListOfAttendance(Attendance,choice);//show list of student  attendance data
          
           setCursorPos(2,10);
           //ask if you want to modify
           if(choice == 3)
              cout << " ENTER ROLL NUMBER THAT YOU WANT TO MARK AS ABSENT  : ";
           else if(choice == 4)
              cout << " ENTER ROLL NUMBER THAT YOU WANT TO MARK AS PRESENT : ";
         
           ShowConsoleCursor(true);
           fflush(stdin);//flushing standard input buffer
           getline(cin,command);//take input
           ShowConsoleCursor(false);
           if(command=="*")
           {    
               return_flag=true;
               break;
           }

           ConvertChoiceToINT = validateRollNo(command,stoi(numberOfstudents), 1);//validate string
           
           if(ConvertChoiceToINT)
           {
             if(choice == 3)//if choice is prasent
             {
               if(checkExistRollNo(Attendance,command,'A',1))//check roll no is already exist then print error
               goto MDAgain;//go to list shown again
               else
               Attendance.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
             }
             else if(choice == 4)//if choice is absent
             {
               if(checkExistRollNo(Attendance,command,'P',1))//check roll no is aleady exist then print error
               goto MDAgain;//go to list shown again
               else
               Attendance.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
             }
           }

           Empty_flag=0;//flag set as 0
           i=0;//i  set as 0

           if(choice == 3)//if choice is present
           {
             while(i<=Attendance.length())
             {
               if(Attendance[i]=='P')
               {
                 Empty_flag=1;//flag is true
                 break;
               }
               Empty_flag=0;//else flag set as 0
               i++;
             }
           }
           else if(choice == 4)//if choice is absent
           { 
             while(i<=Attendance.length())
             {
               if(Attendance[i]=='A')
               {
                 Empty_flag=1;//flag set as true
                 break;
               }
               Empty_flag=0;//else flag is 0
               i++;
             }
           } 
           if(!Empty_flag)//if flag is false
           {     
                   
             if(choice == 3)//if choice is present than
              MarkAP_A(2); // all absent
             else if(choice ==4)//if choice is absent than
              MarkAP_A(1); //all present
              return_flag = false;//flag set 0
              break;
           }
           
      }

      return(return_flag);//return flag
      
  }

  int countLinesOfFile(string FilePath) //? function for counting lines in text file
 {   
     string data; // store data temp variable
     int lines=0; // to store the lines
     ifstream read(FilePath.c_str(),ios::in); // reading mode file opened
     if(!read.is_open()) 
     {
        scrClr();
        setCursorPos(9,28);
        cout << "DATA BASE-ERROR-404 ! ";//error
        scrClr(2);
        exit(1); 
     } 
     else
     {   
         getline(read,data); // take first line
         while(!read.eof())
         {
             lines++;
             getline(read,data);
         }
         lines++;
         read.close();
     }
     return(lines);
 } 

  void submitAttendanceToDB(string & Attendance) // ? Finally data sent to database
  {
    string sz;
    command.clear();
    command = SemPath + "\\DAILY-RECORD\\records.txt"; // making path for file handling
  
    if(!checkEmptyFile(command)) // first time write data into database for each course-sem-semester
    {
      sz = CUR_DATE + "|" + CUR_TIME + "|" + Attendance;
      writeDataToFile(command,sz);
    }
    else
    {
      sz = "\n" + CUR_DATE + "|" + CUR_TIME + "|" + Attendance;
      writeDataToFile(command,sz);
    }
     
  }


  int MarkAP_A(int choice) //? function to mark all students present/absent at once
  {
      //variable clear for re-use
      tempStorage.clear();
      command.clear();

      for(int i = 1; i <= stoi(numberOfstudents); i++) //*intial data 
      {
        if(choice == 1)
          tempStorage += "P"; // all present
        else if(choice == 2)
          tempStorage += "A"; // all absent
      }
      
      confirm:

      if(choice == 1)//if all student are present 
      {

        scrClr();
        setCursorPos(5, 14);
        ShowConsoleCursor(false);
        
        SetColor(0);
        cout << "ALL ";

        SetColor(2);
        cout << numberOfstudents;

        SetColor(0);
        cout << " STUDENTS ON ";

        SetColor(2);
        cout << CUR_DATE;

        SetColor(0);
        cout << " WILL BE MARKED AS PRESENT";
        
      }
      else if(choice == 2)//if all students are absent
      {
        scrClr();
        setCursorPos(5, 14);
        ShowConsoleCursor(false);
        
        SetColor(0);
        cout << "ALL ";

        SetColor(2);
        cout << numberOfstudents;

        SetColor(0);
        cout << " STUDENTS ON ";

        SetColor(2);
        cout << CUR_DATE;

        SetColor(0);
        cout << " WILL BE MARKED AS ABSENT";
        
      }

      setCursorPos(3); 
      //confirm msg 
      if(choice==1)//all students are present then confirm this details with yes /no in
      {
        ConvertChoiceToINT = YesNoInput("ALL PRESENT !", command,"ARE YOU SURE ?",1);
      }
      else if(choice==2)//all students are absent then confirm this details with yes /no in
      {
        ConvertChoiceToINT = YesNoInput("ALL ABSENT  !", command,"ARE YOU SURE ?",1);
      }
      if(ConvertChoiceToINT == -1)//if choice is not yes/no then print error
      {
        InvalidInputErr();
        goto confirm;//go to confirm again
      }

      if(ConvertChoiceToINT == 1)//if choice is yes then submit this details
        submitAttendanceToDB(tempStorage);//submit 

  return (ConvertChoiceToINT);//return user input
}

int EnterPR_AR(int choice) // ? function for manually entering absent / present numbers
{

      int i,Empty_flag=0,count=1;
      bool flag=true;
      bool CC_flag=true;
      
      tempStorage.clear();
      command.clear();

      string MCH;

      for(i = 1; i <= stoi(numberOfstudents); i++) 
      {
        // fill up all data with all absent / all present by default initially
        if (choice == 3)
          tempStorage += "A";
        else if (choice == 4)
          tempStorage += "P";
      }
        if(choice == 3)//if choice is present
        {
          while(i<=tempStorage.length())
          {
            if(tempStorage[i]=='P')//fill up data with present
            {
              Empty_flag=1;//empty flag true
              break;
            }
            Empty_flag=0;//else empty flag false
            i++;
          }
        }
        else if(choice == 4)//if choice is absent
        {
          while(i<=tempStorage.length())
          {
            if(tempStorage[i]=='A')//fill up with absent
            {
              Empty_flag=1;//flag set as true
              break;
            }
            Empty_flag=0;//else 0
            i++;
          }
        }

   
      while(true)
      {
         
         reInput:
         
         scrClr(0.5);
         
         setCursorPos(1,26);
         SetColor(2);
         cout<<"PRESS '*' TO PROCEED FURTHER";
         SetColor(0);         

         ListOfAttendance(tempStorage,choice);//show list of students
        
         setCursorPos(2,25);
         
         if(choice == 3)
            cout << "ENTER PRESENT ROLL NUMBER : ";
         else if(choice == 4)
            cout << "ENTER ABSENT ROLL NUMBER  : ";
         
         ShowConsoleCursor(true);
         fflush(stdin);
         getline(cin, MCH);//take input
         ShowConsoleCursor(false);
        
         if(MCH=="*")//if user press *
         {  
            
           if(!Empty_flag)//flag is 0
           {   
             
               if(choice == 3)//choice is present
               {
                scrClr(0.5);
                setCursorPos(9,19);//set cursor
                SetColor(1);
                cout << "KINDLY ADD PRESENT ROLL NUMBERS TO LIST !"<< endl; //warn message
                scrClr(1);
                SetColor(0);
                goto reInput; //re-ask roll no
               }
               else if(choice == 4)//if choice is absent
               {
                scrClr(0.5);
                setCursorPos(9,19); 
                SetColor(4);
                cout << "KINDLY ADD ABSENT  ROLL NUMBERS TO LIST ! " << endl; //warn message
                scrClr(1);
                SetColor(0);
                goto reInput;
               }
           }
           else  
           {
             break;
           }
            
         }
             
          ConvertChoiceToINT = validateRollNo(MCH, stoi(numberOfstudents), 1);//validate string
          
          if(ConvertChoiceToINT)
          {
            count++;
            if(choice == 3)
            {
              if(checkExistRollNo(tempStorage,MCH,'P')) // check exist warning present
              goto reInput;
              else
              tempStorage.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
              
            }
            else if(choice == 4)
            {
              if(checkExistRollNo(tempStorage,MCH,'A')) // check exist warning absent
              goto reInput;
              else
              tempStorage.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
            }
              
          }

          if((count-1)==tempStorage.length())
          {
            break;
          }
          
          Empty_flag=0;//set flag as 0
          i=0;

          if(choice == 3)
          {
            while(i<=tempStorage.length())
            {
              if(tempStorage[i]=='A')//set absent
              {
                Empty_flag=1;//set flag as 1
                break;
              }
              Empty_flag=0;//set flag as 0
              i++;
            }
         }
         else if(choice == 4)//if choice is absent
         {
           while(i<=tempStorage.length())
           {
             if(tempStorage[i]=='P')//if tempstorage == p
             {
               Empty_flag=1;//set flag as 1
               break;
             }
             Empty_flag=0;//set flag as 0
             i++;
           }
         }
      
       
      }

      confirm:
      scrClr(0.5);
      
      ListOfAttendance(tempStorage,choice);//list Attendance
      
      command.clear();
      
      setCursorPos(4,14);//set cursor position
      ConvertChoiceToINT = YesNoInput(" DO YOU CONFIRM THESE NUMBERS ? ", command);//confirm msg
      if(ConvertChoiceToINT == -1)//if choice is not yes or no
      {
        InvalidInputErr();//error
        goto confirm;//re-confirm
      }
      else if(ConvertChoiceToINT == 0)//if choice is no than modify
      {
        if(ModificationOfAttDATA(tempStorage,choice))//modifiction
        {
        goto confirm;//re-ask confirm
        }
        else
         flag=false;
      }

      if(ConvertChoiceToINT == 1&&flag==true)//choice is yes
      {
        submitAttendanceToDB(tempStorage);//submit
      }

      
  return (ConvertChoiceToINT);//return choice
}

  public:

    MODULE_2()
    {
      //clear variable for re-use
      command.clear();
      tempStorage.clear();
      buffer.clear();
      LIST.clear();
      DATA.clear();
    }

    ~MODULE_2()
    {
      buffer.clear(); // clearing buffer
      LIST.clear();   // clearing List
      command.clear(); // clearing command
      tempStorage.clear(); // clearing tempstorage
      DATA.clear(); // clearing DATA
    }

    int condfirmTodayAttendance()
    {
      ConvertChoiceToINT = 1; // re-used
  
      command.clear();
      tempStorage.clear();

      command = SemPath + "\\DAILY-RECORD\\records.txt";//path stored in command var
      getDataFromFile(command,tempStorage,countLinesOfFile(command));
      
        tempStorage = tempStorage.substr(0, tempStorage.find("|"));
        if(tempStorage == CUR_DATE) // to avoid taking attendance for the same day
        {
          command.clear();
          command = course_name + " SEM " + sem + " " + subject_name;
  
          scrClr();
          setCursorPos(8,25);
          ShowConsoleCursor(false);
          SetColor(2);
          cout << command;
          SetColor(0);
          setCursorPos(2,18);
          cout << " ATTENDANCE FOR ";
          SetColor(1);
          cout << CUR_DATE;
          SetColor(0);
          cout << " IS ALREADY TAKEN!";
          command.clear();
          ConvertChoiceToINT=0;
          scrClr(2);
      
     }
      return(ConvertChoiceToINT);//return 
    }

    void AttendanceOptionWindow() //? to display window with 4 Options of attendance
    {
      int line;
      command.clear();
      tempStorage.clear();

      reAskAtdM:
      
      // build UI-Box screen
      scrClr(0.5);
      setCursorPos(4, 18);
      buildVerticalWall(43);
      line = 0;

      while(line < 9) 
      {
        setCursorPos(1, 18);
        if (line == 1)
          buildHorizontalWall(43, "1) MARK ALL PRESENT ");
        else if (line == 3)
          buildHorizontalWall(43, "2) MARK ALL ABSENT ");
        else if (line == 5)
          buildHorizontalWall(43, "3) ENTER PRESENT ROLL NUMBER ");
        else if (line == 7)
          buildHorizontalWall(43, "4) ENTER ABSENT ROLL NUMBER ");
        else
          buildHorizontalWall(43, " ");
        line++;
      }
      setCursorPos(1, 18);
      buildVerticalWall(43);

      askChoice(2, 30, tempStorage); // take input

      ConvertChoiceToINT = validateString(tempStorage, 4, 1); // validate and convert to integer

      if (!ConvertChoiceToINT) // repeat process on wrong input
      {
        goto reAskAtdM;
      }

      AT_OPTION_CHOICE = ConvertChoiceToINT;//string store in static variable

    }

    int takeAttendance(int choice) //? select appropriate option for taking attendace
    {
      int process_flag = 0;

      if(choice == 1 || choice == 2)//if choice is all present or all absent
      {
        process_flag = MarkAP_A(choice);//choice is stored in process flag
      }
      else if(choice == 3 || choice == 4)
      {
        process_flag = EnterPR_AR(choice);
      }

      return (process_flag);//return flag
    }
    void AttendanceTakenSuccessfully() //? module 2 successfully worked
    {
      tempStorage.clear();
      tempStorage = course_name + " SEM " + sem + " " + subject_name;//folder name stored in tempstorage
      MSG("ATTENDANCE TAKEN OF ", tempStorage, 2, 0, 20);//print msg
    }

    protected:

    void SetNoObj()
    {
      //? by empty defination of pure virtual function here we are restricting creation of parent(GENERAL MODULE) class
    }
    //************************************************************************************/
  };

//*---------------------------STATIC DEFINATIONS-MODULE-2------------------------------/

int MODULE_2::AT_OPTION_CHOICE;  //ATTEDANCE OPTION-CHOICE ALL AUTO / ENTER MANUAL;

//-----------------------------------------------------------------------------------/

class MODULE_3 : public MODULE_GENERAL //?module 3 class
{

    //*=============================DATA-MEMBERS================================//

    private:
    
    string date;
    string time;
    string attendance;
    string pdfName; 

    public:

    static int CUS_REPORT_CHOICE; // REPORT CHOICE DATE / STUDENT

    protected:

  //*=============================DATA-MEMBERS-END================================//

  //*=============================MEMBERS-FUNCTIONS===================================//

  private:

  bool dateValidation(string date) //?  date validation
  {
       match_results<string::const_iterator> m;
       regex d("^(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\\d\\d"); //date pattern
       if(regex_match(date,m,d)) // if match
       {
          return(true); // matches then return true
       }
       else
       {
         return(false); // if not then return false
       }
  }

  bool DateInput() //? taking date input
  {
     reAskDate:

     date.clear(); //clear for re-using

     scrClr(0.5);
     fflush(stdin);
     setCursorPos(9,22);
     cout << "Enter Date ";
     SetColor(2);
     cout<<"(DD/MM/YYYY)";
     SetColor(0);
     cout<<" : ";
     SetColor(1);
     getline(cin,date);
     SetColor(0);
     //! EOP() seek.review(*required) :ALL TEAM AMS_Path
     /*
     date input pr proper accurate related error we can give so think on that at last 
     */
     //? review please at last

     if(EmptyInput(date)||(!dateValidation(date))) //validating date
     {
       scrClr(0.5);
       InvalidInputErr();
       goto reAskDate;
     }
     if(!IfDateExistThenGetData(date)) // if valid and exists then get data
     { 
        goto reAskDate;
     }
     
     if(tempStorage=="false") // logic for if date valid and record not exist then return to home screen
     return(true);
     else
     return(false);
  } 

  bool IfDateExistThenGetData(string dt) //? if date valid & exist in DATABASE then get data of that date
  {
    command.clear();
    tempStorage.clear();
    buffer.clear();
    DATA.clear();   
   
    string d,m,y;
    int found_pos,temp_pos;
    bool flag=true;
  
    //validation format DD/MM/YYYY

    found_pos = dt.find("/");   
    d = dt.substr(0,found_pos);
    temp_pos = (found_pos + 1);

    found_pos = dt.find("/",temp_pos);
    m = dt.substr(temp_pos,(found_pos-temp_pos));
    temp_pos = (found_pos + 1);

    found_pos = dt.find("/",temp_pos);
    y = dt.substr(temp_pos);
    

    //validation of leap year and all that related stuff
    if(stoi(d)<1||stoi(d)>31)
    {
      flag = false;
    }
    else if(stoi(m)<1||stoi(m)>12)
    {
      flag = false;
    }
    else if(stoi(y)<2021||stoi(y)>9999) //! EOP() seek.edit(*required) this need to be change at EOP() to 2022 year : ALL TEAM AMS
    { 
      flag = false;
    }
    else if(stoi(d)>29&&stoi(m)==2)
    {
    	flag = false;
    }
    else if((stoi(d)==31) && (stoi(m)==4||stoi(m)==6||stoi(m)==9||stoi(m)==11))
    {
    	flag = false;
    }
    else if((stoi(d)==29&&stoi(m)==2)&&((stoi(y)%100==0&&stoi(y)%400!=0)||(stoi(y)%4!=0)))
    {
    	flag = false;
    }
  
    if(flag)
    {  

      command = SemPath + "\\DAILY-RECORD\\records.txt";//path stored in command var
      ifstream fin(command.c_str(), ios::in);//file open

      if(!fin.is_open())
      {  
        scrClr();
        setCursorPos(9,28);
        cout << "DATA BASE-ERROR : 404 ";
        scrClr(2);
        exit(1);
      }
      else
      {
            fflush(stdin);
            command.clear();
            getline(fin,command);
            buffer.push_back(command);
            
            while(!fin.eof()) // data receive until file ends
            {
              getline(fin, command);     // fetch again from file
              buffer.push_back(command); // save that string(data) in vector
            }

           
           //extracting data from buffer
            for(auto i = buffer.begin(); i != buffer.end(); ++i)
            { 
              tempStorage = (*i);
              found_pos = tempStorage.find("|");
              
              d = tempStorage.substr(0,found_pos);
              temp_pos = (found_pos+1);
    
              found_pos = tempStorage.find("|", temp_pos);
              time = tempStorage.substr(temp_pos,(found_pos-temp_pos));
              temp_pos = (found_pos+1);
      
              found_pos = tempStorage.find("|", temp_pos);
              attendance = tempStorage.substr(temp_pos);
      
              DATA.push_back(make_tuple(d,time,attendance,""));
            }
           
           // get exact match of that input date
            for(auto i = DATA.begin(); i != DATA.end(); i++) 
            {
              
              if(dt == get<0>((*i)))
              {
                time = get<1>((*i));
                attendance = get<2>((*i));
                flag = true;
                tempStorage.clear();// re use as flag return to home screen value store
                tempStorage = "false"; // no return and further process for report making
                break;
              }
              flag = false;
            }
           
          fin.close();  
       }
       if(!flag)
       {
       scrClr(0.5);
       setCursorPos(9,22);
       ShowConsoleCursor(false);
       SetColor(0);
       cout << "REPORT FOR ";
       SetColor(2);
       cout << date;
       SetColor(0);
       cout << " DOESN'T EXIST !";
       scrClr(2);
       flag=true;
       tempStorage.clear();// re use as flag return to home screen value store
       tempStorage = "true"; //yes return to home screen
       }

    }
    else
    {
      scrClr(0.5);
      warnMsg("INVALID DATE / DATE FORMAT !!!",4,25); //error
    }

    return(flag);  
  } 

  void makeDateReport() //?make Date Wise Report
  {
       command.clear();
       tempStorage.clear();

       int j=1,found_pos,temp_pos;
      
       command = SemPath + "\\DAILY-RECORD\\fac_data.txt";
      
       tempStorage = "[Attendance taken on] : [ " + date + " ] [ " + time + " ] ";
       writeDataToFile(command,tempStorage);
       
       tempStorage = "1) FACULTY NAME : " + FacultyName;
       writeDataToFile(command,tempStorage);
       
       tempStorage = "2) COURSE NAME  : " + course_name;
       writeDataToFile(command,tempStorage);
       
       tempStorage = "3) SEMSTER : " + sem;
       writeDataToFile(command,tempStorage);
       
       tempStorage = "4) SUBJECT NAME : " + subject_name;
       writeDataToFile(command,tempStorage);
         
       tempStorage = "[Attendance Data] : ";
       writeDataToFile(command,tempStorage);  
      
      
      while(j<=stoi(numberOfstudents))
      { 
        tempStorage.clear();
        found_pos=temp_pos=0;
        command.clear();
        time.clear();

        command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";
        getDataFromFile(command,tempStorage,j);

        found_pos = tempStorage.find("|");
        time = tempStorage.substr((found_pos+1),(tempStorage.find("|",(found_pos+1))-2)); //time re used as student name
    
        command = SemPath + "\\DAILY-RECORD\\stud_name.txt";
        writeDataToFile(command,time);

        time.clear(); 
        command.clear();
        command = SemPath + "\\DAILY-RECORD\\stud_att"+".txt";

        if(attendance[j-1]=='P')
        {writeDataToFile(command,"Present");}
        else
        {writeDataToFile(command,"Absent");}
        j++;
      }

  }

  bool RollNoInput() //? take roll number input
  {
    rollNoReInput:

    scrClr(0.5);
    RoLLNo.clear();    

    setCursorPos(9,22);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout<<"ENTER ROLL NUMBER OF STUDENT : ";
    getline(cin,RoLLNo);
    ShowConsoleCursor(false);

    ConvertChoiceToINT =  validateRollNo(RoLLNo,stoi(numberOfstudents), 1);//validate roll number
    
    if(!ConvertChoiceToINT)
    {   
        goto rollNoReInput;
    }

    getStudentData(); //get data of that student

    return(true);
  }

  void getStudentData() //? get student data of that particular roll number
  {
    command.clear();
    tempStorage.clear();

    int found_pos,temp_pos;
    
    command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";//path for access student data file
    
    getDataFromFile(command,tempStorage,stoi(RoLLNo));
      
    found_pos = tempStorage.find("|");
    temp_pos = (found_pos+1);
  
    found_pos = tempStorage.find("|", temp_pos);
    student_name = tempStorage.substr(temp_pos,(found_pos-temp_pos));
    temp_pos = (found_pos+1);

    found_pos = tempStorage.find("|", temp_pos);
    student_email = tempStorage.substr(temp_pos);
  
  }
  
  int studConfirmation() //? student confirmation  function (also available in general module as virtual)
  {
    tempStorage.clear();

    int line;

    reAsk:
  
    scrClr(0.5);

    line=0; 
    setCursorPos(2, 7);
    buildVerticalWall(65);
                        
    while(line < 7)
    {
        setCursorPos(1,7);
                  
        if(line == 1)
        {
            buildHorizontalWall(65, "STUDENT ROLL NUMBER     :  " + RoLLNo);
        }
        else if(line == 3)
        {  
            buildHorizontalWall(65, "STUDENT NAME            :  " + student_name);
        }
        else if(line == 5)
        {
            buildHorizontalWall(65, "STUDENT EMAIL           :  " + student_email);
        }
        else
            buildHorizontalWall(65, " ");
            line++;
    } 
  
    setCursorPos(1, 7);
    buildVerticalWall(65);
    
    SetColor(1);
    setCursorPos(3, 23);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
    SetColor(0);
  
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    ShowConsoleCursor(false);
     
    ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value storage
    if(ConvertChoiceToINT == -1) 
    {
        InvalidInputErr(); 
        goto reAsk;
    }
    else if(ConvertChoiceToINT)
    {
      return(1);
    }
    else
    {
      return(0);
    }
  
  }


  void makeStudReport()
  {
   //nupur student report code 
  }

  void reportSentSuccessfully()
  {
    scrClr(0.5);
    command.clear();

    //! EOP() seek.edit(*required) : DATE FORMET ADD AT LAST DD-MM-YYYY e.g.OOP_DD-MM-YYYY
    pdfName = "AMS_REPORT_BSCIT_SEM_3_OOP.pdf";//! need to be removed as pdf function provide value   
    command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt";
    
    setCursorPos(6,25);
    SetColor(2);
    cout<<pdfName;
    setCursorPos(2,35);
    SetColor(1);
    cout<<CUR_DATE;
    setCursorPos(2,22);
    SetColor(0);
    cout<<"REPORT HAS BEEN SENT SUCCESSFULLY TO ";
    setCursorPos(2,25);
    SetColor(1);
    cout<<FacultyEmail;
    scrClr(3);
    SetColor(0);
    
  }

  public:

  MODULE_3()
  {
    tempStorage.clear();
    command.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
  }

  int proceedFurther() //? confirmation  step
  {
      int line = 0;

      reinputforattedance:

      scrClr(0.5); 
      line = 0;
      command.clear();
      
      command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // making path to access faculty file
      getDataFromFile(command,FacultyEmail,2);// it will be needed later when sending email
      
      //BOX-UI FOR Details confirmation
      setCursorPos(1, 7);
      buildVerticalWall(65);

      while(line < 11)
      {
          setCursorPos(1,7);
          if(line == 1)
          {
              getDataFromFile(command,FacultyName,1); // getting facultyname 
              buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
          }
          else if(line == 3)
          {
              buildHorizontalWall(65, "COURSE               :  " + course_name);
          }
          else if(line == 5)
          {
              buildHorizontalWall(65, "SEM                  :  " + sem);
          }
          else if(line == 7)
          {  
              buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
          }
          else if(line == 9)
          {
              getDataFromFile(command, numberOfstudents,6); //getting number of students
              buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
          }
          else
            buildHorizontalWall(65, " ");

          line++;
      }

      setCursorPos(1, 7);
      buildVerticalWall(65);

      tempStorage.clear();
      SetColor(1);
      setCursorPos(2,23);
      cout << "DO YOU WANT TO PROCEED FURTHER ?";
      SetColor(0);
      setCursorPos(2, 32);
      fflush(stdin);
      ShowConsoleCursor(true);
      cout << "Type : ";
      getline(cin, tempStorage);
      ShowConsoleCursor(false);
      ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value
    
      if(ConvertChoiceToINT == -1) // validate input
      {
        InvalidInputErr(); 
        goto reinputforattedance;
      }

      return (ConvertChoiceToINT); // return confirmation 
  }

  void askReportChoice() // ? report type select choice
  {
        int line = 0;
        reask_report:
        

        //BOX-UI FOR REPORT CHOICE
        scrClr(0.5);
        setCursorPos(3);
        cout<<setw(64)<<" WHICH TYPE OF REPORT DO YOU WANT TO GENERATE ? "<<endl;
        setCursorPos(2,23);
        buildVerticalWall(30);
        
        line=0;

        while(line<5)
        {
            setCursorPos(1,23);
            if(line == 1)
            {
                buildHorizontalWall(30,"1) DATE-WISE REPORT ");
            }
            else if(line == 3)
            {
                buildHorizontalWall(30, "2) STUDENT REPORT ");
            }
            else
                buildHorizontalWall(30, " ");
            line++;
        }
        setCursorPos(1,23);
        buildVerticalWall(30);
    
        askChoice(3,33,tempStorage);

        if(!cin)
        {
            cin.clear();
            cin.ignore(80,'\n');
        }
        ConvertChoiceToINT = validateString(tempStorage,2,1);
        if(ConvertChoiceToINT == 0)
        {
            goto reask_report;
        }
        else
        {
          CUS_REPORT_CHOICE=(ConvertChoiceToINT);
        }
  }

  void DateWiseReport() //? DateWise report create method
  {
    if(DateInput()) 
    {

      makeDateReport(); // make Report of that date
        
      //*threading used for  processing email part 
      //! EOP() seek.edit(*required) ->attachmentpath ->pdf name  : HARSHIL RAMANI ,SHUBHAM KHUNT
      // MODULE_3 MD3;
      // thread t1(&sendToEmail,MD3,"ams.software.team@gmail.com","Amsisrich@45",FacultyEmail,"CUSTOMIZE-ATTENDANCE-REPORT","Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your Customized Attendance Report.\n\nThank You.\n\n",SemPath+"\\DAILY-RECORD\\052_Harshil_Ramani_PA04.pdf","AMS_REPORT_BSCIT_SEM_3_OOP.pdf"); 
      // thread t2(&LoadingProcess,MD3);
// 
      // t1.join(); // join the thread
      // t2.join(); // join the thread

      scrClr(); //by clearing screen it resolves flickring error of screen...
      
      if(process_flag && email_flag)
      {
        reportSentSuccessfully(); //sent email successfully
      }
      else
      {
        warnMsg("REPORT COULDN'T BE SENT !",4,26,"ERROR CODE : 404/444/599 ",1,26); // error while sending email
      }
      
    }
  
  }

  
  void studentReport()
  {
    if(RollNoInput()) 
    {  

      if(studConfirmation())
      {
         makeStudReport(); // make Report of that date
         //makePdf(); // make Report into Pdf
         //sendEmail(); // send report email to AMS user 
      }
    }
    
  }

  ~MODULE_3()
  {
    tempStorage.clear();
    command.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
  }
  
  protected:

  void SetNoObj()
  {
    //*empty defination of pure virtual functions , parent class object can't be created
  }

  //*=============================MEMBERS-FUNCTIONS-END===================================//

};

//*---------------------------STATIC DEFINATIONS-MODULE-3------------------------------/

int MODULE_3::CUS_REPORT_CHOICE; // report choice student/datewise

//-----------------------------------------------------------------------------------/
 

//**************************************   MODULES-END   ***************************************************/

//? ****************************** GENERAL FUNCTIONS ***********************************/




//? ********************************************************************************/

int main()
{ 
    //* jay swaminrayan *//
    //* jay ganeshay namh *//
    //* jay kashtbhanjan dev *//

    APP A;
    
    bool loop = true; // set true to run app by 1 time

    while(loop)
    { 
      
      A.startApp();//start app
      A.scrClr();//clear screen
      A.setCursorPos(2, 10);//set cursor position

      switch (APP::MODULE_CHOICE) // module choice asking
      {
        case 1:
        {
            MODULE_1 MD1;
            MD1.askFacDetails();//ask faculty details
            MD1.askStudDetails();//ask student details
            MD1.SetUpSucceed();//succeed msg print
            break;
        }
        case 2:
        {
            MODULE_2 MD2;
            if(MD2.checkDB())//check database
            {
                 MD2.askCourseChoice();//ask course 
                 MD2.askSemsterChoice();//ask semester
                 
                 if(MD2.askSubjectChoice())//ask subject
                 {
                    if(MD2.proceedFurther()) //confirmation for right choice
                    {
                         if(MD2.condfirmTodayAttendance()) //check if already taken for today
                         {
                              reask:
                              
                              MD2.AttendanceOptionWindow(); //ask easy option for attendance taking method
                     
                              if(MD2.takeAttendance(MODULE_2::AT_OPTION_CHOICE)) //take attendance
                              {
                                MD2.AttendanceTakenSuccessfully(); //finally taken
                              }
                              else
                              {
                                goto reask; //if option change automatically at last step
                              }
         
                         }
                    }
                 }     
            }

            break;
        }
        case 3:
        {
          MODULE_3 MD3;

          if(MD3.checkDB())//check database
          {
              MD3.askCourseChoice();//ask course 
              MD3.askSemsterChoice();//ask semester

              if(MD3.askSubjectChoice())//ask subject
              {
               
                   if(MD3.proceedFurther()) //confirm taking attendance or Return to Home Screen
                   { 
                         MD3.askReportChoice(); // select datewise or studentwise report
                                                
                              switch(MODULE_3::CUS_REPORT_CHOICE)
                              {
                                case 1:{ 
                                         MD3.DateWiseReport();
                                         break;
                                       }
                                case 2:{ 
                                         MD3.studentReport();
                                         break;
                                       }
                                default:{break;}       
                              }   
                   } 
              
              }

          }  

          break;
        }
        case 4:
        {
          break;
        }
        case 5:
        {
          loop = false; // exit Application
          break;
        }

        default:{A.setCursorPos(9,24);cout << "ERROR CODE : 421/422/424 : APPLICATION CRASHED !!!" << endl;A.scrClr(3);exit(1);break;} //* exceptional  case
      }

        A.scrClr(); // screen clear
    }
 
    return EXIT_SUCCESS;
  }
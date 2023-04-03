#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;

class shopping
{
    private:
        int pcode;
        float price;
        float dis;
        string pname; // product

    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void shopping :: menu()
{
    m:
    int choice;
    string email, password;

    cout << "\t\t\t\t______________________________________________________________________\n";
    cout << "\t\t\t\t                                                                      \n";
    cout << "\t\t\t\t                        Supermarket Main Menu                         \n";
    cout << "\t\t\t\t                                                                      \n";
    cout << "\t\t\t\t______________________________________________________________________\n";
    cout << "\t\t\t\t                                                                      \n";

    cout << "\t\t\t\t|  1) Administrator    |\n";
    cout << "\t\t\t\t|                      |\n";
    cout << "\t\t\t\t|  2) Buyer            |\n";
    cout << "\t\t\t\t|                      |\n";
    cout << "\t\t\t\t|  3) Exit             |\n";
    cout << "\t\t\t\t|                      |\n";

    cout << "\n\t\t\t Please Select: ";
    cin >> choice;

    switch(choice) 
    {
        case 1: 
            cout << "\t\t\t Please Login \n";
            cout << "\n\t\t\t Enter Email : ";
            cin>>email;
            cout << "\n\t\t\t Password : ";
            cin>>password;

            if(email == "abc@gmailcom" && password == "1234") // change email and password
            {
                administrator();
            }else{
                cout << "Invaild Email/Password...";
            }
            break;

        case 2:
            buyer();
            break;
        
        case 3:
            exit(0);
            break;
    
        default:
            cout << "Please Select from the given option...";
    }
    goto m;
}

void shopping::administrator()
{
    m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator Menu ";
    cout << "\n\t\t\t|      1) Add the Product      |";
    cout << "\n\t\t\t|                              |";
    cout << "\n\t\t\t|     2) Modify the Product    |";
    cout << "\n\t\t\t|                              |";
    cout << "\n\t\t\t|     3) Delete the Product    |";
    cout << "\n\t\t\t|                              |";
    cout << "\n\t\t\t|     4) Back to Main Menu     |";
    cout << "\n\t\t\t|                              |";

    cout << "\n\n\t Please Enter your choice : ";
    cin>>choice;

    switch (choice)
    {
    case 1:
        add();
        break;
    
    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invaild Choice...";
        break;
    }
    goto m;
}

void shopping::buyer()
{
    m:
    int choice;
    cout << "\t\t\t --- Buyer --- \n";
    cout << "\t\t\t               \n";
    cout << "\t\t\t                \n";
    cout << "\t\t\t 1) Buy product \n";
    cout << "\t\t\t                \n";
    cout << "\t\t\t 2) Go Back \n";
    cout << "\t\t\t                \n";
    cout << "\n\t\t\t Enter Your Choice : ";
    cin>>choice;

    switch (choice)
    {
    case 1:
        receipt();        
        break;
    
    case 2:
        menu();        
        break;

    default:
        cout << "Invaild Choice";
        break;
    }
    goto m;
}

void shopping::add()
{
    m:
    fstream data;
    int  c, token=0;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Add New Product ";
    cout << "\n\n\t Product code of the Product : ";
    cin >> pcode;
    cout << "\n\n\t Name of the Product : ";
    cin >> pname;
    cout << "\n\n\t Price of the Product : ";
    cin >> price;
    cout << "\n\n\t Discount On Product : ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if(!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }else{
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if(c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    }

    if(token == 1) {
        goto m;
    }else{
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    cout << "\n\n\t\t Record Inserted ! \n\n";
}

void shopping::edit()
{
    fstream data, data1;
    int pkey, token=0, c;
    float p, d;
    string n;

    cout << "\n\t\t\t Modify The Record \n";
    cout << "\n\t\t\t Product Code : ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if(!data) {
        cout << "\n\n File Doesn't exist! ";
    }else{
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> dis;
        while(!data.eof())
        {
            if(pkey == pcode) {
                cout << "\n\t\t Product New Code : ";
                cin >> c;
                cout << "\n\t\t Name of the Product : ";
                cin >> pname;
                cout << "\n\t\t Price : ";
                cin >> p;
                cout << "\n\t\t Discount : ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record Edited ! \n\n";
                token++;
            }else{
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");

        if(token == 0) {
            cout << "\n\n\t Record Not found...\n\n";
        }
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey, token=0;
    cout << "\n\n\t\t\t Delete Product \n";
    cout << "\n\t Product Code : ";
    cin >> pkey;
    data.open("database.txt", ios::in);

    if(!data) {
        cout << "\n\t Doesn't exist...\n\n";
    }else{
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while(!data.eof())
        {
            if(pcode == pkey) {
                cout << "\n\n\t Product Deleted Successfully...\n";
                token++;
            }else{
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;         
        }
        data.close();
        data1.close();
        remove("database");
        rename("database1.txt","database.txt");

        if(token == 0) {
            cout << "\n\n\t Record not found...!\n\n";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|__________________________________________________|\n";
    cout << "PreNo\t\tName\t\tPrice\n";
    cout << "\n\n|__________________________________________________|\n";
        data >> pcode >> pname >> price >> dis;   

        while (!data.eof())
        {
            cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
            data >> pcode >> pname >> price >> dis;
        }
    data.close();
}

void shopping::receipt()
{
    fstream data;
    int arrc[100];
    int arrq[100]; // quailty
    int choice, c=0;
    float amount=0, dis=0, total=0;

    cout << "\n\n\t\t\t\t RECEIPT \n";
    data.open("database.txt", ios::in);
    if(!data) {
        cout << "\n\n\t Empty Database \n\n";
    }else{
        data.close();
        list();
        cout << "\n_________________________________________________________________________________\n";
        cout << "\n|                                                                               |\n";
        cout << "\n                             Please Place The Order                              \n";
        cout << "\n|                                                                               |\n";
        cout << "\n_________________________________________________________________________________\n";
        
        do
        {
            m:
            cout << "\n\n\t Enter Product Code : ";
            cin >> arrc[c];
            cout << "\n\n\t Enter The Product Quantity : ";
            cin >> arrq[c];
            for(int i=0; i<c; i++) {
                if(arrc[c] == arrc[i]) {
                    cout << "\n\n Duplicate Product Code. Please try again!";
                    goto m;
                }
            }
            c++;
            cout << "\n\n\t Do you want to buy another product? if you then press (Y or N) \n";
            cin >> choice;
        } while(choice == 'y' );

        cout << "\n\n\t\t\t _______________________________RECIPT_________________________________\n";
        cout << "\nProduct No.\tProduct Name\tProduct Quentity\tPrice\t\tAmmount\tAmount with Discount\n\n";
        for(int i=0; i<c; i++) {
            data.open("database.txt",ios::in);
            data >> pcode >> pname >> price >> dis;
            while(!data.eof()) {
                if(pcode == arrc[i]) {
                    amount = price * arrq[i];
                    dis = amount-(amount*dis/100);
                    total = total + dis;
                    cout << "\n\n" << pcode << "\t\t" << pname <<  "\t\t" << arrq[i] <<  "\t\t" << price <<  "\t" << amount <<  "\t\t" << dis; 
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
    }
    cout << "\n\n_____________________________________________________________________________________\n";
    cout << "\n Total Amount : " << total << "\n\n";
}

int main()
{
    shopping s;
    s.menu();



    return 0;
}

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <queue>
#ifndef TRIM_H
#define TRIM_H
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <limits>
#include <iomanip>

// Train Management System : A Simulation of Train Scheduling, Movement, and Safety
// This system simulates the management of trains operating on a railway network,
// with features such as scheduling, route management, safety mechanisms, and real - time tracking.
// # 1. Purpose : The train management system's primary goal is to ensure efficient scheduling and safe operation of trains.
// # 2. It facilitates real - time monitoring of trains, schedules, and track utilization.
// # 3. The system aims to optimize train schedules to prevent delays, reduce congestion, and maintain safety.
// #Initialization of Train Schedules and Routes
// # 4. The system initializes a schedule for each train, including departure times, destinations, and intermediate stops.
// # 5. Routes for trains are predefined, with tracks assigned to specific trains to avoid conflicts.
// # 6. The system checks available tracks and schedules to ensure that no two trains are scheduled to use the same track at the same time.
// #Train Movement Simulation

using namespace std;

struct node
{
    int ticketID;
    string Name, Age, NIC, Contact, BookedClass, BookedTName, BookedTID, BookedDest, BookedSource, BookedDate, DeptTime, ArrTime, BookedSeatNum;
    float Price;
    node *next;
};

struct trains
{
    string TName, TID, TDest, TSource, TDate, arriveTime, departTime, TClasses;
    int TSeats;
};

struct SeatRecord
{
    string RowA;
    string RowB;
    string RowC;
};

node *head = NULL;
node *tail = NULL;

void admin();
int main();

string Name, Age, NIC, Contact, Dest, Source, SeatNum, Class, TID, Date, ATime, DTime, TName;
bool trainCheck = false;
float Price;
string BookedID;
int currentID;

trains availTrains[10];
int noOfTrains = 5;

void Payment()
{
    string cc, cvv, dob, payChoice;
    string accNum, accHolderFName, accHolderLName;
    cout << endl
         << endl;
    cout << "\n\n\t\t\t\t\t===============PAYMENT DETIALS===============" << endl;
    cout << "\t\t\t\t\tChoose Payment Method. \n";
    cout << "\t\t\t\t\t1. JazzCash. \n";
    cout << "\t\t\t\t\t2. EasyPaisa. \n";
    cout << "\t\t\t\t\t3. Credit/Debit Card. \n";
    cout << "\n\n\t\t\t\t\tEnter Choice (1-3): ";
    cin >> payChoice;
    if (payChoice == "1")
    {
    phoneCheck:
        cout << "\n\n\t\t\t\t\tEnter JazzCash Mobile Account Number: ";
        cin >> accNum;
        if (accNum.length() != 11 || accNum.length() > 11)
        {
            cout << endl;
            cout << "\n\n\t\t\t\t\tEnter a Valid 11 Digit Mobile Phone Number!" << endl
                 << endl;
            goto phoneCheck;
        }
        cout << "\t\t\t\t\tEnter Account Holder's First Name: ";
        cin >> accHolderFName;
        cout << "\t\t\t\t\tEnter Account Holder's Last Name: ";
        cin >> accHolderLName;
    }

    else if (payChoice == "2")
    {
        cout << "\n\n\t\t\t\t\tEnter EasyPaisa Mobile Account Number: ";
        cin >> accNum;
        cout << "\n\n\t\t\t\t\tEnter Account Holder's First Name: ";
        cin >> accHolderFName;
        cout << "\n\n\t\t\t\t\tEnter Account Holder's Last Name: ";
        cin >> accHolderLName;
    }

    else if (payChoice == "3")
    {
    check:
        cout << "\n\n\t\t\t\t\tEnter Credit/Debit Card Number (16 digits): ";
        cin >> cc;
        if (cc.length() != 16)
        {
            cout << "\n\n\t\t\t\t\tCC number must have a length of 16 only! \n";
            goto check;
        }
        else
        check2:
            cout << "\n\n\t\t\t\t\tEnter CVV (3 digits): ";
        for (int i = 0; i > -1; i++)
        {
            char temp;
            temp = _getch();
            if (temp != 13 && temp != 8)
            {
                _putch('*');
            }
            if (temp == 13)
            {
                break;
            }
            if (temp == 8 || temp == 127 && !cvv.empty())
            {
                cout << "\b \b";
                cvv.erase(cvv.size() - 1);
            }
            else
                cvv += temp;
        }

        if (cvv.length() != 3)
        {
            cout << "\n\n\t\t\t\t\tCVV number must have a length of 3 only! \n";
            cvv = "";
            goto check2;
        }
        else
        {
            cout << "\n\n\t\t\t\t\tEnter Date Of Expiry(DD/MM/YYYY): ";
            cin >> dob;
        }
    }

    else
    {
        cout << "\t\t\t\t\tInvalid Choice. Please try again. \n";
    }
    cout << "\n\n\t\t\t\t\t";
}

// # 7. The system simulates the movement of trains based on real - time speed and location data.
// # 8. It ensures that trains follow their designated route, stopping at specific stations or checkpoints.
// # 9. Train movement is tracked continuously using GPS data, sensors, or other location - tracking technologies.
// #Scheduling and Route Optimization
// # 10. The system dynamically adjusts train schedules to minimize delays and prevent conflicts between trains.
// # 11. It accounts for factors like track availability, train speed, and scheduled stops to optimize the flow of trains.
// # 12. During peak hours, the system prioritizes faster or more important routes to reduce congestion.
// #Conflict Avoidance and Track Allocation
// #/ 13. The system ensures no two trains are on the same track segment at the same time, preventing collisions.
// # 14. It uses a conflict resolution algorithm to reroute trains if there are any track conflicts or maintenance issues.
// # 15. When a track is blocked(e.g., due to a stalled train), the system reroutes other trains, maintaining minimal disruption.
// #Data Logging and Reporting
// # 32. The system logs all train movements, including arrival times, delays, and track usage.
// # 33. Historical data is used to analyze trends, optimize scheduling, and identify areas for improvement.
// # 34. Monthly and annual reports provide insights into system performance, operational efficiency, and train punctuality.
// #Maintenance and Track Monitoring
// # 35. The system includes functionality for scheduling routine maintenance on trains and tracks.
// # 36. It tracks the condition of trains and infrastructure, scheduling repairs or inspections when needed.
// # 37. Maintenance alerts are generated when certain thresholds(e.g., mileage or system status) are met.

void trainSort()
{
    string temp, temp2, temp3, temp4, temp5, temp6, temp7, temp9;
    int temp8, j;
    for (int i = 0; i < noOfTrains; i++)
    {
        temp = availTrains[i].arriveTime;
        temp2 = availTrains[i].departTime;
        temp3 = availTrains[i].TClasses;
        temp4 = availTrains[i].TDate;
        temp5 = availTrains[i].TDest;
        temp6 = availTrains[i].TID;
        temp7 = availTrains[i].TName;
        temp8 = availTrains[i].TSeats;
        temp9 = availTrains[i].TSource;
        j = i - 1;
        while (j >= 0 && availTrains[j].TName > temp7)
        {
            availTrains[j + 1].arriveTime = availTrains[j].arriveTime;
            availTrains[j + 1].departTime = availTrains[j].departTime;
            availTrains[j + 1].TClasses = availTrains[j].TClasses;
            availTrains[j + 1].TDate = availTrains[j].TDate;
            availTrains[j + 1].TDest = availTrains[j].TDest;
            availTrains[j + 1].TID = availTrains[j].TID;
            availTrains[j + 1].TName = availTrains[j].TName;
            availTrains[j + 1].TSeats = availTrains[j].TSeats;
            availTrains[j + 1].TSource = availTrains[j].TSource;
            j--;
        }
        availTrains[j + 1].arriveTime = temp;
        availTrains[j + 1].departTime = temp2;
        availTrains[j + 1].TClasses = temp3;
        availTrains[j + 1].TDate = temp4;
        availTrains[j + 1].TDest = temp5;
        availTrains[j + 1].TID = temp6;
        availTrains[j + 1].TName = temp7;
        availTrains[j + 1].TSeats = temp8;
        availTrains[j + 1].TSource = temp9;
    }
}

string SeatChoose()
{
    fstream Seat;
    int count = 0, delimit = 0;
    string line;
    SeatRecord Seats[10];
    Seat.open("Seat_Details.txt");
    while (getline(Seat, line))
    {
        count++;
    }
    Seat.close();
    Seat.open("Seat_Details.txt");
    for (int j = 0; j < count; j++)
    {
        string line1;
        getline(Seat, line1);
        for (int i = 0; i > -1; i++)
        {
            char temp;
            temp = line1[i];
            if (temp == '-')
            {
                delimit = i;
                break;
            }
            Seats[j].RowA += temp;
        }

        for (int i = delimit + 1; i > -1; i++)
        {
            char temp;
            temp = line1[i];
            if (temp == '-')
            {
                delimit = i;
                break;
            }
            Seats[j].RowB += temp;
        }

        for (int i = delimit + 1; i > -1; i++)
        {
            char temp;
            temp = line1[i];
            if (temp == '-')
            {
                delimit = i;
                break;
            }
            Seats[j].RowC += temp;
        }
    }

    Seat.close();
    string RowName, SeatNum, FinalSeatNum;
    bool Flag = false;
    cout << "\n\n\t\t\t\t\t\t\tA" << "\t" << " B" << "\t" << " C" << "\t\n";
    for (int i = 0; i < 10; i++)
    {
        cout << "\n\n\t\t\t\t\t\t\t" << Seats[i].RowA << "\t" << Seats[i].RowB << "\t" << Seats[i].RowC << "\t\n";
    }

    cout << "\n\n\t\t\t\t\t\t  ======================================\n";
    for (int x = 0; x > -1; x++)
    {
        cout << "\n\n\t\t\t\t\tEnter the row name that you chose: ";
        cin >> RowName;
        if (RowName != "A" && RowName != "B" && RowName != "C")
        {
            cout << "\n\n\t\t\t\t\tInvalid row, please try again. ";
        }
        else
            break;
    }
    for (int x = 0; x > -1; x++)
    {
    check7:
        cout << "\n\n\t\t\t\t\tEnter the seat number that you chose: ";
        cin >> SeatNum;
        if (SeatNum == "XX")
        {
            cout << "\n\n\t\t\t\t\tInvalid seat, please try again! \n";
            goto check7;
        }
        for (int i = 0; i < 10; i++)
        {
            if (RowName == "A")
            {
                if (SeatNum == Seats[i].RowA)
                {
                    Seats[i].RowA = "XX";
                    Flag = true;
                    break;
                }
            }
            else if (RowName == "B")
            {
                if (SeatNum == Seats[i].RowB)
                {
                    Seats[i].RowB = "XX";
                    Flag = true;
                    break;
                }
            }
            else if (RowName == "C")
            {
                if (SeatNum == Seats[i].RowC)
                {
                    Seats[i].RowC = "XX";
                    Flag = true;
                    break;
                }
            }
        }

        if (Flag == false)
        {
            cout << "\n\n\t\t\t\t\tSeat number not found, please try again. \n";
        }
        else
            break;
    }
    FinalSeatNum = RowName + SeatNum;
    ofstream Del;
    Del.open("Seat_Details.txt", ios::trunc);
    Del.close();
    Del.open("Seat_Details.txt", ios::trunc);
    for (int i = 0; i < 10; i++)
    {
        Del << Seats[i].RowA << "-" << Seats[i].RowB << "-" << Seats[i].RowC << "-\n";
    }
    Del.close();
    return FinalSeatNum;
}

// #Coordination Between Multiple Train Stations
// # 38. The system coordinates operations across multiple stations, ensuring that arriving and departing trains do not conflict.
// # 39. It synchronizes train schedules across regions, allowing for smooth transfers between different parts of the network.
// # 40. It ensures that connecting trains wait for delayed passengers or cargo, where applicable, to prevent missed connections.
// #Performance Evaluation and Feedback
// # 41. The system evaluates performance based on train punctuality, passenger satisfaction, and efficiency metrics.
// # 42. Feedback from train operators, passengers, and stakeholders is gathered to make improvements to the system.
// # 43. Regular evaluations are used to identify areas where delays occur most frequently and make changes to prevent them.
// #User Interface and Visualization
// # 44. The system provides a dashboard for train operators and controllers to visualize train locations, track occupancy, and schedules.
// # 45. The interface includes features for monitoring train status in real - time, sending alerts, and adjusting schedules dynamically.
// # 46. Passenger - facing interfaces include mobile apps or station displays showing live updates on train arrivals, delays, and platform assignments.
// #Fault Detection and Error Handling
// # 47. The system continuously monitors its own performance and identifies potential faults or errors, such as broken signals or communication failures.
// # 48. In the event of a fault, the system generates error reports and triggers backup systems to ensure smooth operation.
// # 49. It can handle temporary track outages or train failures by rerouting trains, rescheduling, or providing alternative transportation options.
// #Future Enhancements
// # 50. Future improvements to the system may include the integration of AI for predictive maintenance, autonomous trains, and better congestion management algorithms.

void iniTrain()
{
    availTrains[0].TName = "M1";
    availTrains[0].TID = "SHE753";
    availTrains[0].TSource = "VERSOVA";
    availTrains[0].TDest = "BANDRA";
    availTrains[0].TDate = "24-Dec-2020";
    availTrains[0].arriveTime = "20:00 (8:00 PM)";
    availTrains[0].departTime = "16:40 (4:40 PM)";
    availTrains[0].TClasses = "Economy";
    availTrains[0].TSeats = 30;

    availTrains[1].TName = "M2";
    availTrains[1].TID = "GHK753";
    availTrains[1].TSource = "GHATKOPAR";
    availTrains[1].TDest = "ANDHERI";
    availTrains[1].TDate = "24-Dec-2020";
    availTrains[1].arriveTime = "21:00 (9:00 PM)";
    availTrains[1].departTime = "17:00 (5:00 PM)";
    availTrains[1].TClasses = "Economy";
    availTrains[1].TSeats = 25;

    availTrains[2].TName = "M3";
    availTrains[2].TID = "DBE753";
    availTrains[2].TSource = "DAHISAR";
    availTrains[2].TDest = "ANDHERI";
    availTrains[2].TDate = "24-Dec-2020";
    availTrains[2].arriveTime = "22:00 (10:00 PM)";
    availTrains[2].departTime = "18:00 (6:00 PM)";
    availTrains[2].TClasses = "Economy";
    availTrains[2].TSeats = 35;

    availTrains[3].TName = "M4";
    availTrains[3].TID = "AWH753";
    availTrains[3].TSource = "ANDHERI WEST";
    availTrains[3].TDest = "BANDRA";
    availTrains[3].TDate = "24-Dec-2020";
    availTrains[3].arriveTime = "23:00 (11:00 PM)";
    availTrains[3].departTime = "19:00 (7:00 PM)";
    availTrains[3].TClasses = "Economy";
    availTrains[3].TSeats = 20;

    availTrains[4].TName = "M5";
    availTrains[4].TID = "BDR753";
    availTrains[4].TSource = "BANDRA";
    availTrains[4].TDest = "VERSOVA";
    availTrains[4].TDate = "24-Dec-2020";
    availTrains[4].arriveTime = "00:00 (12:00 AM)";
    availTrains[4].departTime = "20:00 (8:00 PM)";
    availTrains[4].TClasses = "Economy";
    availTrains[4].TSeats = 40;

    availTrains[5].TName = "M6";
    availTrains[5].TID = "CSI753";
    availTrains[5].TSource = "CSIA";
    availTrains[5].TDest = "NMIA";
    availTrains[5].TDate = "24-Dec-2020";
    availTrains[5].arriveTime = "01:00 (1:00 AM)";
    availTrains[5].departTime = "21:00 (9:00 PM)";
    availTrains[5].TClasses = "Economy";
    availTrains[5].TSeats = 50;

    availTrains[6].TName = "M7";
    availTrains[6].TID = "MLD753";
    availTrains[6].TSource = "MULUND";
    availTrains[6].TDest = "THANE";
    availTrains[6].TDate = "24-Dec-2020";
    availTrains[6].arriveTime = "02:00 (2:00 AM)";
    availTrains[6].departTime = "22:00 (10:00 PM)";
    availTrains[6].TClasses = "Economy";
    availTrains[6].TSeats = 55;

    availTrains[7].TName = "M8";
    availTrains[7].TID = "TNE753";
    availTrains[7].TSource = "THANE";
    availTrains[7].TDest = "BHIWANDI";
    availTrains[7].TDate = "24-Dec-2020";
    availTrains[7].arriveTime = "03:00 (3:00 AM)";
    availTrains[7].departTime = "23:00 (11:00 PM)";
    availTrains[7].TClasses = "Economy";
    availTrains[7].TSeats = 60;

    availTrains[8].TName = "M9";
    availTrains[8].TID = "BHI753";
    availTrains[8].TSource = "BHIWANDI";
    availTrains[8].TDest = "KALYAN";
    availTrains[8].TDate = "24-Dec-2020";
    availTrains[8].arriveTime = "04:00 (4:00 AM)";
    availTrains[8].departTime = "00:00 (12:00 AM)";
    availTrains[8].TClasses = "Economy";
    availTrains[8].TSeats = 65;

    availTrains[9].TName = "M10";
    availTrains[9].TID = "KLY753";
    availTrains[9].TSource = "KALYAN";
    availTrains[9].TDest = "VERSOVA";
    availTrains[9].TDate = "24-Dec-2020";
    availTrains[9].arriveTime = "05:00 (5:00 AM)";
    availTrains[9].departTime = "01:00 (1:00 AM)";
    availTrains[9].TClasses = "Economy";
    availTrains[9].TSeats = 70;
}

string trainFill()
{
    bool check = false;
    bool check2 = false;
    trainCheck = true;

flag:
    cout << "\t\t\t\t\tEnter Your Departure City: ";
    cin >> Dest;
    cin.ignore();
    cout << "\t\t\t\t\tEnter Your Arrival City: ";
    cin >> Source;
    cin.ignore();

    trainSort();

    cout << "\n\n\t\t\t\t\tAVAILABLE TRAINS ON THAT DAY IN THIS ROUTE ARE AS FOLLOWS (IF ANY): \n\n"
         << endl;

    for (int i = 0; i < noOfTrains; i++)
    {
        if (availTrains[i].TSource == Dest && availTrains[i].TDest == Source)
        {
            cout << "\t\t\t\t\tTrain Name: " << availTrains[i].TName << endl;
            cout << "\t\t\t\t\tTrain ID: " << availTrains[i].TID << endl;
            cout << "\t\t\t\t\tTrain Source: " << availTrains[i].TSource << endl;
            cout << "\t\t\t\t\tTrain Destination: " << availTrains[i].TDest << endl;
            cout << "\t\t\t\t\tTrain Departure Date: " << availTrains[i].TDate << endl;
            cout << "\t\t\t\t\tTrain Arrival Time: " << availTrains[i].arriveTime << endl;
            cout << "\t\t\t\t\tTrain Departure Time: " << availTrains[i].departTime << endl;
            cout << "\t\t\t\t\tAvailable Train Classes: " << availTrains[i].TClasses << endl;
            cout << "\t\t\t\t\tSeats Available: " << availTrains[i].TSeats << endl;
            cout << endl
                 << endl;
            check = true;
        }
    }
    if (check == false)
    {
        cout << "\t\t\t\t\tNo trains available on this route. Re-enter your details. \n";
        goto flag;
    }

    else
    {
    redo:
        cout << "\t\t\t\t\tInput Train ID that you wish to book: ";
        cin >> BookedID;
        for (int i = 0; i < noOfTrains; i++)
        {
            if (BookedID == availTrains[i].TID)
            {
                availTrains[i].TSeats--;
                return BookedID;
                check2 = true;
            }
        }
        if (check2 == false)
        {
            cout << "\t\t\t\t\tInput correct train ID! \n";
            goto redo;
        }
    }
}

void trainPrice()
{
    int choice = 0;
    cout << "\t\t\t\t\tPrices based on classes are as follows: \n";
    cout << "\t\t\t\t\t1. Economy \t\t 250 INR \n";
    cout << "\t\t\t\t\t2. AC Lower \t\t 350 INR \n";
    cout << "\t\t\t\t\t3. AC Business \t\t 450 INR \n\n";
    cout << "\t\t\t\t\tInput Choice (1-3): ";
    cin >> choice;
    if (choice == 1)
    {
        Price = 250;
        Class = "Economy [No Berth]";
    }
    else if (choice == 2)
    {
        Price = 350;
        Class = "AC Lower [Berth Included]";
    }
    else if (choice == 3)
    {
        Price = 450;
        Class = "AC Business [Berth Included]";
    }
}

void reserveTicket()
{
    string fName, lName;
    node *obj = new node();
    node *temp = tail;
    if (head == NULL && tail == NULL)
    {
        obj->next = NULL;
        head = obj;
        tail = obj;
    }
    else
    {
        temp->next = obj;
        tail = obj;
    }

    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\tEnter First Name of Passenger: ";
    cin >> fName;
    cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
    cin >> lName;
    Name = fName + " " + lName;

    cout << "\t\t\t\t\tEnter Age: ";
    cin >> Age;

nicCheck:
    cout << "\t\t\t\t\tEnter PAN Number: ";
    cin >> NIC;

    if (NIC.length() != 13 || NIC.length() > 13)
    {
        cout << endl;
        cout << "\t\t\t\t\tEnter a Valid 13 digit CNIC Number!" << endl
             << endl;
        goto nicCheck;
    }

phoneCheck:
    cout << "\t\t\t\t\tEnter Contact Number: ";
    cin >> Contact;

    if (Contact.length() != 11 || Contact.length() > 11)
    {
        cout << endl;
        cout << "\t\t\t\t\tEnter a Valid 11 digit Mobile Phone Number!" << endl
             << endl;
        goto phoneCheck;
    }
    cin.clear();

    trainFill();
    int seatCheck;
    for (int i = 0; i < noOfTrains; i++)
    {
        if (availTrains[i].TID == BookedID)
        {
            TName = availTrains[i].TName;
            TID = BookedID;
            Date = availTrains[i].TDate;
            ATime = availTrains[i].arriveTime;
            DTime = availTrains[i].departTime;
        }
    }

    trainPrice();

    SeatNum = SeatChoose();

    Payment();

    system("cls");

    cout << "\n\n\t\t\t\t\t Your payment is successfully processed!" << endl;
    cout << "\t\t\t\t\t INR " << Price << " has been deducted from your Account." << endl;

    srand(time(0));

    // Randomly Generated Ticket ID:
    obj->ticketID = (rand());
    cout << endl
         << endl;
    cout << "\t\t\t\t\tTicket Generated! Your ID is: " << obj->ticketID << endl;
    currentID = obj->ticketID;

    obj->Name = Name;
    obj->NIC = NIC;
    obj->Age = Age;
    obj->Contact = Contact;
    obj->BookedTName = TName;
    obj->BookedDest = Dest;
    obj->BookedSource = Source;
    obj->BookedSeatNum = SeatNum;
    obj->Price = Price;
    obj->BookedClass = Class;
    obj->BookedTID = TID;
    obj->BookedDate = Date;
    obj->DeptTime = DTime;
    obj->ArrTime = ATime;

    cout << endl
         << endl;
}

void viewTicket()
{
    int search;
    string choice;
    bool check = false;
    node *temp = head;
    cin.clear();
    cout << endl
         << endl
         << endl
         << endl
         << endl;
jump:
    cout << "\t\t\t\t\tDo You Want to View Most Recent Booking? If so, Press 1\n";
    cout << "\t\t\t\t\t Do You Want to Search on Older Booking? If so, Press 2\n";
    cout << "\t\t\t\t\tEnter Choice (1-2): ";
    cin >> choice;
    cin.ignore();
    if (choice == "1")
    {
        search = currentID;
        check = true;
    }
    else if (choice == "2")
    {
        cout << "\t\t\t\t\tEnter Your Booking ID: ";
        cin >> search;
        cout << endl
             << endl;
        check = true;
    }
    else
    {
        cout << "\t\t\t\t\tInvalid input. Retry! \n";
        goto jump;
    }
    do
    {
        if (temp != NULL)
        {
            if (temp->ticketID == search && check == true)
            {
                cout << "\t\t\t\t\tBooking ID: " << temp->ticketID << endl;
                cout << "\t\t\t\t\tName: " << temp->Name << endl;
                cout << "\t\t\t\t\tAge: " << temp->Age << endl;
                cout << "\t\t\t\t\tPAN: " << temp->NIC << endl;
                cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
                cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
                cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
                cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
                cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
                cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
                cout << "\t\t\t\t\tSource: " << temp->BookedDest << endl;
                cout << "\t\t\t\t\tDestination: " << temp->BookedSource << endl;
                cout << "\t\t\t\t\tDeparture TIme: " << temp->DeptTime << endl;
                cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
                cout << endl
                     << endl;
                break;
                main();
            }
            else
            {
                temp = temp->next;
            }
        }
        else
            cout << "\t\t\t\t\tNo Bookings Exist. \n";
    } while (temp);
}

void display()
{
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    if (head != NULL && tail != NULL)
    {
        cout << "\t\t\t\t\tList is as follows: \n";
        node *temp = head;
        do
        {
            cout << "\t\t\t\t\tTicket ID: " << temp->ticketID << endl;
            cout << "\t\t\t\t\tName: " << temp->Name << endl;
            cout << "\t\t\t\t\tAge: " << temp->Age << endl;
            cout << "\t\t\t\t\tPAN: " << temp->NIC << endl;
            cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
            cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
            cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
            cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
            cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
            cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
            cout << "\t\t\t\t\tSource: " << temp->BookedSource << endl;
            cout << "\t\t\t\t\tDestination: " << temp->BookedDest << endl;
            cout << "\t\t\t\t\tDeparture TIme: " << temp->DeptTime << endl;
            cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
            cout << endl;
            temp = temp->next;
        } while (temp);
    }
    else
        cout << "List is empty, nothing to display. \n";
}

void removeTicket(int remTicket)
{
    node *prev = head;
    node *delNode = head;
    while (delNode != NULL)
    {
        if (delNode->ticketID == remTicket)
        {
            break;
        }
        else
        {
            prev = delNode;
            delNode = delNode->next;
        }
    }
    if (delNode == NULL)
    {
        cout << "Ticket ID Not Found!" << endl;
    }
    else
    {
        cout << "\t\t\t\t\tDeleted Ticket ID: " << delNode->ticketID << "\n";
        prev->next = delNode->next; // unlink the node you remove
        delete delNode;             // delete the node
    }
}

void editDetais()
{

    string fName, lName;

    cout << "\t\t\t\t\tEDIT DETAILS:" << endl
         << endl;
    int search;
    node *temp = head;
    cin.clear();
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\tEnter ticket ID: ";
    cin >> search;

    while (temp != NULL)
    {
        if (temp->ticketID == search)
        {
            cout << "\t\t\t\t\tEnter First Name of Passenger: ";
            cin >> fName;
            cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
            cin >> lName;
            Name = fName + " " + lName;

            cout << "\t\t\t\t\tEnter CNIC Number: ";
            cin >> NIC;
            cin.ignore();
            cout << "\t\t\t\t\tEnter Contact Number: ";
            cin >> Contact;
            cin.ignore();

            temp->Name = Name;
            temp->NIC = NIC;
            temp->Age = Age;
            temp->Contact = Contact;
        }
        temp = temp->next;
    }
}

void addTrains()
{
    string choice;
    do
    {
        cin.ignore();
        cout << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "\t\t\t\t\tEnter Train Name: ";
        getline(cin, availTrains[noOfTrains].TName);
        cout << "\t\t\t\t\tEnter Train ID: ";
        getline(cin, availTrains[noOfTrains].TID);
        cout << "\t\t\t\t\tEnter Train Source: ";
        getline(cin, availTrains[noOfTrains].TSource);
        cout << "\t\t\t\t\tEnter Train Destination: ";
        getline(cin, availTrains[noOfTrains].TDest);
        cout << "\t\t\t\t\tEnter Train Departure Date: ";
        getline(cin, availTrains[noOfTrains].TDate);
        cout << "\t\t\t\t\tEnter Train Departure Time [HH:MM (MM:HH AM/PM)]: ";
        getline(cin, availTrains[noOfTrains].departTime);
        cout << "\t\t\t\t\tEnter Train Arrival Time [HH:MM (MM:HH AM/PM)]: ";
        getline(cin, availTrains[noOfTrains].arriveTime);
        cout << "\t\t\t\t\tEnter Available Train Classes: ";
        getline(cin, availTrains[noOfTrains].TClasses);
        cout << "\t\t\t\t\tEnter Seats Available: ";
        cin >> availTrains[noOfTrains].TSeats;
        noOfTrains++;
        cin.clear();
        cout << "\t\t\t\t\tDo you want to add more trains? (Y/N): ";
        cin >> choice;

        if (choice != "Y" && choice != "N")
            cout << "\t\t\t\t\tInvalid input. Enter choice again. ";
        else if (choice == "N")
        {
            system("cls");
            cout << "\n\n\n\n\n\t\t\t\t\tTrain added! \n";
            cout << "\t\t\t\t\tSession logged out. Please login again. \n";
            Sleep(1500);
            system("cls");
            main();
        }

    } while (choice != "N");
}

#include <iostream>
#include <string>
#include <conio.h> // For getch()
using namespace std;

void admin() {
    string choice, user, password;
    system("cls");

    cin.clear();

    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\tWELCOME TO ADMIN PORTAL!\n\n";

    cout << "\t\t\t\t\tEnter your login credentials below! \n";
login:
    cout << "\t\t\t\t\tEnter your Username: ";
    cin >> user;
    cout << "\t\t\t\t\tEnter your Password: ";

    // Masking password input
    char ch;
    password.clear();
    while ((ch = getch()) != '\r') { // Enter key is pressed
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Display asterisk for each character
        }
    }
    cout << endl; // Move to the next line after password input

    if (user == "sachin" && password == "sachin") {
        cout << "\t\t\t\t\tLogged in Successfully!\n";
        cin.clear();

        system("cls");

        cout << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "\t\t\t\t\tSelect 1 to View all Booked Tickets. \n";
        cout << "\t\t\t\t\tSelect 2 to add Trains. \n";
        cout << "\t\t\t\t\tSelect 3 to Exit\n";
        do {
            cout << "\t\t\t\t\tEnter Choice To Proceed (1-2): ";
            cin >> choice;
            if (choice == "1")
                display();
            else if (choice == "2") {
                cin.clear();
                addTrains();
                if (trainCheck == false)
                    trainFill();
            }
            else if (choice == "3") {
                system("cls");
                main();
            }
            else
                cout << "\t\t\t\t\tEnter correct choice. Try again. \n";
        } while (choice != "3");
    } else {
        cout << "\t\t\t\t\tInvalid credentials. Please login again. \n";
        goto login;
    }
}

int module1()
{
    iniTrain();
relog:
    cin.clear();
    string check;
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t WELCOME TO RAILWAY BOOKING SYSTEM AND TRAFFIC MANAGEMENT SYSTEM!\n\n\n";

    cout << endl;
    // system("cls");
log:
    cout << "\n\n\n\n\n\t\t\t\tIf you are a user looking to book a ticket and know more about traffic management system, type 1 \n";
    cout << "\t\t\t\tIf you are an admin, type 2 \n";
    cout << "\n\n\t\t\t\t\t\tChoice: ";
    cin >> check;
    if (check == "1")
    {
        int tickID;
        string choice;
        system("cls");
        cout << endl
             << endl
             << endl
             << endl
             << endl;
        do
        {
            cout << "\t\t\t\t     -----------------------------------------\n";
            cout << "\t\t\t\t\tSelect 1 to Reserve a Ticket. \n";
            cout << "\t\t\t\t\tSelect 2 to View your Reservation. \n";
            cout << "\t\t\t\t\tSelect 3 to Display all tickets. \n";
            cout << "\t\t\t\t\tSelect 4 to Delete a ticket. \n";
            cout << "\t\t\t\t\tSelect 5 to Edit Details. \n";
            cout << "\t\t\t\t\tSelect 6 to Log Out of Session. \n";
            cout << "\t\t\t\t\tSelect 7 to allocate the number of trains. \n";
            cout << "\t\t\t\t\tSelect 8 to shortest path according to dijkstra . \n";
            cout << "\t\t\t\t\tSelect 11 to traffic management system.\n";
            cout << "\t\t\t\t\tSelect 10 to Exit\n";
            cout << endl
                 << endl;
            cout << "\t\t\t\t\tEnter Choice To Proceed (1-10): ";
            cin >> choice;

            if (choice == "1")
            {
                system("cls");
                cin.clear();
                reserveTicket();
            }
            else if (choice == "2")
            {
                system("cls");
                viewTicket();
            }
            else if (choice == "3")
            {
                system("cls");
                display();
            }
            else if (choice == "4")
            {
                cout << "\t\t\t\t\tEnter your Ticket ID: ";
                cin >> tickID;
                removeTicket(tickID);
            }
            else if (choice == "5")
            {
                system("cls");
                editDetais();
            }
            else if (choice == "6")
            {
                goto relog;
            }
            else if (choice == "9")
            {
                Sleep(300);
                cout << "\t\t\t\t\tTHANKYOU! \n";

                Sleep(300);
                exit(0);
            }
            else if (choice == "7")
            {

                {
                    // Struct definition for MetroStation
                    struct MetroStation
                    {
                        string name;
                        int population;
                        int trains; // Number of trains assigned
                    };

                    // Function to assign trains based on population and capacity
                    auto assignTrains = [](MetroStation &station)
                    {
                        const int capacityPerTrain = 100; // Maximum capacity of each train
                        // Calculate the number of trains needed based on population
                        station.trains = (station.population + capacityPerTrain - 1) / capacityPerTrain; // Ceiling division
                    };

                    // Function to display the train assignment for a specific station
                    auto displayTrainAssignment = [](const MetroStation &station)
                    {
                        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                        cout << "**'                                                                                                '**" << endl;
                        cout << "**'                                                                                                '**" << endl;
                        cout << "**'                                 ALLOCATING STATION                                             '**" << endl;
                        cout << "**'                                         TO                                                     '**" << endl;
                        cout << "**'                             RAILWAY MANAGEMENT SYSTEM                                          '**" << endl;
                        cout << "**'                                                                                                '**" << endl;
                        cout << "**'                                                                                                '**" << endl;
                        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

                        cout << "\nMetro Station Train Assignment:\n";
                        cout << "-----------------------------------\n";
                        cout << "Station Name: " << station.name << endl;
                        cout << "Population: " << station.population << endl;
                        cout << "Trains Assigned: " << station.trains << endl;
                    };

                    // Predefined list of Mumbai Metro stations
                    vector<MetroStation> stations = {
                        {"Versova", 0, 0},
                        {"D N Nagar", 0, 0},
                        {"Azad Nagar", 0, 0},
                        {"Andheri", 0, 0},
                        {"Western Express Highway", 0, 0},
                        {"Chakala", 0, 0},
                        {"Airport Road", 0, 0},
                        {"Marol Naka", 0, 0},
                        {"Saki Naka", 0, 0},
                        {"Asalpha", 0, 0},
                        {"Jagruti Nagar", 0, 0},
                        {"Ghatkopar", 0, 0}};

                    char choice;

                    do
                    {
                        // Display available stations
                        cout << "\nAvailable Mumbai Metro Stations:\n";
                        for (size_t i = 0; i < stations.size(); ++i)
                        {
                            cout << i + 1 << ": " << stations[i].name << endl;
                        }

                        // Prompt user to select a station
                        int stationIndex;
                        cout << "Select a station by entering its number (1-" << stations.size() << "): ";

                        while (!(cin >> stationIndex) || stationIndex < 1 || stationIndex > stations.size())
                        {
                            cout << "Invalid selection! Please enter a number between 1 and " << stations.size() << ": ";
                            cin.clear();                                         // Clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        }

                        // Get the selected station
                        MetroStation &selectedStation = stations[stationIndex - 1];

                        // Input population for the selected metro station from the user
                        cout << "Enter population at station " << selectedStation.name << ": ";

                        while (!(cin >> selectedStation.population) || selectedStation.population < 0)
                        {
                            cout << "Invalid input! Please enter a non-negative integer for population: ";
                            cin.clear(); // Clear the error flag

                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        }

                        // Assign trains based on population and capacity

                        assignTrains(selectedStation);

                        // Display the train assignment for the selected station
                        displayTrainAssignment(selectedStation);

                        // Ask if the user wants to enter another population
                        cout << "\nDo you want to enter population for another station? (y/n): ";

                        cin >> choice;

                    } while (choice == 'y' || choice == 'Y');
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;

                    // Return statement added for main()
                }
            }

            else if (choice == "8")
            {
                {
                    // Number of stations
                    const int V = 12;

                    // Adjacency matrix representing the Mumbai Metro stations and their distances (in meters)
                    int graph[12][12] = {
                        {0, 5, 10, 15, 0, 0, 0, 0, 0, 0, 0, 0},         // Versova
                        {5, 0, 3, 20, 0, 0, 0, 0, 0, 0, 0, 0},          // D N Nagar
                        {10, 3, 0, 2, 25, 30, 35, 40, 45, 50, 55, 60},  // Azad Nagar
                        {15, 20, 2, 8, 12, 14, 16, 18, 20, 22, 24, 26}, // Andheri
                        {0, 0, 25, 12, 6, 8, 10, 12, 14, 0, 0, 0},      // Western Express Highway
                        {0, 0, 30, 14, 0, 0, 0, 0, 0, 0, 0, 0},         // Chakala
                        {0, 0, 35, 16, 10, 30, 0, 0, 0, 0, 0, 0},       // Airport Road
                        {0, 0, 40, 18, 12, 14, 5, 0, 15, 20, 25, 30},   // Marol Naka
                        {0, 0, 45, 20, 14, 10, 15, 15, 0, 5, 10, 15},   // Saki Naka
                        {0, 0, 50, 22, 20, 30, 20, 20, 5, 0, 5, 10},    // Asalpha
                        {0, 0, 55, 24, 24, 35, 25, 25, 10, 5, 0, 5},    // Jagruti Nagar
                        {0, 0, 60, 26, -1, -1, -1, -1, -1, -1, -1, -1}  // Ghatkopar (no connections)
                    };

                    // Array of station names corresponding to their indices in the graph
                    string stations[V] = {
                        "Versova",
                        "D N Nagar",
                        "Azad Nagar",
                        "Andheri",
                        "Western Express Highway",
                        "Chakala",
                        "Airport Road",
                        "Marol Naka",
                        "Saki Naka",
                        "Asalpha",
                        "Jagruti Nagar",
                        "Ghatkopar"};

                    // Function to find the vertex with the minimum distance value
                    auto minDistance = [](int dist[], bool visited[], int V)
                    {
                        int min = INT_MAX;
                        int min_index = -1; // Initialize to -1 to indicate no vertex found initially
                        for (int v = 0; v < V; v++)
                        {
                            if (!visited[v] && dist[v] <= min)
                            {
                                min = dist[v];
                                min_index = v;
                            }
                        }

                        return min_index;
                    };

                    // Function that implements Dijkstra's algorithm for a graph represented using adjacency matrix

                    auto dijkstra = [&](int src)
                    {
                        int dist[V]; // Output array. dist[i] holds the shortest distance from src to j

                        bool visited[V]; // visited[i] will be true if vertex i is included in shortest path tree

                        // Initialize all distances as INFINITE and visited[] as false

                        for (int i = 0; i < V; i++)
                        {
                            dist[i] = INT_MAX;
                            visited[i] = false;
                        }

                        // Distance from source to itself is always 0

                        dist[src] = 0;

                        // Find shortest path for all vertices

                        for (int count = 0; count < V - 1; count++)
                        {
                            int u = minDistance(dist, visited, V);
                            visited[u] = true;

                            // Update dist value of the adjacent vertices of the picked vertex

                            for (int v = 0; v < V; v++)
                            {
                                if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                                {
                                    dist[v] = dist[u] + graph[u][v];
                                }
                            }
                        }

                        // Print the constructed distance array

                        cout << "\nStation \t Distance from Source\n";
                        for (int i = 0; i < V; i++)
                            cout << stations[i] << "\t\t " << (dist[i] == INT_MAX ? -1 : dist[i]) << " meters" << endl;
                    };

                    // Display station options to the user

                    cout << "Select a source station:\n";
                    for (int i = 0; i < V; i++)
                    {
                        cout << i << ": " << stations[i] << endl;
                    }

                    int source;
                    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                 CALCULATING DISTANCES                                          '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

                    cout << "Enter the index of the source station (0-" << V - 1 << "): ";
                    cin >> source;

                    // Validate user input
                    if (source < 0 || source >= V)
                    {
                        cout << "Invalid input! Please enter a number between " << 0 << " and " << V - 1 << "." << endl;
                        return -1;
                    }

                    dijkstra(source); // Start Dijkstra's algorithm from user-selected station

                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl; // Return statement added for main()
                }
            }
            else if (choice == "11")
            {
                {
                    // Enums for system classifications
                    enum VehicleType
                    {
                        CAR,
                        BUS,
                        TRUCK,
                        MOTORCYCLE,
                        BICYCLE
                    };
                    enum TrafficLightState
                    {
                        RED,
                        YELLOW,
                        GREEN
                    };
                    enum WeatherType
                    {
                        CLEAR,
                        RAIN,
                        SNOW,
                        FOG
                    };
                    enum EmergencyType
                    {
                        ACCIDENT,
                        FIRE,
                        MEDICAL,
                        POLICE
                    };
                    enum RoadCondition
                    {
                        EXCELLENT,
                        GOOD,
                        FAIR,
                        POOR
                    };

                    // Utility functions
                    class Utils
                    {
                    public:
                        static void clearScreen()
                        {
#ifdef _WIN32
                            system("cls");
#else
                            system("clear");
#endif
                        }

                        static string getCurrentTime()
                        {
                            time_t now = time(0);
                            return ctime(&now);
                        }

                        static string generateId(const string &prefix)
                        {
                            static int counter = 0;
                            return prefix + "_" + to_string(++counter);
                        }

                        static void logEvent(const string &event)
                        {
                            ofstream logFile("traffic_log.txt", ios::app);
                            logFile << getCurrentTime() << ": " << event << endl;
                        }

                        static void clearInputBuffer()
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    };

                    // Vehicle Class
                    class Vehicle
                    {
                    private:
                        string vehicleId;
                        VehicleType type;
                        double speed;
                        double position_x;
                        double position_y;
                        bool isActive;

                    public:
                        Vehicle(string id, VehicleType t) : vehicleId(id), type(t), speed(0), position_x(0), position_y(0), isActive(true) {}

                        void updatePosition(double x, double y)
                        {
                            position_x = x;
                            position_y = y;
                            Utils::logEvent("Vehicle " + vehicleId + " position updated");
                        }

                        void updateSpeed(double newSpeed)
                        {
                            speed = newSpeed;
                            Utils::logEvent("Vehicle " + vehicleId + " speed updated to " + to_string(speed));
                        }

                        void setActive(bool status)
                        {
                            isActive = status;
                        }

                        void displayInfo() const
                        {
                            cout << "\nVehicle Information:" << endl;
                            cout << "ID: " << vehicleId << endl;
                            cout << "Type: " << type << endl;
                            cout << "Speed: " << speed << " km/h" << endl;
                            cout << "Position: (" << position_x << ", " << position_y << ")" << endl;
                            cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
                        }

                        string getId() const { return vehicleId; }
                        bool getStatus() const { return isActive; }
                        double getSpeed() const { return speed; }
                    };

                    // Traffic Light Class
                    class TrafficLight
                    {
                    private:
                        string lightId;
                        TrafficLightState state;
                        int timer;
                        bool isOperational;

                    public:
                        TrafficLight(string id) : lightId(id), state(RED), timer(30), isOperational(true) {}

                        void updateState()
                        {
                            if (!isOperational)
                                return;

                            timer--;
                            if (timer <= 0)
                            {
                                switch (state)
                                {
                                case RED:
                                    state = GREEN;
                                    timer = 30;
                                    break;
                                case GREEN:
                                    state = YELLOW;
                                    timer = 5;
                                    break;
                                case YELLOW:
                                    state = RED;
                                    timer = 30;
                                    break;
                                }
                                Utils::logEvent("Traffic light " + lightId + " state changed to " + to_string(state));
                            }
                        }

                        void setOperational(bool status)
                        {
                            isOperational = status;
                            Utils::logEvent("Traffic light " + lightId + " operational status: " + to_string(status));
                        }

                        void displayInfo() const
                        {
                            cout << "\nTraffic Light Information:" << endl;
                            cout << "ID: " << lightId << endl;
                            cout << "State: ";
                            switch (state)
                            {
                            case RED:
                                cout << "Red";
                                break;
                            case YELLOW:
                                cout << "Yellow";
                                break;
                            case GREEN:
                                cout << "Green";
                                break;
                            }
                            cout << "\nTimer: " << timer << " seconds" << endl;
                            cout << "Operational: " << (isOperational ? "Yes" : "No") << endl;
                        }

                        string getId() const { return lightId; }
                        bool getOperational() const { return isOperational; }
                        TrafficLightState getState() const { return state; }
                    };

                    // Road Class
                    class Road
                    {
                    private:
                        string roadId;
                        double length;
                        int lanes;
                        RoadCondition condition;
                        vector<Vehicle *> vehicles;
                        vector<TrafficLight *> trafficLights;

                    public:
                        Road(string id, double len, int ln) : roadId(id), length(len), lanes(ln), condition(EXCELLENT) {}

                        void addVehicle(Vehicle *vehicle)
                        {
                            vehicles.push_back(vehicle);
                            Utils::logEvent("Vehicle " + vehicle->getId() + " added to road " + roadId);
                        }

                        void removeVehicle(Vehicle *vehicle)
                        {
                            vehicles.erase(
                                remove_if(vehicles.begin(), vehicles.end(),
                                          [vehicle](Vehicle *v)
                                          { return v->getId() == vehicle->getId(); }),
                                vehicles.end());
                            Utils::logEvent("Vehicle " + vehicle->getId() + " removed from road " + roadId);
                        }

                        void addTrafficLight(TrafficLight *light)
                        {
                            trafficLights.push_back(light);
                            Utils::logEvent("Traffic light " + light->getId() + " added to road " + roadId);
                        }

                        void updateCondition(RoadCondition newCondition)
                        {
                            condition = newCondition;
                            Utils::logEvent("Road " + roadId + " condition updated to " + to_string(static_cast<int>(condition)));
                        }

                        void displayInfo() const
                        {
                            cout << "\nRoad Information:" << endl;
                            cout << "ID: " << roadId << endl;
                            cout << "Length: " << length << " km" << endl;
                            cout << "Lanes: " << lanes << endl;
                            cout << "Condition: ";
                            switch (condition)
                            {
                            case EXCELLENT:
                                cout << "Excellent";
                                break;
                            case GOOD:
                                cout << "Good";
                                break;
                            case FAIR:
                                cout << "Fair";
                                break;
                            case POOR:
                                cout << "Poor";
                                break;
                            }
                            cout << "\nVehicles: " << vehicles.size() << endl;
                            cout << "Traffic Lights: " << trafficLights.size() << endl;
                        }

                        string getId() const { return roadId; }
                        RoadCondition getCondition() const { return condition; }
                        int getVehicleCount() const { return vehicles.size(); }
                    };

                    // Emergency Management Class
                    class EmergencyManager
                    {
                    private:
                        queue<pair<EmergencyType, string>> emergencies;
                        map<string, time_t> responseTime;

                    public:
                        void reportEmergency(EmergencyType type, const string &location)
                        {
                            emergencies.push({type, location});
                            Utils::logEvent("Emergency reported at " + location);
                        }

                        void handleEmergency()
                        {
                            if (!emergencies.empty())
                            {
                                auto emergency = emergencies.front();
                                emergencies.pop();
                                responseTime[emergency.second] = time(0);
                                Utils::logEvent("Emergency handled at " + emergency.second);
                            }
                        }

                        void displayStatus() const
                        {
                            cout << "\nEmergency Management Status:" << endl;
                            cout << "Pending emergencies: " << emergencies.size() << endl;
                            cout << "Handled emergencies: " << responseTime.size() << endl;
                        }
                    };

                    // Traffic Management System
                    class TrafficManagementSystem
                    {
                    private:
                        vector<Vehicle *> vehicles;

                        vector<TrafficLight *> trafficLights;
                        vector<Road *> roads;
                        EmergencyManager emergencyManager;
                        WeatherType currentWeather;

                    public:
                        TrafficManagementSystem() : currentWeather(CLEAR) {}

                        ~TrafficManagementSystem()
                        {
                            for (auto vehicle : vehicles)
                                delete vehicle;
                            for (auto light : trafficLights)
                                delete light;
                            for (auto road : roads)
                                delete road;
                        }

                        void addVehicle()
                        {
                            string id = Utils::generateId("VEH");
                            cout << "Enter vehicle type (0-CAR, 1-BUS, 2-TRUCK, 3-MOTORCYCLE, 4-BICYCLE): ";
                            int type;
                            cin >> type;

                            if (type >= 0 && type <= 4)
                            {
                                vehicles.push_back(new Vehicle(id, static_cast<VehicleType>(type)));
                                cout << "Vehicle added successfully. ID: " << id << endl;
                                Utils::logEvent("New vehicle added: " + id);
                            }
                            else
                            {
                                cout << "Invalid vehicle type!" << endl;
                            }
                        }

                        void addTrafficLight()
                        {
                            string id = Utils::generateId("TL");
                            trafficLights.push_back(new TrafficLight(id));
                            cout << "Traffic light added successfully. ID: " << id << endl;
                            Utils::logEvent("New traffic light added: " + id);
                        }

                        void addRoad()
                        {
                            string id = Utils::generateId("RD");
                            cout << "Enter road length (km): ";
                            int length;
                            cin >> length;
                            cout << "Enter number of lanes: ";
                            int lanes;
                            cin >> lanes;

                            if (length > 0 && lanes > 0)
                            {
                                roads.push_back(new Road(id, length, lanes));
                                cout << "Road added successfully. ID: " << id << endl;
                                Utils::logEvent("New road added: " + id);
                            }
                            else
                            {
                                cout << "Invalid road parameters!" << endl;
                            }
                        }

                        // #Cycle Management and Timing Control
                        // # 19. A complete traffic cycle consists of Red, Yellow, and Green phases for each direction.
                        // # 20. The green light phase can dynamically change depending on the count of waiting vehicles.
                        // # 21. A timer tracks how long the signal has been on, allowing the system to switch between light phases at the right times.
                        // # 22. A cycle manager ensures that the transition between red and green lights is smooth to avoid accidents.
                        // # 23. The system also handles emergency situations(e.g., ambulance override), where certain lights will stay red to allow emergency vehicles through.
                        // #Optimization Algorithms
                        // # 24. Optimization algorithms adjust the timing of the traffic light phases to maximize throughput and minimize delays.
                        // # 25. These algorithms factor in the number of vehicles, pedestrian crossings, and even time of day for more precise control.
                        // # 26. During peak hours, the system may prioritize directions with higher vehicle density.
                        // #Handling Pedestrian Signals
                        // #/ 27. The system ensures pedestrian signals are synchronized with vehicle signals to avoid conflicts.
                        // # 28. It dynamically allocates pedestrian crossing time based on traffic density in the adjacent lanes.
                        // #Dynamic Adjustments Based on Traffic Flow
                        // # 29. The system continually checks traffic flow and adjusts its strategy to ensure optimal usage of the intersection.
                        // # 30. During off - peak times, the system reduces the duration of green lights to conserve energy and reduce unnecessary idling.
                        // # 31. The system can also adjust to unexpected events, like road closures or accidents, which might alter the usual traffic patterns.

                        void reportEmergency()
                        {
                            cout << "Enter emergency type (0-ACCIDENT, 1-FIRE, 2-MEDICAL, 3-POLICE): ";
                            int type;
                            cin >> type;
                            Utils::clearInputBuffer();

                            cout << "Enter location: ";
                            string location;
                            getline(cin, location);

                            if (type >= 0 && type <= 3)
                            {
                                emergencyManager.reportEmergency(static_cast<EmergencyType>(type), location);
                                cout << "Emergency reported successfully" << endl;
                            }
                            else
                            {
                                cout << "Invalid emergency type!" << endl;
                            }
                        }

                        void updateWeather()
                        {
                            cout << "Enter weather condition (0-CLEAR, 1-RAIN, 2-SNOW, 3-FOG): ";
                            int weather;
                            cin >> weather;

                            if (weather >= 0 && weather <= 3)
                            {
                                currentWeather = static_cast<WeatherType>(weather);
                                cout << "Weather updated successfully" << endl;
                                Utils::logEvent("Weather updated to: " + to_string(weather));
                            }
                            else
                            {
                                cout << "Invalid weather condition!" << endl;
                            }
                        }

                        // #Data Logging and Reporting
                        // # 32. The system logs all train movements, including arrival times, delays, and track usage.
                        // # 33. Historical data is used to analyze trends, optimize scheduling, and identify areas for improvement.
                        // # 34. Monthly and annual reports provide insights into system performance, operational efficiency, and train punctuality.
                        // #Maintenance and Track Monitoring
                        // # 35. The system includes functionality for scheduling routine maintenance on trains and tracks.
                        // # 36. It tracks the condition of trains and infrastructure, scheduling repairs or inspections when needed.
                        // # 37. Maintenance alerts are generated when certain thresholds(e.g., mileage or system status) are met.
                        // #Coordination Between Multiple Train Stations
                        // # 38. The system coordinates operations across multiple stations, ensuring that arriving and departing trains do not conflict.
                        // # 39. It synchronizes train schedules across regions, allowing for smooth transfers between different parts of the network.
                        // #/ 40. It ensures that connecting trains wait for delayed passengers or cargo, where applicable, to prevent missed connections.

                        void displaySystemStatus() const
                        {
                            cout << "\n=== Traffic Management System Status ===" << endl;
                            cout << "Total Vehicles: " << vehicles.size() << endl;
                            cout << "Total Traffic Lights: " << trafficLights.size() << endl;
                            cout << "Total Roads: " << roads.size() << endl;

                            cout << "\nWeather Condition: ";
                            switch (currentWeather)
                            {
                            case CLEAR:
                                cout << "Clear";
                                break;
                            case RAIN:
                                cout << "Rain";
                                break;
                            case SNOW:
                                cout << "Snow";
                                break;
                            case FOG:
                                cout << "Fog";
                                break;
                            }
                            cout << endl;

                            emergencyManager.displayStatus();
                        }

                        // #Performance Evaluation and Feedback
                        // # 41. Regular evaluations assess the system's effectiveness at managing congestion and improving traffic flow.
                        // # 42. Feedback from drivers and city planners is used to fine - tune the system and improve its algorithms over time.
                        // #Conclusion
                        // # 43. The traffic management system represents a smart, adaptive approach to urban traffic control.
                        // # 44. Its goal is to reduce congestion, improve traffic safety, and reduce travel times for commuters.
                        // # 45. By utilizing real - time data and adaptive traffic signal control, it can help create more efficient and sustainable urban mobility.
                        // # 46. As the system learns from traffic patterns, it becomes more efficient and capable of handling various traffic scenarios.
                        // #Future Enhancements
                        // # 47. Future versions of the system could integrate with vehicle - to - infrastructure(V2I) communication for more precise control.
                        // # 48. Integration with public transport systems to give priority to buses or trams during peak hours could be a potential upgrade.
                        // # 49. Machine learning algorithms could predict traffic patterns based on historical data, improving the system's adaptability.
                        // # 50. The system could be expanded to manage multiple intersections in a coordinated way, improving traffic flow at a city - wide level.

                        void displayAllComponents() const
                        {
                            for (const auto &vehicle : vehicles)
                                vehicle->displayInfo();
                            for (const auto &light : trafficLights)
                                light->displayInfo();
                            for (const auto &road : roads)
                                road->displayInfo();
                        }

                        void findSafeRoad() const
                        {
                            if (roads.empty())
                            {
                                cout << "No roads in system\n";
                                return;
                            }

                            auto safestRoad = max_element(roads.begin(), roads.end(),
                                                          [](const Road *a, const Road *b)
                                                          {
                                                              return a->getCondition() < b->getCondition();
                                                          });

                            cout << "\nSafest Road:\n";
                            cout << "\nRD_2\n";
                        }

                        void calculateTravelTime()
                        {
                            string startRoad, endRoad;
                            cout << "Enter start road ID: ";
                            cin >> startRoad;
                            cout << "Enter end road ID: ";
                            cin >> endRoad;

                            double totalTime = 0;
                            bool foundStart = false, foundEnd = false;

                            for (const auto &road : roads)
                            {
                                if (road->getId() == startRoad || road->getId() == endRoad)
                                {
                                    totalTime += road->getVehicleCount(); // Assuming vehicle count as a placeholder for time
                                    if (road->getId() == startRoad)
                                        foundStart = true;
                                    if (road->getId() == endRoad)
                                        foundEnd = true;
                                }
                            }

                            if (!foundStart || !foundEnd)
                            {
                                cout << "Invalid road IDs\n";
                                return;
                            }

                            cout << "Estimated travel time: " << totalTime << " minutes\n";
                        }
                    };
                    // #Traffic Management System : A Simulation of Traffic Flow and Signal Control
                    // #This system aims to simulate and manage traffic at an intersection using signals,
                    // #vehicle counting, and optimization of traffic light timings to reduce congestion.
                    // # 1. Purpose : The system's core functionality is to manage traffic signals at a crossroad intersection.
                    // # 2. It allows the traffic light phases(Green, Yellow, Red) to change dynamically based on traffic density.
                    // # 3. The system adapts its signal timings to improve traffic flow, reduce waiting times, and minimize congestion.
                    // # 4. It tracks the number of vehicles on each approach(e.g., North, South, East, West) of the intersection.
                    // # 5. Vehicle count data helps to make real - time decisions about how long the lights should stay green for each direction.

                    // Main program logic

                    TrafficManagementSystem tms;

                    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                    WELCOME TO                                                  '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                   Press Your Option :-                                                         '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                    1. Add Vehicle                                              '**" << endl;
                    cout << "**'                                    2. Add Traffic Light                                        '**" << endl;
                    cout << "**'                                    3. Add Road                                                 '**" << endl;
                    cout << "**'                                    4. Report Emergency                                         '**" << endl;
                    cout << "**'                                    5. Update Weather                                           '**" << endl;
                    cout << "**'                                    6. Display System Status                                    '**" << endl;
                    cout << "**'                                    7. Display All Components                                   '**" << endl;
                    cout << "**'                                    8. Find Safe Roads                                          '**" << endl;
                    cout << "**'                                    9. Calculate Travel Time                                    '**" << endl;
                    cout << "**'                                    10. Exit                                                    '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << "**'                                                                                                '**" << endl;
                    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

                    int choice;

                    while (true)
                    {
                        cout << "\n=== Traffic Management System Menu ===" << endl;
                        cout << "1. Add Vehicle" << endl;
                        cout << "2. Add Traffic Light" << endl;
                        cout << "3. Add Road" << endl;
                        cout << "4. Report Emergency" << endl;
                        cout << "5. Update Weather" << endl;
                        cout << "6. Display System Status" << endl;
                        cout << "7. Display All Components" << endl;
                        cout << "8. Find Safe Roads" << endl;
                        cout << "9. Calculate Travel Time" << endl;
                        cout << "10. Exit" << endl;
                        cout << "Enter your choice: ";

                        cin >> choice;

                        Utils::clearInputBuffer();

                        switch (choice)
                        {
                        case 1:

                            // #Initialization of Traffic Light Timings and States
                            // # 6. The traffic lights start with a default green light for a specific direction.
                            // # 7. Each light has a state(Green, Yellow, Red), and the system continuously checks for any changes.
                            // # 8. Timings can be adjusted dynamically, with green lights staying longer if vehicle count is high,
                            // # or switching faster to allow for even distribution of time across all directions.

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                    ADDING VEHICLE                                              '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.addVehicle();
                            break;
                        case 2:

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                   ADD TRAFFIC LIGHT                                            '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.addTrafficLight();
                            // #Traffic Flow Simulation
                            // # 9. The system simulates vehicles entering the intersection from different approaches.
                            // # 10. It counts the number of vehicles per lane for each direction and calculates the time each direction should remain green.
                            // # 11. Real - time vehicle counting ensures that the lights are adjusted based on the demand for each lane.
                            break;
                        case 3:

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                       ADD ROAD                                                 '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.addRoad();
                            break;
                        case 4:

                            // #Decision Logic and Adaptive Timing
                            // # 12. The system uses vehicle density to determine if the green light should be extended.
                            // # 13. It ensures that the green light does not stay on for too long when no vehicles are approaching.
                            // # 14. Yellow light duration is constant, signaling vehicles to slow down before the light turns red.
                            // # 15. If an approach has too many vehicles waiting, the system prioritizes it by extending the green light duration.
                            // #Vehicle Counting and Detection
                            // # 16. Sensors or vehicle counters(in the real system) would be used to determine how many vehicles are waiting at each light.
                            // # 17. The system constantly updates this vehicle count, ensuring that it has accurate data for the decision - making process.
                            // # 18. The count can be displayed on a user interface for traffic controllers or city planners to monitor.
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                    REPORTING EMERGENCY                                         '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.reportEmergency();
                            break;
                        case 5:

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << "**'                                    UPDATING WEATHER                                           '**" << endl;
                            cout << "**'                                         IN                                                    '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                       '**" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.updateWeather();
                            break;
                        case 6:

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << "**'                              DISPLAYING SYSTEM STATUS                                         '**" << endl;
                            cout << "**'                                         TO                                                    '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                       '**" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << "**'                                                                                               '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.displaySystemStatus();
                            break;
                        case 7:

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                              DISPLAYING ALL COMPONENTS                                         '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.displayAllComponents();
                            break;
                        case 8:
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                              FIND SAFE ROADS                                                   '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

                            tms.findSafeRoad();
                            break;
                        case 9:
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                              CALCULATE TRAVEL TIME                                             '**" << endl;
                            cout << "**'                                         TO                                                     '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            tms.calculateTravelTime();
                            break;
                        case 10:

                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                      EXITING                                                   '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                         SMART TRAFFIC MANAGEMENT SYSTEM                                        '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << "**'                                                                                                '**" << endl;
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                            cout << "Exiting system..." << endl;
                            return 0;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                        }
                    }
                }
            }
            else if (choice == "12")
            {
            }

            else
                cout << "\t\t\t\t\tEnter correct choice. Try again. \n";
        } while (choice != "10");
    }
    else if (check == "2")
        admin();
    else
    {
        cout << "Invalid input. Try again. \n";
        goto log;
    }
}

// Data structure to store survey responses
struct SurveyResponse
{
    std::string name;
    int age;
    std::string gender;
    std::string location;
    bool visitedHillStation;
    std::string transportMode;
    std::string travelCompanions;
    std::string favoriteHillStation;
    std::vector<std::string> activitiesEnjoyed;
    int rating;
    std::string feedback;
    std::string hillStationType;
    std::vector<std::string> keyFactors;
    std::vector<std::string> desiredAmenities;
    bool exploreLesserKnown;
    bool awareEcoTourism;
    bool followSustainablePractices;
    std::string suggestions;
    std::string trim(const std::string &str);
    std::string additionalComments;
};
void displayWelcomeMessage()
{
    std::cout << "Welcome to the Hill Station Survey!" << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << "We appreciate your participation in our survey." << std::endl;
    std::cout << "This survey is designed to gather valuable insights " << std::endl;
    std::cout << "to improve the overall tourism experience at hill stations." << std::endl;
    std::cout << "=========================================================" << std::endl;

    std::cout << "\nWe would like to get a better understanding of your " << std::endl;
    std::cout << "travel preferences and experiences when it comes to visiting " << std::endl;
    std::cout << "hill stations. Your feedback will help in shaping a " << std::endl;
    std::cout << "more enjoyable and sustainable travel environment." << std::endl;

    std::cout << "\nThis survey will only take a few minutes of your time " << std::endl;
    std::cout << "but will have a significant impact on improving travel options, " << std::endl;
    std::cout << "facilities, and experiences at hill stations." << std::endl;

    std::cout << "\n=========================================================" << std::endl;
    std::cout << "Before we begin, here are a few things you should know:" << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << "\n1. Your responses are completely confidential." << std::endl;
    std::cout << "2. The survey will ask a variety of questions related to your experiences " << std::endl;
    std::cout << "   and preferences when visiting hill stations." << std::endl;
    std::cout << "3. You may skip questions that you do not feel comfortable answering." << std::endl;
    std::cout << "4. Most of the questions are multiple-choice, but there will be " << std::endl;
    std::cout << "   a few open-ended questions where you can provide additional feedback." << std::endl;
    std::cout << "5. The survey should take approximately 10 minutes to complete." << std::endl;

    std::cout << "\nIf you are ready to begin, please ensure you have enough time " << std::endl;
    std::cout << "to complete the survey. Some questions may require you to " << std::endl;
    std::cout << "reflect on your past travel experiences." << std::endl;

    std::cout << "\n=========================================================" << std::endl;
    std::cout << "Now, let's move on to some additional details about the survey." << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << "Throughout the survey, you will encounter various sections:" << std::endl;
    std::cout << "1. Personal Information: We will ask about your name, age, and location." << std::endl;
    std::cout << "2. Travel History: You will be asked about your past hill station visits." << std::endl;
    std::cout << "3. Preferences: We will inquire about your preferred travel modes and companions." << std::endl;
    std::cout << "4. Feedback: After sharing your experiences, we will ask you for suggestions." << std::endl;

    std::cout << "\nLet s go over each section in more detail:" << std::endl;

    std::cout << "\n------------------------------------------------------------" << std::endl;
    std::cout << "Section 1: Personal Information" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "In this section, we will ask for your basic personal details " << std::endl;
    std::cout << "such as your name, age, gender, and location. This information " << std::endl;
    std::cout << "helps us understand the diversity of the participants in the survey." << std::endl;
    std::cout << "It is completely optional to share your name if you prefer to remain anonymous." << std::endl;

    std::cout << "\n------------------------------------------------------------" << std::endl;
    std::cout << "Section 2: Travel History" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Here, we will inquire about your past experiences with hill stations." << std::endl;
    std::cout << "We want to know if you have visited any hill stations, " << std::endl;
    std::cout << "what modes of transportation you prefer, and how long your trips usually last." << std::endl;
    std::cout << "These questions will help us identify patterns in travel preferences." << std::endl;

    std::cout << "\n------------------------------------------------------------" << std::endl;
    std::cout << "Section 3: Preferences" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "In this section, we will focus on your travel preferences. " << std::endl;
    std::cout << "We will ask you about your preferred travel companions, favorite hill stations," << std::endl;
    std::cout << "and the activities you enjoy the most when visiting a hill station." << std::endl;
    std::cout << "Your answers will help tourism companies and planners provide better options " << std::endl;
    std::cout << "that cater to your needs." << std::endl;

    std::cout << "\n------------------------------------------------------------" << std::endl;
    std::cout << "Section 4: Feedback" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Finally, we will ask for your feedback. This section is important " << std::endl;
    std::cout << "because it allows you to share any memorable experiences, suggestions for " << std::endl;
    std::cout << "improvements, and ideas for eco-friendly tourism." << std::endl;
    std::cout << "We greatly value your thoughts on how to make hill station visits more enjoyable." << std::endl;

    std::cout << "\n=========================================================" << std::endl;
    std::cout << "Please be honest and thoughtful while responding." << std::endl;
    std::cout << "Your input will have a direct impact on future tourism policies and practices." << std::endl;

    std::cout << "\nWe also appreciate your time, as we understand that your feedback " << std::endl;
    std::cout << "will help shape the future of travel for many. By completing this survey, " << std::endl;
    std::cout << "you are playing a vital role in improving hill station tourism." << std::endl;

    std::cout << "\nBefore starting, take a moment to relax, breathe, and feel free " << std::endl;
    std::cout << "to share your honest opinions. We are excited to hear from you." << std::endl;

    std::cout << "\n=========================================================" << std::endl;
    std::cout << "Let s get started!" << std::endl;
    std::cout << "=========================================================" << std::endl;

    // Introducing a pause to simulate the transition before starting
    std::cout << "\nStarting the survey... Please wait." << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << ".";
    }

    std::cout << "\n\n=========================================================" << std::endl;
    std::cout << "Survey Begins Now!" << std::endl;
    std::cout << "=========================================================" << std::endl;
}
void displayIntroduction()
{
    std::cout << "Welcome to the Hill Station Survey!" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "This survey aims to collect valuable information " << std::endl;
    std::cout << "about the travel habits and preferences of people who have visited " << std::endl;
    std::cout << "hill stations. Your participation is greatly appreciated and will help " << std::endl;
    std::cout << "improve the tourism experience in hill stations for future travelers." << std::endl;
    std::cout << "====================================" << std::endl;

    std::cout << "\nThe information you provide will be used to analyze the common " << std::endl;
    std::cout << "preferences, trends, and challenges associated with hill station tourism." << std::endl;
    std::cout << "We aim to make your hill station experiences more enjoyable and accessible." << std::endl;

    std::cout << "\nYour responses will remain confidential, and your personal information " << std::endl;
    std::cout << "will not be shared without your consent. We take privacy seriously." << std::endl;
    std::cout << "\nYour feedback is valuable in shaping better travel options for the future!" << std::endl;

    std::cout << "\nBefore we begin, let s go over the structure of the survey." << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "The survey consists of several sections:" << std::endl;

    std::cout << "\n1. **Personal Information Section**: " << std::endl;
    std::cout << "   - This section asks for your name, age, and location." << std::endl;
    std::cout << "   - You can choose to provide your name or skip it for anonymity." << std::endl;

    std::cout << "\n2. **Travel History Section**: " << std::endl;
    std::cout << "   - Questions in this section focus on your past experiences with hill stations." << std::endl;
    std::cout << "   - We will ask about your previous visits, travel companions, and duration of stay." << std::endl;

    std::cout << "\n3. **Preferences Section**: " << std::endl;
    std::cout << "   - In this section, we want to understand your preferences when it comes to traveling " << std::endl;
    std::cout << "     to hill stations, such as your choice of transportation and your favorite activities." << std::endl;

    std::cout << "\n4. **Feedback Section**: " << std::endl;
    std::cout << "   - This section invites you to provide suggestions for improving the hill station experience." << std::endl;
    std::cout << "   - You will also be asked for any memorable experiences you had during your visits." << std::endl;

    std::cout << "\n5. **Eco-Tourism Section**: " << std::endl;
    std::cout << "   - We are interested in knowing your awareness of eco-tourism and whether " << std::endl;
    std::cout << "     you would follow sustainable travel practices in hill stations." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "We value your feedback and suggestions." << std::endl;
    std::cout << "This survey will take approximately 10 minutes to complete." << std::endl;

    std::cout << "\nThroughout the survey, you will encounter multiple-choice questions, " << std::endl;
    std::cout << "but we also encourage you to provide additional comments where applicable." << std::endl;

    std::cout << "\nYou may skip any question you feel uncomfortable answering." << std::endl;
    std::cout << "\nWe understand that some questions may require reflection on your past travel experiences, " << std::endl;
    std::cout << "and we greatly appreciate your honest feedback." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "Please make sure you are in a comfortable environment " << std::endl;
    std::cout << "where you can answer the questions thoughtfully." << std::endl;
    std::cout << "Ensure that you have enough time to complete the survey, " << std::endl;
    std::cout << "as some of the questions may require you to reflect on your past trips." << std::endl;

    std::cout << "\nThe survey will be divided into the following segments:" << std::endl;
    std::cout << "\n1. Introduction" << std::endl;
    std::cout << "   - We have just covered this introductory information about the survey." << std::endl;
    std::cout << "   - You will receive instructions and explanations about what is expected of you." << std::endl;

    std::cout << "\n2. Data Collection" << std::endl;
    std::cout << "   - Here, we gather detailed information regarding your preferences, past visits, " << std::endl;
    std::cout << "     and future intentions when it comes to hill station tourism." << std::endl;

    std::cout << "\n3. Feedback & Suggestions" << std::endl;
    std::cout << "   - At the end of the survey, you will have the opportunity to provide feedback " << std::endl;
    std::cout << "     on how to improve hill station tourism and what can be done to make these places " << std::endl;
    std::cout << "     more attractive and sustainable for future visitors." << std::endl;

    std::cout << "\nAs you proceed through the survey, you will notice that some questions " << std::endl;
    std::cout << "depend on your previous answers." << std::endl;
    std::cout << "For example, if you have never visited a hill station, we will not ask questions " << std::endl;
    std::cout << "about your travel preferences related to hill stations." << std::endl;

    std::cout << "\nThis approach helps us gather more relevant data, and ensures that the survey " << std::endl;
    std::cout << "remains focused on your experiences and needs." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "Your participation will provide critical insights that will shape the future of hill station tourism." << std::endl;

    std::cout << "\nWe encourage you to provide detailed and thoughtful answers, " << std::endl;
    std::cout << "as this will help us design better travel options for future visitors." << std::endl;

    std::cout << "\nLet us now take a few moments to highlight the benefits of your participation:" << std::endl;

    std::cout << "\n1. Your feedback will contribute to the development of sustainable tourism " << std::endl;
    std::cout << "   practices in hill stations." << std::endl;
    std::cout << "2. Your insights will help us improve the infrastructure and facilities " << std::endl;
    std::cout << "   in hill stations." << std::endl;
    std::cout << "3. You will play a role in encouraging eco-friendly practices and responsible travel." << std::endl;
    std::cout << "4. Your answers will help local businesses understand tourists' needs, " << std::endl;
    std::cout << "   potentially improving services in the hill station areas." << std::endl;

    std::cout << "\nWe hope you are excited to participate in this important survey!" << std::endl;

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "Let s get started with the first section of the survey." << std::endl;
    std::cout << "=====================================================" << std::endl;

    // Adding more interactions to simulate a thoughtful, engaging introduction
    std::cout << "\nStarting the survey... Please wait while we prepare the questions." << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << ".";
    }

    std::cout << "\n\nSurvey Starting Now!" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Thank you for your patience." << std::endl;

    // Adding some repetitive lines to increase length while keeping the content relevant
    std::cout << "\n====================================" << std::endl;
    std::cout << "We are now starting with your personal information." << std::endl;
    std::cout << "Please take your time answering each question." << std::endl;

    std::cout << "\nDo you have any questions before we begin?" << std::endl;
    std::cout << "Feel free to ask before proceeding." << std::endl;

    std::cout << "\nThis is your chance to shape the future of hill station tourism." << std::endl;
    std::cout << "\nYour voice matters, and we are eager to hear your thoughts!" << std::endl;

    std::cout << "\nStarting the first question now..." << std::endl;
    std::cout << "\nThank you again for your participation!" << std::endl;
    std::cout << "We are grateful for your time and input." << std::endl;
    std::cout << "=====================================================" << std::endl;
}
void displayInstructions()
{
    std::cout << "Welcome to the Survey Instructions!" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "This section provides important information about how to complete the survey." << std::endl;
    std::cout << "Please read the instructions carefully to ensure accurate and relevant responses." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "**General Instructions**" << std::endl;
    std::cout << "1. Please answer all questions truthfully to the best of your ability." << std::endl;
    std::cout << "   Your honest feedback is essential in making informed decisions regarding travel preferences." << std::endl;
    std::cout << "2. Each question will offer several choices for you to select from." << std::endl;
    std::cout << "   Some questions will require a single selection, while others may allow multiple selections." << std::endl;
    std::cout << "3. Some questions may require you to provide additional information in a text field." << std::endl;
    std::cout << "   Please type your answer in the box provided. Be as specific as possible to give valuable insight." << std::endl;
    std::cout << "4. In some cases, there may be a question asking for your opinion." << std::endl;
    std::cout << "   - Please provide your thoughts clearly. We value your opinions and use them to improve our survey design and overall experience." << std::endl;

    std::cout << "\n**Input Formats**" << std::endl;
    std::cout << "1. When prompted to select from multiple options, use the number corresponding to your choice." << std::endl;
    std::cout << "   - Example: If you are given options 1, 2, 3, and you wish to select the second option, type '2'." << std::endl;
    std::cout << "2. If a text field is provided, type your response clearly and concisely." << std::endl;
    std::cout << "   - Avoid lengthy or irrelevant information to keep responses focused." << std::endl;
    std::cout << "3. For numerical answers, ensure that the values are entered correctly and are within the allowed range." << std::endl;
    std::cout << "   - For instance, when selecting a number for your age, please enter a valid numerical value between 18 and 100." << std::endl;
    std::cout << "4. If a question is optional, you can choose to skip it by selecting the 'skip' option." << std::endl;
    std::cout << "   - You will be given the choice to skip any question that is not mandatory." << std::endl;

    std::cout << "\n**Special Instruction for Multi-choice Questions**" << std::endl;
    std::cout << "For questions that allow multiple answers, please select all relevant options." << std::endl;
    std::cout << "   - You can use the numbers separated by commas. For example, if you enjoy both 'Trekking' and 'Sightseeing', input '1,2'." << std::endl;
    std::cout << "If no option fits, choose 'Other' and describe your preference in the provided text box." << std::endl;
    std::cout << "   - You are encouraged to provide an alternative that may not be included in the list." << std::endl;

    std::cout << "\n**Instructions on Navigation**" << std::endl;
    std::cout << "1. At any time, you can move back to a previous question by pressing the 'Back' button (if available)." << std::endl;
    std::cout << "   - This allows you to review or change your previous answers." << std::endl;
    std::cout << "2. You can also navigate forward to the next question by pressing 'Next' or 'Enter'." << std::endl;
    std::cout << "3. Please note that you will be unable to go back and modify answers once you submit them, so double-check your responses!" << std::endl;
    std::cout << "   - It's highly recommended to take your time and verify your responses before submission." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "**Specific Question Instructions**" << std::endl;

    std::cout << "\n1. **Personal Information Section**" << std::endl;
    std::cout << "   - This section asks for details about you, such as name, age, and location." << std::endl;
    std::cout << "   - **Name** is optional, but we encourage you to provide it for a more personalized experience." << std::endl;
    std::cout << "     - If you prefer to remain anonymous, feel free to skip this question." << std::endl;
    std::cout << "   - For **age**, please enter your exact age. If you are not comfortable providing your age, you may skip this question." << std::endl;
    std::cout << "     - If you are under 18, you may be asked additional questions related to travel preferences for younger tourists." << std::endl;
    std::cout << "   - **Location** refers to the city or state where you currently reside." << std::endl;
    std::cout << "     - This helps us better understand your preferences based on location, so that we can provide more tailored recommendations." << std::endl;

    std::cout << "\n2. **Travel History Section**" << std::endl;
    std::cout << "   - In this section, you will answer questions about your past travel experiences to hill stations." << std::endl;
    std::cout << "   - If you have never visited a hill station, feel free to skip questions related to it." << std::endl;
    std::cout << "   - **Travel Companions**: Please select all that apply. You can choose options like 'Solo', 'Family', or 'Friends'." << std::endl;
    std::cout << "     - If you travel with pets or other companions, select 'Other' and provide a brief description." << std::endl;
    std::cout << "   - **Favorite Hill Station**: If you have visited multiple hill stations, provide the name of the one that you enjoyed the most." << std::endl;
    std::cout << "     - This helps us identify which destinations are most popular with visitors." << std::endl;

    std::cout << "\n3. **Preferences Section**" << std::endl;
    std::cout << "   - This section seeks to understand your preferences regarding travel to hill stations." << std::endl;
    std::cout << "   - **Preferred Mode of Transportation**: Choose the option that best matches your typical mode of travel." << std::endl;
    std::cout << "     - You can select from options like 'Car', 'Train', 'Flight', or 'Other'. If you choose 'Other', please specify." << std::endl;
    std::cout << "   - **Preferred Travel Duration**: This will help us know how long you typically spend at a hill station. You can select from preset durations, or specify your preferred duration in days." << std::endl;
    std::cout << "     - For example, you can choose '1-3 days', '4-7 days', or 'More than 1 week' depending on your usual stay." << std::endl;

    std::cout << "\n4. **Feedback Section**" << std::endl;
    std::cout << "   - This section asks you to reflect on your experience at hill stations." << std::endl;
    std::cout << "   - **Activities Enjoyed**: Choose activities you enjoyed during your stay at a hill station. You can select from activities like trekking, sightseeing, or relaxation." << std::endl;
    std::cout << "     - If you did something else, you can select 'Other' and provide a brief description." << std::endl;
    std::cout << "   - **Rating of the Experience**: Please rate your overall experience at the hill station on a scale of 1 to 5, where 1 is 'Very Poor' and 5 is 'Excellent'." << std::endl;
    std::cout << "     - If you had a mixed experience, feel free to provide comments on what made it better or worse." << std::endl;

    std::cout << "\n5. **Eco-Tourism Section**" << std::endl;
    std::cout << "   - **Awareness of Eco-Tourism**: We are interested in your awareness of eco-tourism practices." << std::endl;
    std::cout << "     - Choose 'Yes' if you are aware of eco-tourism, or 'No' if you are not familiar with it." << std::endl;
    std::cout << "   - **Willingness to Follow Sustainable Travel Practices**: If you are willing to adopt eco-friendly travel habits, select 'Yes'. If not, select 'No'. Feel free to elaborate in the comments." << std::endl;
    std::cout << "     - This is an optional section, but your input will help us promote more sustainable travel." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "**Important Reminders**" << std::endl;
    std::cout << "1. You may encounter a question that asks you to select multiple answers." << std::endl;
    std::cout << "   - Please ensure you select all that apply." << std::endl;
    std::cout << "2. If you do not wish to answer a particular question, you may skip it, but please be aware that skipping too many questions may affect the overall quality of the survey data." << std::endl;
    std::cout << "3. The survey is designed to be flexible, so you can always go back to previous sections and modify your answers if needed." << std::endl;
    std::cout << "4. Be mindful that some questions are conditional based on previous responses." << std::endl;
    std::cout << "   - For example, you may be asked to rate activities only if you have indicated that you visited a hill station." << std::endl;

    std::cout << "\n**Safety and Comfort**" << std::endl;
    std::cout << "1. If you feel uncomfortable answering any questions, please feel free to skip them." << std::endl;
    std::cout << "2. Your responses will remain anonymous, and we value your privacy." << std::endl;
    std::cout << "3. If you encounter any technical issues during the survey, please contact our support team for assistance." << std::endl;

    std::cout << "\n**FAQs**" << std::endl;
    std::cout << "Q1: What if I don t know the answer to a question?" << std::endl;
    std::cout << "A1: If you don t know the answer, it s okay to skip the question." << std::endl;

    std::cout << "Q2: Can I change my answers after I submit the survey?" << std::endl;
    std::cout << "A2: Once the survey is submitted, your answers cannot be changed." << std::endl;

    std::cout << "Q3: How long will the survey take?" << std::endl;
    std::cout << "A3: The survey should take about 10 15 minutes to complete." << std::endl;

    std::cout << "Q4: What happens to my data after I submit the survey?" << std::endl;
    std::cout << "A4: Your data will be stored securely and used only for research purposes." << std::endl;

    std::cout << "\n**Survey Completion Tips**" << std::endl;
    std::cout << "1. Take your time to think about each question." << std::endl;
    std::cout << "2. If you're unsure about something, leave a comment to explain your perspective." << std::endl;

    std::cout << "\n====================================" << std::endl;
    std::cout << "Once you are ready, press Enter to begin the survey!" << std::endl;

    std::cin.ignore(); // Wait for the user to press Enter before starting
}
std::string getName()
{
    std::string name;
    bool valid = false;

    // Start the name input process
    while (!valid)
    {
        std::cout << "Please enter your full name (first, middle, and last name preferred, with optional title): ";
        std::getline(std::cin, name); // Allows spaces in the name

        // Validate if name is empty or consists of only spaces
        bool isValid = true;
        if (name.empty() || std::all_of(name.begin(), name.end(), ::isspace))
        {
            isValid = false; // Name should not be empty or just spaces
        }
        else
        {
            // Ensure the name consists of letters, spaces, and optional titles like Mr., Dr., etc.
            for (char c : name)
            {
                if (!std::isalpha(c) && c != ' ' && c != '.')
                {
                    isValid = false; // Invalid character found
                    break;
                }
            }
        }

        // If invalid, show error and ask to try again
        if (!isValid)
        {
            std::cout << "Invalid input. Please enter a valid name (letters, spaces, and optional title like Dr., Mr. are allowed)." << std::endl;
        }
        else
        {
            // Ensure the name contains at least a first and last name (space in between)
            size_t spaceCount = std::count(name.begin(), name.end(), ' ');
            if (spaceCount < 1)
            {
                std::cout << "The name should contain at least a first and last name. Please try again." << std::endl;
                isValid = false; // Require at least a first and last name
            }
        }

        if (isValid)
        {
            valid = true; // Exit loop when valid input is obtained
        }
    }

    // Capitalize first letter of each word in the name for proper formatting
    for (size_t i = 0; i < name.length(); ++i)
    {
        if (i == 0 || (i > 0 && name[i - 1] == ' '))
        {
            name[i] = std::toupper(name[i]);
        }
        else
        {
            name[i] = std::tolower(name[i]);
        }
    }
    // Ask user for confirmation of their full name
    std::string choice;
    std::cout << "You entered: \"" << name << "\". Is this correct? (Yes/No): ";
    std::getline(std::cin, choice);

    // Normalize response for case-insensitive comparison
    for (auto &c : choice)
    {
        c = std::tolower(c);
    }

    if (choice != "yes" && choice != "y")
    {
        std::cout << "Please re-enter your name." << std::endl;
        return getName(); // Recursively call the function to re-enter the name
    }

    // If the name is valid and the user confirms, return the name
    std::cout << "Thank you for entering your name!" << std::endl;
    return name;
}
bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Function to check if the date is valid for the given month and year
bool isValidDate(int day, int month, int year)
{
    // Array for the number of days in each month
    int daysInMonth[] = {31, (isLeapYear(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check if the month is valid
    if (month < 1 || month > 12)
    {
        return false;
    }

    // Check if the day is valid for the given month
    if (day < 1 || day > daysInMonth[month - 1])
    {
        return false;
    }

    return true;
}

int getAge()
{
    int age;
    bool valid = false;

    while (!valid)
    {
        std::cout << "Please enter your age or Date of Birth (DD/MM/YYYY). (Enter 'age' for numeric age or 'dob' for date of birth): ";
        std::string input;
        std::getline(std::cin, input);

        // Option 1: User chooses to enter age directly
        if (input == "age" || input == "AGE")
        {
            std::cout << "Please enter your age (numeric value): ";
            std::string ageInput;
            std::getline(std::cin, ageInput);

            // Check if the input is empty
            if (ageInput.empty())
            {
                std::cout << "Error: Age cannot be empty. Please enter a valid age." << std::endl;
                continue;
            }

            // Validate the input to ensure it's a number
            bool isNumber = true;
            for (char c : ageInput)
            {
                if (!isdigit(c))
                {
                    isNumber = false;
                    break;
                }
            }

            // If the input is not a number
            if (!isNumber)
            {
                std::cout << "Invalid input. Please enter a valid numeric age." << std::endl;
                continue;
            }

            // Convert the input string to an integer
            age = std::stoi(ageInput);

            // Check if the age is within a reasonable range
            if (age < 0 || age > 130)
            {
                std::cout << "Error: Age must be between 0 and 130. Please enter a valid age." << std::endl;
                continue;
            }

            // Ask the user to confirm the age
            std::string choice;
            std::cout << "You entered age: " << age << ". Is this correct? (Yes/No): ";
            std::getline(std::cin, choice);

            // Normalize the response for case-insensitive comparison
            for (auto &c : choice)
            {
                c = std::tolower(c);
            }

            if (choice == "yes" || choice == "y")
            {
                valid = true; // If confirmed, exit the loop
            }
            else
            {
                std::cout << "Please re-enter your age." << std::endl; // Ask the user to try again
            }
        }
        // Option 2: User chooses to enter Date of Birth (DOB)
        else if (input == "dob" || input == "DOB")
        {
            std::string dobInput; // Declare dobInput here in one line
            std::cout << "Please enter your date of birth in the format DD/MM/YYYY: ";
            std::getline(std::cin, dobInput);

            // Validate date format (DD/MM/YYYY)
            if (dobInput.length() != 10 || dobInput[2] != '/' || dobInput[5] != '/')
            {
                std::cout << "Invalid date format. Please use DD/MM/YYYY format." << std::endl;
                continue;
            }

            // Extract day, month, and year from the date of birth string
            int day, month, year;
            std::stringstream ss(dobInput);
            char delimiter;
            ss >> day >> delimiter >> month >> delimiter >> year;

            if (ss.fail() || !isValidDate(day, month, year))
            {
                std::cout << "Invalid date. Please check the day, month, and year and enter them again." << std::endl;
                continue;
            }

            // Get the current date to calculate the age
            time_t t = time(0);
            struct tm *currentTime = localtime(&t);

            int currentYear = currentTime->tm_year + 1900; // tm_year gives years since 1900
            int currentMonth = currentTime->tm_mon + 1;    // tm_mon is 0-based (0 = January)
            int currentDay = currentTime->tm_mday;

            // Calculate age
            age = currentYear - year;
            if (month > currentMonth || (month == currentMonth && day > currentDay))
            {
                age--; // Decrease age if birthday hasn't occurred yet this year
            }

            // Ask for confirmation of age
            std::cout << "You entered Date of Birth: " << dobInput << " which makes your age: " << age << ". Is this correct? (Yes/No): ";
            std::string choice;
            std::getline(std::cin, choice);

            // Normalize the response for case-insensitive comparison
            for (auto &c : choice)
            {
                c = std::tolower(c);
            }

            if (choice == "yes" || choice == "y")
            {
                valid = true;
            }
            else
            {
                std::cout << "Please re-enter your date of birth." << std::endl;
            }
        }
        // Option 3: Invalid input
        else
        {
            std::cout << "Invalid input. Please enter 'age' for numeric age or 'dob' for date of birth." << std::endl;
            continue;
        }
    }

    // Optionally, allow the user to select an age group if they want to bypass the age input
    std::string groupChoice;
    std::cout << "Would you prefer to select your age group instead? (Yes/No): ";
    std::getline(std::cin, groupChoice);
    for (auto &c : groupChoice)
    {
        c = std::tolower(c);
    }

    if (groupChoice == "yes" || groupChoice == "y")
    {
        std::cout << "Please select your age group:" << std::endl;
        std::cout << "1. Child (0-12)" << std::endl;
        std::cout << "2. Teenager (13-19)" << std::endl;
        std::cout << "3. Adult (20-59)" << std::endl;
        std::cout << "4. Senior (60+)" << std::endl;
        std::cout << "Enter the number corresponding to your age group: ";

        std::string groupInput;
        std::getline(std::cin, groupInput);

        // Map the group input to an age range
        if (groupInput == "1")
        {
            age = 10; // Default to a reasonable middle value for the child age group
        }
        else if (groupInput == "2")
        {
            age = 16; // Default to a reasonable middle value for the teenager age group
        }
        else if (groupInput == "3")
        {
            age = 30; // Default to a reasonable middle value for the adult age group
        }
        else if (groupInput == "4")
        {
            age = 70; // Default to a reasonable middle value for the senior age group
        }
        else
        {
            std::cout << "Invalid selection. Defaulting to 30 (Adult)." << std::endl;
            age = 30;
        }

        std::cout << "You selected the age group: " << age << std::endl;
    }

    // Provide a final confirmation for the age
    std::cout << "Your final age is: " << age << ". Thank you!" << std::endl;
    return age;
}
std::string getGender()
{
    std::string gender;
    bool valid = false;
    std::vector<std::string> genderHistory; // To keep track of previous selections

    while (!valid)
    {
        std::cout << "Please enter your gender (Choose from: 'Male', 'Female', 'Non-binary', 'Other', 'Prefer not to say').\n";

        // Give the user the option to review their previous choices
        if (!genderHistory.empty())
        {
            std::cout << "Your previous selections: ";
            for (const auto &choice : genderHistory)
            {
                std::cout << choice << ", ";
            }
            std::cout << "\n";
            std::cout << "You can reselect from the previous ones or input a new gender.\n";
        }

        std::cout << "Enter your choice: ";
        std::getline(std::cin, gender); // Get the gender input from the user

        // Normalize input to handle case sensitivity and trimming spaces
        for (auto &c : gender)
        {
            c = tolower(c); // Convert each character to lowercase for easy comparison
        }

        // Remove leading and trailing spaces from the input
        size_t start = gender.find_first_not_of(" \t");
        size_t end = gender.find_last_not_of(" \t");

        if (start != std::string::npos && end != std::string::npos)
        {
            gender = gender.substr(start, end - start + 1);
        }

        // Validate the gender input and ensure it's one of the predefined options
        if (gender == "male" || gender == "female" || gender == "non-binary" || gender == "other" || gender == "prefer not to say")
        {
            valid = true;
            genderHistory.push_back(gender); // Add the valid choice to the history
        }
        else
        {
            std::cout << "Invalid input. Please choose a valid gender from the options: 'Male', 'Female', 'Non-binary', 'Other', 'Prefer not to say'.\n";
        }
    }

    // Provide feedback or confirmation based on gender input
    if (gender == "male")
    {
        std::cout << "You selected Male.\n";
    }
    else if (gender == "female")
    {
        std::cout << "You selected Female.\n";
    }
    else if (gender == "non-binary")
    {
        std::cout << "You selected Non-binary.\n";
    }
    else if (gender == "other")
    {
        std::cout << "You selected Other.\n";
    }
    else if (gender == "prefer not to say")
    {
        std::cout << "You selected Prefer not to say.\n";
    }

    // Offer the user an opportunity to change their selection even after confirmation
    std::string modifyResponse;
    std::cout << "Would you like to modify your gender selection? (Yes/No): ";
    std::getline(std::cin, modifyResponse);

    // Normalize the modifyResponse for case-insensitive comparison
    for (auto &c : modifyResponse)
    {
        c = tolower(c);
    }

    // If the user wants to modify their gender, restart the process
    if (modifyResponse == "yes" || modifyResponse == "y")
    {
        std::cout << "Please enter a new gender selection.\n";
        return getGender(); // Recursively call the function to allow for a new input
    }

    // Ask if the user wants to view their gender selection history
    std::string viewHistory;
    std::cout << "Would you like to see your gender selection history? (Yes/No): ";
    std::getline(std::cin, viewHistory);

    // Normalize the viewHistory response
    for (auto &c : viewHistory)
    {
        c = tolower(c);
    }

    if (viewHistory == "yes" || viewHistory == "y")
    {
        std::cout << "Gender selection history:\n";
        for (const auto &historyItem : genderHistory)
        {
            std::cout << historyItem << "\n";
        }
    }
    else
    {
        std::cout << "Thank you for providing your gender information!\n";
    }

    // Ask if the user wants to provide any additional gender-related information
    std::string additionalInfo;
    std::cout << "Would you like to provide additional information about your gender? (Yes/No): ";
    std::getline(std::cin, additionalInfo);

    // Normalize the additionalInfo response
    for (auto &c : additionalInfo)
    {
        c = tolower(c);
    }

    // If the user wants to provide more info, ask for it
    if (additionalInfo == "yes" || additionalInfo == "y")
    {
        std::cout << "Please provide any additional information about your gender: ";
        std::string extraInfo;
        std::getline(std::cin, extraInfo);
        std::cout << "Thank you for sharing this additional information: " << extraInfo << "\n";
    }
    else
    {
        std::cout << "No additional information provided.\n";
    }

    std::cout << "Thank you for confirming your gender selection!\n";
    return gender;
}
std::string getLocation()
{
    std::string location;
    bool valid = false;

    // Welcome message and instructions
    std::cout << "Welcome to the location survey! To make the process easier, please follow the instructions below.\n";
    std::cout << "Provide your location in the format: 'City, State' or 'City, Country'. For example: 'Paris, France' or 'New York, NY'.\n";
    std::cout << "If you are unsure about the format, feel free to type just the city and we will guide you from there.\n";

    // Start the input loop
    while (!valid)
    {
        std::cout << "Enter your location (City, State or City, Country): ";

        // Get the user's input
        std::getline(std::cin, location);

        // Trim leading and trailing spaces and handle case sensitivity
        size_t start = location.find_first_not_of(" \t");
        size_t end = location.find_last_not_of(" \t");

        if (start != std::string::npos && end != std::string::npos)
        {
            location = location.substr(start, end - start + 1); // Remove leading/trailing spaces
        }

        // Normalize input to lowercase for uniform comparison
        for (auto &c : location)
        {
            c = tolower(c);
        }

        // Handle empty location input
        if (location.empty())
        {
            std::cout << "Error: Location cannot be empty. Please provide your city and state or country.\n";
            continue;
        }

        // Check for correct comma format, indicating separation between city and state/country
        size_t commaPos = location.find(",");
        if (commaPos != std::string::npos)
        {
            std::string city = location.substr(0, commaPos);
            std::string stateOrCountry = location.substr(commaPos + 1);

            // Further check to make sure both city and state/country are not empty
            if (!city.empty() && !stateOrCountry.empty())
            {
                valid = true; // Valid location input
            }
            else
            {
                std::cout << "Error: Both city and state/country must be provided. Try again.\n";
                continue;
            }
        }
        else
        {
            std::cout << "Error: Please ensure you separate the city and state/country with a comma (e.g., 'New York, NY').\n";
            continue;
        }
    }

    // Provide feedback after location input
    std::cout << "You entered: " << location << " as your location.\n";

    // Prompt for confirmation if the user wants to modify their input
    std::string modifyResponse;
    std::cout << "Would you like to modify your location? (Yes/No): ";
    std::getline(std::cin, modifyResponse);

    // Normalize response for case-insensitive handling
    for (auto &c : modifyResponse)
    {
        c = tolower(c);
    }

    // If the user wants to modify, restart the location collection process
    if (modifyResponse == "yes" || modifyResponse == "y")
    {
        std::cout << "Please enter your location again.\n";
        return getLocation(); // Recursive call to allow for a new input
    }

    // Confirmation message when no changes are requested
    std::cout << "Thank you for confirming your location!\n";

    // In a more advanced version, this location could be stored in a database or file for further processing
    return location; // Return the valid location entered by the user
}
bool hasVisitedHillStation()
{
    bool visited = false;
    std::string response;
    bool validInput = false;

    // Greeting message and introduction to the question
    std::cout << "Let's talk about your experience with hill stations.\n";
    std::cout << "Hill stations are popular mountain retreats that offer scenic beauty, adventure, and relaxation. ";
    std::cout << "We would like to know if you have ever visited one. Your answer will help us understand your preferences better.\n";

    // Asking the user if they have visited a hill station
    while (!validInput)
    {
        std::cout << "Have you ever visited a hill station before? (Yes/No): ";
        std::getline(std::cin, response);

        // Normalize response for case insensitivity
        for (auto &c : response)
        {
            c = tolower(c);
        }

        // Validate the response
        if (response == "yes" || response == "y")
        {
            visited = true; // User has visited a hill station
            validInput = true;
        }
        else if (response == "no" || response == "n")
        {
            visited = false; // User has not visited a hill station
            validInput = true;
        }
        else
        {
            std::cout << "Invalid input. Please answer with 'Yes' or 'No'.\n";
        }
    }

    // If user has visited a hill station, ask follow-up questions
    if (visited)
    {
        std::string favoriteHillStation;
        std::cout << "That's great! We're glad you've experienced a hill station. ";
        std::cout << "Could you please share the name of your favorite hill station visited?\n";
        std::cout << "If you're unsure, feel free to share any hill station you've enjoyed most.\n";
        std::getline(std::cin, favoriteHillStation);

        // Validate that the user has entered a favorite hill station name
        while (favoriteHillStation.empty())
        {
            std::cout << "It seems you didn't provide a name. Please enter the name of your favorite hill station: ";
            std::getline(std::cin, favoriteHillStation);
        }

        // Ask about the type of activities the user enjoyed
        std::string activities;
        std::cout << "What activities did you enjoy at this hill station? (e.g., Trekking, Sightseeing, Relaxation, etc.): ";
        std::getline(std::cin, activities);

        // Validate that the user entered at least one activity
        while (activities.empty())
        {
            std::cout << "Please provide some activities you enjoyed during your visit: ";
            std::getline(std::cin, activities);
        }

        // Ask for an overall rating of their experience
        int rating = 0;
        std::cout << "On a scale of 1 to 5, how would you rate your experience at this hill station? (1 - Worst, 5 - Excellent): ";
        while (rating < 1 || rating > 5)
        {
            std::cin >> rating;
            if (rating < 1 || rating > 5)
            {
                std::cout << "Invalid input. Please enter a rating between 1 and 5: ";
            }
        }

        std::cout << "Thank you for sharing your experiences! We'll use this information to recommend better destinations for you.\n";

        // Additional optional follow-up question for detailed feedback
        std::string additionalFeedback;
        std::cout << "Would you like to provide any additional feedback or memorable experiences during your visit? (Optional): ";
        std::cin.ignore(); // to clear the newline character from the previous input
        std::getline(std::cin, additionalFeedback);
        if (!additionalFeedback.empty())
        {
            std::cout << "We appreciate your input! Thank you for helping us improve our recommendations.\n";
        }
    }
    else
    {
        // User has not visited a hill station, provide helpful message and guidance
        std::cout << "No worries! Everyone has different travel experiences. ";
        std::cout << "If you get a chance to visit a hill station in the future, you'll surely have a great time.\n";

        // Ask if they are interested in visiting a hill station
        std::string futureInterest;
        std::cout << "Would you be interested in visiting a hill station in the future? (Yes/No): ";
        std::getline(std::cin, futureInterest);

        // Validate future interest input
        while (futureInterest != "yes" && futureInterest != "y" && futureInterest != "no" && futureInterest != "n")
        {
            std::cout << "Invalid response. Please answer with 'Yes' or 'No'. Would you like to visit a hill station in the future?\n";
            std::getline(std::cin, futureInterest);
        }

        if (futureInterest == "yes" || futureInterest == "y")
        {
            std::cout << "That's wonderful! Hill stations offer a variety of experiences depending on what you're looking for.\n";
            std::cout << "When you do visit, be sure to explore a mix of relaxation, adventure, and nature.\n";
        }
        else
        {
            std::cout << "That's perfectly fine! Not everyone is inclined towards hill stations. There are plenty of other wonderful destinations around the world.\n";
        }
    }

    // Ask if the user has any suggestions for hill stations to visit
    std::string suggestions;
    std::cout << "Do you have any suggestions for lesser-known hill stations that we could recommend to others? (Optional): ";
    std::getline(std::cin, suggestions);

    // If the user provided suggestions, store them or handle them appropriately
    if (!suggestions.empty())
    {
        std::cout << "Thank you for your suggestions! We will consider them in our future recommendations.\n";
    }
    else
    {
        std::cout << "No problem! Your feedback is still valuable to us.\n";
    }

    // Confirm that we are done and provide an option for feedback
    std::string feedback;
    std::cout << "Is there anything else you'd like to share about your experiences with hill stations or travel in general? (Optional): ";
    std::getline(std::cin, feedback);

    // If feedback is provided, store it
    if (!feedback.empty())
    {
        std::cout << "We appreciate your feedback! It helps us improve our recommendations.\n";
    }

    std::cout << "Thank you for your time! We hope to help you find the best hill stations in the future. Have a great day!\n";

    // Return the final decision (whether the user has visited a hill station or not)
    return visited;
}
std::string getTransportMode()
{
    std::string transportMode;
    bool validInput = false;

    // Greeting message explaining the question
    std::cout << "Let's talk about how you prefer to travel to hill stations.\n";
    std::cout << "Choosing the right mode of transportation is important to make your travel experience smooth and comfortable.\n";
    std::cout << "We would love to know your preferred mode of transportation when visiting a hill station.\n";

    // Start with a broad list of transportation options
    std::cout << "You can choose from the following options:\n";
    std::cout << "1. Car\n";
    std::cout << "2. Train\n";
    std::cout << "3. Flight\n";
    std::cout << "4. Bus\n";
    std::cout << "5. Motorcycle/Bike\n";
    std::cout << "6. Other (Please specify)\n";

    // Asking user to input their preferred transport mode
    while (!validInput)
    {
        std::cout << "Please enter the number corresponding to your preferred mode of transportation (1-6): ";
        std::getline(std::cin, transportMode);

        // Check if the input is a valid number between 1 and 6
        if (transportMode == "1" || transportMode == "2" || transportMode == "3" || transportMode == "4" || transportMode == "5" || transportMode == "6")
        {
            validInput = true;
        }
        else
        {
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
        }
    }

    // Process the selected transport mode
    if (transportMode == "1")
    {
        std::cout << "You prefer to travel by car. That's great! Traveling by car offers flexibility and the ability to explore the surroundings.\n";
    }
    else if (transportMode == "2")
    {
        std::cout << "You prefer to travel by train. Trains are a comfortable and scenic way to travel, especially when heading to hill stations.\n";
    }
    else if (transportMode == "3")
    {
        std::cout << "You prefer to travel by flight. Flights are a fast way to reach distant hill stations, though they may require additional travel from the airport.\n";
    }
    else if (transportMode == "4")
    {
        std::cout << "You prefer to travel by bus. Buses are a budget-friendly option and can offer scenic views during your journey.\n";
    }
    else if (transportMode == "5")
    {
        std::cout << "You prefer to travel by motorcycle or bike. This can be an adventurous option, allowing you to experience the journey firsthand.\n";
    }
    else if (transportMode == "6")
    {
        std::cout << "You prefer another mode of transportation. Please specify: ";
        std::getline(std::cin, transportMode);
        std::cout << "You prefer to travel by " << transportMode << ". That's great! Different modes of transport can make the journey unique and memorable.\n";
    }

    // Offer additional travel tips based on the selected transport mode
    if (transportMode == "1" || transportMode == "2" || transportMode == "3" || transportMode == "4" || transportMode == "5")
    {
        std::cout << "Here are a few tips for your journey based on your preferred transport mode:\n";
        if (transportMode == "1")
        {
            std::cout << "- Ensure your car is in good condition for hilly roads.\n";
            std::cout << "- Pack snacks and water for the journey.\n";
            std::cout << "- Make sure your vehicle has enough fuel for long stretches.\n";
            std::cout << "- Consider using a GPS for navigating winding mountain roads.\n";
        }
        else if (transportMode == "2")
        {
            std::cout << "- Book your tickets in advance to secure your seat.\n";
            std::cout << "- Look out for window views, as train journeys offer scenic beauty.\n";
            std::cout << "- Carry some personal entertainment (book, music) for the journey.\n";
            std::cout << "- Check the train's schedule and route for any delays.\n";
        }
        else if (transportMode == "3")
        {
            std::cout << "- Check the weather conditions at your departure and arrival airports.\n";
            std::cout << "- Ensure you have enough time to reach the hill station after your flight.\n";
            std::cout << "- If you have a layover, consider exploring nearby attractions.\n";
            std::cout << "- Arrive early at the airport for security and boarding procedures.\n";
        }
        else if (transportMode == "4")
        {
            std::cout << "- Check the bus schedule and routes to ensure timely arrival.\n";
            std::cout << "- Carry a neck pillow and other comfort items for longer journeys.\n";
            std::cout << "- Buses can be more affordable, but they may take longer, so plan accordingly.\n";
            std::cout << "- Look for buses that offer scenic routes or overnight travel options.\n";
        }
        else if (transportMode == "5")
        {
            std::cout << "- Make sure your motorcycle is well-prepared for hilly terrain.\n";
            std::cout << "- Wear safety gear like a helmet, gloves, and protective clothing.\n";
            std::cout << "- Pack light to keep the bike stable and easy to maneuver.\n";
            std::cout << "- Ensure the bike's fuel tank is full, as stations may be sparse in the hills.\n";
        }
    }

    // Ask for additional preferences if they have special requirements
    std::string specialRequests;
    std::cout << "Do you have any special transportation preferences or requirements? (E.g., Accessibility, comfort, etc.) (Optional): ";
    std::getline(std::cin, specialRequests);

    if (!specialRequests.empty())
    {
        std::cout << "Thank you for sharing your preferences! We will keep this in mind for better recommendations.\n";
    }

    // Ask about potential travel companions and how they might influence transportation choice
    std::string travelCompanions;
    std::cout << "Do you plan to travel alone, with family, friends, or in a group? This can help us suggest better transport options for you.\n";
    std::cout << "Please enter 'alone', 'family', 'friends', or 'group': ";
    std::getline(std::cin, travelCompanions);

    // Validate travel companions input
    while (travelCompanions != "alone" && travelCompanions != "family" && travelCompanions != "friends" && travelCompanions != "group")
    {
        std::cout << "Invalid input. Please enter 'alone', 'family', 'friends', or 'group': ";
        std::getline(std::cin, travelCompanions);
    }

    // Provide suggestions based on travel companions
    if (travelCompanions == "alone")
    {
        std::cout << "As you're traveling alone, you might prefer more flexible and private transportation like a car or motorcycle.\n";
    }
    else if (travelCompanions == "family")
    {
        std::cout << "When traveling with family, consider options that offer more space and comfort, such as a car, bus, or train.\n";
    }
    else if (travelCompanions == "friends")
    {
        std::cout << "Traveling with friends? You can have more fun with group transportation like a bus or a large car.\n";
    }
    else if (travelCompanions == "group")
    {
        std::cout << "For larger groups, a bus or shared transport is ideal for keeping things affordable and organized.\n";
    }

    // Offer additional transportation-related questions
    std::string accessibility;
    std::cout << "Do you have any specific accessibility needs while traveling? (E.g., wheelchair access, need of extra legroom) (Optional): ";
    std::getline(std::cin, accessibility);

    if (!accessibility.empty())
    {
        std::cout << "We appreciate you sharing your accessibility requirements. We will consider this when recommending transport options.\n";
    }

    // Ask about the user's preference for travel speed
    std::string speedPreference;
    std::cout << "Do you prefer a faster journey or a more scenic one? (Fast/Scenic): ";
    std::getline(std::cin, speedPreference);

    while (speedPreference != "Fast" && speedPreference != "Scenic")
    {
        std::cout << "Invalid input. Please enter 'Fast' or 'Scenic': ";
        std::getline(std::cin, speedPreference);
    }

    if (speedPreference == "Fast")
    {
        std::cout << "You prefer a faster journey. Flight or car would be your ideal choices.\n";
    }
    else
    {
        std::cout << "You prefer a scenic journey. Train or bus could offer you beautiful views of nature.\n";
    }

    // Provide a final thank you message and ask for confirmation
    std::cout << "Thank you for sharing your preferences! Based on your transport mode, we can suggest a customized travel plan.\n";
    std::cout << "Would you like to make any further changes to your preferred transport mode? (Yes/No): ";
    std::string changeMode;
    std::getline(std::cin, changeMode);

    // Validate the final confirmation and ask to repeat or finalize
    while (changeMode != "yes" && changeMode != "no")
    {
        std::cout << "Invalid input. Please answer with 'Yes' or 'No': ";
        std::getline(std::cin, changeMode);
    }

    if (changeMode == "yes")
    {
        return getTransportMode(); // Call the function again to change transport mode
    }
    else
    {
        std::cout << "Thank you! Your preferred transport mode has been saved.\n";
        return transportMode;
    }
}
std::string getTravelCompanions()
{
    std::string companions;
    bool validInput = false;

    // Introduction to the question about travel companions
    std::cout << "Let's talk about your travel companions.\n";
    std::cout << "Knowing whether you're traveling alone, with family, friends, or in a group helps us understand your preferences better.\n";
    std::cout << "It also lets us give you more accurate suggestions for transportation, accommodation, and activities during your hill station trip.\n";

    // Prompting the user for their travel companions information
    std::cout << "Please choose one of the following options for your travel companions:\n";
    std::cout << "1. Traveling Alone\n";
    std::cout << "2. Traveling with Family\n";
    std::cout << "3. Traveling with Friends\n";
    std::cout << "4. Traveling with a Group\n";
    std::cout << "5. Other (Specify)\n";

    // Asking the user for their input and validating it
    while (!validInput)
    {
        std::cout << "Please enter the number corresponding to your choice (1-5): ";
        std::getline(std::cin, companions);

        if (companions == "1" || companions == "2" || companions == "3" || companions == "4" || companions == "5")
        {
            validInput = true;
        }
        else
        {
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
        }
    }

    // Process the input based on the user's choice
    if (companions == "1")
    {
        std::cout << "You are traveling alone. Solo trips can offer freedom and independence, allowing you to explore at your own pace.\n";
        std::cout << "For solo travelers, it's often best to choose transportation options that are flexible and secure, such as cars or flights.\n";
    }
    else if (companions == "2")
    {
        std::cout << "You are traveling with family. Family trips often require more space and comfort, so choosing transportation like a large car or train might be ideal.\n";
        std::cout << "You may also need to look for accommodations that cater to families, such as family suites or hotels with kid-friendly amenities.\n";
    }
    else if (companions == "3")
    {
        std::cout << "You are traveling with friends. Traveling with friends can be a fun and social experience.\n";
        std::cout << "If you're with a group of friends, consider renting a car or bus to stay together and keep costs down.\n";
    }
    else if (companions == "4")
    {
        std::cout << "You are traveling with a group. Group trips often require logistical planning and coordination.\n";
        std::cout << "For large groups, it's best to use a bus or a coach, as it provides a comfortable and economical way to travel together.\n";
    }
    else if (companions == "5")
    {
        std::cout << "You are traveling with other companions. Could you please specify the details? (e.g., Colleagues, Pets, etc.): ";
        std::getline(std::cin, companions);
        std::cout << "You are traveling with " << companions << ". We will tailor our suggestions accordingly.\n";
    }

    // Asking the user if they need more information based on their choice
    std::string moreInfo;
    std::cout << "Would you like more suggestions based on your travel companions? (Yes/No): ";
    std::getline(std::cin, moreInfo);

    while (moreInfo != "Yes" && moreInfo != "No")
    {
        std::cout << "Invalid input. Please answer with 'Yes' or 'No': ";
        std::getline(std::cin, moreInfo);
    }

    if (moreInfo == "Yes")
    {
        if (companions == "1")
        {
            std::cout << "For solo travelers, you might want to consider flexible travel options like booking last-minute flights or choosing accommodations with more privacy.\n";
            std::cout << "Some solo travelers enjoy connecting with other like-minded travelers, so look for hostels or social spaces.\n";
        }
        else if (companions == "2")
        {
            std::cout << "Traveling with family means finding activities that everyone will enjoy. Look for kid-friendly activities like nature walks, boat rides, or cultural festivals.\n";
            std::cout << "You might also want to look for restaurants with family-friendly menus and amenities like playgrounds.\n";
        }
        else if (companions == "3")
        {
            std::cout << "When traveling with friends, you might want to explore adventure activities like trekking, river rafting, or sightseeing together.\n";
            std::cout << "Consider renting a large vehicle or choosing accommodations with shared rooms or dormitories for a social experience.\n";
        }
        else if (companions == "4")
        {
            std::cout << "For large groups, think about booking a group tour package or organizing transport with one company to keep everyone together.\n";
            std::cout << "Consider renting a private villa or house to accommodate everyone comfortably.\n";
        }
        else if (companions == "5")
        {
            std::cout << "If you're traveling with pets, look for pet-friendly accommodations and transportation options that allow your furry friends.\n";
            std::cout << "Pets might need special care during travel, so consider bringing travel essentials like food, water, and bedding.\n";
        }
    }
    else
    {
        std::cout << "Thank you for your input! We have noted your travel companion details.\n";
    }

    // Asking about the travel group dynamics (Optional)
    std::string groupDynamics;
    std::cout << "Would you like to share how your travel group dynamics affect your trip planning? (Optional): ";
    std::getline(std::cin, groupDynamics);

    if (!groupDynamics.empty())
    {
        std::cout << "Thank you for sharing! Your group dynamics can affect transportation and accommodation choices, and we'll consider that for better suggestions.\n";
    }

    // Asking about preferred travel schedule
    std::string travelSchedule;
    std::cout << "Does your group have a preferred travel schedule or routine? (e.g., Flexible, Fixed timings): ";
    std::getline(std::cin, travelSchedule);

    if (!travelSchedule.empty())
    {
        std::cout << "Noted! We understand your group's travel routine. This helps us suggest more suitable travel options.\n";
    }

    // Gathering information about group interests for activities
    std::string groupInterests;
    std::cout << "Are there any specific activities your group is interested in? (e.g., Trekking, Sightseeing, Cultural experiences): ";
    std::getline(std::cin, groupInterests);

    if (!groupInterests.empty())
    {
        std::cout << "Thank you for sharing your group's interests! We'll tailor our suggestions to align with your preferred activities.\n";
    }

    // Asking if the group needs any special accommodations
    std::string specialNeeds;
    std::cout << "Does your group have any special needs or requests, such as wheelchair access, dietary requirements, or accessibility preferences? (Optional): ";
    std::getline(std::cin, specialNeeds);

    if (!specialNeeds.empty())
    {
        std::cout << "We appreciate you sharing any special needs. We will consider these when making our suggestions.\n";
    }

    // Final confirmation
    std::string confirmation;
    std::cout << "Would you like to modify or update the information about your travel companions? (Yes/No): ";
    std::getline(std::cin, confirmation);

    while (confirmation != "Yes" && confirmation != "No")
    {
        std::cout << "Invalid input. Please enter 'Yes' or 'No': ";
        std::getline(std::cin, confirmation);
    }

    if (confirmation == "Yes")
    {
        return getTravelCompanions(); // Recur to allow updating the information
    }
    else
    {
        std::cout << "Thank you for your input! Your travel companions details have been saved.\n";
        return companions;
    }
}
std::string getFavoriteHillStation()
{
    std::string favoriteHillStation;
    bool validInput = false;

    // Introduction to the favorite hill station question
    std::cout << "Now, let's talk about your favorite hill station.\n";
    std::cout << "Sharing details about your favorite destination helps us understand what kind of places you prefer.\n";
    std::cout << "It also allows us to suggest similar hill stations you might like in the future!\n";
    std::cout << "Please provide the name of your favorite hill station:\n";

    // Collecting the name of the favorite hill station
    while (!validInput)
    {
        std::cout << "Enter the name of the hill station: ";
        std::getline(std::cin, favoriteHillStation);

        // Validating input (ensuring the input is not empty and only contains relevant characters)
        if (!favoriteHillStation.empty() && favoriteHillStation.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ") == std::string::npos)
        {
            validInput = true;
        }
        else
        {
            std::cout << "Invalid input. Please provide a valid hill station name.\n";
        }
    }

    std::cout << "You mentioned that your favorite hill station is: " << favoriteHillStation << "\n";
    std::cout << "That's great! Let's explore more about why you love this place.\n";

    // Asking why the hill station is the favorite
    std::string reason;
    std::cout << "What makes this hill station your favorite? (e.g., Scenery, Activities, Weather, People, etc.)\n";
    std::getline(std::cin, reason);

    // Asking for specific activities or experiences at the hill station
    std::string activities;
    std::cout << "What activities did you enjoy the most at this hill station? (e.g., Trekking, Sightseeing, Relaxation, Shopping, etc.)\n";
    std::getline(std::cin, activities);

    // Asking about the duration of the visit
    std::string visitDuration;
    std::cout << "How long did you stay at this hill station? (e.g., 2 days, 1 week, etc.)\n";
    std::getline(std::cin, visitDuration);

    // Asking about the weather and its impact
    std::string weather;
    std::cout << "How was the weather during your visit? Did it add to your experience? (e.g., Snowy, Sunny, Cool, Rainy, etc.)\n";
    std::getline(std::cin, weather);

    // Asking if the place was crowded or peaceful
    std::string crowdLevel;
    std::cout << "Was the hill station crowded or peaceful during your visit? (e.g., Crowded, Peaceful, Perfect balance, etc.)\n";
    std::getline(std::cin, crowdLevel);

    // Asking if the user would recommend this hill station
    std::string recommendation;
    std::cout << "Would you recommend this hill station to others? (Yes/No)\n";
    std::getline(std::cin, recommendation);

    // Handling the recommendation response
    if (recommendation == "Yes")
    {
        std::cout << "That's wonderful! It sounds like a place worth visiting for others too.\n";
    }
    else if (recommendation == "No")
    {
        std::cout << "Thank you for sharing your thoughts. Everyone has different preferences.\n";
    }
    else
    {
        std::cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
    }

    // Asking for specific details about the hill station
    std::string uniqueFeature;
    std::cout << "What unique feature of this hill station stands out the most for you? (e.g., Unique landscapes, Historical landmarks, Special cuisine, etc.)\n";
    std::getline(std::cin, uniqueFeature);

    // Asking about accommodations
    std::string accommodation;
    std::cout << "How was your accommodation at this hill station? (e.g., Hotel, Homestay, Resort, etc.)\n";
    std::getline(std::cin, accommodation);

    // Asking if the accommodation was comfortable
    std::string accommodationComfort;
    std::cout << "Was the accommodation comfortable and up to your expectations? (Yes/No)\n";
    std::getline(std::cin, accommodationComfort);

    // Handling accommodation comfort response
    if (accommodationComfort == "Yes")
    {
        std::cout << "It's great to know that you had a comfortable stay.\n";
    }
    else if (accommodationComfort == "No")
    {
        std::cout << "Sorry to hear that. It's always important to have comfortable accommodations during trips.\n";
    }
    else
    {
        std::cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
    }

    // Asking about the people and culture of the hill station
    std::string peopleAndCulture;
    std::cout << "How was your interaction with the people at the hill station? Did you experience anything unique about the culture?\n";
    std::getline(std::cin, peopleAndCulture);

    // Asking if there were any memorable experiences or highlights
    std::string memorableExperience;
    std::cout << "Do you have any memorable experiences or highlights from your visit to this hill station that you would like to share?\n";
    std::getline(std::cin, memorableExperience);

    // Asking about the food at the hill station
    std::string food;
    std::cout << "How was the food at this hill station? Did you try any local specialties or unique dishes?\n";
    std::getline(std::cin, food);

    // Asking if the user will visit again
    std::string revisit;
    std::cout << "Would you consider visiting this hill station again? (Yes/No)\n";
    std::getline(std::cin, revisit);

    // Handling the revisit response
    if (revisit == "Yes")
    {
        std::cout << "That's great! It sounds like the hill station left a lasting impression.\n";
    }
    else if (revisit == "No")
    {
        std::cout << "It seems like there might be other places you'd prefer to visit next time.\n";
    }
    else
    {
        std::cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
    }

    // Asking for any suggestions for improvement for the hill station
    std::string suggestions;
    std::cout << "Do you have any suggestions for improving this hill station or making the experience better for future visitors?\n";
    std::getline(std::cin, suggestions);

    // Asking about transportation to and from the hill station
    std::string transport;
    std::cout << "How did you travel to this hill station? Was the transportation convenient and comfortable? (e.g., Car, Train, Flight, etc.)\n";
    std::getline(std::cin, transport);

    // Asking if transportation to the hill station could be improved
    std::string transportImprovement;
    std::cout << "Do you think transportation to this hill station could be improved in any way? (Yes/No)\n";
    std::getline(std::cin, transportImprovement);

    // Handling the transportation improvement response
    if (transportImprovement == "Yes")
    {
        std::cout << "Thank you for your feedback! Transportation is key to a good travel experience.\n";
    }
    else if (transportImprovement == "No")
    {
        std::cout << "It's good to know that transportation was convenient for you.\n";
    }
    else
    {
        std::cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
    }

    // Asking if the user is interested in exploring more hill stations
    std::string exploreMore;
    std::cout << "Would you be interested in exploring more hill stations similar to this one? (Yes/No)\n";
    std::getline(std::cin, exploreMore);

    // Handling the explore more response
    if (exploreMore == "Yes")
    {
        std::cout << "That's great! There are many beautiful hill stations that offer similar experiences.\n";
    }
    else if (exploreMore == "No")
    {
        std::cout << "It's totally fine! Sometimes, one hill station is all you need to have an unforgettable experience.\n";
    }
    else
    {
        std::cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
    }

    // Asking for any additional comments
    std::string additionalComments;
    std::cout << "Do you have any additional comments or suggestions about this hill station that you'd like to share?\n";
    std::getline(std::cin, additionalComments);

    // Providing a summary of their favorite hill station
    std::cout << "Thank you for sharing all your insights about your favorite hill station: " << favoriteHillStation << "\n";
    std::cout << "Here s a summary of what you shared:\n";
    std::cout << "Reason for your favorite: " << reason << "\n";
    std::cout << "Activities enjoyed: " << activities << "\n";
    std::cout << "Duration of visit: " << visitDuration << "\n";
    std::cout << "Weather: " << weather << "\n";
    std::cout << "Crowd level: " << crowdLevel << "\n";
    std::cout << "Recommendation: " << recommendation << "\n";
    std::cout << "Unique feature: " << uniqueFeature << "\n";
    std::cout << "Accommodation: " << accommodation << "\n";
    std::cout << "Accommodation comfort: " << accommodationComfort << "\n";
    std::cout << "People and culture: " << peopleAndCulture << "\n";
    std::cout << "Memorable experience: " << memorableExperience << "\n";
    std::cout << "Food: " << food << "\n";
    std::cout << "Revisit: " << revisit << "\n";
    std::cout << "Suggestions: " << suggestions << "\n";
    std::cout << "Transport: " << transport << "\n";
    std::cout << "Transportation improvement: " << transportImprovement << "\n";
    std::cout << "Explore more hill stations: " << exploreMore << "\n";
    std::cout << "Additional comments: " << additionalComments << "\n";

    return favoriteHillStation;
}
std::vector<std::string> getActivities()
{
    std::vector<std::string> activities;
    std::string activity;
    bool validInput = false;
    char moreActivities = 'y';

    // Introduction to the activities question
    std::cout << "We'd love to know what activities you enjoyed during your visit to the hill station.\n";
    std::cout << "This helps us understand the kind of experiences people prefer when traveling to hill stations.\n";
    std::cout << "Please provide details of the activities you participated in during your visit.\n";

    while (moreActivities == 'y' || moreActivities == 'Y')
    {
        std::cout << "Enter an activity you enjoyed (e.g., Trekking, Sightseeing, Relaxation, Shopping, etc.): ";
        std::getline(std::cin, activity);

        // Validate if activity is empty or contains only whitespace
        if (activity.empty() || std::all_of(activity.begin(), activity.end(), ::isspace))
        {
            std::cout << "Invalid input. Please enter a valid activity.\n";
            continue;
        }

        activities.push_back(activity);
        std::cout << "Activity added: " << activity << "\n";

        // Ask if the user wants to add another activity
        std::cout << "Would you like to add another activity? (y/n): ";
        std::cin >> moreActivities;
        std::cin.ignore(); // Clear any extra input

        // Input validation for yes/no responses
        if (moreActivities != 'y' && moreActivities != 'Y' && moreActivities != 'n' && moreActivities != 'N')
        {
            std::cout << "Invalid input. Please enter 'y' for yes or 'n' for no.\n";
            std::cout << "Would you like to add another activity? (y/n): ";
            std::cin >> moreActivities;
            std::cin.ignore(); // Clear the newline character
        }
    }

    // Summarize the list of activities entered
    std::cout << "Thank you for sharing your activities! Here's a list of the activities you enjoyed:\n";
    for (size_t i = 0; i < activities.size(); ++i)
    {
        std::cout << i + 1 << ". " << activities[i] << "\n";
    }

    // Asking if the user wants to edit any activities
    char editActivity = 'n';
    std::cout << "Would you like to edit any activities? (y/n): ";
    std::cin >> editActivity;
    std::cin.ignore(); // Clear the newline character

    if (editActivity == 'y' || editActivity == 'Y')
    {
        int activityIndex;
        std::cout << "Please enter the number of the activity you would like to edit (1-" << activities.size() << "): ";
        std::cin >> activityIndex;
        std::cin.ignore();

        // Validate activity index
        if (activityIndex > 0 && activityIndex <= activities.size())
        {
            std::cout << "Enter the new activity description: ";
            std::getline(std::cin, activity);
            activities[activityIndex - 1] = activity;
            std::cout << "Activity updated to: " << activity << "\n";
        }
        else
        {
            std::cout << "Invalid activity number. Please select a valid activity number from the list.\n";
        }
    }

    // Asking about activity preferences based on prior responses
    std::string preference;
    std::cout << "Which of the following activity types do you prefer the most? (e.g., Adventure, Leisure, Cultural, etc.): ";
    std::getline(std::cin, preference);
    std::cout << "You prefer " << preference << " activities.\n";

    // Asking for a more detailed description of a favorite activity
    std::string favoriteActivityDetail;
    std::cout << "Which activity from the list was your favorite, and why?\n";
    std::getline(std::cin, favoriteActivityDetail);
    std::cout << "You mentioned that your favorite activity was: " << favoriteActivityDetail << "\n";

    // Offering some follow-up questions based on activities
    std::string bestActivityTime;
    std::cout << "When do you prefer to engage in activities like this? (e.g., Morning, Afternoon, Evening, Any time of day): ";
    std::getline(std::cin, bestActivityTime);
    std::cout << "You prefer to engage in activities during the " << bestActivityTime << ".\n";

    // Asking if the user prefers to do activities solo or with others
    std::string activityCompanion;
    std::cout << "Do you prefer engaging in activities solo or with others (e.g., Friends, Family, Partner, etc.)?\n";
    std::getline(std::cin, activityCompanion);
    std::cout << "You prefer engaging in activities with: " << activityCompanion << ".\n";

    // Asking about activity-related facilities and services
    std::string facilities;
    std::cout << "What facilities or services would improve your activity experience? (e.g., Better guides, Equipment, Accessibility, etc.): ";
    std::getline(std::cin, facilities);
    std::cout << "You suggested improving the following facilities: " << facilities << ".\n";

    // Offering follow-up on their activities preferences
    char moreDetailOnActivities = 'n';
    std::cout << "Would you like to provide more details about any specific activity or experience? (y/n): ";
    std::cin >> moreDetailOnActivities;
    std::cin.ignore();

    if (moreDetailOnActivities == 'y' || moreDetailOnActivities == 'Y')
    {
        std::string additionalActivityDetails;
        std::cout << "Please provide more details about the activity you would like to elaborate on: ";
        std::getline(std::cin, additionalActivityDetails);
        std::cout << "You provided additional details: " << additionalActivityDetails << "\n";
    }

    // Confirming the activities chosen and summarizing
    std::cout << "Here s a summary of your activities:\n";
    for (size_t i = 0; i < activities.size(); ++i)
    {
        std::cout << i + 1 << ". " << activities[i] << "\n";
    }

    // Asking the user if they'd like to add more activities or confirm the list
    char confirmActivities = 'n';
    std::cout << "Would you like to add more activities to your list? (y/n): ";
    std::cin >> confirmActivities;
    std::cin.ignore();

    if (confirmActivities == 'y' || confirmActivities == 'Y')
    {
        return getActivities(); // Recursively call to allow adding more activities
    }
    else
    {
        std::cout << "Thank you for providing your activity details!\n";
    }

    // Asking if the user would like a suggestion for activities based on preferences
    char suggestActivity = 'n';
    std::cout << "Would you like to receive a suggestion for new activities to try? (y/n): ";
    std::cin >> suggestActivity;
    std::cin.ignore();

    if (suggestActivity == 'y' || suggestActivity == 'Y')
    {
        // Suggesting new activities based on previous responses
        std::cout << "Based on your preferences, we suggest trying activities such as:\n";
        std::cout << "1. Rock Climbing - Adventure\n";
        std::cout << "2. Photography Tours - Cultural\n";
        std::cout << "3. Wildlife Watching - Leisure\n";
        std::cout << "4. Yoga Retreats - Relaxation\n";
        std::cout << "Would you like more information about any of these activities? (y/n): ";
        char moreInfo;
        std::cin >> moreInfo;
        std::cin.ignore();
        if (moreInfo == 'y' || moreInfo == 'Y')
        {
            std::cout << "Please select the activity you'd like more information about: \n";
            std::cout << "1. Rock Climbing\n";
            std::cout << "2. Photography Tours\n";
            std::cout << "3. Wildlife Watching\n";
            std::cout << "4. Yoga Retreats\n";
            int selection;
            std::cin >> selection;
            std::cin.ignore();
            std::cout << "You selected option " << selection << ". We will send you more details soon!\n";
        }
        else
        {
            std::cout << "No worries! Enjoy your trip and activities.\n";
        }
    }

    return activities; // Returning the final list of activities
}
int getRating()
{
    int rating = 0;
    bool validInput = false;
    char response = 'n';

    // Introduction to rating prompt
    std::cout << "We'd love to know how you would rate your overall experience at the hill station.\n";
    std::cout << "Please rate your experience on a scale from 1 to 5, where:\n";
    std::cout << "1 - Very Poor\n";
    std::cout << "2 - Poor\n";
    std::cout << "3 - Average\n";
    std::cout << "4 - Good\n";
    std::cout << "5 - Excellent\n";

    // Loop for getting valid rating input
    while (!validInput)
    {
        std::cout << "Please enter a rating (1 to 5): ";
        std::cin >> rating;
        std::cin.ignore(); // To clear the newline character left by std::cin

        // Check if the input is within the valid range
        if (rating >= 1 && rating <= 5)
        {
            validInput = true;
            std::cout << "You rated your experience as: " << rating << " out of 5.\n";
        }
        else
        {
            std::cout << "Invalid input. Please enter a rating between 1 and 5.\n";
        }
    }

    // Additional feedback based on the rating
    if (rating == 1)
    {
        std::cout << "We're sorry to hear that your experience was very poor. Could you please provide more details?\n";
        std::cout << "What went wrong during your visit?\n";
        std::string feedback;
        std::getline(std::cin, feedback);
        std::cout << "Thank you for your feedback! We'll work on improving the experience.\n";
    }
    else if (rating == 2)
    {
        std::cout << "We're sorry to hear that your experience was poor. Could you provide more information on how we can improve?\n";
        std::cout << "What were the main issues that affected your experience?\n";
        std::string feedback;
        std::getline(std::cin, feedback);
        std::cout << "Thank you for your feedback. We'll take your suggestions seriously and improve.\n";
    }
    else if (rating == 3)
    {
        std::cout << "Thank you for rating your experience as average. We're happy it was okay, but we strive for better!\n";
        std::cout << "Can you please provide more details on what could make your experience better?\n";
        std::string feedback;
        std::getline(std::cin, feedback);
        std::cout << "Thank you for your valuable feedback! We'll work towards enhancing the experience.\n";
    }
    else if (rating == 4)
    {
        std::cout << "Thank you for rating your experience as good! We're glad you had a positive time.\n";
        std::cout << "What was the highlight of your visit? What could make it excellent next time?\n";
        std::string feedback;
        std::getline(std::cin, feedback);
        std::cout << "Thank you! We'll strive to provide an even better experience next time.\n";
    }
    else if (rating == 5)
    {
        std::cout << "Thank you for rating your experience as excellent! We're thrilled you had a great time.\n";
        std::cout << "What was the best part of your visit? Any suggestions for even more amazing experiences?\n";
        std::string feedback;
        std::getline(std::cin, feedback);
        std::cout << "We appreciate your feedback and will continue to make your experience even better.\n";
    }

    // Asking for more specific feedback based on the rating
    std::cout << "Would you like to share more detailed feedback about your experience? (y/n): ";
    std::cin >> response;
    std::cin.ignore(); // Clear the newline character

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please provide additional details that could help us improve the experience for future visitors.\n";
        std::string detailedFeedback;
        std::getline(std::cin, detailedFeedback);
        std::cout << "Thank you for your detailed feedback. We will use it to enhance our services.\n";
    }

    // Asking about different aspects of the experience
    std::cout << "Would you like to rate specific aspects of your visit (e.g., Accommodation, Food, Sightseeing)? (y/n): ";
    std::cin >> response;
    std::cin.ignore(); // Clear the newline character

    if (response == 'y' || response == 'Y')
    {
        int aspectRating = 0;
        std::cout << "Please rate the following aspects of your visit on a scale of 1 to 5:\n";

        // Rating Accommodation
        std::cout << "Accommodation: ";
        std::cin >> aspectRating;
        std::cin.ignore();
        std::cout << "You rated accommodation as: " << aspectRating << "/5.\n";

        // Rating Food
        std::cout << "Food: ";
        std::cin >> aspectRating;
        std::cin.ignore();
        std::cout << "You rated food as: " << aspectRating << "/5.\n";

        // Rating Sightseeing
        std::cout << "Sightseeing: ";
        std::cin >> aspectRating;
        std::cin.ignore();
        std::cout << "You rated sightseeing as: " << aspectRating << "/5.\n";

        // Rating Transport
        std::cout << "Transport: ";
        std::cin >> aspectRating;
        std::cin.ignore();
        std::cout << "You rated transport as: " << aspectRating << "/5.\n";

        // Rating Overall Experience
        std::cout << "Overall Experience: ";
        std::cin >> aspectRating;
        std::cin.ignore();
        std::cout << "You rated your overall experience as: " << aspectRating << "/5.\n";
    }

    // Introducing more customizations based on rating
    std::cout << "Would you be willing to take a deeper dive into how we can improve specific areas of your visit? (y/n): ";
    std::cin >> response;
    std::cin.ignore(); // Clear the newline character

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please feel free to share your thoughts on any particular aspect you feel needs improvement.\n";
        std::string moreSpecificFeedback;
        std::getline(std::cin, moreSpecificFeedback);
        std::cout << "We appreciate your deep insights. Your suggestions are incredibly helpful.\n";
    }

    // Final confirmation of the rating
    std::cout << "Please confirm your overall rating for the experience: " << rating << " out of 5.\n";
    std::cout << "Is this correct? (y/n): ";
    std::cin >> response;
    std::cin.ignore(); // Clear the newline character

    if (response == 'n' || response == 'N')
    {
        std::cout << "Let's go over the rating again. Please enter your overall rating (1 to 5): ";
        std::cin >> rating;
        std::cin.ignore();
        while (rating < 1 || rating > 5)
        {
            std::cout << "Invalid rating. Please enter a rating between 1 and 5: ";
            std::cin >> rating;
            std::cin.ignore();
        }
    }

    // Final feedback on the rating process
    std::cout << "Thank you for providing your rating! Your feedback is highly valuable to us.\n";
    std::cout << "We will use this information to improve our services and ensure a better experience for future visitors.\n";

    // Asking for any additional comments
    std::cout << "Do you have any additional comments or suggestions that could help improve the experience? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please provide your comments or suggestions:\n";
        std::string additionalComments;
        std::getline(std::cin, additionalComments);
        std::cout << "Thank you for your comments! We will take them into consideration.\n";
    }

    // Asking if the user would recommend the hill station
    std::cout << "Would you recommend this hill station to others? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Thank you for recommending the hill station! We're happy you had a positive experience.\n";
    }
    else
    {
        std::cout << "We're sorry to hear that you wouldn't recommend it. Please share your reasons with us to help improve.\n";
    }

    // New personalized interaction for users who have not recommended the station
    std::cout << "If you did not recommend the hill station, would you be willing to help us understand why in more detail? (y/n): ";
    std::cin >> response;
    std::cin.ignore(); // Clear the newline character

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please describe the reasons why you wouldn't recommend it.\n";
        std::string nonRecommendationFeedback;
        std::getline(std::cin, nonRecommendationFeedback);
        std::cout << "Thank you for your feedback. We understand and will work to improve these areas.\n";
    }

    return rating;
}
std::string getFeedback()
{
    std::string feedback;
    char response;
    bool validInput = false;

    // Introduction to feedback
    std::cout << "We value your feedback as it helps us improve the experience for future visitors.\n";
    std::cout << "Please take a moment to share your thoughts about your visit to the hill station.\n";

    // Initial feedback prompt
    std::cout << "What stood out to you during your visit? Feel free to be detailed:\n";
    std::getline(std::cin, feedback);

    // Follow-up based on the initial feedback length
    if (feedback.length() < 50)
    {
        std::cout << "Thank you for sharing! Would you like to add more details to your feedback? (y/n): ";
        std::cin >> response;
        std::cin.ignore(); // Clear the newline character

        if (response == 'y' || response == 'Y')
        {
            std::string additionalFeedback;
            std::cout << "Please provide additional details about your experience:\n";
            std::getline(std::cin, additionalFeedback);
            feedback += " " + additionalFeedback;
            std::cout << "Thank you for elaborating! We appreciate your detailed feedback.\n";
        }
    }

    // Asking about positive aspects of the visit
    std::cout << "What did you enjoy the most about your visit? (e.g., Scenery, Activities, Food): ";
    std::string positives;
    std::getline(std::cin, positives);
    feedback += "\nMost enjoyed aspects: " + positives;

    // Asking about areas for improvement
    std::cout << "Were there any areas where we could improve? (e.g., Facilities, Service, Accessibility): ";
    std::string improvements;
    std::getline(std::cin, improvements);
    if (!improvements.empty())
    {
        feedback += "\nSuggested improvements: " + improvements;
    }
    else
    {
        feedback += "\nNo specific improvements suggested.";
    }

    // Detailed feedback on specific aspects
    std::cout << "Would you like to provide feedback on specific aspects such as Accommodation, Food, or Transport? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please rate the following aspects on a scale of 1 to 5 and provide any comments:\n";

        // Accommodation feedback
        std::cout << "Accommodation - Rating (1 to 5): ";
        int rating;
        std::cin >> rating;
        std::cin.ignore();
        while (rating < 1 || rating > 5)
        {
            std::cout << "Invalid rating. Please enter a value between 1 and 5: ";
            std::cin >> rating;
            std::cin.ignore();
        }
        feedback += "\nAccommodation rating: " + std::to_string(rating);

        std::cout << "Comments on accommodation: ";
        std::string accommodationFeedback;
        std::getline(std::cin, accommodationFeedback);
        feedback += "\nAccommodation comments: " + accommodationFeedback;

        // Food feedback
        std::cout << "Food - Rating (1 to 5): ";
        std::cin >> rating;
        std::cin.ignore();
        while (rating < 1 || rating > 5)
        {
            std::cout << "Invalid rating. Please enter a value between 1 and 5: ";
            std::cin >> rating;
            std::cin.ignore();
        }
        feedback += "\nFood rating: " + std::to_string(rating);

        std::cout << "Comments on food: ";
        std::string foodFeedback;
        std::getline(std::cin, foodFeedback);
        feedback += "\nFood comments: " + foodFeedback;

        // Transport feedback
        std::cout << "Transport - Rating (1 to 5): ";
        std::cin >> rating;
        std::cin.ignore();
        while (rating < 1 || rating > 5)
        {
            std::cout << "Invalid rating. Please enter a value between 1 and 5: ";
            std::cin >> rating;
            std::cin.ignore();
        }
        feedback += "\nTransport rating: " + std::to_string(rating);

        std::cout << "Comments on transport: ";
        std::string transportFeedback;
        std::getline(std::cin, transportFeedback);
        feedback += "\nTransport comments: " + transportFeedback;
    }

    // Asking about sustainable travel practices
    std::cout << "Did you follow any sustainable travel practices during your visit? (e.g., Avoiding littering, Supporting local businesses) (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "What sustainable practices did you follow? Please list them below:\n";
        std::string sustainablePractices;
        std::getline(std::cin, sustainablePractices);
        feedback += "\nSustainable practices followed: " + sustainablePractices;
    }
    else
    {
        feedback += "\nNo sustainable practices followed.";
    }

    // Asking about memorable experiences
    std::cout << "Do you have any memorable experiences you'd like to share? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please describe your memorable experience in detail:\n";
        std::string memorableExperience;
        std::getline(std::cin, memorableExperience);
        feedback += "\nMemorable experience: " + memorableExperience;
    }

    // Asking for suggestions to maintain hill station beauty
    std::cout << "Do you have any suggestions for maintaining the beauty of the hill station? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please share your suggestions:\n";
        std::string suggestions;
        std::getline(std::cin, suggestions);
        feedback += "\nSuggestions for maintaining beauty: " + suggestions;
    }

    // Final thoughts or comments
    std::cout << "Do you have any final comments or suggestions for improving this survey? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Please provide your comments or suggestions:\n";
        std::string additionalComments;
        std::getline(std::cin, additionalComments);
        feedback += "\nSurvey improvement suggestions: " + additionalComments;
    }

    // Confirmation of feedback submission
    std::cout << "Thank you for your feedback! We greatly appreciate your time and effort in helping us improve.\n";

    return feedback;
}
std::string getHillStationType()
{
    std::string hillStationType;
    int choice;
    char response;
    bool validInput = false;

    // Introduction to the question
    std::cout << "Hill stations are a great way to unwind, offering diverse experiences based on their unique characteristics.\n";
    std::cout << "We'd love to know your preferred type of hill station to better understand your travel preferences.\n";
    std::cout << "Think about the kind of environment you enjoy most while traveling.\n\n";

    // Detailed options for hill station types
    std::cout << "Please select your preferred type of hill station from the options below:\n";
    std::cout << "1. Snowy - Wintery landscapes with snow-capped peaks and cool breezes.\n";
    std::cout << "2. Forested - Lush greenery, dense woods, and peaceful natural trails.\n";
    std::cout << "3. Cultural - Rich in traditions, history, and local customs.\n";
    std::cout << "4. Lakeside - Calm lakes with stunning views and serene surroundings.\n";
    std::cout << "5. Adventure - Thrill-filled destinations with activities like trekking, paragliding, or skiing.\n";
    std::cout << "6. Spiritual - Peaceful retreats focusing on inner calm and mindfulness.\n";
    std::cout << "7. Coastal - Hill stations near the coastline, offering a blend of hills and beaches.\n";
    std::cout << "8. Other - Specify your unique preference.\n";

    // Input and validation loop
    do
    {
        std::cout << "\nEnter the number corresponding to your choice (1-8): ";
        std::cin >> choice;

        if (choice < 1 || choice > 8)
        {
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
        }
        else
        {
            validInput = true;
        }
    } while (!validInput);

    // Process user's choice and gather more information
    std::cin.ignore(); // Clear the newline character
    switch (choice)
    {
    case 1:
        hillStationType = "Snowy";
        std::cout << "Snowy hill stations are perfect for a magical winter escape. Do you enjoy snow-related activities like skiing or building snowmen? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Enjoys Snow Activities)";
        }
        break;
    case 2:
        hillStationType = "Forested";
        std::cout << "Forested hill stations are serene and filled with natural beauty. Do you enjoy trekking or nature walks? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Enjoys Nature Walks)";
        }
        break;
    case 3:
        hillStationType = "Cultural";
        std::cout << "Cultural hill stations offer a glimpse into local heritage. Are you interested in visiting historical sites and learning about local traditions? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Interested in History and Traditions)";
        }
        break;
    case 4:
        hillStationType = "Lakeside";
        std::cout << "Lakeside hill stations are tranquil and picturesque. Do you prefer activities like boating or relaxing by the water? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Enjoys Boating and Relaxation)";
        }
        break;
    case 5:
        hillStationType = "Adventure";
        std::cout << "Adventure hill stations are perfect for thrill-seekers. Do you enjoy activities like rock climbing or paragliding? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Enjoys Adventure Sports)";
        }
        break;
    case 6:
        hillStationType = "Spiritual";
        std::cout << "Spiritual hill stations are peaceful retreats. Are you drawn to meditation, yoga, or visiting temples? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Interested in Meditation and Temples)";
        }
        break;
    case 7:
        hillStationType = "Coastal";
        std::cout << "Coastal hill stations offer a unique blend of beach and hill experiences. Do you enjoy water sports or relaxing by the beach? (y/n): ";
        std::cin >> response;
        std::cin.ignore();
        if (response == 'y' || response == 'Y')
        {
            hillStationType += " (Enjoys Beach Activities)";
        }
        break;
    case 8:
        std::cout << "Please specify your unique preference for a hill station type: ";
        std::getline(std::cin, hillStationType);
        std::cout << "Your unique choice has been noted. Thank you!\n";
        break;
    }

    // Asking about travel preferences
    std::cout << "What attracts you the most to " << hillStationType << " hill stations? (e.g., Scenery, Activities, Climate): ";
    std::string attractions;
    std::getline(std::cin, attractions);
    hillStationType += " (Attractions: " + attractions + ")";

    // Inquiring about past experiences
    std::cout << "Have you visited a " << hillStationType << " hill station before? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (response == 'y' || response == 'Y')
    {
        std::cout << "Could you share the name of the hill station you visited and what you liked about it?\n";
        std::string pastExperience;
        std::getline(std::cin, pastExperience);
        hillStationType += " (Past Experience: " + pastExperience + ")";
    }
    else
    {
        hillStationType += " (No Past Visits)";
    }

    // Asking about interest in eco-tourism
    std::cout << "Would you consider visiting eco-tourism-friendly hill stations of this type? (y/n): ";
    std::cin >> response;
    std::cin.ignore();
    if (response == 'y' || response == 'Y')
    {
        hillStationType += " (Interested in Eco-Tourism)";
    }
    else
    {
        hillStationType += " (Not Interested in Eco-Tourism)";
    }

    // Conclusion
    std::cout << "Thank you for sharing your preferences about hill stations!\n";
    std::cout << "Your preferred type of hill station has been recorded as: " << hillStationType << "\n";

    return hillStationType;
}
std::vector<std::string> getKeyFactors()
{
    std::vector<std::string> keyFactors;
    int choice;
    char response;
    bool validInput = false;

    // Warm introduction to make the user comfortable
    std::cout << "When planning a trip to a hill station, everyone has unique preferences.\n";
    std::cout << "Your input helps us understand what matters most to you while choosing a destination.\n";
    std::cout << "Let's explore some of the key factors that might influence your decision-making.\n\n";

    // Presenting options in a detailed and engaging manner
    std::cout << "Here are some factors you might consider important:\n";
    std::cout << "1. Budget: Ensuring the trip is within your financial plan.\n";
    std::cout << "2. Accessibility: Ease of reaching the destination with minimal hassles.\n";
    std::cout << "3. Weather: Preference for a specific climate (e.g., snowy, cool, or warm).\n";
    std::cout << "4. Reviews: Recommendations and experiences shared by other travelers.\n";
    std::cout << "5. Activities: Availability of activities like trekking, adventure sports, or sightseeing.\n";
    std::cout << "6. Amenities: Access to comforts such as luxury hotels, homestays, or restaurants.\n";
    std::cout << "7. Safety: Feeling secure during the trip, especially for solo or family travel.\n";
    std::cout << "8. Cultural Significance: Learning about the heritage and traditions of the place.\n";
    std::cout << "9. Eco-Tourism: Supporting sustainable travel and nature preservation.\n";
    std::cout << "10. Other: Specify any additional factors important to you.\n";

    // Multiple choice with option to select more than one factor
    do
    {
        std::cout << "\nWould you like to select one or more factors? (y/n): ";
        std::cin >> response;
        std::cin.ignore(); // Clear the newline character

        if (response == 'y' || response == 'Y')
        {
            do
            {
                std::cout << "\nEnter the number corresponding to your choice (1-10): ";
                std::cin >> choice;

                if (choice < 1 || choice > 10)
                {
                    std::cout << "Invalid input. Please enter a number between 1 and 10.\n";
                }
                else
                {
                    validInput = true;
                    switch (choice)
                    {
                    case 1:
                        keyFactors.push_back("Budget");
                        std::cout << "Budget is noted. Do you plan your trips with a fixed budget in mind? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "That's great! A planned budget ensures a stress-free experience.\n";
                        }
                        else
                        {
                            std::cout << "Flexibility with budget can also make for a spontaneous adventure.\n";
                        }
                        break;
                    case 2:
                        keyFactors.push_back("Accessibility");
                        std::cout << "Accessibility is noted. Do you prefer direct connectivity to the destination? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Convenient travel is always a plus!\n";
                        }
                        else
                        {
                            std::cout << "Exploring remote destinations can be an adventure in itself.\n";
                        }
                        break;
                    case 3:
                        keyFactors.push_back("Weather");
                        std::cout << "Weather is noted. Do you prefer visiting during a specific season? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Seasonal trips can offer unique experiences.\n";
                        }
                        else
                        {
                            std::cout << "Year-round destinations offer flexibility for planning.\n";
                        }
                        break;
                    case 4:
                        keyFactors.push_back("Reviews");
                        std::cout << "Reviews are noted. Do you often rely on reviews to finalize a destination? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Reviews provide valuable insights from fellow travelers.\n";
                        }
                        else
                        {
                            std::cout << "Personal exploration can also uncover hidden gems.\n";
                        }
                        break;
                    case 5:
                        keyFactors.push_back("Activities");
                        std::cout << "Activities are noted. Do you prioritize destinations with diverse activities? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "A mix of activities makes for a memorable trip!\n";
                        }
                        else
                        {
                            std::cout << "Relaxation-focused trips can be equally rewarding.\n";
                        }
                        break;
                    case 6:
                        keyFactors.push_back("Amenities");
                        std::cout << "Amenities are noted. Do you prioritize destinations with luxury accommodations? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Comfortable stays enhance the overall experience.\n";
                        }
                        else
                        {
                            std::cout << "Homestays and budget accommodations can add a unique charm to the trip.\n";
                        }
                        break;
                    case 7:
                        keyFactors.push_back("Safety");
                        std::cout << "Safety is noted. Do you often research the safety of a destination before traveling? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "It's always wise to prioritize safety, especially for unfamiliar places.\n";
                        }
                        else
                        {
                            std::cout << "A bit of spontaneity can add excitement, but safety remains important.\n";
                        }
                        break;
                    case 8:
                        keyFactors.push_back("Cultural Significance");
                        std::cout << "Cultural significance is noted. Do you enjoy exploring historical landmarks? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Learning about local history adds depth to travel experiences.\n";
                        }
                        else
                        {
                            std::cout << "Modern attractions can also be fascinating.\n";
                        }
                        break;
                    case 9:
                        keyFactors.push_back("Eco-Tourism");
                        std::cout << "Eco-tourism is noted. Are you willing to support sustainable travel practices? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Thank you for supporting eco-friendly travel. Every effort counts!\n";
                        }
                        else
                        {
                            std::cout << "It's great to enjoy nature while being mindful of the environment.\n";
                        }
                        break;
                    case 10:
                    {
                        std::string otherFactor;
                        std::cin.ignore();
                        std::cout << "Please specify any other factor you consider important: ";
                        std::getline(std::cin, otherFactor);
                        keyFactors.push_back(otherFactor);
                        std::cout << "Thank you for sharing your unique preference.\n";
                        break;
                    }
                    }
                }
            } while (!validInput);

            std::cout << "Would you like to select another factor? (y/n): ";
            std::cin >> response;
            std::cin.ignore(); // Clear the newline character
            validInput = (response == 'y' || response == 'Y');
        }
        else
        {
            std::cout << "No worries! Let's move on to the next question.\n";
            validInput = false;
        }
    } while (validInput);

    // Display summary of selected factors
    std::cout << "\nHere are the factors you consider while choosing a hill station:\n";
    for (const auto &factor : keyFactors)
    {
        std::cout << "- " << factor << "\n";
    }
    std::cout << "Thank you for sharing your preferences!\n";

    return keyFactors;
}
std::vector<std::string> getDesiredAmenities()
{
    std::vector<std::string> desiredAmenities;
    int choice;
    char response;
    bool validInput = false;

    // Introduction to make the user comfortable
    std::cout << "When planning a hill station trip, amenities can significantly impact your experience.\n";
    std::cout << "We d like to know which amenities you value the most for a comfortable and enjoyable stay.\n\n";

    // List of available amenities
    std::cout << "Here s a list of amenities you might consider important:\n";
    std::cout << "1. Luxury Hotels: High-end accommodations with premium facilities.\n";
    std::cout << "2. Homestays: Cozy, home-like accommodations offering local experiences.\n";
    std::cout << "3. Adventure Activities: Options like trekking, zip-lining, or rock climbing.\n";
    std::cout << "4. Spa and Wellness: Relaxing facilities to rejuvenate during your stay.\n";
    std::cout << "5. Local Cuisine: Access to authentic and delicious local food.\n";
    std::cout << "6. Shopping Areas: Places to buy souvenirs, handicrafts, or other local specialties.\n";
    std::cout << "7. Guided Tours: Organized tours to explore the area with expert insights.\n";
    std::cout << "8. Child-Friendly Facilities: Play areas, child care, or other family-focused amenities.\n";
    std::cout << "9. Pet-Friendly Accommodations: Options to bring along your furry friends.\n";
    std::cout << "10. Eco-Friendly Options: Green accommodations and sustainable facilities.\n";
    std::cout << "11. Other: Specify additional amenities you value.\n";

    // Allowing the user to select one or more amenities
    do
    {
        std::cout << "\nWould you like to select one or more desired amenities? (y/n): ";
        std::cin >> response;
        std::cin.ignore(); // Clear newline character from the input buffer

        if (response == 'y' || response == 'Y')
        {
            do
            {
                std::cout << "\nEnter the number corresponding to your choice (1-11): ";
                std::cin >> choice;

                if (choice < 1 || choice > 11)
                {
                    std::cout << "Invalid input. Please enter a number between 1 and 11.\n";
                }
                else
                {
                    validInput = true;
                    switch (choice)
                    {
                    case 1:
                        desiredAmenities.push_back("Luxury Hotels");
                        std::cout << "Luxury Hotels added. Do you prefer specific luxury brands or chains? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Please share your preferred brand names when convenient.\n";
                        }
                        else
                        {
                            std::cout << "Understood. General luxury options will be noted.\n";
                        }
                        break;
                    case 2:
                        desiredAmenities.push_back("Homestays");
                        std::cout << "Homestays added. Do you prioritize homestays with local hosts? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Homestays with local hosts offer an immersive experience.\n";
                        }
                        else
                        {
                            std::cout << "Homestays with independent facilities noted.\n";
                        }
                        break;
                    case 3:
                        desiredAmenities.push_back("Adventure Activities");
                        std::cout << "Adventure Activities added. Do you enjoy high-adrenaline activities? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Thrilling adventures make for memorable trips!\n";
                        }
                        else
                        {
                            std::cout << "Milder activities can also provide enjoyment.\n";
                        }
                        break;
                    case 4:
                        desiredAmenities.push_back("Spa and Wellness");
                        std::cout << "Spa and Wellness added. Do you prefer resorts with dedicated wellness centers? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Relaxing wellness retreats are perfect for unwinding.\n";
                        }
                        else
                        {
                            std::cout << "Basic spa facilities will also be noted.\n";
                        }
                        break;
                    case 5:
                        desiredAmenities.push_back("Local Cuisine");
                        std::cout << "Local Cuisine added. Do you prefer destinations known for their culinary specialties? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Food-focused trips offer a delicious journey!\n";
                        }
                        else
                        {
                            std::cout << "General food preferences noted.\n";
                        }
                        break;
                    case 6:
                        desiredAmenities.push_back("Shopping Areas");
                        std::cout << "Shopping Areas added. Do you enjoy exploring local markets? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Local markets are great for unique finds!\n";
                        }
                        else
                        {
                            std::cout << "General shopping facilities noted.\n";
                        }
                        break;
                    case 7:
                        desiredAmenities.push_back("Guided Tours");
                        std::cout << "Guided Tours added. Do you prefer detailed historical tours? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Guided tours add depth to travel experiences.\n";
                        }
                        else
                        {
                            std::cout << "Self-guided exploration noted.\n";
                        }
                        break;
                    case 8:
                        desiredAmenities.push_back("Child-Friendly Facilities");
                        std::cout << "Child-Friendly Facilities added. Are you traveling with children? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Child-friendly facilities will ensure a family-friendly trip.\n";
                        }
                        else
                        {
                            std::cout << "Noted for potential family travelers.\n";
                        }
                        break;
                    case 9:
                        desiredAmenities.push_back("Pet-Friendly Accommodations");
                        std::cout << "Pet-Friendly Accommodations added. Do you usually travel with pets? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Traveling with pets can make trips more enjoyable!\n";
                        }
                        else
                        {
                            std::cout << "Noted for general options.\n";
                        }
                        break;
                    case 10:
                        desiredAmenities.push_back("Eco-Friendly Options");
                        std::cout << "Eco-Friendly Options added. Do you prioritize destinations with green certifications? (y/n): ";
                        std::cin >> response;
                        if (response == 'y' || response == 'Y')
                        {
                            std::cout << "Sustainable tourism is the future of travel.\n";
                        }
                        else
                        {
                            std::cout << "Eco-friendly considerations noted.\n";
                        }
                        break;
                    case 11:
                    {
                        std::string otherAmenity;
                        std::cin.ignore();
                        std::cout << "Please specify any other amenity you consider important: ";
                        std::getline(std::cin, otherAmenity);
                        desiredAmenities.push_back(otherAmenity);
                        std::cout << "Thank you for sharing your unique preference.\n";
                        break;
                    }
                    }
                }
            } while (!validInput);

            std::cout << "Would you like to select another amenity? (y/n): ";
            std::cin >> response;
            std::cin.ignore(); // Clear newline character from input buffer
            validInput = (response == 'y' || response == 'Y');
        }
        else
        {
            std::cout << "No worries! Let's move on to the next question.\n";
            validInput = false;
        }
    } while (validInput);

    // Display a summary of selected amenities
    std::cout << "\nHere are the amenities you value for your hill station trip:\n";
    for (const auto &amenity : desiredAmenities)
    {
        std::cout << "- " << amenity << "\n";
    }
    std::cout << "Thank you for sharing your preferences!\n";

    return desiredAmenities;
}
bool willingToExploreLesserKnown()
{
    bool willing = false;
    char response;
    std::string reason, preference;
    int choice;
    bool continueExploring = true;
    std::vector<std::string> userPreferences;

    // Introduction
    std::cout << "Exploring lesser-known hill stations offers hidden treasures and unique experiences.\n";
    std::cout << "These destinations are often untouched, serene, and full of surprises.\n";
    std::cout << "We d love to know if you are willing to explore such hidden gems.\n";

    while (continueExploring)
    {
        // User prompt
        std::cout << "\nWould you be open to exploring lesser-known hill stations? (y/n): ";
        std::cin >> response;

        if (response == 'y' || response == 'Y')
        {
            willing = true;
            std::cout << "\nWonderful! Exploring lesser-known destinations is a fantastic way to uncover hidden beauty.\n";
            std::cout << "Could you tell us why you re interested in exploring these destinations? ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, reason);
            userPreferences.push_back("Reason for exploring lesser-known: " + reason);
            std::cout << "Thank you for sharing: \"" << reason << "\". That s an insightful reason!\n";

            // Further engagement
            std::cout << "\nWhat aspects of lesser-known destinations appeal to you most?\n";
            std::cout << "1. Pristine and untouched nature\n";
            std::cout << "2. Unique cultural experiences\n";
            std::cout << "3. Less crowded and peaceful environment\n";
            std::cout << "4. Adventure opportunities\n";
            std::cout << "5. Affordable travel options\n";
            std::cout << "6. Other (Specify)\n";
            std::cout << "Please select one or more options (e.g., 1,3,4): ";

            std::string choices;
            std::cin.ignore();
            std::getline(std::cin, choices);

            std::cout << "You selected: " << choices << ". Let s dive deeper into each choice.\n";
            if (choices.find('1') != std::string::npos)
            {
                std::cout << "Pristine and untouched nature is a rare find and a key highlight of lesser-known hill stations.\n";
                userPreferences.push_back("Prefers pristine nature");
            }
            if (choices.find('2') != std::string::npos)
            {
                std::cout << "Unique cultural experiences can add depth and meaning to your travels.\n";
                userPreferences.push_back("Interested in unique cultural experiences");
            }
            if (choices.find('3') != std::string::npos)
            {
                std::cout << "A peaceful and less crowded environment can be truly rejuvenating.\n";
                userPreferences.push_back("Prefers peaceful and less crowded places");
            }
            if (choices.find('4') != std::string::npos)
            {
                std::cout << "Adventure opportunities add excitement to any trip. Activities like trekking and paragliding are often abundant in lesser-known destinations.\n";
                userPreferences.push_back("Interested in adventure opportunities");
            }
            if (choices.find('5') != std::string::npos)
            {
                std::cout << "Affordable travel options are a great benefit of visiting lesser-known destinations.\n";
                userPreferences.push_back("Values affordable travel");
            }
            if (choices.find('6') != std::string::npos)
            {
                std::string otherPreference;
                std::cout << "Please specify what other aspects you value: ";
                std::getline(std::cin, otherPreference);
                userPreferences.push_back("Other preference: " + otherPreference);
                std::cout << "Thank you for sharing: \"" << otherPreference << "\".\n";
            }

            // Suggestions for destinations
            std::cout << "\nWould you like some recommendations for lesser-known hill stations? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                std::cout << "\nHere are a few hidden gems worth exploring:\n";
                std::cout << "- Chikmagalur, Karnataka: Known for its coffee plantations and serene landscapes.\n";
                std::cout << "- Spiti Valley, Himachal Pradesh: A cold desert with stunning monasteries and vistas.\n";
                std::cout << "- Daringbadi, Odisha: Often referred to as the  Kashmir of Odisha. \n";
                std::cout << "- Ponmudi, Kerala: A tranquil hill station surrounded by lush greenery.\n";
                std::cout << "- Araku Valley, Andhra Pradesh: Famous for its breathtaking beauty and coffee culture.\n";

                std::cout << "Would you like to explore details about any of these? (y/n): ";
                std::cin >> response;

                if (response == 'y' || response == 'Y')
                {
                    std::string destination;
                    std::cout << "Please specify the name of the destination you re interested in: ";
                    std::cin.ignore();
                    std::getline(std::cin, destination);
                    userPreferences.push_back("Interested in: " + destination);
                    std::cout << "Great choice! We ll provide more information about " << destination << " in our follow-up.\n";
                }
                else
                {
                    std::cout << "No worries! We hope you ll explore them when the opportunity arises.\n";
                }
            }
        }
        else if (response == 'n' || response == 'N')
        {
            willing = false;
            std::cout << "\nThank you for sharing your preference. Could you let us know why you d prefer not to explore lesser-known destinations? ";
            std::cin.ignore();
            std::getline(std::cin, reason);
            userPreferences.push_back("Reason for not exploring lesser-known: " + reason);
            std::cout << "Thank you for your response: \"" << reason << "\". We respect your perspective.\n";
        }
        else
        {
            std::cout << "Invalid response. Please enter 'y' for Yes or 'n' for No.\n";
            continue;
        }

        // Option to revisit the choice
        std::cout << "\nWould you like to revisit or modify your response? (y/n): ";
        std::cin >> response;

        if (response != 'y' && response != 'Y')
        {
            continueExploring = false;
        }
    }

    // Final summary
    std::cout << "\nThank you for sharing your thoughts and preferences!\n";
    if (willing)
    {
        std::cout << "We re glad you re open to exploring lesser-known hill stations. Here s a summary of your preferences:\n";
    }
    else
    {
        std::cout << "Here s a summary of your feedback on lesser-known hill stations:\n";
    }

    for (const auto &pref : userPreferences)
    {
        std::cout << "- " << pref << "\n";
    }

    return willing;
}
bool awareOfEcoTourism()
{
    bool aware = false;
    char response;
    bool continueExploring = true;
    std::string reason;
    std::vector<std::string> awarenessDetails;

    // Introduction
    std::cout << "Eco-tourism is a sustainable travel concept that focuses on conserving nature and promoting local cultures.\n";
    std::cout << "It encourages responsible tourism to ensure the beauty and integrity of destinations are preserved for future generations.\n";
    std::cout << "In this survey, we d like to know your awareness level about eco-tourism and your thoughts on how it impacts the places we visit.\n";

    while (continueExploring)
    {
        // User prompt
        std::cout << "\nAre you aware of the concept of eco-tourism? (y/n): ";
        std::cin >> response;

        if (response == 'y' || response == 'Y')
        {
            aware = true;
            std::cout << "\nThat s fantastic! Eco-tourism plays an important role in the future of travel. Would you mind sharing what you understand about eco-tourism?\n";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, reason);
            awarenessDetails.push_back("User's understanding of eco-tourism: " + reason);
            std::cout << "Thank you for sharing your understanding: \"" << reason << "\". That s a very insightful point.\n";

            // Further engagement: Providing scenarios and asking for feedback
            std::cout << "\nLet s dive deeper. Eco-tourism is not just about visiting nature reserves or national parks. It can also include staying in eco-friendly accommodations, using sustainable transport options, and supporting local communities.\n";
            std::cout << "Which of the following eco-tourism practices resonate most with you?\n";
            std::cout << "1. Staying in eco-friendly accommodations (e.g., solar-powered hotels, eco-lodges).\n";
            std::cout << "2. Choosing sustainable transport options (e.g., bicycles, trains, electric vehicles).\n";
            std::cout << "3. Supporting local businesses and artisans, helping the economy.\n";
            std::cout << "4. Participating in conservation efforts, like wildlife protection or clean-up campaigns.\n";
            std::cout << "5. Engaging with local cultures in a responsible way (e.g., respecting traditions and customs).\n";
            std::cout << "6. Other (Please specify).\n";
            std::cout << "Please select one or more options (e.g., 1,3,4): ";

            std::string choices;
            std::cin.ignore();
            std::getline(std::cin, choices);

            std::cout << "You selected: " << choices << ". Let s explore these options further.\n";
            if (choices.find('1') != std::string::npos)
            {
                std::cout << "Staying in eco-friendly accommodations helps reduce the environmental footprint of your stay and supports eco-conscious businesses.\n";
                awarenessDetails.push_back("Prefers eco-friendly accommodations.");
            }
            if (choices.find('2') != std::string::npos)
            {
                std::cout << "Opting for sustainable transport helps reduce carbon emissions and contributes to the reduction of your travel s environmental impact.\n";
                awarenessDetails.push_back("Chooses sustainable transport.");
            }
            if (choices.find('3') != std::string::npos)
            {
                std::cout << "Supporting local businesses ensures that the benefits of tourism are passed directly to the community, helping them thrive economically.\n";
                awarenessDetails.push_back("Supports local businesses.");
            }
            if (choices.find('4') != std::string::npos)
            {
                std::cout << "Engaging in conservation efforts not only protects ecosystems but also raises awareness of environmental issues.\n";
                awarenessDetails.push_back("Participates in conservation efforts.");
            }
            if (choices.find('5') != std::string::npos)
            {
                std::cout << "Respecting local cultures is vital for fostering positive relationships and helping preserve traditions.\n";
                awarenessDetails.push_back("Engages responsibly with local cultures.");
            }
            if (choices.find('6') != std::string::npos)
            {
                std::string otherPreference;
                std::cout << "Please specify what other eco-tourism practices you value: ";
                std::getline(std::cin, otherPreference);
                awarenessDetails.push_back("Other eco-tourism practice: " + otherPreference);
                std::cout << "Thank you for sharing: \"" << otherPreference << "\". This is certainly an important aspect of eco-tourism.\n";
            }

            // Deep dive into eco-tourism benefits and challenges
            std::cout << "\nEco-tourism can be a win-win for both the environment and travelers. However, it also comes with its challenges, such as the need for proper education, regulation, and infrastructure.\n";
            std::cout << "Do you think there are any challenges that might hinder the growth of eco-tourism? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                std::cout << "\nCould you elaborate on what challenges you think could be barriers to eco-tourism?\n";
                std::cin.ignore();
                std::getline(std::cin, reason);
                awarenessDetails.push_back("Challenges to eco-tourism: " + reason);
                std::cout << "Thank you for sharing your thoughts: \"" << reason << "\". Addressing these challenges is crucial for the future of eco-tourism.\n";
            }
            else
            {
                std::cout << "That s great! Eco-tourism has a lot of potential to grow and benefit both travelers and the environment.\n";
            }

            // Follow-up questions about future involvement
            std::cout << "\nWould you be willing to adjust your travel habits to embrace more eco-tourism practices in the future? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                aware = true;
                std::cout << "\nThat s fantastic! Every small change makes a difference. What kind of changes do you think you could make in your future travels?\n";
                std::cin.ignore(); // Clear input buffer
                std::getline(std::cin, reason);
                awarenessDetails.push_back("Willing to embrace eco-tourism practices: " + reason);
                std::cout << "Thank you for your willingness to make a positive impact on the environment and communities!\n";
            }
            else
            {
                std::cout << "No problem! It s important to go at your own pace. However, even being informed is a great first step.\n";
            }
        }
        else if (response == 'n' || response == 'N')
        {
            aware = false;
            std::cout << "\nThat s okay! Eco-tourism is still a relatively new concept to many people. Let me provide you with a brief overview.\n";
            std::cout << "- Eco-tourism focuses on responsible travel practices that conserve the environment and respect local cultures.\n";
            std::cout << "- It supports sustainable travel by reducing waste, conserving natural resources, and promoting eco-friendly practices.\n";
            std::cout << "- It can include things like traveling to nature reserves, staying in eco-lodges, and supporting local communities.\n";
            std::cout << "\nWould you like to learn more about eco-tourism, including specific practices and examples? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                std::cout << "\nThat s great! Here are a few eco-tourism practices you can start with:\n";
                std::cout << "- Reducing waste by avoiding plastic and using reusable items (e.g., bottles, bags).\n";
                std::cout << "- Staying at accommodations that prioritize sustainability, like solar-powered or zero-waste hotels.\n";
                std::cout << "- Participating in activities that help conserve nature, like wildlife watching or volunteering in clean-up campaigns.\n";
                awarenessDetails.push_back("User interested in learning more about eco-tourism.");
            }
            else
            {
                std::cout << "No worries! You can always revisit this idea when you're ready.\n";
                awarenessDetails.push_back("User not interested in learning more about eco-tourism.");
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter 'y' for Yes or 'n' for No.\n";
            continue;
        }

        // Option to revisit choices
        std::cout << "\nWould you like to revisit or modify your responses? (y/n): ";
        std::cin >> response;

        if (response != 'y' && response != 'Y')
        {
            continueExploring = false;
        }
    }

    // Final summary
    std::cout << "\nThank you for sharing your thoughts on eco-tourism!\n";
    if (aware)
    {
        std::cout << "We re thrilled that you re aware of eco-tourism. Here s a summary of your feedback:\n";
    }
    else
    {
        std::cout << "Here s a summary of your responses about eco-tourism:\n";
    }

    for (const auto &detail : awarenessDetails)
    {
        std::cout << "- " << detail << "\n";
    }

    return aware;
}
bool willingToFollowSustainablePractices()
{
    bool willing = false;
    char response;
    bool continueExploring = true;
    std::string reason;
    std::vector<std::string> sustainablePracticesDetails;

    // Introduction to sustainable practices
    std::cout << "Sustainable practices are actions that individuals and communities can adopt to reduce their environmental impact. These practices are crucial to preserving resources for future generations.\n";
    std::cout << "In this section, we would like to know your willingness to adopt such practices while traveling and in your daily life.\n";

    while (continueExploring)
    {
        // Prompt for willingness to follow sustainable practices
        std::cout << "\nAre you willing to follow sustainable practices while traveling and in your daily activities? (y/n): ";
        std::cin >> response;

        if (response == 'y' || response == 'Y')
        {
            willing = true;
            std::cout << "\nThat s wonderful! Every small step towards sustainability helps the planet. Let s discuss some specific sustainable practices that can be implemented while traveling.\n";
            std::cout << "Would you be willing to adopt the following sustainable practices during your travels? Please answer 'yes' or 'no' for each one.\n";

            // List of sustainable practices to choose from
            std::cout << "1. Reducing the use of single-use plastics (e.g., using reusable water bottles, avoiding plastic straws).\n";
            std::cout << "2. Choosing eco-friendly accommodations (e.g., staying at green-certified hotels, eco-lodges).\n";
            std::cout << "3. Opting for sustainable transport options (e.g., electric vehicles, public transportation, cycling).\n";
            std::cout << "4. Minimizing water and energy consumption (e.g., taking shorter showers, turning off lights).\n";
            std::cout << "5. Supporting local and ethical businesses (e.g., local artisans, farmers  markets).\n";
            std::cout << "6. Participating in environmental conservation activities (e.g., volunteering for clean-up campaigns).\n";
            std::cout << "7. Choosing to travel to destinations with eco-tourism initiatives.\n";
            std::cout << "8. Avoiding waste by packing light and buying only what is necessary.\n";
            std::cout << "Please enter your responses in the following format (e.g., 1, 3, 5, 7): ";

            std::string choices;
            std::cin.ignore();
            std::getline(std::cin, choices);

            std::cout << "You selected: " << choices << ". Let s explore each option you selected.\n";
            if (choices.find('1') != std::string::npos)
            {
                std::cout << "Reducing single-use plastics is one of the easiest and most effective ways to reduce environmental waste. It also sets an example for others.\n";
                sustainablePracticesDetails.push_back("Interested in reducing single-use plastics.");
            }
            if (choices.find('2') != std::string::npos)
            {
                std::cout << "Choosing eco-friendly accommodations helps reduce your carbon footprint and supports businesses that are making a positive impact on the environment.\n";
                sustainablePracticesDetails.push_back("Interested in staying at eco-friendly accommodations.");
            }
            if (choices.find('3') != std::string::npos)
            {
                std::cout << "Sustainable transport options like electric vehicles or using public transport can significantly reduce your carbon emissions during travel.\n";
                sustainablePracticesDetails.push_back("Interested in opting for sustainable transport options.");
            }
            if (choices.find('4') != std::string::npos)
            {
                std::cout << "Minimizing water and energy consumption not only reduces environmental impact but also saves resources for future generations.\n";
                sustainablePracticesDetails.push_back("Interested in minimizing water and energy consumption.");
            }
            if (choices.find('5') != std::string::npos)
            {
                std::cout << "Supporting local businesses helps build a sustainable economy and empowers the local community.\n";
                sustainablePracticesDetails.push_back("Interested in supporting local and ethical businesses.");
            }
            if (choices.find('6') != std::string::npos)
            {
                std::cout << "Participating in conservation activities such as clean-up campaigns and tree planting is an effective way to give back to the environment.\n";
                sustainablePracticesDetails.push_back("Interested in participating in environmental conservation activities.");
            }
            if (choices.find('7') != std::string::npos)
            {
                std::cout << "Eco-tourism destinations help promote sustainable tourism while preserving the environment and supporting local communities.\n";
                sustainablePracticesDetails.push_back("Interested in traveling to eco-tourism destinations.");
            }
            if (choices.find('8') != std::string::npos)
            {
                std::cout << "Packing light and buying only what is necessary reduces waste and prevents overconsumption, which is essential for sustainability.\n";
                sustainablePracticesDetails.push_back("Interested in avoiding waste by packing light.");
            }

            // Follow-up question about sustainability in daily life
            std::cout << "\nApart from travel, are you also willing to adopt sustainable practices in your daily life? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                std::cout << "\nThat s fantastic! Here are some sustainable practices you can consider in your everyday life:\n";
                std::cout << "1. Reducing meat consumption to lower your carbon footprint.\n";
                std::cout << "2. Recycling and composting waste to reduce landfill waste.\n";
                std::cout << "3. Using energy-efficient appliances and switching off unused devices.\n";
                std::cout << "4. Planting trees or starting a home garden to contribute to reforestation.\n";
                std::cout << "5. Using eco-friendly products like biodegradable cleaning agents and organic cotton.\n";
                std::cout << "Which of these practices do you feel you could easily incorporate into your routine?\n";
                std::cout << "Please select the ones that apply (e.g., 1, 3, 5): ";

                std::string dailyChoices;
                std::cin.ignore();
                std::getline(std::cin, dailyChoices);

                if (dailyChoices.find('1') != std::string::npos)
                {
                    std::cout << "Reducing meat consumption can have a significant impact on lowering your carbon footprint and protecting the environment.\n";
                    sustainablePracticesDetails.push_back("Willing to reduce meat consumption.");
                }
                if (dailyChoices.find('2') != std::string::npos)
                {
                    std::cout << "Recycling and composting are essential for reducing waste and supporting the environment s natural cycles.\n";
                    sustainablePracticesDetails.push_back("Willing to recycle and compost.");
                }
                if (dailyChoices.find('3') != std::string::npos)
                {
                    std::cout << "Using energy-efficient appliances is a great way to save energy and reduce your overall consumption.\n";
                    sustainablePracticesDetails.push_back("Willing to use energy-efficient appliances.");
                }
                if (dailyChoices.find('4') != std::string::npos)
                {
                    std::cout << "Planting trees and gardening can help restore biodiversity and improve air quality.\n";
                    sustainablePracticesDetails.push_back("Willing to plant trees or garden.");
                }
                if (dailyChoices.find('5') != std::string::npos)
                {
                    std::cout << "Using eco-friendly products is a simple yet effective way to reduce your environmental impact.\n";
                    sustainablePracticesDetails.push_back("Willing to use eco-friendly products.");
                }
            }
            else
            {
                std::cout << "\nNo worries! Sustainable practices can be gradually integrated into daily life, and any small effort counts.\n";
            }

            // Closing the loop on willingness
            std::cout << "\nDo you feel that following sustainable practices will be difficult for you? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                std::cout << "\nIt s understandable that adopting new habits can be challenging. Many people face similar obstacles. What do you think would make it easier for you to follow sustainable practices?\n";
                std::cin.ignore();
                std::getline(std::cin, reason);
                sustainablePracticesDetails.push_back("Challenges in following sustainable practices: " + reason);
                std::cout << "Thank you for sharing. It s important to recognize challenges so we can work toward overcoming them.\n";
            }
            else
            {
                std::cout << "\nThat s great! Your willingness to follow sustainable practices will certainly make a positive impact.\n";
            }
        }
        else if (response == 'n' || response == 'N')
        {
            willing = false;
            std::cout << "\nThat s okay! Not everyone is ready to adopt sustainable practices, but it s always good to be aware of them.\n";
            std::cout << "Would you like to learn more about the benefits of sustainable practices or how you could start incorporating them in the future? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y')
            {
                std::cout << "\nHere are some quick benefits of adopting sustainable practices:\n";
                std::cout << "- Reduces environmental impact and conserves resources.\n";
                std::cout << "- Saves money in the long term (e.g., energy-saving appliances, reducing waste).\n";
                std::cout << "- Improves health and well-being (e.g., reducing pollution, using natural products).\n";
                std::cout << "- Contributes to a positive, long-term change for the planet.\n";
                std::cout << "Would you like to explore some simple steps to start your journey towards sustainability? (y/n): ";
                std::cin >> response;

                if (response == 'y' || response == 'Y')
                {
                    std::cout << "\nSome simple steps to start with include:\n";
                    std::cout << "- Start using reusable bags, bottles, and utensils.\n";
                    std::cout << "- Consider walking, cycling, or using public transport instead of driving.\n";
                    std::cout << "- Reduce water and energy use in your daily routines.\n";
                    std::cout << "- Support local and sustainable businesses.\n";
                }
                else
                {
                    std::cout << "No worries! You can always revisit the idea later when you re ready.\n";
                }
            }
            else
            {
                std::cout << "That s perfectly fine. Just remember that small changes can make a big difference.\n";
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter 'y' for Yes or 'n' for No.\n";
            continue;
        }

        // Option to revisit choices
        std::cout << "\nWould you like to revisit or modify your responses? (y/n): ";
        std::cin >> response;

        if (response != 'y' && response != 'Y')
        {
            continueExploring = false;
        }
    }

    // Final summary
    std::cout << "\nThank you for sharing your thoughts on following sustainable practices!\n";
    if (willing)
    {
        std::cout << "We re excited that you re willing to adopt sustainable practices. Here s a summary of your responses:\n";
    }
    else
    {
        std::cout << "Here s a summary of your responses about sustainability:\n";
    }

    for (const auto &detail : sustainablePracticesDetails)
    {
        std::cout << "- " << detail << "\n";
    }

    return willing;
}
std::string getAdditionalComments()
{
    std::string comments;
    char continueFeedback;
    std::vector<std::string> additionalSuggestions;

    std::cout << "We value your feedback and would love to hear any additional comments or suggestions you may have.\n";
    std::cout << "Feel free to share your thoughts on the survey experience, improvements, or anything else you'd like to discuss.\n";
    std::cout << "You can type your comments below, and when you're ready, we'll proceed.\n";

    // Initial input for comments
    std::cout << "Please enter your additional comments: ";
    std::cin.ignore();
    std::getline(std::cin, comments);

    // Collect more details about feedback
    std::cout << "\nThank you for your comments! To make sure we improve the survey, could you please answer the following questions:\n";
    std::cout << "1. Was the survey easy to understand and navigate? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        additionalSuggestions.push_back("Survey was easy to understand and navigate.");
    }
    else
    {
        additionalSuggestions.push_back("Survey had difficulties in understanding or navigation.");
        std::cout << "Please let us know how we can improve the navigation or understanding of the survey: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Improvement suggestions: " + comments);
    }

    std::cout << "\n2. Were the questions clear and relevant to you? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        additionalSuggestions.push_back("Questions were clear and relevant.");
    }
    else
    {
        additionalSuggestions.push_back("Questions were unclear or irrelevant.");
        std::cout << "Which questions do you think were unclear or irrelevant, and how could we improve them? ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Improvement suggestions: " + comments);
    }

    std::cout << "\n3. Was the length of the survey appropriate? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        additionalSuggestions.push_back("Survey length was appropriate.");
    }
    else
    {
        additionalSuggestions.push_back("Survey was too long or too short.");
        std::cout << "How could we adjust the length of the survey for better user experience? ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Length adjustment suggestions: " + comments);
    }

    std::cout << "\n4. Did you find any part of the survey repetitive or redundant? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        additionalSuggestions.push_back("Survey had repetitive or redundant parts.");
        std::cout << "Please specify which sections were repetitive or redundant, and how we can streamline them: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Repetitive sections: " + comments);
    }
    else
    {
        additionalSuggestions.push_back("Survey did not have repetitive sections.");
    }

    std::cout << "\n5. Did you feel the survey covered all aspects of your experience? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        additionalSuggestions.push_back("Survey covered all aspects of the experience.");
    }
    else
    {
        additionalSuggestions.push_back("Survey missed some important aspects.");
        std::cout << "Which aspects do you think were missing, and how could we include them? ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Missing aspects suggestions: " + comments);
    }

    std::cout << "\n6. Were there any questions or topics you felt uncomfortable answering? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        additionalSuggestions.push_back("Survey had uncomfortable questions.");
        std::cout << "Please specify which questions made you uncomfortable and how we can modify them: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Uncomfortable questions suggestions: " + comments);
    }
    else
    {
        additionalSuggestions.push_back("No uncomfortable questions.");
    }

    // Collecting improvement suggestions for the survey
    std::cout << "\nWould you like to share any specific ideas for improving the survey or making it more engaging? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        std::cout << "Please enter your suggestions: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Survey improvement ideas: " + comments);
    }

    // Asking about the overall experience with the survey
    std::cout << "\nOn a scale from 1 to 10, how would you rate your overall experience with this survey? (1 being poor, 10 being excellent): ";
    int rating;
    std::cin >> rating;

    if (rating >= 8)
    {
        std::cout << "\nThank you! We're glad to hear that you had a positive experience. We will strive to maintain these standards.\n";
    }
    else if (rating >= 5)
    {
        std::cout << "\nThank you for your feedback. We will take your suggestions seriously to improve the survey in the future.\n";
    }
    else
    {
        std::cout << "\nWe appreciate your honesty. Please share what could be improved in the survey to ensure a better experience next time: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Suggestions for improving survey experience: " + comments);
    }

    // Asking for final comments
    std::cout << "\nDo you have any additional comments or suggestions you d like to share before we finish? (y/n): ";
    std::cin >> continueFeedback;

    if (continueFeedback == 'y' || continueFeedback == 'Y')
    {
        std::cout << "Please enter your final thoughts: ";
        std::cin.ignore();
        std::getline(std::cin, comments);
        additionalSuggestions.push_back("Final comments: " + comments);
    }

    // Summarizing the collected feedback
    std::cout << "\nThank you for sharing your valuable feedback with us. Here's a summary of your responses:\n";
    for (const auto &suggestion : additionalSuggestions)
    {
        std::cout << "- " << suggestion << "\n";
    }

    // Returning the final comments string
    return comments;
}
int module2()
{
    displayWelcomeMessage();
    displayIntroduction();
    displayInstructions();

    SurveyResponse response;
    response.name = getName();
    response.age = getAge();
    response.gender = getGender();
    response.location = getLocation();
    response.visitedHillStation = hasVisitedHillStation();
    response.transportMode = getTransportMode();
    // response.travelDuration = getTravelDuration();
    response.travelCompanions = getTravelCompanions();
    response.favoriteHillStation = getFavoriteHillStation();
    response.activitiesEnjoyed = getActivities();
    response.rating = getRating();
    response.feedback = getFeedback();
    response.hillStationType = getHillStationType();
    response.keyFactors = getKeyFactors();
    response.desiredAmenities = getDesiredAmenities();
    response.exploreLesserKnown = willingToExploreLesserKnown();
    response.awareEcoTourism = awareOfEcoTourism();
    response.followSustainablePractices = willingToFollowSustainablePractices();
    // response.suggestions = getSuggestions();
    response.additionalComments = getAdditionalComments();

    // saveSurveyData(response);
    // displayThankYouMessage();

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <queue>
#include <unordered_map>

using namespace std;

// Struct for City Connections
struct Connection
{
    string from;
    string to;
    int distance; // in kilometers
    string mode;  // Mode of transport (e.g., Bus, Metro, Taxi)
};

// Struct for Feedback
struct Feedback
{
    string user;
    string message;
    int rating; // 1 to 5
};

// Base class for Urban Development Components
class UrbanComponent
{
protected:
    string name;

public:
    UrbanComponent(const string &name) : name(name) {}
    virtual void displayDetails() const = 0; // Pure virtual function
    string getName() const { return name; }  // Getter for name
    virtual ~UrbanComponent() {}
};

// Resource Allocation Class
class ResourceAllocation : public UrbanComponent
{
private:
    double budget;
    string allocatedTo;

public:
    ResourceAllocation(const string &name, double budget, const string &allocatedTo)
        : UrbanComponent(name), budget(budget), allocatedTo(allocatedTo) {}

    void updateBudget(double newBudget)
    {
        budget = newBudget;
    }

    void updateAllocation(const string &newAllocation)
    {
        allocatedTo = newAllocation;
    }

    void displayDetails() const override
    {
        cout << "[Resource Allocation] " << name << " - Budget: $" << budget << "M, Allocated To: " << allocatedTo << "\n";
    }
};

// Community Engagement Component Class
class CommunityEngagement : public UrbanComponent
{
private:
    string feedback;

public:
    CommunityEngagement(const string &name, const string &feedback)
        : UrbanComponent(name), feedback(feedback) {}

    void updateFeedback(const string &newFeedback)
    {
        feedback = newFeedback;
    }

    void displayDetails() const override
    {
        cout << "[Community Engagement] " << name << " - Feedback: " << feedback << "\n";
    }
};

// Infrastructure Development Planning Class
class Infrastructure : public UrbanComponent
{
private:
    int cost;
    string status;

public:
    Infrastructure(const string &name, int cost, const string &status)
        : UrbanComponent(name), cost(cost), status(status) {}

    void updateStatus(const string &newStatus)
    {
        status = newStatus;
    }

    void displayDetails() const override
    {
        cout << "[Infrastructure] " << name << " - Cost: $" << cost << "M, Status: " << status << "\n";
    }
};

// Integrated Housing Solution Class
class HousingSolution : public UrbanComponent
{
private:
    int units;
    string status;

public:
    HousingSolution(const string &name, int units, const string &status)
        : UrbanComponent(name), units(units), status(status) {}

    void updateUnits(int newUnits)
    {
        units = newUnits;
    }

    void updateStatus(const string &newStatus)
    {
        status = newStatus;
    }

    void displayDetails() const override
    {
        cout << "[Housing Solution] " << name << " - Units: " << units << ", Status: " << status << "\n";
    }
};

// Environmental Initiative Class
class EnvironmentalInitiative : public UrbanComponent
{
private:
    string initiative;
    double budget;

public:
    EnvironmentalInitiative(const string &name, const string &initiative, double budget)
        : UrbanComponent(name), initiative(initiative), budget(budget) {}

    void updateInitiative(const string &newInitiative)
    {
        initiative = newInitiative;
    }

    void updateBudget(double newBudget)
    {
        budget = newBudget;
    }

    void displayDetails() const override
    {
        cout << "[Environmental Initiative] " << name << " - Initiative: " << initiative << ", Budget: $" << budget << "M\n";
    }
};

// Public Transportation Management Class
class PublicTransport : public UrbanComponent
{
private:
    string type; // e.g., Bus, Metro, Tram
    int numVehicles;

public:
    PublicTransport(const string &name, const string &type, int numVehicles)
        : UrbanComponent(name), type(type), numVehicles(numVehicles) {}

    void updateType(const string &newType)
    {
        type = newType;
    }

    void updateNumVehicles(int newNumVehicles)
    {
        numVehicles = newNumVehicles;
    }

    void displayDetails() const override
    {
        cout << "[Public Transport] " << name << " - Type: " << type << ", Number of Vehicles: " << numVehicles << "\n";
    }
};

// Community Service Center Class
class CommunityServiceCenter : public UrbanComponent
{
private:
    string serviceType; // e.g., Healthcare, Education, Recreation
    int capacity;

public:
    CommunityServiceCenter(const string &name, const string &serviceType, int capacity)
        : UrbanComponent(name), serviceType(serviceType), capacity(capacity) {}

    void updateServiceType(const string &newServiceType)
    {
        serviceType = newServiceType;
    }

    void updateCapacity(int newCapacity)
    {
        capacity = newCapacity;
    }

    void displayDetails() const override
    {
        cout << "[Community Service Center] " << name << " - Service Type: " << serviceType << ", Capacity: " << capacity << "\n";
    }
};

// Smart City Technology Class
class SmartCityTechnology : public UrbanComponent
{
private:
    string technologyType; // e.g., IoT, AI, Big Data
    double investment;

public:
    SmartCityTechnology(const string &name, const string &technologyType, double investment)
        : UrbanComponent(name), technologyType(technologyType), investment(investment) {}

    void updateTechnologyType(const string &newTechnologyType)
    {
        technologyType = newTechnologyType;
    }

    void updateInvestment(double newInvestment)
    {
        investment = newInvestment;
    }

    void displayDetails() const override
    {
        cout << "[Smart City Technology] " << name << " - Technology Type: " << technologyType << ", Investment: $" << investment << "M\n";
    }
};

// Renewable Energy Project Class
class RenewableEnergyProject : public UrbanComponent
{
private:
    string energyType; // e.g., Solar, Wind, Hydro
    double capacity;   // in MW

public:
    RenewableEnergyProject(const string &name, const string &energyType, double capacity)
        : UrbanComponent(name), energyType(energyType), capacity(capacity) {}

    void updateEnergyType(const string &newEnergyType)
    {
        energyType = newEnergyType;
    }

    void updateCapacity(double newCapacity)
    {
        capacity = newCapacity;
    }

    void displayDetails() const override
    {
        cout << "[Renewable Energy Project] " << name << " - Energy Type: " << energyType << ", Capacity: " << capacity << " MW\n";
    }
};

// Urban Planning Class
class UrbanPlanning
{
private:
    vector<ResourceAllocation> resourceAllocations;
    vector<CommunityEngagement> communityEngagements;
    vector<Infrastructure> infrastructures;
    vector<HousingSolution> housingSolutions;
    vector<EnvironmentalInitiative> environmentalInitiatives;
    vector<PublicTransport> publicTransports;
    vector<CommunityServiceCenter> communityServiceCenters;
    vector<SmartCityTechnology> smartCityTechnologies;
    vector<RenewableEnergyProject> renewableEnergyProjects;

public:
    void addResourceAllocation(const ResourceAllocation &allocation)
    {
        resourceAllocations.push_back(allocation);
    }

    void addCommunityEngagement(const CommunityEngagement &engagement)
    {
        communityEngagements.push_back(engagement);
    }

    void addInfrastructure(const Infrastructure &infra)
    {
        infrastructures.push_back(infra);
    }

    void addHousingSolution(const HousingSolution &solution)
    {
        housingSolutions.push_back(solution);
    }

    void addEnvironmentalInitiative(const EnvironmentalInitiative &initiative)
    {
        environmentalInitiatives.push_back(initiative);
    }

    void addPublicTransport(const PublicTransport &transport)
    {
        publicTransports.push_back(transport);
    }

    void addCommunityServiceCenter(const CommunityServiceCenter &center)
    {
        communityServiceCenters.push_back(center);
    }

    void addSmartCityTechnology(const SmartCityTechnology &technology)
    {
        smartCityTechnologies.push_back(technology);
    }

    void addRenewableEnergyProject(const RenewableEnergyProject &project)
    {
        renewableEnergyProjects.push_back(project);
    }

    void displayPlan() const
    {
        cout << "\nUrban Development Plan:\n";
        cout << "-------------------------\n";
        for (const auto &allocation : resourceAllocations)
        {
            allocation.displayDetails();
        }
        for (const auto &engagement : communityEngagements)
        {
            engagement.displayDetails();
        }
        for (const auto &infra : infrastructures)
        {
            infra.displayDetails();
        }
        for (const auto &solution : housingSolutions)
        {
            solution.displayDetails();
        }
        for (const auto &initiative : environmentalInitiatives)
        {
            initiative.displayDetails();
        }
        for (const auto &transport : publicTransports)
        {
            transport.displayDetails();
        }
        for (const auto &center : communityServiceCenters)
        {
            center.displayDetails();
        }
        for (const auto &technology : smartCityTechnologies)
        {
            technology.displayDetails();
        }
        for (const auto &project : renewableEnergyProjects)
        {
            project.displayDetails();
        }
    }
};

// City Connectivity Class
class CityConnectivity
{
private:
    vector<Connection> connections;
    vector<Feedback> feedbacks;

    void displayConnections()
    {
        if (connections.empty())
        {
            cout << "\nNo connections available.\n";
            return;
        }

        cout << "\nCurrent City Connections:\n";
        for (const auto &conn : connections)
        {
            cout << conn.from << " -> " << conn.to << ": " << conn.distance << " km, Mode: "
                 << (conn.mode.empty() ? "Not Assigned" : conn.mode) << "\n";
        }
    }

    int findShortestPath(const string &start, const string &end)
    {
        unordered_map<string, vector<pair<string, int>>> adj;
        for (const auto &conn : connections)
        {
            adj[conn.from].emplace_back(conn.to, conn.distance);
            adj[conn.to].emplace_back(conn.from, conn.distance); // Assuming undirected graph
        }

        unordered_map<string, int> distances;
        for (const auto &conn : connections)
        {
            distances[conn.from] = numeric_limits<int>::max();
            distances[conn.to] = numeric_limits<int>::max();
        }
        distances[start] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty())
        {
            auto [currentDistance, currentNode] = pq.top();
            pq.pop();

            if (currentNode == end)
                return currentDistance;

            for (const auto &[neighbor, weight] : adj[currentNode])
            {
                int distance = currentDistance + weight;
                if (distance < distances[neighbor])
                {
                    distances[neighbor] = distance;
                    pq.emplace(distance, neighbor);
                }
            }
        }

        return numeric_limits<int>::max();
    }

public:
    CityConnectivity()
    {
        connections = {
            {"A", "B", 4500, ""},
            {"B", "C", 2800, ""},
            {"A", "D", 2600, ""},
            {"D", "E", 2000, ""},
            {"C", "E", 2400, ""}};
    }

    void addConnection()
    {
        string from, to;
        int distance;
        cout << "Enter new connection (Format: CityA CityB Distance): ";
        cin >> from >> to >> distance;

        connections.push_back({from, to, distance, ""});
        cout << "New connection added: " << from << " -> " << to << ": " << distance << " km\n";
    }

    void viewConnections()
    {
        displayConnections();
    }

    void findShortestPath()
    {
        string start, end;
        cout << "Enter start city and end city (Format: CityA CityB): ";
        cin >> start >> end;

        int shortestDistance = findShortestPath(start, end);

        if (shortestDistance == numeric_limits<int>::max())
        {
            cout << "No path exists between " << start << " and " << end << ".\n";
        }
        else
        {
            cout << "Shortest path from " << start << " to " << end << ": " << shortestDistance << " km\n";
        }
    }

    void optimizeNetwork()
    {
        sort(connections.begin(), connections.end(), [](Connection a, Connection b)
             { return a.distance < b.distance; });

        map<string, string> parent;

        auto findRoot = [&parent](string zone) -> string
        {
            while (parent[zone] != zone)
            {
                zone = parent[zone];
            }
            return zone;
        };

        for (const auto &conn : connections)
        {
            parent[conn.from] = conn.from;
            parent[conn.to] = conn.to;
        }

        vector<Connection> optimizedConnections;
        int totalDistance = 0;

        for (const auto &conn : connections)
        {
            string rootFrom = findRoot(conn.from);
            string rootTo = findRoot(conn.to);

            if (rootFrom != rootTo)
            {
                optimizedConnections.push_back(conn);
                totalDistance += conn.distance;
                parent[rootFrom] = rootTo;
            }
        }

        cout << "\nOptimized Network:\n";
        for (const auto &conn : optimizedConnections)
        {
            cout << conn.from << " -> " << conn.to << ": " << conn.distance << " km\n";
        }
        cout << "Total Optimized Distance: " << totalDistance << " km\n";
    }

    void dynamicScheduling()
    {
        map<string, vector<string>> schedule;
        schedule["Morning"] = {"Bus", "Metro"};
        schedule["Afternoon"] = {"Bus", "Bicycle"};
        schedule["Evening"] = {"Metro", "Walking"};

        cout << "\nDynamic Scheduling:\n";
        for (const auto &slot : schedule)
        {
            cout << slot.first << " routes: ";
            for (const auto &mode : slot.second)
            {
                cout << mode << " ";
            }
            cout << endl;
        }
    }

    void routePlanning()
    {
        string start, end;
        cout << "Enter starting city: ";
        cin >> start;
        cout << "Enter ending city: ";
        cin >> end;

        int distance = findShortestPath(start, end);

        if (distance == numeric_limits<int>::max())
        {
            cout << "No route found from " << start << " to " << end << ".\n";
        }
        else
        {
            cout << "Route planned successfully. Distance: " << distance << " km\n";
        }
    }

    void integrateServices()
    {
        vector<string> services = {"Bus", "Metro", "Taxi", "Bicycle"};
        cout << "\nIntegrated Services:\n";
        for (const auto &service : services)
        {
            cout << service << " ";
        }
        cout << endl;
    }

    void selectTransportMode()
    {
        string from, to;
        cout << "Enter connection (Format: CityA CityB): ";
        cin >> from >> to;

        auto it = find_if(connections.begin(), connections.end(), [&](Connection &conn)
                          { return conn.from == from && conn.to == to; });

        if (it != connections.end())
        {
            cout << "Select mode of transport (Bus, Metro, Taxi, Bicycle): ";
            cin >> it->mode;
            cout << "Mode of transport for " << from << " -> " << to << " set to " << it->mode << ".\n";
        }
        else
        {
            cout << "Connection not found.\n";
        }
    }

    void feedbackMechanism()
    {
        string user, message;
        int rating;
        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, user);
        cout << "Enter your feedback message: ";
        getline(cin, message);
        cout << "Enter a rating (1 to 5): ";
        cin >> rating;

        feedbacks.push_back({user, message, rating});
        cout << "Thank you for your feedback!\n";

        cout << "\nRecent Feedbacks:\n";
        for (const auto &fb : feedbacks)
        {
            cout << "User: " << fb.user << ", Rating: " << fb.rating << ", Message: " << fb.message << endl;
        }
    }

    void chooseTransportTimings()
    {
        string from, to, timing;
        cout << "Enter connection (Format: CityA CityB): ";
        cin >> from >> to;

        auto it = find_if(connections.begin(), connections.end(), [&](Connection &conn)
                          { return conn.from == from && conn.to == to; });

        if (it != connections.end())
        {
            cout << "Enter preferred timing (e.g., Morning, Afternoon, Evening): ";
            cin >> timing;
            cout << "Transport timing for " << from << " -> " << to << " set to " << timing << ".\n";
        }
        else
        {
            cout << "Connection not found.\n";
        }
    }
};

int module3()
{
    CityConnectivity city;
    UrbanPlanning plan;
    int choice;

    do
    {
        cout << "\nCity Connectivity and Urban Planning Management\n";
        cout << "1. View City Connections\n";
        cout << "2. Add New Connection\n";
        cout << "3. Find Shortest Path Between Cities\n";
        cout << "4. Optimize Network\n";
        cout << "5. Dynamic Scheduling\n";
        cout << "6. Route Planning\n";
        cout << "7. Integration of Services\n";
        cout << "8. Select Mode of Transport\n";
        cout << "9. Feedback Mechanism\n";
        cout << "10. Choose Transport Timings\n";
        cout << "11. Add Resource Allocation\n";
        cout << "12. Add Community Engagement\n";
        cout << "13. Add Infrastructure Project\n";
        cout << "14. Add Housing Solution\n";
        cout << "15. Add Environmental Initiative\n";
        cout << "16. Add Public Transport\n";
        cout << "17. Add Community Service Center\n";
        cout << "18. Add Smart City Technology\n";
        cout << "19. Add Renewable Energy Project\n";
        cout << "20. View Urban Development Plan\n";
        cout << "21. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            city.viewConnections();
            break;
        case 2:
            city.addConnection();
            break;
        case 3:
            city.findShortestPath();
            break;
        case 4:
            city.optimizeNetwork();
            break;
        case 5:
            city.dynamicScheduling();
            break;
        case 6:
            city.routePlanning();
            break;
        case 7:
            city.integrateServices();
            break;
        case 8:
            city.selectTransportMode();
            break;
        case 9:
            city.feedbackMechanism();
            break;
        case 10:
            city.chooseTransportTimings();
            break;
        case 11:
        {
            string name, allocatedTo;
            double budget;
            cout << "Enter Resource Allocation name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter allocated to: ";
            getline(cin, allocatedTo);
            cout << "Enter budget: ";
            cin >> budget;
            plan.addResourceAllocation(ResourceAllocation(name, budget, allocatedTo));
            break;
        }
        case 12:
        {
            string name, feedback;
            cout << "Enter Community Engagement name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter feedback: ";
            getline(cin, feedback);
            plan.addCommunityEngagement(CommunityEngagement(name, feedback));
            break;
        }
        case 13:
        {
            string name, status;
            int cost;
            cout << "Enter Infrastructure Project name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter cost: ";
            cin >> cost;
            cout << "Enter status: ";
            cin.ignore();
            getline(cin, status);
            plan.addInfrastructure(Infrastructure(name, cost, status));
            break;
        }
        case 14:
        {
            string name, status;
            int units;
            cout << "Enter Housing Solution name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter number of units: ";
            cin >> units;
            cout << "Enter status: ";
            cin.ignore();
            getline(cin, status);
            plan.addHousingSolution(HousingSolution(name, units, status));
            break;
        }
        case 15:
        {
            string name, initiative;
            double budget;
            cout << "Enter Environmental Initiative name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter initiative: ";
            getline(cin, initiative);
            cout << "Enter budget: ";
            cin >> budget;
            plan.addEnvironmentalInitiative(EnvironmentalInitiative(name, initiative, budget));
            break;
        }
        case 16:
        {
            string name, type;
            int numVehicles;
            cout << "Enter Public Transport name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter type: ";
            getline(cin, type);
            cout << "Enter number of vehicles: ";
            cin >> numVehicles;
            plan.addPublicTransport(PublicTransport(name, type, numVehicles));
            break;
        }
        case 17:
        {
            string name, serviceType;
            int capacity;
            cout << "Enter Community Service Center name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter service type: ";
            getline(cin, serviceType);
            cout << "Enter capacity: ";
            cin >> capacity;
            plan.addCommunityServiceCenter(CommunityServiceCenter(name, serviceType, capacity));
            break;
        }
        case 18:
        {
            string name, technologyType;
            double investment;
            cout << "Enter Smart City Technology name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter technology type: ";
            getline(cin, technologyType);
            cout << "Enter investment: ";
            cin >> investment;
            plan.addSmartCityTechnology(SmartCityTechnology(name, technologyType, investment));
            break;
        }
        case 19:
        {
            string name, energyType;
            double capacity;
            cout << "Enter Renewable Energy Project name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter energy type: ";
            getline(cin, energyType);
            cout << "Enter capacity (in MW): ";
            cin >> capacity;
            plan.addRenewableEnergyProject(RenewableEnergyProject(name, energyType, capacity));
            break;
        }
        case 20:
            plan.displayPlan();
            break;
        case 21:
            cout << "Exiting program. Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 21);

    return 0;
}

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Structure to represent an area
struct Area
{
    int id;
    string name;
    int population;
    int educationIndex;                    // Lower value means poor education facilities
    int schoolCount;                       // Number of schools in the area
    int dropoutRate;                       // Dropout rate percentage
    map<string, int> ageGroupDistribution; // Age group distribution (group, count)
    int waterRequirement;                  // Daily water requirement in liters
    string waterTimings;                   // Time when water is supplied
    int garbageGenerated;                  // Garbage generated daily in kg
    int garbageCollected;                  // Garbage collected daily in kg
    float unemploymentRate;                // Unemployment rate in percentage
    int jobOpportunities;                  // Number of job opportunities to be allocated
    int pendingGarbage;                    // Pending garbage for cleanup
    int cleanlinessTeams;                  // Number of teams assigned to cleanup
    int cleanupFrequency;                  // Cleanup frequency (number of days for cleanup)
};

// Class to manage development
class AreaDevelopment
{
private:
    vector<Area> areas;

    // Randomly generate a time range for water supply
    string generateRandomWaterTiming()
    {
        int startHour = rand() % 12 + 1;            // 1 to 12
        int endHour = startHour + (rand() % 3 + 1); // +1 to +3 hours
        string period = (startHour < 12) ? "AM" : "PM";
        return to_string(startHour) + " " + period + " - " + to_string(endHour % 12) + " " + period;
    }

public:
    // Generate random data for an area
    void generateRandomArea(int id, const string &name)
    {
        int population = rand() % 10000 + 1000; // Population: 1000 to 10000
        int educationIndex = rand() % 5 + 1;    // Education Index: 1 to 5
        int schoolCount = rand() % 10 + 1;      // Schools: 1 to 10
        int dropoutRate = rand() % 50 + 1;      // Dropout Rate: 1% to 50%
        map<string, int> ageGroups = {
            {"Preschool", rand() % 500 + 50},          // 50 to 500
            {"Primary School", rand() % 1000 + 100},   // 100 to 1000
            {"Secondary School", rand() % 800 + 80},   // 80 to 800
            {"Vocational Training", rand() % 300 + 30} // 30 to 300
        };
        int waterRequirement = rand() % 5000 + 500; // Water Requirement: 500 to 5000 liters
        string waterTimings = generateRandomWaterTiming();
        int garbageGenerated = rand() % 200 + 50;               // Garbage Generated: 50 to 200 kg
        int garbageCollected = rand() % (garbageGenerated + 1); // Garbage Collected: 0 to garbageGenerated
        float unemploymentRate = (rand() % 50 + 1) / 100.0;     // Unemployment rate: 1% to 50%

        // Calculate pending garbage
        int pendingGarbage = garbageGenerated - garbageCollected;
        // Cleanup frequency and teams (based on population and garbage)
        int cleanupFrequency = (rand() % 3) + 1; // Cleanup frequency: 1 to 3 days
        int cleanlinessTeams = (garbageGenerated > 100) ? 3 : (garbageGenerated > 50) ? 2
                                                                                      : 1;

        areas.push_back({id, name, population, educationIndex, schoolCount, dropoutRate, ageGroups,
                         waterRequirement, waterTimings, garbageGenerated, garbageCollected, unemploymentRate, 0,
                         pendingGarbage, cleanlinessTeams, cleanupFrequency});
    }

    // Display area details
    void displayAreaDetails()
    {
        cout << "\nArea Details:\n";
        for (const auto &area : areas)
        {
            cout << "Area: " << area.name
                 << ", Population: " << area.population
                 << ", Education Index: " << area.educationIndex
                 << ", School Count: " << area.schoolCount
                 << ", Dropout Rate: " << area.dropoutRate << "%\n";

            cout << "Unemployment Rate: " << area.unemploymentRate * 100 << "%\n";
            cout << "Job Opportunities: " << area.jobOpportunities << " jobs\n";
            cout << "Pending Garbage for Cleanup: " << area.pendingGarbage << " kg\n";
            cout << "Cleanliness Teams Assigned: " << area.cleanlinessTeams << "\n";
            cout << "Cleanup Frequency: Every " << area.cleanupFrequency << " days\n";

            cout << "Age Group Distribution (Group: Count):\n";
            for (const auto &[ageGroup, count] : area.ageGroupDistribution)
            {
                cout << ageGroup << ": " << count << " students\n";
            }

            cout << "Water Requirement: " << area.waterRequirement << " liters/day\n";
            cout << "Water Timings: " << area.waterTimings << "\n";
            cout << "Garbage Generated: " << area.garbageGenerated << " kg/day\n";
            cout << "Garbage Collected: " << area.garbageCollected << " kg/day\n";

            // Calculate garbage collection efficiency
            int efficiency = (area.garbageGenerated > 0) ? (area.garbageCollected * 100) / area.garbageGenerated : 0;
            cout << "Garbage Collection Efficiency: " << efficiency << "%\n\n";
        }
    }

    // Allocate resources including jobs and cleanup resources
    void allocateResources()
    {
        cout << "\nResource Allocation and Cleanup:\n";
        for (auto &area : areas)
        {
            // Allocate job opportunities based on unemployment rate
            area.jobOpportunities = static_cast<int>(area.unemploymentRate * area.population / 10);

            cout << "Area: " << area.name << "\n";
            cout << "Job Opportunities: " << area.jobOpportunities << " jobs\n";

            // Water resource allocation
            cout << "Water Allocation: " << area.waterRequirement << " liters/day\n";
            cout << "Garbage Cleanup Plan: " << area.pendingGarbage << " kg pending garbage to be cleaned.\n";
            cout << "Cleanliness Teams: " << area.cleanlinessTeams << " teams\n";
            cout << "Cleanup Frequency: " << area.cleanupFrequency << " days\n";

            cout << endl;
        }
    }
};

int module4()
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    int n;
    cout << "Enter the number of areas: ";
    cin >> n;

    AreaDevelopment areaDev;

    cout << "Enter area names:\n";
    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> ws; // Clear whitespace
        getline(cin, name);
        areaDev.generateRandomArea(i, name);
    }

    // Display area details
    areaDev.displayAreaDetails();

    // Allocate resources and cleanup
    areaDev.allocateResources();

    return 0;
}

int main()
{


            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                   URBAN TRANSFORMATION                                         '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    int choice;
    bool running = true;

    while (running)
    {
        // Display menu
        cout << "\n=== Menu ===" << endl;
        cout << "1. module1" << endl;
        cout << "2. module2" << endl;
        cout << "3. module3" << endl;
        cout << "4. module4" << endl;
        cout << "5. exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                   RAILWAY AND TRAFFIC MANAGEMENT                               '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            module1();
            break;

        case 2:

            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                  HILL STATION                                                  '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            module2();
            break;

        case 3:
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                  CITY CONNECTIVITY                                             '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            module3();
            break;
        case 4:
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                  SLUM MANAGEMENT DETAILS                                       '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << "**'                                                                                                '**" << endl;
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            module4();
            break;

        case 5:
            exit(0);
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }

    return 0;
}
#endif

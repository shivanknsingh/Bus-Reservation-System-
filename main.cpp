#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<limits> 

using namespace std;
struct Bus{
    string number;
    string driver;
    string arrival;
    string depart;
    string from;
    string to;
    // seats[rows=8][cols=4]
    vector<vector<string>> seats;

    Bus() : seats(8,vector<string>(4,"Empty")){}
    void setBasicInfo(){
        cout <<"Enter Bus Number: ";
        getline(cin, number);
        cout <<"Enter Driver's Name: ";
        getline(cin, driver);
        cout <<"Arrival Time: ";
        getline(cin, arrival);
        cout <<"Departure Time: ";
        getline(cin, depart);
        cout <<"From: ";
        getline(cin, from);
        cout <<"To: ";
        getline(cin,to);
    }
    // Reserve a seat (returns true if successful)
    bool reserveSeat(int seatNo,const string &passenger){
        if (seatNo<1 || seatNo>32)
            return false;
        int r=(seatNo - 1)/4;
        int c=(seatNo - 1)%4;
        if (seats[r][c] == "Empty"){
            seats[r][c]=passenger;
            return true;
        }
        return false;
    }

    void showReservations() const{
        cout <<"Bus Number: "<<number<<"\nDriver: "<<driver
             << "\nArrival: "<< arrival<<"\tDeparture: " <<depart
             << "\nFrom: " << from << "\tTo: "<< to <<"\n";
        printSeatMap();
    }

    void printSeatMap() const{
        cout << "Seat map (Empty means available):\n";
        int idx = 1;
        for (int r = 0; r < 8; ++r){
            for (int c = 0; c < 4; ++c)
            {
                cout << setw(2) << idx++ << ". " << setw(10) << seats[r][c] << "  ";
            }
            cout << "\n";
        }
        cout <<"\n";
    }
    // Count empty seats
    int emptyCount() const{
        int cnt=0;
        for (auto &row :seats)
            for (auto &s :row)
                if (s == "Empty")
                    ++cnt;
        return cnt;
    }
};

static vector<Bus> buses;

static void pauseForEnter()
{
    cout<<"Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void printHeader(){
    cout << "\n-------------------------------------\n";
    cout << "|   SIMPLE BUS RESERVATION SYSTEM   |\n";
    cout << "-------------------------------------\n";
}

int findBusIndexByNumber(const string &num){
    for (size_t i = 0; i < buses.size(); ++i)
        if (buses[i].number == num)
            return static_cast<int>(i);
    return -1;
}

void addNewBus(){
    Bus b;
    cout << "\nAdding new bus:\n";
    b.setBasicInfo();
    buses.push_back(move(b));
    cout << "New Bus Added Successfully.\n";
}

void makeReservation(){
    if (buses.empty())
    {
        cout << "No buses available. Add a bus first.\n";
        return;
    }
    string num;
    cout << "Enter Bus Number: ";
    getline(cin, num);
    int idx = findBusIndexByNumber(num);
    if (idx == -1)
    {
        cout << "Bus not found.\n";
        return;
    }
    Bus &b = buses[idx];
    cout << "Available empty seats: " << b.emptyCount() << "\n";
    int seat;
    cout << "Enter Seat Number (1-32): ";
    if (!(cin >> seat))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid seat input.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume endline
    if (seat < 1 || seat > 32)
    {
        cout << "Invalid seat number.\n";
        return;
    }
    if (b.seats[(seat - 1) / 4][(seat - 1) % 4] != "Empty")
    {
        cout << "Seat already reserved.\n";
        return;
    }
    cout << "Enter Passenger's Name: ";
    string pname;
    getline(cin, pname);
    if (pname.empty())
    {
        cout << "Passenger name cannot be empty.\n";
        return;
    }
    if (b.reserveSeat(seat, pname))
    {
        cout << "Seat reserved successfully.\n";
    }
    else
    {
        cout << "Failed to reserve seat.\n";
    }
}

void showReservation(){
    if (buses.empty())
    {
        cout << "No buses available.\n";
        return;
    }
    cout << "Enter Bus Number: ";
    string num;
    getline(cin, num);
    int idx = findBusIndexByNumber(num);
    if (idx == -1)
    {
        cout << "Bus not found.\n";
        return;
    }
    buses[idx].showReservations();
    cout << "Empty seats: " << buses[idx].emptyCount() << "\n";
}

void listAvailableBuses()
{
    if (buses.empty())
    {
        cout << "No buses available.\n";
        return;
    }
    for (size_t i = 0; i < buses.size(); ++i)
    {
        cout << "\n-----------------------------\n";
        cout << "Bus #" << (i + 1) << "\n";
        cout << "Number: " << buses[i].number << "\n";
        cout << "Driver: " << buses[i].driver << "\n";
        cout << "Arrival: " << buses[i].arrival << "  Departure: " << buses[i].depart << "\n";
        cout << "From: " << buses[i].from << "  To: " << buses[i].to << "\n";
        cout << "Empty seats: " << buses[i].emptyCount() << "\n";
    }
    cout << "\n";
}

int main()
{
    while (true)
    {
        printHeader();
        cout << "1. Add New Bus\n2. Reservation\n3. Show Reservation\n4. Buses Available\n5. Exit\n";
        cout << "Enter your Choice: ";
        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume newline
        switch (choice)
        {
        case 1:
            addNewBus();
            pauseForEnter();
            break;
        case 2:
            makeReservation();
            pauseForEnter();
            break;
        case 3:
            showReservation();
            pauseForEnter();
            break;
        case 4:
            listAvailableBuses();
            pauseForEnter();
            break;
        case 5:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

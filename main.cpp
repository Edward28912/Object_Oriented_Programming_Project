#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // FOR SETPRECISION
#include <cstdlib> // FOR RAND()

using namespace std;

int orderReturnAmount = 0;

//AIRPLANE CLASS
class Airplane {
public:
    int seats;
    string name;
    Airplane(); // IMPLICIT CONSTRUCTOR
    Airplane(int u_seats, string u_name); // PARAMETRIZED CONSTRUCTOR
};

//DEFINING IMPLICIT CONSTRUCTOR
Airplane::Airplane() {
    seats = 100;
    name = "WizzAir Aircraft";
}

//DEFINING PARAMETRIZED CONSTRUCTOR
Airplane::Airplane(int u_seats, string u_name) {
    name = u_name;
    seats = u_seats;
}

//SEAT CLASS
class Seat:public Airplane {
public:
    float price;
    float business;
    float economy;
    int economySeats;
    int businessSeats;

    void set_business(float u_price);
    void set_economy(float u_price);

    Seat(); //IMPLICIT CONSTRUCTOR
};

//DEFINING 'SET_BUSINESS' 
void Seat::set_business(float u_price) {
    business = u_price;
}

//DEFINING 'SET_ECONOMY'
void Seat::set_economy(float u_price) {
    economy = u_price;
}

//DEFINING IMPLICIT CONSTRUCTOR
Seat::Seat() {
    business=0;
    economy=0;
    economySeats= 80 - rand() % 80;
    businessSeats= 20 - rand() % 20; // 0
}

//CITY CLASS
class City {
public:
    float distance;
    string name;
    string cardinalPoint;
    City(); // IMPLICIT CONSTRUCTOR
    City(float u_distance, string u_name, string u_cardinalPoint); //PARAMETRIZED CONSTRUCTOR
};

//DEFINING PARAMETRIZED CONSTRUCTOR
City::City(float u_distance, string u_name, string u_cardinalPoint) {
    distance = u_distance;
    name = u_name;
    cardinalPoint = u_cardinalPoint;
}

//CUSTOMER CLASS
class Customer {
private:
    int id;
public:
    float balance;
    string name;

    Customer(float u_balance, int u_id, string u_name); //PARAMETRIZED CONSTRUCTOR

    void order(Customer& customer); //FUNCTION TO ORDER FOOD/DRINKS

    int getID() const;
};

//DEFINING PARAMETRIZED CONSTRUCTOR
Customer::Customer(float u_balance, int u_id, string u_name) {
    balance = u_balance;
    id=u_id;
    name=u_name;
}

int Customer::getID() const  {
    return id;
}

void Customer::order(Customer& customer) {

    string customerChoice;
    string itemChoice;

    vector<string> items = {
            "Sandwich",
            "Soup",
            "Pasta",
            "Water",
            "Beer",
            "Wine",
            "Sushi"
    };

    cout << "Would you like to order any food/drinks?[Y/N]" << endl;
    cin >> customerChoice;

    if (customerChoice == "N")
        cout << "Enjoy your flight. " << endl;

    if (customerChoice == "Y") {
        cout << "This is the list of available food/drinks." << endl;
        for (int i = 0; i < items.size(); i++)
            cout << items[i] << endl;
        cout << "Choose one of the options above: " << endl;
        cin >> itemChoice;
        for (int i = 0; i < items.size(); i++)
            if (itemChoice == items[i]) {
                if (customer.balance < 10)
                    cout << "You don't have enough money. Enjoy your flight. " << endl;
                else {
                    cout << "You have ordered " << items[i] << "." << endl;
                    balance -= 10; // ALL ITEMS HAVE A PREDEFINED PRICE OF 10.
                    cout << "Your new balance is " << customer.balance << "EUR. Enjoy your flight." << endl;
                    orderReturnAmount=10;
                }
            }

    }
}

class customerDatabase {
private:
    vector<Customer> customers; // VECTOR USED FOR STORING CLIENTS

public:
    void addCustomer(const Customer& customer); // ADD CLIENTS
    Customer* searchCustomerByID(int id); // SEARCH CLIENT BY ID
};

void customerDatabase::addCustomer(const Customer& customer) {
    customers.push_back(customer);
}

Customer* customerDatabase::searchCustomerByID(int id) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getID() == id) {
            return &customers[i];
        }
    }
    return nullptr; // CLIENT NOT FOUND
}


vector<City> showRemaining; //VECTOR USED TO STORE REMAINING CITIES

void showCityDirection(string point) {
    City city[26] = {
			//LIST OF CITIES SHOWING THEIR DISTANCE WITH RESPECT TO ROMANIA, THEIR CAPITAL, AND THEIR CARDINAL POINT WITH RESPECT TO EUROPE
            City(1216, "Germany", "W"),
            City(944, "Poland", "E"),
            City(1751, "Finland", "N"),
            City(855, "Austria", "W"),
            City(1769, "Belgium", "W"),
            City(295, "Bulgaria", "E"),
            City(808, "Croatia", "S"),
            City(1201, "Cyprus", "E"),
            City(10372, "Czechia", "E"),
            City(1573, "Denmark", "N"),
            City(1671, "Estonia", "N"),
            City(1869, "France", "W"),
            City(745, "Greece", "S"),
            City(642, "Hungary", "E"),
            City(2537, "Ireland", "N"),
            City(1137, "Italy", "S"),
            City(1398, "Latvia", "N"),
            City(1141, "Lithuania", "N"),
            City(1613, "Louxembourg", "W"),
            City(1365, "Malta", "S"),
            City(1787, "Netherlands", "W"),
            City(2975, "Portugal", "S"),
            City(804, "Slovakia", "E"),
            City(924, "Slovenia", "S"),
            City(2472, "Spain", "S"),
            City(1742, "Sweden", "N")

    };

    for (int i = 0; i <= 26; i++)
        if (city[i].cardinalPoint == point) {
            cout << city[i].name << endl;
            showRemaining.push_back(city[i]); //ADD THE CITY WITH THE SAME CARDINAL POINT TO THE VECTOR
        }
}
//FUNCTION THAT SHOWS DETAILS OF THE CHOSEN CITY
float showCityDetails(string option, Customer& customer) {
    float sum=0;
    int speed=925; // KM per H
    for (int i = 0; i < showRemaining.size(); i++)
        if (showRemaining[i].name == option)
        {
            //CALCULATING TRIP DURATION IN HOURS & MINUTES.
            double durationInHours = showRemaining[i].distance/speed;
            int durationInMinutes = (durationInHours - (int)durationInHours)*60;

            cout << showRemaining[i].distance << " km until the destination.\n";
            if ((int)durationInHours == 1) {
                if (durationInMinutes == 1)
                    cout << "Estimated time until arrival will be: " << (int)durationInHours << " hour and " << durationInMinutes<< " minute." << endl;
                else
                    cout << "Estimated time until arrival will be: " << (int)durationInHours << " hour and " << durationInMinutes<< " minutes." << endl;
            }
            else if ((int)durationInHours == 0)
            {
                if (durationInMinutes == 1)
                    cout << "Estimated time until arrival will be: " << durationInMinutes << " minute." << endl;
                else
                    cout << "Estimated time until arrival will be: " << durationInMinutes << " minutes." << endl;
            }
            else if (durationInMinutes == 1)
                cout << "Estimated time until arrival will be: " << (int)durationInHours << " hours and " << durationInMinutes << " minute." << endl;
            else
                cout << "Estimated time until arrival will be: " << (int)durationInHours << " hours and " << durationInMinutes << " minutes." << endl;
            cout << "Your total balance is: " << customer.balance << "EUR. " << endl;
            cout << "Price for flying at Economy Class: " << showRemaining[i].distance * 0.45 << "EUR " << endl;
            cout << "Price for flying at Business Class: " << showRemaining[i].distance * 0.50 << "EUR " << endl;
            return sum=showRemaining[i].distance * 0.95;
            break;
        }

}

//FUNCTION THAT REMOVES A CLIENT'S BOOKING, RETURNING TICKET MONEY + FOOD/DRINKS(if ordered)
void removeBooking(Customer& customer, Seat& seat, string classOption) {
    if (classOption == "Business") {
        if (seat.businessSeats > 0) {
            seat.businessSeats++;
            customer.balance += seat.business;
            cout <<"Your booking has been removed from Business Class.\n";
            if (orderReturnAmount == 10)
                cout << "Your new balance is: " << customer.balance + 10 << "EUR.\n";
            else
                cout << "Your new balance is: " << customer.balance << "EUR.\n";
        } else
            cout << "No available booking found in Business Class.\n";
    } else if (classOption == "Economy") {
        if (seat.economySeats > 0) {
            seat.economySeats++;
            customer.balance += seat.economy;
            cout <<"Your booking has been removed from Economy Class.\n";
            if (orderReturnAmount == 10)
                cout << "Your new balance is: " << customer.balance + 10 << "EUR.\n";
            else
                cout << "Your new balance is: " << customer.balance << "EUR.\n";
        } else
            cout << "No available booking found in Economy Class.\n";
    } else
        cout << "No flight has been booked.\n";
}

int main() {
    customerDatabase database;
    string direction;
    string travelOption;
    string classOption;
    Customer customer1(872.00, 5, "Valeriu");
    database.addCustomer(customer1);
    int searchID;
    Seat seat1;
    while (true) {
        cout << "=========================="<< endl;
        cout << "WizzAir Reservation System" << endl;
        cout << "==========================" << endl;
        cout << "1. Search customer by ID." << endl;
        cout << "2. Book a flight." << endl;
        cout << "3. Remove booking." << endl;
        cout << "4. Exit." << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter customer ID to search: ";
            cin >> searchID;
            Customer* foundCustomer = database.searchCustomerByID(searchID);
            if (foundCustomer != nullptr)
                cout << "Customer found, name: " << foundCustomer->name << ", ID:" << foundCustomer->getID() << endl;
            else
                cout << "Customer not found!" << endl;
        } else if (choice == 2) {

            int i = 0;
            do {
                if (i != 0)
                    cout << "You have " << 3 - i << " more attempts remaining." << endl;
                cout << "Welcome to Henri Coanda Airport, Bucharest! Which part of Europe would you like to visit?[N/S/E/W]" << endl;
                cin >> direction;
                i++;
                if (direction == "N" || direction == "S" || direction == "E" || direction == "W") {
                    showCityDirection(direction);
                    cout << "Choose one of the options above: " << endl;
                    cin >> travelOption;
                    seat1.set_business(showCityDetails(travelOption, customer1) / 1.9);
                    seat1.set_economy(seat1.business * 0.9);
                    cout << "Choose the preferred class." << endl;
                    cin >> classOption;
                    if (classOption == "Business") {
                        if (seat1.businessSeats == 0) {
                            cout << "We do not have any available seats." << endl;
                            if (seat1.economySeats != 0)
                                cout << "We have available seats at Economy Class. Do you want to try? [Y/N]" << endl;
                            cin >> classOption;
                            if (classOption == "Y") {
                                if (customer1.balance >= seat1.economy) {
                                    cout << setprecision(4) << "Welcome to WizzAir Aircraft." << endl;
                                    cout << "Your new balance, after taxes, is: " << customer1.balance - seat1.economy << "EUR." << endl;
                                    customer1.balance -= seat1.economy;
                                    customer1.order(customer1);
                                    break;
                                } else if (customer1.balance < seat1.economy)
                                    cout << "You do not have enough money for any of our classes." << endl;
                            } else if (classOption == "N"){
                                cout << "Have a great day!" << endl;
                                break;}
                        } else if (customer1.balance < seat1.business && customer1.balance < seat1.economy)
                            cout << "You cannot afford any of our classes." << endl;
                        else if (customer1.balance < seat1.business && customer1.balance >= seat1.economy){
                            cout<<"You cannot afford Business class, but we recommend you our Economy class. Do you want to try? [Y/N]" << endl;
                            cin >> classOption;
                            if (classOption == "N")
                                cout << "Have a great day!";
                            else if (classOption == "Y") {
                                cout << "Welcome to WizzAir Aircraft." << endl;
                                cout << "Your new balance, after taxes, is: " << customer1.balance - seat1.economy << "EUR. " << endl;
                                customer1.balance -= seat1.economy;
                                customer1.order(customer1);
                                break;
                            }
                        }
                        else if (customer1.balance >= seat1.business) {
                            cout << setprecision(4) << "Welcome to WizzAir Aircraft." << endl;
                            cout << "Your new balance, after taxes, is: " << customer1.balance - seat1.business << "EUR." << endl;
                            customer1.balance -= seat1.business;
                            customer1.order(customer1);
                            break;
                        }
                    } else if (classOption == "Economy") {
                        if (seat1.economySeats == 0) {
                            cout << "We do not have any available seats." << endl;
                            if (seat1.businessSeats != 0)
                                cout << "We have available seats at Business Class. Do you want to try? [Y/N]" << endl;
                            cin >> classOption;
                            if (classOption == "Y") {
                                if (customer1.balance >= seat1.business) {
                                    cout << setprecision(4) << "Welcome to WizzAir Aircraft." << endl;
                                    cout << "Your new balance, after taxes, is: " << customer1.balance - seat1.business << "EUR." << endl;
                                    customer1.balance -= seat1.business;
                                    customer1.order(customer1);
                                    break;
                                } else if (customer1.balance < seat1.business)
                                    cout << "You do not have enough money for any of our classes." << endl;
                            } else if (classOption == "N")
                                cout << "Have a great day!" << endl;
                        } else if (customer1.balance < seat1.economy && customer1.balance < seat1.business)
                            cout << "You cannot afford any of our classes." << endl;
                        else if (customer1.balance >= seat1.economy) {
                            cout << setprecision(4) << "Welcome to WizzAir Aircraft." << endl;
                            cout << "Your new balance, after taxes, is: " << customer1.balance - seat1.economy << "EUR." << endl;
                            customer1.balance -= seat1.economy;
                            customer1.order(customer1);
                            break;
                        }
                    }
                }
            } while (i <= 3 );
        }
        else if (choice == 3)
            removeBooking(customer1, seat1, classOption);

        else if (choice == 4) {
            cout << "Goodbye :)";
            break;
        }
    }
    return 0;
}
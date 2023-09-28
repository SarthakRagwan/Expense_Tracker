
#include <bits/stdc++.h>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
using namespace std;
#define expense_vector map<string, vector<int>> &expenses_categories
#define frd "\t\t----------" <<
#define f "----------" <<
#define bkd << "----------"
#define ds "\t\t\t\t" <<
#define de endl << endl
#define line cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl \
                  << endl;

#include <bits/stdc++.h>
using namespace std;
string username;
class Methods
{
public:
    string matching_category(string category)
    {
        string matched_category = "";
        for (int i = 0; i < category.length(); i++)
        {
            matched_category += tolower(category[i]);
        }
        matched_category[0] = category[0] - 32;
        return matched_category;
    }
    int int_length(int num)
    {
        int count = 1;
        while (num)
        {
            num /= 10;
            count++;
        }
        return count;
    }
    string fd(int n)
    {
        string s = "\t\t\t\t";
        for (int i = 0; i < n; i++)
        {
            s += "-";
        }
        return s;
    }
    string bd(int n)
    {
        string s = "";
        for (int i = 0; i < n; i++)
        {
            s += "-";
        }
        return s;
    }
    string date()
    {
        time_t now = time(0);
        string date_time = ctime(&now);
        return date_time;
    }
    string space(int n)
    {
        string s = "";
        for (int i = 0; i < n; i++)
            s += " ";
        return s;
    }
} methods;

class IO : public Methods
{
private:
    vector<string> expenses_categories =
        {"Housing", "Transportation", "Food", "Utilities", "Insurance ", "Medical/healthcare", "Saving", "Investing", "Debt_payments", "Personal_spending", "Entertainment", "Miscellaneous"};
    // multimap<string, pair<int, string>> history;
    int expense_sum;
    multimap<string, float> history;

public:
    void expense_history()
    {
        if (history.size())
        {
            for (auto expense : history)
            {
                cout << "\t\t\t" << expense.first << space(30 - expense.first.length()) << "₹" << expense.second << endl
                     << endl;
            }
        }
        else
            cout << "\t\t\tNo history till now" << endl
                 << endl;
    }
    string user_database(string entity)
    {
        string base = "./database/" + username + "/" + entity + ".txt";
        return base;
    }
    void categories()
    {
        fstream data, data1;
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        bool flag = true;
        data.open(user_database("expense"), ios::in);
        if (!data)
            cout << "\t\t\t\t"
                 << "No expenses till now !" << endl
                 << endl;
        else
        {
            data >> data_expense >> data_expense_value >> data_expense_per;
            int i = 1;
            while (!data.eof())
            {
                cout << "\t\t\t\t" << i << "." << data_expense << endl;
                i++;
                data >> data_expense >> data_expense_value >> data_expense_per;
            }
            cout << endl;
        }
    }
    float total_expense(float expense)
    {
        fstream data, data1;
        data.open(user_database("total_expense"), ios::in);
        if (!data)
        {
            data.open(user_database("total_expense"), ios::app | ios::out);
            data << " " << expense << endl;
            data.close();
            return expense;
        }
        else
        {
            data1.open(user_database("total_expense1"), ios::app | ios::out);
            float total;
            data >> total;
            data1 << " " << total + expense;
            data.close();
            data1.close();
            remove(user_database("total_expense").c_str());
            rename(user_database("total_expense1").c_str(), user_database("total_expense").c_str());
            return total + expense;
        }
    }
    void input_per(float expense_sum)
    {
        fstream data, data1;
        data.open(user_database("expense"), ios::in);
        data1.open(user_database("expense1"), ios::app | ios::out);
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        data >> data_expense >> data_expense_value >> data_expense_per;
        while (!data.eof())
        {
            float per = (float(data_expense_value / expense_sum)) * 100;
            data1 << " " << data_expense << space(30 - data_expense.length()) << data_expense_value << space(15 - int_length(data_expense_value)) << per << endl;
            data >> data_expense >> data_expense_value >> data_expense_per;
        }
        data.close();
        data1.close();
        remove(user_database("expense").c_str());
        rename(user_database("expense1").c_str(), user_database("expense").c_str());
    }
    void input_expense(string expense_type)
    {
        bool flag = true;
        fstream data, data1;
        string data_expense;
        float data_expense_value;
        float data_expense_per;

        float expense = 0;
        data.open(user_database("expense"), ios::in);
        if (!data)
        {
            data.open(user_database("expense"), ios::app | ios::out);
            for (auto category : expenses_categories)
            {
                if (category == expense_type)
                {
                    cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";

                    while(!(cin >> expense))
                    {
                        cout << endl
                         << "\tEnter expense value spent on " << expense_type << "): ";
                         cin.clear();
                         cin.ignore(123,'\n');
                    }
                    expense_sum = total_expense(expense);
                    data << " " << category << " " << expense << " "
                         << "100" << endl;
                    history.insert({expense_type, expense});
                    flag = false;
                }
                else
                {
                    data << " " << category << " "
                         << "0"
                         << " "
                         << "0" << endl;
                }
            }

            if (flag)
            {
                cout << endl
                     << ds "No such category ! would you like to add new category ?(1) : ";
                string s;
                cin >> s;
                if (s == "1")
                {
                    cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";
                    while(!(cin >> expense))
                    {
                        cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";
                         cin.clear();
                         cin.ignore(123,'\n');
                    }
                    expense_sum = total_expense(expense);
                    data << " " << expense_type << " " << expense << " "
                         << "100" << endl;
                    history.insert({expense_type, expense});
                }
            }
            if (expense)
                cout << endl
                     << ds "Expense of ₹" << expense << " on " << expense_type << " added successfully." << de;
            else
                cout << endl
                     << ds "Try again !" << de;
            data.close();
        }

        else
        {
            data1.open(user_database("expense1"), ios::app | ios::out);
            data >> data_expense >> data_expense_value >> data_expense_per;
            while (!data.eof())
            {
                if (data_expense == expense_type)
                {
                    cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";
                    while(!(cin >> expense))
                    {
                        cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";
                         cin.clear();
                         cin.ignore(123,'\n');
                    }
                    expense_sum = total_expense(expense);
                    flag = false;
                    data1 << " " << data_expense << space(30 - data_expense.length()) << data_expense_value + expense << space(15 - int_length(data_expense_value + expense)) << data_expense_per << endl;
                    history.insert({expense_type, expense});
                }
                else
                {
                    data1 << " " << data_expense << space(30 - data_expense.length()) << data_expense_value << space(15 - int_length(data_expense_value)) << data_expense_per << endl;
                }
                data >> data_expense >> data_expense_value >> data_expense_per;
            }

            if (flag)
            {
                cout << endl
                     << ds "No such category ! would you like to add new category ?(1) : ";
                string s;
                cin >> s;
                if (s == "1")
                {

                    cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";
                    while(!(cin >> expense))
                    {
                        cout << endl
                         << "\tEnter expense value spent on " << expense_type << " : ";
                         cin.clear();
                         cin.ignore(123,'\n');
                    }
                    expense_sum = total_expense(expense);
                    history.insert({expense_type, expense});
                    data1 << " " << expense_type << space(30 - expense_type.length()) << expense << space(15 - int_length(expense)) << "0" << endl;
                }
            }
            data.close();
            data1.close();
            remove(user_database("expense").c_str());
            rename(user_database("expense1").c_str(), user_database("expense").c_str());
            if (expense)
            {
                input_per(expense_sum);
                cout << endl
                     << ds "Expense of ₹" << expense << " on " << expense_type << " added successfully." << de;
            }
            else
                cout << endl
                     << ds "Try again !" << de;
        }
    }
    void read_expense()
    {
        fstream data;
        data.open(user_database("expense"), ios::in);
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        string l;
        data >> data_expense >> data_expense_value >> data_expense_per;
        while (!data.eof())
        {
            cout << "\t\t\t" << data_expense << space(30 - data_expense.length()) << "₹" << data_expense_value << space(20 - int_length(data_expense_value)) << data_expense_per << "%" << endl;

            data >> data_expense >> data_expense_value >> data_expense_per;
            // getline(data, l);
            // cout << "\t\t\t" << l << endl;
        }
        data.close();
    }
    void del_expense(string category)
    {
        fstream data, data1;
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        bool flag = true;
        data.open(user_database("expense"), ios::in);
        if (!data)
            cout << "No expenses till now !" << endl;
        else
        {
            while (!data.eof())
            {
                if (data_expense == category)
                {
                    flag = false;
                    break;
                }
                data >> data_expense >> data_expense_value >> data_expense_per;
            }
            data.close();
            if (flag)
                cout << endl
                     << "\t\t\t\t"
                     << "No such category !" << endl;
            else
            {
                string s;
                cout << endl
                     << ds "Are you sure you want to delete " << category << " ? (1) : ";
                cin >> s;
                if (s == "1")
                {
                    expense_sum = total_expense((-1) * data_expense_value);
                    if (!expense_sum)
                        expense_sum = 1;
                    data1.open(user_database("expense1"), ios::app | ios::out);
                    data.open(user_database("expense"), ios::in);
                    data >> data_expense >> data_expense_value >> data_expense_per;
                    while (!data.eof())
                    {
                        if (data_expense != category)
                        {
                            float per = (float((data_expense_value) / expense_sum)) * 100;
                            data1 << " " << data_expense << space(30 - data_expense.length()) << data_expense_value << space(20 - int_length(data_expense_value)) << per << endl;
                        }
                        data >> data_expense >> data_expense_value >> data_expense_per;
                    }
                    cout << endl
                         << ds category << " expense"
                         << " deleted successfully." << endl;
                    data.close();
                    data1.close();
                    remove(user_database("expense").c_str());
                    rename(user_database("expense1").c_str(), user_database("expense").c_str());
                }
                else
                {
                    cout << endl
                         << ds "Try again !" << endl;
                }
            }
        }
    }
    void edit_input(string category)
    {
        fstream data, data1;
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        bool flag = true;
        data.open(user_database("expense"), ios::in);
        float expense = 0;
        if (!data)
            cout << "\t\t\t\t"
                 << "No expenses till now !" << endl;
        else
        {
            data >> data_expense >> data_expense_value >> data_expense_per;
            while (!data.eof())
            {
                if (data_expense == category)
                {
                    flag = false;
                    break;
                }
                data >> data_expense >> data_expense_value >> data_expense_per;
            }
            data.close();
            if (flag)
                cout << endl
                     << "\t\t\t\t"
                     << "No such category ! Try again !" << endl
                     << endl;
            else
            {
                cout << endl
                     << "\t" << category << " has expense value of " << data_expense_value << endl;
                string s;
                cout << endl
                     << ds "Are you sure you want to edit " << category << " ? (1) : ";
                cin >> s;
                if (s == "1")
                {
                    expense_sum = total_expense((-1) * data_expense_value);
                    if (!expense_sum)
                        expense_sum = 1;
                    data1.open(user_database("expense1"), ios::app | ios::out);
                    data.open(user_database("expense"), ios::in);
                    data >> data_expense >> data_expense_value >> data_expense_per;
                    while (!data.eof())
                    {
                        if (data_expense == category)
                        {
                            cout << endl
                                 << "\tEnter new expense value of " << category << " : ";
                            cin >> expense;
                            expense_sum = total_expense(expense);
                            float per = (float((data_expense_value) / expense_sum)) * 100;
                            data1 << " " << data_expense << space(30 - data_expense.length()) << expense << space(20 - int_length(data_expense_value)) << per << endl;
                        }
                        else
                        {
                            float per = (float((data_expense_value) / expense_sum)) * 100;
                            data1 << " " << data_expense << space(30 - data_expense.length()) << data_expense_value << space(20 - int_length(data_expense_value)) << per << endl;
                        }
                        data >> data_expense >> data_expense_value >> data_expense_per;
                    }
                    cout << endl
                         << ds category << " expense"
                         << " edited to " << expense << " successfully." << endl
                         << endl;
                    data.close();
                    data1.close();
                    remove(user_database("expense").c_str());
                    rename(user_database("expense1").c_str(), user_database("expense").c_str());
                    input_per(expense_sum);
                }
                else
                {
                    cout << endl
                         << ds "Try again !" << endl
                         << endl;
                }
            }
        }
    }
    void input_particular(string category)
    {
        fstream data;
        data.open(user_database("expense"), ios::in);
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        bool flag = true;
        if (!data)
            cout << endl
                 << "\t\t\t\t"
                 << "No expenses till now" << endl
                 << endl;
        else
        {
            data >> data_expense >> data_expense_value >> data_expense_per;
            while (!data.eof())
            {
                if (data_expense == category)
                {
                    flag = false;
                    cout << endl
                         << "\t"
                         << "Total expense on " << category << " is " << data_expense_value << " which is " << data_expense_per << "% of total expenses" << endl
                         << endl;
                    break;
                }
                data >> data_expense >> data_expense_value >> data_expense_per;
            }
            data.close();
        }
        if (flag)
            cout << endl
                 << "\t\t\t\t"
                 << "No such category !" << endl
                 << endl;
    }
    void input_max()
    {
        fstream data;
        data.open(user_database("expense"), ios::in);
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        float max_expense = 0;
        string category;
        float percentage;
        while (!data.eof())
        {
            data >> data_expense >> data_expense_value >> data_expense_per;
            if (data_expense_value > max_expense)
            {
                category = data_expense;
                max_expense = data_expense_value;
                percentage = data_expense_per;
            }
        }
        if (max_expense)
            cout
                << "\t"
                << "Maximum expensse is incurd on " << category << " of ₹" << max_expense << " which is " << percentage << "% of total expense" << endl
                << endl;
        else
            cout
                << "\t"
                << "No expense till now" << endl
                << endl;
    }
    void input_min()
    {
        fstream data;
        data.open(user_database("expense"), ios::in);
        string data_expense;
        float data_expense_value;
        float data_expense_per;
        float min_expense = INT_MAX;
        string category;
        float percentage;
        while (!data.eof())
        {
            data >> data_expense >> data_expense_value >> data_expense_per;
            if (data_expense_value < min_expense && data_expense_value != 0)
            {
                category = data_expense;
                min_expense = data_expense_value;
                percentage = data_expense_per;
            }
        }
        if (min_expense == 0)
            cout
                << "\t"
                << "No expense till now" << endl
                << endl;
        else
            cout
                << "\t"
                << "Minimum expense is incurd on " << category << " of ₹" << min_expense << " which is " << percentage << "% of total expense" << endl
                << endl;
    }
};

class Expense : public IO
{
public:
    void total_expenses()
    {
        options();
        cout << "\tTotal expenses : ₹" << total_expense(0) << de;
        line
    }
    void print_expenses()
    {
        options();
        cout << "-----------------------------------------------------------Expenses----------------------------------------------------------------------" << de;
        read_expense();
        cout << endl;
        line
    }

    void adding_expense()
    {
        cout << "--------------------------------------------------------Adding Expenses------------------------------------------------------------------" << endl;

        cout << endl
             << ds "Enter 0 in expense category anytime to stop adding expense" << de;
        categories();
        line while (1)
        {
            string expense_type;
            cout << "\tEnter expense Category : ";
            cin >> expense_type;
            if (expense_type == "0")
            {
                system("cls");
                break;
            }
            expense_type = matching_category(expense_type);
            input_expense(expense_type);
        }
    }
    void delete_expense()
    {
        cout << "-------------------------------------------------------Deleting Expenses-----------------------------------------------------------------" << endl;

        string n;
        cout << endl
             << ds "Enter 0 in expense category anytime to stop deleting expense" << endl;
        categories();
        line while (1)
        {
            string category;
            cout << endl
                 << "\tEnter category to delete : ";
            cin >> category;
            if (category == "0")
            {
                system("cls");
                break;
            }
            category = matching_category(category);
            del_expense(category);
        }
    }
    void edit_expense()
    {
        cout << "--------------------------------------------------------Editing Expenses-----------------------------------------------------------------" << endl;

        cout << endl
             << ds "Enter 0 in expense category anytime to stop editing expense" << de;
        categories();
        line while (1)
        {
            string category;
            cout << "\tEnter the expense category to edit : ";
            cin >> category;
            if (category == "0")
            {
                system("cls");
                break;
            }
            category = matching_category(category);
            edit_input(category);
        }
    }
    void particular_expense()
    {
        cout << "-------------------------------------------------------Particuar Expense-----------------------------------------------------------------" << endl;

        string category;
        cout << endl
             << ds "Enter 0 in expense category anytime to return to main menu" << de;
        categories();
        line while (1)
        {
            cout << "\tEnter category to know expense : ";
            cin >> category;
            if (category == "0")
            {
                system("cls");
                break;
            }
            category = matching_category(category);
            input_particular(category);
        }
    }
    void most_expense()
    {
        input_max();
        line
    }
    void least_expense()
    {
        input_min();
        line
    }
    void expense_histor()
    {
        cout << "---------------------------------------------------------Expense History-----------------------------------------------------------------" << de;
        expense_history();
        line
    }
    void options()
    {
        cout << endl
             << "--------------------------------------------------------Expense Menu---------------------------------------------------------------------" << endl;
        cout << endl
             << ds "\t1.To Add Expense" << endl;
        cout << ds "\t2.Delete Expense" << endl;
        cout << ds "\t3.Edit Expense" << endl;
        cout << ds "\t4.Total Expense" << endl;
        cout << ds "\t5.Total expense of a paricular category" << endl;
        cout << ds "\t6.Expense history" << endl;
        cout << ds "\t7.Maximum expense category" << endl;
        cout << ds "\t8.Minimum expense category" << endl;
        cout << ds "\t9.To Print Expenses" << endl;
        cout << ds "\t0.To Exit" << endl
             << endl;
        line
    }
    void driver()
    {
        options();
        int choice;
        int n = 1;
        cout << "\tPlease Enter Your Choice : ";
        while (n)
        {
            cin >> choice;
            cout << endl;
            switch (choice)
            {
            case 1:
                system("cls");
                cout << endl;
                adding_expense();
                options();
                break;
            case 2:
                system("cls");
                cout << endl;
                delete_expense();
                options();
                break;
            case 3:
                system("cls");
                cout << endl;
                edit_expense();
                options();
                break;
            case 4:
                system("cls");
                cout << endl;
                total_expenses();
                break;
            case 5:
                system("cls");
                cout << endl;
                particular_expense();
                options();
                break;
            case 6:
                system("cls");
                cout << endl;
                options();
                expense_histor();
                break;
            case 7:
                system("cls");
                cout << endl;
                options();
                most_expense();
                break;
            case 8:
                system("cls");
                cout << endl;
                options();
                least_expense();
                break;
            case 9:
                system("cls");
                cout << endl;
                print_expenses();
                break;
            case 0:
                n = 0;
                system("cls");
                break;
            default:
                system("cls");
                options();
                cout << ds "Invalid option choosen ! please try again ! " << endl<<endl;
                break;
            }
            if (n)
                cout << "\tPlease Enter Your Next Choice : ";
        }
    }
} expense;
class Users : public Methods
{

public:
    creating_database(string username)
    {
        fstream data;
        data.open("database");
        if (!data)
            mkdir("database");
        string newUser = "./database/" + username;
        mkdir(newUser.c_str());
    }
    bool username_avaibality(string username)
    {
        fstream data;
        string u;
        string p;
        data.open("users.txt", ios::in);
        if (!data)
        {
            data.open("users.txt", ios::app | ios::out);
            return true;
        }
        else
        {
            data >> u >> p;
            while (!data.eof())
            {
                if (u == username)
                    return false;
                data >> u >> p;
            }
        }
        return true;
    }
    void login_account(int i = 1)
    {
        if (i)
            system("cls");
        cout << "----------------------------------------------------------User Login---------------------------------------------------------------------" << de;
        string password;
        bool flag = false;
        int chance = 4;
        fstream data;
        string u, p;
        data.open("users.txt", ios::in);
        if (!data)
            cout << "\t\t\t\t"
                 << "No User Till Now " << endl
                 << endl;
        else
        {
            while (chance--)
            {
                if (chance == 0)
                {
                    string s;
                    cout << endl
                         << "\t\t\t\t"
                         << "Attempt to enter user name exceed ! still you want to try ?(1): ";
                    cin >> s;
                    if (s == "1")
                        chance++;
                    else
                    {
                        system("cls");
                        break;
                    }
                }
                cout << endl
                     << "\t\t\t"
                     << "Enter user Name : ";
                cin >> username;
                data >> u >> p;
                while (!data.eof())
                {
                    if (u == username)
                    {
                        break;
                    }
                    data >> u >> p;
                }
                if (u == username)
                {
                    int n = 3;
                    while (n--)
                    {
                        cout << endl
                             << "\t\t\t"
                             << "Enter password : ";
                        cin >> password;
                        if (password == p)
                        {
                            system("cls");
                            cout << endl
                                 << "\t\t\t\t\t\t\t"
                                 << "Welcome " << username << endl
                                 << endl;
                            expense.driver();
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << endl
                                 << "\t\t\t"
                                 << "Wrong password ! please try again !" << endl;
                            cout << endl
                                 << "\t\t\t" << n << " attempts remaining !" << endl
                                 << endl;
                            cout << "\t\t\t"
                                 << "Enter User Name : " << username << endl;
                        }
                    }
                    if (n == -1)
                    {
                        system("cls");
                        cout << endl
                             << "\t\t\t" << username << " ,You exceed Attempt to enter password !" << endl
                             << endl;
                        break;
                    }
                    else
                        break;
                }
                else
                {
                    system("cls");
                    cout << endl
                         << "\t\t\t\t"
                         << "Invalid User Name ! Try Again !" << endl;
                }
            }
        }
    }
    void new_account()
    {
        system("cls");
        cout << "------------------------------------------------------New Account----------------------------------------------------------------" << de;
        while (1)
        {
            string password;
            cout << endl
             << ds "Enter 0 as username to not creat an account" << de;
            cout << endl
                 << "\t\t\t"
                 << "Enter a user Name : ";
            cin >> username;
            if(username=="0"){system("cls");break;}
            if (username_avaibality(username))
            {
                cout << endl
                     << "\t\t\t"
                     << "Enter a password : ";
                cin >> password;
                fstream data, data1;
                string u, p;
                data.open("users.txt", ios::in);
                data1.open("users1.txt", ios::app | ios::out);
                data >> u >> p;
                while (!data.eof())
                {
                    data1 << " " << u << " " << p << endl;
                    data >> u >> p;
                }
                data1 << " " << username << " " << password << endl;
                data.close();
                data1.close();
                remove("users.txt");
                rename("users1.txt", "users.txt");
                creating_database(username);
                system("cls");
                cout << endl
                     << "\t\t\t"
                     << "Account created successfully !" << endl
                     << endl;
                cout << "\t\t\t"
                     << "Please log in to your Account " << endl
                     << endl;
                login_account(0);
                break;
            }
            else
            {
                cout << endl
                     << "\t\t\t"
                     << "User Name already taken ! Please Try another User Name !" << endl;
            }
        }
    }
    void delete_account()
    {
        system("cls");
        cout << "------------------------------------------------------Deleting an Account----------------------------------------------------------------" << de;
        string password;
        bool flag = false;
        int chance = 4;
        fstream data;
        string u, p;
        data.open("users.txt", ios::in);
        if (!data)
            cout << "\t\t\t\t"
                 << "No User Till Now " << endl
                 << endl;
        else
        {
            while (chance--)
            {
                if (chance == 0)
                {
                    string s;
                    cout << endl
                         << "\t\t\t\t"
                         << "Attempt to enter user name exceed !want to try ?(1): ";
                    cin >> s;
                    if (s == "1")
                        chance++;
                    else
                    {
                        system("cls");
                        break;
                    }
                }
                cout << endl
                     << "\t\t\t"
                     << "Enter user Name : ";
                cin >> username;
                data >> u >> p;
                while (!data.eof())
                {
                    if (u == username)
                    {
                        break;
                    }
                    data >> u >> p;
                }
                if (u == username)
                {
                    int n = 3;
                    while (n--)
                    {
                        cout << endl
                             << "\t\t\t"
                             << "Enter password : ";
                        cin >> password;
                        if (password == p)
                        {
                            data.close();
                            system("cls");
                            fstream data1, data2;
                            data1.open("users.txt", ios::in);
                            data2.open("users1.txt", ios::app | ios::out);
                            string s, k;
                            data1 >> s >> k;
                            while (!data1.eof())
                            {
                                if (username != s)
                                {
                                    data2 << " " << s << " " << k << endl;
                                }
                                data1 >> s >> k;
                            }
                            data1.close();
                            data2.close();
                            remove("users.txt");
                            rename("users1.txt", "users.txt");
                            string base = "./database/" + username;
                            string x="./database/" + username + "/expense.txt";
                            string y="./database/" + username + "/total_expense.txt";
                            remove(x.c_str());
                            remove(y.c_str());
                            rmdir(base.c_str());
                            cout << endl
                                 << "\t\t\t\t\t\t"
                                 << "Account deleted successfullly " << endl
                                 << endl;
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << endl
                                 << "\t\t\t"
                                 << "Wrong password ! please try again !" << endl;
                            cout << endl
                                 << "\t\t\t" << n << " attempts remaining !" << endl
                                 << endl;
                            cout << "\t\t\t"
                                 << "Enter User Name : " << username << endl;
                        }
                    }
                    if (n == -1)
                    {
                        system("cls");
                        cout << endl
                             << "\t\t\t" << username << " ,You exceed Attempt to enter password exceed !" << endl
                             << endl;
                        break;
                    }
                    else
                        break;
                }
                else
                {
                    system("cls");
                    cout << endl
                         << "\t\t\t\t"
                         << "Invalid User Name ! Try Again !" << endl;
                }
            }
        }
    }
    void driver()
    {
        while (1)
        {
            cout << "------------------------------------------------------User Authentication----------------------------------------------------------------" << de;
            cout << "\t\t\t"
                 << "1.To LogIn in your Existing Account" << endl
                 << endl;
            cout << "\t\t\t"
                 << "2.To Creat a new Account" << endl
                 << endl;
            cout << "\t\t\t"
                 << "3.To Delete an Account" << endl
                 << endl;
            cout << "\t\t\t"
                 << "0.To Exit" << endl
                 << endl;
            string choice;
            cout << "\t"
                 << "Enter your choice : ";
            cin >> choice;
            if (choice == "1")
                login_account();
            else if (choice == "2")
                new_account();
            else if (choice == "3")
                delete_account();
            else if (choice == "0")
            {
                system("cls");
                cout << endl
                     << endl
                     << fd(11) << "ThanYou For Trying Our Advanced Expense Tracker." << bd(10) << endl
                     << endl;
                break;
            }
            else
            {
                system("cls");
                cout << "\t\t\t"
                     << "Invalid Input try again " << endl
                     << endl;
            }
        }
    }
} users;
int main()
{
    users.driver();
}


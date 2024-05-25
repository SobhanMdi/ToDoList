#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

struct task_struct{
    string text;
    string date;
    bool completed;
};

class Task;

void menuNavigate(string input);
void print(vector<task_struct> tasks);
void mainMenu();
int i_input(string str);
void change(vector<task_struct> &tasks, int input);
void change_bool(vector<task_struct> &tasks, int input);
void complete();
void edit();
void remove(vector<task_struct> &tasks);
vector<task_struct> tasks;
string input();

int main(){
    while(true){
        mainMenu();
        menuNavigate(input());
    }
}

class Task{
public:
    string text;
    string date;

    Task(){
        cout << "enter Task: ";
        getline(cin, text);
        cout << "enter date: ";
        getline(cin, date);
        tasks.push_back({text, date, false});

        ofstream file("tasks.txt", ios_base::app);
        if(file.is_open()){
            file << text << "," << date << "," << false << endl;
            file.close();
        } else {
            cout << "Error opening file." << endl;
        }
    }
};

void menuNavigate(string input){
    switch(input[0]){
        case '0':
        {
            system("cls");
            cout << "Thank you for your time\n";
            system("pause");
            exit(0);
        }
        case '1':
        {
            Task task;
            break;
        }
        case '2':
        {
            print(tasks);
            system("pause");
            break;
        }
        case '3':
        {
            complete();
            break;
        }
        case '4':
        {
            edit();
            system("pause");
            break;
        }
        case '5':
        {
            remove(tasks);
            system("pause");
            break;
        }
        default:
        {
            system("cls");
            cout << "ENTER A NUMBER BETWEEN 0 - 5" << '\n';
            system("pause");
            break;
        }
    }
}

string input(){
    string input;
    cout << "\n\n";
    while(true){
        cout << "Enter Your Choice:";
        getline(cin, input);
        if(input.size() != 1){
            continue;
        } else {
            return input;
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

void mainMenu(){
    system("cls");
    cout << R"(
   _________________________________________________
  /                                                 \
 (                     Todo List                     )
  \_________________________________________________/
     
 :::::::::::::::::::: PROGRAM MENU :::::::::::::::::::: 

 1. Add New Task
 2. Display All Tasks
 3. Mark As Complete
 4. Edit Task
 5. Remove Task
 0. Exit)";
}

void print(vector<task_struct> tasks){
    int c = 1;
    for(auto t : tasks){
        cout << c << ". " << t.text << '\t' << t.date;
        if(t.completed){
            cout << "\tCOMPLETED";
        } else {
            cout << "\tNOT COMPLETED";
        }
        cout << '\n';
        c++;
    }
}

int i_input(string str){
    int i_input;
    cout << str;
    cin >> i_input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return i_input;
}

void change_bool(vector<task_struct> &tasks, int input){
    tasks[input-1].completed = true;
}

void complete(){
    int input;
    print(tasks);
    input = i_input("\nwhat task is completed? ");
    while(input > tasks.size() || input < 1){
        input = i_input("\nwhat task is completed? ");
    }
    change_bool(tasks, input);
}

void change(vector<task_struct> &tasks, int input){
    string text;
    string date;
    cout << "enter Task: ";
    getline(cin, text);
    cout << "enter date: ";
    getline(cin, date);
    tasks[input-1].text = text;
    tasks[input-1].date = date;
}
void edit(){
    int inputt;
    print(tasks);
    inputt = i_input("\nwhat task needs edit? ");
    while(inputt > tasks.size() || inputt < 1){
        inputt = i_input("\nwhat task needs edit? ");
    }
    change(tasks, inputt);
}

void remove(vector<task_struct> &tasks){
    int input;
    print(tasks);
    input = i_input("\nwhat task should be deleted? ");
    while(input > tasks.size() || input < 1){
        input = i_input("\nwhat task should be deleted? ");
    }
    tasks.erase(tasks.begin() + input - 1);

    ofstream file("tasks.txt");
    if(file.is_open()){
        for(auto t : tasks){
            file << t.text << "," << t.date << "," << t.completed << endl;
        }
        file.close();
    } else {
        cout << "Error opening file." << endl;
    }
}
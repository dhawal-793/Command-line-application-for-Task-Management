#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

void Help()
{
    cout << "Usage :-\n";
    cout << "$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n";
    cout << "$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order:\n";
    cout << "$ ./task del INDEX            # Delete the incomplete item with the given index\n";
    cout << "$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n";
    cout << "$ ./task help                 # Show usage\n";
    cout << "$ ./task report               # Statistics\n";
}

void List()
{
    ifstream in("task.txt");
    string st;
    while (in.eof() == 0)
    {
        getline(in, st);
        cout << st << "\n";
    }
}
void Report()
{
    ifstream in1("task.txt");
    string st, st1 = "", st2 = "";
    int taskline = 0, compline = 0;
    getline(in1, st);
    if (st != "")
    {
        in1.seekg(0);
        while (in1.eof() == 0)
        {
            ++taskline;
            getline(in1, st);
            st1 += st + "\n";
        }
    }
    cout << "Pending : " << to_string(taskline) << endl
         << st1 << endl;
    ifstream in2("completed.txt");
    getline(in2, st);
    if (st != "")
    {
        in2.seekg(0);
        while (in2.eof() == 0)
        {
            ++compline;
            getline(in2, st);
            st2 += st + "\n";
        }
    }
    cout << "Completed : " << to_string(compline) << endl
         << st2;
}

void Add(int priority, string task_to_do)
{
    string old_val = "", st, st1 = "";
    ifstream in("task.txt");
    getline(in, st);
    int index = 1;
    if (st != "")
    {
        in.seekg(0);
        int next_index = 0;
        bool added = false;
        while (in.eof() == 0)
        {
            getline(in, st);
            if (!added)
            {
                unsigned first = st.find("[");
                unsigned last = st.find("]");
                string old_pr = st.substr(first + 1, last - first - 1);
                int old_priority = 0;
                stringstream x(old_pr);
                x >> old_priority;
                if (old_priority <= priority)
                {
                    st1 += st + "\n";
                    index++;
                    continue;
                }
                else
                {
                    int ind = 0;
                    int last_char = st.find('.');
                    string line_index = st.substr(0, last_char);
                    stringstream z(line_index);
                    z >> ind;
                    st1 = st1 + to_string(ind) + ". " + task_to_do + " [" + to_string(priority) + "]\n";
                    added = true;
                    st = st.substr(last_char);
                    st1 = st1 + to_string(ind + 1) + st + "\n";
                    next_index = ind + 2;
                }
            }
            else
            {
                int pos = st.find('.');
                st = st.substr(pos);
                st1 += to_string(next_index) + st + "\n";
                next_index++;
            }
        }
        ofstream out("task.txt");
        if (added)
        {
            int x = st1.length() - 1;
            st1 = st1.substr(0, x);
            out << st1;
            cout << "Added task: "+task_to_do+" with priority "+to_string(priority);
        }
        else
        {
            st1 += to_string(index) + ". " + task_to_do + " [" + to_string(priority) + "]";
            out << st1;
            cout << "Added task: "+task_to_do+" with priority "+to_string(priority);
        }
    }
    else
    {
        ofstream out("task.txt");
        string val = old_val + to_string(index) + ". " + task_to_do + " [" + to_string(priority) + "]";
        out << val;
    }
}
void Del(int index)
{
    int line_no = 1;
    ifstream in("task.txt");
    string st, st1 = "";
    bool found = false;
    while (in.eof() == 0)
    {
        getline(in, st);
        if (line_no < index)
        {
            st1 += st + "\n";
            line_no++;
        }
        else if (line_no == index)
        {
            found = true;
            line_no++;
        }
        else
        {
            int ind = 0;
            int last_char = st.find('.');
            string line_index = st.substr(0, last_char);
            stringstream z(line_index);
            z >> ind;
            ind -= 1;
            st = st.substr(last_char);
            st1 = st1 + to_string(ind) + st + "\n";
        }
    }
    if (found)
    {
        ofstream out("task.txt");
        int x = st1.length() - 1;
        st1 = st1.substr(0, x);
        out << st1;
        cout << "Deleted item with index " + to_string(index);
    }
    else
        cout << "Error: item with index" + to_string(index) + "does not exist. Nothing deleted.";
}
void Done(int index)
{
    int line_no = 1;
    ifstream in("task.txt");
    string st, st1 = "";
    bool found = false;
    while (in.eof() == 0)
    {
        getline(in, st);
        if (line_no < index)
        {
            st1 += st + "\n";
            line_no++;
        }
        else if (line_no == index)
        {
            int x = st.length() - 7;
            string task = st.substr(3, x);
            ofstream compfile;
            compfile.open("completed.txt", ios_base::app);
            compfile << task;
            found = true;
            line_no++;
        }
        else
        {
            int ind = 0;
            int last_char = st.find('.');
            string line_index = st.substr(0, last_char);
            stringstream z(line_index);
            z >> ind;
            ind -= 1;
            st = st.substr(last_char);
            st1 = st1 + to_string(ind) + st + "\n";
        }
    }
    if (found)
    {
        ofstream out("task.txt");
        int x = st1.length() - 1;
        st1 = st1.substr(0, x);
        out << st1;
        cout << "Marked item as done.";
    }
    else
        cout << "Error: no incomplete item with index " + to_string(index) + " exists.";
}
int main(int argc, char *argv[])
{
    if (argc < 2)
        Help();
    else
    {
        string work = argv[1];
        if (argc == 2)
        {
            if (work == "help")
                Help();
            else if (work == "report")
                Report();
            else if (work == "ls")
                List();
        }
        else if (argc == 3)
        {
            int index = 0;
            string ind = (argv[2]);
            stringstream x(ind);
            x >> index;
            if (work == "del")
                Del(index);
            else if (work == "done")
                Done(index);
        }
        else
        {
            int priority = 0;
            string pr = (argv[2]);
            stringstream x(pr);
            x >> priority;
            string task_to_do = argv[3];
            Add(priority, task_to_do);
        }
    }
    return 0;
}
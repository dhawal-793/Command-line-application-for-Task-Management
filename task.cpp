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
    ifstream in;
    in.open("task.txt");
    string st;
    getline(in, st);
    if (st == "")
        cout << "There are no pending tasks!" << endl;
    else
    {
        cout << st << "\n";
        while (in.eof() == 0)
        {
            getline(in, st);
            cout << st << "\n";
        }
    }
    in.close();
}
void Report()
{
    ifstream in1, in2;
    in1.open("task.txt");
    in2.open("completed.txt");
    string str1, str2, st1 = "", st2 = "";
    int taskline = 0, compline = 0;
    getline(in1, str1);
    if (str1 != "")
    {
        in1.seekg(0);
        while (in1.eof() == 0)
        {
            ++taskline;
            getline(in1, str1);
            st1 += str1 + "\n";
        }
    }
    cout << "Pending : " << to_string(taskline) << endl
         << st1 << endl;
    in1.close();
    getline(in2, str2);
    if (str2 != "")
    {
        in2.seekg(0);
        while (in2.eof() == 0)
        {
            ++compline;
            getline(in2, str2);
            st2 += str2 + "\n";
        }
    }
    cout << "Completed : " << to_string(compline) << endl
         << st2 << endl;
    in2.close();
}

void Add(int priority, string task_to_do)
{
    string old_val = "", st, st1 = "";
    ifstream in;
    in.open("task.txt");
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
        ofstream out;
        out.open("task.txt");
        if (added)
        {
            int x = st1.length() - 1;
            st1 = st1.substr(0, x);
            out << st1;
            cout << "Added task: \"" + task_to_do + "\" with priority " + to_string(priority);
        }
        else
        {
            st1 += to_string(index) + ". " + task_to_do + " [" + to_string(priority) + "]";
            out << st1;
            cout << "Added task: \"" + task_to_do + "\" with priority " + to_string(priority);
        }
        out.close();
    }
    else
    {
        ofstream out;
        out.open("task.txt");
        string val = old_val + to_string(index) + ". " + task_to_do + " [" + to_string(priority) + "]";
        out << val;
        cout << "Added task: \"" + task_to_do + "\" with priority " + to_string(priority);
        out.close();
    }
    in.close();
}
void Del(int index)
{
    int line_no = 1;
    ifstream in;
    in.open("task.txt");
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
        ofstream out;
        out.open("task.txt");
        int x = st1.length() - 1;
        st1 = st1.substr(0, x);
        out << st1;
        cout << "Deleted task #" + to_string(index);
        out.close();
    }
    else
        cout << "Error: task with index #" + to_string(index) + "does not exist. Nothing deleted.";
    in.close();
}
void Done(int index)
{
    int line_no = 1;
    ifstream in;
    in.open("task.txt");
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
            compfile.close();
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
        ofstream out;
        out.open("task.txt");
        int x = st1.length() - 1;
        st1 = st1.substr(0, x);
        out << st1;
        cout << "Marked item as done.";
        out.close();
    }
    else
        cout << "Error: no incomplete item with index #" + to_string(index) + " exists.";
    in.close();
}
int main(int argc, char *argv[])
{
    if (argc < 2)
        Help();
    else
    {
        string work = argv[1];

        if (work == "help" && argc == 2)
            Help();
        else if (work == "report" && argc == 2)
        {
            // ofstream out;
            // out.open("completed.txt");
            // out.close();
            Report();
        }

        else if (work == "ls" && argc == 2)
            List();
        // {
        //     // cout << "listing...\n";
        // }
        else if (work == "del" && argc == 3)
        {
            int index = 0;
            string ind = (argv[2]);
            stringstream x(ind);
            Del(index);
        }
        else if (work == "done" && argc == 3)
        {
            int index = 0;
            string ind = (argv[2]);
            stringstream x(ind);
            Done(index);
        }

        else if (work == "add" && argc == 4)
        {
            int priority = 0;
            string pr = (argv[2]);
            stringstream x(pr);
            x >> priority;
            string task_to_do = argv[3];
            Add(priority, task_to_do);
        }
        else
        {
            if (work == "add" && argc < 4)
                cout << "Error: Missing tasks string. Nothing added!" << endl;
            else if (work == "del" && argc < 3)
                cout << "Error: Missing NUMBER for deleting tasks." << endl;
            else if (work == "done" && argc < 3)
                cout << "Error: Missing NUMBER for marking tasks as done." << endl;
        }
    }
    return 0;
}
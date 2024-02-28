#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Utility
{
public:
    static vector<string> splitUtils(string inputs, char delim);
    static vector<int> parseRanges(string val, int startval, int endval);
    static void printDetails(vector<int> minute, vector<int> hour, vector<int> dayOfMonth, vector<int> month, vector<int> dayOfWeek, string command);
    static void printColumnInfo(string val);
};

//this takes in input string and splits it to vector<string> based on the delim supplied
vector<string> Utility :: splitUtils(string input, char delim)
{
    stringstream ss(input);
    string word;

    vector<string> result;

    while(getline(ss, word, delim))
    {
        result.push_back(word);
    }

    return result;
}

vector<int> Utility :: parseRanges(string val, int startval, int endval)
{
    vector<int> temp_data;

    //direct value without range or step-up
    if( val.length() <= 2 )
    {
        temp_data.push_back(stoi(val));
    }
    //value with a range
    else if(val.find('-') != string::npos)
    {
        vector<string> data = Utility::splitUtils(val, '-');

        int startval = stoi(data[0]);
        int endval = stoi(data[1]);

        if(startval > endval)
        {
            throw invalid_argument("Invalid cron expression"); 
        }

        for(int i = startval;i<=endval;i++)
        {
            temp_data.push_back(i);
        }
    }
    //value with a step-up
    else if(val.find('/') != string::npos)
    {
        vector<string> data = Utility::splitUtils(val, '/');

        int startval = 0;

        if(data[0] != "*")
        {
            startval = stoi(data[0]);
        }

        int stepup = stoi(data[1]);

        for(int i=startval;i<endval;i+=stepup)
        {
            temp_data.push_back(i);
        }
    }
    else
    {
        throw invalid_argument("Invalid cron expression");
    }

    return temp_data;
}

void Utility :: printColumnInfo(string val)
{
    int len = val.length();
    cout<<val;

    int idx = len + 1;
    while(idx <= 14)
    {
        cout<<" ";
        idx++;
    }

}

void Utility :: printDetails(vector<int>  minute, vector<int>  hour, vector<int>  dayOfMonth, vector<int>  month, vector<int>  dayOfWeek, string command)
{
    printColumnInfo("minute");
    for(int i=0;i<minute.size();i++)
    {
        if(minute[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    printColumnInfo("hours");
    for(int i=0;i<hour.size();i++)
    {
        if(hour[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    printColumnInfo("day of month");
    for(int i=0;i<dayOfMonth.size();i++)
    {
        if(dayOfMonth[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    printColumnInfo("month");
    for(int i=0;i<month.size();i++)
    {
        if(month[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    printColumnInfo("day of week");
    for(int i=0;i<dayOfWeek.size();i++)
    {
        if(dayOfWeek[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    printColumnInfo("command");
    cout<<command<<endl;
}
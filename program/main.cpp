#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>

#include "utils/utils.cpp"

using namespace std;

class CronParser
{
private:
     //computes the current year and handle the leap year case for Feb -> days
    void InitTimeSetup()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        
        this->current_year = 1900 + ltm->tm_year;

        if(current_year % 4 == 0)
        {
            monthDaysMap[2] = 29;
        }
        else
        {
           monthDaysMap[2] = 28;
        }
    }

    //resizes the vectors with their expected size
    void InitVectorResize()
    {
        minute.resize(MINUTES);
        hour.resize(HOURS);
        dayOfMonth.resize(DAYOFMONTH);
        month.resize(MONTH);
        dayOfWeek.resize(DAYOFWEEK);
    }

protected:
    int current_year;
    
    int MINUTES = 60;//minutes from 0-59
    int HOURS = 24;//hours from 0-23
    int DAYOFMONTH = 32;//days of month from 1-31
    int MONTH = 13;//as month range is from 1-12
    int DAYOFWEEK = 7;//day of week from 0-6

    string curr_minute;
    string curr_hour;
    string curr_dayOfMonth;
    string curr_month;
    string curr_dayOfWeek;

    vector<int> minute;
    vector<int> hour;
    vector<int> dayOfMonth;
    vector<int> month;
    vector<int> dayOfWeek;

    bool parseMinutes()
    {
        int startlimit = 0;
        int endlimit = 60;

        if(this->curr_minute == "*")
        {
            //consider all values
            for(int i=startlimit;i<endlimit;i++)
            {
                this->minute[i] = 1;
            }
        }
        else
        {
            //can be , or - or /
            vector<string> data = Utility::splitUtils(curr_minute, ',');

            //loop through the values to process them
            for(string val : data)
            {
                vector<int> parsedData;
                //it can be x-y or x/y
                try
                {
                    parsedData = Utility::parseRanges(val, startlimit, endlimit);

                    for(int val : parsedData)
                    {
                        this->minute[val] = 1;
                    }

                }
                catch(exception& e)
                {
                    cout<<e.what()<<endl;
                    this->minute.clear();
                    return false;
                }

            }

        }

        return true;
    }

    bool parseHour()
    {
        int startlimit = 0;
        int endlimit = 24;

        if(this->curr_hour == "*")
        {
            //consider all values
            for(int i=startlimit;i<endlimit;i++)
            {
                this->hour[i] = 1;
            }
        }
        else
        {
            //can be , or - or /
            vector<string> data = Utility::splitUtils(curr_hour, ',');

            //loop through the values to process them
            for(string val : data)
            {
                vector<int> parsedData;
                //it can be x-y or x/y
                try
                {
                    parsedData = Utility::parseRanges(val, startlimit, endlimit);

                    for(int val : parsedData)
                    {
                        this->hour[val] = 1;
                    }
                }
                catch(exception& e)
                {
                    cout<<e.what()<<endl;
                    this->hour.clear();
                    return false;
                }
            }

        }

        return true;
    }

    bool parseDayOfMonth()
    {
        int startlimit = 1;
        int endlimit = 32;

        if(this->curr_dayOfMonth == "*")
        {
            //consider all values
            for(int i=startlimit;i<endlimit;i++)
            {
                this->dayOfMonth[i] = 1;
            }
        }
        else if(curr_dayOfMonth.length() <= 2)
        {
            int month = stoi(curr_dayOfMonth);
            endlimit = this->monthDaysMap[month] + 1;
        }
        else
        {
            //can be , or - or /
            vector<string> data = Utility::splitUtils(curr_dayOfMonth, ',');

            //loop through the values to process them
            for(string val : data)
            {
                vector<int> parsedData;
                //it can be x-y or x/y
                try
                {
                    parsedData = Utility::parseRanges(val, startlimit, endlimit);

                    for(int val : parsedData)
                    {
                        this->dayOfMonth[val] = 1;
                    }
                }
                catch(exception& e)
                {
                    cout<<e.what()<<endl;
                    this->dayOfMonth.clear();
                    return false;
                }

            }

        }

        return true;
    }

    bool parseMonth()
    {
        int startlimit = 1;
        int endlimit = 13;

        if(this->curr_month == "*")
        {
            //consider all values
            for(int i=startlimit;i<endlimit;i++)
            {
                this->month[i] = 1;
            }
        }
        else
        {
            //can be , or - or /
            vector<string> data = Utility::splitUtils(curr_month, ',');

            //loop through the values to process them
            for(string val : data)
            {
                vector<int> parsedData;
                //it can be x-y or x/y
                try
                {
                    parsedData = Utility::parseRanges(val, startlimit, endlimit);

                    for(int val : parsedData)
                    {
                        this->month[val] = 1;
                    }
                }
                catch(exception& e)
                {
                    cout<<e.what()<<endl;
                    this->month.clear();

                    return false;
                }

            }

        }

        return true;
    }

    bool parseDayOfWeek()
    {
        int startlimit = 0;
        int endlimit = 7;

        if(this->curr_dayOfWeek == "*")
        {
            //consider all values
            for(int i=startlimit;i<endlimit;i++)
            {
                this->dayOfWeek[i] = 1;
            }
        }
        else
        {
            //can be , or - or /
            vector<string> data = Utility::splitUtils(curr_dayOfWeek, ',');

            //loop through the values to process them
            for(string val : data)
            {
                vector<int> parsedData;
                //it can be x-y or x/y
                try
                {
                    parsedData = Utility::parseRanges(val, startlimit, endlimit);

                    for(int val : parsedData)
                    {
                        this->dayOfWeek[val] = 1;
                    }
                }
                catch(exception& e)
                {
                    cout<<e.what()<<endl;
                    this->dayOfWeek.clear();

                    return false;
                }

            }

        }

        return true;
    }

    bool processCronString(string cronString)
    {  
        vector<string> vec = Utility::splitUtils(cronString, ' ');

        if(vec.size() == 5)
        {
            this->curr_minute = vec[0];
            this->curr_hour = vec[1];
            this->curr_dayOfMonth = vec[2];
            this->curr_month = vec[3];
            this->curr_dayOfWeek = vec[4];

            return parseMinutes() && parseHour() && parseDayOfMonth() && parseMonth() && parseDayOfWeek();
        }

       //not a valid string
        return false;
    }

    void printDetails(string command)
    {
        Utility::printDetails(minute, hour, dayOfMonth, month, dayOfWeek, command);
    }

public:
    map<int, int> monthDaysMap;

    CronParser(string input, string command)
    {
        mapSetup();
        InitTimeSetup();
        InitVectorResize();

        bool isValid = processCronString(input);

        if(isValid == true)
        {
            printDetails(command);
        }
    }

    void mapSetup()
    {
        monthDaysMap[1] = 31;
        monthDaysMap[2] = 28;
        monthDaysMap[3] = 31;
        monthDaysMap[4] = 30;
        monthDaysMap[5] = 31;
        monthDaysMap[6] = 30;
        monthDaysMap[7] = 31;
        monthDaysMap[8] = 31;
        monthDaysMap[9] = 30;
        monthDaysMap[10] = 31;
        monthDaysMap[11] = 30;
        monthDaysMap[12] = 31;
    }

    vector<int> getMinutes()
    {
        return this->minute;
    }

    vector<int> getHours()
    {
        return this->hour;
    }

    vector<int> getDayOfMonth()
    {
        return this->dayOfMonth;
    }

    vector<int> getMonth()
    {
        return this->month;
    }

    vector<int> getDayOfWeek()
    {
        return this->dayOfWeek;
    }

};

int main(int argc, char* argv[])
{
    //at args[1] we receive the input argument
    string input = argv[1];
    string command = argv[2];
    //cout<<input<<endl;

    CronParser cp(input, command);

    return 0;
}


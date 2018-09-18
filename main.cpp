#include <iostream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Date {
  public:
    Date()
    {
      year = 0;
      month = 0;
      day = 0;
    }
    Date(int y, int m, int d)
    {
      year = y;
      month = m;
      day = d;
    }
    int GetYear() const
    {
      return year;
    }
    int GetMonth() const
    {
      return month;
    }
    int GetDay() const
    {
      return day;
    }
    void SetYear(int y)
    {
      year = y;
    }
    void SetMonth(int m)
    {
      month = m;
    }
    void SetDay(int d)
    {
      day = d;
    }
  private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs)
{

}

stringstream& operator >> (stringstream& ss, Date& date)
{
  int year{};
  char delim1;
  int month{};
  char delim2;
  int day{};
  ss >> year >> delim1 >> month >> delim2 >> day;
  date.SetYear(year);
  date.SetMonth(month);
  date.SetDay(day);
  return ss;
}

class Database {
  public:
    void AddEvent(const Date& date, const string& event)
    {

    }
    bool DeleteEvent(const Date& date, const string& event)
    {

    }
    int  DeleteDate(const Date& date)
    {

    }

    set<string> Find(const Date& date) const
    {
      return {};
    }

    void Print() const
    {

    }
};

struct Command
{
    string operation;
    string date1;
    Date date;
    string event;
};

stringstream& operator >> (stringstream& ss, Command& command)
{
  ss >> command.operation;
  ss >> command.date;
  ss >> command.event;
  return ss;
}

Command ParseCommand(const std::string& cmd)
{
  Command command;
  stringstream ss;
  ss << cmd;
  ss >> command;
  return command;
}

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
    auto cmd = ParseCommand(command);
    if(cmd.operation == "Add")
      db.AddEvent(cmd.date, cmd.event);
    else if((cmd.operation == "Del") && !cmd.event.empty())
      db.DeleteEvent(cmd.date, cmd.event);
    else if((cmd.operation == "Del") && cmd.event.empty())
      db.DeleteDate(cmd.date);
    else if(cmd.operation == "Find")
      db.Find(cmd.date);
    else if(cmd.operation == "Print")
      db.Print();
  }

  return 0;
}

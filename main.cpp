#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <string>
#include <sstream>

using namespace std;

class Date {
public:
  Date()
  {
    year = 1;
    month = 1;
    day = 1;
  }
  Date(int y, int m, int d)
  {
    if(m < 1 || m > 12)
      throw invalid_argument("Month value is invalid: " + std::to_string(m));
    if (d < 1 || d > 31)
      throw invalid_argument("Day value is invalid: " + std::to_string(d));

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
    if(m < 1 || m > 12)
      throw invalid_argument("Month value is invalid: " + std::to_string(m));
    month = m;
  }
  void SetDay(int d)
  {
    if (d < 1 || d > 31)
      throw invalid_argument("Day value is invalid: " + std::to_string(d));
    day = d;
  }
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs)
{
  if(lhs.GetYear() != rhs.GetYear())
    return lhs.GetYear() < rhs.GetYear();
  else
  {
    if(lhs.GetMonth() != rhs.GetMonth())
      return lhs.GetMonth() < rhs.GetMonth();
    else
      return lhs.GetDay() < rhs.GetDay();
  }
}

stringstream& operator >> (stringstream& ss, Date& date)
{
  int year{};
  char delim1;
  int month{};
  char delim2;
  int day{};
  string temp;
  ss >> temp;
  stringstream ssd;
  ssd << temp;
  ssd >> year >> delim1 >> month >> delim2 >> day;
  if((delim1 != '-') || (delim2 != '-') || ssd.rdbuf()->in_avail())
    throw invalid_argument("Wrong date format: " + temp);
  date.SetYear(year);
  date.SetMonth(month);
  date.SetDay(day);
  return ss;
}

ostream& operator << (ostream& os, const Date& date)
{
  os << setfill('0') << setw(4) << date.GetYear() << '-'
     << setfill('0') << setw(2) << date.GetMonth() << '-'
     << setfill('0') << setw(2) << date.GetDay();
  return os;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event)
  {
    db[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event)
  {
    if (db[date].count(event) != 0)
    {
      db[date].erase(event);
      return true;
    }
    else
      return false;
  }
  int  DeleteDate(const Date& date)
  {
    int count = static_cast<int>(db[date].size());
    db.erase(date);
    return count;
  }

  set<string> Find(const Date& date) const
  {
    if(db.count(date) > 0)
      return db.at(date);
    else
      return {};
  }

  void Print() const
  {
    for(const auto& mi : db)
    {
      for(const auto& si : mi.second)
      {
        cout << mi.first << " " << si << endl;
      }
    }
  }
private:
  std::map<Date, std::set<std::string>> db;
};

struct Command
{
  string operation;
  Date date;
  string event;
};

stringstream& operator >> (stringstream& ss, Command& command)
{
  if(ss.rdbuf()->in_avail())
    ss >> command.operation;
  if(ss.rdbuf()->in_avail())
    ss >> command.date;
  if(ss.rdbuf()->in_avail())
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

ostream& operator << (ostream& os, const set<string>& s)
{
  for(auto i : s)
  {
    os << i;
    if(i != *s.rbegin())
      os << endl;
  }
  return os;
}

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
    if(command.empty())
      continue;

    try {
      auto cmd = ParseCommand(command);
      if(cmd.operation == "Add")
        db.AddEvent(cmd.date, cmd.event);
      else if((cmd.operation == "Del") && !cmd.event.empty())
        db.DeleteEvent(cmd.date, cmd.event) ? (cout << "Deleted successfully" << endl) : (cout << "Event not found" << endl);
      else if((cmd.operation == "Del") && cmd.event.empty())
        cout << "Deleted " << db.DeleteDate(cmd.date) << " events" << endl;
      else if(cmd.operation == "Find")
      {
        auto s = db.Find(cmd.date);
        if(!s.empty())
          cout << s << endl;
      }
      else if(cmd.operation == "Print")
        db.Print();
      else
        cout << "Unknown command: " << cmd.operation << endl;
    }
    catch (exception& e) {
      cout << e.what() << endl;
      return 1;
    }
  }

  return 0;
}

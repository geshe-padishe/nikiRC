#include "BitcoinExchange.hpp"

std::multimap<std::string, double>::iterator getLowerBound(std::multimap<std::string, double>& aMultimap, std::string key)
{
    std::multimap<std::string, double>::iterator it = aMultimap.lower_bound(key);
    
    if (it == aMultimap.end() || it->first != key)
    {
        --it;
    }
    return it;
}

void print_multimap(const std::multimap<std::string, double>& m)
{
	for (std::multimap<std::string, double>::const_iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout << it->first << " = " << it->second;
		std::cout << std::endl;
	}
}

bool validateDate(const std::string& dateString)
{
    int y, m, d;

    if (sscanf(dateString.c_str(), "%4d-%2d-%2d", &y, &m, &d) != 3)
    { return false; }
	if ((y < 2009) || (y == 2009 && m == 1 && d < 2))
		return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;
    if (m == 2)
    {
        if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
            return (d <= 29);
        else
            return (d <= 28);
    }
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);
    return (true);
}

std::multimap<std::string, double> parseInputFile(std::ifstream &file, std::multimap<std::string, double> &m)
{
    std::multimap<std::string, double> dvList;
    std::string line;
    std::string date;
	std::string sep;
    double value;

	if (!file.is_open())
		return (std::cout << "Error: could not open file." << std::endl, std::multimap<std::string, double>());
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
		std::getline(iss, date, ' ');
		std::getline(iss, sep, '|');
		std::getline(iss, sep, ' ');
		if (!validateDate(date))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (!(iss >> value))
		{
			std::cout << "Error: bad input => " << value << std::endl;;
			continue;
		}
		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large number." << std::endl;
			continue;		
		}
		std::multimap<std::string, double>::iterator it = m.find(date);
		if (it == m.end())
			it = getLowerBound(m, date);
		//std::cout << "date = " << date << "| value = " << value << " | it->second = " << it->second << std::endl;
		std::cout << date << " => " << value  << " = " << it->second * value << std::endl;
		dvList.insert(std::make_pair(date, it->second * value));
    }
	return dvList;
}

std::multimap<std::string, double> parseCsvFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::multimap<std::string, double> dvList;
    std::string line;
    std::string date;
    double value;

    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
		std::getline(iss, date, ',');
        if (!validateDate(date))
			continue;
		if (!(iss >> value))
			continue;
		if (value < 0)
			continue;
		//std::cout << date << "," << value << std::endl;
		dvList.insert(std::make_pair(date, value));
    }
	return dvList;
}
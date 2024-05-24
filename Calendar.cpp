#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>

constexpr uint16_t spaces = 4;
constexpr uint16_t ThreeLettersMonth = 3;
constexpr uint16_t MaxSpaces = (spaces * 7) + (ThreeLettersMonth * 7);
const int ZellerRule(const int d, int m, int y)
{
	// Adjust month and year for Zeller's Congruence
	if (m < 3)
	{
		m += 12;
		y -= 1;
	}

	y = std::abs(y);
	const int lastTwoDigitsYear = y % 100;

	// Calculate the number of digits in the number
	const int numDigits = static_cast<int>(std::log10(y)) + 1;

	// Calculate the power to raise 10 to in order to get the first two digits
	const int divisor = static_cast<int>(std::pow(10, numDigits - 2));

	const int firstTwoDigitsYear = y / divisor;

	// Zeller's Congruence formula
	int h = (d + (13 * (m + 1)) / 5 + lastTwoDigitsYear + lastTwoDigitsYear / 4 + firstTwoDigitsYear / 4 - 2 * firstTwoDigitsYear) % 7;
	if(h < 0)
	{
		h += 7;
	}

	// sat = 0, sunday = 1, monday = 2, tue = 3, wed = 4, thu = 5, fri = 6
	return h;
}

void printProcess(const uint16_t days, const uint16_t month, const uint16_t year)
{
	std::cout << std::setw(spaces) << ""
			  << "SUN" << std::setw(spaces) << ""
			  << "MON" << std::setw(spaces) << ""
			  << "TUE" << std::setw(spaces) << ""
			  << "WED" << std::setw(spaces) << ""
			  << "THU" << std::setw(spaces) << ""
			  << "FRI" << std::setw(spaces) << ""
			  << "SAT\n";
	bool newLineActivated = true;
	for (uint16_t i = 1; i <= days; i++)
	{
		const uint16_t dayToday = ZellerRule(i, month, year);
		const uint16_t minusSpace = (i < 10) ? 0 : 1;
		std::stringstream ss;
		ss << i;
		/*
		if (dayToday == 1 || dayToday == 0) // if the color does not work then delete
		{
			ss << "\033[31m" << i << "\033[0m";  // red
		}
		else
		{
			ss << i;
		}*/
		const std::string iSTR = ss.str();
		if (newLineActivated) // at the beginning or SUN or SAT or END
		{
			newLineActivated = false;
			if (dayToday == 0)
			{
				std::cout << std::setw(7 * (spaces + ThreeLettersMonth) - 2 - minusSpace) << "" << iSTR << "\n"; // if the 1st day of a month is at SAT format
				newLineActivated = true;
			}
			else
			{
				std::cout << std::setw(dayToday * (spaces + ThreeLettersMonth) - 2 - minusSpace) << "" << iSTR; // For SUN
			}
		}
		else // not beginning nor SUN nor SAT nor END
		{
			std::cout << std::setw(spaces + ThreeLettersMonth - 1 - minusSpace) << "" << iSTR;
			if (dayToday == 0)
			{
				std::cout << "\n";
				newLineActivated = true;
			}
		}
	}
	std::cout << "\n\n";
}

void printMonth(const uint16_t month, const uint16_t year)
{
	uint16_t days = 0;
	std::string monthName;
	switch (month)
	{
	case 1:
		monthName = "January";
		days = 31;
		break;
	case 2:
		monthName = "February";
		days = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
		break;
	case 3:
		monthName = "March";
		days = 31;
		break;
	case 4:
		monthName = "April";
		days = 30;
		break;
	case 5:
		monthName = "May";
		days = 31;
		break;
	case 6:
		monthName = "June";
		days = 30;
		break;
	case 7:
		monthName = "July";
		days = 31;
		break;
	case 8:
		monthName = "August";
		days = 31;
		break;
	case 9:
		monthName = "September";
		days = 30;
		break;
	case 10:
		monthName = "October";
		days = 31;
		break;
	case 11:
		monthName = "November";
		days = 30;
		break;
	case 12:
		monthName = "December";
		days = 31;
		break;
	default:
		break;
	}
	const uint16_t spaces_toCenter = std::abs(static_cast<int>((monthName.length() / 2) - (MaxSpaces / 2)));

	std::cout << std::setw(spaces_toCenter) << "" << monthName << "\n";
	printProcess(days, month, year);
}

int main()
{
	uint16_t year = 0;
	//std::cout << ZellerRule(23,5,2024) << "\n";

	std::cout << "Enter Year: ";
	std::cin >> year;

	std::cout << "Calender of the year " << year << ":\n";
	std::cout << "Max Spaces: " << MaxSpaces << "\n";
	for (int i = 1; i <= 12; i++)
	{
		printMonth(i, year);
	}
	return 0;
}

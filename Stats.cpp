// Name: Navdeep Virdi
// Seneca email: nvirdi2@myseneca.ca
// Student ID: 166485193
// Date: March 16, 2021

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include <fstream>
#include "cstring.h"
#include "Stats.h"
#include <string>
#include <sstream> 

using namespace std;
namespace sdds
{
	Stats::Stats(const char* filename, unsigned columnWidth, unsigned noOfColumns, unsigned precision) :m_num(nullptr), m_numOfNums(0), m_filename(nullptr), m_columnWidth(0), m_noOfColumns(0), m_precision(0) 
	{	
		m_numOfNums = 0;

		m_columnWidth = columnWidth;
		m_noOfColumns = noOfColumns;
		m_precision = precision;

		m_filename = nullptr;
		m_num = nullptr;

			if (filename != nullptr) 
			{
				setFilename(filename);
				loadNums();
			}
	}

	Stats::Stats(unsigned columnWidth, unsigned noOfColumns, unsigned precision) :m_num(nullptr), m_numOfNums(0), m_filename(nullptr), m_columnWidth(0), m_noOfColumns(0), m_precision(0) 
	{	
		m_numOfNums = 0;

		m_columnWidth = columnWidth;
		m_noOfColumns = noOfColumns;
		m_precision = precision;

		m_filename = nullptr;
		m_num = nullptr;
	}

	Stats::Stats(const Stats& stat) :m_num(nullptr), m_numOfNums(0), m_filename(nullptr), m_columnWidth(0), m_noOfColumns(0), m_precision(0) 
	{
		ifstream file(stat.m_filename);

		if (file.good()) 
		{
			m_noOfColumns = stat.m_noOfColumns;
			m_precision = stat.m_precision;
			m_columnWidth = stat.m_columnWidth;

			setFilename(stat.m_filename, true);
			stat.saveAs(m_filename);

			loadNums();
		}
	}

	Stats::~Stats() 
	{
		if (m_numOfNums != 0)
		{
			delete[] m_num;
		}
		if (m_filename != nullptr && strLen(m_filename) > 0)
		{
			delete[] m_filename;
		}
	}



	void Stats::setFilename(const char* fname, bool isCopy) 
	{
		m_filename = new char[strLen(fname) + 3];

		if (!isCopy)
		{
			strCpy(m_filename, fname);
		}
		else 
		{
			strCpy(m_filename, "C_");
			strCat(m_filename, fname);
		}
	}

	void Stats::saveAs(const char* fileName) const 
	{
		ofstream fout(fileName);
		ifstream fin(m_filename);

		string line;

			while (getline(fin, line)) 
			{
				fout << line;
			}

		fin.close();

		fout.close();
	}

	void Stats::loadNums() 
	{
		m_numOfNums = 0;
		ifstream file(m_filename);

		if (file.good()) 
		{
			string line;
			getline(file, line);
			stringstream x(line);
			double i;
			string num;

				while (getline(x, num, ',')) 
				{
					m_numOfNums++;
				}

			m_num = new double[m_numOfNums];

			stringstream x2(line);

			int index = 0;
			while (getline(x2, num, ',')) 
			{
				i = stod(num);
				m_num[index] = i;
				index++;
			}

			file.close();
		}
	}

	void Stats::sort(bool ascending) 
	{
		int x, i;
		int y = m_numOfNums;
		for (x = 0; x < y - 1; x++) 
		{
			for (i = 0; i < y - x - 1; i++) 
			{
				if ((ascending && m_num[i] > m_num[i + 1]) || (!ascending && m_num[i] < m_num[i + 1])) 
				{
					double tmp = m_num[i];
					m_num[i] = m_num[i + 1];
					m_num[i + 1] = tmp;
				}
			}
		}

	}



	double Stats::operator[](unsigned index) const 
	{
		double x = 0;
		if (*this && m_numOfNums > 0) 
		{
			x = m_num[index % m_numOfNums];
		} return x;
	}

	double& Stats::operator[](unsigned index) 
	{
		
		if (!(*this && m_numOfNums > 0))
		{
			return nothing;
		} return m_num[index % m_numOfNums];
	}



	std::istream& operator>>(std::istream& istr, Stats& text) 
	{
		return (text.getFile(istr));
	}

	std::ostream& operator<<(std::ostream& ostr, const Stats& text) 
	{
		text.view(ostr);
			return ostr;
	}

	std::ostream& Stats::view(std::ostream& ostr) const 
	{
		if (m_num == nullptr || m_filename == nullptr || m_numOfNums == 0) 
		{
			return ostr;
		}

		ostr << m_filename << endl;

		for (int i = 0; m_filename[i] != '\0'; i++) 
		{
			ostr << "=";
		}

		bool lookover = false;
		ostr << endl << endl;
		ostr << fixed << setprecision(m_precision);

		for (int x = 0; x < m_numOfNums; x++) 
		{
			ostr << right << setw(m_columnWidth) << m_num[x];
			lookover = false;

			if ((x + 1) % m_noOfColumns == 0) 
			{
				lookover = true;
				ostr << endl;
			}
		}

		if (!lookover) 
		{
			ostr << endl;
		}
		ostr << "Total of " << m_numOfNums << " listed!" << endl;
			return ostr;
	}

	std::istream& Stats::getFile(std::istream& istr) 
	{
		string tmp;

		getline(istr, tmp);
		setFilename(tmp.c_str());
		loadNums();

		return istr;
	}



	Stats::operator bool() const 
	{
		if (m_filename == nullptr || m_numOfNums == 0) 
		{
			return false;
		} return true;
	}

	unsigned Stats::occurrence(double min, double max, std::ostream& ostr) 
	{
		unsigned x = 0;
		if (*this) 
		{
			ostr << endl;
			ostr << fixed << setprecision(m_precision);
			bool lookover = false;
			
			for (int i = 0; i < m_numOfNums; ++i) 
			{
				if (m_num[i] >= min && m_num[i] <= max) 
				{
					lookover = false;
					ostr << right << setw(m_columnWidth) << m_num[i];
					
					if ((x + 1) % m_noOfColumns == 0) 
					{
						lookover = true;
						ostr << endl;
					}
					x++;
				}
			}

			if (!lookover)
			{
				ostr << endl;
			}
			ostr << "Total of " << x << " numbers are between " << min << " and " << max << endl;
		}

		return x;
	}


	unsigned Stats::size() const 
	{	
		return m_numOfNums;
	}

	const char* Stats::name() const 
	{	
		return m_filename;
	}


	Stats& Stats::operator=(Stats& stat) 
	{
		ifstream file1(m_filename);
		ifstream file2(stat.m_filename);

		if (file1.good() && file2.good()) 
		{
			m_noOfColumns = stat.m_noOfColumns;
			m_precision = stat.m_precision;
			m_columnWidth = stat.m_columnWidth;

			stat.saveAs(m_filename);

			delete[] m_num;
			delete[] stat.m_num;

			m_numOfNums = 0;
			stat.m_numOfNums = 0;

			loadNums();
		} return *this;
	}
}

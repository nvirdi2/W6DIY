#include <iostream>
#include <iomanip>
#include <fstream>
#include "cstring.h"
#include "Stats.h"
#include <string>
#include <sstream> 

using namespace std;
namespace sdds{

	void Stats::setFilename(const char* fname, bool isCopy) {
		m_filename = new char[strLen(fname) + 3];
		if (!isCopy)
			strCpy(m_filename, fname);
		else {
			strCpy(m_filename, "C_");
			strCat(m_filename, fname);
		}
	}

	void Stats::saveAs(const char* fileName) const {
		ofstream fout(fileName);
		ifstream fin(m_filename);
		string line;

		while (getline(fin, line)) {
			fout << line;
		}

		fin.close();
		fout.close();
	}

	void Stats::loadNums() {
		m_noOfNums = 0;
		ifstream file(m_filename);

		if (file.good()) {
			string line;
			getline(file, line);
			stringstream ss(line);
			double a;
			string num;

			while (getline(ss, num, ',')) {
				m_noOfNums++;
			}

			m_arr = new double[m_noOfNums];
			stringstream ss2(line);
			int idex = 0;
			while (getline(ss2, num, ',')) {
				a = stod(num);
				m_arr[idex] = a;
				idex++;
			}

			file.close();
		}
	}

	Stats::Stats(const char* filename, unsigned columnWidth, unsigned noOfColumns, unsigned precision) :m_arr(nullptr), m_noOfNums(0), m_filename(nullptr), m_columnWidth(0), m_noOfColumns(0), m_precision(0) {	
		m_noOfNums = 0;
		m_columnWidth = columnWidth;
		m_noOfColumns = noOfColumns;
		m_precision = precision;
		m_filename = nullptr;
		m_arr = nullptr;

		if (filename != nullptr) {
			setFilename(filename);
			loadNums();
		}
	}

	Stats::Stats(unsigned columnWidth, unsigned noOfColumns, unsigned precision) :m_arr(nullptr), m_noOfNums(0), m_filename(nullptr), m_columnWidth(0), m_noOfColumns(0), m_precision(0) {	
		m_noOfNums = 0;
		m_filename = nullptr;
		m_columnWidth = columnWidth;
		m_noOfColumns = noOfColumns;
		m_precision = precision;
		m_arr = nullptr;
	}

	Stats::Stats(const Stats& other) :m_arr(nullptr), m_noOfNums(0), m_filename(nullptr), m_columnWidth(0), m_noOfColumns(0), m_precision(0) {
		ifstream file(other.m_filename);

		if (file.good()) {
			m_noOfColumns = other.m_noOfColumns;
			m_precision = other.m_precision;
			m_columnWidth = other.m_columnWidth;
			setFilename(other.m_filename, true);
			other.saveAs(m_filename);
			loadNums();
		}
	}

	Stats::~Stats() {
		if (m_noOfNums != 0)
			delete[] m_arr;
		if (m_filename != nullptr && strLen(m_filename) > 0)
			delete[] m_filename;
	}

	Stats& Stats::operator=(Stats& other) {
		ifstream file1(m_filename);
		ifstream file2(other.m_filename);

		if (file1.good() && file2.good()) {

			m_noOfColumns = other.m_noOfColumns;
			m_precision = other.m_precision;
			m_columnWidth = other.m_columnWidth;
			other.saveAs(m_filename);
			delete[] m_arr;
			delete[] other.m_arr;
			m_noOfNums = 0;
			other.m_noOfNums = 0;
			loadNums();
		}

		return *this;
	}

	void Stats::sort(bool ascending) {
		int b, c;
		int d = m_noOfNums;
		for (b = 0; b < d - 1; b++) {
			for (c = 0; c < d - b - 1; c++) {
				if ((ascending && m_arr[c] > m_arr[c + 1]) ||
					(!ascending && m_arr[c] < m_arr[c + 1])) {
					double temp = m_arr[c];
					m_arr[c] = m_arr[c + 1];
					m_arr[c + 1] = temp;
				}
			}
		}

	}

	unsigned Stats::size() const {	
		return m_noOfNums;
	}

	const char* Stats::name() const {	
		return m_filename;
	}

	unsigned Stats::occurrence(double min, double max, std::ostream& ostr) {
		unsigned count = 0;
		if (*this) {
			ostr << endl;
			ostr << fixed << setprecision(m_precision);
			bool check = false;
			for (int e = 0; e < m_noOfNums; e++) {
				if (m_arr[e] >= min && m_arr[e] <= max) {
					check = false;
					ostr << right << setw(m_columnWidth) << m_arr[e];
					if ((count + 1) % m_noOfColumns == 0) {
						check = true;
						ostr << endl;
					}

					count++;
				}
			}

			if (!check)
				ostr << endl;
			ostr << "Total of " << count << " numbers are between " << min << " and " << max << endl;
		}

		return count;
	}

	double Stats::operator[](unsigned idx) const {
		
		double i = 0;
		if (*this && m_noOfNums > 0) {
			i = m_arr[idx % m_noOfNums];
		}

		return i;
	}

	double& Stats::operator[](unsigned idx) {
		
		if (!(*this && m_noOfNums > 0))
			return dummy;
		return m_arr[idx % m_noOfNums];
	}

	Stats::operator bool() const {
		if (m_filename == nullptr || m_noOfNums == 0) {
			return false;
		}

		return true;
	}

	std::ostream& Stats::view(std::ostream& ostr) const {
		if (m_arr == nullptr || m_filename == nullptr || m_noOfNums == 0) {
			return ostr;
		}

		ostr << m_filename << endl;
		for (int i = 0; m_filename[i] != '\0'; i++) {
			ostr << "=";
		}

		bool check = false;
		ostr << endl << endl;
		ostr << fixed << setprecision(m_precision);

		for (int e = 0; e < m_noOfNums; e++) {
			ostr << right << setw(m_columnWidth) << m_arr[e];
			check = false;
			if ((e + 1) % m_noOfColumns == 0) {
				check = true;
				ostr << endl;
			}
		}

		if (!check)
			ostr << endl;
		ostr << "Total of " << m_noOfNums << " listed!" << endl;
		return ostr;
	}

	std::istream& Stats::getFile(std::istream& istr) {
		string temp;
		getline(istr, temp);
		setFilename(temp.c_str());
		loadNums();
		return istr;
	}

	std::istream& operator>>(std::istream& istr, Stats& text) {
		return text.getFile(istr);
	}

	std::ostream& operator<<(std::ostream& ostr, const Stats& text) {
		text.view(ostr);
		return ostr;
	}
}

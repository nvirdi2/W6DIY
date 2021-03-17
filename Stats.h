// Name: Navdeep Virdi
// Seneca email: nvirdi2@myseneca.ca
// Student ID: 166485193
// Date: March 16, 2021

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_STATS_H__
#define SDDS_STATS_H__
#include <iostream>

namespace sdds {

    class Stats {
        double* m_num;
        int m_numOfNums;
        char* m_filename;

        unsigned m_columnWidth;
        unsigned m_noOfColumns;
        unsigned m_precision;

        double nothing = 0;

    public:
        Stats(unsigned columnWidth = 15, unsigned noOfColumns = 4, unsigned precision = 2);
        Stats(const char* filename, unsigned columnWidth = 15, unsigned noOfColumns = 4, unsigned precision = 2);
        Stats(const Stats&);
        ~Stats();

        void setFilename(const char* fname, bool isCopy = false);
        void loadNums();
        void saveAs(const char* fileName)const;
        void sort(bool ascending);

        double& operator[](unsigned index);
        double operator[](unsigned index)const;

        std::ostream& view(std::ostream& ostr) const;
        std::istream& getFile(std::istream& istr);

        unsigned occurrence(double min, double max, std::ostream& ostr = std::cout);
        unsigned size()const;

        Stats& operator=(Stats&);
        operator bool()const;
        const char* name()const;
    };
    std::ostream& operator<<(std::ostream& ostr, const Stats& text);
    std::istream& operator>>(std::istream& istr, Stats& text);
}
#endif

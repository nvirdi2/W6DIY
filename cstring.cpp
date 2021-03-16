// Name: Navdeep Virdi
// Seneca email: nvirdi2@myseneca.ca
// Student ID: 166485193
// Date: March 16, 2021

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

namespace sdds 
{

    void strCpy(char* des, const char* src)
    {
        while ((*des++ = *src++));
    }

    int strnCmp(const char* s1, const char* s2, int len)
    {
        while (len && *s1 && (*s1 == *s2))
        {
            ++s1;
            ++s2;
            --len;
        }

        if (len == 0)
        {
            return 0;
        }
        
        else
        {
            return(*(unsigned char *) s1 - * (unsigned char *) s2);
        }   
    }

    const char* strStr(const char* str1, const char* str2)
    {
        int i = 0;
        int x = 0;
        int y = 0;

        while (str1[i] != '\0')
        {
            x = i;

            while (str2[y] != '\0')
            {
                
                if (str1[x] != str2[y])
                {
                    break;
                }
                x++;
                y++;
            }

            if (str2[y] == '\0')
            {
                return (char *) str1 + i;
            }

            else
            {
                i++;
                x = 0;
            } 
        } 
        return nullptr;
    }

    int strLen(const char* s)
    {
        int lenght = 0;
        int x;

        for (x = 0; s[x] != 0; x++)
        {
            lenght++;
        } return (lenght);
    }

    void strnCpy(char* des, const char* src, int len)
    {
        int x;

        for (x = 0; x < len; x++)
        {
            des[x] = src[x];
        }
    }

    int strCmp(const char* s1, const char* s2)
    {
        while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
        {
            s1++;
            s2++;
        }

        if (*s1 == *s2)
        {
            return 0;
        }

        else if (*s1 > *s2)
        {
            return 1;
        }

        else
        {
            return 1;
        } 
    }

    void strCat(char* des, const char* src)
    {
        while (*des != '\0')
        {
            des++;
        }

        while ((*des++ = *src++) != '\0');
    }
}

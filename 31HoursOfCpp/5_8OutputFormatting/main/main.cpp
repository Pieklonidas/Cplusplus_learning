#include <iostream>
#include <ios>
#include <iomanip>

int main()
{
    //std::flush : flushes the output buffer to its final destination
    std::cout << "This is nice message..." << std::endl << std::flush;
    //After this std::flush, we're sure that at this line, the message has been sent
    //to the stream. This may be important in some applications.

    std::cout << std::endl;

    //std::setw() : Adjusts the field with for the item about to be printed.
    //The setw() manipulator only affects the next value to be printed.

    std::cout << "Unfortunate table: " << std::endl;
    std::cout << "Daniel" << " " << "Gray" << " 25" << std::endl;
    std::cout << "Joe" << " " << "Robinson" << " 35" << std::endl;
    std::cout << "Stanley" << " " << "Woods" << " 45" << std::endl;
    std::cout << std::endl;

    std::cout << "Formatted table: " << std::endl;
    std::cout << std::setw(10) << "Lastname" << std::setw(10)  << "Firstname"<< std::setw(5)  << "age" << std::setw(10)  <<std::endl;
    std::cout << std::setw(10) << "Daniel" << std::setw(10) << "Gray" << std::setw(5)  << "25" << std::endl;
    std::cout << std::setw(10) << "Joe" << std::setw(10)  << "Robinson" << std::setw(5) << "35" << std::endl;
    std::cout << std::setw(10) << "Stanley" << std::setw(10) << "Woods" << std::setw(5) << "45" << std::endl;
    std::cout << std::endl;

    int col_width{14};
    std::cout << "Formatted table with variable: " << std::endl;
    std::cout << std::setw(col_width) << "Lastname" << std::setw(col_width)  << "Firstname"<< std::setw(col_width)  << "age" << std::setw(10)  <<std::endl;
    std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width)  << "25" << std::endl;
    std::cout << std::setw(col_width) << "Joe" << std::setw(col_width)  << "Robinson" << std::setw(col_width) << "35" << std::endl;
    std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width) << "45" << std::endl;
    std::cout << std::endl;

    //Justify

    //right

    col_width = 20;
    std::cout << "Right justified table(default): " << std::endl;
    std::cout << std::right;
    std::cout << std::setw(col_width) << "Lastname" << std::setw(col_width)  << "Firstname"<< std::setw(col_width)  << "age" << std::setw(10)  <<std::endl;
    std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width)  << "25" << std::endl;
    std::cout << std::setw(col_width) << "Joe" << std::setw(col_width)  << "Robinson" << std::setw(col_width) << "35" << std::endl;
    std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width) << "45" << std::endl;
    std::cout << std::endl;

    //left

    std::cout << "Left justified table(default): " << std::endl;
    std::cout << std::left;
    std::cout << std::setw(col_width) << "Lastname" << std::setw(col_width)  << "Firstname"<< std::setw(col_width)  << "age" << std::setw(10)  <<std::endl;
    std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width)  << "25" << std::endl;
    std::cout << std::setw(col_width) << "Joe" << std::setw(col_width)  << "Robinson" << std::setw(col_width) << "35" << std::endl;
    std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width) << "45" << std::endl;
    std::cout << std::endl;

    //Internal : sign is left justified, data is right justified
    std::cout << "Internal justified: " << std::endl;
    std::cout << std::right;
    std::cout << std::setw(10) << -123.45 << std::endl;
    std::cout << std::internal;
    std::cout << std::setw(10) << -123.45 << std::endl;
    std::cout << std::endl;

    //setfill
    std::cout << "Table with fill characters: " << std::endl;
    std::cout << std::left;
    std::cout << std::setfill('-'); // The fill character
    std::cout << std::setw(col_width) << "Lastname" << std::setw(col_width)  << "Firstname"<< std::setw(col_width)  << "age" << std::setw(10)  <<std::endl;
    std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width)  << "25" << std::endl;
    std::cout << std::setw(col_width) << "Joe" << std::setw(col_width)  << "Robinson" << std::setw(col_width) << "35" << std::endl;
    std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width) << "45" << std::endl;
    std::cout << std::endl;

    //boolalpha

    bool condition{true};
    bool other_condition{false};

    std::cout << "condition: " << condition << std::endl;
    std::cout << "other condition: " << other_condition << std::endl;
    std::cout << std::endl;
    std::cout << std::boolalpha;
    std::cout << "condition: " << condition << std::endl;
    std::cout << "other condition: " << other_condition << std::endl;
    std::cout << std::endl;
    std::cout << std::noboolalpha;
    std::cout << "condition: " << condition << std::endl;
    std::cout << "other condition: " << other_condition << std::endl;
    std::cout << std::endl;

    //showpos

    int pos_num{35};
    int neg_num{-45};

    std::cout << "pos_num: " << pos_num << std::endl;
    std::cout << "neg_num: " << neg_num << std::endl;
    std::cout << std::endl;
    std::cout << std::showpos;
    std::cout << "pos_num: " << pos_num << std::endl;
    std::cout << "neg_num: " << neg_num << std::endl;
    std::cout << std::endl;
    std::cout << std::noshowpos;
    std::cout << "pos_num: " << pos_num << std::endl;
    std::cout << "neg_num: " << neg_num << std::endl;
    std::cout << std::endl;

    int pos_int{717171};
    int neg_int{-47347};
    double double_var{498.32};

    std::cout << "default base format: " << std::endl;
    std::cout << "pos_int: " << pos_int << std::endl;
    std::cout << "neg_int: " << neg_int << std::endl;
    std::cout << "double_var: " << double_var << std::endl;
    std::cout << std::endl;
    std::cout << "pos_int in different bases: " << std::endl;
    std::cout << "pos_int: " << std::dec << pos_int << std::endl;
    std::cout << "pos_int: " << std::hex << pos_int << std::endl;
    std::cout << "pos_int: " << std::oct << pos_int << std::endl;
    std::cout << std::endl;
    std::cout << "neg_int in different bases: " << std::endl;
    std::cout << "neg_int: " << std::dec << neg_int << std::endl;
    std::cout << "neg_int: " << std::hex << neg_int << std::endl;
    std::cout << "neg_int: " << std::oct << neg_int << std::endl;
    std::cout << std::endl;
    std::cout << "double_var in different bases: " << std::endl;
    std::cout << "double_var: " << std::dec << double_var << std::endl;
    std::cout << "double_var: " << std::hex << double_var << std::endl;
    std::cout << "double_var: " << std::oct << double_var << std::endl;
    std::cout << std::dec;
    std::cout << std::endl;

    //uppercase
    std::cout << "pos_int uppercase: " << std::endl;
    std::cout << std::uppercase;
    std::cout << "pos_int: " << std::dec << pos_int << std::endl;
    std::cout << "pos_int: " << std::hex << pos_int << std::endl;
    std::cout << "pos_int: " << std::oct << pos_int << std::endl;
    std::cout << std::endl;

    //fixed and scientific : for floating point values

    double a{3.1415926535897932384626433832795};
    double b{2006.0};
    double c{1.34e-10};

    std::cout << "double variables (default : use scientific where necessary): " << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << std::endl;

    std::cout << "double values fixed: " << std::endl;
    std::cout << std::fixed;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << std::endl;

    std::cout << "double values scientific: " << std::endl;
    std::cout << std::scientific;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << std::endl;

    std::cout << "double values back to default: " << std::endl;
    std::cout.unsetf(std::ios::scientific | std::ios::fixed);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << std::endl;

    a = 3.1415926535897932384626433832795;

    std::cout << "a (default precision (6)): " << a << std::endl;
    std::cout << std::setprecision(10);
    std::cout << "a (default precision (10)): " << a << std::endl;
    std::cout << std::setprecision(20);
    std::cout << "a (default precision (20)): " << a << std::endl;
    std::cout << std::endl;

    //showpoint

    double d{34.1};
    double e{101.99};
    double f{12.0};
    int g{45};

    std::cout << "noshowpoint (default): " << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "f: " << f << std::endl;
    std::cout << "g: " << g << std::endl;
    std::cout << std::endl;

    std::cout << "showpoint: " << std::endl;
    std::cout << std::showpoint;
    std::cout << "d: " << d << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "f: " << f << std::endl;
    std::cout << "g: " << g << std::endl;
    std::cout << std::endl;

    return 0;
}

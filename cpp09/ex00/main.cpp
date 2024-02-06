#include "BitcoinExchange.hpp"

int main(int ac, char **argv)
{
  struct stat st;
    if (ac != 2)
      return (std::cout << "Error: could not open file." << std::endl, 1);
    if (stat("data.csv", &st) == -1)
      return (std::cout << "Error: could not open file." << std::endl, 1);
    else if (S_ISDIR(st.st_mode))
      return (std::cout << "ErroL could not open file." << std::endl, 1);
    if (stat(argv[1], &st) == -1)
      return (std::cout << "Error: could not open file." << std::endl, 1);   
    else if (S_ISDIR(st.st_mode))
      return (std::cout << "Error: could not open file." << std::endl, 1);
    std::ifstream file(argv[1]);
    std::multimap<std::string, double> dvList2 = parseCsvFile("data.csv");
    //std::cout << "DEBUG PRINT multimap CSV\n";
    //print_multimap(dvList2);
      //  std::cout << "END DEBUG PRINT multimap CSV\n";
    std::multimap<std::string, double> dvList = parseInputFile(file, dvList2);
    //print_multimap(dvList);
}

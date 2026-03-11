#include<stdio.h>
#include<iostream>
#include<string>
#include<map>

std::map<char, std::string> hexToBin = {
  {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
  {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
  {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"},
  {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
};

int main(void) { 
  char[8] ch;
  scanf("%c%c%c%c ", &ch[0], &ch[1], &ch[2], &ch[3]);
  scanf("%c%c%c%c\n", &ch[4], &ch[5], &ch[6], &ch[7]);
  return 0;
}

#include<stdio.h>
#include<iostream>
#include<string>
#include<map>
#include<math.h>
#include<bitset>

std::map<char, std::string> hexToBin = {
  {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
  {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
  {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"},
  {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
};

std::map<std::string, char> binToHex;
for (const auto& pair : hexToBin) {
  binToHex[pair.second] = pair.first;
}

int main(void) { 
  char[4] ch1;
  char[4] ch2;
  scanf("%c%c%c%c ", &ch1[0], &ch1[1], &ch1[2], &ch1[3]);
  scanf("%c%c%c%c\n", &ch2[0], &ch2[1], &ch2[2], &ch2[3]);

  std::string bin1;
  std::string bin2;
  for (char c : ch1) {
    if (hexToBin.find(c) != hexToBin.end()) {
      bin1 += hexToBin[c];
    }
  }
  for (char c : ch2) {
    if (hexToBin.find(c) != hexToBin.end()) {
      bin2 += hexToBin[c];
    }
  }

  char s1 = bin1[0];
  std::string e1_bin = bin1.substr(1, 5);
  std::string m1_bin = bin1.substr(6, 10);
  std::bitset<5> e1_bitset(e1_bin);
  std::bitset<12> m1_bitset(m1_bin << 2);
  char s2 = bin2[0];
  std::string e2_bin = bin2.substr(1, 5);
  std::string m2_bin = bin2.substr(6, 10);
  std::bitset<5> e2_bitset(e2_bin);
  std::bitset<12> m2_bitset(m2_bin << 2);

  int e1 = -15;
  for(i = 0; i < 5; i++) {
    if(e1_bitset[i] == '1') {
      e1 += pow(2, 4 - i);
    }
  }
  std::string m1 = "";
  for (size_t i = 0; i < m1_bitset.length(); i += 4) {
    std::string group = m1_bitset.substr(i, 4);
    m1 += binToHex[group];
  }
  
  int e2 = -15;
  for(i = 0; i < 5; i++) {
    if(e2_bitset[i] == '1') {
      e2 += pow(2, 4 - i);
    }
  }
  std::string m2 = "";
  for (size_t i = 0; i < m2_bitset.length(); i += 4) {
    std::string group = m2_bitset.substr(i, 4);
    m2 += binToHex[group];
  }  
  
  std::string type1 = "normal";
  if (e1_bitset.none()) {
    if (m1_bitset.none()) {
      type1 = "zero";
    } else {
      type1 = "subnormal";
    }
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=0." << m1 << " " << type1 << std::endl;
  } else if (e1_bitset.all()) {
    if (m1_bitset.none()) {
      type1 = "inf";
    } else {
      type1 = "nan";
    }
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=1." << m1 << " " << type1 << std::endl;
  } else {
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=1." << m1 << " " << type1 << std::endl;
  }

  std::string type2 = "normal";
  if (e2_bitset.none()) {
    if (m2_bitset.none()) {
      type2 = "zero";
    } else {
      type2 = "subnormal";
    }
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=0." << m2 << " " << type2 << std::endl;
  } else if (e2_bitset.all()) {
    if (m2_bitset.none()) {
      type2 = "inf";
    } else {
      type2 = "nan";
    }
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=1." << m2 << " " << type2 << std::endl;
  } else {
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=1." << m2 << " " << type2 << std::endl;
  }
  
  return 0;
}

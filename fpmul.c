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

int main(void) { 
  for (const auto& pair : hexToBin) {
    binToHex[pair.second] = pair.first;
  }
  
  char ch1[4];
  char ch2[4];
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
  m1_bin = m1_bin + "00";
  char s2 = bin2[0];
  std::string e2_bin = bin2.substr(1, 5);
  std::string m2_bin = bin2.substr(6, 10);
  m2_bin = m2_bin + "00";

  int e1 = -15;
  for(int i = 0; i < 5; i++) {
    if(e1_bin[i] == '1') {
      e1 += 1 << (4 - i);
    }
  }
  std::string m1 = "";
  for (size_t i = 0; i < m1_bin.length(); i += 4) {
    std::string group = m1_bin.substr(i, 4);
    m1 += binToHex[group];
  }
  
  int e2 = -15;
  for(int i = 0; i < 5; i++) {
    if(e2_bin[i] == '1') {
      e2 += 1 << (4 - i);
    }
  }
  std::string m2 = "";
  for (size_t i = 0; i < m2_bin.length(); i += 4) {
    std::string group = m2_bin.substr(i, 4);
    m2 += binToHex[group];
  }  
  
  std::string type1 = "normal";
  if (e1_bin == "00000") {
    if (m1_bin == "000000000000") {
      type1 = "zero";
    } else {
      type1 = "subnormal";
    }
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=0." << m1 << " " << type1 << std::endl;
  } else if (e1_bin == "11111") {
    if (m1_bin == "000000000000") {
      type1 = "inf";
    } else {
      type1 = "nan";
    }
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=1." << m1 << " " << type1 << std::endl;
  } else {
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=1." << m1 << " " << type1 << std::endl;
  }

  std::string type2 = "normal";
  if (e2_bin == "00000") {
    if (m2_bin == "000000000000") {
      type2 = "zero";
    } else {
      type2 = "subnormal";
    }
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=0." << m2 << " " << type2 << std::endl;
  } else if (e2_bin == "11111") {
    if (m2_bin == "000000000000") {
      type2 = "inf";
    } else {
      type2 = "nan";
    }
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=1." << m2 << " " << type2 << std::endl;
  } else {
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=1." << m2 << " " << type2 << std::endl;
  }

  int value1 = 0;
  for(int i = 0; i < 10; i++) {
    if(m1_bin[i] == '1') {
      value1 += (1 << (9 - i));
    }
  }
  if (e1_bin != "00000") {
    value1 += (1 << 10);
  }
  
  int value2 = 0;
  for(int i = 0; i < 10; i++) {
    if(m2_bin[i] == '1') {
      value2 += (1 << (9 - i));
    }
  }
  if (e2_bin != "00000") {
    value2 += (1 << 10);
  }

  int multiplyValue = value1 * value2;
  int multiplyExp = e1 + e2;
  std::string binMultiplyValue = "";
  for(int i = 0; i < 22; i++) {
    if (multiplyValue >= (1 << (21 - i))) {
      binMultiplyValue += "1";
      multiplyValue -= (1 << (21 - i));
    } else {
      binMultiplyValue += "0";
    }
  }
  std::cout << "Raw: " << binMultiplyValue << " E_raw=" << multiplyExp << std::endl;

  binMultiplyValue += "000000000000";
  int e_norm = multiplyExp;
  std::string fraction;
  if (e_norm < -14) {
    e_norm = -14;
    int expcount = 1;
    fraction = "";
    while (e_norm - expcount > multiplyExp && expcount < 10) {
      expcount++;
      fraction += "0";
    }
    int cnt = 0;
    while (binMultiplyValue[cnt] == '0') cnt++;
    fraction += binMultiplyValue.substr(cnt, 11 - expcount);
  }
  int cnt = 0;
  while (binMultiplyValue[cnt] == '0') cnt++;
  if (multiplyExp >= -14) {
    fraction = binMultiplyValue.substr(cnt + 1, 10);
  } 
  char g = binMultiplyValue[cnt + 11];
  char r = binMultiplyValue[cnt + 12];
  char s = '0';
  cnt += 12;
  for (; cnt < 22; cnt++) {
    if (binMultiplyValue[cnt] == '1') {
      s = '1';
      break;
    }
  }
  bool inexact = (g == '1' || r == '1' || s == '1') ? true : false;
  char sign = (s1 == s2) ? '0' : '1';
  std::string action = "Truncate";
  if (inexact && sign == '0') {
    action = "Up";
  }
  std::cout << "Norm: " << e_norm << " Fraction=" << fraction 
    << " G=" << g << " R=" << r << " S=" << s << " Action=" << action << std::endl;
  
  return 0;
}

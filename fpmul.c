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
    e1 = -14;
    if (m1_bin == "000000000000") {
      type1 = "zero";
    } else {
      type1 = "subnormal";
    }
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=0." << m1 << " " << type1 << std::endl;
  } else if (e1_bin == "11111") {
    e1 = 0;
    if (m1_bin == "000000000000") {
      type1 = "inf";
      std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=1." << m1 << " " << type1 << std::endl;
    } else {
      type1 = "nan";
      std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=0." << m1 << " " << type1 << std::endl;
    }
  } else {
    std::cout << "Op1: S=" << s1 << " E=" << e1 << " M=1." << m1 << " " << type1 << std::endl;
  }

  std::string type2 = "normal";
  if (e2_bin == "00000") {
    e2 = -14;
    if (m2_bin == "000000000000") {
      type2 = "zero";
    } else {
      type2 = "subnormal";
    }
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=0." << m2 << " " << type2 << std::endl;
  } else if (e2_bin == "11111") {
    e2 = 0;
    if (m2_bin == "000000000000") {
      type2 = "inf";
      std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=1." << m2 << " " << type2 << std::endl;
    } else {
      type2 = "nan";
      std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=0." << m2 << " " << type2 << std::endl;
    }
  } else {
    std::cout << "Op2: S=" << s2 << " E=" << e2 << " M=1." << m2 << " " << type2 << std::endl;
  }

  if (type1 == "inf") {
    std::cout << "Raw: N/A" << std::endl;
    std::cout << "Norm: N/A" << std::endl;
    if (type2 == "normal") {
      std::cout << "Result: " << ch1[0] << ch1[1] << ch1[2] << ch1[3] << std::endl;
    } else {
      std::cout << "Result: N/A" << std::endl;
    }
    return 0;
  }
  if (type2 == "inf") {
    std::cout << "Raw: N/A" << std::endl;
    std::cout << "Norm: N/A" << std::endl;
    if (type1 == "normal") {
      std::cout << "Result: " << ch2[0] << ch2[1] << ch2[2] << ch2[3] << std::endl;
    } else {
      std::cout << "Result: N/A" << std::endl;
    }
    return 0;
  }
  if (type1 == "nan" || type2 == "nan") {
    std::cout << "Raw: N/A" << std::endl;
    std::cout << "Norm: N/A" << std::endl;
    std::cout << "Result: N/A" << std::endl;
    return 0;
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

  int e_exact = multiplyExp;
  int e_norm = e_exact;

  if (e_exact <= -14) {
    e_norm = -14;
  }

  std::string fraction;
  char g;
  char r;
  char s = '0';
  int read;

  if (binMultiplyValue[0] == '1') {
    e_exact++;
    fraction = binMultiplyValue.substr(1, 10);
    g = binMultiplyValue[11];
    r = binMultiplyValue[12];
    read = 13;
  } else {
    fraction = binMultiplyValue.substr(2, 10);
    g = binMultiplyValue[12];
    r = binMultiplyValue[13];
    read = 14;
  }
  for (; read < 22; read++) {
    if (binMultiplyValue[read] == '1') {
      s = '1';
      break;
    }
  }

  bool inexact = (g == '1' || r == '1' || s == '1');
  char sign = (s1 == s2)? '0' : '1';
  std::string action = (inexact && sign == '0')? "Up" : "Truncate";
  std::cout << "Norm: E_norm=" << e_norm << " Fraction=" << fraction
    << " G=" << g << " R=" << r << " S=" << s << " Action=" << action << std::endl;

  if (action == "Up") {
    if (fraction == "1111111111") {
      e_exact++;
      fraction = "0000000000";
    } else {
      int value = 0;
      for(int i = 0; i < 10; i++) {
        if(fraction[i] == '1') {
          value += (1 << (9 - i));
        }
      }
      value++;
      fraction = "";
      for(int i = 0; i < 10; i++) {
        if(value >= (1 << (9 - i))) {
          fraction += "1";
          value -= (1 << (9 - i));
        } else {
          fraction += "0";
        }
      }
    }
  }

  std::string bin_result = (sign == '1') ? "1" : "0";
  std::string e_bin = "";
  for(int i = 0; i < 5; i++) {
    int v = e_exact + 14;
    if(v >= (1 << (4 - i))) {
      e_bin += "1";
      v -= (1 << (4 - i));
    } else {
      e_bin += "0";
    }
  }
  bin_result += e_bin;
  bin_result += fraction;

  std::string hex_result = "";
  for (size_t i = 0; i < bin_result.length(); i += 4) {
    std::string group = bin_result.substr(i, 4);
    hex_result += binToHex[group];
  }
  std::cout << "Result: " << hex_result << std::endl;

  return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>

const char* hexToBin(char c) {
  switch (c) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'a': return "1010";
    case 'b': return "1011";
    case 'c': return "1100";
    case 'd': return "1101";
    case 'e': return "1010";
    case 'f': return "1111";
  }
}

const char* binToHex(string s) {
  switch (s) {
    case "0000": return '0';
    case "0001": return '1';
    case "0010": return '2';
    case "0011": return '3';
    case "0100": return '4';
    case "0101": return '5';
    case "0110": return '6';
    case "0111": return '7';
    case "1000": return '8';
    case "1001": return '9';
    case "1010": return 'a';
    case "1011": return 'b';
    case "1100": return 'c';
    case "1101": return 'd';
    case "1010": return 'e';
    case "1111": return 'f';
  }
}

int main(void) { 
  for (const auto& pair : hexToBin) {
    binToHex[pair.second] = pair.first;
  }
  
  char ch1[4];
  char ch2[4];
  scanf("%c%c%c%c ", &ch1[0], &ch1[1], &ch1[2], &ch1[3]);
  scanf("%c%c%c%c\n", &ch2[0], &ch2[1], &ch2[2], &ch2[3]);

  string bin1;
  string bin2;
  for (char c : ch1) {
    bin1 += hexToBin(c);
  }
  for (char c : ch2) {
    bin2 += hexToBin(c);
  }

  char s1 = bin1[0];
  string e1_bin = bin1.substr(1, 5);
  string m1_bin = bin1.substr(6, 10);
  m1_bin = m1_bin + "00";
  char s2 = bin2[0];
  string e2_bin = bin2.substr(1, 5);
  string m2_bin = bin2.substr(6, 10);
  m2_bin = m2_bin + "00";

  int e1 = -15;
  for(int i = 0; i < 5; i++) {
    if(e1_bin[i] == '1') {
      e1 += 1 << (4 - i);
    }
  }
  string m1 = "";
  for (size_t i = 0; i < m1_bin.length(); i += 4) {
    string group = m1_bin.substr(i, 4);
    m1 += binToHex(group);
  }
  
  int e2 = -15;
  for(int i = 0; i < 5; i++) {
    if(e2_bin[i] == '1') {
      e2 += 1 << (4 - i);
    }
  }
  string m2 = "";
  for (size_t i = 0; i < m2_bin.length(); i += 4) {
    string group = m2_bin.substr(i, 4);
    m2 += binToHex(group);
  }  
  
  string type1 = "normal";
  if (e1_bin == "00000") {
    e1 = -14;
    if (m1_bin == "000000000000") {
      type1 = "zero";
    } else {
      type1 = "subnormal";
    }
    printf("Op1: S=%c E=%d M=0.%s %s\n", s1, e1, m1, type1);
  } else if (e1_bin == "11111") {
    e1 = 0;
    if (m1_bin == "000000000000") {
      type1 = "inf";
      printf("Op1: S=%c E=%d M=1.%s %s\n", s1, e1, m1, type1);
    } else {
      type1 = "nan";
      printf("Op1: S=%c E=%d M=0.%s %s\n", s1, e1, m1, type1);
    }
  } else {
    printf("Op1: S=%c E=%d M=1.%s %s\n", s1, e1, m1, type1);
  }

  string type2 = "normal";
  if (e2_bin == "00000") {
    e2 = -14;
    if (m2_bin == "000000000000") {
      type2 = "zero";
    } else {
      type2 = "subnormal";
    }
    printf("Op1: S=%c E=%d M=0.%s %s\n", s1, e1, m1, type1);
  } else if (e2_bin == "11111") {
    e2 = 0;
    if (m2_bin == "000000000000") {
      type2 = "inf";
      printf("Op1: S=%c E=%d M=1.%s %s\n", s1, e1, m1, type1);
    } else {
      type2 = "nan";
      printf("Op1: S=%c E=%d M=0.%s %s\n", s1, e1, m1, type1);
    }
  } else {
    printf("Op1: S=%c E=%d M=1.%s %s\n", s1, e1, m1, type1);
  }

  if (type1 == "inf") {
    printf("Raw: N/A");
    printf("Norm: N/A");
    if (type2 == "normal") {
      printf("Result: %c%c%c%c\n", ch1[0], ch1[1], ch1[2], ch1[3]);
    } else {
      printf("Result: N/A");
    }
    return 0;
  }
  if (type2 == "inf") {
    printf("Raw: N/A");
    printf("Norm: N/A");
    if (type1 == "normal") {
      printf("Result: %c%c%c%c\n", ch2[0], ch2[1], ch2[2], ch2[3]);
    } else {
      printf("Result: N/A");
    }
    return 0;
  }
  if (type1 == "nan" || type2 == "nan") {
    printf("Raw: N/A");
    printf("Norm: N/A");
    printf("Result: N/A");
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
  string binMultiplyValue = "";
  for(int i = 0; i < 22; i++) {
    if (multiplyValue >= (1 << (21 - i))) {
      binMultiplyValue += "1";
      multiplyValue -= (1 << (21 - i));
    } else {
      binMultiplyValue += "0";
    }
  }
  printf("Raw: %s E_raw=%d\n", binMultiplyValue, multiplyExp);

  int e_exact = multiplyExp;
  int e_norm = e_exact;

  if (e_exact <= -14) {
    e_norm = -14;
  }

  string fraction;
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
  string action = (inexact && sign == '0')? "Up" : "Truncate";
  printf("Norm: E_norm=%d Fraction=%s G=%c R=%c S=&c Action=%s\n", e_norm, fraction, g, r, s, action);

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

  string bin_result = (sign == '1') ? "1" : "0";
  string e_bin = "";
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

  string hex_result = "";
  for (size_t i = 0; i < bin_result.length(); i += 4) {
    string group = bin_result.substr(i, 4);
    hex_result += binToHex(group);
  }
  printf("Result: %s\n", hex_result);

  return 0;
}

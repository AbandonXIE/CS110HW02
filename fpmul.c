#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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
    case 'e': return "1110";
    case 'f': return "1111";
    default: return "";
  }
}

char binToHex(const char s[4]) {
    int val = 0;
    for (int i = 0; i < 4; i++) {
        val = val * 2 + (s[i] - '0');
    }
    const char hex[] = "0123456789abcdef";
    return hex[val];
}

int main(void) {   
  char ch1[4];
  char ch2[4];
  scanf("%c%c%c%c ", &ch1[0], &ch1[1], &ch1[2], &ch1[3]);
  scanf("%c%c%c%c\n", &ch2[0], &ch2[1], &ch2[2], &ch2[3]);

  char bin1[17];
  char bin2[17];
  char *p = bin1;
  for (int i = 0; i < 4; i++) {
    const char *bits = hexToBin(ch1[i]);
    strcpy(p, bits);
    p += 4;
  }
  bin1[16] = '\0';
  char *q = bin2;
  for (int i = 0; i < 4; i++) {
    const char *bits = hexToBin(ch2[i]);
    strcpy(q, bits);
    q += 4;
  }
  bin2[16] = '\0';

  char s1 = bin1[0];
  char e1_bin[6];
  strncpy(e1_bin, bin1 + 1, 5);
  e1_bin[5] = '\0';
  char m1_bin[13];
  strncpy(m1_bin, bin1 + 6, 10);
  m1_bin[10] = '0';
  m1_bin[11] = '0';
  m1_bin[12] = '\0';
  char s2 = bin2[0];
  char e2_bin[6];
  strncpy(e2_bin, bin2 + 1, 5);
  e2_bin[5] = '\0';
  char m2_bin[13];
  strncpy(m2_bin, bin2 + 6, 10);
  m2_bin[10] = '0';
  m2_bin[11] = '0';
  m2_bin[12] = '\0';

  int e1 = -15;
  for(int i = 0; i < 5; i++) {
    if(e1_bin[i] == '1') {
      e1 += 1 << (4 - i);
    }
  }
  char m1[4];
  for (int i = 0; i < 3; i ++) {
    char group[5];
    strncpy(group, m1_bin + i * 4, 4);
    group[4] = '\0';
    m1[i] = binToHex(group);
  }
  m1[3] = '\0';
  
  int e2 = -15;
  for(int i = 0; i < 5; i++) {
    if(e2_bin[i] == '1') {
      e2 += 1 << (4 - i);
    }
  }
  char m2[4];
  for (int i = 0; i < 3; i ++) {
    char group[5];
    strncpy(group, m2_bin + i * 4, 4);
    group[4] = '\0';
    m2[i] = binToHex(group);
  }
  m2[3] = '\0';
  
  char type1[10] = "normal";
  if (strcmp(e1_bin, "00000") == 0) {
    e1 = -14;
    if (strcmp(m1_bin, "000000000000") == 0) {
      strcpy(type1, "zero");
    } else {
      strcpy(type1, "subnormal");
    }
    printf("Op1: S=%c E=%d M=0.%s %s\n", s1, e1, m1, type1);
  } else if (strcmp(e1_bin, "11111") == 0) {
    e1 = 0;
    if (strcmp(m1_bin, "000000000000") == 0) {
      strcpy(type1, "inf");
      printf("Op1: S=%c E=%d M=1.%s %s\n", s1, e1, m1, type1);
    } else {
      strcpy(type1, "nan");
      printf("Op1: S=%c E=%d M=0.%s %s\n", s1, e1, m1, type1);
    }
  } else {
    printf("Op1: S=%c E=%d M=1.%s %s\n", s1, e1, m1, type1);
  }

  char type2[10] = "normal";
if (strcmp(e2_bin, "00000") == 0) {
    e2 = -14;
    if (strcmp(m2_bin, "000000000000") == 0) {
      strcpy(type2, "zero");
    } else {
      strcpy(type2, "subnormal");
    }
    printf("Op2: S=%c E=%d M=0.%s %s\n", s2, e2, m2, type2);
  } else if (strcmp(e2_bin, "11111") == 0) {
    e2 = 0;
    if (strcmp(m2_bin, "000000000000") == 0) {
      strcpy(type2, "inf");
      printf("Op2: S=%c E=%d M=1.%s %s\n", s2, e2, m2, type2);
    } else {
      strcpy(type2, "nan");
      printf("Op2: S=%c E=%d M=0.%s %s\n", s2, e2, m2, type2);
    }
  } else {
    printf("Op2: S=%c E=%d M=1.%s %s\n", s2, e2, m2, type2);
  }

  if (strcmp(type1, "inf") == 0) {
    printf("Raw: N/A\n");
    printf("Norm: N/A\n");
    if (strcmp(type2, "normal") == 0) {
      printf("Result: %c%c%c%c\n", ch1[0], ch1[1], ch1[2], ch1[3]);
    } else {
      printf("Result: N/A\n");
    }
    return 0;
  }
  if (strcmp(type2, "inf") == 0) {
    printf("Raw: N/A\n");
    printf("Norm: N/A\n");
    if (strcmp(type1, "normal") == 0) {
      printf("Result: %c%c%c%c\n", ch2[0], ch2[1], ch2[2], ch2[3]);
    } else {
      printf("Result: N/A\n");
    }
    return 0;
  }
  if (strcmp(type1, "nan") ==0 || strcmp(type2, "nan") == 0) {
    printf("Raw: N/A\n");
    printf("Norm: N/A\n");
    printf("Result: N/A\n");
    return 0;
  }

  int value1 = 0;
  for(int i = 0; i < 10; i++) {
    if(m1_bin[i] == '1') {
      value1 += (1 << (9 - i));
    }
  }
  if (strcmp(e1_bin, "00000") != 0) {
    value1 += (1 << 10);
  }
  
  int value2 = 0;
  for(int i = 0; i < 10; i++) {
    if(m2_bin[i] == '1') {
      value2 += (1 << (9 - i));
    }
  }
  if (strcmp(e2_bin, "00000") != 0) {
    value2 += (1 << 10);
  }

  int multiplyValue = value1 * value2;
  int multiplyExp = e1 + e2;
  char binMultiplyValue[23];
  for(int i = 0; i < 22; i++) {
    if (multiplyValue >= (1 << (21 - i))) {
      binMultiplyValue[i] = '1';
      multiplyValue -= (1 << (21 - i));
    } else {
      binMultiplyValue[i] = '0';
    }
  }
  binMultiplyValue[22] = '\0';
  printf("Raw: %s E_raw=%d\n", binMultiplyValue, multiplyExp);

  int e_exact = multiplyExp;
  int e_norm = e_exact;

  if (e_exact <= -14) {
    e_norm = -14;
  }

  char fraction[11];
  char g;
  char r;
  char s = '0';
  int read;

  if (binMultiplyValue[0] == '1') {
    e_exact++;
    strncpy(fraction, binMultiplyValue + 1, 10);
    fraction[10] = 0;
    g = binMultiplyValue[11];
    r = binMultiplyValue[12];
    read = 13;
  } else {
    strncpy(fraction, binMultiplyValue + 2, 10);
    fraction[10] = 0;
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
  char action[10] = "Truncate";
  if (inexact && sign == '0') {
    strcpy(action, "Up");
  }
  printf("Norm: E_norm=%d Fraction=%s G=%c R=%c S=%c Action=%s\n", e_norm, fraction, g, r, s, action);

  if (strcmp(action, "Up") == 0) {
    if (strcmp(fraction, "1111111111") == 0) {
      e_exact++;
      strcpy(fraction, "0000000000");
    } else {
      int value = 0;
      for(int i = 0; i < 10; i++) {
        if(fraction[i] == '1') {
          value += (1 << (9 - i));
        }
      }
      value++;
      for(int i = 0; i < 10; i++) {
        if(value >= (1 << (9 - i))) {
          fraction[i] = '1';
          value -= (1 << (9 - i));
        } else {
          fraction[i] = '0';
        }
      }
    }
  }

  char e_bin[6];
  int v = e_exact + 14;
  for (int i = 0; i < 5; i++) {
      if (v >= (1 << (4 - i))) {
          e_bin[i] = '1';
          v -= (1 << (4 - i));
      } else {
          e_bin[i] = '0';
      }
  }
  e_bin[5] = '\0';
  char bin_result[17];
  int pos = 0;
  bin_result[pos++] = (sign == '1') ? '1' : '0';
  for (int i = 0; i < 5; i++) {
    bin_result[pos++] = e_bin[i];
  }
  for (int i = 0; i < 10; i++) {
    bin_result[pos++] = fraction[i];
  }
  bin_result[pos] = '\0';

  char hex_result[5];
  for (int i = 0; i < 4; i ++) {
    char group[5];
    strncpy(group, bin_result + i * 4, 4);
    group[4] = '\0';
    hex_result[i] = binToHex(group);
  }
  hex_result[5] = '\0';
  printf("Result: %s\n", hex_result);

  return 0;
}

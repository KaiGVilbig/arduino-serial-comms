#include "morse.h";

int char2Morse(const char c) {
  // Upper case letters, compare agains ASCII values
  if ((int)c >= 65 && (int)c <= 90) {
    return (int)c - (int)'A';
  } 
  // Lower case letters
  else if ((int)c >= 97 && (int)c <= 122) {
    return (int)c - (int)'a';
  }
  // Numbers
  else if ((int)c >= 48 && (int)c <= 57) {
    return (int)c - (int)'0' + 26;
  }
  // Special , . ?
  else if (c == ',') { return 36; }
  else if (c == '.') { return 37; }
  else if (c == '?') { return 38; }
  // Space
  else if (c == ' ') { return 100; }
  else { return -1; }
}
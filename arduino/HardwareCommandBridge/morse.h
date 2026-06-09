#pragma once

const int DOT = 1;
const int DASH = 3;
const int LETTER_GAP = 3;
const int WORD_GAP = 7 - LETTER_GAP;
const int MORSE_SPEED = 100;
const int GAP = 50;

const int m_A[] = {DOT, DASH};
const int m_B[] = {DASH, DOT, DOT, DOT};
const int m_C[] = {DASH, DOT, DASH, DOT};
const int m_D[] = {DASH, DOT, DOT};
const int m_E[] = {DOT};
const int m_F[] = {DOT, DOT, DASH, DOT};
const int m_G[] = {DASH, DASH, DOT};
const int m_H[] = {DOT, DOT, DOT, DOT};
const int m_I[] = {DOT, DOT};
const int m_J[] = {DOT, DASH, DASH, DASH};
const int m_K[] = {DASH, DOT, DASH};
const int m_L[] = {DOT, DASH, DOT, DOT};
const int m_M[] = {DASH, DASH};
const int m_N[] = {DASH, DOT};
const int m_O[] = {DASH, DASH, DASH};
const int m_P[] = {DOT, DASH, DASH, DOT};
const int m_Q[] = {DASH, DASH, DOT, DASH};
const int m_R[] = {DOT, DASH, DOT};
const int m_S[] = {DOT, DOT, DOT};
const int m_T[] = {DASH};
const int m_U[] = {DOT, DOT, DASH};
const int m_V[] = {DOT, DOT, DOT, DASH};
const int m_W[] = {DOT, DASH, DASH};
const int m_X[] = {DASH, DOT, DOT, DASH};
const int m_Y[] = {DASH, DOT, DASH, DASH};
const int m_Z[] = {DASH, DASH, DOT, DOT};
const int m_0[] = {DASH, DASH, DASH, DASH, DASH};
const int m_1[] = {DOT, DASH, DASH, DASH, DASH};
const int m_2[] = {DOT, DOT, DASH, DASH, DASH};
const int m_3[] = {DOT, DOT, DOT, DASH, DASH};
const int m_4[] = {DOT, DOT, DOT, DOT, DASH};
const int m_5[] = {DOT, DOT, DOT, DOT, DOT};
const int m_6[] = {DASH, DOT, DOT, DOT, DOT};
const int m_7[] = {DASH, DASH, DOT, DOT, DOT};
const int m_8[] = {DASH, DASH, DASH, DOT, DOT};
const int m_9[] = {DASH, DASH, DASH, DASH, DOT};
const int m_Comma[] = {DOT, DOT, DASH, DOT, DOT};
const int m_Period[] = {DOT, DASH, DOT, DASH, DOT, DASH};
const int m_Quest[] = {DOT, DOT, DASH, DASH, DOT, DOT};

struct MorseChar {
  const int* sequence;
  int length;
};

const MorseChar CHARS[] = {
  {m_A, sizeof(m_A)/sizeof(int)}, 
  {m_B, sizeof(m_B)/sizeof(int)},
  {m_C, sizeof(m_C)/sizeof(int)},
  {m_D, sizeof(m_D)/sizeof(int)},
  {m_E, sizeof(m_E)/sizeof(int)},
  {m_F, sizeof(m_F)/sizeof(int)},
  {m_G, sizeof(m_G)/sizeof(int)},
  {m_H, sizeof(m_H)/sizeof(int)},
  {m_I, sizeof(m_I)/sizeof(int)},
  {m_J, sizeof(m_J)/sizeof(int)},
  {m_K, sizeof(m_K)/sizeof(int)},
  {m_L, sizeof(m_L)/sizeof(int)},
  {m_M, sizeof(m_M)/sizeof(int)},
  {m_N, sizeof(m_N)/sizeof(int)},
  {m_O, sizeof(m_O)/sizeof(int)},
  {m_P, sizeof(m_P)/sizeof(int)},
  {m_Q, sizeof(m_Q)/sizeof(int)},
  {m_R, sizeof(m_R)/sizeof(int)},
  {m_S, sizeof(m_S)/sizeof(int)},
  {m_T, sizeof(m_T)/sizeof(int)},
  {m_U, sizeof(m_U)/sizeof(int)},
  {m_V, sizeof(m_V)/sizeof(int)},
  {m_W, sizeof(m_W)/sizeof(int)},
  {m_X, sizeof(m_X)/sizeof(int)},
  {m_Y, sizeof(m_Y)/sizeof(int)},
  {m_Z, sizeof(m_Z)/sizeof(int)},
  {m_0, sizeof(m_0)/sizeof(int)},
  {m_1, sizeof(m_1)/sizeof(int)},
  {m_2, sizeof(m_2)/sizeof(int)},
  {m_3, sizeof(m_3)/sizeof(int)},
  {m_4, sizeof(m_4)/sizeof(int)},
  {m_5, sizeof(m_5)/sizeof(int)},
  {m_6, sizeof(m_6)/sizeof(int)},
  {m_7, sizeof(m_7)/sizeof(int)},
  {m_8, sizeof(m_8)/sizeof(int)},
  {m_9, sizeof(m_9)/sizeof(int)},
  {m_Comma, sizeof(m_Comma)/sizeof(int)},
  {m_Period, sizeof(m_Period)/sizeof(int)},
  {m_Quest, sizeof(m_Quest)/sizeof(int)}
};

int char2Morse(const char c);
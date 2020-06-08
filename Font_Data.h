// Data file for user example user defined fonts
#ifndef FONTDATA_H
#define FONTDATA_H

MD_MAX72XX::fontType_t BigFontLower[] PROGMEM = 
{
  0,    // 0
  0,    // 1
  0,    // 2
  0,    // 3
  0,    // 4
  0,    // 5
  0,    // 6
  0,    // 7
  0,    // 8
  0,    // 9
  0,    // 10
  0,    // 11
  0,    // 12
  0,    // 13
  0,    // 14
  0,    // 15
  0,    // 16
  0,    // 17
  0,    // 18
  0,    // 19
  0,    // 20
  0,    // 21
  0,    // 22
  0,    // 23
  0,    // 24
  0,    // 25
  0,    // 26
  0,    // 27
  0,    // 28
  0,    // 29
  0,    // 30
  0,    // 31
  4,0,0,0,0,   // 32 - 'Space'
  2,103,103,    // 33 - '!'
  6,0,0,0,0,0,0,    // 34 - '"'
  10,6,6,127,127,6,6,127,127,6,6,    // 35 - '#'
  10,48,112,97,97,255,255,97,115,63,30,    // 36 - '$'
  10,0,96,120,30,7,1,48,120,120,48,    // 37 - '%'
  10,30,63,115,97,97,103,63,28,126,102,    // 38 - '&'
  2,0,0,    // 39 - '''
  5,7,31,60,112,96,    // 40 - '('
  5,96,112,60,31,7,    // 41 - ')'
  10,3,3,1,0,15,15,0,1,3,3,    // 42 - '*'
  10,1,1,1,1,31,31,1,1,1,1,    // 43 - '+'
  2,96,224,    // 44 - ','
  10,1,1,1,1,1,1,1,1,1,1,    // 45 - '-'
  2,96,96,    // 46 - '.'
  8,96,120,30,7,1,0,0,0,    // 47 - '/'
  10,31,63,112,96,96,96,96,112,63,31,  // 48 - '0'
  10,0,0,96,96,127,127,96,96,0,0,     // 49 - '1'
  10,96,112,120,124,110,103,99,97,96,96,   // 50 - '2'
  10,24,56,112,96,96,97,97,113,63,30,   // 51 - '3'
  10,7,7,6,6,6,6,127,127,6,6,    // 52 - '4'
  10,24,56,112,96,96,96,96,112,63,31,   // 53 - '5'
  10,31,63,112,96,96,96,96,113,63,31,  // 54 - '6'
  10,0,0,0,127,127,1,0,0,0,0,     // 55 - '7'
  10,30,63,115,97,97,97,97,115,63,30,  // 56 - '8'
  10,0,0,97,97,113,57,29,15,7,3,   // 57 - '9'
  4,0,12,12,0,    // 58 - ':'
  2, 97,225,    // 59 - ';'
  8,1,3,7,14,28,56,112,96,    // 60 - '<'
  10,12,12,12,12,12,12,12,12,12,12,    // 61 - '='
  8,96,112,56,28,14,7,3,1,    // 62 - '>'
  10,0,0,0,0,111,111,1,0,0,0,    // 63 - '?'
  10,31,63,112,103,111,111,111,108,111,39,    // 64 - '@'
  10,127,127,6,6,6,6,6,6,127,127,   // 65 - 'A'
  10,127,127,97,97,97,97,97,115,63,30,   // 66 - 'B'
  10,31,63,96,96,96,96,96,112,56,24,   // 67 - 'C'
  10,127,127,96,96,96,96,96,112,63,31,   // 68 - 'D'
  10,127,127,97,97,97,97,97,97,96,96,   // 69 - 'E'
  10,127,127,1,1,1,1,1,1,0,0,     // 70 - 'F'
  10,31,63,112,96,96,96,97,113,63,31,    // 71 - 'G'
  10,127,127,1,1,1,1,1,1,127,127,    // 72 - 'H'
  6,96,96,127,127,96,96,    // 73 - 'I'
  8,24,56,112,96,96,112,63,31,    // 74 - 'J'
  10,127,127,3,3,7,14,28,56,112,96,    // 75 - 'K'
  10,127,127,96,96,96,96,96,96,96,96,    // 76 - 'L'
  10,127,127,0,0,0,0,0,0,127,127,    // 77 - 'M'
  10,127,127,0,0,1,7,28,48,127,127,    // 78 - 'N'
  10,31,63,112,96,96,96,96,112,63,31,    // 79 - 'O'
  10,127,127,1,1,1,1,1,1,0,0,    // 80 - 'P'
  10,31,63,112,96,96,108,124,56,127,111,    // 81 - 'Q'
  10,127,127,1,3,7,15,29,57,112,96,    // 82 - 'R'
  10,48,112,97,97,97,97,97,115,63,30,    // 83 - 'S'
  10,0,0,0,0,127,127,0,0,0,0,    // 84 - 'T'
  10,31,63,112,96,96,96,96,112,63,31,    // 85 - 'U'
  10,7,15,28,56,112,112,56,28,15,7,    // 86 - 'V'
  10,31,63,112,120,62,62,120,112,63,31,    // 87 - 'W'
  10,120,124,14,7,3,3,7,14,124,120,    // 88 - 'X'
  10,0,0,0,0,127,127,0,0,0,0,    // 89 - 'Y'
  10,120,124,110,103,99,97,96,96,96,96,    // 90 - 'Z'
  4,127,127,96,96,    // 91 - '['
  8,0,0,0,1,7,30,120,96,    // 92 - '\'
  10,2,6,14,31,63,63,31,14,6,2,    // 94 -//ARROW DOWN
  10,0,0,0,127,127,127,127,0,0,0,    // 94 - '^'        //ARROW
  10,192,192,192,192,192,192,192,192,192,192,    // 95 - '_'
  3,0,0,0,    // 96 - '`'
  10,24,60,102,102,102,102,102,102,127,63,   // 97 - 'a'
  10,127,127,96,96,96,96,96,112,63,31,   // 98 - 'b'
  10,31,63,112,96,96,96,96,112,57,25,   // 99 - 'c'
  10,31,63,112,96,96,96,96,96,127,127,   // 100 - 'd'
  10,31,63,118,102,102,102,102,118,55,19,   // 101 - 'e'
  7,1,127,127,1,1,0,0,     // 102 - 'f'
  10,35,103,238,204,204,204,204,236,127,63,    // 103 - 'g'
  10,127,127,0,0,0,0,0,0,127,127,    // 104 - 'h'
  2,127,127,    // 105 - 'i'
  8,24,56,112,96,96,112,63,31,    // 106 - 'j'
  8,127,127,14,15,31,57,112,96,    // 107 - 'k'
  6,96,96,127,127,96,96,    // 108 - 'l'
  10,127,127,0,0,127,127,0,0,127,127,    // 109 - 'm'
  10,127,127,1,1,0,0,0,0,127,127,    // 110 - 'n'
  10,31,63,112,96,96,96,96,112,63,31,    // 111 - 'o'
  10,255,255,24,24,24,24,24,28,15,7,    // 112 - 'p'
  10,7,15,28,24,24,24,24,24,255,255,    // 113 - 'q'
  10,127,127,3,1,0,0,0,0,1,1,    // 114 - 'r'
  10,49,115,102,102,102,102,102,126,60,24,    // 115 - 's'
  8,0,0,31,63,112,112,56,24,    // 116 - 't'
  10,31,63,112,96,96,96,96,112,63,31,    // 117 - 'u'
  10,7,15,28,56,112,112,56,28,15,7,    // 118 - 'v'
  10,31,63,112,112,62,62,112,112,63,31,    // 119 - 'w'
  10,96,112,57,31,15,15,31,57,112,96,    // 120 - 'x'
  10,3,7,206,204,204,204,204,236,127,63,    // 121 - 'y'
  10,96,112,120,124,110,103,99,97,96,96,    // 122 - 'z'
  6,1,3,31,62,112,96,    // 123 - '{'
  2,255,255,   // 124 - '|'
  6,96,112,62,31,3,1,    // 125 - '}'
  0,    // 126
  0,    // 127
  0,    // 128
  0,    // 129
  0,    // 130
  0,    // 131
  0,    // 132
  0,    // 133
  0,    // 134
  0,    // 135
  0,    // 136
  0,    // 137
  0,    // 138
  0,    // 139
  0,    // 140
  0,    // 141
  0,    // 142
  0,    // 143
  0,    // 144
  0,    // 145
  0,    // 146
  0,    // 147
  0,    // 148
  0,    // 149
  0,    // 150
  0,    // 151
  0,    // 152
  0,    // 153
  0,    // 154
  0,    // 155
  0,    // 156
  0,    // 157
  0,    // 158
  0,    // 159
  0,    // 160
  0,    // 161
  0,    // 162
  0,    // 163
  0,    // 164
  0,    // 165
  0,    // 166
  0,    // 167
  0,    // 168
  0,    // 169
  0,    // 170
  0,    // 171
  0,    // 172
  0,    // 173
  0,    // 174
  0,    // 175
  0,    // 176
  0,    // 177
  0,    // 178
  0,    // 179
  0,    // 180
  0,    // 181
  0,    // 182
  0,    // 183
  0,    // 184
  0,    // 185
  0,    // 186
  0,    // 187
  0,    // 188
  0,    // 189
  0,    // 190
  0,    // 191
  0,    // 192
  0,    // 193
  0,    // 194
  0,    // 195
  0,    // 196
  0,    // 197
  0,    // 198
  0,    // 199
  0,    // 200
  0,    // 201
  0,    // 202
  0,    // 203
  0,    // 204
  0,    // 205
  0,    // 206
  0,    // 207
  0,    // 208
  0,    // 209
  0,    // 210
  0,    // 211
  0,    // 212
  0,    // 213
  0,    // 214
  0,    // 215
  0,    // 216
  0,    // 217
  0,    // 218
  0,    // 219
  0,    // 220
  0,    // 221
  0,    // 222
  0,    // 223
  0,    // 224
  0,    // 225
  0,    // 226
  0,    // 227
  0,    // 228
  0,    // 229
  0,    // 230
  0,    // 231
  0,    // 232
  0,    // 233
  0,    // 234
  0,    // 235
  0,    // 236
  0,    // 237
  0,    // 238
  0,    // 239
  0,    // 240
  0,    // 241
  0,    // 242
  0,    // 243
  0,    // 244
  0,    // 245
  0,    // 246
  0,    // 247
  0,    // 248
  0,    // 249
  0,    // 250
  0,    // 251
  0,    // 252
  0,    // 253
  0,    // 254
  0,    // 255
};


MD_MAX72XX::fontType_t BigFontUpper[] PROGMEM = 
{
  0,    // 0
  0,    // 1
  0,    // 2
  0,    // 3
  0,    // 4
  0,    // 5
  0,    // 6
  0,    // 7
  0,    // 8
  0,    // 9
  0,    // 10
  0,    // 11
  0,    // 12
  0,    // 13
  0,    // 14
  0,    // 15
  0,    // 16
  0,    // 17
  0,    // 18
  0,    // 19
  0,    // 20
  0,    // 21
  0,    // 22
  0,    // 23
  0,    // 24
  0,    // 25
  0,    // 26
  0,    // 27
  0,    // 28
  0,    // 29
  0,    // 30
  0,    // 31
  4,0,0,0,0,   // 32 - 'Space'
  2,254,254,    // 33 - '!'
  6,14,14,0,0,14,14,    // 34 - '"'
  10,96,96,254,254,96,96,254,254,96,96,    // 35 - '#'
  10,120,252,206,134,255,255,134,134,14,12,    // 36 - '$'
  10,12,30,30,12,128,224,120,30,6,0,    // 37 - '%'
  10,0,0,152,252,230,230,60,24,0,0,    // 38 - '&'
  2,14,14,    // 39 - '''
  5,224,248,60,14,6,    // 40 - '('
  5,6,14,60,248,224,    // 41 - ')'
  10,24,184,240,224,254,254,224,240,184,24,    // 42 - '*'
  10,128,128,128,128,248,248,128,128,128,128,    // 43 - '+'
  2,0,0,    // 44 - ','
  10,128,128,128,128,128,128,128,128,128,128,    // 45 - '-'
  2,0,0,    // 46 - '.'
  8,0,0,0,128,224,120,30,6,    // 47 - '/'
  10,248,252,14,6,6,6,6,14,252,248,  // 48 - '0'
  10,0,0,24,28,254,254,0,0,0,0,     // 49 - '1'
  10,24,28,14,6,6,6,134,206,252,120,   // 50 - '2'
  10,24,28,14,6,6,134,134,142,252,120,   // 51 - '3'
  10,128,192,224,112,56,28,254,254,0,0,    // 52 - '4'
  10,126,126,102,102,102,102,102,230,198,134,   // 53 - '5'
  10,248,252,198,198,198,198,198,198,140,8,  // 54 - '6'
  10,6,6,6,6,134,198,230,118,62,30,     // 55 - '7'
  10,56,124,206,134,134,134,134,206,124,56,  // 56 - '8'
  10,120,252,206,134,134,134,134,206,252,248,   // 57 - '9'
  4,0,48,48,0,    // 58 - ':'
  2,128,128,    // 59 - ';'
  8,128,192,224,112,56,28,14,6,    // 60 - '<'
  10,48,48,48,48,48,48,48,48,48,48,    // 61 - '='
  8,6,14,28,56,112,224,192,128,    // 62 - '>'
  10,24,28,14,6,6,134,134,206,252,120,    // 63 - '?'
  10,248,252,14,230,246,246,230,14,252,248,    // 64 - '@'
  10,248,252,14,6,6,6,6,14,252,248,   // 65 - 'A'
  10,254,254,134,134,134,134,134,206,252,120,   // 66 - 'B'
  10,248,252,6,6,6,6,6,14,28,24,   // 67 - 'C'
  10,254,254,6,6,6,6,6,14,252,248,   // 68 - 'D'
  10,254,254,134,134,134,134,134,134,6,6,   // 69 - 'E'
  10,254,254,134,134,134,134,134,134,6,6,     // 70 - 'F'
  10,248,252,14,6,6,6,134,142,156,152,    // 71 - 'G'
  10,254,254,128,128,128,128,128,128,254,254,    // 72 - 'H'
  6,6,6,254,254,6,6,    // 73 - 'I'
  8,6,6,6,6,6,6,254,254,    // 74 - 'J'
  10,254,254,192,192,224,112,56,28,14,6,    // 75 - 'K'
  10,254,254,0,0,0,0,0,0,0,0,    // 76 - 'L'
  10,254,254,28,56,240,240,56,28,254,254,    // 77 - 'M'
  10,254,254,28,112,192,0,0,0,254,254,    // 78 - 'N'
  10,248,252,14,6,6,6,6,14,252,248,    // 79 - 'O'
  10,254,254,134,134,134,134,134,206,252,120,    // 80 - 'P'
  10,248,252,14,6,6,6,6,14,252,248,    // 81 - 'Q'
  10,254,254,134,134,134,134,134,206,252,120,    // 82 - 'R'
  10,120,252,206,134,134,134,134,134,14,12,    // 83 - 'S'
  10,6,6,6,6,254,254,6,6,6,6,    // 84 - 'T'
  10,254,254,0,0,0,0,0,0,254,254,    // 85 - 'U'
  10,254,254,0,0,0,0,0,0,254,254,    // 86 - 'V'
  10,254,254,0,0,0,0,0,0,254,254,    // 87 - 'W'
  10,30,62,48,224,192,192,224,112,62,30,    // 88 - 'X'
  10,30,62,112,224,192,192,224,112,62,30,    // 89 - 'Y'
  10,6,6,6,6,134,198,230,118,62,30,    // 90 - 'Z'
  4,254,254,6,6,    // 91 - '['
  8,6,30,120,224,128,0,0,0,    // 92 - '\'
  10,0,0,0,254,254,254,254,0,0,0,    // 94 - ''         //ARROW DOWN
  10,64,96,112,248,252,252,248,112,96,64,    // 94 -//ARROW UP
  10,0,0,0,0,0,0,0,0,0,0,    // 95 - '_'
  3,6,30,24,    // 96 - '`'
  10,0,192,224,96,96,96,96,224,192,128,   // 97 - 'a'
  10,254,254,96,96,96,96,96,224,192,128,   // 98 - 'b'
  10,128,192,224,96,96,96,96,224,192,128,   // 99 - 'c'
  10,128,192,224,96,96,96,96,96,254,254,   // 100 - 'd'
  10,128,192,224,96,96,96,96,224,192,128,   // 101 - 'e'
  7,128,248,252,142,142,28,24,     // 102 - 'f'
  10,128,192,224,96,96,96,96,96,224,224,    // 103 - 'g'
  10,254,254,96,96,96,96,96,224,192,128,    // 104 - 'h'
  2,236,236,    // 105 - 'i'
  8,0,0,0,0,0,0,230,230,    // 106 - 'j'
  8,254,254,0,0,128,192,224,96,    // 107 - 'k'
  6,6,6,254,254,0,0,    // 108 - 'l'
  10,224,224,96,96,224,224,96,96,224,192,    // 109 - 'm'
  10,224,224,128,192,224,96,96,224,192,128,    // 110 - 'n'
  10,128,192,224,96,96,96,96,224,192,128,    // 111 - 'o'
  10,224,224,96,96,96,96,96,224,192,128,    // 112 - 'p'
  10,128,192,224,96,96,96,96,96,224,224,    // 113 - 'q'
  10,224,224,128,192,224,96,96,224,192,128,    // 114 - 'r'
  10,128,192,96,96,96,96,96,96,192,192,    // 115 - 's'
  8,96,96,254,254,96,96,96,96,    // 116 - 't'
  10,224,224,0,0,0,0,0,0,224,224,    // 117 - 'u'
  10,224,224,0,0,0,0,0,0,224,224,    // 118 - 'v'
  10,224,224,0,0,0,0,0,0,224,224,    // 119 - 'w'
  10,96,224,192,128,0,0,128,192,224,96,    // 120 - 'x'
  10,224,224,0,0,0,0,0,0,224,224,    // 121 - 'y'
  10,96,96,96,96,96,96,224,224,224,96,    // 122 - 'z'
  6,128,192,248,124,14,6,    // 123 - '{'
  2,255,255,   // 124 - '|'
  6,6,14,124,248,192,128,    // 125 - '}'
  0,    // 126
  0,    // 127
  0,    // 128
  0,    // 129
  0,    // 130
  0,    // 131
  0,    // 132
  0,    // 133
  0,    // 134
  0,    // 135
  0,    // 136
  0,    // 137
  0,    // 138
  0,    // 139
  0,    // 140
  0,    // 141
  0,    // 142
  0,    // 143
  0,    // 144
  0,    // 145
  0,    // 146
  0,    // 147
  0,    // 148
  0,    // 149
  0,    // 150
  0,    // 151
  0,    // 152
  0,    // 153
  0,    // 154
  0,    // 155
  0,    // 156
  0,    // 157
  0,    // 158
  0,    // 159
  0,    // 160
  0,    // 161
  0,    // 162
  0,    // 163
  0,    // 164
  0,    // 165
  0,    // 166
  0,    // 167
  0,    // 168
  0,    // 169
  0,    // 170
  0,    // 171
  0,    // 172
  0,    // 173
  0,    // 174
  0,    // 175
  0,    // 176
  0,    // 177
  0,    // 178
  0,    // 179
  0,    // 180
  0,    // 181
  0,    // 182
  0,    // 183
  0,    // 184
  0,    // 185
  0,    // 186
  0,    // 187
  0,    // 188
  0,    // 189
  0,    // 190
  0,    // 191
  0,    // 192
  0,    // 193
  0,    // 194
  0,    // 195
  0,    // 196
  0,    // 197
  0,    // 198
  0,    // 199
  0,    // 200
  0,    // 201
  0,    // 202
  0,    // 203
  0,    // 204
  0,    // 205
  0,    // 206
  0,    // 207
  0,    // 208
  0,    // 209
  0,    // 210
  0,    // 211
  0,    // 212
  0,    // 213
  0,    // 214
  0,    // 215
  0,    // 216
  0,    // 217
  0,    // 218
  0,    // 219
  0,    // 220
  0,    // 221
  0,    // 222
  0,    // 223
  0,    // 224
  0,    // 225
  0,    // 226
  0,    // 227
  0,    // 228
  0,    // 229
  0,    // 230
  0,    // 231
  0,    // 232
  0,    // 233
  0,    // 234
  0,    // 235
  0,    // 236
  0,    // 237
  0,    // 238
  0,    // 239
  0,    // 240
  0,    // 241
  0,    // 242
  0,    // 243
  0,    // 244
  0,    // 245
  0,    // 246
  0,    // 247
  0,    // 248
  0,    // 249
  0,    // 250
  0,    // 251
  0,    // 252
  0,    // 253
  0,    // 254
  0,    // 255
};


#endif

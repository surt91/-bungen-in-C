#include "AES.h"

// s-Box zum Verschlüsseln
static const int s[256] =
 {0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76
 ,0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0
 ,0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15
 ,0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75
 ,0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84
 ,0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf
 ,0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8
 ,0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2
 ,0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73
 ,0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb
 ,0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79
 ,0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08
 ,0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a
 ,0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e
 ,0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf
 ,0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16};

// inverse s-Box zum Entschlüsseln
static const int inv_s[256] =
 {0x52 ,0x09 ,0x6a ,0xd5 ,0x30 ,0x36 ,0xa5 ,0x38 ,0xbf ,0x40 ,0xa3 ,0x9e ,0x81 ,0xf3 ,0xd7 ,0xfb
 ,0x7c ,0xe3 ,0x39 ,0x82 ,0x9b ,0x2f ,0xff ,0x87 ,0x34 ,0x8e ,0x43 ,0x44 ,0xc4 ,0xde ,0xe9 ,0xcb
 ,0x54 ,0x7b ,0x94 ,0x32 ,0xa6 ,0xc2 ,0x23 ,0x3d ,0xee ,0x4c ,0x95 ,0x0b ,0x42 ,0xfa ,0xc3 ,0x4e
 ,0x08 ,0x2e ,0xa1 ,0x66 ,0x28 ,0xd9 ,0x24 ,0xb2 ,0x76 ,0x5b ,0xa2 ,0x49 ,0x6d ,0x8b ,0xd1 ,0x25
 ,0x72 ,0xf8 ,0xf6 ,0x64 ,0x86 ,0x68 ,0x98 ,0x16 ,0xd4 ,0xa4 ,0x5c ,0xcc ,0x5d ,0x65 ,0xb6 ,0x92
 ,0x6c ,0x70 ,0x48 ,0x50 ,0xfd ,0xed ,0xb9 ,0xda ,0x5e ,0x15 ,0x46 ,0x57 ,0xa7 ,0x8d ,0x9d ,0x84
 ,0x90 ,0xd8 ,0xab ,0x00 ,0x8c ,0xbc ,0xd3 ,0x0a ,0xf7 ,0xe4 ,0x58 ,0x05 ,0xb8 ,0xb3 ,0x45 ,0x06
 ,0xd0 ,0x2c ,0x1e ,0x8f ,0xca ,0x3f ,0x0f ,0x02 ,0xc1 ,0xaf ,0xbd ,0x03 ,0x01 ,0x13 ,0x8a ,0x6b
 ,0x3a ,0x91 ,0x11 ,0x41 ,0x4f ,0x67 ,0xdc ,0xea ,0x97 ,0xf2 ,0xcf ,0xce ,0xf0 ,0xb4 ,0xe6 ,0x73
 ,0x96 ,0xac ,0x74 ,0x22 ,0xe7 ,0xad ,0x35 ,0x85 ,0xe2 ,0xf9 ,0x37 ,0xe8 ,0x1c ,0x75 ,0xdf ,0x6e
 ,0x47 ,0xf1 ,0x1a ,0x71 ,0x1d ,0x29 ,0xc5 ,0x89 ,0x6f ,0xb7 ,0x62 ,0x0e ,0xaa ,0x18 ,0xbe ,0x1b
 ,0xfc ,0x56 ,0x3e ,0x4b ,0xc6 ,0xd2 ,0x79 ,0x20 ,0x9a ,0xdb ,0xc0 ,0xfe ,0x78 ,0xcd ,0x5a ,0xf4
 ,0x1f ,0xdd ,0xa8 ,0x33 ,0x88 ,0x07 ,0xc7 ,0x31 ,0xb1 ,0x12 ,0x10 ,0x59 ,0x27 ,0x80 ,0xec ,0x5f
 ,0x60 ,0x51 ,0x7f ,0xa9 ,0x19 ,0xb5 ,0x4a ,0x0d ,0x2d ,0xe5 ,0x7a ,0x9f ,0x93 ,0xc9 ,0x9c ,0xef
 ,0xa0 ,0xe0 ,0x3b ,0x4d ,0xae ,0x2a ,0xf5 ,0xb0 ,0xc8 ,0xeb ,0xbb ,0x3c ,0x83 ,0x53 ,0x99 ,0x61
 ,0x17 ,0x2b ,0x04 ,0x7e ,0xba ,0x77 ,0xd6 ,0x26 ,0xe1 ,0x69 ,0x14 ,0x63 ,0x55 ,0x21 ,0x0c ,0x7d};

// vielen Dank an http://en.wikipedia.org/wiki/Rijndael_S-box

static const int mds[4][4] =
{
    { 2,3,1,1 },
    { 1,2,3,1 },
    { 1,1,2,3 },
    { 3,1,1,2 }
};

static const int inv_mds[4][4] =
{
    { 0x0e, 0x0b, 0x0d, 0x09 },
    { 0x09, 0x0e, 0x0b, 0x0d },
    { 0x0d, 0x09, 0x0e, 0x0b },
    { 0x0b, 0x0d, 0x09, 0x0e }
};

static const int rcon[4][10] =
{
    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

static const int exptable[256] =
 {  0x01, 0x03, 0x05, 0x0f, 0x11, 0x33, 0x55, 0xff, 0x1a, 0x2e, 0x72, 0x96, 0xa1, 0xf8, 0x13, 0x35,
    0x5f, 0xe1, 0x38, 0x48, 0xd8, 0x73, 0x95, 0xa4, 0xf7, 0x02, 0x06, 0x0a, 0x1e, 0x22, 0x66, 0xaa,
    0xe5, 0x34, 0x5c, 0xe4, 0x37, 0x59, 0xeb, 0x26, 0x6a, 0xbe, 0xd9, 0x70, 0x90, 0xab, 0xe6, 0x31,
    0x53, 0xf5, 0x04, 0x0c, 0x14, 0x3c, 0x44, 0xcc, 0x4f, 0xd1, 0x68, 0xb8, 0xd3, 0x6e, 0xb2, 0xcd,
    0x4c, 0xd4, 0x67, 0xa9, 0xe0, 0x3b, 0x4d, 0xd7, 0x62, 0xa6, 0xf1, 0x08, 0x18, 0x28, 0x78, 0x88,
    0x83, 0x9e, 0xb9, 0xd0, 0x6b, 0xbd, 0xdc, 0x7f, 0x81, 0x98, 0xb3, 0xce, 0x49, 0xdb, 0x76, 0x9a,
    0xb5, 0xc4, 0x57, 0xf9, 0x10, 0x30, 0x50, 0xf0, 0x0b, 0x1d, 0x27, 0x69, 0xbb, 0xd6, 0x61, 0xa3,
    0xfe, 0x19, 0x2b, 0x7d, 0x87, 0x92, 0xad, 0xec, 0x2f, 0x71, 0x93, 0xae, 0xe9, 0x20, 0x60, 0xa0,
    0xfb, 0x16, 0x3a, 0x4e, 0xd2, 0x6d, 0xb7, 0xc2, 0x5d, 0xe7, 0x32, 0x56, 0xfa, 0x15, 0x3f, 0x41,
    0xc3, 0x5e, 0xe2, 0x3d, 0x47, 0xc9, 0x40, 0xc0, 0x5b, 0xed, 0x2c, 0x74, 0x9c, 0xbf, 0xda, 0x75,
    0x9f, 0xba, 0xd5, 0x64, 0xac, 0xef, 0x2a, 0x7e, 0x82, 0x9d, 0xbc, 0xdf, 0x7a, 0x8e, 0x89, 0x80,
    0x9b, 0xb6, 0xc1, 0x58, 0xe8, 0x23, 0x65, 0xaf, 0xea, 0x25, 0x6f, 0xb1, 0xc8, 0x43, 0xc5, 0x54,
    0xfc, 0x1f, 0x21, 0x63, 0xa5, 0xf4, 0x07, 0x09, 0x1b, 0x2d, 0x77, 0x99, 0xb0, 0xcb, 0x46, 0xca,
    0x45, 0xcf, 0x4a, 0xde, 0x79, 0x8b, 0x86, 0x91, 0xa8, 0xe3, 0x3e, 0x42, 0xc6, 0x51, 0xf3, 0x0e,
    0x12, 0x36, 0x5a, 0xee, 0x29, 0x7b, 0x8d, 0x8c, 0x8f, 0x8a, 0x85, 0x94, 0xa7, 0xf2, 0x0d, 0x17,
    0x39, 0x4b, 0xdd, 0x7c, 0x84, 0x97, 0xa2, 0xfd, 0x1c, 0x24, 0x6c, 0xb4, 0xc7, 0x52, 0xf6, 0x01 };

static const int logtable[256] =
 {  0x00, 0xff, 0x19, 0x01, 0x32, 0x02, 0x1a, 0xc6, 0x4b, 0xc7, 0x1b, 0x68, 0x33, 0xee, 0xdf, 0x03,
    0x64, 0x04, 0xe0, 0x0e, 0x34, 0x8d, 0x81, 0xef, 0x4c, 0x71, 0x08, 0xc8, 0xf8, 0x69, 0x1c, 0xc1,
    0x7d, 0xc2, 0x1d, 0xb5, 0xf9, 0xb9, 0x27, 0x6a, 0x4d, 0xe4, 0xa6, 0x72, 0x9a, 0xc9, 0x09, 0x78,
    0x65, 0x2f, 0x8a, 0x05, 0x21, 0x0f, 0xe1, 0x24, 0x12, 0xf0, 0x82, 0x45, 0x35, 0x93, 0xda, 0x8e,
    0x96, 0x8f, 0xdb, 0xbd, 0x36, 0xd0, 0xce, 0x94, 0x13, 0x5c, 0xd2, 0xf1, 0x40, 0x46, 0x83, 0x38,
    0x66, 0xdd, 0xfd, 0x30, 0xbf, 0x06, 0x8b, 0x62, 0xb3, 0x25, 0xe2, 0x98, 0x22, 0x88, 0x91, 0x10,
    0x7e, 0x6e, 0x48, 0xc3, 0xa3, 0xb6, 0x1e, 0x42, 0x3a, 0x6b, 0x28, 0x54, 0xfa, 0x85, 0x3d, 0xba,
    0x2b, 0x79, 0x0a, 0x15, 0x9b, 0x9f, 0x5e, 0xca, 0x4e, 0xd4, 0xac, 0xe5, 0xf3, 0x73, 0xa7, 0x57,
    0xaf, 0x58, 0xa8, 0x50, 0xf4, 0xea, 0xd6, 0x74, 0x4f, 0xae, 0xe9, 0xd5, 0xe7, 0xe6, 0xad, 0xe8,
    0x2c, 0xd7, 0x75, 0x7a, 0xeb, 0x16, 0x0b, 0xf5, 0x59, 0xcb, 0x5f, 0xb0, 0x9c, 0xa9, 0x51, 0xa0,
    0x7f, 0x0c, 0xf6, 0x6f, 0x17, 0xc4, 0x49, 0xec, 0xd8, 0x43, 0x1f, 0x2d, 0xa4, 0x76, 0x7b, 0xb7,
    0xcc, 0xbb, 0x3e, 0x5a, 0xfb, 0x60, 0xb1, 0x86, 0x3b, 0x52, 0xa1, 0x6c, 0xaa, 0x55, 0x29, 0x9d,
    0x97, 0xb2, 0x87, 0x90, 0x61, 0xbe, 0xdc, 0xfc, 0xbc, 0x95, 0xcf, 0xcd, 0x37, 0x3f, 0x5b, 0xd1,
    0x53, 0x39, 0x84, 0x3c, 0x41, 0xa2, 0x6d, 0x47, 0x14, 0x2a, 0x9e, 0x5d, 0x56, 0xf2, 0xd3, 0xab,
    0x44, 0x11, 0x92, 0xd9, 0x23, 0x20, 0x2e, 0x89, 0xb4, 0x7c, 0xb8, 0x26, 0x77, 0x99, 0xe3, 0xa5,
    0x67, 0x4a, 0xed, 0xde, 0xc5, 0x31, 0xfe, 0x18, 0x0d, 0x63, 0x8c, 0x80, 0xc0, 0xf7, 0x70, 0x07 };

static const char hextable[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

static char * AESKeyGen(char *schluessel)
{
    int i;
    //~ char schluessel[32];
    //~ srand ( time(NULL) );
    for(i=0; i<32; i++){
        schluessel[i] = hextable[rand() % 15];
    }
    schluessel[32] = '\0';
    return schluessel;
}

//////////////////////////////////////////////////////////////////////////////
// http://www.codeplanet.eu/tutorials/cpp/51-advanced-encryption-standard.html
/**
 * Fast multiply two numbers in the GF(2^8) finite field defined
 * using a logarithm and exponentiation table.
 */
static uint8_t galois_fast_multiplication(uint8_t a, uint8_t b)
{
    return ((a && b) ? exptable[(logtable[a] + logtable[b]) % 255] : 0);
}

static void mixColumn(uint8_t *column, char inv)
{
    uint8_t cpy[4];
    int i;


    for(i = 0; i < 4; i++) {
        cpy[i] = column[i];
    }

    column[0] = galois_fast_multiplication(cpy[0], inv ? 0x0e : 0x02) ^
                galois_fast_multiplication(cpy[3], inv ? 0x09 : 0x01) ^
                galois_fast_multiplication(cpy[2], inv ? 0x0d : 0x01) ^
                galois_fast_multiplication(cpy[1], inv ? 0x0b : 0x03);

    column[1] = galois_fast_multiplication(cpy[1], inv ? 0x0e : 0x02) ^
                galois_fast_multiplication(cpy[0], inv ? 0x09 : 0x01) ^
                galois_fast_multiplication(cpy[3], inv ? 0x0d : 0x01) ^
                galois_fast_multiplication(cpy[2], inv ? 0x0b : 0x03);

    column[2] = galois_fast_multiplication(cpy[2], inv ? 0x0e : 0x02) ^
                galois_fast_multiplication(cpy[1], inv ? 0x09 : 0x01) ^
                galois_fast_multiplication(cpy[0], inv ? 0x0d : 0x01) ^
                galois_fast_multiplication(cpy[3], inv ? 0x0b : 0x03);

    column[3] = galois_fast_multiplication(cpy[3], inv ? 0x0e : 0x02) ^
                galois_fast_multiplication(cpy[2], inv ? 0x09 : 0x01) ^
                galois_fast_multiplication(cpy[1], inv ? 0x0d : 0x01) ^
                galois_fast_multiplication(cpy[0], inv ? 0x0b : 0x03);
}

static void makeColumn(int state[4][4], char inv)
{
    int i, j;
    uint8_t column[4];

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            column[j] = state[j][i];
        }

        inv ? mixColumn(column,1) : mixColumn(column,0);

        for (j = 0; j < 4; j++)
        {
            state[j][i] = column[j];
        }
    }
}

static void mixColumns(int state[4][4])
{
    makeColumn(state,0);
}

//static void invMixColumns(int state[4][4])
//{
//    makeColumn(state,1);
//}
// http://www.codeplanet.eu/tutorials/cpp/51-advanced-encryption-standard.html
//////////////////////////////////////////////////////////////////////////////

static void leftshift(int vektor[4],int anzahl)
{
    int i, k;
    for(i=0;i<anzahl;i++)
    {
        k = vektor[0];
        vektor[0]=vektor[1];
        vektor[1]=vektor[2];
        vektor[2]=vektor[3];
        vektor[3]=k;
    }
}

//static void rightshift(int vektor[4],int anzahl)
//{
//    int i, k;
//    for(i=0;i<anzahl;i++)
//    {
//        k = vektor[3];
//        vektor[3]=vektor[2];
//        vektor[2]=vektor[1];
//        vektor[1]=vektor[0];
//        vektor[0]=k;
//    }
//}

static void schluesselErweitern(int key[4][44])
{
    int spalten, zeilen, tmp[4],n,k;

    for(spalten=4;spalten<44;)
    {
        for(zeilen=0;zeilen<4;zeilen++)
        {
            tmp[zeilen] = key[zeilen][spalten-1];
        }
        leftshift(tmp,1);
        for(n=0;n<4;n++)
        {
            tmp[n] = s[tmp[n]];
        }
        for(zeilen=0;zeilen<4;zeilen++)
        {
            key[zeilen][spalten] = key[zeilen][spalten-4] ^ tmp[zeilen] ^ rcon[zeilen][(spalten/4)-1];
        }
        spalten++;
        for(k=0;k<3;k++,spalten++)
        {
            for(zeilen=0;zeilen<4;zeilen++)
            {
                key[zeilen][spalten] = key[zeilen][spalten-4] ^ key[zeilen][spalten-1];
            }
        }
    }
}

static void sub(int array[4][4])
{
    int zeilen, spalten;
    for(zeilen=0;zeilen<4;zeilen++)
    {
        for(spalten=0;spalten<4;spalten++)
        {
            array[zeilen][spalten] = s[array[zeilen][spalten]];
        }
    }
}

//static void inv_sub(int array[4][4])
//{
//    int zeilen, spalten;
//    for(zeilen=0;zeilen<4;zeilen++)
//    {
//        for(spalten=0;spalten<4;spalten++)
//        {
//            array[zeilen][spalten] = inv_s[array[zeilen][spalten]];
//        }
//    }
//}

//~ void erase_first_n_chars()
void AES_encrypt_start(char *input_key, char *input_text)
{
//    static char message[1024 + 2]; // + 2 because of newline and null
//    char schluessel[33];
    //~ if(!strlen(input_key) || !strlen(input_text))
    //~ {
        //~ printf("Gib den Schlüssel 128 Bit ein in hex (32 Zeichen; zb '%s') oder '0' für einen zufälligen Schlüssel.", AESKeyGen(schluessel));
        //~ fgets(input_key, 32, stdin);
        //~ printf("%s\n",input_key);
        //~ if(strlen(input_key) != 32)
        //~ {
            //~ while(strlen(input_key) != 32 && ! strcmp(input_key, "0"))
            //~ {
                //~ printf("Der Schlüssel ist keine 32 Hex Zeichen (128 Bit) lang\n versuchs nochmal, oder gebe '0'' ein für einen automatisch generierten Schlüssel\n");
                //~ scanf("%s", input_key);
            //~ }
        //~ }
        //~ if(input_key=="0")
        //~ {
            //~ input_key = AESKeyGen(schluessel);
            //~ printf("zufälliger Schlüssel:\n%s\n", input_key);
        //~ }
        //~ printf("Gib jetzt die zu verschlüsselnde Nachricht ein.\n");
        //~ fgets(message, sizeof(message), stdin);
        //~ input_text = message;
        //~ printf("Der zu verschlüsselnde Text:\n%s\n",input_text);
    //~ }
    //~ AES_encrypt(input_key, input_text);

    AES_encrypt("65ED361DDA84619DE6A380591E0C1E470\0", "Hallo Welt\0");
}

void AES_encrypt(char *input_key, char *input_text)
{
    char block[16+1], *keyinput, *textinput, tmp2[16+1], *cipher;
    char schluessel[33];
    int k,zeilen,spalten,keyspalten;
    unsigned i;
    char tmp3[2+1];
    int array[4][4], tmp[4], key[4][44];
    int round;
    char **dst;
    char *b;
    char finished;

    textinput=input_text;
    if(!strcmp(input_key,"0"))
    {
        printf("zufaelliger schluesel");
        input_key = AESKeyGen(schluessel);
    }

    /************************************
    /////////////////////////////////////
    //textinput=ersetze_uml(textinput);
    /////////////////////////////////////
    // aktivieren, wenn Umlaute und andere nicht Ascii Zeichen kodiert werden sollen
    /////////////////////////////////////
    ************************************/
    //~ textinput=ersetze_uml(textinput);

    keyinput = input_key;

    for(zeilen=0;zeilen<4;zeilen++)
    {
        for(spalten=0;spalten<4;spalten++)
        {
            tmp3[0] = keyinput[0];
            tmp3[1] = keyinput[1];
            tmp3[2] = '\0';

            keyinput = keyinput+2;

            k=strtol(tmp3,NULL,16);
            key[zeilen][spalten]=k;
        }
    }
    k=0;
    // Schlüssel erweitern
    schluesselErweitern(key);

    // Verschlüsselungsalgorithmus, bis kein Text mehr in der Warteschlange ist:
    finished = 0;
    while(!finished)
    {
        for(i = 0; i<16; i++)
        {
            if(textinput[i]=='\0')
                break;
        }
        memset(block, '\0', 16);
        memcpy(block, textinput, i-1);
        block[16]='\0';

        dst = &textinput;
        if(strlen(textinput)>16)
        {
            // verschiebe textinput um 16 nach links
            for ( i = 16; textinput[i]!='\0'; i++ )
            {
                **dst = textinput[i];
                dst++;
            }
            *dst = '\0';
        }
        else
        {
            finished = 1;
        }

        b=block;
        for(i=0;i<strlen(b);i++)
        {
            memset(tmp3, '\0', 3);
            sprintf(tmp3,"%x",b[i]);
            tmp2[2*i] = tmp3[0];
            tmp2[2*i+1] = tmp3[1];
        }

        for(zeilen=0;zeilen<4;zeilen++)
            for(spalten=0;spalten<4;spalten++)
                array[zeilen][spalten] = 0;

        for(zeilen=0;zeilen<4;zeilen++)
        {
            for(spalten=0;spalten<4;spalten++)
            {
                memmove(tmp3, tmp2+2*(zeilen+spalten), 2);
                array[zeilen][spalten] = strtol(tmp3,NULL,16);
            }
        }

        // Vorrunde
        ///////////
        //Klartext wird mit dem Schlüssel verXORt
        for(zeilen=0;zeilen<4;zeilen++)
        {
            for(spalten=0;spalten<4;spalten++)
            {
                array[zeilen][spalten] ^= key[zeilen][spalten];
            }
        }

        // Hauptrunden
        //////////////
        //substiturieren
        //line-shift
        //column-shift
        //erweiterterschlüssel-XOR
        //9 mal
        for(round=1;round<=9;round++)
        {
            //mit sBox substituieren
            sub(array);

            // Array Zeilen um ihren Index nach links verschieben (zyklisch)
            for(zeilen=1;zeilen<4;zeilen++)
            {
                for(spalten=0;spalten<4;spalten++)
                {
                    tmp[spalten] = array[zeilen][spalten];
                }
                leftshift(tmp,zeilen);
                for(spalten=0;spalten<4;spalten++)
                {
                    array[zeilen][spalten] = tmp[spalten];
                }
            }

            //spalten-Mix
            mixColumns(array);

            //Spalte für Spalte XORn
            // mit dem erweiterten
            //128bit schlüssel
            for (keyspalten=round*4,spalten=0;keyspalten<(round*4+4);keyspalten++,spalten++)
            {
                for(zeilen=0;zeilen<4;zeilen++)
                {
                    array[zeilen][spalten] ^= key[zeilen][keyspalten];
                }
            }
        }

        // Schlussrunde
        ///////////////
        //substituieren
        //line-shift
        //Key-XOR

        //mit sBox substituieren
        sub(array);

        // Array Zeilen um ihren Index nach links verschieben (zyklisch)
        for(zeilen=1;zeilen<4;zeilen++)
        {
            for(spalten=0;spalten<4;spalten++)
            {
                tmp[spalten] = array[zeilen][spalten];
            }
            leftshift(tmp,zeilen);
            for(spalten=0;spalten<4;spalten++)
            {
                array[zeilen][spalten] = tmp[spalten];
            }
        }

        //mit dem Schlüssel verXORn
        for (keyspalten=40,spalten=0;keyspalten<44;keyspalten++,spalten++)
        {
            for(zeilen=0;zeilen<4;zeilen++)
            {
                array[zeilen][spalten] ^= key[zeilen][keyspalten];
            }
        }

        //Ausgeben
        cipher = (char *) calloc(1000, sizeof(char));
        for(zeilen=0;zeilen<4;zeilen++)
        {
                for(spalten=0;spalten<4;spalten++)
                {
                    sprintf(tmp3,"%x",array[zeilen][spalten]);
                    strcat(cipher, tmp3);
                }
        }
    }

    printf("\n%s\n",cipher);
}

//~ void AES_decrypt(string input_key, string input_text)
//~ {
    //~ string block,keyinput,textinput,tmp2,cipher, klartext;
    //~ int i,k,zeilen,spalten,keyspalten;
    //~ string temp;
    //~ int array[4][4], tmp[4], key[4][44], roundKey[4][4];
//~
    //~ if(input_key.empty() || input_text.empty())
    //~ {
        //~ cout << "Gib den Schlüssel 128Bit ein in hex (32 Zeichen; zb '" << AESKeyGen() << "')." << endl;
        //~ cin >> input_key;
        //~ if(input_key.length() != 32)
        //~ {
            //~ while(input_key.length() != 32 && input_key != "0")
            //~ {
                //~ cout << "Der Schlüssel ist keine 32 Hex Zeichen (128 Bit) lang\n versuchs nochmal" << endl;
                //~ cin >> input_key;
            //~ }
        //~ }
        //~ cout << "Gib jetzt die zu entschlüsselnde Nachricht ein." << endl;
        //~ cin >> temp;   //Weil "cin" immer an leerzeichenscheitert und "getline" sofort abbricht, hilft dieser kleine workaround aus
        //~ getline(cin, input_text);
        //~ input_text = temp.append(input_text);
    //~ }
    //~ textinput = input_text;
//~
    //~ for(zeilen=0;zeilen<4;zeilen++)
    //~ {
        //~ for(spalten=0;spalten<4;spalten++)
        //~ {
            //~ string tmp;
            //~ tmp=input_key.substr(0,2);
            //~ input_key.erase(0,2);
            //~ k=strtol(tmp.c_str(),NULL,16);
            //~ key[zeilen][spalten]=k;
        //~ }
    //~ }
    //~ // Schlüssel erweitern
    //~ schluesselErweitern(key);
//~
    //~ while(!(textinput.empty()))
    //~ {
        //~ int round;
        //~ block=textinput.substr(0,32);
        //~ textinput.erase(0,32);
        //~ i=0;
        //~ for(zeilen=0;zeilen<4;zeilen++)
        //~ {
            //~ for(spalten=0;spalten<4;spalten++)
            //~ {
                //~ string tmp2;
                //~ tmp2=block.substr(0,2);
                //~ block.erase(0,2);
                //~ array[zeilen][spalten] = strtol(tmp2.c_str(),NULL,16);
            //~ }
        //~ }
//~
        //~ // Vorrunde
        //~ ///////////
        //~ //Klartext wird mit dem Schlüssel verXORt
//~
        //~ for (keyspalten=43,spalten=3;keyspalten>=40;keyspalten--,spalten--)
        //~ {
            //~ for(zeilen=0;zeilen<4;zeilen++)
            //~ {
                //~ array[zeilen][spalten] ^= key[zeilen][keyspalten];
            //~ }
        //~ }
//~
        //~ // Hauptrunden
        //~ //////////////
        //~ //substiturieren
        //~ //line-shift
        //~ //column-mix
        //~ //erweiterterschlüssel-XOR
        //~ //x9
//~
        //~ for(round=9;round>0;round--)
        //~ {
//~
            //~ // Array Zeilen um ihren Index nach rechts verschieben (zyklisch)
            //~ for(zeilen=1;zeilen<4;zeilen++)
            //~ {
                //~ for(spalten=0;spalten<4;spalten++)
                //~ {
                    //~ tmp[spalten] = array[zeilen][spalten];
                //~ }
                //~ rightshift(tmp,zeilen);
                //~ for(spalten=0;spalten<4;spalten++)
                //~ {
                    //~ array[zeilen][spalten] = tmp[spalten];
                //~ }
            //~ }
            //~ //mit sBox substituieren
            //~ inv_sub(array);
//~
            //~ //spalten-Mix
            //~ invMixColumns(array);
//~
            //~ //Spalte für Spalte XORn
            //~ // mit dem erweitertem Schlüssel
            //~ //128bit schlüssel
//~
            //~ for (keyspalten=round*4+3,spalten=3;keyspalten>=(round*4);keyspalten--,spalten--)
            //~ {
                //~ for(zeilen=0;zeilen<4;zeilen++)
                //~ {
                    //~ roundKey[zeilen][spalten]=key[zeilen][keyspalten];
                //~ }
            //~ }
//~
            //~ invMixColumns(roundKey);
//~
            //~ for(zeilen=0;zeilen<4;zeilen++)
            //~ {
                //~ for(spalten=0;spalten<4;spalten++)
                //~ {
                   //~ array[zeilen][spalten] ^= roundKey[zeilen][spalten];
                //~ }
            //~ }
        //~ }
//~
        //~ // Schlussrunde
        //~ ///////////////
        //~ //substituieren
        //~ //line-shift
        //~ //Key-XOR
//~
        //~ //mit sBox substituieren
        //~ inv_sub(array);
//~
        //~ // Array Zeilen um ihren Index nach rechts verschieben (zyklisch)
        //~ for(zeilen=1;zeilen<4;zeilen++)
        //~ {
            //~ for(spalten=0;spalten<4;spalten++)
            //~ {
                //~ tmp[spalten] = array[zeilen][spalten];
            //~ }
            //~ rightshift(tmp,zeilen);
            //~ for(spalten=0;spalten<4;spalten++)
            //~ {
                //~ array[zeilen][spalten] = tmp[spalten];
            //~ }
        //~ }
//~
        //~ // add roundKey XOR
        //~ for(zeilen=0;zeilen<4;zeilen++)
        //~ {
            //~ for(spalten=0;spalten<4;spalten++)
            //~ {
                //~ array[zeilen][spalten] ^= key[zeilen][spalten];
            //~ }
        //~ }
//~
        //~ for(zeilen=0;zeilen<4;zeilen++)
        //~ {
            //~ for(spalten=0;spalten<4;spalten++)
            //~ {
                //~ klartext.append<int>(1,array[zeilen][spalten]);
            //~ }
        //~ }
    //~ }
//~
    //~ //klartext.replace(QString ("&ouml;"), QString("ö"));
    //~ //klartext.replace(QString ("&auml;"), QString("ä"));
    //~ //klartext.replace(QString ("&uuml;"), QString("ü"));
    //~ //klartext.replace(QString ("&szlig;"), QString("ß"));
//~
    //~ /************************************
    //~ /////////////////////////////////////
    //~ //klartext=inv_ersetze_uml(klartext);
    //~ /////////////////////////////////////
    //~ // aktivieren, wenn Umlaute und andere nicht Ascii Zeichen kodiert werden sollen
    //~ /////////////////////////////////////
    //~ ************************************/
    //~ klartext=inv_ersetze_uml(klartext);
//~
//~ //    cout << endl << endl;
//~ //    cout << "Nachricht:\n" << klartext<< endl;
//~ //    cout << endl;
    //~ cout << klartext<< endl;
//~ }

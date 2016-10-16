#include "ID3Tag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GENRE_0 "Blues"
#define GENRE_1 "Classic Rock"
#define GENRE_2 "Country"
#define GENRE_3 "Dance"
#define GENRE_4 "Disco"
#define GENRE_5 "Funk"
#define GENRE_6 "Grunge"
#define GENRE_7 "Hip-Hop"
#define GENRE_8 "Jazz"
#define GENRE_9 "Metal"
#define GENRE_10 "New Age"
#define GENRE_11 "Oldies"
#define GENRE_12 "Other"
#define GENRE_13 "Pop"
#define GENRE_14 "R&B"
#define GENRE_15 "Rap"
#define GENRE_16 "Reggae"
#define GENRE_17 "Rock"
#define GENRE_18 "Techno"
#define GENRE_19 "Industrial"
#define GENRE_20 "Alternative"
#define GENRE_21 "Ska"
#define GENRE_22 "Death Metal"
#define GENRE_23 "Pranks"
#define GENRE_24 "Soundtrack"
#define GENRE_25 "Euro-Techno"
#define GENRE_26 "Ambient"
#define GENRE_27 "Trip-Hop"
#define GENRE_28 "Vocal"
#define GENRE_29 "Jazz+Funk"
#define GENRE_30 "Fusion"
#define GENRE_31 "Trance"
#define GENRE_32 "Classical"
#define GENRE_33 "Instrumental"
#define GENRE_34 "Acid"
#define GENRE_35 "House"
#define GENRE_36 "Game"
#define GENRE_37 "Sound Clip"
#define GENRE_38 "Gospel"
#define GENRE_39 "Noise"
#define GENRE_40 "Alternative Rock"
#define GENRE_41 "Bass"
#define GENRE_42 "Soul"
#define GENRE_43 "Punk"
#define GENRE_44 "Space"
#define GENRE_45 "Meditative"
#define GENRE_46 "Instrumental Pop"
#define GENRE_47 "Instrumental Rock"
#define GENRE_48 "Ethnic"
#define GENRE_49 "Gothic"
#define GENRE_50 "Darkwave"
#define GENRE_51 "Techno-Industrial"
#define GENRE_52 "Electronic"
#define GENRE_53 "Pop-Folk"
#define GENRE_54 "Eurodance"
#define GENRE_55 "Dream"
#define GENRE_56 "Southern Rock"
#define GENRE_57 "Comedy"
#define GENRE_58 "Cult"
#define GENRE_59 "Gangsta"
#define GENRE_60 "Top 40"
#define GENRE_61 "Christian Rap"
#define GENRE_62 "Pop/Funk"
#define GENRE_63 "Jungle"
#define GENRE_64 "Native US"
#define GENRE_65 "Cabaret"
#define GENRE_66 "New Wave"
#define GENRE_67 "Psychadelic"
#define GENRE_68 "Rave"
#define GENRE_69 "Showtunes"
#define GENRE_70 "Trailer"
#define GENRE_71 "Lo-Fi"
#define GENRE_72 "Tribal"
#define GENRE_73 "Acid Punk"
#define GENRE_74 "Acid Jazz"
#define GENRE_75 "Polka"
#define GENRE_76 "Retro"
#define GENRE_77 "Musical"
#define GENRE_78 "Rock & Roll"
#define GENRE_79 "Hard Rock"
#define GENRE_80 "Folk"
#define GENRE_81 "Folk-Rock"
#define GENRE_82 "National Folk"
#define GENRE_83 "Swing"
#define GENRE_84 "Fast Fusion"
#define GENRE_85 "Bebob"
#define GENRE_86 "Latin"
#define GENRE_87 "Revival"
#define GENRE_88 "Celtic"
#define GENRE_89 "Bluegrass"
#define GENRE_90 "Avantgarde"
#define GENRE_91 "Gothic Rock"
#define GENRE_92 "Progressive Rock"
#define GENRE_93 "Psychedelic Rock"
#define GENRE_94 "Symphonic Rock"
#define GENRE_95 "Slow Rock"
#define GENRE_96 "Big Band"
#define GENRE_97 "Chorus"
#define GENRE_98 "Easy Listening"
#define GENRE_99 "Acoustic"
#define GENRE_100 "Humour"
#define GENRE_101 "Speech"
#define GENRE_102 "Chanson"
#define GENRE_103 "Opera"
#define GENRE_104 "Chamber Music"
#define GENRE_105 "Sonata"
#define GENRE_106 "Symphony"
#define GENRE_107 "Booty Bass"
#define GENRE_108 "Primus"
#define GENRE_109 "Porn Groove"
#define GENRE_110 "Satire"
#define GENRE_111 "Slow Jam"
#define GENRE_112 "Club"
#define GENRE_113 "Tango"
#define GENRE_114 "Samba"
#define GENRE_115 "Folklore"
#define GENRE_116 "Ballad"
#define GENRE_117 "Power Ballad"
#define GENRE_118 "Rhythmic Soul"
#define GENRE_119 "Freestyle"
#define GENRE_120 "Duet"
#define GENRE_121 "Punk Rock"
#define GENRE_122 "Drum Solo"
#define GENRE_123 "Acapella"
#define GENRE_124 "Euro-House"
#define GENRE_125 "Dance Hall"
#define GENRE_126 "Goa"
#define GENRE_127 "Drum & Bass"
#define GENRE_128 "Club - House"
#define GENRE_129 "Hardcore"
#define GENRE_130 "Terror"
#define GENRE_131 "Indie"
#define GENRE_132 "BritPop"
#define GENRE_133 "Negerpunk"
#define GENRE_134 "Polsk Punk"
#define GENRE_135 "Beat"
#define GENRE_136 "Christian Gangsta Rap"
#define GENRE_137 "Heavy Metal"
#define GENRE_138 "Black Metal"
#define GENRE_139 "Crossover"
#define GENRE_140 "Contemporary Christian"
#define GENRE_141 "Christian Rock"
#define GENRE_142 "Merengue"
#define GENRE_143 "Salsa"
#define GENRE_144 "Thrash Metal"
#define GENRE_145 "Anime"
#define GENRE_146 "JPop"
#define GENRE_147 "Synthpop"

typedef struct ID3v1 {
    char header[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
} ID3v1;

void
setGenre(FileInfo* file, unsigned int num)
{
    switch (num) {
    case 0:
        file->genre = (char*) malloc(strlen(GENRE_0) + 1);
        memset(file->genre, '\0', strlen(GENRE_0) + 1);
        strcpy(file->genre, GENRE_0);
        break;
    case 1:
        file->genre = (char*) malloc(strlen(GENRE_1) + 1);
        memset(file->genre, '\0', strlen(GENRE_1) + 1);
        strcpy(file->genre, GENRE_1);
        break;
    case 2:
        file->genre = (char*) malloc(strlen(GENRE_2) + 1);
        memset(file->genre, '\0', strlen(GENRE_2) + 1);
        strcpy(file->genre, GENRE_2);
        break;
    case 3:
        file->genre = (char*) malloc(strlen(GENRE_3) + 1);
        memset(file->genre, '\0', strlen(GENRE_3) + 1);
        strcpy(file->genre, GENRE_3);
        break;
    case 4:
        file->genre = (char*) malloc(strlen(GENRE_4) + 1);
        memset(file->genre, '\0', strlen(GENRE_4) + 1);
        strcpy(file->genre, GENRE_4);
        break;
    case 5:
        file->genre = (char*) malloc(strlen(GENRE_5) + 1);
        memset(file->genre, '\0', strlen(GENRE_5) + 1);
        strcpy(file->genre, GENRE_5);
        break;
    case 6:
        file->genre = (char*) malloc(strlen(GENRE_6) + 1);
        memset(file->genre, '\0', strlen(GENRE_6) + 1);
        strcpy(file->genre, GENRE_6);
        break;
    case 7:
        file->genre = (char*) malloc(strlen(GENRE_7) + 1);
        memset(file->genre, '\0', strlen(GENRE_7) + 1);
        strcpy(file->genre, GENRE_7);
        break;
    case 8:
        file->genre = (char*) malloc(strlen(GENRE_8) + 1);
        memset(file->genre, '\0', strlen(GENRE_8) + 1);
        strcpy(file->genre, GENRE_8);
        break;
    case 9:
        file->genre = (char*) malloc(strlen(GENRE_9) + 1);
        memset(file->genre, '\0', strlen(GENRE_9) + 1);
        strcpy(file->genre, GENRE_9);
        break;
    case 10:
        file->genre = (char*) malloc(strlen(GENRE_10) + 1);
        memset(file->genre, '\0', strlen(GENRE_10) + 1);
        strcpy(file->genre, GENRE_10);
        break;
    case 11:
        file->genre = (char*) malloc(strlen(GENRE_11) + 1);
        memset(file->genre, '\0', strlen(GENRE_11) + 1);
        strcpy(file->genre, GENRE_11);
        break;
    case 12:
        file->genre = (char*) malloc(strlen(GENRE_12) + 1);
        memset(file->genre, '\0', strlen(GENRE_12) + 1);
        strcpy(file->genre, GENRE_12);
        break;
    case 13:
        file->genre = (char*) malloc(strlen(GENRE_13) + 1);
        memset(file->genre, '\0', strlen(GENRE_13) + 1);
        strcpy(file->genre, GENRE_13);
        break;
    case 14:
        file->genre = (char*) malloc(strlen(GENRE_14) + 1);
        memset(file->genre, '\0', strlen(GENRE_14) + 1);
        strcpy(file->genre, GENRE_14);
        break;
    case 15:
        file->genre = (char*) malloc(strlen(GENRE_15) + 1);
        memset(file->genre, '\0', strlen(GENRE_15) + 1);
        strcpy(file->genre, GENRE_15);
        break;
    case 16:
        file->genre = (char*) malloc(strlen(GENRE_16) + 1);
        memset(file->genre, '\0', strlen(GENRE_16) + 1);
        strcpy(file->genre, GENRE_16);
        break;
    case 17:
        file->genre = (char*) malloc(strlen(GENRE_17) + 1);
        memset(file->genre, '\0', strlen(GENRE_17) + 1);
        strcpy(file->genre, GENRE_17);
        break;
    case 18:
        file->genre = (char*) malloc(strlen(GENRE_18) + 1);
        memset(file->genre, '\0', strlen(GENRE_18) + 1);
        strcpy(file->genre, GENRE_18);
        break;
    case 19:
        file->genre = (char*) malloc(strlen(GENRE_19) + 1);
        memset(file->genre, '\0', strlen(GENRE_19) + 1);
        strcpy(file->genre, GENRE_19);
        break;
    case 20:
        file->genre = (char*) malloc(strlen(GENRE_20) + 1);
        memset(file->genre, '\0', strlen(GENRE_20) + 1);
        strcpy(file->genre, GENRE_20);
        break;
    case 21:
        file->genre = (char*) malloc(strlen(GENRE_21) + 1);
        memset(file->genre, '\0', strlen(GENRE_21) + 1);
        strcpy(file->genre, GENRE_21);
        break;
    case 22:
        file->genre = (char*) malloc(strlen(GENRE_22) + 1);
        memset(file->genre, '\0', strlen(GENRE_22) + 1);
        strcpy(file->genre, GENRE_22);
        break;
    case 23:
        file->genre = (char*) malloc(strlen(GENRE_23) + 1);
        memset(file->genre, '\0', strlen(GENRE_23) + 1);
        strcpy(file->genre, GENRE_23);
        break;
    case 24:
        file->genre = (char*) malloc(strlen(GENRE_24) + 1);
        memset(file->genre, '\0', strlen(GENRE_24) + 1);
        strcpy(file->genre, GENRE_24);
        break;
    case 25:
        file->genre = (char*) malloc(strlen(GENRE_25) + 1);
        memset(file->genre, '\0', strlen(GENRE_25) + 1);
        strcpy(file->genre, GENRE_25);
        break;
    case 26:
        file->genre = (char*) malloc(strlen(GENRE_26) + 1);
        memset(file->genre, '\0', strlen(GENRE_26) + 1);
        strcpy(file->genre, GENRE_26);
        break;
    case 27:
        file->genre = (char*) malloc(strlen(GENRE_27) + 1);
        memset(file->genre, '\0', strlen(GENRE_27) + 1);
        strcpy(file->genre, GENRE_27);
        break;
    case 28:
        file->genre = (char*) malloc(strlen(GENRE_28) + 1);
        memset(file->genre, '\0', strlen(GENRE_28) + 1);
        strcpy(file->genre, GENRE_28);
        break;
    case 29:
        file->genre = (char*) malloc(strlen(GENRE_29) + 1);
        memset(file->genre, '\0', strlen(GENRE_29) + 1);
        strcpy(file->genre, GENRE_29);
        break;
    case 30:
        file->genre = (char*) malloc(strlen(GENRE_30) + 1);
        memset(file->genre, '\0', strlen(GENRE_30) + 1);
        strcpy(file->genre, GENRE_30);
        break;
    case 31:
        file->genre = (char*) malloc(strlen(GENRE_31) + 1);
        memset(file->genre, '\0', strlen(GENRE_31) + 1);
        strcpy(file->genre, GENRE_31);
        break;
    case 32:
        file->genre = (char*) malloc(strlen(GENRE_32) + 1);
        memset(file->genre, '\0', strlen(GENRE_32) + 1);
        strcpy(file->genre, GENRE_32);
        break;
    case 33:
        file->genre = (char*) malloc(strlen(GENRE_33) + 1);
        memset(file->genre, '\0', strlen(GENRE_33) + 1);
        strcpy(file->genre, GENRE_33);
        break;
    case 34:
        file->genre = (char*) malloc(strlen(GENRE_34) + 1);
        memset(file->genre, '\0', strlen(GENRE_34) + 1);
        strcpy(file->genre, GENRE_34);
        break;
    case 35:
        file->genre = (char*) malloc(strlen(GENRE_35) + 1);
        memset(file->genre, '\0', strlen(GENRE_35) + 1);
        strcpy(file->genre, GENRE_35);
        break;
    case 36:
        file->genre = (char*) malloc(strlen(GENRE_36) + 1);
        memset(file->genre, '\0', strlen(GENRE_36) + 1);
        strcpy(file->genre, GENRE_36);
        break;
    case 37:
        file->genre = (char*) malloc(strlen(GENRE_37) + 1);
        memset(file->genre, '\0', strlen(GENRE_37) + 1);
        strcpy(file->genre, GENRE_37);
        break;
    case 38:
        file->genre = (char*) malloc(strlen(GENRE_38) + 1);
        memset(file->genre, '\0', strlen(GENRE_38) + 1);
        strcpy(file->genre, GENRE_38);
        break;
    case 39:
        file->genre = (char*) malloc(strlen(GENRE_39) + 1);
        memset(file->genre, '\0', strlen(GENRE_39) + 1);
        strcpy(file->genre, GENRE_39);
        break;
    case 40:
        file->genre = (char*) malloc(strlen(GENRE_40) + 1);
        memset(file->genre, '\0', strlen(GENRE_40) + 1);
        strcpy(file->genre, GENRE_40);
        break;
    case 41:
        file->genre = (char*) malloc(strlen(GENRE_41) + 1);
        memset(file->genre, '\0', strlen(GENRE_41) + 1);
        strcpy(file->genre, GENRE_41);
        break;
    case 42:
        file->genre = (char*) malloc(strlen(GENRE_42) + 1);
        memset(file->genre, '\0', strlen(GENRE_42) + 1);
        strcpy(file->genre, GENRE_42);
        break;
    case 43:
        file->genre = (char*) malloc(strlen(GENRE_43) + 1);
        memset(file->genre, '\0', strlen(GENRE_43) + 1);
        strcpy(file->genre, GENRE_43);
        break;
    case 44:
        file->genre = (char*) malloc(strlen(GENRE_44) + 1);
        memset(file->genre, '\0', strlen(GENRE_44) + 1);
        strcpy(file->genre, GENRE_44);
        break;
    case 45:
        file->genre = (char*) malloc(strlen(GENRE_45) + 1);
        memset(file->genre, '\0', strlen(GENRE_45) + 1);
        strcpy(file->genre, GENRE_45);
        break;
    case 46:
        file->genre = (char*) malloc(strlen(GENRE_46) + 1);
        memset(file->genre, '\0', strlen(GENRE_46) + 1);
        strcpy(file->genre, GENRE_46);
        break;
    case 47:
        file->genre = (char*) malloc(strlen(GENRE_47) + 1);
        memset(file->genre, '\0', strlen(GENRE_47) + 1);
        strcpy(file->genre, GENRE_47);
        break;
    case 48:
        file->genre = (char*) malloc(strlen(GENRE_48) + 1);
        memset(file->genre, '\0', strlen(GENRE_48) + 1);
        strcpy(file->genre, GENRE_48);
        break;
    case 49:
        file->genre = (char*) malloc(strlen(GENRE_49) + 1);
        memset(file->genre, '\0', strlen(GENRE_49) + 1);
        strcpy(file->genre, GENRE_49);
        break;
    case 50:
        file->genre = (char*) malloc(strlen(GENRE_50) + 1);
        memset(file->genre, '\0', strlen(GENRE_50) + 1);
        strcpy(file->genre, GENRE_50);
        break;
    case 51:
        file->genre = (char*) malloc(strlen(GENRE_51) + 1);
        memset(file->genre, '\0', strlen(GENRE_51) + 1);
        strcpy(file->genre, GENRE_51);
        break;
    case 52:
        file->genre = (char*) malloc(strlen(GENRE_52) + 1);
        memset(file->genre, '\0', strlen(GENRE_52) + 1);
        strcpy(file->genre, GENRE_52);
        break;
    case 53:
        file->genre = (char*) malloc(strlen(GENRE_53) + 1);
        memset(file->genre, '\0', strlen(GENRE_53) + 1);
        strcpy(file->genre, GENRE_53);
        break;
    case 54:
        file->genre = (char*) malloc(strlen(GENRE_54) + 1);
        memset(file->genre, '\0', strlen(GENRE_54) + 1);
        strcpy(file->genre, GENRE_54);
        break;
    case 55:
        file->genre = (char*) malloc(strlen(GENRE_55) + 1);
        memset(file->genre, '\0', strlen(GENRE_55) + 1);
        strcpy(file->genre, GENRE_55);
        break;
    case 56:
        file->genre = (char*) malloc(strlen(GENRE_56) + 1);
        memset(file->genre, '\0', strlen(GENRE_56) + 1);
        strcpy(file->genre, GENRE_56);
        break;
    case 57:
        file->genre = (char*) malloc(strlen(GENRE_57) + 1);
        memset(file->genre, '\0', strlen(GENRE_57) + 1);
        strcpy(file->genre, GENRE_57);
        break;
    case 58:
        file->genre = (char*) malloc(strlen(GENRE_58) + 1);
        memset(file->genre, '\0', strlen(GENRE_58) + 1);
        strcpy(file->genre, GENRE_58);
        break;
    case 59:
        file->genre = (char*) malloc(strlen(GENRE_59) + 1);
        memset(file->genre, '\0', strlen(GENRE_59) + 1);
        strcpy(file->genre, GENRE_59);
        break;
    case 60:
        file->genre = (char*) malloc(strlen(GENRE_60) + 1);
        memset(file->genre, '\0', strlen(GENRE_60) + 1);
        strcpy(file->genre, GENRE_60);
        break;
    case 61:
        file->genre = (char*) malloc(strlen(GENRE_61) + 1);
        memset(file->genre, '\0', strlen(GENRE_61) + 1);
        strcpy(file->genre, GENRE_61);
        break;
    case 62:
        file->genre = (char*) malloc(strlen(GENRE_62) + 1);
        memset(file->genre, '\0', strlen(GENRE_62) + 1);
        strcpy(file->genre, GENRE_62);
        break;
    case 63:
        file->genre = (char*) malloc(strlen(GENRE_63) + 1);
        memset(file->genre, '\0', strlen(GENRE_63) + 1);
        strcpy(file->genre, GENRE_63);
        break;
    case 64:
        file->genre = (char*) malloc(strlen(GENRE_64) + 1);
        memset(file->genre, '\0', strlen(GENRE_64) + 1);
        strcpy(file->genre, GENRE_64);
        break;
    case 65:
        file->genre = (char*) malloc(strlen(GENRE_65) + 1);
        memset(file->genre, '\0', strlen(GENRE_65) + 1);
        strcpy(file->genre, GENRE_65);
        break;
    case 66:
        file->genre = (char*) malloc(strlen(GENRE_66) + 1);
        memset(file->genre, '\0', strlen(GENRE_66) + 1);
        strcpy(file->genre, GENRE_66);
        break;
    case 67:
        file->genre = (char*) malloc(strlen(GENRE_67) + 1);
        memset(file->genre, '\0', strlen(GENRE_67) + 1);
        strcpy(file->genre, GENRE_67);
        break;
    case 68:
        file->genre = (char*) malloc(strlen(GENRE_68) + 1);
        memset(file->genre, '\0', strlen(GENRE_68) + 1);
        strcpy(file->genre, GENRE_68);
        break;
    case 69:
        file->genre = (char*) malloc(strlen(GENRE_69) + 1);
        memset(file->genre, '\0', strlen(GENRE_69) + 1);
        strcpy(file->genre, GENRE_69);
        break;
    case 70:
        file->genre = (char*) malloc(strlen(GENRE_70) + 1);
        memset(file->genre, '\0', strlen(GENRE_70) + 1);
        strcpy(file->genre, GENRE_70);
        break;
    case 71:
        file->genre = (char*) malloc(strlen(GENRE_71) + 1);
        memset(file->genre, '\0', strlen(GENRE_71) + 1);
        strcpy(file->genre, GENRE_71);
        break;
    case 72:
        file->genre = (char*) malloc(strlen(GENRE_72) + 1);
        memset(file->genre, '\0', strlen(GENRE_72) + 1);
        strcpy(file->genre, GENRE_72);
        break;
    case 73:
        file->genre = (char*) malloc(strlen(GENRE_73) + 1);
        memset(file->genre, '\0', strlen(GENRE_73) + 1);
        strcpy(file->genre, GENRE_73);
        break;
    case 74:
        file->genre = (char*) malloc(strlen(GENRE_74) + 1);
        memset(file->genre, '\0', strlen(GENRE_74) + 1);
        strcpy(file->genre, GENRE_74);
        break;
    case 75:
        file->genre = (char*) malloc(strlen(GENRE_75) + 1);
        memset(file->genre, '\0', strlen(GENRE_75) + 1);
        strcpy(file->genre, GENRE_75);
        break;
    case 76:
        file->genre = (char*) malloc(strlen(GENRE_76) + 1);
        memset(file->genre, '\0', strlen(GENRE_76) + 1);
        strcpy(file->genre, GENRE_76);
        break;
    case 77:
        file->genre = (char*) malloc(strlen(GENRE_77) + 1);
        memset(file->genre, '\0', strlen(GENRE_77) + 1);
        strcpy(file->genre, GENRE_77);
        break;
    case 78:
        file->genre = (char*) malloc(strlen(GENRE_78) + 1);
        memset(file->genre, '\0', strlen(GENRE_78) + 1);
        strcpy(file->genre, GENRE_78);
        break;
    case 79:
        file->genre = (char*) malloc(strlen(GENRE_79) + 1);
        memset(file->genre, '\0', strlen(GENRE_79) + 1);
        strcpy(file->genre, GENRE_79);
        break;
    case 80:
        file->genre = (char*) malloc(strlen(GENRE_80) + 1);
        memset(file->genre, '\0', strlen(GENRE_80) + 1);
        strcpy(file->genre, GENRE_80);
        break;
    case 81:
        file->genre = (char*) malloc(strlen(GENRE_81) + 1);
        memset(file->genre, '\0', strlen(GENRE_81) + 1);
        strcpy(file->genre, GENRE_81);
        break;
    case 82:
        file->genre = (char*) malloc(strlen(GENRE_82) + 1);
        memset(file->genre, '\0', strlen(GENRE_82) + 1);
        strcpy(file->genre, GENRE_82);
        break;
    case 83:
        file->genre = (char*) malloc(strlen(GENRE_83) + 1);
        memset(file->genre, '\0', strlen(GENRE_83) + 1);
        strcpy(file->genre, GENRE_83);
        break;
    case 84:
        file->genre = (char*) malloc(strlen(GENRE_84) + 1);
        memset(file->genre, '\0', strlen(GENRE_84) + 1);
        strcpy(file->genre, GENRE_84);
        break;
    case 85:
        file->genre = (char*) malloc(strlen(GENRE_85) + 1);
        memset(file->genre, '\0', strlen(GENRE_85) + 1);
        strcpy(file->genre, GENRE_85);
        break;
    case 86:
        file->genre = (char*) malloc(strlen(GENRE_86) + 1);
        memset(file->genre, '\0', strlen(GENRE_86) + 1);
        strcpy(file->genre, GENRE_86);
        break;
    case 87:
        file->genre = (char*) malloc(strlen(GENRE_87) + 1);
        memset(file->genre, '\0', strlen(GENRE_87) + 1);
        strcpy(file->genre, GENRE_87);
        break;
    case 88:
        file->genre = (char*) malloc(strlen(GENRE_88) + 1);
        memset(file->genre, '\0', strlen(GENRE_88) + 1);
        strcpy(file->genre, GENRE_88);
        break;
    case 89:
        file->genre = (char*) malloc(strlen(GENRE_89) + 1);
        memset(file->genre, '\0', strlen(GENRE_89) + 1);
        strcpy(file->genre, GENRE_89);
        break;
    case 90:
        file->genre = (char*) malloc(strlen(GENRE_90) + 1);
        memset(file->genre, '\0', strlen(GENRE_90) + 1);
        strcpy(file->genre, GENRE_90);
        break;
    case 91:
        file->genre = (char*) malloc(strlen(GENRE_91) + 1);
        memset(file->genre, '\0', strlen(GENRE_91) + 1);
        strcpy(file->genre, GENRE_91);
        break;
    case 92:
        file->genre = (char*) malloc(strlen(GENRE_92) + 1);
        memset(file->genre, '\0', strlen(GENRE_92) + 1);
        strcpy(file->genre, GENRE_92);
        break;
    case 93:
        file->genre = (char*) malloc(strlen(GENRE_93) + 1);
        memset(file->genre, '\0', strlen(GENRE_93) + 1);
        strcpy(file->genre, GENRE_93);
        break;
    case 94:
        file->genre = (char*) malloc(strlen(GENRE_94) + 1);
        memset(file->genre, '\0', strlen(GENRE_94) + 1);
        strcpy(file->genre, GENRE_94);
        break;
    case 95:
        file->genre = (char*) malloc(strlen(GENRE_95) + 1);
        memset(file->genre, '\0', strlen(GENRE_95) + 1);
        strcpy(file->genre, GENRE_95);
        break;
    case 96:
        file->genre = (char*) malloc(strlen(GENRE_96) + 1);
        memset(file->genre, '\0', strlen(GENRE_96) + 1);
        strcpy(file->genre, GENRE_96);
        break;
    case 97:
        file->genre = (char*) malloc(strlen(GENRE_97) + 1);
        memset(file->genre, '\0', strlen(GENRE_97) + 1);
        strcpy(file->genre, GENRE_97);
        break;
    case 98:
        file->genre = (char*) malloc(strlen(GENRE_98) + 1);
        memset(file->genre, '\0', strlen(GENRE_98) + 1);
        strcpy(file->genre, GENRE_98);
        break;
    case 99:
        file->genre = (char*) malloc(strlen(GENRE_99) + 1);
        memset(file->genre, '\0', strlen(GENRE_99) + 1);
        strcpy(file->genre, GENRE_99);
        break;
    case 100:
        file->genre = (char*) malloc(strlen(GENRE_100) + 1);
        memset(file->genre, '\0', strlen(GENRE_100) + 1);
        strcpy(file->genre, GENRE_100);
        break;
    case 101:
        file->genre = (char*) malloc(strlen(GENRE_101) + 1);
        memset(file->genre, '\0', strlen(GENRE_101) + 1);
        strcpy(file->genre, GENRE_101);
        break;
    case 102:
        file->genre = (char*) malloc(strlen(GENRE_102) + 1);
        memset(file->genre, '\0', strlen(GENRE_102) + 1);
        strcpy(file->genre, GENRE_102);
        break;
    case 103:
        file->genre = (char*) malloc(strlen(GENRE_103) + 1);
        memset(file->genre, '\0', strlen(GENRE_103) + 1);
        strcpy(file->genre, GENRE_103);
        break;
    case 104:
        file->genre = (char*) malloc(strlen(GENRE_104) + 1);
        memset(file->genre, '\0', strlen(GENRE_104) + 1);
        strcpy(file->genre, GENRE_104);
        break;
    case 105:
        file->genre = (char*) malloc(strlen(GENRE_105) + 1);
        memset(file->genre, '\0', strlen(GENRE_105) + 1);
        strcpy(file->genre, GENRE_105);
        break;
    case 106:
        file->genre = (char*) malloc(strlen(GENRE_106) + 1);
        memset(file->genre, '\0', strlen(GENRE_106) + 1);
        strcpy(file->genre, GENRE_106);
        break;
    case 107:
        file->genre = (char*) malloc(strlen(GENRE_107) + 1);
        memset(file->genre, '\0', strlen(GENRE_107) + 1);
        strcpy(file->genre, GENRE_107);
        break;
    case 108:
        file->genre = (char*) malloc(strlen(GENRE_108) + 1);
        memset(file->genre, '\0', strlen(GENRE_108) + 1);
        strcpy(file->genre, GENRE_108);
        break;
    case 109:
        file->genre = (char*) malloc(strlen(GENRE_109) + 1);
        memset(file->genre, '\0', strlen(GENRE_109) + 1);
        strcpy(file->genre, GENRE_109);
        break;
    case 110:
        file->genre = (char*) malloc(strlen(GENRE_110) + 1);
        memset(file->genre, '\0', strlen(GENRE_110) + 1);
        strcpy(file->genre, GENRE_110);
        break;
    case 111:
        file->genre = (char*) malloc(strlen(GENRE_111) + 1);
        memset(file->genre, '\0', strlen(GENRE_111) + 1);
        strcpy(file->genre, GENRE_111);
        break;
    case 112:
        file->genre = (char*) malloc(strlen(GENRE_112) + 1);
        memset(file->genre, '\0', strlen(GENRE_112) + 1);
        strcpy(file->genre, GENRE_112);
        break;
    case 113:
        file->genre = (char*) malloc(strlen(GENRE_113) + 1);
        memset(file->genre, '\0', strlen(GENRE_113) + 1);
        strcpy(file->genre, GENRE_113);
        break;
    case 114:
        file->genre = (char*) malloc(strlen(GENRE_114) + 1);
        memset(file->genre, '\0', strlen(GENRE_114) + 1);
        strcpy(file->genre, GENRE_114);
        break;
    case 115:
        file->genre = (char*) malloc(strlen(GENRE_115) + 1);
        memset(file->genre, '\0', strlen(GENRE_115) + 1);
        strcpy(file->genre, GENRE_115);
        break;
    case 116:
        file->genre = (char*) malloc(strlen(GENRE_116) + 1);
        memset(file->genre, '\0', strlen(GENRE_116) + 1);
        strcpy(file->genre, GENRE_116);
        break;
    case 117:
        file->genre = (char*) malloc(strlen(GENRE_117) + 1);
        memset(file->genre, '\0', strlen(GENRE_117) + 1);
        strcpy(file->genre, GENRE_117);
        break;
    case 118:
        file->genre = (char*) malloc(strlen(GENRE_118) + 1);
        memset(file->genre, '\0', strlen(GENRE_118) + 1);
        strcpy(file->genre, GENRE_118);
        break;
    case 119:
        file->genre = (char*) malloc(strlen(GENRE_119) + 1);
        memset(file->genre, '\0', strlen(GENRE_119) + 1);
        strcpy(file->genre, GENRE_119);
        break;
    case 120:
        file->genre = (char*) malloc(strlen(GENRE_120) + 1);
        memset(file->genre, '\0', strlen(GENRE_120) + 1);
        strcpy(file->genre, GENRE_120);
        break;
    case 121:
        file->genre = (char*) malloc(strlen(GENRE_121) + 1);
        memset(file->genre, '\0', strlen(GENRE_121) + 1);
        strcpy(file->genre, GENRE_121);
        break;
    case 122:
        file->genre = (char*) malloc(strlen(GENRE_122) + 1);
        memset(file->genre, '\0', strlen(GENRE_122) + 1);
        strcpy(file->genre, GENRE_122);
        break;
    case 123:
        file->genre = (char*) malloc(strlen(GENRE_123) + 1);
        memset(file->genre, '\0', strlen(GENRE_123) + 1);
        strcpy(file->genre, GENRE_123);
        break;
    case 124:
        file->genre = (char*) malloc(strlen(GENRE_124) + 1);
        memset(file->genre, '\0', strlen(GENRE_124) + 1);
        strcpy(file->genre, GENRE_124);
        break;
    case 125:
        file->genre = (char*) malloc(strlen(GENRE_125) + 1);
        memset(file->genre, '\0', strlen(GENRE_125) + 1);
        strcpy(file->genre, GENRE_125);
        break;
    case 126:
        file->genre = (char*) malloc(strlen(GENRE_126) + 1);
        memset(file->genre, '\0', strlen(GENRE_126) + 1);
        strcpy(file->genre, GENRE_126);
        break;
    case 127:
        file->genre = (char*) malloc(strlen(GENRE_127) + 1);
        memset(file->genre, '\0', strlen(GENRE_127) + 1);
        strcpy(file->genre, GENRE_127);
        break;
    case 128:
        file->genre = (char*) malloc(strlen(GENRE_128) + 1);
        memset(file->genre, '\0', strlen(GENRE_128) + 1);
        strcpy(file->genre, GENRE_128);
        break;
    case 129:
        file->genre = (char*) malloc(strlen(GENRE_129) + 1);
        memset(file->genre, '\0', strlen(GENRE_129) + 1);
        strcpy(file->genre, GENRE_129);
        break;
    case 130:
        file->genre = (char*) malloc(strlen(GENRE_130) + 1);
        memset(file->genre, '\0', strlen(GENRE_130) + 1);
        strcpy(file->genre, GENRE_130);
        break;
    case 131:
        file->genre = (char*) malloc(strlen(GENRE_131) + 1);
        memset(file->genre, '\0', strlen(GENRE_131) + 1);
        strcpy(file->genre, GENRE_131);
        break;
    case 132:
        file->genre = (char*) malloc(strlen(GENRE_132) + 1);
        memset(file->genre, '\0', strlen(GENRE_132) + 1);
        strcpy(file->genre, GENRE_132);
        break;
    case 133:
        file->genre = (char*) malloc(strlen(GENRE_133) + 1);
        memset(file->genre, '\0', strlen(GENRE_133) + 1);
        strcpy(file->genre, GENRE_133);
        break;
    case 134:
        file->genre = (char*) malloc(strlen(GENRE_134) + 1);
        memset(file->genre, '\0', strlen(GENRE_134) + 1);
        strcpy(file->genre, GENRE_134);
        break;
    case 135:
        file->genre = (char*) malloc(strlen(GENRE_135) + 1);
        memset(file->genre, '\0', strlen(GENRE_135) + 1);
        strcpy(file->genre, GENRE_135);
        break;
    case 136:
        file->genre = (char*) malloc(strlen(GENRE_136) + 1);
        memset(file->genre, '\0', strlen(GENRE_136) + 1);
        strcpy(file->genre, GENRE_136);
        break;
    case 137:
        file->genre = (char*) malloc(strlen(GENRE_137) + 1);
        memset(file->genre, '\0', strlen(GENRE_137) + 1);
        strcpy(file->genre, GENRE_137);
        break;
    case 138:
        file->genre = (char*) malloc(strlen(GENRE_138) + 1);
        memset(file->genre, '\0', strlen(GENRE_138) + 1);
        strcpy(file->genre, GENRE_138);
        break;
    case 139:
        file->genre = (char*) malloc(strlen(GENRE_139) + 1);
        memset(file->genre, '\0', strlen(GENRE_139) + 1);
        strcpy(file->genre, GENRE_139);
        break;
    case 140:
        file->genre = (char*) malloc(strlen(GENRE_140) + 1);
        memset(file->genre, '\0', strlen(GENRE_140) + 1);
        strcpy(file->genre, GENRE_140);
        break;
    case 141:
        file->genre = (char*) malloc(strlen(GENRE_141) + 1);
        memset(file->genre, '\0', strlen(GENRE_141) + 1);
        strcpy(file->genre, GENRE_141);
        break;
    case 142:
        file->genre = (char*) malloc(strlen(GENRE_142) + 1);
        memset(file->genre, '\0', strlen(GENRE_142) + 1);
        strcpy(file->genre, GENRE_142);
        break;
    case 143:
        file->genre = (char*) malloc(strlen(GENRE_143) + 1);
        memset(file->genre, '\0', strlen(GENRE_143) + 1);
        strcpy(file->genre, GENRE_143);
        break;
    case 144:
        file->genre = (char*) malloc(strlen(GENRE_144) + 1);
        memset(file->genre, '\0', strlen(GENRE_144) + 1);
        strcpy(file->genre, GENRE_144);
        break;
    case 145:
        file->genre = (char*) malloc(strlen(GENRE_145) + 1);
        memset(file->genre, '\0', strlen(GENRE_145) + 1);
        strcpy(file->genre, GENRE_145);
        break;
    case 146:
        file->genre = (char*) malloc(strlen(GENRE_146) + 1);
        memset(file->genre, '\0', strlen(GENRE_146) + 1);
        strcpy(file->genre, GENRE_146);
        break;
    case 147:
        file->genre = (char*) malloc(strlen(GENRE_147) + 1);
        memset(file->genre, '\0', strlen(GENRE_147) + 1);
        strcpy(file->genre, GENRE_147);
        break;
    }
}

void
id3v1(FileInfo* file, FILE* handle)
{
    ID3v1 tag;
    char buffer[31];
    int index;

    buffer[30] = '\0';
    fseek(handle, -128, SEEK_END);
    index = fread(&tag, 1, 128, handle);

    /* Title */
    strncpy(buffer, tag.title, 30);
    index = 29;
    while (index >= 0) {
        if (buffer[index] != 32) {
            break;
        }
        --index;
    }
    buffer[index + 1] = '\0';
    file->title = (char*) malloc(strlen(buffer) + 1);
    memset(file->title, '\0', strlen(buffer) + 1);
    strcpy(file->title, buffer);

    /* Artist */
    strncpy(buffer, tag.artist, 30);
    index = 29;
    while (index >= 0) {
        if (buffer[index] != 32) {
            break;
        }
        --index;
    }
    buffer[index + 1] = '\0';
    file->artist = (char*) malloc(strlen(buffer) + 1);
    memset(file->artist, '\0', strlen(buffer) + 1);
    strcpy(file->artist, buffer);

    /* Album */
    strncpy(buffer, tag.album, 30);
    index = 29;
    while (index >= 0) {
        if (buffer[index] != 32) {
            break;
        }
        --index;
    }
    buffer[index + 1] = '\0';
    file->album = (char*) malloc(strlen(buffer) + 1);
    memset(file->album, '\0', strlen(buffer) + 1);
    strcpy(file->album, buffer);

    /* Comment */
    strncpy(buffer, tag.comment, 28);
    index = 27;
    while (index >= 0) {
        if (buffer[index] != 32) {
            break;
        }
        --index;
    }
    buffer[index + 1] = '\0';
    file->comment = (char*) malloc(strlen(buffer) + 1);
    memset(file->comment, '\0', strlen(buffer) + 1);
    strcpy(file->comment, buffer);

    /* Year */
    strncpy(buffer, tag.year, 4);
    buffer[4] = '\0';
    file->year = atoi(buffer);

    /* Genre */
    setGenre(file, tag.genre);
}

void
id3v2(FileInfo* file, FILE* handle)
{
    char header[10];
    char *buffer = 0;
    char frameName[5] = {0, 0, 0, 0, 0};
    unsigned int index = 0;
    unsigned int readSize = 0;
    int frameHeaderSize = 6;
    int frameSize = 0;
    int tagSize = 0;
    int genre = 0;
    unsigned char encoding = 0;
    char tagVersion = -1;
    char usesSync = 0;
    char hasExtendedHeader = 0;

    fseek(handle, 0, SEEK_SET);

    readSize = fread(header, 1, 10, handle);

    if (header[0] != 'I' || header[1] != 'D' || header[2] != '3') {
        return;
    }

    tagVersion = header[3];
    if (tagVersion < 0 || tagVersion > 4) {
        return;
    }

    tagSize = (header[9] & 0xFF) | ((header[8] & 0xFF) << 7) |
        ((header[7] & 0xFF) << 14) | ((header[6] & 0xFF) << 21) + 10;

    usesSync = (header[5] & 0x80) != 0 ? 1 : 0;
    hasExtendedHeader = (header[5] & 0x40) != 0 ? 1 : 0;

    if (hasExtendedHeader == 1) {
        index = fgetc(handle) << 21 | fgetc(handle) << 14 |
            fgetc(handle) << 7 | fgetc(handle);
        index -= 4;
        while (index > 0) {
            fgetc(handle);
            --index;
        }
    }

    buffer = (char*) malloc(tagSize);
    readSize = fread(buffer, 1, tagSize, handle);

    if (tagVersion >= 3) {
        encoding = 1;
        frameHeaderSize = 10;
    }

    index = 0;
    while (index < tagSize) {
        if (tagSize - index < frameHeaderSize) {
            break;
        }

        if (buffer[index] < 'A' || buffer[index] > 'Z') {
            break;
        }

        if (tagVersion < 3) {
            strncpy(frameName, buffer + index, 3);
            frameName[3] = '\0';
            frameSize = ((buffer[index + 5] & 0xFF) << 8) |
                ((buffer[index + 4] & 0xFF) << 16) |
                ((buffer[index + 3] & 0xFF) << 24);
        } else {
            strncpy(frameName, buffer + index, 4);
            frameName[4] = '\0';
            frameSize = (buffer[index + 7] & 0xFF) |
                ((buffer[index + 6] & 0xFF) << 8) |
                ((buffer[index + 5] & 0xFF) << 16) |
                ((buffer[index + 4] & 0xFF) << 24);
        }

        if (index + frameHeaderSize + frameSize > tagSize) {
            break;
        }

        if (strcmp(frameName, "TIT2") == 0 || strcmp(frameName, "TIT") == 0) {
            free(file->title);
            file->title = (char*) malloc(frameSize);
            memset(file->title, '\0', frameSize);
            strncpy(file->title, buffer + index + frameHeaderSize + encoding,
                frameSize - 1);
        } else if (strcmp(frameName, "TALB") == 0) {
            free(file->album);
            file->album = (char*) malloc(frameSize);
            memset(file->album, '\0', frameSize);
            strncpy(file->album, buffer + index + frameHeaderSize + encoding,
                frameSize - 1);
        } else if (strcmp(frameName, "TPE1") == 0 ||
                strcmp(frameName, "TPE2") == 0 ||
                strcmp(frameName, "TPE3") == 0 ||
                strcmp(frameName, "TPE") == 0) {
            free(file->artist);
            file->artist = (char*) malloc(frameSize);
            memset(file->artist, '\0', frameSize);
            strncpy(file->artist, buffer + index + frameHeaderSize + encoding,
                frameSize - 1);
        } else if (strcmp(frameName, "COMM") == 0) {
            free(file->comment);
            file->comment = (char*) malloc(frameSize);
            memset(file->comment, '\0', frameSize);
            strncpy(file->comment, buffer + index + frameHeaderSize + encoding,
                frameSize - 1);
        } else if (strcmp(frameName, "TCON") == 0) {
            free(file->genre);
            genre = 0;
            while (buffer[index + frameHeaderSize + encoding + genre] == '(') {
                ++genre;
            }
            strncpy(frameName,
                buffer + index + frameHeaderSize + encoding + genre, 3);
            frameName[4] = '\0';
            genre = atoi(frameName);
            setGenre(file, genre);
        } else if (strcmp(frameName, "TYER") == 0) {
            strncpy(frameName, buffer + index + frameHeaderSize + encoding, 4);
            frameName[4] = '\0';
            file->year = atoi(frameName);
        }

        index += frameHeaderSize + frameSize;
    }

    free(buffer);
}

unsigned int
frameSize(unsigned char header[4])
{
    unsigned int result = 0;
    static const unsigned short mpeg_bitrates[4][4][16] = {
        { // Version 2.5
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}, // Reserved
            {0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160, 0}, // Layer 3
            {0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160, 0}, // Layer 2
            {0,  32,  48,  56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256, 0}  // Layer 1
        },
        { // Reserved
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}, // Invalid
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}, // Invalid
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}, // Invalid
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}  // Invalid
        },
        { // Version 2
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}, // Reserved
            {0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160, 0}, // Layer 3
            {0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160, 0}, // Layer 2
            {0,  32,  48,  56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256, 0}  // Layer 1
        },
        { // Version 1
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0}, // Reserved
            {0,  32,  40,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 0}, // Layer 3
            {0,  32,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 384, 0}, // Layer 2
            {0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 0}, // Layer 1
        }};
    static const unsigned short mpeg_srates[4][4] = {
        {11025, 12000,  8000, 0}, // MPEG 2.5
        {    0,     0,     0, 0}, // Reserved
        {22050, 24000, 16000, 0}, // MPEG 2
        {44100, 48000, 32000, 0}};  // MPEG 1
    static const unsigned short mpeg_frame_samples[4][4] = {
        //Rsvd     3     2     1  < Layer   Version
        {    0,  576, 1152,  384}, //       2.5
        {    0,    0,    0,    0}, //       Reserved
        {    0,  576, 1152,  384}, //       2
        {    0, 1152, 1152,  384}};//       1
    static const unsigned char mpeg_slot_size[4] = {0, 1, 1, 4}; // Rsvd, 3, 2, 1
    unsigned char versionIndex;
    unsigned char layerIndex;
    unsigned char padding;
    unsigned char bitRateIndex;
    unsigned char sampleRateIndex;
    unsigned int bitRate;
    unsigned int sampleRate;
    unsigned short samples;
    unsigned char slotSize;
    unsigned short bitsPerSecond;

    if ((header[0] & 0xff) == 0xff && (header[1] & 0xe0) == 0xe0) {
        versionIndex = (header[1] & 0x18) >> 3;
        layerIndex = (header[1] & 0x06) >> 1;
        padding = (header[2] & 0x02) >> 1;
        bitRateIndex = (header[2] & 0xf0) >> 4;
        sampleRateIndex = (header[2] & 0x0c) >> 2;

        bitRate = mpeg_bitrates[versionIndex][layerIndex][bitRateIndex] * 1000;
        sampleRate = mpeg_srates[versionIndex][sampleRateIndex];
        samples = mpeg_frame_samples[versionIndex][layerIndex];
        slotSize = mpeg_slot_size[layerIndex];
        bitsPerSecond = samples / 8;

        if (sampleRate != 0) {
            result = (bitsPerSecond * bitRate) / sampleRate +
                (padding ? slotSize : 0);
        }
    }

    return result;
}

void
determineNumberOfFrames(FileInfo* file, FILE* handle)
{
    unsigned int numFrames = 0;
    unsigned char buffer[4];
    long int fileSize = 0;
    unsigned int incrementAmount = 0;
    int character = 0;

    fseek(handle, 0, SEEK_END);
    fileSize = ftell(handle);
    fseek(handle, 0, SEEK_SET);

    fread(buffer, 1, 4, handle);

    if (buffer[0] == 'I' && buffer[1] == 'D' && buffer[2] == '3') {
        // Skip ID3v2 tags.
        fseek(handle, 2, SEEK_CUR);
        fread(buffer, 1, 4, handle);
        incrementAmount = (buffer[3] & 0xff) |
            ((buffer[2] & 0xff) << 7) | ((buffer[1] & 0xff) << 14) |
            ((buffer[0] & 0xff) << 21) + 6;
        fseek(handle, incrementAmount, SEEK_CUR);
    }

    while (ftell(handle) < fileSize) {
        fread(buffer, 1, 4, handle);
        incrementAmount = frameSize(buffer);
        if (incrementAmount > 0) {
            ++numFrames;
            fseek(handle, incrementAmount - 4, SEEK_CUR);
        } else {
            fseek(handle, 28, SEEK_CUR);
            fread(buffer, 1, 4, handle);
            if (buffer[0] == 0x58 && buffer[1] == 0x69 && buffer[2] == 0x6e &&
                    buffer[3] == 0x67) {
                // Check for the Xing header.
                fread(buffer, 1, 4, handle);
                if ((buffer[3] & 0x01) == 0x01) {
                    fread(buffer, 1, 4, handle);
                    numFrames = ((buffer[0] & 0xff) << 24) |
                        ((buffer[1] & 0xff) << 16) | ((buffer[2] & 0xff) << 8) |
                        (buffer[0] & 0xff);
                    break;
                }
            }

            // Find the next frame header.
            character = fgetc(handle);
            while (feof(handle) == 0) {
                if ((character & 0x000000ff) == 0x000000ff) {
                    character = fgetc(handle);
                    if ((character & 0x000000e0) == 0x000000e0) {
                        fseek(handle, -2, SEEK_CUR);
                        break;
                    }
                }
                character = fgetc(handle);
            }
        }
    }

    file->frameCount = numFrames;
}

char
readTags(FileInfo* file)
{
    char result = 0;
    FILE *handle = 0;
    char buffer[128];
    long int size;
    unsigned char id3Type = 0;

    if (file != 0 && file->filePath != 0) {
        handle = fopen(file->filePath, "r");
    } else {
        result = 2;
    }

    if (handle != 0) {
        size = fread(buffer, 1, 128, handle);
        if (strncmp(buffer, "ID3", 3) == 0) {
            id3Type |= 2;
        }

        fseek(handle, -128, SEEK_END);
        size = fread(buffer, 1, 128, handle);
        if (strncmp(buffer, "TAG", 3) == 0) {
            id3Type |= 1;
        }

        if ((id3Type & 1) != 0) {
            id3v1(file, handle);
        }
        if ((id3Type & 2) != 0) {
            id3v2(file, handle);
        }

        determineNumberOfFrames(file, handle);

        fclose(handle);
    } else {
        result = 1;
    }

    return result;
}

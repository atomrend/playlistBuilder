#include "XmlWriter.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void
convertForXml(char* result, const char* str, char utf8)
{
    char buffer[33];
    unsigned int index = 0;
    unsigned int resultIndex = 0;
    unsigned int stringLength = 0;
    unsigned int newValue = 0;
    unsigned int byte1 = 0;
    unsigned int byte2 = 0;
    unsigned int byte3 = 0;
    unsigned int byte4 = 0;

    if (str != 0) {
        stringLength = strlen(str);
    }

    result[0] = '\0';

    while (index < stringLength && resultIndex < BUFFER_SIZE) {
        if (str[index] == '&') {
            result[resultIndex] = '&';
            ++resultIndex;
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '#';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '3';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '8';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = ';';
            }
        } else if (str[index] == '<') {
            result[resultIndex] = '&';
            ++resultIndex;
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '#';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '6';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '0';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = ';';
            }
        } else if (str[index] == '>') {
            result[resultIndex] = '&';
            ++resultIndex;
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '#';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '6';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '2';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = ';';
            }
        } else if (str[index] == '\'') {
            result[resultIndex] = '&';
            ++resultIndex;
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '#';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '3';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '9';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = ';';
            }
        } else if (str[index] == '"') {
            result[resultIndex] = '&';
            ++resultIndex;
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '#';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '3';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = '4';
                ++resultIndex;
            }
            if (resultIndex < BUFFER_SIZE) {
                result[resultIndex] = ';';
            }
        } else if (utf8 == 1 && str[index] < 0) {
            byte1 = (unsigned int) (str[index] & 0xff);
            byte2 = 0;
            if (index + 1 < stringLength) {
                byte2 = (unsigned int) (str[index + 1] & 0xff);
            }
            byte3 = 0;
            if (index + 2 < stringLength) {
                byte3 = (unsigned int) (str[index + 2] & 0xff);
            }
            byte4 = 0;
            if (index + 3 < stringLength) {
                byte4 = (unsigned int) (str[index + 3] & 0xff);
            }
            if ((byte1 & 0xf8) == 0xf0 && (byte2 & 0xc0) == 0x80 &&
                    (byte3 & 0xc0) == 0x80 && (byte4 & 0xc0) == 0x80) {
                newValue = ((byte1 & 0x07) << 18) | ((byte2 & 0x3f) << 12) |
                    ((byte3 & 0x3f) << 6) | (byte4 & 0x3f);
                snprintf(buffer, 33, "&#%i;", newValue);
                if (resultIndex + strlen(buffer) < BUFFER_SIZE) {
                    sprintf(result + resultIndex, "%s", buffer);
                }
                resultIndex += strlen(buffer) - 1;
                index += 3;
            } else if ((byte1 & 0xf0) == 0xe0 && (byte2 & 0xc0) == 0x80 &&
                    (byte3 & 0xc0) == 0x80) {
                newValue = ((byte1 & 0x0f) << 12) | ((byte2 & 0x3f) << 6) |
                    (byte3 & 0x3f);
                snprintf(buffer, 33, "&#%i;", newValue);
                if (resultIndex + strlen(buffer) < BUFFER_SIZE) {
                    sprintf(result + resultIndex, "%s", buffer);
                }
                resultIndex += strlen(buffer) - 1;
                index += 2;
            } else if ((byte1 & 0xe0) == 0xc0 && (byte2 & 0xc0) == 0x80) {
                newValue = ((byte1 & 0x1f) << 6) | (byte2 & 0x3f);
                snprintf(buffer, 33, "&#%u;", newValue);
                if (resultIndex + strlen(buffer) < BUFFER_SIZE) {
                    sprintf(result + resultIndex, "%s", buffer);
                }
                resultIndex += strlen(buffer) - 1;
                index += 1;
            } else {
                snprintf(buffer, 33, "&#%u;", byte1);
                if (resultIndex + strlen(buffer) < BUFFER_SIZE) {
                    sprintf(result + resultIndex, "%s", buffer);
                }
                resultIndex += strlen(buffer) - 1;
            }
        } else {
            result[resultIndex] = str[index];
        }
        if (resultIndex < BUFFER_SIZE) {
            ++resultIndex;
        }
        ++index;
    }

    result[resultIndex] = '\0';
}

char
writeXml(const char* path, FileList* fileList, AlbumList* albumList)
{
    char result = 0;
    FILE *handle = fopen(path, "w");
    FileInfo *currFile = (FileInfo*) fileList->list;
    Album *currAlbum = (Album*) albumList->list;
    unsigned int index;
    char buffer[BUFFER_SIZE + 1];
    char converted[BUFFER_SIZE + 1];
    unsigned int songIndex;

    if (handle != 0) {
        buffer[BUFFER_SIZE] = '\0';
        converted[BUFFER_SIZE] = '\0';

        snprintf(buffer, BUFFER_SIZE, "<?xml version=\"1.0\" "
            "encoding=\"utf-8\"?>\n<JukeboxPlaylist>\n");
        fwrite(buffer, sizeof(char), strlen(buffer), handle);

        snprintf(buffer, BUFFER_SIZE, "    <FileList count=\"%u\">\n",
            fileList->count);
        fwrite(buffer, sizeof(char), strlen(buffer), handle);

        index = 0;
        while (index < fileList->count) {
            snprintf(buffer, BUFFER_SIZE,
                "        <file id=\"%s\" favorite=\"%i\">\n", currFile->id,
                currFile->favorite);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->filePath, 0);
            snprintf(buffer, BUFFER_SIZE,
                "            <filePath>%s</filePath>\n", converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->title, 1);
            snprintf(buffer, BUFFER_SIZE, "            <title>%s</title>\n",
                converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->album, 1);
            snprintf(buffer, BUFFER_SIZE, "            <album>%s</album>\n",
                converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->artist, 1);
            snprintf(buffer, BUFFER_SIZE, "            <artist>%s</artist>\n",
                converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->genre, 1);
            snprintf(buffer, BUFFER_SIZE, "            <genre>%s</genre>\n",
                converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            snprintf(buffer, BUFFER_SIZE, "            <year>%u</year>\n",
                currFile->year);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->comment, 1);
converted[0] = '\0';
            snprintf(buffer, BUFFER_SIZE,
                "            <comment>%s</comment>\n", converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currFile->albumArt, 0);
            snprintf(buffer, BUFFER_SIZE,
                "            <albumArt>%s</albumArt>\n", converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            snprintf(buffer, BUFFER_SIZE,
                "            <frameCount>%u</frameCount>\n",
                currFile->frameCount);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            snprintf(buffer, BUFFER_SIZE, "        </file>\n");
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            ++currFile;
            ++index;
        }

        snprintf(buffer, BUFFER_SIZE, "    </FileList>\n");
        fwrite(buffer, sizeof(char), strlen(buffer), handle);

        snprintf(buffer, BUFFER_SIZE, "    <AlbumList count=\"%u\">\n",
            albumList->count);
        fwrite(buffer, sizeof(char), strlen(buffer), handle);

        index = 0;
        while (index < albumList->count) {
            snprintf(buffer, BUFFER_SIZE, "        <Album id=\"%s\" name=\"",
                currAlbum->id);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currAlbum->name, 1);
            snprintf(buffer, BUFFER_SIZE,
                "%s\" count=\"%i\" shuffle=\"%i\" repeat=\"%i\"", converted,
                currAlbum->count, currAlbum->shuffle, currAlbum->repeat);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            convertForXml(converted, currAlbum->albumArt, 0);
            snprintf(buffer, BUFFER_SIZE, " albumArt=\"%s\">\n", converted);
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            if (currAlbum->algorithm != 0) {
                convertForXml(converted, currAlbum->algorithm, 1);
                snprintf(buffer, BUFFER_SIZE,
                    "            <algorithm>%s</algorithm>\n",
                    converted);
                fwrite(buffer, sizeof(char), strlen(buffer), handle);
            }

            songIndex = 0;
            while (songIndex < currAlbum->count) {
                snprintf(buffer, BUFFER_SIZE, "            <song>%s</song>\n",
                    currAlbum->songs[songIndex]);
                fwrite(buffer, sizeof(char), strlen(buffer), handle);
                ++songIndex;
            }

            snprintf(buffer, BUFFER_SIZE, "        </Album>\n");
            fwrite(buffer, sizeof(char), strlen(buffer), handle);

            ++currAlbum;
            ++index;
        }

        snprintf(buffer, BUFFER_SIZE, "    </AlbumList>\n");
        fwrite(buffer, sizeof(char), strlen(buffer), handle);

        snprintf(buffer, BUFFER_SIZE, "</JukeboxPlaylist>\n");
        fwrite(buffer, sizeof(char), strlen(buffer), handle);

        fclose(handle);
    } else {
        result = 1;
    }

    return result;
}

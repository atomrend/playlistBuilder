#include <dirent.h>
#include "ID3Tag.h"
#include "JukeboxPlaylist.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "XmlReader.h"
#include "XmlWriter.h"

char*
generateID()
{
    static char *result = 0;
    unsigned char index = 0;
    char randNum;

    if (result == 0) {
        result = (char*) malloc(17 * sizeof(char));
        result[16] = '\0';
    }

    while (index < 16) {
        randNum = (char) rand() % 85 + 40;
        if ((randNum >= 40 && randNum <= 59) ||
                (randNum >= 63 && randNum <= 90) ||
                (randNum >= 95 && randNum <= 125)) {
            result[index] = randNum;
            ++index;
        }
    }
    result[16] = '\0';

    return result;
}

FileInfo*
findFileById(FileList* fileList, const char* id)
{
    FileInfo *result = 0;
    unsigned int index = 0;
    FileInfo *curr = (FileInfo*) fileList->list;

    while (index < fileList->count) {
        if (curr->id != 0 && strcmp(curr->id, id) == 0) {
            result = curr;
            break;
        }
        ++curr;
        ++index;
    }

    return result;
}

char
isMP3(const char* path)
{
    char result = 0;

    if (strncmp(path + strlen(path) - 4, ".mp3", 4) == 0) {
        result = 1;
    }

    return result;
}

void
checkDirectory(FileList* fileList, const char* dir)
{
    struct stat fileStat;
    struct dirent *dirFile;
    DIR *dirp = opendir(dir);
    char path[PATH_MAX + 1];
    char realPath[PATH_MAX + 1];
    int index = 0;
    FileInfo *currFileInfo = (FileInfo*) fileList->list;
    FileInfo *tmpFileInfoPtr;
    FileInfo *tmpList;
    char **sorted;
    unsigned int numFiles = 0;
    unsigned int tmpIndex;
    char buffer[257];
    char *tmpString;

    if (dirp != 0) {
        printf("Looking in directory: %s\n", dir);
        buffer[256] = '\0';

        strcpy(path, dir);
        path[strlen(dir)] = '/';
        path[strlen(dir) + 1] = '\0';

        /* Determine number of MP3 files in the directory. */
        numFiles = 0;
        while ((dirFile = readdir(dirp))) {
            if (strcmp(dirFile->d_name, ".") != 0 &&
                    strcmp(dirFile->d_name, "..") != 0) {
                if (isMP3(dirFile->d_name) == 1) {
                    ++numFiles;
                }
            }
        }

        if (numFiles > 0) {
            /* Sort the file names. */
            sorted = (char**) malloc(numFiles * sizeof(char*));
            memset(sorted, 0, numFiles * sizeof(char*));
            index = 0;
            rewinddir(dirp);
            while ((dirFile = readdir(dirp))) {
                if (strcmp(dirFile->d_name, ".") != 0 &&
                        strcmp(dirFile->d_name, "..") != 0) {
                    if (isMP3(dirFile->d_name) == 1 && index < numFiles) {
                        sorted[index] =
                            (char*) malloc(strlen(dirFile->d_name) + 1);
                        memset(sorted[index], '\0',
                            strlen(dirFile->d_name) + 1);
                        strcpy(sorted[index], dirFile->d_name);
                        ++index;
                    }
                }
            }

            index = 0;
            while (index < numFiles - 1) {
                tmpIndex = index + 1;
                while (tmpIndex < numFiles) {
                    if (strcmp(sorted[index], sorted[tmpIndex]) > 0) {
                        tmpString = sorted[index];
                        sorted[index] = sorted[tmpIndex];
                        sorted[tmpIndex] = tmpString;
                    }
                    ++tmpIndex;
                }
                ++index;
            }

            /* Allocate space for the files */
            tmpList = fileList->list;
            fileList->list = (FileInfo*) malloc(
                (fileList->count + numFiles) * sizeof(FileInfo));
            currFileInfo = (FileInfo*) fileList->list;
            tmpFileInfoPtr = (FileInfo*) tmpList;
            index = 0;
            while (index < fileList->count) {
                /* Copy the old information; */
                currFileInfo->id = tmpFileInfoPtr->id;
                currFileInfo->filePath = tmpFileInfoPtr->filePath;
                currFileInfo->title = tmpFileInfoPtr->title;
                currFileInfo->album = tmpFileInfoPtr->album;
                currFileInfo->artist = tmpFileInfoPtr->artist;
                currFileInfo->genre = tmpFileInfoPtr->genre;
                currFileInfo->comment = tmpFileInfoPtr->comment;
                currFileInfo->albumArt = tmpFileInfoPtr->albumArt;
                currFileInfo->year = tmpFileInfoPtr->year;
                currFileInfo->frameCount = tmpFileInfoPtr->frameCount;
                currFileInfo->favorite = tmpFileInfoPtr->favorite;

                ++currFileInfo;
                ++tmpFileInfoPtr;
                ++index;
            }
            free(tmpList);

            /* Zero out the new space. */
            fileList->count += numFiles;
            while (index < fileList->count) {
                currFileInfo->id = 0;
                currFileInfo->filePath = 0;
                currFileInfo->title = 0;
                currFileInfo->album = 0;
                currFileInfo->artist = 0;
                currFileInfo->genre = 0;
                currFileInfo->comment = 0;
                currFileInfo->albumArt = 0;
                currFileInfo->year = 0;
                currFileInfo->frameCount = 0;
                currFileInfo->favorite = 0;

                ++currFileInfo;
                ++index;
            }

            /* Check the files first. */
            currFileInfo = (FileInfo*) fileList->list;
            index = 0;
            while (index < fileList->count) {
                if (currFileInfo->id == 0) {
                    break;
                }
                ++currFileInfo;
                ++index;
            }

            index = 0;
            while (index < numFiles) {
                currFileInfo->id = (char*) malloc(17 * sizeof(char));
                memset(currFileInfo->id, '\0', 17 * sizeof(char));
                while (1) {
                    strcpy(buffer, generateID());
                    if (findFileById(fileList, buffer) == 0) {
                        strcpy(currFileInfo->id, buffer);
                        break;
                    }
                }

                strcpy(path + strlen(dir) + 1, sorted[index]);
                if (realpath(path, realPath) != 0) {
                    currFileInfo->filePath = (char*) malloc(
                        strlen((const char*) realPath) + 1);
                    memset(currFileInfo->filePath, '\0', strlen(realPath) + 1);
                    strcpy(currFileInfo->filePath, (const char*) realPath);
                } else {
                    currFileInfo->filePath = (char*) malloc(strlen(path) + 1);
                    memset(currFileInfo->filePath, '\0', strlen(path) + 1);
                    strcpy(currFileInfo->filePath, path);
                }

                readTags(currFileInfo);

                ++currFileInfo;
                ++index;
            }

            /* Free memory allocated for the sorting. */
            if (numFiles > 0) {
                index = numFiles - 1;
                while (index >= 0) {
                    free(sorted[index]);
                    --index;
                }
                free(sorted);
            }
        }

        /* If any directories exist within this directory,
            check that directory for any MP3 files. */

        /* Determine the number of directories within this directory. */
        numFiles = 0;
        rewinddir(dirp);
        while ((dirFile = readdir(dirp))) {
            if (strcmp(dirFile->d_name, ".") != 0 &&
                    strcmp(dirFile->d_name, "..") != 0) {
                strcpy(path + strlen(dir) + 1, dirFile->d_name);
                if (stat(path, &fileStat) == 0) {
                    if (S_ISDIR(fileStat.st_mode)) {
                        ++numFiles;
                    }
                }
            }
        }

        if (numFiles > 0) {
            /* Sort the directory names. */
            sorted = (char**) malloc(numFiles * sizeof(char*));
            memset(sorted, 0, numFiles * sizeof(char*));
            index = 0;
            rewinddir(dirp);
            while ((dirFile = readdir(dirp))) {
                if (strcmp(dirFile->d_name, ".") != 0 &&
                        strcmp(dirFile->d_name, "..") != 0) {
                    strcpy(path + strlen(dir) + 1, dirFile->d_name);
                    if (stat(path, &fileStat) == 0) {
                        if (S_ISDIR(fileStat.st_mode)) {
                            sorted[index] =
                                (char*) malloc(strlen(dirFile->d_name) + 1);
                            memset(sorted[index], '\0',
                                strlen(dirFile->d_name) + 1);
                            strcpy(sorted[index], dirFile->d_name);
                            ++index;
                        }
                    }
                }
            }
            index = 0;
            while (index < numFiles - 1) {
                tmpIndex = index + 1;
                while (tmpIndex < numFiles) {
                    if (strcmp(sorted[index], sorted[tmpIndex]) > 0) {
                        tmpString = sorted[index];
                        sorted[index] = sorted[tmpIndex];
                        sorted[tmpIndex] = tmpString;
                    }
                    ++tmpIndex;
                }
                ++index;
            }

            index = 0;
            while (index < numFiles) {
                strcpy(path + strlen(dir) + 1, sorted[index]);
                checkDirectory(fileList, path);
                ++index;
            }

            /* Free memory allocated for the sorting. */
            index = numFiles - 1;
            while (index >= 0) {
                free(sorted[index]);
                --index;
            }
            free(sorted);
        }

        closedir(dirp);
    }
}

int
main(int argc, char** argv)
{
    char *outputXML = 0;
    FileList fileList;
    AlbumList albumList;
    char pathBuffer[PATH_MAX + 1];

    fileList.list = 0;
    fileList.count = 0;
    albumList.list = 0;
    albumList.count = 0;

    /* buildPlaylist <output XML> <existing XML (optional)> */
    if (argc > 1) {
        outputXML = argv[1];
    }
    if (argc > 2) {
        readPlaylistFile(argv[2], &fileList, &albumList);
    }

    if (outputXML != 0 && getcwd(pathBuffer, PATH_MAX) != 0) {
        srand(time(0));
        checkDirectory(&fileList, pathBuffer);
        writeXml(outputXML, &fileList, &albumList);
    }

    return 0;
}

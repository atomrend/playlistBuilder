MODULE=playlistBuilder
EXECUTABLE=playlistBuilder

DEFINES+= \
    -D__BYTE_ORDER=__LITTLE_ENDIAN \

LIBS+= \
    -lexpat \

SOURCES= \
    ID3Tag.c \
    main.c \
    XmlReader.c \
    XmlWriter.c \

include Makefile.template

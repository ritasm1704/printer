#ifndef DATAMSG_H
#define DATAMSG_H

class DataMsg {

public:
    uint8_t* offset;
    size_t size;

};

enum class ReadingStatus {reading_continues, reading_is_stopped};

#endif
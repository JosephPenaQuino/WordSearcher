#ifndef CLION_MAIN_H
#define CLION_MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum States {START, MIDDLE, FINAL};

typedef struct {
    enum States state;
    char label_name[30];
    char current_index_on_MIDDLE;
    uint8_t label_length;
    int start_index_last_input;
    int end_index_last_input;
    int temp_start;
} Automata;

typedef struct {
    char * file;
    char * name;
} SearchParameters;

void insert_label(Automata *automata, char const label[], uint8_t length);
void refresh_state(Automata *automata, char input, int index);
void print_information(SearchParameters info_to_search);

#endif //CLION_MAIN_H

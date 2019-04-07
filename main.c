/*
 *
 *
 * Author:  Joseph Pena
 *
 * */

#include "main.h"

int main(int argc, char const *argv[])
{

    SearchParameters information_list[4];
    information_list[0].file="cpuinfo";
    information_list[0].name="model name\t: ";
//    TODO: Continue writing the information list

    for (int i = 0; i < 1; ++i) {
        print_information(information_list[i]);
    }
    return 0;
}

void print_information(SearchParameters info_to_search) {
    Automata automata;
    insert_label(&automata, info_to_search.name, (uint8_t)strlen(info_to_search.name)-1);

    char current_char;
    int current_char_position = 0;
    FILE *p_file;

    p_file = fopen(info_to_search.file, "r");

    if (p_file == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while((current_char = (char)fgetc(p_file)) != EOF && automata.state != FINAL) {
        refresh_state(&automata, current_char, current_char_position);
        current_char_position++;
    }

    while((current_char = (char)fgetc(p_file)) != EOF && current_char != '\n')  {
        printf("%c", current_char);
    }

    fclose(p_file);
}

void insert_label(Automata *automata, char const label[], uint8_t length) {
    int i;
    for (i = 0; i < length; i++)
    {
        automata->label_name[i] = label[i];
    }
    automata->label_length = length;
}

void refresh_state(Automata *automata, char input, int index) {
    switch(automata->state)
    {
        case START:
            if (input == automata->label_name[0])
            {
                automata->temp_start = index;
                automata->current_index_on_MIDDLE = 1;
                automata->state = MIDDLE;
            }
            break;

        case MIDDLE:
            if (input == automata->label_name[automata->current_index_on_MIDDLE])
            {
                if (automata->current_index_on_MIDDLE < automata->label_length-1)
                    automata->current_index_on_MIDDLE++;
                else
                    automata->state = FINAL;
            }
            else
            {
                automata->state = START;
            }
            break;

        case FINAL:
            automata->start_index_last_input = automata->temp_start;
            automata->end_index_last_input = index;
            break;

        default:

            break;
    }
}
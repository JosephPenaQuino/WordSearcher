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
    information_list[0].file="/proc/cpuinfo";
    information_list[0].name="model name\t: ";
    information_list[1].file="/proc/meminfo";
    information_list[1].name="MemTotal:       ";
    information_list[2].file="/proc/version";
    information_list[2].name="Linux version ";
    information_list[3].file="/proc/stat";
    information_list[3].name="btime ";

    for (int i = 0; i < 4; ++i) {
        printf("%s", information_list[i].name);
        print_information(information_list[i]);
    }

    last_login[10] = '\n';
    char * ptr;
    time_t curtime = (int)strtol(last_login, &ptr, 10);
    printf("Last login= %s", ctime(&curtime));

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
    int xd = 0;
    while((current_char = (char)fgetc(p_file)) != EOF && current_char != '\n')  {
        printf("%c", current_char);
        last_login[xd] = current_char;
        xd++;
    }
    printf("\n");
    fclose(p_file);
}

void insert_label(Automata *automata, char const label[], uint8_t length) {
    int i;
    automata->state = START;
    automata->start_index_last_input = 0;
    automata->current_index_on_MIDDLE = 0;
    automata->end_index_last_input = 0;
    automata->temp_start = 0;
    for (i = 0; i < length; i++)
    {
        automata->label_name[i] = label[i];
    }
    automata->label_length = length;
}

void refresh_state(Automata *automata, char input, int index)
{
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
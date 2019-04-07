/*
 *
 *
 * Author:  Joseph Pena
 *
 * */

#include "main.h"

int main(int argc, char const *argv[])
{
    char ch;
    char file_name[] = "cpuinfo";
    char label_name[] = "model name\t:";

    FILE *fp;

    Automata automata;

    insert_label(&automata, label_name, (uint8_t)sizeof(label_name)-1);

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    
    while((ch = (char)fgetc(fp)) != EOF && automata.state != FINAL) {
        refresh_state(&automata, ch, cnt);
        cnt++;
    }

    while((ch = (char)fgetc(fp)) != EOF && ch != '\n')  {
        printf("%c", ch);
        cnt++;
    }
    fclose(fp);

    return 0;
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
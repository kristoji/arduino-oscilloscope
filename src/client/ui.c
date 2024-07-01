#include "ui.h"

int8_t get_num()
{
    int8_t res;
    scanf("%hhd", &res);
    return res;
}

int8_t display_menu(ui_t* options)
{
    int8_t res;

    do 
    {
        printf("\n--------------------------------\n");
        printf("Select an option:\n");
        printf("    0. Set channels\t[curr msk: %2x]\n", options->channel_msk);
        printf("    1. Set frequency\t[curr Hz: %d]\n", options->frequency);
        printf("    2. Set mode\t\t[curr mode: %s]\n", !options->mode? "continuous": (options->mode == 1? "buffered" : "stop"));
        printf("    3. Start sampling\n");
        printf("    4. Exit\n");
        printf("> ");

        res = get_num();

    } while (res < 0 || res > 4);

    return res;
}

void set_channels(ui_t* options)
{
    int8_t res;
    options->channel_msk = 0;
    
    do 
    {
        printf("\nCurrent mask: %2x\n", options->channel_msk);
        printf("Insert a channel to sample between [0:15] (-1 to finish): ");
        res = get_num();

        if (res >= 0 && res <= 15)
        {
            options->channel_msk |= (1<<res);            
        }
        else if (res != -1)
        {
            printf("Invalid!\n");
        }

    } while (res != -1);

}

void set_freq(ui_t* options)
{
    uint8_t res;

    do
    {
        printf("Insert a frequency between [1:20] Hz: ");
        res = get_num();
    } while (res < 1 || res > MAX_FREQ);

    options->frequency = res;
}

void set_mode(ui_t* options)
{
    uint8_t res;

    do
    {
        printf("Insert a mode (0: continuous, 1: buffered, 2: stop): ");
        res = get_num();
    } while (res < 0 || res > 2);

    options->mode = res;
}

uint8_t ui_menu(ui_t* options)
{
    uint8_t res = display_menu(options);

    switch (res)
    {
        case 0:
            set_channels(options);
            break;

        case 1:
            set_freq(options);
            break;

        case 2:
            set_mode(options);
            break;

        case 3:
            send_settings(options);

            if (options->mode == 1)
            {
                sample_buf(options);
            }
            else if (options->mode == 0)
            {
                sample_cont(options);
            }
            break;

        case 4:
            return 0;

        default:
            break;
    }
    return 1;
}
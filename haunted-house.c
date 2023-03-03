#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROOMS 6
#define MAX_GHOSTS 5
#define MAX_ITEMS 5

int health = 100;
int rooms_visited[MAX_ROOMS] = {0};
int room_items[MAX_ROOMS][MAX_ITEMS] = {{0}};
int num_ghosts = 0;
int has_flashlight = 0;
int crucifix_used = 0;
int has_shotgun = 0;
int has_key = 0;
int rooms_connected = 0;
int exit_room = 0;

void print_room(int room_num);
void print_map();
void print_status();
void generate_ghosts();
int move_player(int current_room);
int fight_ghost(int current_room);
void use_item(int current_room);

int my_func()
{
    srand(time(NULL));

    printf("Welcome to The Haunted House!\n");
    printf("You are trapped in a haunted house and must find your way out while avoiding ghosts and other supernatural entities.\n");
    printf("You have 100 health points. If your health reaches 0, you will die.\n");
    printf("Good luck!\n\n");

    int current_room = 0;
    int previous_room = 0;
    int moves = 0;
    const char *directions[previous_room][current_room] = {
        {"", "north", "", "east", "", ""}, // Room 0
        {"south", "", "", "east", "", ""}, // Room 1
        {"", "", "west", "", "north", ""}, // Room 2
        {"", "west", "", "", "", ""},      // Room 3
        {"", "", "", "", "", "south"},     // Room 4
        {"", "", "", "", "south", ""}      // Room 5
    };
    
    while (1)
    {
        print_status();
        print_map();
        print_room(current_room);

        if (rooms_visited[current_room] == 0)
        {
            rooms_visited[current_room] = 1;
            generate_ghosts();
        }

        if (num_ghosts > 0)
        {
            int result = fight_ghost(current_room);
            if (result == 0)
            {
                printf("You were killed by a ghost!\n");
                printf("Game over.\n");
                return 0;
            }
            else
            {
                num_ghosts -= result;
            }
        }

        int result = move_player(current_room);
        if (result == -1)
        {
            printf("You have exited the haunted house!\n");
            printf("Congratulations, you have won the game!\n");
            return 0;
        }
        else
        {
            current_room = result;
        }

        moves++;
        if (moves % 5 == 0)
        {
            printf("You feel a chill down your spine...\n");
            generate_ghosts();
        }
    }

    return 0;
}

void print_room(int room_num)
{
    switch (room_num)
    {
    case 0:
        printf("You are in the entrance hall.\n");
        printf("You see a dusty chandelier hanging from the ceiling and a creepy painting on the wall.\n");
        break;
    case 1:
        printf("You are in the dining room.\n");
        printf("You see a large table with rotting food on it and a strange noise coming from the kitchen.\n");
        break;
    case 2:
        printf("You are in the kitchen.\n");
        printf("You see a stove with a pot boiling on it and a door leading to the basement.\n");
        break;
    case 3:
        printf("You are in the basement.\n");
        printf("You see a dark room with cobwebs and a musty smell.\n");
        break;
    case 4:
        printf("You are in the living room.\n");
        printf("You see a couch and a TV with static on the screen.\n");
        break;
    case 5:
        printf("You are in the bedroom.\n");
        printf("You see a bed with tattered sheets and a closet with the door slightly open.\n");
        break;
    default:
        break;
    }

    if (room_items[room_num][0] == 1)
    {
        printf("There is a flashlight on the ground.\n");
    }

    if (room_items[room_num][1] == 1)
    {
        printf("There is a crucifix on the wall.\n");
    }
    if (room_items[room_num][2] == 1)
    {
        printf("There is a first-aid kit on the shelf.\n");
    }
    if (room_items[room_num][3] == 1)
    {
        printf("There is a shotgun on the table.\n");
    }
    if (room_items[room_num][4] == 1)
    {
        printf("There is a key on the ground.\n");
    }
}

void generate_ghosts()
{
    num_ghosts = rand() % (MAX_GHOSTS + 1);
}

int move_player(int current_room)
{
    char direction[10];

    printf("Which direction do you want to go? (north, south, east, west)\n");
    scanf("%s", direction);

    if (strcmp(direction, "north") == 0)
    {
        if (current_room == 1 || current_room == 2)
        {
            printf("You have entered a hidden passage!\n");
            return 6;
        }
        else if (current_room == 6)
        {
            return 1;
        }
    }
    else if (strcmp(direction, "south") == 0)
    {
        if (current_room == 1 || current_room == 2)
        {
            printf("You have entered a hidden passage!\n");
            return 7;
        }
        else if (current_room == 7)
        {
            return 2;
        }
    }
    else if (strcmp(direction, "east") == 0)
    {
        if (current_room == 0)
        {
            return 1;
        }
        else if (current_room == 1)
        {
            return 2;
        }
        else if (current_room == 2)
        {
            return 3;
        }
        else if (current_room == 4)
        {
            return 5;
        }
    }
    else if (strcmp(direction, "west") == 0)
    {
        if (current_room == 1)
        {
            return 0;
        }
        else if (current_room == 2)
        {
            return 1;
        }
        else if (current_room == 3)
        {
            return 2;
        }
        else if (current_room == 5)
        {
            return 4;
        }
    }

    printf("You cannot go in that direction.\n");
    return current_room;
}

int fight_ghost(int current_room)
{
    int player_attack = rand() % 21 + 10;
    int ghost_health = rand() % 41 + 10;

    printf("You have encountered a ghost!\n");

    while (1)
    {
        printf("Your health: %d\n", health);
        printf("Ghost's health: %d\n", ghost_health);

        char action[10];
        printf("What do you want to do? (fight, use item, run)\n");
        scanf("%s", action);

        if (strcmp(action, "fight") == 0)
        {
            ghost_health -= player_attack;
            printf("You attack the ghost for %d damage!\n", player_attack);
            if (ghost_health <= 0)
            {
                printf("You have defeated the ghost!\n");
                if (room_items[current_room][4] == 0)
                {
                    room_items[current_room][4] = 1;
                    printf("The ghost drops a key!\n");
                }
                return current_room;
            }
            if (health <= 0)
            {
                printf("You have been defeated by the ghost.\n");
                exit(0);
            }
        }
        else if (strcmp(action, "use item") == 0)
        {
            int num_items = 0;
            if (room_items[current_room][0] == 1)
            {
                printf("%d. Flashlight\n", ++num_items);
            }
            if (room_items[current_room][1] == 1)
            {
                printf("%d. Crucifix\n", ++num_items);
            }
            if (room_items[current_room][2] == 1)
            {
                printf("%d. First-aid kit\n", ++num_items);
            }
            if (room_items[current_room][3] == 1)
            {
                printf("%d. Shotgun\n", ++num_items);
            }
            if (num_items == 0)
            {
                printf("There are no items in this room.\n");
            }
            else
            {
                int item_choice;
                printf("Which item do you want to use? (1-%d)\n", num_items);
                scanf("%d", &item_choice);

                if (item_choice < 1 || item_choice > num_items)
                {
                    printf("Invalid choice.\n");
                }
                else
                {
                    if (item_choice == 1)
                    {
                        if (has_flashlight)
                        {
                            printf("You already have a flashlight.\n");
                        }
                        else
                        {
                            printf("You pick up the flashlight.\n");
                            has_flashlight = 1;
                        }
                    }
                    else if (item_choice == 2)
                    {
                        printf("You hold the crucifix tightly.\n");
                        crucifix_used = 1;
                    }
                    else if (item_choice == 3)
                    {
                        printf("You use the first-aid kit to heal yourself.\n");
                        health += 20;
                        if (health > 100)
                        {
                            health = 100;
                        }
                    }
                    else if (item_choice == 4)
                    {
                        if (has_shotgun)
                        {
                            printf("You already have the shotgun.\n");
                        }
                        else
                        {
                            printf("You pick up the shotgun.\n");
                            has_shotgun = 1;
                        }
                    }
                }
            }
        }
        else if (strcmp(action, "run") == 0)
        {
            printf("You run away from the ghost.\n");
            return current_room;
        }
        else
        {
            printf("Invalid action.\n");
        }
    }
}

int main()
{
    srand(time(0));

    generate_ghosts();

    printf("Welcome to The Haunted House.\n");
    printf("You have entered the house and the door has locked behind you.\n");
    printf("You must find a way out before the ghosts get you!\n");

    int current_room = 0;
    int previous_room;

    while (1)
    {
        print_map();
        print_status();
        print_room(current_room);

        if (num_ghosts > 0)
        {
            int chance_encounter = rand() % 2;
            if (chance_encounter == 0)
            {
                printf("You hear a faint whisper in the distance...\n");
            }
            else
            {
                printf("You sense a ghostly presence nearby!\n");
                current_room = fight_ghost(current_room);
                num_ghosts--;
                continue;
            }
        }

        previous_room = current_room;
        current_room = move_player(current_room);
        const char *directions[previous_room][current_room] = {
            {"", "north", "", "east", "", ""}, // Room 0
            {"south", "", "", "east", "", ""}, // Room 1
            {"", "", "west", "", "north", ""}, // Room 2
            {"", "west", "", "", "", ""},      // Room 3
            {"", "", "", "", "", "south"},     // Room 4
            {"", "", "", "", "south", ""}      // Room 5
        };
        if (current_room == previous_room)
        {
            printf("You are already in this room.\n");
        }
        else if (rooms_connected[current_room][previous_room] == 1)
        {
            printf("You move to the %s.\n", directions[previous_room][current_room]);
            if (room_items[current_room][0] == 1)
            {
                printf("There is a flashlight on the ground.\n");
            }
            else if (room_items[current_room][1] == 1)
            {
                printf("There is a note on the table.\n");
            }
            else if (room_items[current_room][2] == 1)
            {
                printf("There is a dusty old book on the shelf.\n");
            }
            else if (room_items[current_room][3] == 1)
            {
                printf("There is a mirror on the wall.\n");
            }
            else
            {
                printf("There is nothing of interest in this room.\n");
            }
            if (room_items[current_room][4] == 1 && has_key == 0)
            {
                printf("There is a key on the ground.\n");
            }
        }
        else
        {
            printf("You cannot go that way.\n");
            current_room = previous_room;
        }

        // Check if player has encountered a ghost
        if (num_ghosts > 0)
        {
            int chance_encounter = rand() % 2;
            if (chance_encounter == 0)
            {
                printf("You hear a faint whisper in the distance...\n");
            }
            else
            {
                printf("You sense a ghostly presence nearby!\n");
                current_room = fight_ghost(current_room);
                num_ghosts--;
                continue;
            }
        }
    }

    // Check if player has won the game by reaching the exit with the key
    if (current_room == exit_room && has_key == 1)
    {
        printf("Congratulations! You have escaped the haunted house!\n");
    }
    else
    {
        printf("You have been trapped in the haunted house forever...\n");
    }

    // Game over
    printf("\nGame over.\n");
    printf("Thanks for playing!\n");

    return 0;
}

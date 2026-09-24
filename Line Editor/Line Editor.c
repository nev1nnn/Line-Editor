#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

int main()
{
    char lines[MAX_LINES][MAX_LENGTH];
    char backup[MAX_LINES][MAX_LENGTH];

    int count = 0;
    int backupCount = 0;
    int canUndo = 0;

    int command;

   printf("\n");
printf("+--------------------------------------+\n");
printf("|              LINE EDITOR             |\n");
printf("|        Mini Terminal Text Editor     |\n");
printf("+--------------------------------------+\n");
    while (1)
    {
        printf("\n1-Add\n2-Insert\n3-View\n4-Edit");

        printf("\n5-Delete\n6-Find\n7-Replace");
        printf("\n8-Undo\n9-Count\n0-Quit");
        printf("\n\nEnter command: ");

        scanf(" %d", &command);
        getchar();

        /* ================= ADD ================= */

        if (command == 1)
        {
            if (count == MAX_LINES)
            {
                printf("Document is full!\n");
                continue;
            }

            /* Save current document for undo */
            backupCount = count;

            for (int i = 0; i < count; i++)
                strcpy(backup[i], lines[i]);

            canUndo = 1;

            printf("Enter text: ");
            fgets(lines[count], MAX_LENGTH, stdin);

            lines[count][strcspn(lines[count], "\n")] = '\0';

            count++;

            printf("Line added successfully.\n");
        }

        /* ================= INSERT ================= */

        else if (command == 2)
        {
            int pos;

            if (count == MAX_LINES)
            {
                printf("Document is full!\n");
                continue;
            }

            printf("Enter line number to insert before: ");
            scanf("%d", &pos);
            getchar();

            if (pos < 1 || pos > count + 1)
            {
                printf("Invalid line number!\n");
                continue;
            }

            /* Save current document for undo */
            backupCount = count;

            for (int i = 0; i < count; i++)
                strcpy(backup[i], lines[i]);

            canUndo = 1;

            /* Shift lines to the right */
            for (int i = count; i >= pos; i--)
            {
                strcpy(lines[i], lines[i - 1]);
            }

            printf("Enter text: ");
            fgets(lines[pos - 1], MAX_LENGTH, stdin);

            lines[pos - 1][strcspn(lines[pos - 1], "\n")] = '\0';

            count++;

            printf("Line inserted successfully.\n");
        }

        /* ================= VIEW ================= */

        else if (command == 3)
        {
            if (count == 0)
            {
                printf("\nDocument is empty!\n");
            }
            else
            {
                printf("\n----------- DOCUMENT -----------\n");

                for (int i = 0; i < count; i++)
                {
                    printf("%d. %s\n", i + 1, lines[i]);
                }

                printf("--------------------------------\n");
            }
        }

        /* ================= EDIT ================= */

        else if (command == 4)
        {
            int line;

            printf("Enter line number to edit: ");
            scanf("%d", &line);
            getchar();

            if (line < 1 || line > count)
            {
                printf("Invalid line number!\n");
                continue;
            }

            /* Save current document for undo */
            backupCount = count;

            for (int i = 0; i < count; i++)
                strcpy(backup[i], lines[i]);

            canUndo = 1;

            printf("Old text: %s\n", lines[line - 1]);

            printf("Enter new text: ");
            fgets(lines[line - 1], MAX_LENGTH, stdin);

            lines[line - 1][strcspn(lines[line - 1], "\n")] = '\0';

            printf("Line edited successfully.\n");
        }

        /* ================= DELETE ================= */

        else if (command == 5)
        {
            int line;

            printf("Enter line number to delete: ");
            scanf("%d", &line);
            getchar();

            if (line < 1 || line > count)
            {
                printf("Invalid line number!\n");
                continue;
            }

            /* Save current document for undo */
            backupCount = count;

            for (int i = 0; i < count; i++)
                strcpy(backup[i], lines[i]);

            canUndo = 1;

            /* Shift lines to the left */
            for (int i = line - 1; i < count - 1; i++)
            {
                strcpy(lines[i], lines[i + 1]);
            }

            count--;

            printf("Line deleted successfully.\n");
        }

        /* ================= FIND ================= */

        else if (command == 6)
        {
            char word[MAX_LENGTH];
            int found = 0;

            printf("Enter text to find: ");
            fgets(word, MAX_LENGTH, stdin);

            word[strcspn(word, "\n")] = '\0';

            for (int i = 0; i < count; i++)
            {
                if (strstr(lines[i], word) != NULL)
                {
                    printf("Found in line %d: %s\n",
                           i + 1, lines[i]);

                    found = 1;
                }
            }

            if (!found)
            {
                printf("Text not found.\n");
            }
        }

        /* ================= FIND AND REPLACE ================= */

        else if (command == 7)
        {
            char find[MAX_LENGTH];
            char replace[MAX_LENGTH];

            int found = 0;

            printf("Enter text to find: ");
            fgets(find, MAX_LENGTH, stdin);

            find[strcspn(find, "\n")] = '\0';

            printf("Enter replacement text: ");
            fgets(replace, MAX_LENGTH, stdin);

            replace[strcspn(replace, "\n")] = '\0';

            /* Save document for undo */
            backupCount = count;

            for (int i = 0; i < count; i++)
                strcpy(backup[i], lines[i]);

            /*
             * Replace the first occurrence in each line.
             * This keeps the code simple.
             */
            for (int i = 0; i < count; i++)
            {
                char *position = strstr(lines[i], find);

                if (position != NULL)
                {
                    char newLine[MAX_LENGTH];

                    int before = position - lines[i];

                    snprintf(newLine,
                             MAX_LENGTH,
                             "%.*s%s%s",
                             before,
                             lines[i],
                             replace,
                             position + strlen(find));

                    strcpy(lines[i], newLine);

                    found = 1;
                }
            }

            if (found)
            {
                canUndo = 1;
                printf("Text replaced successfully.\n");
            }
            else
            {
                printf("Text not found.\n");
                canUndo = 0;
            }
        }

        /* ================= UNDO ================= */

        else if (command == 8)
        {
            if (canUndo == 0)
            {
                printf("Nothing to undo.\n");
            }
            else
            {
                count = backupCount;

                for (int i = 0; i < count; i++)
                {
                    strcpy(lines[i], backup[i]);
                }

                canUndo = 0;

                printf("Last action undone successfully.\n");
            }
        }

        /* ================= COUNT ================= */

        else if (command == 9)
        {
            int words = 0;

            for (int i = 0; i < count; i++)
            {
                char temp[MAX_LENGTH];

                strcpy(temp, lines[i]);

                char *word = strtok(temp, " \t");

                while (word != NULL)
                {
                    words++;

                    word = strtok(NULL, " \t");
                }
            }

            printf("\n========== DOCUMENT COUNT ==========\n");
            printf("Number of lines : %d\n", count);
            printf("Number of words : %d\n", words);
            printf("====================================\n");
        }

        /* ================= QUIT ================= */

        else if (command == 0)
        {
            printf("\nThank you for using the editor!\n");
            break;
        }

        /* ================= INVALID ================= */

        else
        {
            printf("Invalid command!\n");
        }
    }

    return 0;
}
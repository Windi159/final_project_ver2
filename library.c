#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <io.h>

#define EMPTY ' '

struct canvas
{
    char user_input;
    char array[20][71];
};

void printing(struct canvas *show_setting)
{
    for(int row = 0; row <= 21; row++)
    {
        if(row <= 1)
            printf("**");

        else
        {
            if(row <= 10)
                printf("0");

            printf("%d", row - 1);
        }


        for(int col = 0; col < 70; col++)
        {
            if(row == 0)
                printf("%d", (col + 1) % 10);

            else if(row == 1)
                printf("*");

            else
                printf("%c", show_setting -> array[row - 2][col]);
        }
        printf("\n");
    }
}

void save_file(struct canvas *save_setting, char *named_file, int size)
{
    FILE* user_text_file;
    char name[size];

    for(int i = 0; i <= size; i++)
        name[i] = *(named_file + i);

    user_text_file = fopen(named_file, "w");

    save_setting -> array[19][70] = '\0';
    fprintf(user_text_file, save_setting -> array);

    fclose(user_text_file);
}

void naming_file(struct canvas *file_setting)
{
    char *user_named_file;
    char override;
    int len = 0;

    user_named_file = calloc(81, sizeof(char));

    printf("���� �̸��� �����ּ���. �̸��� �ִ� ���̴� 80�Դϴ�.\n");
    scanf( " %s", user_named_file);

    while(user_named_file[len] != '\0')
        len++;

    if(_access(user_named_file, 0) != 0)
        save_file(file_setting, user_named_file, len);

    else
    {
        while(true)
        {
            printf("������ ���ϸ��� �����մϴ�. ���� ���ðڽ��ϱ�?(y, n)\n");
            scanf(" %c", &override);

            if(override == 'y' || override == 'Y')
            {
                save_file(file_setting, user_named_file, len);
                break;
            }

            else if(override == 'n' || override == 'N')
            {
                printf("�ٸ� �̸��� �Է����ּ���.\n");
                naming_file(file_setting);
                break;
            }

            else
                continue;
        }
    }
}

void initialize(struct canvas *array)
{
    for(int row = 0; row <= 19; row++)
    {
        for(int col = 0; col <= 69; col++)
            array -> array[row][col] = EMPTY;

        array -> array[row][70] = '\n';
    }
}

void load_file(struct canvas *array)
{
    FILE *loading_file;
    char *find_file = calloc(81, sizeof(char));
    char contents[71];

    printf("ã������ ������ �̸��� �Է����ּ���.\n");
    scanf("%s", find_file);

    if (_access(find_file, 0) == 0)
    {
        loading_file = fopen(find_file, "r");

        if (loading_file != NULL)
        {
            for (int row = 0; row <= 19; row++)
            {
                fgets(contents, 78, loading_file);
                for (int col = 0; col < 70; col++)
                    array->array[row][col] = contents[col];
            }

            fclose(loading_file);
        }
        else
        {
            printf("���� %s��(��) �� �� �����ϴ�.\n", find_file);
        }
    }
    else
    {
        printf("%s ��� ������ ã�� �� �����ϴ�.\n", find_file);
    }
}

int main() {
    struct canvas setting;

    char mode_select;
    int x, y;

    initialize(&setting);

    while (true) {
        printing(&setting);

        while(true)
        {
            printf("\n             ����� ����� �������ּ���.\n");
            printf("1.�׸��� 2.����� 3.�����ϱ� 4.�ҷ����� 5.�� ȭ�� 6.����\n");

            scanf(" %c", &mode_select);

            if (mode_select == '1')
            {
                printf("� ���ڸ� ǥ���Ͻðڽ��ϱ�?\n");
                scanf(" %c", &setting.user_input);

                printf("��� ���ڸ� ǥ���Ͻðڽ��ϱ�?\n�Է� ���� : ���� ����\n");
                scanf(" %d %d", &x, &y);

                setting.array[y - 1][x - 1] = setting.user_input;

                break;
            }


            else if (mode_select == '2')
            {
                printf("��� ���ڸ� ����ðڽ��ϱ�?\n�Է� ���� : ���� ����\n");
                scanf(" %d %d", &x, &y);

                setting.array[y - 1][x - 1] = EMPTY;
                break;
            }


            else if (mode_select == '3')
            {
                naming_file(&setting);
                break;
            }

            else if (mode_select == '4')
            {
                load_file(&setting);
                break;
            }

            else if (mode_select == '5')
            {
                initialize(&setting);
                break;
            }

            else if (mode_select == '6')
                exit(2);

            else
            {
                printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
                break;
            }
        }

        system("cls");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <io.h>

#define EMPTY ' '

struct canvas
{
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
    fprintf(user_text_file, save_setting->array);

    fclose(user_text_file);
}

void naming_file(struct canvas *file_setting)
{
    char *user_named_file;
    char override;
    int len = 0;

    user_named_file = calloc(81, sizeof(char));

    printf("파일 이름을 정해주세요. 이름의 최대 길이는 80입니다.\n");
    scanf( " %s", user_named_file);

    while(user_named_file[len] != '\0')
        len++;

    if(_access(user_named_file, 0) != 0)
        save_file(file_setting, user_named_file, len);

    else
    {
        while(true)
        {
            printf("동일한 파일명이 존재합니다. 덮어 쓰시겠습니까?(y, n)\n");
            scanf(" %c", &override);

            if(override == 'y' || override == 'Y')
            {
                save_file(file_setting, user_named_file, len);
                break;
            }

            else if(override == 'n' || override == 'N')
            {
                printf("다른 이름을 입력해주세요.\n");
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

    printf("찾으려는 파일의 이름을 입력해주세요.\n");
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
            printf("파일 %s을(를) 열 수 없습니다.\n", find_file);
        }
    }
    else
    {
        printf("%s 라는 파일을 찾을 수 없습니다.\n", find_file);
    }
}

void indexArrange(int r[2], int l[2])
{
    int emp = 0;

    if(r[0] > r[1])
    {
        emp = r[0];
        r[0] = r[1];
        r[1] = emp;
    }
    
    if(l[0] > l[1])
    {
        emp = l[0];
        l[0] = l[1];
        l[1] = emp;
    }
}

void drawingLine(struct canvas *Canvas)
{
    int row[2], col[2], len = 0;

    printf("어디서 시작 하시겠습니까?\n 입력 예시 : 가로 세로\n");
    scanf(" %d %d", &row[0], &col[0]);

    printf("어디까지 잇겠습니까?\n 입력 예시 : 가로 세로\n");
    scanf(" %d %d", &row[1], &col[1]);

    indexArrange(row, col);
        
    int length[2] = {row[1] - row[0], col[1] - col[0]};

    for(int i = row[0]; i <= row[1]; i++)
    {
        for(int j = 0; j <= length[1] / length[0]; j++)
        {
            
        }
    }
}

void drawingToCanvas(struct canvas *draw)
{
    int row, col;
    char user_input, drawing;

    printf("어떤 문자를 표시하시겠습니까?\n");
    scanf(" %c", &user_input);

    printf("선을 그리시겠습니까? (y/n)\n");
    scanf(" %c", &drawing);

    if(drawing == 'y' || drawing == 'Y')
        drawingLine(draw);

    else if(drawing == 'n' || drawing == 'N')
    {
        printf("어디에 문자를 표시하시겠습니까?\n입력 예시 : 가로 세로\n");
        scanf(" %d %d", &row, &col);

        draw -> array[col - 1][row - 1] = user_input;
    }
}

void deleteToCanvas(struct canvas *erase)
{
    int row, col;
    char remove_all;

    printf("전부 지우시겠습니까? (y/n)\n");
    scanf(" %c", &remove_all);

    if(remove_all == 'y' || remove_all == 'Y')
        initialize(erase);

    else if(remove_all == 'n' || remove_all == 'N')
    {
        printf("어디에 문자를 지우시겠습니까?\n입력 예시 : 가로 세로\n");
        scanf(" %d %d", &row, &col);

        erase -> array[col - 1][row - 1] = EMPTY;
    }

    else
    {
        printf("잘못 입력하셨습니다. 다시 입력해주세요.\n");
        deleteToCanvas(erase);
    }
}

int modeSelect(struct canvas *Canvas)
{
    char mode_select;

    while(true)
    {
        printf("\n             사용할 기능을 선택해주세요.\n");
        printf("1.그리기 2.지우기 3.저장하기 4.불러오기 5.새 화면 6.종료\n");

        scanf(" %c", &mode_select);

        if (mode_select == '1')
        {
            drawingToCanvas(Canvas);
            break;
        }


        else if (mode_select == '2')
        {
            deleteToCanvas(Canvas);
            break;
        }


        else if (mode_select == '3')
        {
            naming_file(Canvas);
            break;
        }

        else if (mode_select == '4')
        {
            load_file(Canvas);
            break;
        }

        else if (mode_select == '5')
        {
            initialize(Canvas);
            break;
        }

        else if (mode_select == '6')
            break;

        else
        {
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    }

    system("cls");

    return atoi(&mode_select);
}

int main() {
    struct canvas setting;
    int end;

    initialize(&setting);

    while(true){
        printing(&setting);
        end = modeSelect(&setting);

        if(end == 6)
            exit(2);
    }
}

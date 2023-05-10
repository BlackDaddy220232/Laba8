#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
#include"intcheck.h"
int Inputcheck()
{
    rewind(stdin);
    char string[15];
    fgets(string, 15, stdin);
    string[14] = '\n';
    rewind(stdin);
    int symbolcnt = 0, result = 0, mincnt = 0, dot = 0, dotcnt = 0, pluscnt = 0;
    if (string[0] == '\n') // if (!string[0])
    {
        printf("\n\x1B[31mInvalid input.Empty field.Try again \033[0m \n");
        return Inputcheck();
    }
    for (int i = 0; string[i] != '\n'; i++)
    {
        if (string[i] == 44 || string[i] == 46)
        {
            dotcnt++; //подсчет точек
        }
        symbolcnt++; //Подсчет символов
        if (string[i] == 45)
        {
            mincnt++; //Подсчет минусов
        }
        if (string[i] == 43)
        {
            pluscnt++;
        }
        if ((string[0] == 45 || string[0] == 43) && (string[1] == 44 || string[1] == 46)) // Проверка на +- точки / запятые
        {
            printf("\n\x1B[31mInvalid input.Try again \033[0m \n");
            return Inputcheck();
        }
        // printf("%d\n", bn++);
    }
    if (string[0] == 44 || string[0] == 46) //Прверку на первую точку или запятую
    {
        printf("\n\x1B[31mInvalid input.Try again \033[0m \n");
        return Inputcheck();
    }
    if (symbolcnt > 9 || mincnt > 1 || dotcnt > 1 || pluscnt > 1) //Проеверка на переполнение и на колличесвто минусов
    {
        printf("\n\x1B[31mInvalid input.Try again \033[0m \n");
        return Inputcheck();
    }
    if (string[0] == 45 || string[0] == 43) //Если первый символ минус-сдвигаем массив влево
    {
        for (int i = 1; i < symbolcnt; i++)
        {
            string[i - 1] = string[i];
        }
    }
    for (int i = 0; string[i] != '\n'; i++) //поиск индекса точки/запятой
    {
        if (string[i] == 44 || string[i] == 46)
        {
            dot = i;
        }
    }
    if (dotcnt != 0) //Проверка на точку или запятую(если есть сдвигаем влево после запаятой/точки)
    {
        for (int i = dot + 1; i < symbolcnt; i++)
        {
            if (string[i] != 48)
            {
                printf("\n\x1B[31mInvalid input.Try again \033[0m \n");
                return Inputcheck();
            }
            string[i - 1] = string[i];
        }
        symbolcnt--;
    }
 
    for (int i = 0; string[i] != '\n'; i++)
    {
 
        if (string[i] < 48 || string[i] > 57) //Проверка на буквы
        {
            printf("\n\x1B[31mInvalid input.Try again \033[0m \n");
            return Inputcheck();
        }
    }
 
    int symbolcnt2 = symbolcnt; //Дубляж для цикла
 
    if ((mincnt == 1 || pluscnt == 1) && dotcnt == 1)
    {
        int dot2 = dot;
        symbolcnt2--;
        symbolcnt--;
        for (int i = 0; i < dot2; i++) // Перевод из char в int отрицательные
        {
            result += (string[i] - '0') * DegreeCounting(10, dot - 1);
            dot--;
        }
        if (mincnt == 1)
            return -1 * result;
        else
            return result;
    }
 
    if ((mincnt == 1 || pluscnt == 1) && dotcnt == 0)
    {
        symbolcnt2--;
        symbolcnt--;
        for (int i = 0; i < symbolcnt2; i++) // Перевод из char в int отрицательные
        {
            result += (string[i] - '0') * DegreeCounting(10, symbolcnt - 1);
            symbolcnt--;
        }
        if (mincnt == 1)
            return -1 * result;
        else
            return result;
    }
    if (mincnt == 0 && dotcnt == 0 && pluscnt == 0)
    {
        for (int i = 0; i < symbolcnt2; i++) // Перевод из char в int отрицательные
        {
            result += (string[i] - '0') * DegreeCounting(10, symbolcnt - 1);
            symbolcnt--;
        }
        return result;
    }
    if (mincnt == 0 && dotcnt == 1 && pluscnt == 0)
    {
        int dot2 = dot;
        for (int i = 0; i < dot2; i++) // Перевод из char в int отрицательные
        {
            result += (string[i] - '0') * DegreeCounting(10, dot - 1);
            dot--;
        }
        return result;
    }
}
 
int DegreeCounting(int number, int degree)
{
    if (0 == number)
        return 0;
    if (degree == 0)
        return 1;
    if (degree % 2 == 1)
        return number * DegreeCounting(number, degree - 1);
    else
        return DegreeCounting(number * number, degree / 2);
}
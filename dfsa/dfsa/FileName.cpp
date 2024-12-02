// gcc -o prob prob.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>

void sumung(void) {
    printf("            ;#*      .*;$#*             \n");
    printf("            $~~#.    $~:~~~#            \n");
    printf("           $~~~~$~   #~#;#~#            \n");
    printf("          -;~~~:~#   $~#.$~!            \n");
    printf("          ;:=!~$#:   $~~;~;.            \n");
    printf("           $~*~#.    .#~~:=.            \n");
    printf("            ;#~;!=.  !=~*-.             \n");
    printf("           #~~~~~!, *~~~!#;             \n");
    printf("           =**~~#:  ;*:~~~#             \n");
    printf("             ;~~$    ,!~##,             \n");
    printf("             -!$=;:~:;!~#:              \n");
    printf("            :#       .!!~ #$            \n");
    printf("          .#-         -~   .#.          \n");
    printf("         ,=                 -#####=     \n");
    printf("    ,###$*                        #     \n");
    printf("    #   *                         #     \n");
    printf("    $  $                    ,    =      \n");
    printf("    .=~-                    !=:*#~      \n");
    printf("     .#                          #      \n");
    printf("      !                          ;      \n");
    printf("     .-                           #     \n");
    printf("     #                            #     \n");
    printf("     #                            *     \n");
    printf("     #                             ~    \n");
    printf("    .;       ,     !               ;    \n");
    printf("    ;       .#     #:              ;    \n");
    printf("    =           #                  :    \n");
    printf("    #;~       .#:$                -.    \n");
    printf("    = ,#                          #     \n");
    printf("   #   ~= : :,.- : :..:           #     \n");
    printf("   #   ##*,-==#*,-,*#$!          ;      \n");
    printf("    !:!#;$;;=;#;=;;$;#;!*        *      \n");
    printf("    ;$ .      .    .   ##       #       \n");
    printf("   ,=                 = #      =        \n");
    printf("   $                 $. #    ,#         \n");
    printf("   -~#~~~~~~~~~~~~~~~.  #~~#*!!         \n");
    printf("     $                  ##,   :,        \n");
    printf("     $                  =#,   .~        \n");
    printf("     $                 ~.=,.   = =      \n");
    printf("     $                 * .~,  $#! $     \n");
}

void init() {
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

int main() {
    int numbers[7];
    int used[46] = { 0 };
    int size = 7;
    int max = 45;
    int i, temp;


    init();
    sumung();

    printf("--- ���� ���� 7�� (1 ~ 45) ���߰� ���������� flag�� ������! ---\n\n");

    srand(time(NULL));
    for (i = 0; i < size; i++) {
        do {
            temp = rand() % max + 1;
        } while (used[temp] == 1);

        numbers[i] = temp;
        used[temp] = 1;
    }

    for(i = 0; i < 7; i++){
        printf("%d��° ��ȣ�� ���纸����! : ", i + 1);
        scanf_s("%d", &temp);

        if(numbers[i] != temp){
            printf("\n\nƲ�Ⱦ��! �ٽ� �õ��غ�����~ \n\n");
            return 0;
        }
    }

    printf("\n �����ؿ�! ��� ���ڸ� ���߼̾��!\n\n");
    system("cat flag");

    printf("\n");

    return 0;
}

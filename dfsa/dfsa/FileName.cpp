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

    printf("--- 랜덤 숫자 7개 (1 ~ 45) 맞추고 수뭉이한테 flag를 얻어가세요! ---\n\n");

    srand(time(NULL));
    for (i = 0; i < size; i++) {
        do {
            temp = rand() % max + 1;
        } while (used[temp] == 1);

        numbers[i] = temp;
        used[temp] = 1;
    }

    for(i = 0; i < 7; i++){
        printf("%d번째 번호를 맞춰보세요! : ", i + 1);
        scanf_s("%d", &temp);

        if(numbers[i] != temp){
            printf("\n\n틀렸어요! 다시 시도해보세요~ \n\n");
            return 0;
        }
    }

    printf("\n 축하해요! 모든 숫자를 맞추셨어요!\n\n");
    system("cat flag");

    printf("\n");

    return 0;
}

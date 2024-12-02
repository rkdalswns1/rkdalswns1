#include <windows.h>
#include <stdio.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

int encrypt_file(const char* filename, const unsigned char* key,int strength);
int decrypt_file(const char* filename, const unsigned char* key,int strength);
void conversion(const char* password, unsigned char* key, int strength);

void main()
{
    char filename[256];
    char password[256];
    unsigned char key[256];
    int choice;
    int strength;
    
    strcpy(filename, "C:/Users/kmj/Desktop/qlalf.txt");


    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);

    system("cls");


    while (1)
    {
        printf("===============================================================\n");
        printf("\t0.파일 암호화 1.파일 복호화 9.프로그램 종료\n");
        printf("===============================================================\n");
        scanf_s("%d", &choice);

        if (choice != 1 && choice != 0 &&choice != 9)
        {
            system("cls");
            printf("다시 입력해주세요.\n\n");
            continue;
        }
        
        if (choice == 0) {
            system("cls");
            printf("암호화 수준을 선택하세요 (128, 192, 256)");
            scanf("%d", &strength);

            if (strength != 128 && strength != 192 && strength != 256) {
                printf("잘못된 선택입니다\n\n");
                continue;
            }

            printf("파일의 비밀번호를 설정해주세요\n");
            scanf("%s", password);

            conversion(password, key, strength);//파일 암호화 함수
            
            int checkpoint = encrypt_file(filename, key, strength);

            if (checkpoint == 0) {
                printf("파일 암호화 성공\n\n");
            }
            else {
                printf("암호화 실패\n\n");
            }
        }
        else if (choice == 1)
        {
            system("cls");
            int checkpoint = decrypt_file(filename, key,strength);
            if (checkpoint == 0)
            {
                printf("파일 복호화 성공\n");
            }
            else {
                printf("복호화 실패\n");
            }
        }
        else if (choice == 9) {
            return 0;
        }
    }
}


int encrypt_file(const char* filename, const unsigned char* key,int strength) {
    FILE* file = fopen(filename, "rb+");   // 암호화할 파일 열기

    if (!file)
    {
        perror("파일 열기 실패\n");
        return -1;
    }

    FILE* temp_file = fopen("temp.txt","wb");
    if (!temp_file) {
        perror("임시파일 생성 실패\n");
        fclose(file);
        return -1;
    }

    AES_KEY aes_ekey;
    if (AES_set_encrypt_key(key, 256, &aes_ekey) < 0) {
        perror("aes키 설정 실패\n");
        fclose(file);
        fclose(temp_file);
        return -1;
    }

    unsigned char save[16];
    unsigned char encrypt_save[16];
    size_t padding;

    while ((padding = fread(save, 1, 16, file)) > 0) { //마지막 블록이 16바이트보다 작으면 padding으로 16바이트 크기 조절
        if (padding < 16) {
            for (size_t i = padding; i < 16; i++) {
                save[i] = 16 - padding; //빈공간의 수로 빈공간 채우기 
            }
        }
        AES_encrypt(save, encrypt_save, &aes_ekey);
        
        fwrite(encrypt_save, 1, 16, temp_file);

        printf("16바이트 단위 암호화 완료\n\n");
    }
    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.txt", filename);

    printf("암호화 완료..!\n\n");
    return 0;
}

int decrypt_file(const char* filename, const unsigned char* key, int strength) {
    FILE* file = fopen(filename, "rb+");
    char password[256];

    if (!file) {
        perror("파일 열기 실패\n");
        return -1;
    }
    
    FILE* temp_file = fopen("temp.txt", "wb");
    if (!temp_file) {
        perror("임시파일 생성 실패\n");
        fclose(file);
        return -1;
    }
    AES_KEY aes_dkey;
    printf("복호화 키를 입력하세요\n");
    scanf("%s", password);
    conversion(password, key,strength);

    if (AES_set_decrypt_key(key, 256, &aes_dkey) < 0) {
        perror("aes키 설정 실패\n");
        fclose(file);
        fclose(temp_file);
        return -1;
    }

    unsigned char save[16];
    unsigned char decrypt_save[16];
    size_t size;

    while ((size = fread(save, 1, 16, file)) > 0) { //마지막 블록이 16바이트보다 작으면 padding으로 16바이트 크기 조절
        AES_decrypt(save, decrypt_save, &aes_dkey);

        fwrite(decrypt_save, 1, 16, temp_file);

        printf("16바이트 단위 복호화 완료\n\n");
    }
    
    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.txt", filename);

    printf("복호화 완료\n\n");
    return 0;
}

void conversion(const char* password, unsigned char* key, int strength) {
    SHA256_CTX sha256; //openssl 라이브러리에 있는 구조체 해시값을 저장하는 역할
    SHA256_Init(&sha256); //위에 있는 구조체를 초기화하고 해시계산에 필요한 설정 진행 
    SHA256_Update(&sha256, password, strlen(password)); //사용자에게 받은 비밀번호를 구조체에 추가

    unsigned char hash[32]; //해시값을 저장할 배열 (256비트)
    SHA256_Final(hash, &sha256); //해시연산

    memcpy(key, hash, strength / 8); //원본 메모리블록의 시작 주소(hash), strength/8 만큼의 데이터를 메모리 주소(key)에 복사 //key의 첫 주소값 반환
}
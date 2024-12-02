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
        printf("\t0.���� ��ȣȭ 1.���� ��ȣȭ 9.���α׷� ����\n");
        printf("===============================================================\n");
        scanf_s("%d", &choice);

        if (choice != 1 && choice != 0 &&choice != 9)
        {
            system("cls");
            printf("�ٽ� �Է����ּ���.\n\n");
            continue;
        }
        
        if (choice == 0) {
            system("cls");
            printf("��ȣȭ ������ �����ϼ��� (128, 192, 256)");
            scanf("%d", &strength);

            if (strength != 128 && strength != 192 && strength != 256) {
                printf("�߸��� �����Դϴ�\n\n");
                continue;
            }

            printf("������ ��й�ȣ�� �������ּ���\n");
            scanf("%s", password);

            conversion(password, key, strength);//���� ��ȣȭ �Լ�
            
            int checkpoint = encrypt_file(filename, key, strength);

            if (checkpoint == 0) {
                printf("���� ��ȣȭ ����\n\n");
            }
            else {
                printf("��ȣȭ ����\n\n");
            }
        }
        else if (choice == 1)
        {
            system("cls");
            int checkpoint = decrypt_file(filename, key,strength);
            if (checkpoint == 0)
            {
                printf("���� ��ȣȭ ����\n");
            }
            else {
                printf("��ȣȭ ����\n");
            }
        }
        else if (choice == 9) {
            return 0;
        }
    }
}


int encrypt_file(const char* filename, const unsigned char* key,int strength) {
    FILE* file = fopen(filename, "rb+");   // ��ȣȭ�� ���� ����

    if (!file)
    {
        perror("���� ���� ����\n");
        return -1;
    }

    FILE* temp_file = fopen("temp.txt","wb");
    if (!temp_file) {
        perror("�ӽ����� ���� ����\n");
        fclose(file);
        return -1;
    }

    AES_KEY aes_ekey;
    if (AES_set_encrypt_key(key, 256, &aes_ekey) < 0) {
        perror("aesŰ ���� ����\n");
        fclose(file);
        fclose(temp_file);
        return -1;
    }

    unsigned char save[16];
    unsigned char encrypt_save[16];
    size_t padding;

    while ((padding = fread(save, 1, 16, file)) > 0) { //������ ����� 16����Ʈ���� ������ padding���� 16����Ʈ ũ�� ����
        if (padding < 16) {
            for (size_t i = padding; i < 16; i++) {
                save[i] = 16 - padding; //������� ���� ����� ä��� 
            }
        }
        AES_encrypt(save, encrypt_save, &aes_ekey);
        
        fwrite(encrypt_save, 1, 16, temp_file);

        printf("16����Ʈ ���� ��ȣȭ �Ϸ�\n\n");
    }
    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.txt", filename);

    printf("��ȣȭ �Ϸ�..!\n\n");
    return 0;
}

int decrypt_file(const char* filename, const unsigned char* key, int strength) {
    FILE* file = fopen(filename, "rb+");
    char password[256];

    if (!file) {
        perror("���� ���� ����\n");
        return -1;
    }
    
    FILE* temp_file = fopen("temp.txt", "wb");
    if (!temp_file) {
        perror("�ӽ����� ���� ����\n");
        fclose(file);
        return -1;
    }
    AES_KEY aes_dkey;
    printf("��ȣȭ Ű�� �Է��ϼ���\n");
    scanf("%s", password);
    conversion(password, key,strength);

    if (AES_set_decrypt_key(key, 256, &aes_dkey) < 0) {
        perror("aesŰ ���� ����\n");
        fclose(file);
        fclose(temp_file);
        return -1;
    }

    unsigned char save[16];
    unsigned char decrypt_save[16];
    size_t size;

    while ((size = fread(save, 1, 16, file)) > 0) { //������ ����� 16����Ʈ���� ������ padding���� 16����Ʈ ũ�� ����
        AES_decrypt(save, decrypt_save, &aes_dkey);

        fwrite(decrypt_save, 1, 16, temp_file);

        printf("16����Ʈ ���� ��ȣȭ �Ϸ�\n\n");
    }
    
    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.txt", filename);

    printf("��ȣȭ �Ϸ�\n\n");
    return 0;
}

void conversion(const char* password, unsigned char* key, int strength) {
    SHA256_CTX sha256; //openssl ���̺귯���� �ִ� ����ü �ؽð��� �����ϴ� ����
    SHA256_Init(&sha256); //���� �ִ� ����ü�� �ʱ�ȭ�ϰ� �ؽð�꿡 �ʿ��� ���� ���� 
    SHA256_Update(&sha256, password, strlen(password)); //����ڿ��� ���� ��й�ȣ�� ����ü�� �߰�

    unsigned char hash[32]; //�ؽð��� ������ �迭 (256��Ʈ)
    SHA256_Final(hash, &sha256); //�ؽÿ���

    memcpy(key, hash, strength / 8); //���� �޸𸮺���� ���� �ּ�(hash), strength/8 ��ŭ�� �����͸� �޸� �ּ�(key)�� ���� //key�� ù �ּҰ� ��ȯ
}
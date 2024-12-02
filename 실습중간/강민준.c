#include <stdio.h>

int main(void)
{
	int source_no[20] = { 1010,2011,1015,3012,3001,2023,2016,1018,3012,3022,3010,4010,1019,2212,3001,3004,4010 };
	int source_data[20] = { 90,80,60,100,65,85,60,95,60,90,90,60,80,90,80,75,88 };
	int choice_main;
	int choice_no;
	int ret;
	int tmep = 0;

	int grade1_no[20] = { 0 };
	int grade2_no[20] = { 0 };
	int grade3_no[20] = { 0 };
	int grade4_no[20] = { 0 };

	int grade1_data[20] = { 0 };
	int grade2_data[20] = { 0 };
	int grade3_data[20] = { 0 };
	int grade4_data[20] = { 0 };

	int pointer1, pointer2, pointer3, pointer4;

	while(1)
	{
		system("cls");
		int first = 0;
		int first_no;
		pointer1 = pointer2 = pointer3 = pointer4 = 0;
		int ret = 1;

		printf("�����б� 2024�� ���� �û��� �����ȸ ����...\n");
		printf("========================================================================================================================\n");
		printf("1.�й��˻�\t2.�Է¼����\t3.�г⺰ �з�����\t4.�ְ�����\t0.ȭ�������\n");
		printf("========================================================================================================================\n");
		printf("���ϴ� ��ȣ�� �����ϼ���>>");
		scanf_s("%d", &choice_main);

		if (choice_main == 1)
		{
			printf("�˻��� �й��� �Է��ϼ���:");
			scanf_s("%d", &choice_no);
			
			for (int i = 0; i < 17; i++)
			{
				if (source_no[i] == choice_no)
				{
					printf("�й�=%d, ����=%d\n", source_no[i],source_data[i]);
					printf("����Ϸ��� 0�� ��������:");
					scanf_s("%d", &ret);
				}
				else if(i==16)
				{
					printf("ã�»���� �����ϴ�.\n");
					printf("����Ϸ��� 0�� ��������:");
					scanf_s("%d", &ret);
				}
				if (ret == 0)
				{
					break;
				}
			}
		}
		else if (choice_main == 2)
		{
			for (int j = 0; j < 20; j++)
			{
				printf("%d\t%d\t%d\n", j + 1, source_no[j], source_data[j]);
			}
			printf("����Ϸ��� 0�� ��������:");
			scanf_s("%d", &ret);
			if (ret == 0)
			{
				continue;
			}
		}
		else if (choice_main == 3)
		{
			for (int i = 0; i < 20; i++)
			{
				if (source_no[i] / 1000 == 1)
				{
					grade1_no[pointer1] = source_no[i];
					grade1_data[pointer1] = source_data[i];
					pointer1++;
				}
				else if (source_no[i] / 1000 == 2)
				{
					grade2_no[pointer2] = source_no[i];
					grade2_data[pointer2] = source_data[i];
					pointer2++;
				}
				else if (source_no[i] / 1000 == 3)
				{
					grade3_no[pointer3] = source_no[i];
					grade3_data[pointer3] = source_data[i];
					pointer3++;
				}
				else if (source_no[i] / 1000 == 4)
				{
					grade4_no[pointer4] = source_no[i];
					grade4_data[pointer4] = source_data[i];
					pointer4++;
				}
			}
			printf("  1�г�\t\t  2�г�\t\t  3�г�\t\t  4�г�\n");
			printf("==================================================================================\n");
			for (int p = 0; p < 20; p++)
			{
				printf("%4d %4d\t", grade1_no[p], grade1_data[p]);
				printf("%4d %4d\t", grade2_no[p], grade2_data[p]);
				printf("%4d %4d\t", grade3_no[p], grade3_data[p]);
				printf("%4d %4d\n", grade4_no[p], grade4_data[p]);
			}
			printf("����Ϸ��� 0�� ��������:");
			scanf_s("%d", &ret);
			if (ret == 0)
			{
				continue;
			}
		}
		else if (choice_main == 4)
		{
			for (int j = 0; j < 20; j++)
			{
				if (source_data[j] > first)
				{
					first = source_data[j];
					first_no = source_no[j];
				}
			}
			printf("===============================================================\n");
			printf("1���� �й�:%d\n", first_no);
			printf("===============================================================\n");

			printf("����Ϸ��� 0�� ��������:");
			scanf_s("%d", &ret);
			if (ret == 0)
			{
				continue;
			}
		}
		else if (choice_main == 0)
		{
			system("cls");
		}
	}
	return 0;
}
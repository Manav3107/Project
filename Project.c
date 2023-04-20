#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

int student[3][4] = {0};

void *teacher();
void *student1();
void *student2();
void *student3();

pthread_mutex_t lck;
int choice1, choice2;
int resource1, resource2;

int main()
{
    pthread_mutex_init(&lck,NULL);

    student[1][1] = 1;
    student[2][2] = 2;
    student[3][3] = 1;

    pthread_t t_thread;
    pthread_t s_thread;

    printf("Resources Menu:\n");
    printf("\tPress '1' for pen\n");
    printf("\tPress '2' for paper\n");
    printf("\tPress '3' for question_paper\n");

    while (1) {
        if (student[1][4] == 1 && student[2][4] == 1 && student[3][4] == 1) {
            break;
        }

        pthread_create(&t_thread, NULL, teacher, NULL);
        pthread_join(t_thread, NULL);

        if ((choice1 == 1 && choice2 == 2 || choice2 == 1 && choice1 == 2) && student[3][4] == 0) {
            pthread_create(&s_thread, NULL, student3, NULL);
            pthread_join(s_thread, NULL);
        } else if ((choice1 == 1 && choice2 == 3 || choice2 == 1 && choice1 == 3) && student[2][4] == 0) {
            pthread_create(&s_thread, NULL, student2, NULL);
            pthread_join(s_thread, NULL);
        } else if ((choice1 == 2 && choice2 == 3 || choice2 == 2 && choice1 == 3) && student[1][4] == 0) {
            pthread_create(&s_thread, NULL, student1, NULL);
            pthread_join(s_thread, NULL);
        } else {
            printf("\n\tTry again with different choices.\n");
        }
    }

    printf("\tDone\n");
}

void *teacher()
{
    pthread_mutex_lock(&lck);
    printf("\nEnter first choice of resource:\t");
    scanf("%d", &choice1);
    printf("\nEnter second choice of resource:\t");
    scanf("%d", &choice2);
    pthread_mutex_unlock(&lck);
}

void *student1()
{
    pthread_mutex_lock(&lck);
    printf("\nStudent 1 chose 'paper' and 'question_paper'.\n");
    student[1][4] = 1;
    printf("\n\tStudent 1 has completed the assignment.\n");
    pthread_mutex_unlock(&lck);
}

void *student2()
{
    pthread_mutex_lock(&lck);
    printf("\nStudent 2 chose 'pen' and 'question_paper'.\n");
    student[2][4] = 1;
    printf("\n\tStudent 2 has completed the assignment.\n");
    pthread_mutex_unlock(&lck);
}

void *student3()
{
    pthread_mutex_lock(&lck);
    printf("\nStudent 3 chose 'pen' and 'paper'.\n");
    student[3][4] = 1;
    printf("\n\tStudent 3 has completed the assignment.\n");
    pthread_mutex_unlock(&lck);
}

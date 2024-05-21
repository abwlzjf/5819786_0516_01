#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = h;
    h = p;
    return h;
}

ListNode* insert_last(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = NULL; // 링크를 NULL로 초기화

    if (h == NULL) {
        h = p;
    }
    else {
        ListNode* q = h;
        while (q->link != NULL) {
            q = q->link;
        }
        q->link = p;
    }
    return h;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (pre == (ListNode*)NULL) {
        fprintf(stderr, "Insert parameter error: pre is NULL\n");
        return head;
    }
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* delete_first(ListNode* head) {
    if (head == NULL) return NULL;
    ListNode* remove = head;
    head = remove->link;
    free(remove);
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
    if (pre == NULL || pre->link == NULL) {
        fprintf(stderr, "Delete parameter error\n");
        return head;
    }
    ListNode* remove = pre->link;
    pre->link = remove->link;
    free(remove);
    return head;
}

void print_list(ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}

int main() {
    ListNode* head = NULL;
    int choice, position, value, link_count;

    while (1) {
        printf("메뉴: \n");
        printf("1. 숫자를 위치에 삽입\n");
        printf("2. 위치에서 숫자 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료\n");
        printf("선택하세요: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("삽입할 숫자를 입력하세요: ");
            scanf_s("%d", &value);
            printf("삽입할 위치를 입력하세요: ");
            scanf_s("%d", &position);

            link_count = 0;
            if (position == 0) {
                head = insert_first(head, value);
                link_count++;
            }
            else {
                ListNode* pre = head;
                for (int i = 0; i < position - 2; i++) {
                    if (pre == NULL) break;
                    pre = pre->link;
                    link_count++;
                }
                link_count++;
                if (pre != NULL) {
                    head = insert(head, pre, value);
                    link_count++;
                }
                else {
                    head = insert_last(head, value);
                    link_count++;
                }
            }
            printf("삽입시 링크를 따라 이동한 횟수: %d\n", link_count);
            break;

        case 2:
            printf("삭제할 위치를 입력하세요: ");
            scanf_s("%d", &position);
            link_count = 0;
            if (position == 0) {
                head = delete_first(head);
                link_count++;
            }
            else {
                ListNode* pre = head;
                for (int i = 0; i < position - 1; i++) {
                    if (pre == NULL) break;
                    pre = pre->link;
                    link_count++;
                }
                if (pre != NULL && pre->link != NULL) {
                    head = delete(head, pre);
                    link_count++;
                }
                else {
                    printf("유효하지 않은 위치입니다!\n");
                }
            }
            printf("삭제시 링크를 따라 이동한 횟수: %d\n", link_count);
            break;

        case 3:
            print_list(head);
            break;

        case 0:
            exit(0);

        default:
            printf("유효하지 않은 선택입니다!\n");
        }
    }

    return 0;
}
#include "dance_studio.h"
void room_update_status() {
    printf("请输入教室ID：");
    char room_id[STR_LEN];
    fgets(room_id, STR_LEN, stdin);
    room_id[strcspn(room_id, "\n")] = '\0';

    RoomNode *room = find_room_by_id(room_id);  // 需实现教室查找函数
    if (room == NULL) {
        printf("教室不存在！\n");
        return;
    }

    printf("请设置教室状态（0-可用，1-不可用）：");
    int status;
    scanf("%d", &status);
    getchar();

    room->data.isAvailable = status;
    storage_save_rooms();
    printf("教室状态更新成功！\n");
}
// 于根据ID查找教室
RoomNode* find_room_by_id(const char* room_id) {
    // 从教室链表头节点开始遍历
    RoomNode* current = roomHead;
    
    // 遍历整个链表查找匹配的教室ID
    while (current != NULL) {
        // 比较当前节点的教室ID与目标ID
        if (strcmp(current->data.room_id, room_id) == 0) {
            return current;  // 找到匹配的教室，返回该节点
        }
        current = current->next;  // 继续查找下一个节点
    }
    
    return NULL;  // 遍历完链表仍未找到，返回NULL
}
    
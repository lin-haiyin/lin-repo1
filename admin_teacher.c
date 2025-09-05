#include "dance_studio.h"
void teacher_add() {
    Teacher new_teacher;
    memset(&new_teacher, 0, sizeof(Teacher));
    new_teacher.course_count = 0;  // 初始授课课程数为0

    // 生成教师ID（格式：T+日期+序号）
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[10];
    sprintf(date, "%04d%02d%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
    sprintf(new_teacher.teacher_id, "T%s%03d", date, teacherCount+1);
    printf("自动生成教师ID：%s\n", new_teacher.teacher_id);

    printf("请输入教师姓名：");
    fgets(new_teacher.teacher_name, STR_LEN, stdin);
    new_teacher.teacher_name[strcspn(new_teacher.teacher_name, "\n")] = '\0';

    // 插入教师链表（参考会员添加逻辑）
    TeacherNode *new_node = (TeacherNode*)malloc(sizeof(TeacherNode));
    new_node->data = new_teacher;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (teacherHead == NULL) {
        teacherHead = new_node;
    } else {
        TeacherNode *current = teacherHead;
        while (current->next != NULL) current = current->next;
        current->next = new_node;
        new_node->prev = current;
    }
    teacherCount++;
    storage_save_teachers();  // 保存到文件
    printf("教师添加成功！\n");
}
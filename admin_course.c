#include "dance_studio.h"

void course_add() {
    Course new_course;
    memset(&new_course, 0, sizeof(Course));

    // 生成课程ID（格式：C+日期+序号，参考会员ID生成逻辑）
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[10];
    sprintf(date, "%04d%02d%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
    sprintf(new_course.course_id, "C%s%03d", date, courseCount+1);
    printf("自动生成课程ID：%s\n", new_course.course_id);

    // 输入课程信息
    printf("请输入课程名称：");
    fgets(new_course.course_name, STR_LEN, stdin);
    new_course.course_name[strcspn(new_course.course_name, "\n")] = '\0';

    printf("请输入授课教师ID：");
    fgets(new_course.teacher_id, STR_LEN, stdin);
    new_course.teacher_id[strcspn(new_course.teacher_id, "\n")] = '\0';

    printf("请输入上课教室ID：");
    fgets(new_course.course_room, STR_LEN, stdin);
    new_course.course_room[strcspn(new_course.course_room, "\n")] = '\0';

    // 其他字段输入（价格、时长、最大人数等）
    printf("请输入课程价格：");
    scanf("%d", &new_course.course_price);
    getchar();  // 吸收换行符

    new_course.status = COURSE_ONGOING;  // 默认为进行中
    new_course.course_current_number = 0;  // 初始报名人数为0

    // 插入课程链表（参考会员添加逻辑）
    CourseNode *new_node = (CourseNode*)malloc(sizeof(CourseNode));
    new_node->data = new_course;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (courseHead == NULL) {
        courseHead = new_node;
    } else {
        CourseNode *current = courseHead;
        while (current->next != NULL) current = current->next;
        current->next = new_node;
        new_node->prev = current;
    }
    courseCount++;
    storage_save_courses();  // 保存到文件
    printf("课程添加成功！\n");
}
// 在admin_course.c中添加（用于根据ID查找课程）
CourseNode* find_course_by_id(const char* course_id) {
    // 从课程链表头节点开始遍历
    CourseNode* current = courseHead;
    
    // 遍历整个链表查找匹配的课程ID
    while (current != NULL) {
        // 比较当前节点的课程ID与目标ID
        if (strcmp(current->data.course_id, course_id) == 0) {
            return current;  // 找到匹配的课程，返回该节点
        }
        current = current->next;  // 继续查找下一个节点
    }
    
    return NULL;  // 遍历完链表仍未找到，返回NULL
}
    

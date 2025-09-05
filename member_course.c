
#include "dance_studio.h"
int course_enroll(MemberNode *member, char *course_id) {
    CourseNode *course = find_course_by_id(course_id);  // 需实现课程查找函数
    if (course == NULL) return -1;

    // 校验逻辑：次卡只能报名单次课程，月卡/年卡可报多次
    if (member->data.card_type == CARD_TYPE_TIMES) {
        if (member->data.card_times <= 0) {
            printf("次卡次数不足！\n");
            return -1;
        }
        member->data.card_times--;  // 扣减次数
    } else if (member->data.card_type == CARD_TYPE_MONEY) {
        if (member->data.balance < course->data.course_price) {
            printf("储值卡余额不足！\n");
            return -1;
        }
        member->data.balance -= course->data.course_price;  // 扣减余额
    }

    // 记录报名信息（添加会员ID到课程的报名列表）
    strcpy(course->data.course_members[course->data.course_current_number], member->data.member_id);
    course->data.course_current_number++;
    storage_save_courses();
    storage_save_members();
    return 0;
}
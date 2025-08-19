#include "dance_studio.h"

// 定义全局变量并初始化，仅此处定义
MemberNode *memberHead = NULL;
int memberCount = 0;

AdminNode *adminHead = NULL;
int adminCount = 0;

CourseNode *courseHead = NULL;
int courseCount = 0;

RoomNode *roomHead = NULL;
int roomCount = 0;

TeacherNode *teacherHead = NULL;
int teacherCount = 0;

int is_login_success = 0;  // 登录状态标志
FILE *original_stdin = NULL;  // 输入流保存变量
// 系统初始化：加载所有数据
void init_system() {
	storage_load_members();
	storage_load_admins();
	storage_load_courses();
	storage_load_rooms();
	storage_load_teachers();
	printf("系统初始化完成！\n");
}

// 系统退出：保存所有数据
void exit_system() {
	storage_save_members();
	storage_save_admins();
	storage_save_courses();
	storage_save_rooms();
	storage_save_teachers();
	printf("数据已保存！\n");
}

// 会员数据存储
void storage_save_members() {
    FILE *fp = fopen("members.dat", "wb");
    if (fp == NULL) {
        printf("会员数据保存失败：无法打开文件！\n");
        return;
    }

    MemberNode *current = memberHead;
    while (current != NULL) {
        fwrite(&current->data, sizeof(Member), 1, fp);
        current = current->next;
    }

    fclose(fp);
}

void storage_load_members() {
    FILE *fp = fopen("members.dat", "rb");
    if (fp == NULL) {
        printf("未找到会员数据文件，从空开始\n");
        return;
    }

    // 清空现有链表
    MemberNode *temp;
    while (memberHead != NULL) {
        temp = memberHead;
        memberHead = memberHead->next;
        free(temp);
    }
    memberCount = 0;

    // 读取数据
    Member temp_member;
    while (fread(&temp_member, sizeof(Member), 1, fp) == 1) {
        MemberNode *new_node = (MemberNode *)malloc(sizeof(MemberNode));
        new_node->data = temp_member;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (memberHead == NULL) {
            memberHead = new_node;
        } else {
            MemberNode *current = memberHead;
            while (current->next != NULL) current = current->next;
            current->next = new_node;
            new_node->prev = current;
        }
        memberCount++;
    }

    fclose(fp);
    printf("加载会员数据：%d名会员\n", memberCount);
}

// 管理员数据存储
void storage_save_admins() {
    FILE *fp = fopen("admins.dat", "wb");
    if (fp == NULL) {
        printf("管理员数据保存失败！\n");
        return;
    }

    AdminNode *current = adminHead;
    while (current != NULL) {
        fwrite(&current->data, sizeof(Admin), 1, fp);
        current = current->next;
    }

    fclose(fp);
}

void storage_load_admins() {
    FILE *fp = fopen("admins.dat", "rb");
    if (fp == NULL) {
        printf("未找到管理员数据文件，从空开始\n");
        // 添加默认管理员
        AdminNode *default_admin = (AdminNode*)malloc(sizeof(AdminNode));
        strcpy(default_admin->data.admin_id, "admin001");
        strcpy(default_admin->data.admin_name, "管理员");
        strcpy(default_admin->data.password, "123456");
        default_admin->prev = default_admin->next = NULL;
        adminHead = default_admin;
        adminCount = 1;

		// 新增调试日志：打印默认管理员信息
        printf("[调试] 默认管理员创建成功：ID=%s, 姓名=%s, 密码=%s\n",
               adminHead->data.admin_id,
               adminHead->data.admin_name,
               adminHead->data.password);
        return;
    }

    // 清空现有链表
    AdminNode *temp;
    while (adminHead != NULL) {
        temp = adminHead;
        adminHead = adminHead->next;
        free(temp);
    }
    adminCount = 0;

    // 读取数据
    Admin temp_admin;
    while (fread(&temp_admin, sizeof(Admin), 1, fp) == 1) {
        AdminNode *new_node = (AdminNode *)malloc(sizeof(AdminNode));
        new_node->data = temp_admin;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (adminHead == NULL) {
            adminHead = new_node;
        } else {
            AdminNode *current = adminHead;
            while (current->next != NULL) current = current->next;
            current->next = new_node;
            new_node->prev = current;
        }
        adminCount++;
    }

    fclose(fp);
    printf("加载管理员数据：%d名管理员\n", adminCount);
}

// 课程数据存储（简化版，与会员逻辑类似）
void storage_save_courses() {
    FILE *fp = fopen("courses.dat", "wb");
    if (fp == NULL) {
        printf("课程数据保存失败！\n");
        return;
    }

    CourseNode *current = courseHead;
    while (current != NULL) {
        fwrite(&current->data, sizeof(Course), 1, fp);
        current = current->next;
    }

    fclose(fp);
}

void storage_load_courses() {
    FILE *fp = fopen("courses.dat", "rb");
    if (fp == NULL) {
        printf("未找到课程数据文件，从空开始\n");
        return;
    }

    // 清空现有链表
    CourseNode *temp;
    while (courseHead != NULL) {
        temp = courseHead;
        courseHead = courseHead->next;
        free(temp);
    }
    courseCount = 0;

    // 读取数据
    Course temp_course;
    while (fread(&temp_course, sizeof(Course), 1, fp) == 1) {
        CourseNode *new_node = (CourseNode *)malloc(sizeof(CourseNode));
        new_node->data = temp_course;
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
    }

    fclose(fp);
    printf("加载课程数据：%d门课程\n", courseCount);
}

// 教室和教师数据存储（简化实现）
void storage_save_rooms() {
    FILE *fp = fopen("rooms.dat", "wb");
    if (fp == NULL) {
        printf("教室数据保存失败！\n");
        return;
    }

    RoomNode *current = roomHead;
    while (current != NULL) {
        fwrite(&current->data, sizeof(Room), 1, fp);
        current = current->next;
    }
    fclose(fp);
}

void storage_load_rooms() {
    FILE *fp = fopen("rooms.dat", "rb");
    if (fp == NULL) {
        printf("未找到教室数据文件，从空开始\n");
        return;
    }

    // 清空现有链表
    RoomNode *temp;
    while (roomHead != NULL) {
        temp = roomHead;
        roomHead = roomHead->next;
        free(temp);
    }
    roomCount = 0;

    // 读取数据
    Room temp_room;
    while (fread(&temp_room, sizeof(Room), 1, fp) == 1) {
        RoomNode *new_node = (RoomNode *)malloc(sizeof(RoomNode));
        new_node->data = temp_room;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (roomHead == NULL) {
            roomHead = new_node;
        } else {
            RoomNode *current = roomHead;
            while (current->next != NULL) current = current->next;
            current->next = new_node;
            new_node->prev = current;
        }
        roomCount++;
    }

    fclose(fp);
    printf("加载教室数据：%d间教室\n", roomCount);
}

void storage_save_teachers() {
    FILE *fp = fopen("teachers.dat", "wb");
    if (fp == NULL) {
        printf("教师数据保存失败！\n");
        return;
    }

    TeacherNode *current = teacherHead;
    while (current != NULL) {
        fwrite(&current->data, sizeof(Teacher), 1, fp);
        current = current->next;
    }
    fclose(fp);
}

void storage_load_teachers() {
    FILE *fp = fopen("teachers.dat", "rb");
    if (fp == NULL) {
        printf("未找到教师数据文件，从空开始\n");
        return;
    }

    // 清空现有链表
    TeacherNode *temp;
    while (teacherHead != NULL) {
        temp = teacherHead;
        teacherHead = teacherHead->next;
        free(temp);
    }
    teacherCount = 0;

    // 读取数据
    Teacher temp_teacher;
    while (fread(&temp_teacher, sizeof(Teacher), 1, fp) == 1) {
        TeacherNode *new_node = (TeacherNode *)malloc(sizeof(TeacherNode));
        new_node->data = temp_teacher;
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
    }

    fclose(fp);
    printf("加载教师数据：%d名教师\n", teacherCount);
}

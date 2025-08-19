#ifndef DANCE_STUDIO_H
#define DANCE_STUDIO_H

/* 必要头文件包含 */
#include <stdlib.h>   // 定义 size_t
#include <stddef.h>   // 补充 size_t 定义
#include <stdio.h>
#include <string.h>
#include <time.h>

/* 宏定义：配置常量 */
#define MAX_MEMBERS 1000         // 最大会员数
#define MAX_COURSE 20            // 最大课程数
#define MAX_ROOMS 10             // 最大教室数
#define MAX_TEACHER 10           // 最大教师数
#define MAX_ADMINS 3             // 最大管理员数
#define STR_LEN 50               // 字符串最大长度
#define MAX_COURSE_MAX_PEOPLE 50 // 每门课程最大报名人数

/* 枚举定义：状态和类型 */
// 会员卡类型
typedef enum {
    CARD_TYPE_TIMES,   // 次卡
    CARD_TYPE_MONTHS,  // 月卡
    CARD_TYPE_YEARS,   // 年卡
    CARD_TYPE_MONEY    // 储值卡
} CardType;

// 性别
typedef enum {
    FEMALE,
    MALE
} Sex;

// 会员状态
typedef enum {
    STATUS_ACTIVE,   // 正常
    STATUS_INACTIVE  // 注销
} MemberStatus;

// 教室状态
typedef enum {
    ROOM_AVAILABLE,   // 可用
    ROOM_INAVAILABLE  // 不可用
} RoomStatus;

// 课程类型
typedef enum {
    JAZZ,        // 爵士
    LOCKING,     // 锁舞
    HIP_HOP,     // 嘻哈舞
    POPPING,     // 机械舞
    K_POP,       // 韩舞
    BREAKING,    // 霹雳舞
    POLE,        // 钢管舞
    RUMBA,       // 伦巴舞
    BASIC        // 舞蹈基础
} CourseType;

// 教室类型
typedef enum {
    ROOM_JZ_01,  // 爵士教室
    ROOM_LK_01,  // locking教室
    ROOM_HH_01,  // hiphop教室
    ROOM_PP_01,  // poping教室
    ROOM_KP_01,  // kpop教室
    ROOM_BK_01,  // breaking教室
    ROOM_PL_01,  // 钢管舞教室
    ROOM_RB_01,  // 伦巴教室
    ROOM_BS_01,  // 基础教室1
    ROOM_BS_02   // 基础教室2
} RoomType;

/* 结构体定义：核心数据模型 */
// 会员结构体
typedef struct Member {
    char card_id[STR_LEN];       // 会员卡卡号（唯一，可变）
    char member_id[STR_LEN];     // 会员ID（唯一，不可变）
    char member_name[STR_LEN];   // 会员姓名
    char birthday[STR_LEN];      // 生日（yyyy-mm-dd）
    char phone[STR_LEN];         // 手机号
    char reg_time[STR_LEN];      // 注册时间（yyyy-mm-dd）
    Sex sex;                     // 性别
    CardType card_type;          // 会员卡类型
    char expire_time[STR_LEN];   // 有效期（yyyy-mm-dd）
    double balance;              // 储值余额（储值卡专用）
    MemberStatus isActive;       // 会员状态（正常/注销）
    int card_times;              // 剩余次数（次卡专用）
} Member;

// 管理员结构体
typedef struct Admin {
    char admin_id[STR_LEN];      // 管理员ID
    char admin_name[STR_LEN];    // 管理员姓名
    char password[STR_LEN];      // 管理员密码
} Admin;

// 课程结构体
typedef struct Course {
    char course_id[STR_LEN];     // 课程ID
    char course_name[STR_LEN];   // 课程名称
    char teacher[STR_LEN];       // 授课教师（关联教师ID）
    char time[STR_LEN];          // 单节课程时长
    char course_room[STR_LEN];   // 上课教室（关联教室ID）
    int course_price;            // 课程价格
    int course_lessons;          // 课程总节数
    int course_current_number;   // 当前报名人数
    char course_members[MAX_COURSE_MAX_PEOPLE][STR_LEN]; // 报名会员ID列表
    int course_max_people;       // 最大授课人数
    CourseType course_type;      // 课程类型
    char start_time[STR_LEN];    // 开课时间
    char end_time[STR_LEN];      // 结课时间
} Course;

// 教室结构体
typedef struct Room {
    char room_id[STR_LEN];       // 教室ID
    char room_name[STR_LEN];     // 教室名称
    RoomStatus isAvailable;      // 教室状态（可用/不可用）
    char current_course_id[STR_LEN]; // 当前关联课程ID（课程结束后清空）
} Room;

// 教师结构体
typedef struct Teacher {
    char teacher_id[STR_LEN];    // 教师ID
    char teacher_name[STR_LEN];  // 教师姓名
    char teacher_course[5][STR_LEN]; // 授课课程（最多5门）
} Teacher;

/* 链表节点定义：用于数据存储 */
// 会员链表节点
typedef struct MemberNode {
    Member data;                 // 会员数据
    struct MemberNode* prev;     // 前驱节点（双向链表）
    struct MemberNode* next;     // 后继节点
} MemberNode;

// 管理员链表节点
typedef struct AdminNode {
    Admin data;                  // 管理员数据
    struct AdminNode* prev;      // 前驱节点
    struct AdminNode* next;      // 后继节点
} AdminNode;

// 课程链表节点
typedef struct CourseNode {
    Course data;                 // 课程数据
    struct CourseNode* prev;     // 前驱节点
    struct CourseNode* next;     // 后继节点
} CourseNode;

// 教室链表节点
typedef struct RoomNode {
    Room data;                   // 教室数据
    struct RoomNode* prev;       // 前驱节点
    struct RoomNode* next;       // 后继节点
} RoomNode;

// 教师链表节点
typedef struct TeacherNode {
    Teacher data;                // 教师数据
    struct TeacherNode* prev;    // 前驱节点
    struct TeacherNode* next;    // 后继节点
} TeacherNode;

/* 全局变量声明：跨文件共享数据 */
// 会员相关
extern MemberNode* memberHead;   // 会员链表头指针
extern int memberCount;          // 会员总数

// 管理员相关
extern AdminNode* adminHead;     // 管理员链表头指针
extern int adminCount;           // 管理员总数

// 课程相关
extern CourseNode* courseHead;   // 课程链表头指针
extern int courseCount;          // 课程总数

// 教室相关
extern RoomNode* roomHead;       // 教室链表头指针
extern int roomCount;            // 教室总数

// 教师相关
extern TeacherNode* teacherHead; // 教师链表头指针
extern int teacherCount;         // 教师总数

// 登录状态和输入流（图形界面新增）
extern int is_login_success;     // 会员登录成功标志
extern FILE* original_stdin;     // 原始标准输入流（用于重定向恢复）
// 全局变量声明
extern int memberCount;
extern int adminCount;
extern int courseCount;
extern int roomCount;
extern int teacherCount;
/* 函数声明：系统管理 */
// 系统初始化（加载数据）
void init_system();
// 系统退出（保存数据）
void exit_system();

/* 函数声明：会员相关 */
// 会员注册（控制台/图形界面共用逻辑）
void member_reg();
// 会员登录（参数：登录方式1-4）
void member_log(int log_choice);
// 生成唯一会员ID
void generate_member_id(char* id);
// 会员查看个人信息
void member_view_info(MemberNode* member);
// 课程报名
int course_sign_up(MemberNode* member);

/* 函数声明：管理员相关 */
// 管理员登录（控制台逻辑，图形界面通过链表直接验证）
void admin_log();
// 管理员主菜单（图形化）
void admin_menu();
// 会员管理子菜单
void admin_member_submenu();
// 查看全部会员
void member_all_scan();
// 修改会员信息
void member_mod();
// 删除（注销）会员
void member_del();
// 新增会员
void member_add();
// 会员查找函数（按不同字段）
MemberNode* find_card_id(char* input);
MemberNode* find_member_id(char* input);
MemberNode* find_member_name(char* input);
MemberNode* find_phone(char* input);

/* 函数声明：课程管理 */
// 课程管理菜单
void course_manage_menu();
// 新增课程
void course_add();
// 删除课程
void course_del();
// 修改课程信息
void course_mod();
// 查看全部课程
void course_all_scan();

/* 函数声明：教室管理 */
// 教室管理菜单
void room_manage_menu();
// 新增教室
void room_add();
// 删除教室
void room_del();
// 修改教室信息
void room_mod();
// 查看全部教室
void room_all_scan();

/* 函数声明：教师管理 */
// 教师管理菜单
void teacher_manage_menu();
// 新增教师
void teacher_add();
// 删除教师
void teacher_del();
// 修改教师信息
void teacher_mod();
// 查看全部教师
void teacher_all_scan();

/* 函数声明：数据存储（文件读写） */
// 会员数据保存/加载
void storage_save_members();
void storage_load_members();
// 管理员数据保存/加载
void storage_save_admins();
void storage_load_admins();
// 课程数据保存/加载
void storage_save_courses();
void storage_load_courses();
// 教室数据保存/加载
void storage_save_rooms();
void storage_load_rooms();
// 教师数据保存/加载
void storage_save_teachers();
void storage_load_teachers();

/* 函数声明：工具函数 */
// 打印会员信息
void print_member(MemberNode* member);
// 选择是否打印会员信息
void is_print(MemberNode* member);
// 统一查找入口（1=卡号，2=会员ID，3=姓名，4=手机号）
MemberNode* find_member_by_type(int find_type, char* input);

/* 函数声明：图形界面专用（GTK） */
// 主窗口创建
void create_main_window();
// 会员登录窗口
void show_member_login_window();
// 管理员登录窗口
void show_admin_login_window();
// 会员注册窗口
void show_member_reg_window();
// 模拟标准输入（适配原有控制台输入逻辑）
void simulate_input(const char* input);
// 恢复标准输入流
void restore_stdin();

#endif // DANCE_STUDIO_H

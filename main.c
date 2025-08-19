
/*main.c 文件是系统入口 */

#include "dance_studio.h"

// 初始化全局变量
extern MemberNode *memberHead;
extern AdminNode *adminHead;
extern int is_login_success;
extern FILE *original_stdin;

// 会员登录
// 管理员登录
// 系统初始化（加载数据）
// 系统退出（保存数据）
int main (){
	init_system();
	int user_choice;
	while(1){
		printf("\n==========欢迎来到舞室管理系统==========\n");
		printf("1.会员登录\n");
		printf("2.管理员登录\n");
		printf("3.会员注册\n");
		printf("0.退出系统\n"); 
		printf("请输入操作编号: ");
		// 读取用户选择（处理输入错误）
		if (scanf("%d", &user_choice) != 1) {
			printf("输入错误，请重新输入数字！\n");
			// 清空输入缓冲区
			while (getchar() != '\n');
		}
		// 吸收换行符
		getchar();
		switch(user_choice){
			case 0:
			//	exit_system();
				printf("感谢使用本系统\n");
				return 0;
			case 1:
				{
					/*会员登录*/
					int mem_choice;
					char mem_choice_buf[STR_LEN];
					printf("\n请选择会员登录方式：\n");
					printf("1. 刷卡登录（读取卡号）\n");
					printf("2. 会员ID登录\n");
					printf("3. 手机号登录\n");
					printf("4. 会员姓名登录\n");
					printf("请输入选择: ");
					fgets(mem_choice_buf,sizeof(mem_choice_buf),stdin);
					if (sscanf(mem_choice_buf, "%d", &mem_choice) != 1 ||
							mem_choice < 1 || mem_choice > 4) {
						printf("无效选择，返回主菜单！\n");
						break;
					}
					member_log(mem_choice); // 会员登录
					break;
				}
				break;
			case 2:
				/*管理员登录*/
				{
				admin_log();
				}
				break;
			case 3:
				//会员注册
				{
					member_reg();
				}
				break;
			default:
				printf("无效操作，请重新选择\n");

		}

	}
}

/*member.c 文件用于会员功能处理,1会员登录，2注册*/
#include "dance_studio.h"
//会员注册由管理员增加会员来完成
void generate_member_id(char* id); 
//功能1：会员登录以查看个人信息
void member_log(int log_choice){
	char input[STR_LEN];  // 声明输入缓冲区
	char card_id[STR_LEN],phone[STR_LEN],member_id[STR_LEN],member_name[STR_LEN];
	MemberNode* current = memberHead;
	int is_success = 0;
	switch(log_choice)
	{
		case 1://刷卡即登录
			printf("请刷卡\n");
			fgets(card_id,STR_LEN,stdin);
			card_id[strcspn(card_id, "\n")] = '\0'; // 去除换行符
			while(current != NULL)
			{
				if((strcmp(current->data.card_id,card_id)==0&&current->data.isActive == STATUS_ACTIVE))//卡号一致且会员状态正常
				{	
					is_success = 1;
					printf("欢迎%s会员登录",current->data.member_name);
					//	member_view_info();登录后自动查看个人全部信息
					break;
				}
				current = current->next;
			}
			break;
		case 2://ID登录
			printf("请输入会员ID: ");
			fgets(input, STR_LEN, stdin);
			input[strcspn(input, "\n")] = '\0';

			while(current != NULL) {
				if(strcmp(current->data.member_id, input) == 0 && 
						current->data.isActive == STATUS_ACTIVE) {
					is_success = 1;
					printf("欢迎%s会员登录",current->data.member_name);
					//  member_view_info();登录后自动查看个人全部信息

					break;
				}
				current = current->next;
			}
			break;

		case 3://手机号登录
			printf("请输入手机号: ");
			fgets(input, STR_LEN, stdin);
			input[strcspn(input, "\n")] = '\0';

			while(current != NULL) {
				if(strcmp(current->data.phone, input) == 0 && 
						current->data.isActive == STATUS_ACTIVE) {
					is_success = 1;
					printf("欢迎%s会员登录",current->data.member_name);
					//  member_view_info();登录后自动查看个人全部信息

					break;
				}
				current = current->next;
			}
			break;

		case 4://姓名登录
			printf("请输入姓名: ");
			fgets(input, STR_LEN, stdin);
			input[strcspn(input, "\n")] = '\0';

			while(current != NULL) {
				if(strcmp(current->data.member_name, input) == 0 && 
						current->data.isActive == STATUS_ACTIVE) {
					is_success = 1;
					printf("欢迎%s会员登录",current->data.member_name);
					//  member_view_info();登录后自动查看个人全部信息
					break;
				}
				current = current->next;
			}
			break;
		default:
			printf("登录方式错误\n");
			return;
	}
	if(!is_success)
	{
		printf("登录失败，没有有效的会员信息\n");
	}
}
//功能2：会员注册
void member_reg(){
	if(memberCount >= MAX_MEMBERS) {
		printf("会员已满，无法注册！\n");
		return;
	}

	Member new_member;
	memset(&new_member, 0, sizeof(Member));

	// 生成唯一会员ID
	generate_member_id(new_member.member_id);
	printf("自动生成会员ID: %s\n", new_member.member_id);
	char card_id[STR_LEN];
	char birthday[STR_LEN];
	printf("请录入新会员卡");
	fgets(new_member.card_id, STR_LEN, stdin);
	new_member.card_id[strcspn(new_member.card_id, "\n")] = '\0';
	// 3. 读取其他基本信息
	printf("请输入姓名: ");
	fgets(new_member.member_name, STR_LEN, stdin);
	new_member.member_name[strcspn(new_member.member_name, "\n")] = '\0';

	printf("请输入生日（yyyy-mm-dd）: ");
	fgets(new_member.birthday, STR_LEN, stdin);
	new_member.birthday[strcspn(new_member.birthday, "\n")] = '\0';

	printf("请输入手机号: ");
	fgets(new_member.phone, STR_LEN, stdin);
	new_member.phone[strcspn(new_member.phone, "\n")] = '\0';

	// 4. 选择会员类型（枚举）
	printf("请选择会员类型（0-次卡，1-月卡，2-年卡，3-储值卡）: ");
	int type_choice;
	scanf("%d", &type_choice);
	getchar();  // 吸收换行符
	new_member.card_type = type_choice;

	// 5. 设置注册时间(取得系统时间)
	time_t t = time(NULL);//time_t 为时间类型，存储1970年1月1日零时令分到现在的秒数也称为时间戳，是一个非常大的整数。time（NULL）函数来获取当前系统的时间戳，NULL表示不需要额外存储，直接返回结果
	struct tm* tm_info = localtime(&t);//struct tm是一个时间结构体，里面自带time_year,time_mon,time_mday,time_hour,time_min, time_sec这些成员。这里将取得的时间戳存到tm_info这个指向结构体的指针中
	//sprintf函数将多个变量按照指定格式拼成一个字符串存放到目标字符串中
	//格式为sprintf(目标字符串,格式，变量)
	sprintf(new_member.reg_time ,"%04d-%02d-%02d %02d:%02d:%02d",
			tm_info->tm_year + 1900,  // 年份 = 结构体年份 + 1900（因为tm_year从1900开始算）
			tm_info->tm_mon + 1,      // 月份 = 结构体月份 + 1（因为月份从0开始算，0=1月）
			tm_info->tm_mday,         // 日期（1-31）
			tm_info->tm_hour,         // 小时（0-23）
			tm_info->tm_min,          // 分钟（0-59）
			tm_info->tm_sec);         // 秒（0-59） );
	printf("您的注册时间是：%s",new_member.reg_time);



	// 6. 设置有效期（根据会员类型自动计算，此处简化为手动输入）
	//要增加次卡余额计算
	switch(new_member.card_type)
	{
		case CARD_TYPE_TIMES:
		{
			int buy_times;
			printf("请输入您想要购买的次数\n");
			scanf("%d",&buy_times);
			getchar();//吸收换行符
			new_member.card_times = buy_times;
			printf("您的次卡余额为%d次",new_member.card_times);
		}

		case CARD_TYPE_MONTHS:  // 月卡：自动计算1个月后的有效期
		{
			struct tm expire_tm = *tm_info;  // 复制当前时间
			expire_tm.tm_mon += 1;  // 月份+1（核心：直接加1个月）
			mktime(&expire_tm);  // 关键函数：自动处理月份溢出
			// （比如当前是12月，+1后会变成下一年1月；当前是2月28日，+1月会自动调整为3月28日）

			// 格式化有效期为"yyyy-mm-dd"
			sprintf(new_member.expire_time, "%04d-%02d-%02d",
					expire_tm.tm_year + 1900,
					expire_tm.tm_mon + 1,
					expire_tm.tm_mday);

			printf("月卡办理成功！有效期至：%s\n", new_member.expire_time);
			break;
		}

		case CARD_TYPE_YEARS:  // 年卡：自动计算1年后的有效期（同理）
		{
			struct tm expire_tm = *tm_info;
			expire_tm.tm_year += 1;  // 年份+1
			mktime(&expire_tm);

			sprintf(new_member.expire_time, "%04d-%02d-%02d",
					expire_tm.tm_year + 1900,
					expire_tm.tm_mon + 1,
					expire_tm.tm_mday);

			printf("年卡办理成功！有效期至：%s\n", new_member.expire_time);
			break;
		}

		case CARD_TYPE_MONEY:  // 储值卡：有效期可以设为长期（比如2年）
		{
			struct tm expire_tm = *tm_info;
			expire_tm.tm_year += 2;  // 2年后过期
			mktime(&expire_tm);

			sprintf(new_member.expire_time, "%04d-%02d-%02d",
					expire_tm.tm_year + 1900,
					expire_tm.tm_mon + 1,
					expire_tm.tm_mday);

			printf("储值卡办理成功！有效期至：%s\n", new_member.expire_time);
			break;
		}
	}



	// 7. 初始化其他字段
	new_member.balance = 0.0;  // 储值卡初始余额为0
	new_member.isActive = STATUS_ACTIVE;  // 初始状态为正常

	// 8. 创建链表节点并插入双向链表（尾部插入）
	MemberNode *new_node = (MemberNode *)malloc(sizeof(MemberNode));
	if (new_node == NULL) {
		printf("注册失败：内存分配失败！\n");
		return;
	}
	new_node->data = new_member;  // 复制数据到节点
	new_node->prev = NULL;
	new_node->next = NULL;

	// 插入双向链表（尾部插入）
	if (memberHead == NULL) {
		// 链表为空，新节点作为头节点
		memberHead = new_node;
	} else {
		// 遍历到尾部
		MemberNode *current = memberHead;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_node;
		new_node->prev = current;
	}

	// 9. 更新会员数量并保存数据
	memberCount++;
	printf("注册成功！会员总数：%d\n", memberCount);
	// 调用保存函数（需实现，将链表写入文件）
	storage_save_members();
}
//功能3： 查看个人信息
void member_view_info(MemberNode* member) {
	printf("\n===== 个人信息 =====");
	printf("\n会员ID: %s", member->data.member_id);
	printf("\n姓名: %s", member->data.member_name);
	printf("\n生日: %s", member->data.birthday);
	printf("\n手机号: %s", member->data.phone);
	printf("\n会员类型: ");
	switch(member->data.card_type) {
		case CARD_TYPE_TIMES: printf("次卡"); break;
		case CARD_TYPE_MONTHS: printf("月卡"); break;
		case CARD_TYPE_YEARS: printf("年卡"); break;
		case CARD_TYPE_MONEY: printf("储值卡"); break;
	}
	printf("\n有效期至: %s", member->data.expire_time);
	printf("\n余额: %.2f元", member->data.balance);
	printf("\n状态: %s", member->data.isActive == STATUS_ACTIVE ? "正常" : "注销");
	printf("\n====================\n");
}
//功能4： 生成唯一会员ID（格式：MEM+日期+序号）
void generate_member_id(char* id) {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	sprintf(id, "MEM%d%02d%02d%03d", 
			tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, memberCount + 1);
}

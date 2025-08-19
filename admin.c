/*admin.c 文件用于管理员功能处理*/
#include "dance_studio.h"

// 声明管理员菜单函数
void admin_menu();
void admin_member_submenu();
// 声明会员管理子函数
void member_all_scan();
void member_mod();
void member_del();
void member_add();
MemberNode* find_card_id(char* input);
MemberNode* find_member_id(char *input);
MemberNode* find_phone(char *input);
MemberNode* find_member_name(char *input);
void admin_log();

// 管理员登录函数
void admin_log(){
	char admin_id[STR_LEN],admin_name[STR_LEN],password[STR_LEN];
 // 新增：清空输入缓冲区（解决主菜单输入残留的换行符）
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

	printf("请输入管理员id:\n");
	fgets(admin_id,STR_LEN,stdin);
	admin_id[strcspn(admin_id, "\n")] = '\0'; // 去除换行符
	printf("请输入管理员姓名:\n");
	fgets(admin_name,STR_LEN,stdin);
	admin_name[strcspn(admin_name, "\n")] = '\0'; // 去除换行符
	printf("请输入管理员密码:\n");
	fgets(password,STR_LEN,stdin);
	password[strcspn(password, "\n")] = '\0'; // 去除换行符

 // 新增调试日志：打印实际读取的输入
    printf("[调试] 输入的管理员信息：ID=%s, 姓名=%s, 密码=%s\n",
           admin_id, admin_name, password);


	//遍历管理员链表进行验证
	AdminNode* current = adminHead;//从头节点开始
	while(current != NULL)
	{
		// 对比管理员ID、姓名、密码（原代码逻辑正确，补充闭合）
		if (strcmp(current->data.admin_id,admin_id)==0 && 
				strcmp(current->data.admin_name,admin_name)==0 && 
				strcmp(current->data.password,password)==0)
		{	
			printf("管理员%s登录成功\n",admin_name);
			admin_menu();//进入管理员菜单
			return ;
		}
		current = current->next;
	}
	printf("登录失败，账号，姓名或密码错误\n");
}


// 管理员菜单
void admin_menu(){
	int choice;
	while(1){// 循环显示菜单，直到选择返回主菜单
		printf("\n===== 管理员中心 =====");
		printf("\n1. 会员管理（增删改查）\n");
		printf("2. 课程管理\n");
		printf("3. 场地管理\n");
		printf("4. 教师管理\n");
		printf("0. 返回主菜单\n");
		printf("请输入操作编号：");

		// 处理输入错误（沿用main.c的输入逻辑）
		if (scanf("%d", &choice) != 1) {
			printf("输入错误，请重新输入数字！\n");
			while (getchar() != '\n');
			continue;
		}
		getchar();//吸收换行符

		switch(choice){
			case 1:
				// 会员管理子菜单
				admin_member_submenu();
				break;
			case 2:
				// 课程管理（后续完善，先提示）
				printf("课程管理功能待完善\n");
				break;
			case 3:
				// 场地管理（后续完善，先提示）
				printf("场地管理功能待完善\n");
				break;
			case 4:
				// 教师管理（后续完善，先提示）
				printf("教师管理功能待完善\n");
				break;
			case 0:
				printf("返回主菜单\n");
				return;//退出管理员菜单
			default:
				printf("无效操作，请重新选择\n");
		}
	}
}

// 1. 会员管理子菜单（管理员菜单中调用）
void admin_member_submenu(){
	int choice;
	while(1){
		printf("\n===== 会员管理子菜单 =====");
		printf("\n1. 查看全部会员\n");
		printf("2. 新增会员\n");
		printf("3. 删除会员（注销）\n");
		printf("4. 修改会员信息\n");
		printf("5. 按卡号查找会员\n");
		printf("6. 按手机号查找会员\n");
		printf("7. 按姓名查找会员\n");
		printf("8. 按会员id查找会员\n");
		printf("0. 返回管理员菜单\n");
		printf("请输入操作编号：");

		if (scanf("%d", &choice) != 1) {
			printf("输入错误，请重新输入数字！\n");
			while (getchar() != '\n');
			continue;
		}
		getchar();//吸收换行符

		switch(choice){
			case 1: member_all_scan(); break;
			case 2: member_add(); break;
			case 3: member_del(); break;
			case 4: member_mod(); break;
			case 5:
					{
						printf("请输入会员卡号:\n");  // 注意：原注释写的是"会员id"，但case5实际是"按卡号查找"，这里修正文字提示
						char input_card_id[STR_LEN];
						fgets(input_card_id, STR_LEN, stdin);
						input_card_id[strcspn(input_card_id, "\n")] = '\0';  // 去除换行符
						find_card_id(input_card_id);  // 传递输入的卡号作为参数
						break;
					}
			case 6:
					{
						printf("请输入手机号:\n");
						char input_phone[STR_LEN];
						fgets(input_phone, STR_LEN, stdin);
						input_phone[strcspn(input_phone, "\n")] = '\0';
						find_phone(input_phone);  // 传递输入的手机号作为参数
						break;
					}
			case 7:
					{
						printf("请输入会员姓名:\n");
						char input_name[STR_LEN];
						fgets(input_name, STR_LEN, stdin);
						input_name[strcspn(input_name, "\n")] = '\0';
						find_member_name(input_name);  // 传递输入的姓名作为参数
						break;
					}
			case 8:
					{
						printf("请输入会员ID:\n");
						char input_member_id[STR_LEN];
						fgets(input_member_id, STR_LEN, stdin);
						input_member_id[strcspn(input_member_id, "\n")] = '\0';
						find_member_id(input_member_id);  // 传递输入的会员ID作为参数
						break;
					}
			case 0: return;
			default: printf("无效操作，请重新选择\n");
		}
	}
}
// 2. 查看全部会员信息
void member_all_scan(){
	if (memberHead == NULL) {
		printf("暂无会员数据\n");
		return;
	}

	MemberNode *current = memberHead;
	int index = 1;
	printf("\n===== 全部会员信息 =====\n");
	while (current != NULL) {
		// 打印会员核心信息（格式清晰，易读）
		printf("第%d名会员：\n", index);
		printf("会员ID：%s\n", current->data.member_id);
		printf("姓名：%s\n", current->data.member_name);
		printf("卡号：%s\n", current->data.card_id);
		printf("手机号：%s\n", current->data.phone);
		printf("会员类型：%s\n",
				current->data.card_type == CARD_TYPE_TIMES ? "次卡" :
				current->data.card_type == CARD_TYPE_MONTHS ? "月卡" :
				current->data.card_type == CARD_TYPE_YEARS ? "年卡" : "储值卡");
		printf("状态：%s\n", current->data.isActive == STATUS_ACTIVE ? "正常" : "注销");
		printf("------------------------\n");

		current = current->next;
		index++;
	}
}

// 3. 新增会员（管理员手动添加，逻辑类似member_reg，补充会员ID生成）
void member_add(){
	Member new_member;
	memset(&new_member, 0, sizeof(Member));//初始化

	// 生成唯一会员ID（格式：M+日期+序号，如M20240815001）
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char date[10];
	sprintf(date, "%04d%02d%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
	sprintf(new_member.member_id, "M%s%03d", date, memberCount+1);
	printf("自动生成会员ID：%s（唯一不可变）\n", new_member.member_id);

	// 录入卡号（确保唯一）
	char card_id[STR_LEN];
	while(1){
		printf("请输入会员卡号：");
		fgets(card_id, STR_LEN, stdin);
		card_id[strcspn(card_id, "\n")] = '\0';

		// 检查卡号是否已存在
		MemberNode *current = memberHead;
		int is_exist = 0;
		while(current != NULL){
			if (strcmp(current->data.card_id, card_id) == 0) {
				is_exist = 1;
				break;
			}
			current = current->next;
		}
		if (is_exist) {
			printf("该卡号已存在，请重新输入\n");
		} else {
			strcpy(new_member.card_id, card_id);
			break;
		}
	}


	printf("请输入姓名: ");
	fgets(new_member.member_name, STR_LEN, stdin);
	new_member.member_name[strcspn(new_member.member_name, "\n")] = '\0';

	printf("请输入生日（yyyy-mm-dd）: ");
	fgets(new_member.birthday, STR_LEN, stdin);
	new_member.birthday[strcspn(new_member.birthday, "\n")] = '\0';

	printf("请输入手机号: ");
	fgets(new_member.phone, STR_LEN, stdin);
	new_member.phone[strcspn(new_member.phone, "\n")] = '\0';

	// 选择会员类型
	printf("请选择会员类型（0-次卡，1-月卡，2-年卡，3-储值卡）: ");
	int type_choice;
	scanf("%d", &type_choice);
	getchar();
	new_member.card_type = type_choice;

	//要封装为函数 注册时间（取当前系统时间）
	sprintf(new_member.reg_time, "%04d-%02d-%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
	printf("注册时间（自动填充）：%s\n", new_member.reg_time);

	// 要封装为函数 有效期（手动输入，可后续扩展自动计算）
	printf("请输入有效期（yyyy-mm-dd）: ");
	fgets(new_member.expire_time, STR_LEN, stdin);
	new_member.expire_time[strcspn(new_member.expire_time, "\n")] = '\0';

	// 初始化其他字段
	new_member.balance = 0.0;
	new_member.isActive = STATUS_ACTIVE;

	// 插入链表（复用member_reg的逻辑）
	MemberNode *new_node = (MemberNode *)malloc(sizeof(MemberNode));
	new_node->data = new_member;
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
	printf("新增会员成功！当前会员总数：%d\n", memberCount);
	printf("\n================ 插入的会员信息 ================\n");
	print_member(new_node);
	storage_save_members();//保存到文件
}

// 4. 删除会员（逻辑：设置状态为注销，而非物理删除）
void member_del(){
	if (memberHead == NULL) {
		printf("暂无会员数据，无法删除\n");
		return;
	}

	char card_id[STR_LEN];
	printf("请输入要删除（注销）的会员卡号：");
	fgets(card_id, STR_LEN, stdin);
	card_id[strcspn(card_id, "\n")] = '\0';

	MemberNode *current = memberHead;
	while (current != NULL) {
		if (strcmp(current->data.card_id, card_id) == 0) {
			if (current->data.isActive == STATUS_INACTIVE) {
				printf("该会员已注销，无需重复操作\n");
				return;
			}
			// 设置状态为注销
			current->data.isActive = STATUS_INACTIVE;
			printf("会员%s（卡号：%s）已注销\n", current->data.member_name, card_id);
			storage_save_members();//保存修改
			return;
		}
		current = current->next;
	}
	printf("未找到该卡号对应的会员\n");
}

//5. 修改会员        
void member_mod(){
	printf("请问你想修改哪位会员信息？(请输入1.卡号/2.会员id/3.姓名/4.手机号)");
	int mod_info_choice;
	scanf("%d",&mod_info_choice);
	getchar();
	// 定义查找用的指针（移到switch外，避免语法错误）
	MemberNode* current = memberHead;
	// 标记是否找到会员
	int found = 0;
	// 存储找到的会员节点（用于后续修改）
	MemberNode* target_member = NULL;
	switch(mod_info_choice)
	{//输入会员信息验证有无该会员存在
		//卡号id
		case 1:
			{
				printf("请输入卡号：");
				char input_mod_info[STR_LEN];
				fgets(input_mod_info,STR_LEN,stdin);
				input_mod_info[strcspn(input_mod_info, "\n")] = '\0'; // 去除换行符
				target_member = find_card_id(input_mod_info);
			}
			break;
			//会员id
		case 2:
			{
				printf("请输入会员id：");
				char input_mod_info[STR_LEN];
				fgets(input_mod_info,STR_LEN,stdin);
				input_mod_info[strcspn(input_mod_info, "\n")] = '\0'; // 去除换行符
				target_member = find_member_id(input_mod_info);
			}
			break;
			//姓名
		case 3:
			{		
				printf("请输入会员姓名：");
				char input_mod_info[STR_LEN];
				fgets(input_mod_info,STR_LEN,stdin);
				input_mod_info[strcspn(input_mod_info, "\n")] = '\0'; // 去除换行符
				target_member = find_member_name(input_mod_info);
			}
			break;
			//手机号
		case 4:
			{
				printf("请输入会员手机号：");
				char input_mod_info[STR_LEN];
				fgets(input_mod_info,STR_LEN,stdin);
				input_mod_info[strcspn(input_mod_info, "\n")] = '\0'; // 去除换行符
				target_member = find_phone(input_mod_info);
			}
			break;
		default:
			printf("输入错误\n");
			return;
	}
	// 判断是否找到会员
	if(target_member == NULL)
	{
		printf("未找到该会员信息！\n");
		return;
	}
	//找到后进入会员修改页面
	while(1){
		int mod_choice;
		printf("\n============这里是修改会员信息页面===========\n");
		printf("您想修改哪项会员信息？\n");
		printf("------1.会员卡号------\n");
		printf("------2.会员姓名------\n");
		printf("------3.会员手机号----\n");
		printf("------4.会员卡类型----\n");
		printf("------5.会员生日------\n");
		printf("------0.退出修改------\n");
		printf("请输入操作编号：\n");
		scanf("%d",&mod_choice);
		getchar();
		switch(mod_choice)
		{
			case 0:
				printf("已退出修改，信息已保存\n");
				storage_save_members();
				return;
				break;
			case 1://修改卡号
				{
					printf("请录入新会员卡:");
					while(1)
					{
						char input_card_id[STR_LEN];
						fgets(input_card_id,STR_LEN,stdin);
						input_card_id[strcspn(input_card_id,"\n")]='\0';
						// 检查新卡号是否已存在
						MemberNode* check = memberHead;
						int exists = 0;
						while(check != NULL)
						{
							if(strcmp(check->data.card_id, input_card_id) == 0)
							{
								exists = 1;
								break;
							}
							check = check->next;
						}
						if(exists)
						{
							printf("修改失败：该卡号已被使用！\n");
							printf("请重新录入会员卡：");
							continue;

						}

						strcpy(target_member->data.card_id,input_card_id);
						printf("卡号修改成功，新的会员信息为：\n");
						storage_save_members();
						print_member(target_member);
						break;
					}
					break;
				}
			case 2://修改姓名
				{
					printf("请输入要修改的姓名：");
					while(1)
					{
						char input_member_name[STR_LEN];
						fgets(input_member_name,STR_LEN,stdin);
						input_member_name[strcspn(input_member_name,"\n")]='\0';//去除换行符
						//检查要修改的姓名是否存在，由用户决定是否继续修改
						MemberNode* check = memberHead;
						int exists = 0;
						while(check != NULL)
						{
							//姓名存在时
							if(strcmp(check->data.member_name,input_member_name) == 0)
							{
								exists = 1;
								break;//退出当前while循环。找到同名时直接退出不再继续遍历链表
							}
							check = check->next;
						}
						if(exists)//遍历循环结束后执行，进行重名处理
						{
							printf("该姓名已存在，确定修改？y是/n否：");
							char choice_name[STR_LEN];
							fgets(choice_name,STR_LEN,stdin);
							choice_name[strcspn(choice_name,"\n")]='\0';//去除换行符
							if(strcmp(choice_name,"y") == 0)
							{
								strcpy(target_member->data.member_name ,input_member_name);
								printf("姓名修改成功");
								storage_save_members();
								is_print(target_member);
							}
							else
							{
								printf("请重新输入姓名：");
								continue;//跳过当前循环剩余的代码，重名重新修改，回到while(1)开头
							}
						}
						else
						{
							strcpy(target_member->data.member_name,input_member_name);
							printf("姓名修改成功！\n");
							storage_save_members();
							is_print(target_member);
							break;//退出while(1)，非重名修改成功后

						}
						break;//退出while(1)，重名确认修改

					}
					break;//退出case2
				}
			case 3://修改手机号
			case 4://修改会员卡类型
			case 5://修改会员生日
			default:
				printf("输入无效\n");
				
		}
	}
}

//6.会员卡号寻找会员
MemberNode* find_card_id(char* input){
	MemberNode* current = memberHead;
	while(current != NULL)
	{
		if(strcmp(current->data.card_id,input) == 0)
		{
			printf("已查找到卡号为%s的用户，以下为该用户的全部信息",current->data.card_id);
			print_member(current);
			return current;
		}
		current= current->next;

	}
	printf("为找到该卡号的会员\n");
	return 0;
}
//7.手机号寻找会员
MemberNode* find_phone(char* input){
	printf("按手机号查找功能\n");
	MemberNode* current = memberHead;
	while(current != NULL)
	{
		if(strcmp(current->data.phone,input) == 0)
		{
			printf("已查找到手机号为%s的用户，以下为该用户的全部信息\n",current->data.phone);
			print_member(current);
			return current;
		}
		current= current->next;

	}
	printf("未找到该手机号的会员\n");
	return 0;
}
//8.姓名寻找会员
MemberNode* find_member_name(char* input){
	printf("按姓名查找功能\n");
	MemberNode* current = memberHead;
	while(current != NULL)
	{
		if(strcmp(current->data.member_name,input) == 0)
		{
			printf("已查找到姓名为%s的用户，以下为该用户的全部信息\n",current->data.member_name);
			print_member(current);
			return current;
		}
		current= current->next;

	}
	printf("未找到该姓名的会员\n");
	return 0;
}
//9.会员id寻找会员
MemberNode* find_member_id(char* input){
	printf("按会员id查找功能\n");
	MemberNode* current = memberHead;
	while(current != NULL)
	{
		if(strcmp(current->data.member_id,input) == 0)
		{
			printf("查询到手机号为%s的用户，以下为该用户的全部信息",current->data.member_id);
			print_member(current);
			return current;
		}
		current= current->next;


	}
	printf("未找到该会员id的会员\n");
	return 0;
}



//打印会员信息
void print_member(MemberNode* member){
	if(member == NULL)
	{
		printf("错误的会员信息\n");
		return;
	}
	// 统一格式打印会员信息
	printf("会员ID：%s\n", member->data.member_id);
	printf("会员姓名：%s\n", member->data.member_name);
	printf("生日：%s\n", member->data.birthday);
	printf("手机号：%s\n", member->data.phone);
	printf("会员卡卡号：%s\n", member->data.card_id);

	// 会员卡类型（转换枚举为中文）
	printf("会员卡类型：");
	switch (member->data.card_type) {
		case CARD_TYPE_TIMES:  printf("次卡（剩余次数：%d次）\n", member->data.card_times); break;
		case CARD_TYPE_MONTHS: printf("月卡\n"); break;
		case CARD_TYPE_YEARS:  printf("年卡\n"); break;
		case CARD_TYPE_MONEY:  printf("储值卡（余额：%.2f元）\n", member->data.balance); break;
		default:               printf("未知类型\n");
	}

	printf("注册时间：%s\n", member->data.reg_time);
	printf("到期时间：%s\n", member->data.expire_time);
	printf("状态：%s\n", member->data.isActive == STATUS_ACTIVE ? "正常" : "注销");
	printf("==========================================\n");
}
//选择是否打印会员信息
void is_print(MemberNode* member)
{
	printf("是否查看修改后信息? y是/n否：");
	char choice_print[STR_LEN];
	fgets(choice_print,STR_LEN,stdin);
	choice_print[strcspn(choice_print,"\n")]='\0';
	if(strcmp(choice_print,"y") == 0)
	{
		print_member(member);
	}
}

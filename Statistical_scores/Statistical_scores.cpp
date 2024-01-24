#include <iostream>
#include <string>
#define MAXLENGTH 6
using namespace std;

typedef struct Struct_student {
	string student_id;
	string name;
	int chinese_score;
	int math_score;
	int english_score;
	int total_score;
	int length;
};


void Insertion_sort(Struct_student struct_student[]);

int main()
{
	Struct_student struct_student[101];
	struct_student[1].student_id = "2022211501";
	struct_student[2].student_id = "2022211502";
	struct_student[3].student_id = "2022211503";
	struct_student[4].student_id = "2022211504";
	struct_student[5].student_id = "2022211505";
	struct_student[6].student_id = "2022211506";

	struct_student[1].name = "zhangyi";
	struct_student[2].name = "zhanger";
	struct_student[3].name = "zhangsan";
	struct_student[4].name = "zhangsi";
	struct_student[5].name = "zhangwu";
	struct_student[6].name = "zhangliu";

	struct_student[1].chinese_score = 90;
	struct_student[2].chinese_score = 85;
	struct_student[3].chinese_score = 82;
	struct_student[4].chinese_score = 83;
	struct_student[5].chinese_score = 88;
	struct_student[6].chinese_score = 90;

	struct_student[1].math_score = 80;
	struct_student[2].math_score = 85;
	struct_student[3].math_score = 89;
	struct_student[4].math_score = 81;
	struct_student[5].math_score = 87;
	struct_student[6].math_score = 80;

	struct_student[1].english_score = 80;
	struct_student[2].english_score = 76;
	struct_student[3].english_score = 82;
	struct_student[4].english_score = 79;
	struct_student[5].english_score = 81;
	struct_student[6].english_score = 80;

	struct_student[1].length = MAXLENGTH;
	struct_student[2].length = MAXLENGTH;
	struct_student[3].length = MAXLENGTH;
	struct_student[4].length = MAXLENGTH;
	struct_student[5].length = MAXLENGTH;
	struct_student[6].length = MAXLENGTH;

	for (int i = 0; i < MAXLENGTH; i++)
	{
		struct_student[i + 1].total_score = struct_student[i + 1].chinese_score + struct_student[i + 1].math_score + struct_student[i + 1].english_score;
	}
	Insertion_sort(struct_student);

	return 0;
}

void Insertion_sort(Struct_student struct_student[]) {
	for (int i = 2; i < struct_student[1].length + 1; i++)
	{
		if (struct_student[i - 1].total_score < struct_student[i].total_score)
		{
			struct_student[0] = struct_student[i];
			int j;
			for (j = i - 1; struct_student[0].total_score > struct_student[j].total_score; j--)
			{
				struct_student[j + 1] = struct_student[j];
			}
			struct_student[j + 1] = struct_student[0];
		}
	}
	for (int i = 1; i < struct_student[1].length + 1; i++)
	{
		cout << "第" << i << "名同学的成绩如下" << endl;
		if (struct_student[i].total_score == struct_student[i + 1].total_score)
		{
			cout << "姓名：" << struct_student[i].name << "，学号" << struct_student[i].student_id << "，总分" << struct_student[i].total_score << endl;
			cout << "语文成绩：" << struct_student[i].chinese_score << "，数学成绩" << struct_student[i].math_score << "，英语成绩" << struct_student[i].english_score << endl;
			cout << "第" << i << "名同学的成绩如下" << endl;
			i++;
		}
		cout << "姓名：" << struct_student[i].name << "，学号" << struct_student[i].student_id << "，总分" << struct_student[i].total_score << endl;
		cout << "语文成绩：" << struct_student[i].chinese_score << "，数学成绩" << struct_student[i].math_score << "，英语成绩" << struct_student[i].english_score << endl;
	}
}
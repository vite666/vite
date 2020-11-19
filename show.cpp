

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <tchar.h>
#include <stdlib.h>
#include <easyx.h>


/* ��������չʾ���Ŀ�ߣ����ݵ�����Ļ��΢�� */ 
#define WIDTH 100
#define HEIGHT 28//HEIGHT����ڵ���28 
/******************************************/ 
void create_list(char [][WIDTH] );//����һ����20����100������ 
void print_list(const char [][WIDTH] );//��ӡ������ 
void gotoxy(int,int);//�ƶ���� 
void print_helix(char [][WIDTH]);//��������
int assertnum(char [][WIDTH],int,int); 
void HideCursor();//���ع�� 
void color(const unsigned short color1);
void print_heart1(char [][WIDTH],int );//������
void print_heart2(char [][WIDTH],int ); //������ӡ

int print_heart3(int*,int ,int);//�������� 
float f(float x, float y, float z);
float h(float x, float z);

void roll_screen(char [][5],int,int);//��ӡ�֣��޳�99����Ĭ����Ļ�м���ж��� 

void clean_screen(char list[][WIDTH]){//����ר�ú��� 
	create_list(list);
    gotoxy(0,0);
  	print_list(list);
  	gotoxy(0,0);
}
/*���Ǵ��ĵ��µ�����*/ 
void sentance() {
    char title[] ="============ 2020 11 18 ============";          //�������
    char word[] = "         �Ķ��ͳ������㿴��";          //������˵������
    /*ע�������ʽ*/
	printf("\n\t      ");                                    
    printf("%s",title);
    printf("\n\t      ");
    printf("%s", word);
}
/**************MAIN����**********************************/ 
int main(){
	/*��ʼ�����ݺ���*/ 
	int heart_count=1;
    char list[HEIGHT][WIDTH];
    create_list(list);
    setbkcolor(WHITE);
    /*******************/ 
    
    /*��ɫ��Ӧֵ��
����0=��ɫ                8=��ɫ����
  �� 1=��ɫ                9=����ɫ                ����                        
����2=��ɫ                10=����ɫ               ����
����3=����ɫ          11=��ǳ��ɫ        ��
����4=��ɫ                12=����ɫ        ����
����5=��ɫ                13=����ɫ                ����
����6=��ɫ                14=����ɫ               ����
����7=��ɫ                15=����ɫ        
����
*/
   /*��˫��������Ҫ��ӡ����*/ 
    char word1[21][5]={"��","��","��","x","x","ͬ","ѧ"}; //��ʽ������и��� 
    int len1=7;//�����ж����־����ö��� ��߲�����WIDTHֵ 
    int color_num=3;//���������ɫ��Ӧֵ 
    roll_screen(word1,len1,color_num);
  	clean_screen(list);
  	
    /*���������*/ 
    print_helix(list);
    clean_screen(list);
    
    /*������ӡ��Ч*/ 
    color_num=4;//������ɫ 
    print_heart2(list,color_num);
    clean_screen(list);
    
    /*��������Ч*/ 
    color_num=4;//������ɫ 
    print_heart1(list,color_num);
    clean_screen(list);
    
    /*��������*/ 
    color_num=4;//������ɫ 
    int speed=1;//�������������ٶ� ����ֵԽСԽ�죬��������� 
  	int a=print_heart3(&heart_count,color_num,speed);
  	clean_screen(list);
  	
  	
  	char word2[21][5]={"��","Ļ"};
	int len2=2;//�������ݵ����� 
	color_num=10;//������ɫ 
  	roll_screen(word2,len2,color_num);
  	clean_screen(list); 
 
 	/*���ϵĸ��ĵ��ԣ���õ�����Ҫ�Ľ����*/   
}
/****************�������ݿ��Բ���****************/ 
/*����ע��Ҳд�ıȽ���ϸ*/ 
void roll_screen(char word[][5],int len,int color_num){
	int x=50;
	int count=0;
	color(color_num);
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(i==10){
				if(j>(50-len)&&j<(50+len)){
					printf("%s",word[count]);
					count+=1;
					j+=1;
					continue;
				}
			
			}
			printf(" ");	
	}
	printf("\n");
	
	} 
	Sleep(2000);
	color(16);
}

void print_heart1(char list[][WIDTH],int color_num){
	color(color_num);
	char module_1[WIDTH+10]={'0','0','*','*','*','0','0','0','0','0','*','*','*','0','0'};
	char module_2[WIDTH+10]={'0','*','*','*','*','*','0','0','0','*','*','*','*','*','0'};
	char module_3[WIDTH+10]={'*','*','*','*','*','*','*','0','*','*','*','*','*','*','*'};
	char module_4[WIDTH+10]={'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'};
	char module_5[WIDTH+10]={'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'};
	char module_6[WIDTH+10]={'0','*','*','*','*','*','*','*','*','*','*','*','*','*','0'};
	char module_7[WIDTH+10]={'0','0','*','*','*','*','*','*','*','*','*','*','*','0','0'};
	char module_8[WIDTH+10]={'0','0','0','*','*','*','*','*','*','*','*','*','0','0','0'};
	char module_9[WIDTH+10]={'0','0','0','0','*','*','*','*','*','*','*','0','0','0','0'};
	char module_10[WIDTH+10]={'0','0','0','0','0','*','*','*','*','*','0','0','0','0','0'};
	char module_11[WIDTH+10]={'0','0','0','0','0','0','*','*','*','0','0','0','0','0','0'};
	char module_12[WIDTH+10]={'0','0','0','0','0','0','0','*','0','0','0','0','0','0','0'};
		int module_num=0;
		int count=1;
		int count_1=1;
		for(int i=0;i<WIDTH-1;i++){
			
			list[3][i]=module_1[module_num];
			list[4][i]=module_2[module_num];
			list[5][i]=module_3[module_num];
			list[6][i]=module_4[module_num];
			list[7][i]=module_5[module_num];
			list[8][i]=module_6[module_num];
			list[9][i]=module_7[module_num];
			list[10][i]=module_8[module_num];
			list[11][i]=module_9[module_num];
			list[12][i]=module_10[module_num];
			list[13][i]=module_11[module_num];
			list[14][i]=module_12[module_num];
			
			
			if(count%15==0){
				module_num=0;
				i+=1;
				count=1;
				count_1+=1; 
				continue;
				
			}
			if(count_1==6){
				break;
			}
			
			count+=1;
			module_num+=1;
			
			gotoxy(0,0);
			HideCursor();
			 
			print_list(list);
		}
	
	color(16);
	
}
void print_heart2(char list[][WIDTH],int color_num){
	color(color_num);
	char module_1[WIDTH+10]={'0','0','*','*','*','0','0','0','0','0','*','*','*','0','0'};
	char module_2[WIDTH+10]={'0','*','*','*','*','*','0','0','0','*','*','*','*','*','0'};
	char module_3[WIDTH+10]={'*','*','*','*','*','*','*','0','*','*','*','*','*','*','*'};
	char module_4[WIDTH+10]={'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'};
	char module_5[WIDTH+10]={'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'};
	char module_6[WIDTH+10]={'0','*','*','*','*','*','*','*','*','*','*','*','*','*','0'};
	char module_7[WIDTH+10]={'0','0','*','*','*','*','*','*','*','*','*','*','*','0','0'};
	char module_8[WIDTH+10]={'0','0','0','*','*','*','*','*','*','*','*','*','0','0','0'};
	char module_9[WIDTH+10]={'0','0','0','0','*','*','*','*','*','*','*','0','0','0','0'};
	char module_10[WIDTH+10]={'0','0','0','0','0','*','*','*','*','*','0','0','0','0','0'};
	char module_11[WIDTH+10]={'0','0','0','0','0','0','*','*','*','0','0','0','0','0','0'};
	char module_12[WIDTH+10]={'0','0','0','0','0','0','0','*','0','0','0','0','0','0','0'};
		
		for(int j=0;j<(WIDTH>>1)-1;j++){
			int module_num=0;
			int count=j+1;
			int speed=1;
			int i=j;
			while(count){
				list[3][i]=module_1[module_num];
				list[4][i]=module_2[module_num];
				list[5][i]=module_3[module_num];
				list[6][i]=module_4[module_num];
				list[7][i]=module_5[module_num];
				list[8][i]=module_6[module_num];
				list[9][i]=module_7[module_num];
				list[10][i]=module_8[module_num];
				list[11][i]=module_9[module_num];
				list[12][i]=module_10[module_num];
				list[13][i]=module_11[module_num];
				list[14][i]=module_12[module_num];
				list[3][WIDTH-2-i]=module_1[module_num];
				list[4][WIDTH-2-i]=module_2[module_num];
				list[5][WIDTH-2-i]=module_3[module_num];
				list[6][WIDTH-2-i]=module_4[module_num];
				list[7][WIDTH-2-i]=module_5[module_num];
				list[8][WIDTH-2-i]=module_6[module_num];
				list[9][WIDTH-2-i]=module_7[module_num];
				list[10][WIDTH-2-i]=module_8[module_num];
				list[11][WIDTH-2-i]=module_9[module_num];
				list[12][WIDTH-2-i]=module_10[module_num];
				list[13][WIDTH-2-i]=module_11[module_num];
				list[14][WIDTH-2-i]=module_12[module_num];
				
				count-=1;
				i-=1;
				speed+=1;
				module_num+=1;
				if(speed%20==0){
					speed=1;
					gotoxy(0,0);
					HideCursor();
					print_list(list);
					
				}
				
			}
			
			
		}
	
	color(16);
	
}
int print_heart3(int *heart_count,int color_num,int speed){
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
    _TCHAR buffer[25][80] = { _T(' ') };
    _TCHAR ramp[] = _T(".:-=+*#%@");
   color(color_num);
    for (float t = 0.0f;; t += 0.1f) {
        int sy = 0;
        float s = sinf(t);
        float a = s * s * s * s * 0.2f;
        for (float z = 1.3f; z > -1.2f; z -= 0.1f) {
            _TCHAR* p = &buffer[sy++][0];
            float tz = z * (1.2f - a);
            for (float x = -1.5f; x < 1.5f; x += 0.05f) {
                float tx = x * (1.2f + a);
                float v = f(tx, 0.0f, tz);
                if (v <= 0.0f) {
                    float y0 = h(tx, tz);
                    float ny = 0.01f;
                    float nx = h(tx + ny, tz) - y0;
                    float nz = h(tx, tz + ny) - y0;
                    float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
                    float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
                    *p++ = ramp[(int)(d * 5.0f)];
                }
                else
                    *p++ = ' ';
            }
        }
        

        for (sy = 0; sy < 25; sy++) {
            COORD coord = { 0, sy };
            SetConsoleCursorPosition(o, coord);
            WriteConsole(o, buffer[sy], 79, NULL, 0);
            
        }
        Sleep(speed);
        
        sentance();
        HideCursor();
        *heart_count+=1;
        if(*heart_count==150){
        	color(16);
        	return 0;
		}
        
    }
}
float f(float x, float y, float z) {
    float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
    return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;

}
float h(float x, float z) {
    for (float y = 1.0f; y >= 0.0f; y -= 0.001f)
        if (f(x, y, z) <= 0.0f)
            return y;
    return 0.0f;
}

void create_list(char list[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            list[i][j]='0';
            
        }
    }
}
void print_list(const char list[][WIDTH]){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
        	if(list[i][j]=='0'){
        		printf(" ");
			}
			else{
				printf("%c",list[i][j]);
			}
        }
        printf("\n");

    }
}
void gotoxy(int x,int y)//��궨λ����
{
    COORD p;//����ṹ�����p
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ�������
    p.X=x;p.Y=y;//������Ŀ���ƶ�λ�ô��ݸ��ṹ��
    SetConsoleCursorPosition(handle,p);//�ƶ����
}
int assertnum(char list[][WIDTH],int width,int height){
    if(list[height][width]!='0')return 0;
    return 1;
}
void print_helix(char list[][WIDTH]){
    int width=0;//�����
    int height=0;//�����
    int first=0;//�ж��Ƿ��һ��ת��
    int first_1=1;//�ж��Ƿ����Ƶ�һȦ
    int right=1;//��ת��ʶ
    int down=0;//���б�ʶ
    int left=0;//��ת��ʶ
    int up=0;//���б�ʶ
    char si='*';//��������ķ��Ϻ� 
    int count=0;
    int speed=120;//������ת�ٶ� 
    int color_num=1;
    for(int i=0;i<WIDTH*HEIGHT;i++){
        if(right){
            if(first){
                width+=1;
            }
            list[height][width]=si;
            if (width<WIDTH-1){
                width+=1;
            }
            right=assertnum(list,width,height);
            first=0;
            if(right){
                down=0;
            }
            else{
                if(first_1){
                    down=1;
                    first=1;
                }else{
                    down=1;
                    first=1;
                    width-=1;
                }
            }
        }
        else if(down){
            if(first){
                height+=1;
            }
            list[height][width]=si;
            if(height<HEIGHT-1){
                height+=1;
            }
            down=assertnum(list,width,height);
            first=0;
            if(down){
                left=0;
            }
            else{
                if(first_1){
                    left=1;
                    first=1;

                }
                else{
                    left=1;
                    first=1;
                    height-=1;
                }
            }
        }
        else if(left){
            if(first){
                width-=1;
            }
            list[height][width]=si;
            if(width>0){
                width-=1;
            }
            left=assertnum(list,width,height);
            first=0;
            if(left){
                up=0;
            }
            else{
                if(first_1){
                    up=1;
                    first=1;
                    first_1=0;
                }else{
                    up=1;
                    first=1;
                    width+=1;
                }
            }
        }
        else if(up){
            if(first){
                height-=1;
            }
            list[height][width]=si;
            if(height>0){
                height-=1;
            }
            up=assertnum(list,width,height);
            first=0;
            if(up){
                right=0;
            }else{
                if(first_1){
                    right=1;
                    first=1;
                }else{
                    right=1;
                    first=1;
                    height+=1;
                }
            }
        }
	gotoxy(0,0);
	HideCursor();
	count+=1;
	
	if(count==speed){
		color(color_num);
		print_list(list);
		count%=speed;
		color_num+=1;
		color(16);
		} 
    }
}
void HideCursor() // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//�����ͽṹ�嶼��windows.h�ж��塣
}
void color(const unsigned short color1)
{        
        if(color1>=0&&color1<=15)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
        /*�������0-15�ķ�Χ��ɫ����ô��ΪĬ�ϵ���ɫ��ɫ��*/
    else
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}





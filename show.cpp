/*志尊威少*/ 

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <tchar.h>
#include <stdlib.h>

/* 此两行是展示屏的宽高，根据电脑屏幕可微调 */ 
#define WIDTH 100
#define HEIGHT 28//HEIGHT须大于等于28 
/******************************************/ 
void create_list(char [][WIDTH] );//创建一个高20，宽100的数组 
void print_list(const char [][WIDTH] );//打印出数组 
void gotoxy(int,int);//移动光标 
void print_helix(char [][WIDTH]);//螺旋矩阵
void print_helix2(char [][WIDTH],int *color_num,int speed,int*count); 
void HideCursor();//隐藏光标 
void color(const unsigned short color1);
void print_heart1(char [][WIDTH],int );//六连心
void print_heart2(char [][WIDTH],int ); //心心相印

int print_heart3(int*,int ,int);//跳动的心 
float f(float x, float y, float z);
float h(float x, float z);

void roll_screen(char [][5],int,int);//打印字（限长99），默认屏幕中间居中对齐 

void clean_screen(char list[][WIDTH]){//清屏专用函数 
	create_list(list);
    gotoxy(0,0);
  	print_list(list);
  	gotoxy(0,0);
}
/*这是大爱心底下的文字*/ 
void sentance() {
    char title[] ="============ 2020 11 18 ============";          //输入标题
    char word[] = "         心都掏出来给你看了";          //输入想说的文字
    /*注意调整格式*/
	printf("\n\t      ");                                    
    printf("%s",title);
    printf("\n\t      ");
    printf("%s", word);
}
/**************MAIN方法**********************************/ 
int main(){
	/*初始化内容忽视*/ 
	int heart_count=1;
    char list[HEIGHT][WIDTH];
    create_list(list);
    
    /*******************/ 
    
    /*颜色对应值：
　　0=黑色                8=灰色　　
  　 1=蓝色                9=淡蓝色                　　                        
　　2=绿色                10=淡绿色               　　
　　3=湖蓝色          11=淡浅绿色        　
　　4=红色                12=淡红色        　　
　　5=紫色                13=淡紫色                　　
　　6=黄色                14=淡黄色               　　
　　7=白色                15=亮白色        
　　
*/
   /*用双引号扩起要打印的字*/ 
    char word1[21][5]={"送","给","李","x","x","同","学"}; //一个字一个双引号 
    int len1=7;//此为字数值，最高不超过WIDTH值 
    int color_num=3;//相应颜色对应值 
    roll_screen(word1,len1,color_num);
  	clean_screen(list);
  	
    /*螺旋跑马灯*/ 
    print_helix(list);
    
    clean_screen(list);
    
    /*心心相印特效*/
    color_num=4;//设置颜色 
    print_heart2(list,color_num);
    clean_screen(list);
    
    /*六连心特效*/
    color_num=4;//设置颜色 
    print_heart1(list,color_num);
    clean_screen(list);
    
    /*跳动的心*/
    color_num=4;//设置颜色 
    int speed=1;//设置心跳动的速度 ，数值越小越快，且须大于零 
  	int a=print_heart3(&heart_count,color_num,speed);
  	clean_screen(list);
  	
  	
  	char word2[21][5]={"落","幕"};
	int len2=2;//内容字数 
	color_num=10;//设置颜色 
  	roll_screen(word2,len2,color_num);
  	clean_screen(list);
 
 	/*不断的更改调试，会得到你想要的结果的*/   
}
/****************以下内容可以不看****************/ 
/*不过注释也写的比较详细*/ 
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
void gotoxy(int x,int y)//光标定位函数
{
    COORD p;//定义结构体变量p
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
    p.X=x;p.Y=y;//将光标的目标移动位置传递给结构体
    SetConsoleCursorPosition(handle,p);//移动光标
}
void print_helix2(char list[][WIDTH],int *color_num,int speed,int *count){
	gotoxy(0,0);
	HideCursor();
	color(*color_num);
	print_list(list);
	(*count)%=speed;
	(*color_num)+=1;
	color(16);
}
void print_helix(char list[][WIDTH]){
	int x=0,y=0,tot=1,count=0,speed=130,color_num=1;
	list[0][0]='*';
    while(tot<WIDTH*HEIGHT){
    	while(x+1<WIDTH&&list[y][x+1]=='0'){
    		list[y][++x]='*';
    		++tot;
			count+=1;	
		if(count==speed){
			print_helix2(list,&color_num,speed,&count);
			}	
		}
		while(y+1<HEIGHT&&list[y+1][x]=='0'){
			list[++y][x]='*';
			++tot;
			count+=1;	
		if(count==speed){
			print_helix2(list,&color_num,speed,&count);
			}
			
		}
		while(x-1>=0&&list[y][x-1]=='0'){
			list[y][--x]='*';
			++tot;
			count+=1;	
		if(count==speed){
			print_helix2(list,&color_num,speed,&count);
			}
			
		}
		while(y-1>=0&&list[y-1][x]=='0'){
			list[--y][x]='*';
			++tot;
			count+=1;	
		if(count==speed){
			print_helix2(list,&color_num,speed,&count);
			}
		}	
		
	}
	 
    
}
void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//函数和结构体都在windows.h中定义。
}
void color(const unsigned short color1)
{        
        if(color1>=0&&color1<=15)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
        /*如果不在0-15的范围颜色，那么改为默认的颜色白色；*/
    else
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}




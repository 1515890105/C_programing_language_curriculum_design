#include <stdio.h>
#include <graphics.h>
#include <conio.h> 
#include <time.h>
#include <stdlib.h>
#define WIDTH 740//��
#define HEIGHT 462//��
#define GAME_HEIGHT (HEIGHT*5/6)//385 ��Ϸ�����

typedef struct 
{
	int x;
	int y;
}Location;

typedef struct node  // ��������
{
    int x, y,s;
    int  data;
    struct node* next;
}METEOR;

typedef struct wenti  //��Ŀ����
{
    int num1;//��һ���� 
    int num2;//�ڶ�����
    char c;//�Ӽ��˳�
    int result;//��� 
    struct wenti* next;
}TITLE;

typedef struct     //����������
{
    TCHAR name[20];
    int score;
}USER;


void Background()  //����
{
    IMAGE back;
    initgraph(740, 462);   //����ͼ����ʾ��ʽ
    loadimage(&back, _T("image\\background.jpg"));   //���ñ���ͼƬ
    cleardevice();
    putimage(0, 0, &back);
    setcolor(RED);
    setlinestyle(PS_SOLID, 2);
    rectangle(1, 1, 739, 461);
    line(0, 385, 740, 385);
    line(370, 385, 370, 462);
}


void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

    // ������ʼ��
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
    int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
    int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
    int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
    int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
    int dstX = 0;    //���Դ������صĽǱ�

    // ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
            int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
                    | (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
            }
        }
    }
}

void displayButton()  //����
{
    IMAGE k1, k2, k3, k4;
    loadimage(&k1, _T("image\\k1.png"));
    loadimage(&k2, _T("image\\k2.png"));
    loadimage(&k3, _T("image\\k3.png"));
    loadimage(&k4, _T("image\\k4.png"));
    drawAlpha(&k1,34, GAME_HEIGHT + 5);
    drawAlpha(&k2,118, GAME_HEIGHT + 5);
    drawAlpha(&k3,202, GAME_HEIGHT + 5);
    drawAlpha(&k4,286, GAME_HEIGHT + 5);

    outtextxy(43, GAME_HEIGHT +55, _T("��ʼ"));

    outtextxy(108, GAME_HEIGHT + 55, _T("��ͣ/����"));

    outtextxy(212, GAME_HEIGHT + 55, _T("ˢ��"));
    outtextxy(295, GAME_HEIGHT + 55, _T("�˳�"));
}




TITLE *CreatTitle()//������Ŀ
{
    int x , c, i;
    TITLE* p, * head = NULL, * r = NULL, * k;
    p = (TITLE*)malloc(sizeof(TITLE));
    srand((unsigned)time(NULL));
    for (x = 0; x < 5; x++)
    {

        p = (TITLE*)malloc(sizeof(TITLE));
        p->num1 = rand() % 10;
        p->num2 = rand() % 9+1;
        if ((p->num1) % (p->num2) != 0)
            c = rand() % 3;
        else
            c = rand() % 4;
        if (c == 0)
        {
            p->c = '+';
            p->result = p->num1 + p->num2;
        }
        else if (c == 1)
        {
            p->c = '-';
            p->result = p->num1 - p->num2;
        }
        else if (c == 2)
        {
            p->c = '*';
            p->result = p->num1 * p->num2;
        }
        else if (c == 3)
        {
            p->c = '/';
            p->result = p->num1 / p->num2;
        }
        p->next = NULL;
        if (head == NULL)
        {
            head = p;
            r = p;
        }
        else
        {
            k = head;
            for (i = 0; i < x; i++)         //��ֹ���ظ�
            {
                if (k->result == p->result)
                    break;
                else
                    k = k->next;
            }
            if (i == x)
            {
                r->next = p;
                r = p;
            }
            else
                x--;

        }
    }
    return head;
}

METEOR *Creatmeteor(TITLE *T) //��������
{
    int x=0,b,c,i,j,k;
    int a[10],s[8];
    srand((unsigned)time(NULL));
    for (j = 0; j < 8; j++)
    {
        s[j] = rand() % 8;
        for (k = 0; k < j; k++)
        {
            if (s[j] == s[k])
                j--;
        }
    }
    METEOR * p, * head = NULL, * r = NULL;
    while (x < 8)
    {
        if (T != NULL)                            //����������������
        {
            p = (METEOR*)malloc(sizeof(METEOR));
            p->data = T->result;
            p->x = (rand() % 100) - 300;
            p->y = 45 + 40 * s[x];
            p->s = (rand() % 2) + 1;
            p->next = NULL;
            a[x] = p->data;
            if (head == NULL)
            {
                head = p;
                r = p;
            }
            else
            {
                r->next = p;
                r = p;
            }
            x++;
            T = T->next;
        }
        else                                    //�����������������
        {
            b = rand() % 82;
            for (i = 0; i < x; i++)
            {
                if (a[i] == b)                  //��ֹ�ظ�
                    break;
            }
            if (i == x)
            {
                p = (METEOR*)malloc(sizeof(METEOR));
                p->data = b;
                p->x = (rand() % 100) - 300;
                p->y = 45 + 40 * s[x];
                p->s = (rand() % 2) + 1;
                p->next = NULL;
                r->next = p;
                r = p;
                a[x] = b;
                x++;
            }
           
        }      
    }
    return head;
}

int checkButton(int mouseX, int mouseY)//��鰴ť
{
    if (mouseX >= 34 && mouseX <= 84 && mouseY >= 390 && mouseY <= 440)
        return 1;
    else if (mouseX >= 118 && mouseX <= 168 && mouseY >= 390 && mouseY <= 440)
        return 2;
    else if (mouseX >= 202 && mouseX <= 252 && mouseY >= 390 && mouseY <= 440)
        return 3;
    else if (mouseX >= 286 && mouseX <= 336 && mouseY >= 390 && mouseY <= 440)
        return 4;
    else
        return -1;  //ûѡ��	
}



void MIANbody(int i,IMAGE *p,IMAGE *temp,METEOR *h,TITLE *T,USER user)//���庯��
{
    int j, a, w,jud,which;
    int mouseX;	        //���λ������X
    int mouseY;
    int flag = 0;
    METEOR *k;
    k = h;
    MOUSEMSG mmsg;	    //�����Ϣ����
    LOGFONT f;
    TCHAR s[3],s1[3],data[3],sco[3];
    LOGFONT g;
    for (j = i; ; j++)
    {
        if (T == NULL)
        {
            while (1)
            {
                BeginBatchDraw();
                getimage(temp, 0, 0, 740, 462);
                gettextstyle(&g);
                g.lfHeight = 50;
                _tcscpy_s(g.lfFaceName, _T("����"));
                g.lfQuality = ANTIALIASED_QUALITY;
                settextstyle(&g);
                setcolor(YELLOW);
                outtextxy(120, 180, _T("�����������ˢ�»��˳�"));
                EndBatchDraw();
                Sleep(10);//��ͣ����
                putimage(0, 0, temp);
                if (MouseHit())
                {
                    mmsg = GetMouseMsg();
                    switch (mmsg.uMsg)
                    {
                    case WM_LBUTTONDOWN:
                        mouseX = mmsg.x;
                        mouseY = mmsg.y;    //ȡ�����x,yֵ

                        //����ڰ�ť��
                        if (mouseX > 0 && mouseX <= WIDTH / 2 && mouseY > GAME_HEIGHT&& mouseY <= HEIGHT)
                        {
                            flag = checkButton(mouseX, mouseY);
                        }
                        if (flag == 3)
                        {
                            T = CreatTitle();
                            h = Creatmeteor(T);
                            MIANbody(0, p, temp, h, T,user);
                        }
                        else if (flag == 4)   //�˳����浵
                        {
                            FILE* fp;                             //д���ļ�
                            errno_t err;
                            err = _wfopen_s(&fp, TEXT("user.txt"), TEXT("a"));
                            fwprintf(fp, TEXT("\n%20s%10d"), user.name, user.score);
                            fclose(fp);
                            closegraph();
                            exit(1);
                        }                           
                    }
                }
            }
        }
          
        if (j > 740)
            j = 0;
        
        _stprintf_s(s,_T("%d"), T->num1);            //ʹint�Ϳ�����ȷ��ʾ����������
        _stprintf_s(s1, _T("%d"), T->num2);
        _stprintf_s(sco, _T("%d"),user.score);
       
        gettextstyle(&f);
        f.lfHeight = 20;
        _tcscpy_s(f.lfFaceName, _T("����"));
        f.lfQuality = ANTIALIASED_QUALITY;
        settextstyle(&f);
        setcolor(YELLOW);
        BeginBatchDraw();
        getimage(temp, 0, 0, 740, 462);
        for (a = 0; k != NULL; a++)
        {
            _stprintf_s(data, _T("%d"), k->data);
            if(k->x + j * k->s>=-200&& k->x + j * k->s<=600)
            drawAlpha(p, k->x + j * k->s, k->y);
            outtextxy(k->x + 165 + j * k->s, k->y + 16, data);
            k = k->next;

        }
        gettextstyle(&g);
        g.lfHeight = 30;
        _tcscpy_s(g.lfFaceName, _T("����"));
        g.lfQuality = ANTIALIASED_QUALITY;
        settextstyle(&g);
        setcolor(YELLOW);
        outtextxy(340, 20, s);
        outtextxy(383, 20, T->c);
        outtextxy(420, 20, s1);
        outtextxy(WIDTH / 2 + 260, GAME_HEIGHT + 23, sco);
        EndBatchDraw();
        Sleep(10);//��ͣ����
        putimage(0, 0, temp);
        k = h;
        if (MouseHit())
        {
            mmsg = GetMouseMsg();
            switch (mmsg.uMsg)
            {
            case WM_LBUTTONDOWN:
                mouseX = mmsg.x;
                mouseY = mmsg.y;    //ȡ�����x,yֵ

                //����ڰ�ť��
                if (mouseX > 0 && mouseX <= WIDTH / 2 && mouseY > GAME_HEIGHT&& mouseY <= HEIGHT)
                {
                    flag = checkButton(mouseX, mouseY);
                }
                //���������
                else
                {
                    while(k!=NULL)
                    {
                        if (mouseX >= (k->x  + j * k->s) && mouseX <= (k->x + 220 + j * k->s) && mouseY >= (k->y) && mouseY <= (k->y + 50))
                        {
                            if (k->data == T->result)
                            {
                                T = T->next;
                                h = h->next;
                                user.score += 1;
                            }                              
                            else
                                user.score -= 1;
                            break;
                        }
                        else
                            k = k->next;
                    }
                    k = h;
                }

                if (flag == 2)  //��ͣ
                {
                    while (1)
                    {

                        gettextstyle(&f);
                        f.lfHeight = 20;
                        _tcscpy_s(f.lfFaceName, _T("����"));
                        f.lfQuality = ANTIALIASED_QUALITY;
                        f.lfQuality = ANTIALIASED_QUALITY;
                        settextstyle(&f);
                        setcolor(YELLOW);
                        BeginBatchDraw();
                        getimage(temp, 0, 0, 740, 462);
                        for (a = 0; k != NULL; a++)
                        {
                            _stprintf_s(data, _T("%d"), k->data);
                            if (k->x + j * k->s >= -200 && k->x + j * k->s <= 600)
                                drawAlpha(p, k->x + j * k->s, k->y);
                            outtextxy(k->x + 165 + j * k->s, k->y + 16, data);
                            k = k->next;

                        }
                        gettextstyle(&g);
                        g.lfHeight = 30;
                        _tcscpy_s(g.lfFaceName, _T("����"));
                        g.lfQuality = ANTIALIASED_QUALITY;
                        settextstyle(&g);
                        setcolor(YELLOW);
                        outtextxy(340, 20, s);
                        outtextxy(383, 20, T->c);
                        outtextxy(420, 20, s1);
                        outtextxy(WIDTH / 2 + 260, GAME_HEIGHT + 23, sco);
                        EndBatchDraw();
                        Sleep(10);//��ͣ����
                        putimage(0, 0, temp);
                        k = h;

                        if (MouseHit())
                        {
                            mmsg = GetMouseMsg();
                            switch (mmsg.uMsg)
                            {
                            case WM_LBUTTONDOWN:
                                mouseX = mmsg.x;
                                mouseY = mmsg.y;    //ȡ�����x,yֵ

                                //����ڰ�ť��
                                if (mouseX > 0 && mouseX <= WIDTH / 2 && mouseY > GAME_HEIGHT&& mouseY <= HEIGHT)
                                {
                                    flag = checkButton(mouseX, mouseY);
                                }
                                if (flag == 2)
                                    MIANbody(j, p, temp, h, T, user);
                                else if (flag == 4)
                                {
                                    FILE* fp;                             //д���ļ�
                                    errno_t err;
                                    err = _wfopen_s(&fp, TEXT("user.txt"), TEXT("a"));
                                    fwprintf(fp, TEXT("\n%20s%10d"), user.name, user.score);
                                    fclose(fp);
                                    closegraph();
                                    exit(1);
                                }
                            }
                        }
                    }
                }
                else if (flag == 3)            //�������ǣ����ڽ���ԭ���ڱ�������ʵ��ˢ����Ŀ
                {

                    T = CreatTitle();
                    h = Creatmeteor(T);
                    MIANbody(0, p, temp, h, T,user);
                }
                else if (flag == 4)         //�˳����浵
                {
                    
                    FILE* fp;                             //д���ļ�
                    errno_t err;
                    err = _wfopen_s(&fp, TEXT("user.txt"), TEXT("a"));             
                    fwprintf(fp, TEXT("\n%20s%10d"), user.name, user.score);
                    fclose(fp);
                    closegraph();
                    exit(1);
                }
                
            }
        }
    }
}

void start(USER user)//��ʼ����
{
    IMAGE  p,temp;
    int x = 0;
    METEOR *h;
    TITLE *T;
    loadimage(&p, _T("image\\meteor.png"));
    T=CreatTitle();
    h = Creatmeteor(T);
    MIANbody(0, &p, &temp, h,T,user);
}





void Mouse(USER user)//������
{
    int mouseX;	        //���λ������X
    int mouseY;
    int flag=0;
    Location ml = { 0,0 };
    MOUSEMSG mmsg;	    //�����Ϣ����
    while (1) 
    {

        //���������Ϣ
        if (MouseHit()) 
        {
            mmsg = GetMouseMsg();
            switch (mmsg.uMsg) 
            {
            case WM_LBUTTONDOWN:
                mouseX = mmsg.x;
                mouseY = mmsg.y;    //ȡ�����x,yֵ

                //����ڰ�ť��
                if (mouseX > 0 && mouseX <= WIDTH / 2 && mouseY > GAME_HEIGHT&& mouseY <= HEIGHT)
                {
                    flag = checkButton(mouseX, mouseY);
                } 
                if (flag == 1)
                   start(user);
                else if (flag == 4)
                {
                    closegraph();
                    exit(1);
                }
            }
        }
    }
}

void main()  //������
{
    Background(); 
    displayButton();
    USER user;
    InputBox(user.name, 20, _T("�������û�����"), _T("��������"));
    outtextxy(WIDTH / 2 + 30, GAME_HEIGHT + 30, _T("Name: "));
    outtextxy(WIDTH / 2 + 80, GAME_HEIGHT + 30, user.name);
    outtextxy(WIDTH / 2 + 200, GAME_HEIGHT + 30, _T("Score: "));
    user.score = 0;
    Mouse(user);
}

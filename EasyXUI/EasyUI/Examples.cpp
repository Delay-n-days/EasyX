#include <graphics.h>
#include <conio.h>
#include <functional>
#include "EasyUI.h"

// !!!!!���д��� * �Ķ��Ǳ������
// һ����˵������Ļ��Ƶ�Ԫ����Ӧ���Լ�λ�ö��Ǳ���
// 
// ���ڰ����еĻص������ķ���
// �Ȱ���ͷ�ļ� functional
// ͨ��ʹ�� std::bind() ����ʵ��
// ������������
// bind(����ָ��(&[����]::[������]), ��ָ��, ����λ��)
// ����λ��һ���� std::placeholders::_x ����ʾ��x ��һ�����֣���ʾ�ǵڼ���������һ��ᰴ��˳��д��ȥ
// ʾ������һЩ�ط�ʹ�������ַ�ʽ��������Ϊ�ο�
// 
// ���� UI �����֣������� UI ��Ψһ��ʶ���������ظ�

// ����һ����Ϣ����
void Message()
{
	MessageBox(nullptr, L"��ť���", L"��Ϣ", MB_OK);
}
// ���һ���ַ���
void MessageStr(std::wstring message)
{
	MessageBox(nullptr, message.c_str(), L"��Ϣ", MB_OK);
}
// ���һ��������
void MessageFloat(float value)
{
	wchar_t str[20];
	swprintf_s(str, L"%f", value);
	MessageBox(nullptr, str, L"��Ϣ", MB_OK);
}

// ����һ����̬UI��ʾ��
void StaticUI()
{
	CUIImage * image = new CUIImage();		// ����һ�� UI ͼ
	IMAGE *maskImage = new IMAGE;			// ����ͼ
	loadimage(maskImage, L"mask.png");		// ��������ͼ
	image->SetDrawPos({ 0, 0 });			// *���û���λ��
	image->SetImage(L"test.jpg");			// ����һ��ͼƬ��Ҳ����ѡ���Լ�����ͼƬ������ָ��
	image->SetMask(maskImage, true);		// ����һ������ͼ������ԭͼ���п�ͼ��(�������Ϊ false���򲻿�)
	image->CompareImageSize();				// *����ͼƬ�Ĵ�С��ͼƬ֧�����ţ����ǲ��Ƽ�ʹ��(ͼƬ������ʧ����)
	image->SetChildCell(new CText({ 270, 130 }));		// ����һ�����ӿؼ�������ؼ��������ʱ��ʹ��

	CStaticUI * staticUI = new CStaticUI();
	staticUI->DrawCell(image)				// *���þ�̬UI�Ļ��Ƶ�Ԫ
		->SetLayer(-1);						// ����UI�㼶��ʹ���ڵײ���ʾ
	// ��ӵ�UI����
	CUIManager::GetInstance()->AddUIElement(L"����ͼ", staticUI);
}

// ����һ����ť��ʾ��
void Button()
{
	CButton *button = new CButton;
	button->SetUIPos({ 50, 50 });			// *���ð�ť��λ��
	button->Normal(new CEllipse({ 50, 50 }, 100, 40, RED, BLUE))	// *������ͨ״̬�µ���ʽ
		->MouseIn(new CEllipse({ 50, 50 }, 100, 40, RED, RED))		// *��������������ʽ
		->Down(new CEllipse({ 50, 50 }, 100, 40, RED, RGB(100, 100, 100)))	// *������갴�º����ʽ
		->Trigger(new CMaskTrigger(100, 40))						// *������Ӧ������ʽ
		->CallBack(Message);				// ���ð�ť���µĻص�����

	// ��������ʹ�õ�����Բ�����Բ�������ͼ�ķ�ʽ��Ӧ�¼�
	// ����ͼ���¼���Ӧ�����ؼ��ģ��ǳ���׼
	// ���ﴴ����һ����Բ����
	// ͼʡ�°ѻ�ȡ���ִ���������ʹ�����Բ�����Լ���������дһ���ˡ���������
	// ���Կ������ȽϿֲ�
	((CMaskTrigger*)(button->GetTrigger()))->CreatMask((CSimpleShape*)button->GetNormal());

	// ��������ť��������ӿؼ�(�ð�ť�����֣����߱�Ķ���)
	button->GetNormal()													// ��ȡ��ͨ״̬�µĻ��Ƶ�Ԫ
		->SetChildCell(new CRect({ 80, 60 }, 40, 20, YELLOW, BLACK))	// ����һ�����λ���
		->SetChildCell(new CText({ 83, 63 }, L"��ť"));					// ��������ʹ������������
	button->GetDown()
		->SetChildCell(new CText({ 83, 63 }, L"��ť"));

	// ���Ѱ�ť���� UI �������в�����Ӧ���󹦸��
	// ����UI����UI��������ά��������
	// �൱��ʹ������� UI��Ȼ�󽻸� UI ������
	// �������赣���ڴ�й©
	CUIManager::GetInstance()->AddUIElement(L"��ť", button);
}

// ����һ��������ʾ��
void InputTextBox()
{
	CInputTextBox * inputbox = new CInputTextBox();
	// ��䳤�Ĺ��֣����Ե�ָ�뿼������=-=����֮���ǻ�ȡ���ڴ������� UI ʱ��ӵĺ���(�ı�)
	CText * text = (CText *)((CStaticUI*)(CUIManager::GetInstance()->GetUIElement(L"����ͼ")))->GetDrawCell()->GetChileCell();

	inputbox->SetUIPos({ 50, 120 });	// *���������λ��
	inputbox->XSpace(7)->YSpace(8)		// ����ˮƽ�ʹ�ֱ���
		->BackBox(new CRoundRect({ 0, 0 }, 200, 35, 9, 9, RED, BLUE))	// *���һ��������
		->Trigger(new CRectTrigger(200, 35))		// *����һ����Ӧ��
		->CursorColor(YELLOW)			// ���ù�����ɫ
		->OnValueChange(std::bind(&CText::SetText, text, std::placeholders::_1))	// ���õ������ֵ�ı��ʱ����õĺ���
		->OnExit(MessageStr);			// ���õ��ı����뿪�����ʱ����õĺ���

	// ��ӵ�UI����
	CUIManager::GetInstance()->AddUIElement(L"�����", inputbox);
}

// ����һ����������ʾ��
void PreBar()
{
	CPreBar * preBar = new CPreBar();

	preBar->SetUIPos({ 50, 190 });					// *���� UI λ��
	preBar->Background(new CRoundRect({ 0, 0 }, 380, 20, 6, 6, YELLOW, RGB(190, 190, 190)))	// *���ñ�����
		->Mask(new CRoundRect({ 0, 0 }, 200, 20, 3, 3, GREEN, GREEN))						// *�������ֿ�
		->Padding({ 3, 3 });						// �����ڱ߾�

	preBar->GetBackground()->LineThickness(3);		// �����ⲿ���ϸ

	// ��ӵ�UI����
	CUIManager::GetInstance()->AddUIElement(L"������", preBar);
}

// ����һ���϶�����ʾ��
void DragBar()
{
	CDragBar *bar = new CDragBar();

	CPreBar * preBar = (CPreBar *)CUIManager::GetInstance()->GetUIElement(L"������");	// �ӹ�������ȡ��������

	bar->SetUIPos({ 50, 250 });						// *����UI��λ��
	bar->Block(new CCircle({ 0, 0 }, 9, RED, RGB(150, 150, 150)))		// *�����϶���
		->BlockTrigger(new CCircleTrigger(9))		// *�����϶���Ĵ�����
		->BlockCenter({ 0, 0 })						// *�����϶�������ģ�����Բ������ģ���Ϊ���Ǵ����Ļ��Ƶģ����ͼ�񶼴����Ͻǿ�ʼ����
		->Line(new CRoundRect({ 0, 0 }, 250, 6, 3, 3, RED, BLUE))		// *���ñ�����
		->LineTrigger(new CRectTrigger(250, 6))		// *���ñ������Ĵ�����
		->LineSize({ 250, 6 })						// *���ñ������ĳߴ�
		->OnValueChange(std::bind(&CPreBar::SetValue, preBar, std::placeholders::_1))		// ������ֵ�ı��ʱ��Ļص�
		->OnExit(MessageFloat);						// �����˳���ʱ��Ļص�����
	
	// ��ӵ�UI����
	CUIManager::GetInstance()->AddUIElement(L"�϶���", bar);
}

// ����һ��ѡ����ʾ��
void CheckBox()
{
	CGUIElement * element = CUIManager::GetInstance()->GetUIElement(L"����ͼ");
	CCheckBox * checkBox = new CCheckBox;

	checkBox->SetUIPos({ 50, 300 });		// *���� UI ��λ��
	checkBox->BackBox(new CCircle({ 50, 300 }, 8, RGB(100, 100, 100), RGB(200, 200, 200)))		// *���ñ�������
		->Checked(new CCircle({ 50, 300 }, 6, RGB(40, 40, 40), RGB(40, 40, 40)))				// *����ѡ�к���ʾ��
		->Trigger(new CCircleTrigger(8))	// *������Ӧ��
		->OnValueChange(std::bind(&CGUIElement::SetUIActive, element, std::placeholders::_1))	// ���ûص�����
		->SetValue(true);					// ����״̬Ϊѡ��

	// ��ӵ� UI ����
	CUIManager::GetInstance()->AddUIElement(L"ѡ���", checkBox);
}


int main(void)
{
	unsigned int curTime, preTime;
	curTime = preTime = GetTickCount();
	initgraph(640, 640);
	setbkcolor(RGB(80, 80, 80));
	setbkmode(TRANSPARENT);
	BeginBatchDraw();

	// ����ʾ��
	StaticUI();
	Button();
	InputTextBox();
	PreBar();
	DragBar();
	CheckBox();

	// ���뽨��һ��ѭ������Ӧ UI �¼�Ŷ
	while (true)
	{
		curTime = GetTickCount();
		if (curTime - preTime >= 16)
		{
			cleardevice();
			CUIManager::GetInstance()->Draw();			// ����
			CUIManager::GetInstance()->ProcessEvent();	// ��Ӧ�¼�
			FlushBatchDraw();
			preTime = curTime;
		}
		else
			Sleep(1);
	}

	_getch();
	delete CUIManager::GetInstance();	// �������ͷſռ�
	EndBatchDraw();
	closegraph();
	return 0;
}

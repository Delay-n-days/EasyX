#pragma once
#include <graphics.h>
#include <Windows.h>
#include <string>
#include <map>
#include <functional>

#pragma region ö��

// ����״��ö��
enum ESimpleShape
{
	RECTANGLE = 0,	// ����
	ROUNDRECT = 1,	// Բ�Ǿ���
	CIRCLE = 2,		// Բ��
	ELLIPSE = 3,	// ��Բ
};
// �ؼ�����ö��
enum EUIElement
{
	UNKNOW = 0,		// δ֪
	STATIC = 1,		// ��̬����޷���Ӧ�¼���ֻ�ܻ���
	BUTTON = 2,		// ��ť
	DRAGBAR = 3,	// �϶���
	INPUTBOX = 4,	// �����
	PREBAR = 5,		// ������
	CHECKBOX = 6,	// ѡ���

	LASTOFENUM = 0xFFFF	// ö�ٸ�ֵ�����ֵ���벻Ҫ�������ֵ
};
// �¼�����ö��
enum EUIEvent
{
	MOUSE_MOVE = 0,		// ����ƶ�
	MOUSE_DOWN = 1,		// ��갴��
	MOUSE_UP = 2,		// ���̧��
	KEYBOARD_INPUT = 3	// ��������
};

#pragma endregion ö��


#pragma region ���Ƶ�Ԫ

// ���Ƶ�Ԫ
// ���пɻ��ƶ���Ļ���(������)
// �̳д�����������ʵ�� Draw ����
// ע�⣺�������չ�������ͣ����Ƶ�ģʽ��Ҫ���� m_DrawPos�����������һ������Ϊ 20 �ľ���
// Ӧ�ô� m_DrawPos Ϊ���Ͻǿ�ʼ�����Ƴ���Ϊ20�ľ���
class CDrawCell
{
public:
	CDrawCell() { m_ChildCell = nullptr; }
	virtual ~CDrawCell() {
		if (m_ChildCell)
			delete m_ChildCell;
	}

	// ���ƺ���
	virtual void Draw() = 0;

	// ���û��Ƶ�λ��
	void SetDrawPos(POINT pos) { m_DrawPos = pos; }
	// ��ȡ���Ƶ�λ��
	POINT GetDrawPos() { return m_DrawPos; }
	// ���ú��ӻ�����
	CDrawCell * SetChildCell(CDrawCell * cell) { m_ChildCell = cell; return m_ChildCell; }
	// ��ȡ���ӻ�����
	CDrawCell * GetChileCell() { return m_ChildCell; }

protected:
	POINT m_DrawPos;				// ���Ƶ�λ��
	CDrawCell *		m_ChildCell;	// ���ӻ�����
private:
};

// �򵥵Ļ���ͼ�Σ�����Σ�Բ�Ǿ��Σ���Բ(Բ)��
// ����ඨ��������ͼ�εĹ�������
// Ŀ����Ϊ�˼��ٴ����ɢ
class CSimpleShape :public CDrawCell
{
public:
	CSimpleShape()
	{
		m_FillStyle.style = BS_SOLID;
		m_FillStyle.hatch = NULL;
		m_FillStyle.ppattern = 0;
		m_LineStyle.style = PS_SOLID;
		m_LineStyle.thickness = 1;
		m_LineStyle.puserstyle = nullptr;
		m_LineStyle.userstylecount = 0;
		m_bFill = true;
	}
	virtual ~CSimpleShape() {}

	CSimpleShape * Fill(bool Fill) { m_bFill = Fill; return this; }
	bool GetFill() { return m_bFill; }
	CSimpleShape * LineColor(COLORREF color) { m_LineColor = color; return this; }
	COLORREF GetLineColor() { return m_LineColor; }
	CSimpleShape * FillColor(COLORREF color) { m_FillColor = color; return this; }
	COLORREF GetFillColor() { return m_FillColor; }
	CSimpleShape * LineStyle(const LINESTYLE & style) { m_LineStyle = style; return this; }
	CSimpleShape * LineStyle(DWORD style) { m_LineStyle.style = style; return this; }
	CSimpleShape * LineThickness(int thickness) { m_LineStyle.thickness = thickness; return this; }
	LINESTYLE * GetLineStyle() { return &m_LineStyle; }
	CSimpleShape * FillStyle(const FILLSTYLE & style) { m_FillStyle = style; return this; }
	CSimpleShape * FillStyle(int style) { m_FillStyle.style = style; return this; }
	FILLSTYLE * GetFillStyle() { return &m_FillStyle; }

protected:
	bool		m_bFill;		// �Ƿ����
	COLORREF	m_LineColor;	// ������ɫ
	COLORREF	m_FillColor;	// �����ɫ
	LINESTYLE	m_LineStyle;	// ��������
	FILLSTYLE	m_FillStyle;	// �������

	void UseAttribute()			// Ӧ������(Ӧ����ɫ���������)
	{
		setlinecolor(m_LineColor);
		setfillcolor(m_FillColor);
		setlinestyle(&m_LineStyle);
		setfillstyle(&m_FillStyle);
	}
private:

};

// ӵ�д�С����
// ͬ����Ϊ�˼��ٴ����ɢ
class CHaveSize
{
public:
	CHaveSize() {}
	virtual ~CHaveSize() {}

	void SetWidth(int width) { m_iWidth = width; }
	int GetWidth() { return m_iWidth; }
	void SetHeight(int height) { m_iHeight = height; }
	int GetHeight() { return m_iHeight; }
protected:
	int			m_iWidth;		// ���
	int			m_iHeight;		// �߶�
private:
};

// ��Բ��
class CCircle :
	public CSimpleShape
{
public:
	CCircle(POINT pos = { 0, 0 }, int radius = 0, COLORREF lineColor = WHITE, COLORREF fillColor = WHITE);
	~CCircle();

	void SetRadius(int round) { m_iRadius = round; }
	int GetRadius() { return m_iRadius; }

	void Draw();
protected:

private:
	int m_iRadius;
};

// ������Բ��
class CEllipse :
	public CSimpleShape,
	public CHaveSize
{
public:
	CEllipse(POINT pos = { 0, 0 }, int width = 0, int height = 0, COLORREF lineColor = WHITE, COLORREF fillColor = WHITE);
	~CEllipse();


	void Draw();

protected:

private:
};

// ����һ������
class CRect :
	public CSimpleShape,
	public CHaveSize
{
public:
	CRect(POINT pos = { 0, 0 }, int width = 0, int height = 0, COLORREF lineColor = WHITE, COLORREF fillColor = WHITE);
	~CRect();


	void Draw();

protected:


private:
};

// ����Բ�Ǿ��ε���
class CRoundRect :
	public CSimpleShape,
	public CHaveSize
{
public:
	CRoundRect(POINT pos = { 0, 0 }, int width = 0, int height = 0,
		int roundWidth = 0, int roundHeight = 0, COLORREF lineColor = WHITE, COLORREF fillColor = WHITE);
	~CRoundRect();

	void SetRoundWidth(int width) { m_iRoundWidth = width; }
	int GetRoundWidth() { return m_iRoundWidth; }
	void SetRoundHeight(int height) { m_iRoundHeight = height; }
	int GetRoundHeight() { return m_iRoundHeight; }

	void Draw();

protected:

private:
	int			m_iRoundWidth;	// Բ�ǿ��
	int			m_iRoundHeight;	// Բ�Ǹ߶�

};

// �ı������
class CText :
	public CDrawCell
{
public:
	CText(POINT pos = { 0, 0 }, std::wstring text = L"") { m_strText = text; m_DrawPos = pos; }
	~CText();
	void SetText(std::wstring text) { m_strText = text; }
	std::wstring & GetText() { return m_strText; }

	void Draw();

protected:

private:
	std::wstring m_strText;

};

// ͼƬ�����࣬Ϊ�������� easyx �� Image ��
class CUIImage :
	public CDrawCell,
	public CHaveSize
{
public:
	CUIImage(IMAGE * image = nullptr, IMAGE * mask = nullptr);
	~CUIImage();

	void CompareImageSize() { if (!m_pImage) return; m_iHeight = m_pImage->getheight(); m_iWidth = m_pImage->getwidth(); }
	void SetImage(IMAGE * image, bool destroyOld = true) { if (m_pImage && destroyOld) delete m_pImage; m_pImage = image; }
	void SetImage(LPCTSTR Address, bool destroyOld = true) { if (m_pImage && destroyOld) delete m_pImage; m_pImage = new IMAGE; loadimage(m_pImage, Address); }
	IMAGE * GetImage() { return m_pImage; }
	void SetMask(IMAGE * mask, bool apllyImage, bool destroyOld = true);
	IMAGE * GetMask() { return m_pMask; }

	// ���������������һ���򵥼���ͼ�ε��������������ڲü�ͼƬ
	// �������������Ͻǿ�ʼ�����ջ��Ƶ�Ԫ�Ļ���ģʽ�����û���ͼƬ����״
	// filp���Ƿ�ʹ�÷�����ã�
	// ���磺��ѡ-��ͼƬ�пٳ�������Բ������
	// 		����-ֻ����Բ�������ڵ�ͼƬ
	void CreatMask(CSimpleShape * shape, bool flip = false);

	void Draw();

protected:

private:
	IMAGE * m_pImage;		// ���Ƶ�ͼƬ
	IMAGE * m_pMask;		// ����ͼ

};

#pragma endregion ���Ƶ�Ԫ


#pragma region ������

// �������࣬���д������Ļ���
class CTrigger
{
public:
	CTrigger();
	virtual ~CTrigger();

	virtual bool PtInTrigger(POINT point) = 0;
	void SetTriggerPos(POINT pos) { m_TriggerPos = pos; }
	POINT GetTriggerPos() { return m_TriggerPos; }

protected:
	POINT	m_TriggerPos;	// ��������λ��

private:
};

// Բ�δ�����
class CCircleTrigger :
	public CTrigger
{
public:
	CCircleTrigger(int Radius = 0) { m_iRadius = Radius; }
	~CCircleTrigger();
	bool PtInTrigger(POINT point);
	void SetRadius(int radius) { m_iRadius = radius; }
	int GetRadius() { return m_iRadius; }
protected:

private:
	int m_iRadius;	// �뾶
};

// ʹ������ͼ��ȷ���Ƿ���Ӧ�¼�����
// ʹ�úڰ�ͼƬ����ɫΪ��Ӧ����ɫΪ����Ӧ
class CMaskTrigger :
	public CTrigger
{
public:
	CMaskTrigger(int width, int height, IMAGE * mask = nullptr) { m_iWidth = width; m_iHeight = height; m_pMask = mask; }
	~CMaskTrigger();

	void SetMask(IMAGE * mask) { m_pMask = mask; }
	IMAGE * GetMask() { return m_pMask; }
	void SetWidth(int width) { m_iWidth = width; }
	int GetWidth() { return m_iWidth; }
	void SetHeight(int height) { m_iHeight = height; }
	int GetHeight() { return m_iHeight; }

	// ���������������һ���򵥼���ͼ�ε����������������ж��Ƿ񴥷��¼�
	// filp���Ƿ�ʹ�÷�����ã�
	// ���磺��ѡ-�Ӿ����п۳�������Ӧ��Բ������
	// 		����-��ӦԲ�������ڵ��¼�
	void CreatMask(CSimpleShape * shape, bool flip = false);

	bool PtInTrigger(POINT point);

protected:

private:
	IMAGE *		m_pMask;	// ����ͼ
	int			m_iWidth;	// ���
	int			m_iHeight;	// �߶�
	RECT m_rectRc;	// ����
};

// ���δ�����
class CRectTrigger :
	public CTrigger
{
public:
	CRectTrigger(int width = 0, int height = 0) { m_iWidth = width; m_iHeight = height; }
	~CRectTrigger();

	void SetWidth(int width) { m_iWidth = width; }
	int GetWidth() { return m_iWidth; }
	void SetHeight(int height) { m_iHeight = height; }
	int GetHeight() { return m_iHeight; }

	bool PtInTrigger(POINT point);

protected:

private:
	int m_iWidth;	// ���
	int m_iHeight;	// �߶�
	RECT m_rectRc;	// ����
};

#pragma endregion ������


#pragma region �ؼ�

// UI Ԫ���࣬һ�� UI �ؼ��Ļ��࣬���������� UI �Ļ�������
// ���е� UI �������Ľṹ�洢
class CGUIElement
{
public:
	CGUIElement(EUIElement type);
	virtual ~CGUIElement();

	EUIElement GetUIType() { return m_eUIType; }
	void SetUIPos(POINT pos) { m_UIPos = pos; }
	POINT GetUIPos() { return m_UIPos; }
	void SetUIActive(bool active) { m_bActive = active; }
	bool GetUIActive() { return m_bActive; }
	void SetUIEventable(bool eventable) { m_bEventable = eventable; }
	bool GetUIEventable() { return m_bEventable; }
	void SetLayer(int layer) { m_iLayer = layer; }
	int GetLayer() { return m_iLayer; }

	virtual void Draw() = 0;
	virtual void OnEvent(EUIEvent event, LPARAM Param) = 0;

protected:

	EUIElement		m_eUIType;		// UI ����
	POINT			m_UIPos;		// UI ��λ��
	bool			m_bActive;		// UI �Ƿ�����
	bool			m_bEventable;	// UI �Ƿ������Ӧ�¼�
	int				m_iLayer;		// UI �Ĳ㼶
private:
};

// ��ť�ؼ�
class CButton :
	public CGUIElement
{
public:
	CButton();
	~CButton();

	void Draw();
	void OnEvent(EUIEvent event, LPARAM Param);
	CDrawCell * GetNormal() { return m_pNormal; }
	CButton * Normal(CDrawCell * style) { m_pNormal = style; return this; }
	CDrawCell * GetDown() { return m_pDown; }
	CButton * Down(CDrawCell * style) { m_pDown = style; return this; }
	CDrawCell * GetMouseIn() { return m_pMouseIn; }
	CButton * MouseIn(CDrawCell * style) { m_pMouseIn = style; return this; }
	CTrigger * GetTrigger() { return m_pTrigger; }
	CButton * Trigger(CTrigger * trigger) { m_pTrigger = trigger; return this; }
	CButton * CallBack(std::function<void(void)> callback) { m_pCallBack = callback; return this; }

protected:

private:
	bool		m_bPressed;	// ������
	bool		m_bMouseIn;	// ����ڿؼ���
	CDrawCell * m_pNormal;	// ��ͨ����µİ�ť���
	CDrawCell * m_pDown;	// ����״̬�µİ�ť���
	CDrawCell * m_pMouseIn;	// �����������µİ�ť���
	CTrigger *	m_pTrigger;	// ������
	std::function<void(void)>	m_pCallBack;	// �ص�����
};

// ѡ���ؼ�
class CCheckBox :
	public CGUIElement
{
public:
	CCheckBox();
	~CCheckBox();

	void Draw();
	void OnEvent(EUIEvent event, LPARAM Param);

	CCheckBox * BackBox(CDrawCell * cell) { m_pBackBox = cell; return this; }
	CDrawCell * GetBackBox() { return m_pBackBox; }
	CCheckBox * Checked(CDrawCell * cell) { m_pChecked = cell; return this; }
	CDrawCell * GetChecked() { return m_pChecked; }
	CCheckBox * Trigger(CTrigger * trigger) { m_pTrigger = trigger; return this; }
	CTrigger * GetTrigger() { return m_pTrigger; }
	CCheckBox *	OnValueChange(std::function<void(bool)> callBack) { m_pCallBack = callBack; return this; }

	void SetValue(bool value) { m_bSelected = value; if (m_pCallBack) m_pCallBack(value); }
	bool GetValue() { return m_bSelected; }

protected:
private:
	CDrawCell *		m_pBackBox;		// ѡ��򱳾�
	CDrawCell *		m_pChecked;		// ѡ����
	CTrigger *		m_pTrigger;		// ������
	bool			m_bSelected;	// �Ƿ�ѡ��
	std::function<void(bool)>	m_pCallBack;	// �ص�����
};

// �϶����ؼ�
class CDragBar :
	public CGUIElement
{
public:
	CDragBar();
	~CDragBar();

	void Draw();
	void OnEvent(EUIEvent event, LPARAM Param);

	CDragBar * BlockCenter(POINT pos) { m_BlockCenter = pos; return this; }
	CDragBar * LineSize(POINT size) { m_LineSize = size; return this; }
	CDragBar * Block(CDrawCell * block) { m_pDragBlock = block; return this; }
	CDragBar * Line(CDrawCell * line) { m_pDragLine = line; return this; }
	CDragBar * BlockTrigger(CTrigger * trigger) { m_pBlockTrigger = trigger; return this; }
	CDragBar * LineTrigger(CTrigger * trigger) { m_pLineTrigger = trigger; return this; }
	CDragBar * OnValueChange(std::function<void(float)> callBack) { m_pCallBack = callBack; return this; }
	CDragBar * OnExit(std::function<void(float)> callBack) { m_pCallBackExit = callBack; return this; }

	CDrawCell * GetBlock() { return m_pDragBlock; }
	CDrawCell * GetLine() { return m_pDragLine; }

	void SetValue(float value) { m_fValue = value; }
	float GetValue() { return m_fValue; }

protected:
private:
	std::function<void(float)>	m_pCallBack;	// �ص�����
	std::function<void(float)>	m_pCallBackExit;	// �ص�����

	CDrawCell *		m_pDragBlock;		// �϶���
	CDrawCell *		m_pDragLine;		// �϶����������
	CTrigger *		m_pBlockTrigger;	// �϶���Ĵ�����
	CTrigger *		m_pLineTrigger;		// �ߵĴ�����
	float			m_fValue;			// �϶�����ֵ
	POINT			m_LineSize;			// �϶����Ĵ�С
	POINT			m_BlockCenter;		// �϶�������ĵ�
	bool			m_bPressed;			// �����
};

// �����ؼ�
class CInputTextBox :
	public CGUIElement
{
public:
	CInputTextBox();
	~CInputTextBox();

	void Draw();
	void OnEvent(EUIEvent event, LPARAM Param);

	std::wstring GetText();
	void SetText(std::wstring text);

	void SetWidth(int width) { m_iWidth = width; }
	int GetWidth() { return m_iWidth; }
	void SetHeight(int height) { m_iHeight = height; }
	int GetHeight() { return m_iHeight; }

	CInputTextBox * CursorColor(COLORREF color) { m_pCursor->LineColor(color); m_pCursor->FillColor(color); return this; }
	CInputTextBox * XSpace(int space) { m_iXSpace = space; return this; }
	CInputTextBox * YSpace(int space) { m_iYSpace = space; return this; }
	CInputTextBox * BackBox(CRect * rect);
	CInputTextBox * BackBox(CRoundRect * roundRc);
	CInputTextBox * Trigger(CTrigger * trigger) { if (m_pTrigger) delete m_pTrigger; m_pTrigger = trigger; return this; }
	CInputTextBox * OnValueChange(std::function<void(std::wstring)> callBack) { m_pCallBack = callBack; return this; }
	CInputTextBox * OnExit(std::function<void(std::wstring)> callBack) { m_pCallBackExit = callBack; return this; }
	CDrawCell * GetBackBox() { return m_pBackBox; }

protected:
private:
	int				m_iWidth;		// ���
	int				m_iHeight;		// �߶�
	int				m_iXSpace;		// ˮƽ�ո�
	int				m_iYSpace;		// ��ֱ�ո�
	CDrawCell *		m_pBackBox;		// ������
	CRect *			m_pCursor;		// ���
	CText *			m_strText;		// �ı�
	CTrigger *		m_pTrigger;		// ������

	std::function<void(std::wstring)>	m_pCallBack;		// �ص�����
	std::function<void(std::wstring)>	m_pCallBackExit;	// �ص�����
	int				m_lastChangeTime;	// �ϴι���л�״̬��ʱ��
	bool			m_bPressed;			// �Ƿ�ѡ��
	bool			m_bShowCursor;		// �Ƿ���ʾ���

};

// �������ؼ�
class CPreBar :
	public CGUIElement
{
public:
	CPreBar();
	~CPreBar();

	void Draw();
	void OnEvent(EUIEvent event, LPARAM Param) {}

	void SetValue(float value) { m_fValue = value; if (m_fValue >= 1) m_fValue = 1; if (m_fValue <= 0)m_fValue = 0; }	// ���ý�������ֵ
	float GetValue() { return m_fValue; }

	CPreBar * Background(CRoundRect * back) { m_pBackground = back; return this; }
	CPreBar * Background(CRect * back) { m_pBackground = back; return this; }
	CSimpleShape * GetBackground() { return m_pBackground; }
	CPreBar * Mask(CRoundRect * mask) { m_pMask = mask; return this; }
	CPreBar * Mask(CRect * mask) { m_pMask = mask; return this; }
	CPreBar * Padding(POINT padding) { m_Padding = padding; return this; }
	POINT GetPadding() { return m_Padding; }
	CSimpleShape * GetMask() { return m_pMask; }

protected:
private:
	CSimpleShape *	m_pBackground;	// ������
	CSimpleShape *	m_pMask;		// ������
	float			m_fValue;		// ��������ֵ
	POINT			m_Padding;		// �ڱ߾�
};

// ��̬ UI �ؼ�
class CStaticUI :
	public CGUIElement
{
public:
	CStaticUI();
	~CStaticUI();


	void Draw();
	void OnEvent(EUIEvent event, LPARAM Param) {}
	CStaticUI * DrawCell(CDrawCell * drawcell) { m_pDrawCell = drawcell; return this; }
	CDrawCell * GetDrawCell() { return m_pDrawCell; }

protected:
private:
	CDrawCell *		m_pDrawCell;		// ���Ƶ�Ԫ

};

#pragma endregion �ؼ�

// UI ������
class CUIManager
{

	static CUIManager * Instance;
	CUIManager();
public:
	~CUIManager();
	static CUIManager * GetInstance() { if (!Instance) Instance = new CUIManager; return Instance; }

	void Draw();			// ����
	void ProcessEvent();	// �����¼�
	void AddUIElement(std::wstring name, CGUIElement * element) {
		m_allUIElement[name] = element;
	}	  // ��� UI �ؼ�
	CGUIElement * GetUIElement(std::wstring name);	// ��ȡ UI �ؼ�

protected:

private:
	std::map<std::wstring, CGUIElement*>			m_allUIElement;	// �������е� UI
	std::multimap<int, CGUIElement *>	m_mapDrawSort;				// ���ڻ�������
};

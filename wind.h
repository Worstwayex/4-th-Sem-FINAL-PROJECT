#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/valgen.h>
#include <wx/statusbr.h>

#define e 15
#define BLACK -1
#define WHITE 1
#define FREE 0
#define rad 12

struct Step{			//��� ��������� ��� ������ ��������� ����� ��� ����� �� ������������ �����
	int green;		//��� ������� ��������� ���� ����� ������������ � �������
	int who;		//����� ������, �� ������� ���� ����������� �������
	int dead[4];		//��� ������� ��� ����� ����
};

class check20{			//��������� ��� �������� ��������� �����
public:
	int a[20];  		//���� a[i] = 1, �� �� i-�� ������ ����� ����� �����, ���� -1 - ������, 0 - ������
	wxPoint pos[20];	//���������� ������ � ���������� ��� ���� ����
	Step go[2];		//��� �������� ���� ��������� ����� ��� ����� �� �����
	int turn;		//��� �������� ���������� � ���, ��� � ������ ������ �����
	int my_color;		//���� ����� ���������� ������������� ��� ���� �� ����
	int ready;		//���������� � ���������� ������������ ��� ���� �� ����

	check20();
	int getNum(wxPoint);	//������ ����� ������ �� ���������� �����
	void stepClear();	//������� � ���� ������� ������, ���������� ��������� ���� ��� ����� ���� �����
	void stepPrep(int);	//�������������� ���� ��� ����� �� ������������ �����, ���������� ������ ���� � �������
	bool ingreen(int);	//���������, �������� �� ���� � �������
	bool kill_opp();	//���������, ���� �� ����������� ������, ���� ����, �� ���� ����� ������ ������
	int win_check();	//���������, ���������� �� ���������� � ������
	void act(int);		//������������ ��������� ���



	class Iter{		//��� ��� ���� ������������ �� ���� ������ �� 20 ������, � ���������� ��� ������
		int* arr;	//��� ������ ��������, ����� �� ������������ � ������ �� ������� �������
		int idx;	//��� ��������� �������� ������

		public:

		Iter(int*);
		Iter* operator=(int);
		Iter* operator++(int);
		int operator[](int);
	};
};

//�����, ����������� ������ � ����� ��� ����
class DrawPanel: public wxPanel{
  public:
        DrawPanel(wxPanel *parent, wxStatusBar *sb, wxSocketClient *sc); //� ������������ ����������� ����� �������, ������� �� ��������
        void OnPaint(wxPaintEvent & event);	//��� ���������
	void OnDclick(wxMouseEvent& event); 	//��� ������ � �������
	check20 pl;				//���������� � ����
	wxStatusBar *dpsb;			//��� ������ ��������� � ������ ���
	wxSocketClient *m_sc;			//���������� � ������
};

// �����, ���������� ���������� ������, ������, ������ ���
class AddE: public wxFrame{
	wxSocketClient * m_SocketClient;		//���������� �����
public:
	AddE(const wxString& title);
	~AddE();
	DECLARE_EVENT_TABLE()

	wxPanel *m_pan;
	wxButton *bt, *ng;
	DrawPanel *dp;

	wxMenuBar *menubar;	//������� ��� ����
	wxMenu *file;
	wxStatusBar *sb;	// ������ ���
	wxString ss;
	void OnQuit(wxCommandEvent& event);	//�������� ��� ������� �� ������ "quit"
	void OnNew(wxCommandEvent& event);	//new - ����� ����

	// ���������� ������� �� ������
	void OnClientSocketEvent(wxSocketEvent & event);
	// ���������� ������ �������
	void OnConnect(wxCommandEvent & event);
	// ���������� ������ ����������
	void OnDisconnect(wxCommandEvent & event);
};


class Pril: public wxApp{
    public:
        virtual bool OnInit();
};

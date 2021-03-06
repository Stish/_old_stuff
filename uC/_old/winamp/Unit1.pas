unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, WinampControl,
  StdCtrls, ExtCtrls, RS232;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Button2: TButton;
    Timer1: TTimer;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Button3: TButton;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormDestroy(Sender: TObject);
    procedure Button4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  winamp : twinampcontrol;
	art_title : string;
        artist : string;
        title : string;
        tit_length : string;
        tit_pos : string;
        tit_pos_ratio : integer;
        
implementation

{$R *.DFM}

procedure TForm1.Button1Click(Sender: TObject);
var
        i : integer;
begin
	art_title := winamp.GetTrackTitle;
        artist := '';
        title := '';
        i := 0;
        if (art_title <> '') then
        begin
        	while (i <= length(art_title)) and (art_title[i+1] <> '-') do
        	begin
			inc(i);
        	end;
        end;
        artist := copy(art_title, 1, i-1);
        title := copy(art_title, i+3, length(art_title));

        tit_length := floattostr(int(winamp.GetLength/60)) + ':';
        if (winamp.GetLength mod 60) < 10 then
        	tit_length := tit_length + '0';
        tit_length := tit_length + inttostr(winamp.GetLength mod 60);

	tit_pos := floattostr(int(winamp.Getoffset/60000000)) + ':';
        if (round((winamp.getoffset mod 60000000)/1000000)) < 10 then
        	tit_pos := tit_pos + '0';
        tit_pos := tit_pos + inttostr(round((winamp.getoffset mod 60000000)/1000000));

        if winamp.GetLength <> 0 then
		tit_pos_ratio := round(winamp.Getoffset/winamp.GetLength/10000)
        else
        	tit_pos_ratio := 0;

        tit_length := tit_pos + ' of ' + tit_length;

        form1.Label1.Caption := artist;
        form1.Label2.Caption := title;
        form1.Label3.caption := tit_length;
        form1.Label4.Caption := tit_pos;
        form1.Label5.Caption := inttostr(tit_pos_ratio);
//        form1.Label3.caption := inttostr(winamp.Getoffset) + 'secs';
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
	winamp.Pause;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
        i : integer;
begin
	if winamp.IsWinampRunning then
     		button1.click;
	form1.Edit3.Text := inttostr(readbyte);
//============ Sending Artist ==================================================
        if artist <> '' then
        begin
        	sendbyte(2);
		for i := 1 to length(artist) do
        	begin
        		sendbyte(ord(artist[i]));
        	end;
        	sendbyte(255);
        end
        else
        begin
        	sendbyte(2);
       		sendbyte(ord(' '));
        	sendbyte(255);
	end;
//============ Sending Title ==================================================
        if title <> '' then
        begin
        	sendbyte(3);
		for i := 1 to length(title) do
        	begin
        		sendbyte(ord(title[i]));
        	end;
        	sendbyte(254);
        end
        else
        begin
        	sendbyte(3);
       		sendbyte(ord(' '));
        	sendbyte(254);
	end;
//============ Sending Title Length ============================================
        if tit_length <> '' then
        begin
        	sendbyte(4);
		for i := 1 to length(tit_length) do
        	begin
        		sendbyte(ord(tit_length[i]));
        	end;
        	sendbyte(253);
        end
        else
        begin
        	sendbyte(4);
       		sendbyte(ord(' '));
        	sendbyte(253);
	end;
//============ Sending Title Position ==========================================
{        if tit_pos <> '' then
        begin
        	sendbyte(5);
		for i := 1 to length(tit_pos) do
        	begin
        		sendbyte(ord(tit_pos[i]));
        	end;
        	sendbyte(252);
        end
        else
        begin
        	sendbyte(5);
       		sendbyte(ord(' '));
        	sendbyte(252);
	end;     }
//============ Sending Title Position Percent ==================================
	sendbyte(6);
        sendbyte(10+tit_pos_ratio);
        sendbyte(251);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
	OPENCOM('COM1: baud=115200 data=8 parity=N stop=1');
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
	CLOSECOM;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
	CLOSECOM;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
	winamp.RestartWinamp;
end;

end.


unit MDTune;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons, Vcl.ComCtrls,
  Vcl.ExtCtrls;

type
  TForm1 = class(TForm)
    GroupBox1: TGroupBox;
    Button1: TButton;
    Button2: TButton;
    GroupBox2: TGroupBox;
    Button4: TButton;
    Button5: TButton;
    GroupBox3: TGroupBox;
    TrackBar1: TTrackBar;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    UpDown1: TUpDown;
    Edit1: TEdit;
    UpDown2: TUpDown;
    Edit2: TEdit;
    Label7: TLabel;
    UpDown3: TUpDown;
    Edit3: TEdit;
    Label8: TLabel;
    GroupBox4: TGroupBox;
    LabeledEdit1: TLabeledEdit;
    ComboBox1: TComboBox;
    Label9: TLabel;
    Memo1: TMemo;
    Button6: TButton;
    Edit4: TEdit;
    Label10: TLabel;
    UpDown4: TUpDown;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
    procedure Edit1Change(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
    procedure UpDown1Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown2Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown3Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown4Click(Sender: TObject; Button: TUDBtnType);
    procedure Button6Click(Sender: TObject);
    procedure Edit3Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

function RunProcess(FileName: string; ShowCmd: DWORD; wait: Boolean; ProcID:
  PDWORD): Longword;
var
  StartupInfo: TStartupInfo;
  ProcessInfo: TProcessInformation;
  x:cardinal;
begin
  FillChar(StartupInfo, SizeOf(StartupInfo), #0);
  StartupInfo.cb := SizeOf(StartupInfo);
  StartupInfo.dwFlags := STARTF_USESHOWWINDOW or STARTF_FORCEONFEEDBACK;
  StartupInfo.wShowWindow := ShowCmd;
  if not CreateProcess(nil,@Filename[1],nil,nil,False,CREATE_NEW_CONSOLE or NORMAL_PRIORITY_CLASS,nil,nil,StartupInfo,ProcessInfo) then
    Result := WAIT_FAILED
  else
  begin
    if wait = FALSE then
    begin
      if ProcID <> nil then
        ProcID^ := ProcessInfo.dwProcessId;
      result := WAIT_FAILED;
      exit;
    end;
    WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
    GetExitCodeProcess(ProcessInfo.hProcess, Result);
  end;
  if ProcessInfo.hProcess <> 0 then
    CloseHandle(ProcessInfo.hProcess);
  if ProcessInfo.hThread <> 0 then
    CloseHandle(ProcessInfo.hThread);
  x:=GetLastError;
end;

procedure TForm1.Button1Click(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 0 L';
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Button2Click(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 0 R';
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Button4Click(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 1 A';
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Button5Click(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 1 M';
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Button6Click(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 6 ' + edit4.text;
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Edit1Change(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 3 '+edit1.Text;
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Edit2Change(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 4 '+edit2.Text;
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.Edit3Change(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
begin
  ProcID := 0;
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 5 '+edit3.Text;
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  memo1.Clear;
  memo1.ScrollBars:=ssBoth;
  memo1.ReadOnly:=true;
  ComboBox1.ItemIndex:=6;
  TrackBar1.Position:=0;
end;

procedure TForm1.TrackBar1Change(Sender: TObject);
var ProcID: Cardinal;
    cmd:string;
    data:array[0..4] of string;
begin
  ProcID := 0;
  data[0]:='200';
  data[1]:='400';
  data[2]:='800';
  data[3]:='1600';
  data[4]:='3200';
  cmd:='serial-update.exe '+labelededit1.Text+' '+ComboBox1.Text+' 2 '+data[TrackBar1.Position];
  RunProcess(cmd, SW_HIDE, TRUE, @ProcID);
end;

procedure TForm1.UpDown1Click(Sender: TObject; Button: TUDBtnType);
begin
  edit1.Text:=inttostr(UpDown1.Position);
end;

procedure TForm1.UpDown2Click(Sender: TObject; Button: TUDBtnType);
begin
  edit2.Text:=inttostr(UpDown2.Position);
end;

procedure TForm1.UpDown3Click(Sender: TObject; Button: TUDBtnType);
begin
  edit3.Text:=inttostr(UpDown3.Position);
end;

procedure TForm1.UpDown4Click(Sender: TObject; Button: TUDBtnType);
begin
  edit4.Text:=inttostr(UpDown3.Position);
end;

end.

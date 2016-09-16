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
    TrackBar1: TTrackBar;
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
    procedure CaptureConsoleOutput(DosApp : string;params : string;AMemo : Tstrings; App:Tapplication);
    procedure Memo1KeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure Memo1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  mauto: boolean;

implementation

{$R *.dfm}

procedure TForm1.CaptureConsoleOutput(DosApp : string;params : string;AMemo : Tstrings; App:Tapplication);
const
  ReadBuffer = 1048576;  // 1 MB Buffer
var
  Security            : TSecurityAttributes;
  ReadPipe,WritePipe  : THandle;
  start               : TStartUpInfo;
  ProcessInfo         : TProcessInformation;
  Buffer              : PAnsiChar;
  TotalBytesRead,
  BytesRead           : DWORD;
  Apprunning,n,
  BytesLeftThisMessage,
  TotalBytesAvail : integer;
  CommandLine         : string;
  lines               : string;
  position            : integer;
  flags               : cardinal;
begin
  with Security do
  begin
    nlength              := SizeOf(TSecurityAttributes);
    binherithandle       := true;
    lpsecuritydescriptor := nil;
  end;

  if CreatePipe (ReadPipe, WritePipe, @Security, 0) then
  begin
    // Redirect In- and Output through STARTUPINFO structure

    Buffer  := AllocMem(ReadBuffer + 1);
    FillChar(Start,Sizeof(Start),#0);
    start.cb          := SizeOf(start);
    start.hStdOutput  := WritePipe;
    start.hStdInput   := ReadPipe;
    start.dwFlags     := STARTF_USESTDHANDLES + STARTF_USESHOWWINDOW;
    start.wShowWindow := SW_HIDE;
    start.hStdError   := WritePipe;

    // Create a Console Child Process with redirected input and output
    FmtStr(CommandLine, '"%s" %s', [DosApp, params]);

    if CreateProcess(nil      ,PChar(CommandLine),
                     @Security,@Security,
                     true     ,CREATE_NO_WINDOW or NORMAL_PRIORITY_CLASS,
                     nil      ,nil,
                     start    ,ProcessInfo) then
    begin
      n:=0;
      TotalBytesRead:=0;
      repeat
        // Increase counter to prevent an endless loop if the process is dead
        Inc(n,1);

        // wait for end of child process
        Apprunning := WaitForSingleObject(ProcessInfo.hProcess,100);
        App.ProcessMessages;

        // it is important to read from time to time the output information
        // so that the pipe is not blocked by an overflow. New information
        // can be written from the console app to the pipe only if there is
        // enough buffer space.

        if not PeekNamedPipe(ReadPipe        ,@Buffer[TotalBytesRead],
                             ReadBuffer      ,@BytesRead,
                             @TotalBytesAvail,@BytesLeftThisMessage) then
                             break
        else
        if BytesRead > 0 then
          ReadFile(ReadPipe,Buffer[TotalBytesRead],BytesRead,BytesRead,nil);
        TotalBytesRead:=TotalBytesRead+BytesRead;
      until (Apprunning <> WAIT_TIMEOUT) or (n > 150);

      Buffer[TotalBytesRead]:= #0;
      lines:=strpas(Buffer);
      if lines<>'' then
        AMemo.Add(lines);
    end;
    FreeMem(Buffer);
    CloseHandle(ProcessInfo.hProcess);
    CloseHandle(ProcessInfo.hThread);
    CloseHandle(ReadPipe);
    CloseHandle(WritePipe);
  end;
end;

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
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 0 L',memo1.Lines,Application);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 0 R',memo1.Lines,Application);
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 1 A',memo1.Lines,Application);
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 1 M',memo1.Lines,Application);
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 6 '+edit4.Text,memo1.Lines,Application);
end;

procedure TForm1.Edit1Change(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 3 '+edit1.Text,memo1.Lines,Application);
end;

procedure TForm1.Edit2Change(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 4 '+edit2.text,memo1.Lines,Application);
end;

procedure TForm1.Edit3Change(Sender: TObject);
begin
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 5 '+edit3.text,memo1.Lines,Application);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  memo1.Clear;
  memo1.ScrollBars:=ssBoth;
  memo1.ReadOnly:=true;
  ComboBox1.ItemIndex:=6;
  TrackBar1.Position:=0;
  mauto:=false;
end;

procedure TForm1.Memo1KeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
begin
  if ssCtrl in Shift then
  begin
    case Key of
      VK_RIGHT:  if TrackBar1.Position < 4 then TrackBar1.Position:=TrackBar1.Position+1;
      VK_LEFT: if TrackBar1.Position > 0 then TrackBar1.Position:=TrackBar1.Position-1;
    end;
  end
  else
  begin
    case Key of
      VK_LEFT:  Button1Click(self);
      VK_RIGHT: Button2Click(self);
      VK_UP:    Edit2.Text:=inttostr(StrToInt(Edit2.Text)+50);
      VK_DOWN:  if strtoint(edit2.Text)>0 then Edit2.Text:=inttostr(StrToInt(Edit2.Text)-50);
      VK_RETURN:if mauto=false then Button6Click(self);
    end;
  end;
end;

procedure TForm1.Memo1KeyPress(Sender: TObject; var Key: Char);
var bCtrl: Boolean;
begin
  //bCtrl := GetKeyState(VK_LCONTROL) <> 0;
  //if bCtrl then
  case Key of
    'a': begin Button4Click(self);mauto:=true;end;
    'm': begin Button5Click(self);mauto:=false;end;
  end;
  Key := #0;
end;

procedure TForm1.TrackBar1Change(Sender: TObject);
var data:array[0..4] of string;
begin
  data[0]:='200';
  data[1]:='400';
  data[2]:='800';
  data[3]:='1600';
  data[4]:='3200';
  CaptureConsoleOutput('serial-update.exe',labelededit1.Text+' '+ComboBox1.Text+' 2 '+data[TrackBar1.Position],memo1.Lines,Application);
end;

procedure TForm1.UpDown1Click(Sender: TObject; Button: TUDBtnType);
begin
  case Button of
    btNext: edit1.Text:=inttostr(strtoint(edit1.Text)+1);
    btPrev: edit1.Text:=inttostr(strtoint(edit1.Text)-1);
  end;
end;

procedure TForm1.UpDown2Click(Sender: TObject; Button: TUDBtnType);
begin
  case Button of
    btNext: edit2.Text:=inttostr(strtoint(edit2.Text)+1);
    btPrev: edit2.Text:=inttostr(strtoint(edit2.Text)-1);
  end;
end;

procedure TForm1.UpDown3Click(Sender: TObject; Button: TUDBtnType);
begin
  case Button of
    btNext: edit3.text:=inttostr(strtoint(edit3.Text)+1);
    btPrev: edit3.text:=inttostr(strtoint(edit3.Text)-1);
  end;
end;

procedure TForm1.UpDown4Click(Sender: TObject; Button: TUDBtnType);
begin
  case Button of
    btNext: edit4.Text:=inttostr(strtoint(edit4.Text)+1);
    btPrev: edit4.Text:=inttostr(strtoint(edit4.Text)-1);
  end;
end;

end.

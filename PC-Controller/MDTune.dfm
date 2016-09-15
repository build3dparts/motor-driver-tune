object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '3D Printer Motor-Driver Tunning Tool'
  ClientHeight = 207
  ClientWidth = 700
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label6: TLabel
    Left = 8
    Top = 159
    Width = 61
    Height = 13
    Caption = 'Step Time us'
  end
  object Label7: TLabel
    Left = 75
    Top = 159
    Width = 72
    Height = 13
    Caption = 'PWM Freq (Hz)'
  end
  object Label8: TLabel
    Left = 156
    Top = 159
    Width = 38
    Height = 13
    Caption = 'PWM %'
  end
  object Label10: TLabel
    Left = 223
    Top = 159
    Width = 48
    Height = 13
    Caption = 'Step once'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 137
    Height = 57
    Caption = 'Direction'
    TabOrder = 0
    object Button1: TButton
      Left = 7
      Top = 21
      Width = 59
      Height = 25
      Caption = '<'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 77
      Top = 21
      Width = 53
      Height = 25
      Caption = '>'
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 151
    Top = 8
    Width = 146
    Height = 57
    Caption = 'Stepping'
    TabOrder = 1
    object Button4: TButton
      Left = 11
      Top = 21
      Width = 54
      Height = 25
      Caption = 'Auto'
      TabOrder = 0
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 73
      Top = 21
      Width = 58
      Height = 25
      Caption = 'Manual'
      TabOrder = 1
      OnClick = Button5Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 7
    Top = 71
    Width = 290
    Height = 82
    Caption = 'Steps/revolution'
    TabOrder = 2
    object Label1: TLabel
      Left = 22
      Top = 60
      Width = 18
      Height = 13
      Caption = '200'
    end
    object Label2: TLabel
      Left = 82
      Top = 60
      Width = 18
      Height = 13
      Caption = '400'
    end
    object Label3: TLabel
      Left = 142
      Top = 60
      Width = 18
      Height = 13
      Caption = '800'
    end
    object Label4: TLabel
      Left = 196
      Top = 60
      Width = 24
      Height = 13
      Caption = '1600'
    end
    object Label5: TLabel
      Left = 251
      Top = 60
      Width = 24
      Height = 13
      Caption = '3200'
    end
    object TrackBar1: TTrackBar
      Left = 21
      Top = 25
      Width = 254
      Height = 37
      LineSize = 3
      Max = 4
      TabOrder = 0
      TickStyle = tsManual
      OnChange = TrackBar1Change
    end
  end
  object UpDown1: TUpDown
    Left = 53
    Top = 174
    Width = 17
    Height = 25
    Max = 1000000
    Position = 10
    TabOrder = 3
    OnClick = UpDown1Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 178
    Width = 39
    Height = 21
    TabOrder = 4
    Text = '10000'
    OnChange = Edit1Change
  end
  object UpDown2: TUpDown
    Left = 129
    Top = 176
    Width = 17
    Height = 25
    Max = 1000000
    Position = 30000
    TabOrder = 5
    OnClick = UpDown2Click
  end
  object Edit2: TEdit
    Left = 75
    Top = 178
    Width = 49
    Height = 21
    TabOrder = 6
    Text = '100'
    OnChange = Edit2Change
  end
  object UpDown3: TUpDown
    Left = 200
    Top = 174
    Width = 17
    Height = 25
    Position = 50
    TabOrder = 7
    OnClick = UpDown3Click
  end
  object Edit3: TEdit
    Left = 156
    Top = 178
    Width = 38
    Height = 21
    TabOrder = 8
    Text = '50'
    OnChange = Edit3Change
  end
  object GroupBox4: TGroupBox
    Left = 303
    Top = 8
    Width = 82
    Height = 125
    Caption = 'Serial Port'
    TabOrder = 9
    object Label9: TLabel
      Left = 10
      Top = 69
      Width = 30
      Height = 13
      Caption = 'Speed'
    end
    object LabeledEdit1: TLabeledEdit
      Left = 10
      Top = 42
      Width = 61
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'COM Port'
      TabOrder = 0
      Text = 'COM4'
    end
    object ComboBox1: TComboBox
      Left = 10
      Top = 88
      Width = 61
      Height = 21
      TabOrder = 1
      Text = '262500'
      Items.Strings = (
        '4800'
        '9600'
        '19200'
        '38400'
        '57000'
        '115200'
        '262500')
    end
  end
  object Memo1: TMemo
    Left = 391
    Top = 8
    Width = 301
    Height = 191
    Lines.Strings = (
      'Memo1')
    TabOrder = 10
  end
  object Button6: TButton
    Left = 303
    Top = 139
    Width = 82
    Height = 60
    Caption = 'Step'
    TabOrder = 11
    OnClick = Button6Click
  end
  object Edit4: TEdit
    Left = 223
    Top = 178
    Width = 38
    Height = 21
    TabOrder = 12
    Text = '50'
  end
  object UpDown4: TUpDown
    Left = 267
    Top = 174
    Width = 17
    Height = 25
    Position = 1
    TabOrder = 13
    OnClick = UpDown4Click
  end
end

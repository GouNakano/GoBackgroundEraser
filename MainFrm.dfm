object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'GoBackgroundEraser'
  ClientHeight = 75
  ClientWidth = 837
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object updateBtn: TBitBtn
    Left = 16
    Top = 8
    Width = 121
    Height = 25
    Caption = #26356#26032
    TabOrder = 0
    OnClick = updateBtnClick
  end
  object BGEraseTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = BGEraseTimerTimer
    Left = 608
    Top = 16
  end
end

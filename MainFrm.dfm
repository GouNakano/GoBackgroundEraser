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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ModeLabel: TLabel
    Left = 16
    Top = 47
    Width = 58
    Height = 14
    Caption = 'ModeLabel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object updateBtn: TBitBtn
    Left = 8
    Top = 8
    Width = 120
    Height = 25
    Caption = #26356#26032
    TabOrder = 0
    OnClick = updateBtnClick
  end
  object saveBtn: TBitBtn
    Left = 152
    Top = 8
    Width = 120
    Height = 25
    Caption = #20445#23384
    TabOrder = 1
    OnClick = saveBtnClick
  end
  object resetBtn: TBitBtn
    Left = 288
    Top = 8
    Width = 120
    Height = 25
    Caption = #12522#12475#12483#12488
    TabOrder = 2
    OnClick = resetBtnClick
  end
  object specifyBGBtn: TBitBtn
    Left = 424
    Top = 8
    Width = 120
    Height = 25
    Caption = #32972#26223#25351#23450#12514#12540#12489
    TabOrder = 3
    OnClick = specifyBGBtnClick
  end
  object specifyFGBtn: TBitBtn
    Left = 568
    Top = 8
    Width = 120
    Height = 25
    Caption = #21069#26223#25351#23450#12514#12540#12489
    TabOrder = 4
    OnClick = specifyFGBtnClick
  end
end

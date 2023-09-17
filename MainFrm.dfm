object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'GoBackgroundEraser'
  ClientHeight = 632
  ClientWidth = 994
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object MenuPanel: TPanel
    Left = 0
    Top = 0
    Width = 994
    Height = 103
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 935
    object updateBtn: TBitBtn
      Left = 432
      Top = 6
      Width = 75
      Height = 56
      Caption = #26356#26032
      TabOrder = 0
      OnClick = updateBtnClick
    end
    object saveBtn: TBitBtn
      Left = 208
      Top = 37
      Width = 100
      Height = 25
      Caption = #30011#20687#20445#23384
      TabOrder = 1
      OnClick = saveBtnClick
    end
    object undoBtn: TBitBtn
      Left = 106
      Top = 37
      Width = 100
      Height = 25
      Caption = #20803#12395#25147#12377
      TabOrder = 2
      OnClick = undoBtnClick
    end
    object specifyBGBtn: TBitBtn
      Left = 208
      Top = 6
      Width = 100
      Height = 25
      Caption = #32972#26223#25351#23450#12514#12540#12489
      TabOrder = 3
      OnClick = specifyBGBtnClick
    end
    object specifyFGBtn: TBitBtn
      Left = 310
      Top = 6
      Width = 120
      Height = 25
      Caption = #21069#26223#25351#23450#12514#12540#12489
      TabOrder = 4
      OnClick = specifyFGBtnClick
    end
    object dispOrigImgBtn: TBitBtn
      Left = 4
      Top = 37
      Width = 100
      Height = 25
      Caption = #20803#30011#20687#12398#34920#31034
      TabOrder = 5
      OnClick = dispOrigImgBtnClick
    end
    object LoadImageBtn: TBitBtn
      Left = 4
      Top = 6
      Width = 100
      Height = 25
      Caption = #30011#20687#35501#36796
      TabOrder = 6
      OnClick = LoadImageBtnClick
    end
    object SelRectBtn: TBitBtn
      Left = 106
      Top = 6
      Width = 100
      Height = 25
      Caption = #31684#22258#25351#23450#12514#12540#12489
      TabOrder = 7
      OnClick = SelRectBtnClick
    end
    object Panel2: TPanel
      Left = 1
      Top = 73
      Width = 992
      Height = 29
      Align = alBottom
      BevelOuter = bvLowered
      TabOrder = 8
      ExplicitWidth = 933
      object ModeLabel: TLabel
        Left = 113
        Top = 7
        Width = 61
        Height = 16
        Caption = 'ModeLabel'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Panel3: TPanel
        Left = 1
        Top = 1
        Width = 105
        Height = 27
        Align = alLeft
        Caption = #12513#12483#12475#12540#12472
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
    end
    object EndBtn: TBitBtn
      Left = 509
      Top = 6
      Width = 75
      Height = 56
      Caption = #32066#20102
      TabOrder = 9
      OnClick = EndBtnClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 103
    Width = 994
    Height = 2
    Align = alTop
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 935
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 613
    Width = 994
    Height = 19
    Panels = <>
    ExplicitTop = 545
    ExplicitWidth = 935
  end
  object MainPanel: TPanel
    Left = 0
    Top = 105
    Width = 994
    Height = 508
    Align = alClient
    TabOrder = 3
    ExplicitWidth = 935
    ExplicitHeight = 440
  end
  object MainMenu1: TMainMenu
    Left = 228
    Top = 100
    object N1: TMenuItem
      Caption = #12501#12449#12452#12523'(&F)'
      object ZZZZZ1: TMenuItem
        Caption = 'ZZZZZ'
        OnClick = ZZZZZ1Click
      end
    end
    object N6: TMenuItem
      Caption = #32232#38598
      object UndoMemu: TMenuItem
        Caption = #20803#12395#25147#12377
        ShortCut = 16474
        OnClick = UndoMemuClick
      end
    end
  end
  object MainMenu: TMainMenu
    Left = 92
    Top = 119
    object F1: TMenuItem
      Caption = #12501#12449#12452#12523'(&F)'
      object LoadImageMenu: TMenuItem
        Caption = #30011#20687#35501#36796
      end
      object MenuItem1: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Caption = #30011#20687#20445#23384
        ShortCut = 16467
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object EndMenu: TMenuItem
        Caption = #32066#20102
      end
    end
    object E1: TMenuItem
      Caption = #32232#38598'(&E)'
      ShortCut = 16474
      object undoMenu: TMenuItem
        Caption = #20803#12395#25147#12377
        ShortCut = 16450
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object UpdateMenu: TMenuItem
        Caption = #26356#26032
      end
    end
    object H1: TMenuItem
      Caption = #12504#12523#12503'&H)'
      object N4: TMenuItem
        Caption = #12496#12540#12472#12519#12531#24773#22577
      end
      object aaaaaa1: TMenuItem
        Caption = 'aaaaaa'
        ShortCut = 16474
      end
    end
  end
  object OpenPictureDialog: TOpenPictureDialog
    Filter = 
      #12377#12409#12390' (*.gif;*.jpg;*.jpeg;*.png;*.bmp)|*.gif;*.jpg;*.jpeg;*.png;*.' +
      'bmp|GIF '#30011#20687' (*.gif)|*.gif|JPEG '#12452#12513#12540#12472#12501#12449#12452#12523' (*.jpg)|*.jpg|JPEG '#12452#12513#12540#12472#12501#12449 +
      #12452#12523' (*.jpeg)|*.jpeg|Portable Network Graphics (*.png)|*.png|'#12499#12483#12488#12510#12483 +
      #12503' (*.bmp)|*.bmp'
    Left = 12
    Top = 118
  end
end

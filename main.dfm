object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 926
  ClientWidth = 1165
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  TextHeight = 13
  object ICanvas: TImage
    Left = 8
    Top = 8
    Width = 929
    Height = 910
    OnMouseDown = ICanvasMouseDown
  end
  object Label1: TLabel
    Left = 943
    Top = 327
    Width = 127
    Height = 13
    Caption = 'Total weight of the edges:'
  end
  object LBTotalWeight: TLabel
    Left = 1088
    Top = 327
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label2: TLabel
    Left = 943
    Top = 356
    Width = 138
    Height = 13
    Caption = 'Weight of the shortest path:'
  end
  object Label3: TLabel
    Left = 1088
    Top = 356
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label4: TLabel
    Left = 943
    Top = 388
    Width = 118
    Height = 13
    Caption = 'Weight of a target path:'
  end
  object LBTargetWeight: TLabel
    Left = 1088
    Top = 388
    Width = 6
    Height = 13
    Caption = '0'
  end
  object RGButtons: TRadioGroup
    Left = 943
    Top = 8
    Width = 218
    Height = 313
    Items.Strings = (
      'Create node'
      'Create branch'
      'Create branch with weight'
      'Select node'
      'Select branch'
      'Delete node'
      'Delete branch'
      'select two point for path building')
    TabOrder = 0
  end
  object BTFindPath: TButton
    Tag = 1
    Left = 943
    Top = 415
    Width = 218
    Height = 25
    Caption = 'Finding the shortest path'
    TabOrder = 1
    OnClick = BTFindPathClick
  end
  object Memo1: TMemo
    Left = 943
    Top = 597
    Width = 185
    Height = 321
    Lines.Strings = (
      'Memo1')
    TabOrder = 2
  end
  object Button1: TButton
    Tag = 2
    Left = 943
    Top = 446
    Width = 139
    Height = 25
    Caption = 'Finding the n-path'
    TabOrder = 3
    OnClick = BTFindPathClick
  end
  object ENValue: TEdit
    Left = 1088
    Top = 446
    Width = 73
    Height = 21
    NumbersOnly = True
    TabOrder = 4
  end
  object MainMenu: TMainMenu
    Left = 1040
    Top = 544
    object S1: TMenuItem
      Caption = 'Save'
      object Savevector1: TMenuItem
        Caption = 'Save vector'
        OnClick = Savevector1Click
      end
      object Savevector2: TMenuItem
        Caption = 'Save matrix'
        OnClick = Savevector2Click
      end
      object Savelist1: TMenuItem
        Caption = 'Save list'
        OnClick = Savelist1Click
      end
    end
    object Open1: TMenuItem
      Caption = 'Open'
      object Openvector1: TMenuItem
        Caption = 'Open vector'
        OnClick = Openvector1Click
      end
      object Openadjectivematrixwizard1: TMenuItem
        Caption = 'Open adjective matrix wizard'
        OnClick = Openadjectivematrixwizard1Click
      end
    end
  end
  object OpenDialog: TOpenDialog
    Left = 976
    Top = 544
  end
  object SaveDialog: TSaveDialog
    Left = 1008
    Top = 544
  end
end

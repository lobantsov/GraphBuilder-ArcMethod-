object FormWeight: TFormWeight
  Left = 0
  Top = 0
  Caption = 'FormWeight'
  ClientHeight = 81
  ClientWidth = 320
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnShow = FormShow
  TextHeight = 15
  object EWeight: TEdit
    Left = 0
    Top = 8
    Width = 313
    Height = 23
    NumbersOnly = True
    TabOrder = 0
  end
  object Button1: TButton
    Left = 0
    Top = 48
    Width = 121
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 1
    OnClick = Button1Click
  end
  object BTCancel: TButton
    Left = 192
    Top = 48
    Width = 121
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
    OnClick = BTCancelClick
  end
end

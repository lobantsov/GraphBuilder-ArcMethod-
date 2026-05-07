object FAdjectiveMatrixWizard: TFAdjectiveMatrixWizard
  Left = 0
  Top = 0
  Caption = 'FAdjectiveMatrixWizard'
  ClientHeight = 653
  ClientWidth = 891
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  OnClose = FormClose
  OnShow = FormShow
  TextHeight = 15
  object ICanvas: TImage
    Left = 0
    Top = 0
    Width = 889
    Height = 649
  end
  object MainMenu1: TMainMenu
    Left = 824
    Top = 584
    object Saveadjectivematrix1: TMenuItem
      Caption = 'Save adjective matrix'
      OnClick = Saveadjectivematrix1Click
    end
  end
  object SaveDialog: TSaveDialog
    Left = 816
    Top = 528
  end
end

   M S B A M L   `   `   `  ���� B  >FMS_GUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:FMS_GUIFMS_GUI  F BFMS_adapter, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null>.clr-namespace:FMS_adapter;assembly=FMS_adapterFMS_adapter     FMS_GUI.CreateDisk   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     'localclr-namespace:FMS_GUI     FFMS_adapter.clr-namespace:FMS_adapter;assembly=FMS_adapter     
�������.���   � RowDefinitions  �� $��* ��� $��* ��� $��* ��� $��* ��� $��* �.+��� -    ��Name$ Title��$��Create a new disk��$��Center=�$��Center=�$��0��$��32(�$��Italic$�
��������� -   $
 Info��$,��&Please fill the field to create a disk��$��Center=�$��Center=�$��27(�$��1��� -    �Name$ grid1��$��2�� � ColumnDefinitions �� $��* ��� $��* �.+��� $��
Disk Name:��$��0��$��Center=�$��Center=�$��25(��� -    ��Name$ diskNameTextBox��$��1��$��25q�$��0��$��Center=�$��Center=�$��25(�� -   $ grid2��$��3�� �� $��* ��� $��* �.+��� $��Disk Owner:��$��0��$��Center=�$��Center=�$��25(��� -   $ diskOwnerTextBox��$��1��$��25q�$��Center=�$��Center=�$��25(�� $��4�� �� $��* ��� $��* �.+��� -    ��Name$ 
BackButton��$
��Back��$��0��
���   �$��
20,35,0,20q�$
��Left=�$	��135���� -   $ 
NextButton��$
��Next��$��1��
���   �$��
0,35,20,20q�$��Right=�$	��135������  �� Triggers ��  �� Binding ��  �� ElementName$ diskNameTextBox��	 �� Path$
	 Text�
 �� Value
  .a���  �� Property � {� �� Value .  ��  �� $ diskOwnerTextBox��$
	 Text�
  .a���  � {� .  
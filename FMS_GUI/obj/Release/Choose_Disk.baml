   M S B A M L   `   `   `  ���� B  >FMS_GUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:FMS_GUIFMS_GUI      FMS_GUI.Choose_Disk   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     'localclr-namespace:FMS_GUI     
�������.���   � RowDefinitions  �� $
��1.5* ��� $��* ��� $��3* ��� $��* �.+��� -    ��Name$ Section��$��Open a disk��$��Center=�$��Center=�
���/���$��30(�$��Normal$�$��0���� -   $
 Info��$��Please select a disk��$��Center=�$��Center=�$��28(�$��1��$��Italic$�&   System.Windows.Controls.DataGrid  -     Name$ Disklist��$��2��$��20q�
�������   AutoGenerateColumns .     SelectionMode$ Single=�   
IsReadOnly .    Columns 0  *System.Windows.Controls.DataGridTextColumn  ,  &System.Windows.Controls.DataGridColumn   Header$ 	Disk Name��   Width5  /System.Windows.Controls.DataGridLengthConverter$ 1* 1  +System.Windows.Controls.DataGridBoundColumn	   Binding	 �� 
 �� Path$

 name�  $ Creation Date��$ 1* 	 �� $

 date�   ColumnHeaderStyle ��  �� 
TargetType=  7System.Windows.Controls.Primitives.DataGridColumnHeader"  .���  �� Property � �� �� Value$ 25(�� $��3�� � ColumnDefinitions �� $��* ��� $��* �.+��� -    ��Name$ 
BackButton��$
��Back��$��0��
���   �$��
20,35,0,20q�$
��Left=�$	��135���� -   $ 
NextButton��$
��Next��$��1��
���   �$��
0,35,20,20q�$��Right=�$	��135��
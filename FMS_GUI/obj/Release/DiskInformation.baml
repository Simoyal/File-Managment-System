   M S B A M L   `   `   `  ���� B  >FMS_GUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:FMS_GUIFMS_GUI      FMS_GUI.DiskInformation   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     'localclr-namespace:FMS_GUI     
�������.��� .+��   � RowDefinitions  �� $��* ��� $��3* ��� $��* ��� $
��6.5* ��� $��* �.+��� $��Information of the disk��$��Center=�$��Center=�
�������
���   �$��0��$��27(�$��Italic$�� $��1��  �� $��* ��� $��* ��� $��* � � ColumnDefinitions �� $��* ��� $��* ��� $��* ��� $��* �.+��� $��Disk Name: ��$��0��$��0��$��Center=�$
��Left=�$��17(��� -    ��Name$ DiskName��$��0��$��1��$��Center=�$
��Left=�$��17(����� *
DiskName+�� $��Disk Owner: ��$��1��$��0��$��Center=�$
��Left=�$��17(��� -   $ 	DiskOwner��$��1��$��1��$��Center=�$
��Left=�$��17(����� *	DiskOwner+�� $��Creation Date: ��$��2��$��0��$��Center=�$
��Left=�$��17(��� -   $ CreationDate��$��2��$��1��$��Center=�$
��Left=�$��17(����� *CreationDate+�� $��IsFormated: ��$��0��$��2��$��Center=�$
��Left=�$��17(��� -   $ 
IsFormated��$��0��$��3��$��Center=�$
��Left=�$��17(����� *
IsFormated+�� $��Disk Capacity: ��$��1��$��2��$��Center=�$
��Left=�$��17(��� -   $ Capacity��$��1��$��3��$��Center=�$
��Left=�$��17(����� *
Capacity+�� $��Size Avalaible��$��2��$��2��$��Center=�$
��Left=�$��17(��� -   $
 Size��$��2��$��3��$��Center=�$
��Left=�$��17(����� *Size+� $��2�� �� $��* ��� $��4* �.+��� $��Disk Storage:��$��Center=�$��Center=�$��17(�$��0��� -    �Name$ 	DiskSpace��$��1��$��10q� � Value$	 100Q�� $��3��  �� $��* ��� $��8* �.+��� $��Disk Allocation Table��$��Center=�$��Center=�$��0��$��17(��� -   $	��DAT��$
��1000��$��230px��$��1��� $��4�� �� $��* ��� $��* ��� $��* �.+��� -	    ��Name$ 
BackButton��$
��Back��$��0��$��13(�$��90��$��30���� -
   $ FormatButton��$��Format��$��1��$��90��$��30��$��13(��� -   $ Defragmentation��$��Defrag��$��2��$��90��$��30��$��13(�
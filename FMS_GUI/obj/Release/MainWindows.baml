   M S B A M L   `   `   `  ���� B  >FMS_GUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:FMS_GUIFMS_GUI      FMS_GUI.MainWindows   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     'localclr-namespace:FMS_GUI     
�������.���   � RowDefinitions  �� $��* ��� $��* ��� $��2* ��� $��* �.+��� $��0��
����  ��� -    ��Name$
 Desc��$'��!Please select an action to perfom��$��Center=�$��Center=�$��26(�$��Italic$�$��1���� -   $ Tittle��$��File Managment System��$��Center=�$��Center=�$��45(�$��Italic$�
�������� $��2��  �� $��2* ��� $��* � � ColumnDefinitions �� $��* ��� $��* ��� $��* ��� $��* �.+��� -   $ Create��$��Create��$��Center=�$��Center=�$��0��$��1��$��24(��� -   $
 Open��$
��Open��$��Center=�$��Center=�$��1��$��1��$��24(��� -   $ Mount��$��Import��$��Center=�$��Center=�$��2��$��1��$��24(��� -   $ Delete��$��Delete��$��Center=�$��Center=�$��3��$��1��$��24(��� -    ��Name$ CreateButton�� 
  Create#��[  $	��100��$��89��$��24q�$��0��$��0��
���   � � ToolTip �� .+��� Create a new disk�� -   $ 
OpenButton��  Open#��[ $	��100��$��89��$��24q�$��1��$��0��
���   � �� .+��� Open an existant disk�� -	   $ ImportButton�� 	 Mount#��[ $	��100��$��89��$��24q�$��2��$��0��
���   � �� .+��� Import an external disk�� -
   $ DeleteButton��  Unmount#��[ $	��100��$��89��$��24q�$��3��$��0��
���   � �� .+��� !Delete a disk from the database� $��3�� �� $��* ��� $��* �.+��� -   $ Simon��$��Simon Moyal 1177707��$��20(�$��Center=�$
��Left=�$��10q��� -   $ Simshon��$��1��$��20(�$��Simshon Attal 209552397��$��Center=�$��Right=�$��10q�
   M S B A M L   `   `   `  ���� B  >FMS_GUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:FMS_GUIFMS_GUI      FMS_GUI.Main_Operation   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     'localclr-namespace:FMS_GUI     
�������.��� .+��   � RowDefinitions  �� $��* ��� $��2* ��� $��8* ��� $��* �.+��� -    ��Name$
 Info��$3��-Please choose an action to perfom on the disk��$��0��$��Center=�$��Center=�$��28(�$��Italic$�
����  �
�������� -    �Name$ FileMenu��$��1��$y�Visible=�  �� $��2* ��� $��* � � ColumnDefinitions �� $��* ��� $��* ��� $��* ��� $��* �.+��� -   $	 Add��$	��Add��$��Center=�$��Center=�$��0��$��1��$��17(��� -   $ Update��$��Update��$��Center=�$��Center=�$��1��$��1��$��17(��� -   $ Delete��$��Delete��$��Center=�$��Center=�$��2��$��1��$��17(��� -   $ Information��$��About��$��Center=�$��Center=�$��3��$��1��$��17(��� -    ��Name$ AddFileButton��$��0��$��0��
����ح�   Add File#��[  $��	60,5,60,2q� � ToolTip �� .+��� 
Add a file�� -   $ UpdateFileButton��$��1��$��0��
����ح�  Update File#��[ $��	60,5,60,2q� �� .+��� Extend a file�� -	   $ DeleteFileButton��$��2��$��0��
����ح�  Delete File#��[ $��	60,5,60,2q� �� .+��� Delete a file�� -
   $ InformationButton��$��3��$��0��
����ح�  Disk Information#��[ $��	60,5,60,2q� �� .+��� Information on the disk� -   $ 
RecordMenu��$��1��$y�Hidden=�  �� $��2* ��� $��* � �� $��* ��� $��* ��� $��* �.+��� $	��Add��$��Center=�$��Center=�$��0��$��1��$��17(��� $��Update��$��Center=�$��Center=�$��1��$��1��$��17(��� $��Delete��$��Center=�$��Center=�$��2��$��1��$��17(��� -   $ AddRecordButton��$��0��$��0��
����ح�  
Add Record#��[ $��	60,5,60,2q� �� .+��� 
Add a file�� -   $ UpdateRecordButton��$��1��$��0��
����ح�  Update Record#��[ $��	60,5,60,2q� �� .+��� Extend a file�� -   $ DeleteRecordButton��$��2��$��0��
����ح�  Delete Record#��[ $��	60,5,60,2q� �� .+��� Delete a file&   System.Windows.Controls.DataGrid  -     Name$ FileList��$��2��$��20q�
�������   AutoGenerateColumns .     SelectionMode$ Single=�	   
IsReadOnly	 . $y�Hidden=�
   Columns
 0  *System.Windows.Controls.DataGridTextColumn  ,  &System.Windows.Controls.DataGridColumn   Header$ 	File Name��   Width5  /System.Windows.Controls.DataGridLengthConverter$ 1* 1  +System.Windows.Controls.DataGridBoundColumn   Binding ��  �� Path$
 name�  $ 
File Owner��$ 1*  �� $ owner�  $ Creation Date��$ 1*  �� $
 date�  $ 	File Size��$ 1*  �� $
 size�  $
 Type��$ 1*  �� $
 type�   ColumnHeaderStyle ��  �� 
TargetType=  7System.Windows.Controls.Primitives.DataGridColumnHeader"  .���  �� Property � �� �� Value$ 20(�  -   $ 
RecordList��$��2��$��20q�
������� .  $ Single=�	 . $y�Hidden=�
   $ ID��$ 1*  �� $ Id�  $
 Name��$ 1*  �� $
 Name�  $	 Age��$ 1*  �� $
 Year�  $ Average��$ 1*  �� $ Average� �� "  .���  � ��$ 20(�  -   $ 
CourseList��$��2��$��20q�
������� .  $ Single=�	 . $y�Hidden=�
   $ 	Course ID��$ 1*  �� $ Id�  $ Course Name��$ 1*  �� $
 Name�  $ Credit��$ 1*  �� $ Credit� �� "  .���  � ��$ 20(�� -   $ Extend��$��2��$��165,35q�$y�Hidden=�  �� $��* ��� $��* ��� $��* �.+��� -   $ Infos��$%��Please fill the followind field��$��Center=�$��Center=�$��0��$��25(�$��Italic$�
�������� $��1�� �� $��* ��� $��* �.+��� $��
File size:��$��0��$��Center=�$��Center=�$��23(��� -    ��Name$ FileSizeTextBox��$��1��$��32q�$��Center=�$��Center=�$��20(�� $��2�� �� $��* ��� $��* �.+��� -   $ cancel��$��Cancel��$��Center=�$��Center=�$��0��$��35��$��90��$��16(��� -   $ Extended��$��Extend��$��Center=�$��Center=�$��1��$��16(�$��90��$��35������  �� Triggers ��  �� Binding ��  �� ElementName$ FileSizeTextBox��$
 Text� �� Value  .a���  � {� .  � -   $ AddFileSection��$��2��$��165,35q�$y�Hidden=�  �� $��* ��� $��* ��� $��* ��� $��* ��� $��* ��� $��* �.+��� -   $ AddInfo��$%��Please fill the followind field��$��Center=�$��Center=�$��0��$��25(�$��Italic$�
�������� $��1�� �� $��* ��� $��* �.+��� $��File type: ��$��0��$��Center=�$��Center=�$��20(��� -    ��Name$ FileType��$��1��$��14q����� *	keyType+� $��2�� �� $��* ��� $��* �.+��� $��File Name: ��$��0��$��Center=�$��Center=�$��20(��� -   $ AddFileNameTextBox��$��1��$��14q�$��Center=�$��Center=�$��13(�� $��3�� �� $��* ��� $��* �.+��� $��File Owner: ��$��0��$��Center=�$��Center=�$��20(��� -   $ AddFileOwnerTextBox��$��1��$��14q�$��Center=�$��Center=�$��13(�� $��4�� �� $��* ��� $��* �.+��� $��
File Size:��$��0��$��Center=�$��Center=�$��20(��� -   $ AddFileSizeTextBox��$��1��$��14q�$��Center=�$��Center=�$��13(�� $��5�� �� $��* ��� $��* �.+��� -   $ 	Addcancel��$��Cancel��$��Center=�$��Center=�$��0��$��35��$��90��$��16(��� -   $ AddFile��$	��Add��$��Center=�$��Center=�$��1��$��16(�$��90��$��35������  ��  �� $ AddFileNameTextBox��$
 Text�  .a���  � {� .  ��  �� $ AddFileOwnerTextBox��$
 Text�  .a���  � {� .  ��  �� $ AddFileSizeTextBox��$
 Text�  .a���  � {� .  � -   $ AddRecordOrCourse��$��2��$��165,20q�$y�Hidden=�  �� $��* ��� $��3* �.+��� $%��Please fill the followind field��$��Center=�$��Center=�$��0��$��25(�$��Italic$�
�������� -    $ StudentGridOption��$��1��$y�Hidden=� �� $��* ��� $��* �  �� $��* ��� $��* ��� $��* ��� $��* �.+��� $��Student's Name: ��$��Center=�$��Center=�$��16(�$��0��$��0���� $��Student's Age: ��$��Center=�$��Center=�$��16(�$��1��$��0���� $��Student's Average: ��$��Center=�$��Center=�$��16(�$��2��$��0���� -!   $ StudentNameTextBox��$��0��$��1��$��16q�$��Center=�$��Center=�$��12(��� -"   $ StudentAgeNameTextBox��$��1��$��1��$��16q�$��Center=�$��Center=�$��12(��� -#   $ StudentAverageTextBox��$��2��$��1��$��16q�$��Center=�$��Center=�$��12(��� -$   $ CancelAddStudent��$��Bottom=�$��Center=�$��3��$��0��$��Cancel��$��110,0,135,15q�$��75��$��30���� -%   $ AddRecordStudent��$��Bottom=�$��Center=�$��3��$��1��$	��Add��$��110,0,135,15q�$��75��$��30������  ��  �� $ StudentNameTextBox��$
 Text�  .a���  � {� .  ��  �� $ StudentAgeNameTextBox��$
 Text�  .a���  � {� .  ��  �� $ StudentAverageTextBox��$
 Text�  .a���  � {� .  � -&   $ UpdateStudentGrid��$��1��$y�Hidden=� �� $��* ��� $��* �  �� $��* ��� $��* ��� $��* ��� $��* �.+��� $��Student's Name: ��$��Center=�$��Center=�$��16(�$��0��$��0���� $��Student's Age: ��$��Center=�$��Center=�$��16(�$��1��$��0���� $��Student's Average: ��$��Center=�$��Center=�$��16(�$��2��$��0���� -'   $ StudentNamTextBox��$��0��$��1��$��16q�$��Center=�$��Center=�$��14(��� -(   $ StudentAgeNamTextBox��$��1��$��1��$��16q�$��Center=�$��Center=�$��14(��� -)   $ StudentAveragTextBox��$��2��$��1��$��16q�$��Center=�$��Center=�$��14(��� -*   $ CancelUpdateStudent��$��Bottom=�$��Center=�$��3��$��0��$��Cancel��$��110,0,135,15q�$��75��$��30���� -+   $ UpdateRecordStudent��$��Bottom=�$��Center=�$��3��$��1��$��Update��$��110,0,135,15q�$��75��$��30������  ��  �� $ StudentNamTextBox��$
 Text�  .a���  � {� .  ��  �� $ StudentAgeNamTextBox��$
 Text�  .a���  � {� .  ��  �� $ StudentAveragTextBox��$
 Text�  .a���  � {� .  � -,   $ CourseGridOption��$��1��$y�Hidden=� �� $��* ��� $��* �  �� $��* ��� $��* ��� $��* ��� $��* �.+��� $��Course Name: ��$��Center=�$��Center=�$��16(�$��0��$��0���� $��Course ID: ��$��Center=�$��Center=�$��16(�$��1��$��0���� $��Course Credit: ��$��Center=�$��Center=�$��16(�$��2��$��0���� --   $ CourseNameTextBox��$��0��$��1��$��16q�$��Center=�$��Center=�$��12(��� -.   $ CourseIDTextBox��$��1��$��1��$��16q�$��Center=�$��Center=�$��12(��� -/   $ CourseCreditTextBox��$��2��$��1��$��16q�$��Center=�$��Center=�$��12(��� -0   $ CancelAddCourse��$��Bottom=�$��Center=�$��3��$��0��$��Cancel��$��110,0,135,15q�$��75��$��30���� -1   $ AddRecordCourse��$��Bottom=�$��Center=�$��3��$��1��$	��Add��$��110,0,135,15q�$��75��$��30������  ��  �� $ CourseNameTextBox��$
 Text�  .a���  � {� .  ��  �� $ CourseIDTextBox��$
 Text�  .a���  � {� .  ��  �� $ CourseCreditTextBox��$
 Text�  .a���  � {� .  � -2   $ UpdateCourseOption��$��1��$y�Hidden=� �� $��* ��� $��* �  �� $��* ��� $��* ��� $��* ��� $��* �.+��� $��Course Name: ��$��Center=�$��Center=�$��16(�$��0��$��0���� $��Course ID: ��$��Center=�$��Center=�$��16(�$��1��$��0���� $��Course Credit: ��$��Center=�$��Center=�$��16(�$��2��$��0���� -3   $ CourseNamTextBox��$��0��$��1��$��16q�$��Center=�$��Center=�$��17(��� -4   $ CourseIdTextBox��$��1��$��1��$��16q�$��Center=�$��Center=�$��17(��� -5   $ CourseCrediTextBox��$��2��$��1��$��16q�$��Center=�$��Center=�$��17(��� -6   $ CancelCourse��$��Bottom=�$��Center=�$��3��$��0��$��Cancel��$��110,0,135,15q�$��75��$��30���� -7   $ UpdateCourse��$��Bottom=�$��Center=�$��3��$��1��$	��Add��$��110,0,135,15q�$��75��$��30������  ��  �� $ CourseNamTextBox��$
 Text�  .a���  � {� .  ��  �� $ CourseIdTextBox��$
 Text�  .a���  � {� .  ��  �� $ CourseCrediTextBox��$
 Text�  .a���  � {� .  � -8   $ 
LastButton��$��3�� �� $��* ��� $��* �.+��� -9   $ 
BackButton��$
��Back��$��0��
���   �$
��Left=�$��Center=�$��
15,10,0,12q�$	��100��$��25���� -:   $ 
NextButton��$
��Open��$��1��
���   �$��Right=�$��Center=�$��
0,10,15,12q�$	��100��$��25��� -;   $ OpenFile��$��2��$��165, 35q�$y�Hidden=�  �� $��* ��� $��2* ��� $��* �.+��� $��Please choose an OpenType��$��Center=�$��Center=�$��0��$��25(�$��Italic$�
�������� $��1�� �� $��* ��� $��* �.+��� $��OpenType available: ��$��Center=�$��Center=�$��0��$��19(��� -<   $ OpenTypeCombobox��$��Center=�$��10q�$��1�� �� SelectedItem �� *
OpenType+� $��2�� �� $��* ��� $��* �.+��� -=   $ 
Opencancel��$��Cancel��$��Center=�$��Center=�$��0��$��35��$��90��$��16(��� ->   $ OpenFileButton��$
��Open��$��Center=�$��Center=�$��1��$��16(�$��90��$��35��
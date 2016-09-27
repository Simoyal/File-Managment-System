
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class Student
    {

        private int _id;
        public int Id
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value;
            }
        }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        private string _Name;
        public string Name
        {
            get
            {
                return _Name;
            }
            set
            {
                _Name = value;
            }
        }

        int _year;
        public int Year
        {
            get
            {
                return _year;
            }

            set
            {
                _year = value;
            }
        }

        float _average;
        public float Average
        {
            get
            {
                return _average;
            }

            set
            {
                _average = value;
            }
        }


        public Student(int id, string Name, int Year, float Averange)
        {
            this.Id = id;
            this.Name = Name;
            this.Year = Year;
            this.Average = Averange;
        }
        public Student()
        {

        }

        public override string ToString()
        {
            string name = Name;

            for (int i = 0; i < (20 - name.Length); i++)
            {
                name += " ";
            }

            return "Id: " + Id + " name: " + Name + " year: " + Year + " average: " + Average;
        }
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class Course
    {
        private int CourseId;
        public int Id
        {
            get
            {
                return CourseId;
            }
            set
            {
                CourseId = value;
            }
        }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        private string CourseName;
        public string Name
        {
            get
            {
                return CourseName;
            }
            set
            {
                CourseName = value;
            }
        }
        private int CourseCredit;
        public int Credit
        {
            set
            {
                if (value < 0)
                    throw new Exception("Credit can't be negative");
                else
                    CourseCredit = value;
            }
            get
            {
                return CourseCredit;
            }
        }

        public Course()
        {
            Credit = Id = 0;
            Name = "";
        }

        public Course(int _Id, string _Name, int _credit)
        {
            Id = _Id;
            Name = _Name;
            Credit = _credit;
        }
    }

}
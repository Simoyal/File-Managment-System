using System;
using System.Runtime.InteropServices;

namespace FMS_adapter
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class DirEntry
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string _filename;
        public string filename { get { return _filename; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string _fileOwner;
        public string fileOwner { get { return _fileOwner; } }

        int _fileAddr;
        public int fileAddr { get { return _fileAddr; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string _crDate;
        public string crDate { get { return _crDate.Substring(3, 2) + "/" + _crDate.Substring(0, 2) + "/" + _crDate.Substring(6); } }

        uint _fileSize;
        public uint fileSize { get { return _fileSize; } }

        int _eofRecNr;
        public int eofRecNr { get { return _eofRecNr; } }

        int _maxRecSize;
        public int maxRecSize { get { return _maxRecSize; } }

        int _actualRecSize;
        public int actualRecSize { get { return _actualRecSize; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 2)]
        string _recFormat;
        public string recFormat { get { return _recFormat; } }

        int _keyOffset;
        public int keyOffset { get { return _keyOffset; } }

        int _keySize;
        public int keySize { get { return _keySize; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 2)]
        string _keyType;
        public string keyType { get { return _keyType; } }

        int _entryStatus;
        public int entryStatus { get { return _entryStatus; } }
    }
}

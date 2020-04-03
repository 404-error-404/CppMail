using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // 这是一个调用dll的例子
        // 下边两行，将dll中的函数引入，这里引入的是一个test函数，直接返回整数 1
        [System.Runtime.InteropServices.DllImport(@"K:\C# Project\mail_client\Release\mail_dll.dll", EntryPoint = "test")]
        public static extern int test();

        // 这是一个调用dll的例子
        // 下边两行，将dll中的函数引入，这里引入的是一个test函数，直接返回整数 1
        [System.Runtime.InteropServices.DllImport(@"K:\C++ Project\CppMail\Debug\Dll1.dll", EntryPoint = "MyClass")]
        public static extern int MyClass();

        private void button1_Click(object sender, EventArgs e)
        {
            MyClass ss = new MyClass();
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
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
        // 下边是将dll中的函数引入
        [System.Runtime.InteropServices.DllImport(@"K:\C++ Project\CppMail\Debug\Dll1.dll", EntryPoint = "send_mail", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = false)]
        public static extern int send_mail(
                [MarshalAs(UnmanagedType.LPStr)] string account,    // 账号
                [MarshalAs(UnmanagedType.LPStr)] string password,   // 密码，QQ邮箱需要是QQ邮箱授权码
                [MarshalAs(UnmanagedType.LPStr)] string site,       // 网址,smtp.qq.com等
                [MarshalAs(UnmanagedType.LPStr)] string receiver,   // 接受者
                [MarshalAs(UnmanagedType.LPStr)] string subject,    // 主题
                [MarshalAs(UnmanagedType.LPStr)] string mail_data,  // 邮件内容
                int port = 25                                       // 端口号，默认是25（SMTP服务默认端口号）
            );

        


        private void button1_Click(object sender, EventArgs e)
        {
            // 声明相关参数
            string account = "1791781644@qq.com";
            string password = "vdpoensbauvabbch";
            string site = "smtp.qq.com";
            string receiver = "m15827603552_1@163.com";
            // receiver = "1791781644@qq.com";
            string subject = "这是一个dll测试";
            string mail_data = "我看看能传多长的邮件这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容这是邮件内容";
            // mail_data = "sadkhsadkjh";
            int port = 25;
            // 发邮件并获得返回值，返回值意义如下:
            /*
             * {0, "邮件发送成功"},
		     * {-1, "域名解析到IPv4地址错误，请核对域名或者检查网络连接"},
		     * {-2, "数据发送出错"},
		     * {-3, "数据接收出错"},
		     * {-4, "服务器连接失败，请核对端口号或者检查网络连接"},
		     * {-5, "账号或密码错误，请核对"},
		     * {-6, "收信人格式错误"},
		     * {-7, "邮件发送失败，请检查邮件正文"},
		     * {-8, "断开连接时出现错误但邮件发送成功"}
             * 
             */
            int i = send_mail(account, password, site, receiver, subject, mail_data, port);
            button1.Text = Convert.ToString(i);
        }
    }
}

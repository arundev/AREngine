using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Windows.Forms;
using mframwork;

namespace editor
{
    public partial class MainForm : Form
    {
        public static EngineWrap gEngineWrap;

        public MainForm()
        {
            InitializeComponent();

            gEngineWrap = new EngineWrap();
            gEngineWrap.Init(renderPanel.Width, renderPanel.Height, renderPanel.Handle, Process.GetCurrentProcess().Handle);
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            base.OnPaint(e);

            gEngineWrap.Update();
        }
    }
}

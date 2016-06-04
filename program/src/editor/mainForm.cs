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
        public MainForm()
        {
            InitializeComponent();

            Global.gEngineWrap = new EngineWrap();
            Global.gEngineWrap.Init(renderPanel.Width, renderPanel.Height, renderPanel.Handle, Process.GetCurrentProcess().Handle);
        }
    }
}

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
        MVector2 mouseLocal = new MVector2();

        public MainForm()
        {
            InitializeComponent();

            Global.gEngineWrap = new EngineWrap();
            Global.gEngineWrap.Init(renderPanel.Width, renderPanel.Height, renderPanel.Handle, Process.GetCurrentProcess().Handle);

            this.KeyDown += OnKeyDown;
        }

        protected void OnKeyDown(Object obj, KeyEventArgs e)
        {
            switch (e.KeyData)
            {
                case Keys.W: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.W); break;
                case Keys.S: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.S); break;
                case Keys.A: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.A); break;
                case Keys.D: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.D); break;
                case Keys.Q: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.Q); break;
                case Keys.E: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.E); break;
                default:
                    Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.Undefine);
                    break;
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void renderPanel_Paint(object sender, PaintEventArgs e)
        {
            Global.gEngineWrap.Update();
        }

        private void renderPanel_MouseDown(object sender, MouseEventArgs e)
        {
            mouseLocal.x = e.Location.X;
            mouseLocal.y = e.Location.Y;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:
                    Global.gEngineWrap.OnMouseDown(mframwork.MKeyCode.MouseLeft, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Right:
                    Global.gEngineWrap.OnMouseDown(mframwork.MKeyCode.MouseRight, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Middle:
                    Global.gEngineWrap.OnMouseDown(mframwork.MKeyCode.MouseMid, mouseLocal);
                    break;
                default:
                    break;
            }
        }

        private void renderPanel_MouseMove(object sender, MouseEventArgs e)
        {
            mouseLocal.x = e.Location.X;
            mouseLocal.y = e.Location.Y;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:
                    Global.gEngineWrap.OnMouseMove(mframwork.MKeyCode.MouseLeft, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Right:
                    Global.gEngineWrap.OnMouseMove(mframwork.MKeyCode.MouseRight, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Middle:
                    Global.gEngineWrap.OnMouseMove(mframwork.MKeyCode.MouseMid, mouseLocal);
                    break;
                default:
                    break;
            }
        }

        private void renderPanel_MouseUp(object sender, MouseEventArgs e)
        {
            mouseLocal.x = e.Location.X;
            mouseLocal.y = e.Location.Y;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:
                    Global.gEngineWrap.OnMouseUp(mframwork.MKeyCode.MouseLeft, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Right:
                    Global.gEngineWrap.OnMouseUp(mframwork.MKeyCode.MouseRight, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Middle:
                    Global.gEngineWrap.OnMouseUp(mframwork.MKeyCode.MouseMid, mouseLocal);
                    break;
                default:
                    break;
            }
        }
    }
}

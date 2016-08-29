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
using Xilath;
using Xilath.Core;

namespace editor
{
    public partial class MainForm : Form
    {
        public static MainForm instance;
        MVector2 mouseLocal = new MVector2();
        
        public MainForm()
        {
            instance = this;

            InitializeComponent();
            KeyPreview = true;

            Global.gEngineWrap = new EngineWrap();
            Global.gEngineWrap.Init(renderPanel.Width, renderPanel.Height, renderPanel.Handle, Process.GetCurrentProcess().Handle);
            Application.Idle += new EventHandler(MainForm.instance.Render);
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

        private bool AppStillIdle
        {
            get
            {
                NativeMethods.Message msg;
                return !NativeMethods.PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }
        public void Render(object sender, EventArgs args)
        {
            while (AppStillIdle)
            {
                Global.gEngineWrap.Update();
            }
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

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
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

        private void MainForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case 'W': Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.W); break;
                case 'S': Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.S); break;
                case 'A': Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.A); break;
                case 'D': Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.D); break;
                case 'Q': Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.Q); break;
                case 'E': Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.E); break;
                default:
                    Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.Undefine);
                    break;
            }
        }
    }
}

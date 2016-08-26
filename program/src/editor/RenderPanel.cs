using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using mframwork;

namespace editor
{
    public class RenderPanel : Panel
    {
        public RenderPanel()
        {
            this.MouseDown += new MouseEventHandler(OnMouseDown);
            this.MouseUp += new MouseEventHandler(OnMouseUp);
            this.MouseMove += new MouseEventHandler(OnMouseMove);
            this.KeyDown += new KeyEventHandler(OnKeyDown);
            this.KeyUp += new KeyEventHandler(OnKeyUp);
        }

        MVector2 mouseLocal = new MVector2();

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            return true;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Global.gEngineWrap.Update();
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);            
        }

        protected void OnKeyPress(Object obj, KeyPressEventArgs e)
        {
            int i = 0;
            return;
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

        protected void OnKeyUp(Object obj, KeyEventArgs e)
        {
            switch (e.KeyData)
            {
                case Keys.W: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.W); break;
                case Keys.S: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.S); break;
                case Keys.A: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.A); break;
                case Keys.D: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.D); break;
                case Keys.Q: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.Q); break;
                case Keys.E: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.E); break;
                default:
                    Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.Undefine);
                    break;
            }
        }

        protected void OnMouseDown(Object obj, MouseEventArgs e)
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

        protected void OnMouseMove(Object obj, MouseEventArgs e)
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

        protected void OnMouseUp(Object obj, MouseEventArgs e)
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
